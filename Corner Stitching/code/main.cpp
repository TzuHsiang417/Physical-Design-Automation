#include <iostream>
#include "readfile.h"
#include "parameter.h"
#include "block.h"

using namespace std;

struct vector_sort
{
    bool operator()(pair<int, TILE *> a, pair<int, TILE *> b) { return a.first < b.first; } // 升序排列
} cmp;

int main(int argc, char *argv[])
{
    vector<vector<string>> testcase;
    Get_File(argv[1], testcase);

    vector<pair<int, TILE *>> block;

    //TILE *base;
    vector<POINT> p;

    cout << "The program begin." << endl;

    for(int i = 0; i < testcase.size(); i++)
    {
        if (i == 0)
        {
            tile_num = 1;
            base = new TILE(POINT(0, 0), stoi(testcase[0][0]), stoi(testcase[0][1]), SPACE);
            s.push_back(base);
            outline_width = stoi(testcase[0][0]);
            outline_height = stoi(testcase[0][1]);
        }
        else if (testcase[i][0] == "P")
            p.push_back(Point_Finding(POINT(stoi(testcase[i][1]), stoi(testcase[i][2])))->coordinate);
        else
        {
            TILE *block_tmp = Block_Insertion(POINT(stoi(testcase[i][1]), stoi(testcase[i][2])), stoi(testcase[i][3]), stoi(testcase[i][4]));
            block.push_back(make_pair(stoi(testcase[i][0]), block_tmp));
        }
    }

    sort(block.begin(), block.end(), cmp);

    create_file(argv[argc-1], block, p);
    create_drawing_file(argv[argc-1], block);

    cout << "The program ended." << endl;

    return 0;
}