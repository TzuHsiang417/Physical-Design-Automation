#ifndef _BLOCK_H
#define _BLOCK_H

#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <algorithm>
#include <utility>
#include "parameter.h"

using namespace std;

struct POINT
{
    int x, y;
    POINT() {}
    POINT(int a, int b)
    {
        x = a;
        y = b;
    }
};

struct TILE
{
    bool type;
    struct POINT coordinate;
    int width, height;
    struct TILE *BL;
    struct TILE *LB;
    struct TILE *RT;
    struct TILE *TR;
    TILE() {}
    TILE(struct POINT a, int b, int c, bool d) : coordinate(a), width(b), height(c), type(d)
    {
        BL = NULL;
        LB = NULL;
        RT = NULL;
        TR = NULL;
    }
};

TILE *Point_Finding(POINT goal);
TILE *Block_Insertion(POINT p, int wid, int hei);
TILE *Seperate_Horizon(TILE *tile, int h);
TILE *Seperate_Vertical(TILE *tile, int v);
void Merge(TILE *tile_a, TILE *tile_b);
pair<int, int> Neighbor_Finding(TILE *tile);
void create_file(char *argv, vector<pair<int, TILE*> >&block, vector<POINT>&p);
void create_drawing_file(char *argv, vector<pair<int, TILE*> >&block);

inline int tile_num;
inline vector<TILE*> s;
inline int outline_width, outline_height;
inline TILE *base;

#endif