#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include "router.h"

void Router::create_graph()
{
    line_info.resize(look_up.size());
    bool locked[look_up.size()];
    // locked[0] = 1;
    // for(int i=1; i<vertex_num; i++)
    //     locked[i] = 0;

    for(int i=1; i<look_up.size(); i++)
    {
        int start;
        int end;

        if(look_up[i].bottom_position.size() == 0)
        {
            start = look_up[i].top_position[0];
            end = look_up[i].top_position[look_up[i].top_position.size()-1];
        }
        else if(look_up[i].top_position.size() == 0)
        {
            start = look_up[i].merge_pin;
            end = look_up[i].merge_pin;
        }
        else
        {
            start = min(look_up[i].top_position[0], look_up[i].merge_pin);
            end = max(look_up[i].top_position[look_up[i].top_position.size()-1], look_up[i].merge_pin);
        }

        line_info[i].s_pos = start;
        line_info[i].e_pos = end;
    }

    edge.clear();
    edge.resize(vertex_num);
    Predecessor_amount.resize(vertex_num);

    for(int i=0; i<vertex_num; i++)
        Predecessor_amount[i] = 0; 

    for(int i=0; i<top_side.size(); i++)
    {
        if(top_side[i] == 0 || merge_side[i] == 0 || top_side[i] == merge_side[i])
            continue;
        else
        {
            AddEdge(top_side[i], merge_side[i]);
            Predecessor_amount[merge_side[i]]++;
        }
    }
}

void Router::AddEdge(int from, int to)
{
    edge[from].push_back(to);
}

bool Router::ReadFile(char *argv)
{
    ifstream ifile(argv, ios::in);
    vector<int> pin_in;
    map<int, int> pin_change;
    int n = 1;

    vertex_num = 0;

    look_up.push_back(Pin_Info(0));

    if(!ifile)
    {
        ifile.close();
        return 0;
    }
    else
    {
        int in, change;
        while(ifile >> in)
        {
            if(in == 0)
                change = 0;
            else if(pin_change[in] == 0)
            {
                look_up.push_back(Pin_Info(in));
                pin_change[in] = n;
                change = n;
                n++;
            }
            else
                change = pin_change[in];

            pin_in.push_back(change);
        }
        
        ifile.close();
    }

    for(int i=0; i<pin_in.size()/2; i++)
    {
        top_side.push_back(pin_in[i]);
        bottom_side.push_back(pin_in[i + pin_in.size()/2]);

        look_up[pin_in[i]].top_position.push_back(i);
        look_up[pin_in[i + pin_in.size()/2]].bottom_position.push_back(i);
    }

    vertex_num = look_up.size();

    return 1;
}

void Router::Bottom_merge()
{
    merge_side.resize(top_side.size());
    for(int i=0; i<top_side.size(); i++)
        merge_side[i] = 0;

    vector<Line_Segment> line;
    for(int i=1; i<look_up.size(); i++)
    {   
        if(look_up[i].bottom_position.size() == 0)
            continue;
        else if(look_up[i].bottom_position.size() == 1)
        {
            look_up[i].merge_pin = look_up[i].bottom_position[0];
            look_up[i].merge_track = 0;
            merge_side[look_up[i].merge_pin] = i;
            continue;
        }

        line.push_back(Line_Segment(look_up[i].bottom_position[0], look_up[i].bottom_position[look_up[i].bottom_position.size() - 1]));
        int tmp = rand() % look_up[i].bottom_position.size();
        look_up[i].merge_pin = look_up[i].bottom_position[tmp];
        merge_side[look_up[i].merge_pin] = i;
    }
    
    sort(line.begin(), line.end(), [](Line_Segment a, Line_Segment b){
        return a.s_pos < b.s_pos;
    });

    int t = 1;
    while(line.size() != 0)
    {
        int watermark = -1;
        for(int i=0; i<line.size();)
        {
            if(line[i].s_pos > watermark)
            {
                look_up[bottom_side[line[i].s_pos]].merge_track = t;
                watermark = line[i].e_pos;
                line.erase(line.begin() + i);
                continue;
            }
            i++;
        }

        t++;
    }
    
    num_track = 0;
    num_track = num_track + t - 1;
}

