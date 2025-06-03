#include <iostream>
#include "block.h"

TILE *Point_Finding(POINT goal)
{
    TILE *position;
    position = base;
    int test = 0;
    while (1)
    {
        if (goal.y < BOTTOM(position))
            position = LB(position);
        else if (goal.y >= TOP(position))
            position = RT(position);
        else if (goal.x < LEFT(position))
            position = BL(position);
        else if (goal.x >= RIGHT(position))
            position = TR(position);
        else
            return position;
        test++;
    }
}

TILE *Block_Insertion(POINT p, int wid, int hei)
{
    TILE *tile = Point_Finding(p);

    if (p.y > BOTTOM(tile))
        tile = Seperate_Horizon(tile, p.y);

    TILE *inserted_tmp = NULL;

    while (tile != NULL && p.y + hei >= TOP(tile))
    {
        if (LEFT(tile) < p.x)
        {
            tile = Seperate_Vertical(tile, p.x);
            TILE *merge_tile = BL(tile);
            Merge(merge_tile, merge_tile->LB);
        }

        if (RIGHT(tile) > p.x + wid)
        {
            TILE *merge_tile = Seperate_Vertical(tile, p.x + wid);
            Merge(merge_tile, merge_tile->LB);
        }

        if (inserted_tmp != NULL)
            Merge(tile, inserted_tmp);

        inserted_tmp = tile;
        tile = RT(tile);
    }

    if (tile != NULL && TOP(tile) > p.y + hei && BOTTOM(tile) < p.y + hei)
    {
        TILE *new_tile = Seperate_Horizon(tile, p.y + hei);

        if (LEFT(tile) < p.x)
        {
            tile = Seperate_Vertical(tile, p.x);
            TILE *merge_tile = BL(tile);
            Merge(merge_tile, merge_tile->LB);
        }

        if (RIGHT(tile) > p.x + wid)
        {
            TILE *merge_tile = Seperate_Vertical(tile, p.x + wid);
            Merge(merge_tile, merge_tile->LB);
        }

        if (inserted_tmp != NULL)
            Merge(tile, inserted_tmp);

        inserted_tmp = tile;
    }
    inserted_tmp->type = BLOCK;

    return inserted_tmp;
}

TILE *Seperate_Horizon(TILE *tile, int p_of_y)
{
    TILE *newtile = new TILE();
    newtile->coordinate.x = LEFT(tile);
    newtile->coordinate.y = p_of_y;
    newtile->width = tile->width;
    newtile->height = TOP(tile) - p_of_y;
    newtile->LB = tile;
    newtile->RT = RT(tile);
    newtile->TR = TR(tile);
    newtile->type = SPACE;

    TILE *search;

    //update the information of adjacent block
    search = TR(tile);
    if (search != NULL)
    {
        for (; search != NULL && BOTTOM(search) >= p_of_y; search = LB(search)) // right
            search->BL = newtile;
    }
    tile->TR = search;

    search = RT(tile);
    if (RT(tile) != NULL)
    {
        for (; search != NULL && LB(search) == tile; search = BL(search)) // top
            search->LB = newtile;
    }
    tile->RT = newtile;

    search = BL(tile);
    while (search != NULL && TOP(search) <= p_of_y)
        search = RT(search);
    newtile->BL = search;

    if (search != NULL)
    {
        for (; search != NULL && TR(search) == tile; search = RT(search)) // left
            search->TR = newtile;
    }

    tile->height = p_of_y - BOTTOM(tile);

    s.push_back(newtile);

    tile_num++;

    return (newtile);
}

