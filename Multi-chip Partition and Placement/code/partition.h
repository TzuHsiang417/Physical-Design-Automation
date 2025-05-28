#ifndef _PARTITION_H
#define _PARTITION_H

#include <vector>
#include <map>
#include <time.h>
#include <algorithm>

using namespace std;

class CELL{
    bool layer;
    int x, y;
    int width, height;
    friend class Placement;
    friend class Partition;

    public:
        CELL(int a, int b, int c, int d): x(a), y(b), width(c), height(d){}
};
typedef CELL TERMINAL;

class INTERSECT_CELL{
    int id;
    int area;
    friend class Partition;

    public:
        INTERSECT_CELL(int a, int b): id(a), area(b){}
};

class Partition{
    int num_cell;
    vector<vector<bool> > graph;
    vector<vector<INTERSECT_CELL> > edge;
    map<int, vector<int> > bucket;
    vector<CELL> cells;
    vector<int> gain;
    vector<bool> current_layer;
    vector<bool> locked;
    long long min_area;
    long long area[2] = {0, 0};

    public:
        Partition(int a, vector<CELL> &cells_PM);
        bool intersect(CELL c1, CELL c2);
        int intersect_area(CELL c1, CELL c2);
        void create_graph();
        vector<CELL> FM_Algorithm();
        void update_gain(int cell_to_move, bool old_layer);
        void update_bucket(int curr_cell, int prev_gain);
};

inline clock_t t1;
inline double PT_time;

#endif