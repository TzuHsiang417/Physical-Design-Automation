#include "floorplan.h"

void FloorPlanning::Op1()
{
    int x = rand() % num_block;
    int tmp = block_info[x].width;
    block_info[x].width = block_info[x].height;
    block_info[x].height = tmp;

    return;
}

void FloorPlanning::Op2()
{
    int max_width = block_info[max_width_node].x + block_info[max_width_node].width;
    int max_height = block_info[max_height_node].y + block_info[max_height_node].height;
    int x;
    if(max_width > outline_width || max_height > outline_height)
    {
        int choose = rand() % 2;
        if(choose == 0)
        {
            if(max_width > outline_width)
                x = max_width_node;
            else
                x = max_height_node;
        }
        else
        {
            if(max_height > outline_height)
                x = max_height_node;
            else
                x = max_width_node;
        }
    }
    else
    {
        x = rand() % num_block;
    }

    int y = rand() % num_block;
    while(y == x)
        y = rand() % num_block;

    Btree node1 = tree[x];
    Btree node2 = tree[y];

    if(tree[x].left_child == -1 && tree[x].right_child == -1)
    {
        int parent = tree[x].parent;
        if(tree[parent].left_child == x)
            tree[parent].left_child = -1;
        else if(tree[parent].right_child == x)
            tree[parent].right_child = -1;
    }
    else if(tree[x].left_child != -1 && tree[x].right_child != -1)
    {
        while(tree[x].left_child != -1 || tree[x].right_child != -1)
        {
            int swapped_node;
            bool p = rand() % 2;
            if(p == 1)
            {
                if(tree[x].left_child == -1)
                    swapped_node = tree[x].right_child;
                else
                    swapped_node = tree[x].left_child;
            }
            else
            {
                if(tree[x].right_child == -1)
                    swapped_node = tree[x].left_child;
                else
                    swapped_node = tree[x].right_child;
            }

            Swap(x, swapped_node);
        }

        int parent = tree[x].parent;
        if(tree[parent].left_child == x)
            tree[parent].left_child = -1;
        else if(tree[parent].right_child == x)
            tree[parent].right_child = -1;
    }
    else
    {
        int child;
        if(tree[x].left_child != -1)
            child = tree[x].left_child;
        else
            child = tree[x].right_child;

        if(tree[x].parent != -1)
        {
            int parent = tree[x].parent;
            if(tree[parent].left_child == x)
                tree[parent].left_child = child;
            else
                tree[parent].right_child = child;
        }

        tree[child].parent = tree[x].parent;

        if(x == root)
            root = child;
    }

    tree[x].parent = y;

    int state = rand() % 4;
    
    int child;
    switch (state)
    {
    case 0:
        child = tree[y].left_child;
        tree[x].left_child = child;
        tree[x].right_child = -1;
        tree[y].left_child = x;
        break;
    case 1:
        child = tree[y].left_child;
        tree[x].left_child = -1;
        tree[x].right_child = child;
        tree[y].left_child = x;
        break;
    case 2:
        child = tree[y].right_child;
        tree[x].left_child = child;
        tree[x].right_child = -1;
        tree[y].right_child = x;
        break;
    case 3:
        child = tree[y].right_child;
        tree[x].left_child = -1;
        tree[x].right_child = child;
        tree[y].right_child = x;
        break;
    }

    if(child != -1)
        tree[child].parent = x;

    int p = rand() % 2;
    if(p == 1)
    {
        int tmp = block_info[x].width;
        block_info[x].width = block_info[x].height;
        block_info[x].height = tmp;
    }

    return;
}

