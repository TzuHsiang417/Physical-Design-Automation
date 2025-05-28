#include "floorplan.h"

bool FloorPlanning::ReadFile(char *argv1, char *argv2)
{
    ifstream ifile1(argv1, ios::in);
    string title1, title2, title3;

    map<string, pair<bool, int> > look_up;

    if(!ifile1)
    {
        ifile1.close();
        return 0;
    }
    else
    {
        ifile1 >> title1 >> outline_width >> outline_height;
        ifile1 >> title2 >> num_block;
        ifile1 >> title3 >> num_terminal;

        string name;
        int width, height;
        int x_coordinate, y_coordinate;

        for (int i=0; i<num_block; i++)
        {
            ifile1 >> name >> width >> height;
            block_info.push_back(Block(name, width, height));
            look_up[name] = make_pair(MODULE, i);
        }
        
        for (int i=0; i<num_terminal; i++)
        {
            string tmp;
            ifile1 >> name >> tmp >> x_coordinate >> y_coordinate;
            terminal_info.push_back(make_pair(x_coordinate, y_coordinate));
            look_up[name] = make_pair(TERMINAL, i);
        }
        
        ifile1.close();
    }

    ifstream ifile2(argv2, ios::in);
    string title4;
    int num_net;

    if(!ifile2)
    {
        ifile2.close();
        return 0;
    }
    else
    {
        ifile2 >> title4 >> num_net;
        for(int i=0; i<num_net; i++)
        {
            int net_degree;
            ifile2 >> title4 >> net_degree;
            vector<pair<bool, int> > node_tmp;
            for(int j=0; j<net_degree; j++)
            {
                string node_name;
                ifile2 >> node_name;
                node_tmp.push_back(look_up[node_name]);
            }
            netlist.push_back(node_tmp);
        }

        ifile2.close();
    }

    return 1;
}


void FloorPlanning::CreateOutputFile(char *argv)
{
    cout.setf(ios::fixed);      
    ofstream ofile(argv, ios::out);
    vector<Block>::iterator it_b;

    if(ofile.is_open())
    {
        ofile << result_cost.cost << endl;
        ofile << result_cost.wirelength << endl;
        ofile << result_cost.area << endl;
        ofile << result_cost.width << " " << result_cost.height << endl;
        ofile << clock() - t1 << endl;
        for(it_b = block_info.begin(); it_b != block_info.end(); it_b++)
        {
            ofile << it_b->name << " ";
            ofile << it_b->x << " " << it_b->y << " ";
            ofile << it_b->x + it_b->width << " " << it_b->y + it_b->height << endl;
        }  
    }
    ofile.close();

    return;
}

void FloorPlanning::CreateDrawingFile(char *argv)
{
    cout.setf(ios::fixed);
    ofstream ofile(argv, ios::out);
    vector<Block>::iterator it_b;

    if(ofile.is_open())
    {
        ofile << num_block << endl;
        if(outline_width > outline_height)
            ofile << outline_width << " " << outline_width << endl;
        else
            ofile << outline_height << " " << outline_height << endl;

        ofile << "0 0 0 " << outline_width << " " << outline_height << endl;
        for(it_b = block_info.begin(); it_b != block_info.end(); it_b++)
        {
            ofile << 1 << " ";
            ofile << it_b->x << " " << it_b->y << " ";
            ofile << it_b->width << " " << it_b->height << endl;
        }
        ofile << "0 0 0 " << result_cost.width << " " << result_cost.height << endl;
        
    }
    ofile.close();

    return;
}