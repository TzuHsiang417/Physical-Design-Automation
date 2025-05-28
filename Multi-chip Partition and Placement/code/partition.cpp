#include "partition.h"
#include "parameter.h"

bool Partition::intersect(CELL c1, CELL c2)
{
    return !(c1.x + c1.width < c2.x || c1.x > c2.x + c2.width ||
             c1.y + c1.height < c2.y || c1.y > c2.y + c2.height);
}

int Partition::intersect_area(CELL c1, CELL c2)
{
    int min_x, min_y, max_x, max_y;

    min_x = max(c1.x, c2.x);
    min_y = max(c1.y, c2.y);
    max_x = min(c1.x + c1.width, c2.x + c2.width);
    max_y = min(c1.y + c1.height, c2.y + c2.height);

    return (max_x - min_x) * (max_y - min_y);
}

Partition::Partition(int a, vector<CELL> &cells_PM)
{
    num_cell = a;

    vector<vector<bool> > tmp(num_cell, vector<bool>(num_cell, 0));
    graph = tmp;

    edge.resize(num_cell);

    cells = cells_PM;
    for(int i=0; i<num_cell; i++)
    {
        if((clock()-t1)/((double)(CLOCKS_PER_SEC)) > PT_time)
            break;
        for(int j=i+1; j<num_cell; j++)
        {
            // if((clock()-t1)/((double)(CLOCKS_PER_SEC)) > PT_time)
            //     break;
            if(intersect(cells[i], cells[j]))
            {
                int area = intersect_area(cells[i], cells[j]);

                graph[i][j] = 1;
                graph[j][i] = 1;
                edge[i].push_back(INTERSECT_CELL(j, area));
                edge[j].push_back(INTERSECT_CELL(i, area));
            }
        }
    }
}

vector<CELL> Partition::FM_Algorithm()
{
    gain.resize(num_cell, 0);
    current_layer.resize(num_cell);
    locked.resize(num_cell, 0);

    vector<bool> min_layer;

    int layer_diff = INT32_MAX;
    int layer0_total_width = 0;
    int layer1_total_width = 0;

    for(int i=0; i<num_cell; i++)
    {
        bool split = rand() % 2;
        cells[i].layer = split;
        current_layer[i] = split;

        if(split == 0)
            layer0_total_width += cells[i].width;
        else
            layer1_total_width += cells[i].width;
    }

    for(int i=0; i<num_cell; i++)
    {
        if((clock()-t1)/((double)(CLOCKS_PER_SEC)) > PT_time)
            break;
        for(int j=i+1; j<num_cell; j++)
        {
            // if((clock()-t1)/((double)(CLOCKS_PER_SEC)) > PT_time)
            //     break;

            if(graph[i][j] == 0)
                continue;

            int area_tmp;
            for(int k=0; k<edge[i].size(); k++)
            {
                if(edge[i][k].id == j)
                {
                    area_tmp = edge[i][k].area;
                    break;
                }
            }

            if(cells[i].layer == cells[j].layer)
            {
                gain[i] += area_tmp;
                gain[j] += area_tmp;
                area[cells[i].layer] += area_tmp;
            }
            else
            {
                gain[i] -= area_tmp;
                gain[j] -= area_tmp;
            }
        }
    }

    min_area = area[0] + area[1];
    min_layer = current_layer;
    
    for(int i=0; i<num_cell; i++)
    {
        bucket[gain[i]].push_back(i);
    }

    map<int, vector<int> >::iterator max_gain_index = bucket.end();
    max_gain_index--;

    while(!bucket.empty() && (clock()-t1)/((double)(CLOCKS_PER_SEC)) < PT_time)
    {
        int s_tmp = 0;

        int cell_to_move = max_gain_index->second.back();
        max_gain_index->second.erase(max_gain_index->second.end()-1);
        locked[cell_to_move] = 1;

        if(max_gain_index->second.empty())
            bucket.erase(max_gain_index);

        bool old_layer = current_layer[cell_to_move];
        current_layer[cell_to_move] = !current_layer[cell_to_move];

        if(old_layer == 0)
        {
            layer0_total_width -= cells[cell_to_move].width;
            layer1_total_width += cells[cell_to_move].width;
        }
        else
        {
            layer0_total_width += cells[cell_to_move].width;
            layer1_total_width -= cells[cell_to_move].width;
        }

        update_gain(cell_to_move, old_layer);

        if(area[0] + area[1] < min_area)
        {
            min_area = area[0] + area[1];
            min_layer = current_layer;
            layer_diff = abs(layer0_total_width - layer1_total_width);
        }
        else if(area[0] + area[1] == min_area)
        {
            if(abs(layer0_total_width - layer1_total_width) < layer_diff)
            {
                min_area = area[0] + area[1];
                min_layer = current_layer;
                layer_diff = abs(layer0_total_width - layer1_total_width);
            }
        }

        if(!bucket.empty())
        {
            max_gain_index = bucket.end();
            max_gain_index--;
        }
    }

    current_layer = min_layer;

    for(int i=0; i<num_cell; i++)
        cells[i].layer = current_layer[i];
    return cells;
}

void Partition::update_gain(int cell_to_move, bool old_layer)
{
    for(int i=0; i<num_cell; i++)
    {
        if(graph[cell_to_move][i] == 0)
            continue;
        
        int area_tmp;
        for(int k=0; k<edge[cell_to_move].size(); k++)
        {
            if(edge[cell_to_move][k].id == i)
            {
                area_tmp = edge[cell_to_move][k].area;
                break;
            }
        }

        int prev_gain = gain[i];
        if(old_layer == current_layer[i])
        {
            area[current_layer[i]] -= area_tmp;
            gain[i] = gain[i] - area_tmp - area_tmp;
        }
        else
        {
            area[current_layer[i]] += area_tmp;
            gain[i] = gain[i] + area_tmp + area_tmp;
        }

        if(locked[i] == 0)
            update_bucket(i, prev_gain);
    }
    //system("pause");
    return;
}

void Partition::update_bucket(int curr_cell, int prev_gain)
{
    bucket[prev_gain].erase(remove(bucket[prev_gain].begin(),bucket[prev_gain].end(),curr_cell),bucket[prev_gain].end());

    if(bucket[prev_gain].empty())
	{
		bucket.erase(prev_gain);
	}
	bucket[gain[curr_cell]].push_back(curr_cell);

    return;
}