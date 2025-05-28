#ifndef _ROUTER_H
#define _ROUTER_H

#include <vector>
#include <list>
#include <time.h>

using namespace std;

class Line_Segment
{
    int track, s_pos, e_pos;
    friend class Pin_info;
    friend class Router;
    friend class Graph;

    public:
        Line_Segment() {}
        Line_Segment(int a, int b): s_pos(a), e_pos(b) {}
};

class Pin_Info
{
    private:
        int number;
        vector<int> top_position, bottom_position;
        int merge_pin, merge_track;
        friend class Router;

        Pin_Info(int a): number(a) {}
};

class Router
{
    private:
        vector<int> top_side, bottom_side, merge_side;
        vector<Pin_Info> look_up;
        int vertex_num;
        vector<list<int> > edge;
        vector<int> Predecessor_amount;
        vector<Line_Segment> line_info;
        int num_track;

        void Bottom_merge();
        void create_graph();
        void AddEdge(int from, int to);
    public:
        Router() {}
        bool ReadFile(char *argv);
        // void debug_out();
        void Left_edge();
        void CreateOutputFile(char *argv);
};

inline int SEED = 413;

#endif