void FloorPlanning::Op3()
{
    int max_width = block_info[max_width_node].x + block_info[max_width_node].width;
    int max_height = block_info[max_height_node].y + block_info[max_height_node].height;
    int x;
    if(max_width > outline_width || max_height > outline_height)
    {
        int choose = rand() % 2;
        if(choose == 0)
        {
            if(max_width > outline_width)
                x = max_width_node;
            else
                x = max_height_node;
        }
        else
        {
            if(max_height > outline_height)
                x = max_height_node;
            else
                x = max_width_node;
        }
    }
    else
    {
        x = rand() % num_block;
    }

    int y = rand() % num_block;
    while(y == x)
        y = rand() % num_block;

    Swap(x, y);

    int p = rand() % 2;
    if(p == 1)
    {
        int tmp = block_info[x].width;
        block_info[x].width = block_info[x].height;
        block_info[x].height = tmp;
    }
    p = rand() % 2;
    if(p == 1)
    {
        int tmp = block_info[y].width;
        block_info[y].width = block_info[y].height;
        block_info[y].height = tmp;
    }

    return;
}

void FloorPlanning::Op4()
{
    int x = rand() % num_block;
    while (tree[x].left_child == -1)
        x = rand() % num_block;

    Swap(x, tree[x].left_child);

    int p = rand() % 2;
    if(p == 1)
    {
        int tmp = block_info[x].width;
        block_info[x].width = block_info[x].height;
        block_info[x].height = tmp;
    }
    p = rand() % 2;
    if(p == 1)
    {
        int tmp = block_info[tree[x].parent].width;
        block_info[tree[x].parent].width = block_info[tree[x].parent].height;
        block_info[tree[x].parent].height = tmp;
    }
}

void FloorPlanning::Op5()
{
    int x = rand() % num_block;
    while (tree[x].right_child == -1)
        x = rand() % num_block;

    Swap(x, tree[x].right_child);

    int p = rand() % 2;
    if(p == 1)
    {
        int tmp = block_info[x].width;
        block_info[x].width = block_info[x].height;
        block_info[x].height = tmp;
    }
    p = rand() % 2;
    if(p == 1)
    {
        int tmp = block_info[tree[x].parent].width;
        block_info[tree[x].parent].width = block_info[tree[x].parent].height;
        block_info[tree[x].parent].height = tmp;
    }
}

void FloorPlanning::Swap(int node1, int node2)
{
    if(root == node1)
        root = node2;
    else if(root == node2)
        root = node1;

    int parent1_tmp = tree[node1].parent;
    int left1_tmp = tree[node1].left_child;
    int right1_tmp = tree[node1].right_child;

    int parent2_tmp = tree[node2].parent;
    int left2_tmp = tree[node2].left_child;
    int right2_tmp = tree[node2].right_child;

    if(parent1_tmp != -1)
    {
        if(tree[parent1_tmp].left_child == node1)
            tree[parent1_tmp].left_child = node2;
        else
            tree[parent1_tmp].right_child = node2;
    }

    if(left1_tmp != -1)
        tree[left1_tmp].parent = node2;
    if(right1_tmp != -1)
        tree[right1_tmp].parent = node2;

    if(parent2_tmp != -1)
    {
        if(tree[parent2_tmp].left_child == node2)
            tree[parent2_tmp].left_child = node1;
        else
            tree[parent2_tmp].right_child = node1;
    }

    if(left2_tmp != -1)
        tree[left2_tmp].parent = node1;
    if(right2_tmp != -1)
        tree[right2_tmp].parent = node1;

    tree[node1].parent = parent2_tmp;
    tree[node1].left_child = left2_tmp;
    tree[node1].right_child = right2_tmp;

    tree[node2].parent = parent1_tmp;
    tree[node2].left_child = left1_tmp;
    tree[node2].right_child = right1_tmp;

    if(tree[node1].parent == node1)
        tree[node1].parent = node2;
    else if(tree[node1].left_child == node1)
        tree[node1].left_child = node2;
    else if(tree[node1].right_child == node1)
        tree[node1].right_child = node2;

    if(tree[node2].parent == node2)
        tree[node2].parent = node1;
    else if(tree[node2].left_child == node2)
        tree[node2].left_child = node1;
    else if(tree[node2].right_child == node2)
        tree[node2].right_child = node1;

    return;
}