#include "floorplan.h"


/*void FloorPlanning::InitialBtree()  //create initial B*-tree
{
    int i = 0;
    root = new Btree(i);
    i++;

    queue<Btree*> q;
    q.push(root);
    tree.push_back(root);

    while(!q.empty())
    {
        Btree* parent = q.front();
        q.pop();

        if(i < num_block)   //set left child
        {
            Btree *left_child = new Btree(i);
            parent->left_child = left_child;
            left_child->parent = parent;
            i++;

            q.push(left_child);
            tree.push_back(left_child);
        }

        if(i < num_block)
        {
            Btree *right_child = new Btree(i);
            parent->right_child = right_child;
            right_child->parent = parent;
            i++;

            q.push(right_child);
            tree.push_back(right_child);
        }
    }

    return;
}*/

void FloorPlanning::InitialBtree()  //create initial B*-tree
{
    int to_x, to_y;
    int max_x = 0;
    for(int i=0; i<num_block; i++)
    {
        if(block_info[i].width < block_info[i].height)
        {
            int tmp = block_info[i].width;
            block_info[i].width = block_info[i].height;
            block_info[i].height = tmp;
        }

        if(i == 0)
        {
            root = i;
            Btree root_tmp(i);
            to_x = to_y = root;
            max_x = block_info[i].width;
            tree.push_back(root_tmp);
        }
        else
        {
            if(max_x + block_info[i].width < outline_width)
            {
                Btree left_child(i);
                tree[to_x].left_child = left_child.id;
                left_child.parent = tree[to_x].id;
                tree.push_back(left_child);

                to_x = left_child.id;
                max_x += block_info[i].width;
            }
            else
            {
                Btree right_child(i);
                tree[to_y].right_child = right_child.id;
                right_child.parent = tree[to_y].id;
                tree.push_back(right_child);

                to_y = right_child.id;
                to_x = to_y;
                max_x = block_info[i].width;
            }
        }
    }

    return;
}

void FloorPlanning::set_coordinate(int node, int* width, int* height, vector<int> &contour, bool child)
{
    if(node == root)
        block_info[node].x = 0;
    else
    {
        int parent = tree[node].parent;
        if(child == LEFT)
            block_info[node].x = block_info[parent].x + block_info[parent].width;
        else
            block_info[node].x = block_info[parent].x;
    }

    int contour_begin = block_info[node].x;
    int contour_end = block_info[node].x + block_info[node].width;
    int node_y = 0;

    while(contour.size() < contour_end + 1)
    {
        contour.push_back(0);
    }

    for(int i = contour_begin; i < contour_end; i++)
    {
        if(node_y < contour[i])
            node_y = contour[i];
    }

    block_info[node].y = node_y;

    for(int i = contour_begin; i < contour_end; i++)
        contour[i] = block_info[node].y + block_info[node].height;

    if(*width < block_info[node].x + block_info[node].width)
        *width = block_info[node].x + block_info[node].width;
    if(*height < block_info[node].y + block_info[node].height)
        *height = block_info[node].y + block_info[node].height;

    if(tree[node].left_child != -1)
        set_coordinate(tree[node].left_child, width, height, contour, LEFT);
    if(tree[node].right_child != -1)
        set_coordinate(tree[node].right_child, width, height, contour, RIGHT);

    return;
}

int FloorPlanning::HPWL()
{
    int total_wirelength = 0;

    for(int i=0; i<netlist.size(); i++)
    {
        int max_x = 0, max_y = 0;
        int min_x = INT32_MAX, min_y = INT32_MAX;
        for(int j=0; j<netlist[i].size(); j++)
        {
            bool node_type = netlist[i][j].first;
            int position = netlist[i][j].second;
            int x, y;

            if(node_type == MODULE)
            {
                x = block_info[position].x + block_info[position].width/2;
                y = block_info[position].y + block_info[position].height/2;
            }
            else if(node_type == TERMINAL)
            {
                x = terminal_info[position].first;
                y = terminal_info[position].second;
            }

            max_x = max(max_x, x);
            max_y = max(max_y, y);
            min_x = min(min_x, x);
            min_y = min(min_y, y);

        }

        total_wirelength = total_wirelength + (max_x - min_x) + (max_y - min_y);
    }
    return total_wirelength;
}

Cost_info FloorPlanning::cost()
{
    int width = 0;
    int height = 0;
    vector<int> contour;

    set_coordinate(root, &width, &height, contour, 0);

    int max_width = 0;
    int max_height = 0;
    for(int i=0; i<num_block; i++)
    {
        if(max_width < block_info[i].x + block_info[i].width)
        {
            max_width = block_info[i].x + block_info[i].width;
            max_width_node = i;
        }
        if(max_height < block_info[i].y + block_info[i].height)
        {
            max_height = block_info[i].y + block_info[i].height;
            max_height_node = i;
        }
    }

    int area = width * height;
    int total_cost = 0;
    int wirelength = 0;
    if(!in_fixed_outline)
    {
        total_cost = area;
    }
    else
    {
        wirelength = HPWL();
        total_cost = ALPHA * (double)area + (1 - ALPHA) * (double)wirelength;
    }

    Cost_info result = Cost_info(total_cost, area, wirelength, width, height);
    

    return result;
}