TILE *Seperate_Vertical(TILE *tile, int v)
{
    TILE *newtile = new TILE();
    newtile->coordinate.x = v;
    newtile->coordinate.y = BOTTOM(tile);
    newtile->width = RIGHT(tile) - v;
    newtile->height = tile->height;
    newtile->BL = tile;
    newtile->RT = RT(tile);
    newtile->TR = TR(tile);
    newtile->type = SPACE;

    TILE *search;
    
    search = RT(tile);
    if (search != NULL)
    {
        for (; search != NULL && LEFT(search) >= v; search = BL(search)) // top
            search->LB = newtile;
    }
    tile->RT = search;

    search = TR(tile);
    if (search != NULL)
    {
        for (; search != NULL && BL(search) == tile; search = LB(search)) // right
            search->BL = newtile;
    }
    tile->TR = newtile;


    search = LB(tile);
    while (search != NULL && RIGHT(search) <= v)
        search = TR(search);
    newtile->LB = search;

    if (search != NULL)
    {
        for (; search != NULL && RT(search) == tile; search = TR(search)) // bottom
            search->RT = newtile;
    }

    tile->width = v - LEFT(tile);

    s.push_back(newtile);

    tile_num++;

    return (newtile);
}

void Merge(TILE *tile_a, TILE *tile_b)
{
    if (tile_a == NULL || tile_b == NULL)
        return;

    if(tile_a->type == BLOCK || tile_b->type == BLOCK)
        return;

    if (LEFT(tile_a) != LEFT(tile_b) || RIGHT(tile_a) != RIGHT(tile_b) || (TOP(tile_a) != BOTTOM(tile_b) && TOP(tile_b) != BOTTOM(tile_a)))
        return;

    if (BOTTOM(tile_a) < BOTTOM(tile_b))
    {
        TILE *search;
        for (search = RT(tile_b); search != NULL && LB(search) == tile_b; search = BL(search))
            search->LB = tile_a;

        tile_a->RT = RT(tile_b);
        tile_a->TR = TR(tile_b);
    }
    else if (BOTTOM(tile_a) >= BOTTOM(tile_b))
    {
        TILE *search;
        for (search = LB(tile_b); search != NULL && RT(search) == tile_b; search = TR(search))
            search->RT = tile_a;

        tile_a->LB = LB(tile_b);
        tile_a->BL = BL(tile_b);
        tile_a->coordinate.y = BOTTOM(tile_b);
    }
    
    tile_a->height = tile_a->height + tile_b->height;

    TILE *search;
    for (search = TR(tile_b); search != NULL && BL(search) == tile_b; search = LB(search))
        search->BL = tile_a;

    for (search = BL(tile_b); search != NULL && TR(search) == tile_b; search = RT(search))
        search->TR = tile_a;

    tile_num--;
    s.erase(remove(s.begin(), s.end(), tile_b), s.end());

    if(base == tile_b)
        base = tile_a;

    delete tile_b;

    return;
}

pair<int, int> Neighbor_Finding(TILE *tile)
{
    int block_num = 0;
    int space_num = 0;

    TILE *search;

    search = RT(tile);  // top
    if (search != NULL)
    {
        for (; search != NULL && RIGHT(search) > LEFT(tile); search = BL(search))
        {
            if (search == NULL)
                break;
            if (search->type == BLOCK)
                block_num++;
            else
                space_num++;
        }
    }

    search = BL(tile);  // left
    if(search != NULL)
    {
        for (; search != NULL && BOTTOM(search) < TOP(tile); search = RT(search)) 
        {
            if (search == NULL)
                break;
            if (search->type == BLOCK)
                block_num++;
            else
                space_num++;
        }
    }

    search = LB(tile);  // bottom
    if(search != NULL)
    {
        for (; search != NULL && LEFT(search) < RIGHT(tile); search = TR(search)) 
        {
            if (search == NULL)
                break;
            if (search->type == BLOCK)
                block_num++;
            else
                space_num++;
        }
    }

    search = TR(tile);  // right
    if (search != NULL)
    {
        for (; search != NULL && TOP(search) > BOTTOM(tile); search = LB(search)) 
        {
            if (search == NULL)
                break;
            if (search->type == BLOCK)
                block_num++;
            else
                space_num++;
        }
    }

    return make_pair(block_num, space_num);
}