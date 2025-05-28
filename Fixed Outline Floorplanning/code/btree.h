#ifndef _BTREE_H
#define _BTREE_H

#include <string>

using namespace std;

class Block{
    string name;
    int x, y;
    int width, height;
    friend class FloorPlanning;
    friend class Btree;

    public:
        Block(string a, int b, int c):name(a), width(b), height(c){} 
};

class Btree{
    int id;
    int parent;
    int left_child;
    int right_child;
    friend class FloorPlanning;

    public:
        Btree(int a):id(a){
            parent = -1;
            left_child = -1;
            right_child = -1;
        }
};

class Cost_info{
    int cost;
    int area;
    int wirelength;
    int width;
    int height;
    friend class FloorPlanning;

    public:
        Cost_info() {}
        Cost_info(int a, int b, int c, int d, int e):cost(a), area(b), wirelength(c), width(d), height(e){}
};

#endif