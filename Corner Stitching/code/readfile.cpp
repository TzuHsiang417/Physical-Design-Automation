#include <iostream>
#include "readfile.h"
#include "block.h"

void Get_File(char *argv, vector<vector<string>> &testcase)
{
    ifstream ifile(argv, ios::in);

    if (!ifile)
    {
        cout << "File can not be opened." << endl;
    }

    string line;
    const char *cut = " "; // token

    while (getline(ifile, line))
    {
        vector<string> word;

        
        char *lineCharArray;
        const int len = line.length();
        lineCharArray = new char[len + 1];
        strcpy(lineCharArray, line.c_str());

        char *p; 
        p = strtok(lineCharArray, cut);
        
        while (p)
        {
            word.push_back(p);
            p = strtok(NULL, cut);
        }

        testcase.push_back(word);
    }

    ifile.close();
}

void create_file(char *argv, vector<pair<int, TILE*> >&block, vector<POINT>&p)    //create output file
{
    ofstream ofile(argv, ios::out);
    if(ofile.is_open())
    {
        ofile << tile_num << endl;
        for(int i = 0; i < block.size(); i++)
        {
            pair<int, int> a = Neighbor_Finding(block[i].second);
            ofile << block[i].first << " " << a.first << " " << a.second << endl;
        }
        for(int i = 0; i < p.size(); i++)
            ofile << p[i].x << " " << p[i].y << endl;
    }
    else
        cout << "The file can not be saved.\n";
    ofile.close();
}

void create_drawing_file(char *argv, vector<pair<int, TILE*> >&block)
{
    char *drawing_file = "drawing_";
    char file_tmp[100] = {0};
    strcat(file_tmp, drawing_file);
    strcat(file_tmp, argv);
    ofstream ofile(file_tmp, ios::out);
    if(ofile.is_open())
    {
        ofile << tile_num << endl;
        ofile << outline_width << " " << outline_height << endl;
        /*for(int i = 0; i < block.size(); i++)
        {
            ofile << block[i].first << " " << block[i].second->coordinate.x << " " << block[i].second->coordinate.y << " " << block[i].second->width << " " << block[i].second->height << endl;
        }*/
        for(int i = 0; i < s.size(); i++)
        {
            if(s[i]->type == BLOCK)
                ofile << "1 " << s[i]->coordinate.x << " " << s[i]->coordinate.y << " " << s[i]->width << " " << s[i]->height << endl;
            else
                ofile << "-1 " << s[i]->coordinate.x << " " << s[i]->coordinate.y << " " << s[i]->width << " " << s[i]->height << endl;
        }
    }
    else
        cout << "The drawing file can not be saved.\n";
    ofile.close();
}