void Router::Left_edge()
{
    int num_OK = 0;
    int track = 1;

    while(num_OK != vertex_num)
    {
        Bottom_merge();
        create_graph();

        track = 1;
        int watermark = -1;

        num_OK = 1;
        for(int i=1; i<look_up.size(); i++)
        {
            if(look_up[i].top_position.size() == 0)
            {
                Predecessor_amount[i] = -1;
                num_OK++;
            }
        }

        while(num_OK < vertex_num)
        {
            vector<int> nets;
            for(int i=1; i<vertex_num; i++)
            {
                if(Predecessor_amount[i] == 0)
                {
                    Predecessor_amount[i] = -1;
                    nets.push_back(i);
                }
            }

            if(nets.size() == 0)
                break;

            for(int i=0; i<nets.size(); i++)
            {
                if(line_info[nets[i]].s_pos > watermark)
                {
                    line_info[nets[i]].track = track;
                    watermark = line_info[nets[i]].e_pos;

                    for(list<int>::iterator j=edge[nets[i]].begin(); j!=edge[nets[i]].end(); j++)
                        (Predecessor_amount[*j])--;

                    num_OK++;
                }
                else
                {
                    Predecessor_amount[nets[i]] = 0;
                }
            }

            track++;
            watermark = -1;
        }
        SEED = rand();
        srand(SEED);
    }

    num_track = num_track + track - 1;
    cout << "track = " << num_track << endl;
    return;
}

// void Router::debug_out()
// {
//     for(int i=0; i<top_side.size(); i++)
//     {
//         cout << top_side[i] << " ";
//     }
//     cout << endl;
//     for(int i=0; i<top_side.size(); i++)
//     {
//         cout << bottom_side[i] << " ";
//     }

//     cout << "vertex " << vertex_num << endl;
//     for(int i=0; i<vertex_num; i++)
//     {
//         cout << look_up[i].number << " " << look_up[i].merge_pin  << " " << line_info[i].track << endl;
//     }
//     cout << num_track << endl;
// }

void Router::CreateOutputFile(char *argv)
{
    cout.setf(ios::fixed);      //將輸出不以科學記號顯示
    ofstream ofile(argv, ios::out);

    if(ofile.is_open())
    {
        for(int i=1; i<look_up.size(); i++)
        {
            ofile << ".begin " << look_up[i].number << endl;
    
            int real_track = num_track - line_info[i].track + 1;
            
            if(line_info[i].s_pos != line_info[i].e_pos)
                ofile << ".H " << line_info[i].s_pos << " " << real_track << " " << line_info[i].e_pos << endl;

            bool set_merge_vertical = 1;

            if(look_up[i].top_position.size() > 0)
            {
                for(vector<int>::iterator j=look_up[i].top_position.begin(); j!=look_up[i].top_position.end(); j++)
                {
                    if(*j == look_up[i].merge_pin)
                    {
                        ofile << ".V " << *j << " " << look_up[i].merge_track << " " << num_track+1 << endl;
                        set_merge_vertical = 0;
                    }
                    else
                        ofile << ".V " << *j << " " << real_track << " " << num_track+1 << endl;
                }

                if(set_merge_vertical && look_up[i].bottom_position.size() > 0)
                    ofile << ".V " << look_up[i].merge_pin << " " << look_up[i].merge_track << " " << real_track << endl;
            }

            if(look_up[i].bottom_position.size() > 1)
            {
                ofile << ".H " << *look_up[i].bottom_position.begin() << " " << look_up[i].merge_track << " " << *(look_up[i].bottom_position.end() - 1) << endl;
                for(vector<int>::iterator j=look_up[i].bottom_position.begin(); j!=look_up[i].bottom_position.end(); j++)
                {
                    ofile << ".V " << *j << " 0 " << look_up[i].merge_track << endl;
                }
            }

            ofile << ".end" << endl;
        }
    }
    ofile.close();

    return;
}