#ifndef _FLOORPLAN_H
#define _FLOORPLAN_H

#include <iostream>
#include <vector>
#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <time.h>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <queue>
#include <cstdlib>
#include "parameter.h"
#include "btree.h"

class FloorPlanning{
    vector<Block> block_info;
    vector<pair<int, int> > terminal_info;
    int outline_width, outline_height;
    int num_block, num_terminal;
    int root;
    vector<Btree> tree;
    Cost_info result_cost;
    int max_height_node, max_width_node;
    vector<vector<pair<bool, int> > > netlist;
    bool in_fixed_outline;
    double ALPHA;

    public:
        FloorPlanning(double a):ALPHA(a){}
        bool ReadFile(char *argv1, char *argv2);
        void InitialBtree();
        Cost_info cost();
        void Op1();
        void Op2();
        void Op3();
        void Op4();
        void Op5();
        void Swap(int node1, int node2);
        void Simulated_Annealing();
        void set_coordinate(int node, int* width, int* height, vector<int> &contour, bool child);
        void CreateOutputFile(char *argv);
        void CreateDrawingFile(char *argv);
        int HPWL();
};

inline clock_t t1, t2;

#endif