#include "placement.h"

void Placement::Abacus(vector<int> &cell_in_layer)
{
    Setting_Row();
    Bubble_sort(cell_in_layer);

    int c_best, r_best;
    pair<ROW_INFO, vector<CLUSTER> > best_trial;

    for(int i=0; i<cell_in_layer.size(); i++)
    {
        c_best = INT32_MAX;
        int current_cell = cell_in_layer[i];
        int limit_bottom = cells[current_cell].y - 2 * row_height;
        int limit_top = cells[current_cell].y + 3 * row_height;

        bool placed = 0;
        for(int r=0; r<row.size(); r++)
        {
            if(row[r].first.y < limit_bottom || row[r].first.y >= limit_top)
                continue;
            
            int reduce_distance = row[r].first.x_end - row[r].first.x_start;
            for(int d=0; d<row[r].second.size(); d++)
                reduce_distance -= row[r].second[d].w_c;

            
            if(cells[current_cell].width > reduce_distance)
                continue;

            pair<ROW_INFO, vector<CLUSTER> > trail_row;
            trail_row = PlaceRow_trial(r, current_cell);

            int cost = Determine_cost(&(row[r]), &trail_row);

            if(cost < c_best)
            {
                c_best = cost;
                r_best = r;
                best_trial = trail_row;
            }

            placed = 1;
        }

        if(placed == 0)
        {
            for(int r=0; r<row.size(); r++)
            {
                int reduce_distance = row[r].first.x_end - row[r].first.x_start;
                for(int d=0; d<row[r].second.size(); d++)
                    reduce_distance -= row[r].second[d].w_c;

                
                if(cells[current_cell].width > reduce_distance)
                    continue;

                pair<ROW_INFO, vector<CLUSTER> > trail_row;
                trail_row = PlaceRow_trial(r, current_cell);

                int cost = Determine_cost(&(row[r]), &trail_row);

                if(cost < c_best)
                {
                    c_best = cost;
                    r_best = r;
                    best_trial = trail_row;
                }

                placed = 1;
            }
        }

        row[r_best] = best_trial;
    }

    for(int i=0; i<row.size(); i++)
    {
        for(int j=0; j<row[i].second.size(); j++)   //cluster
        {   
            int x_pos = row[i].second[j].x_c;
            int y_pos = row[i].first.y;
            for(int k=0; k<row[i].second[j].id.size(); k++) //cell
            {
                int current_cell = row[i].second[j].id[k];
                cells[current_cell].x = x_pos;
                cells[current_cell].y = y_pos;

                x_pos += cells[current_cell].width;
            }
        }
    }
}

void Placement::Bubble_sort(vector<int> &cell_in_layer)
{
    for(int i=0; i<cell_in_layer.size()-1; i++)
    {
        for(int j=0; j<cell_in_layer.size()-i-1; j++)
        {
            if(cells[cell_in_layer[j]].x > cells[cell_in_layer[j+1]].x)
            {
                int tmp = cell_in_layer[j];
                cell_in_layer[j] = cell_in_layer[j+1];
                cell_in_layer[j+1] = tmp;
            }
        }
    }
}

void Placement::Setting_Row()
{
    row.clear();
    vector<vector<pair<int, int> > > row_tmp(row_number);

    for(int i=0 ; i<num_terminal; i++)
    {   
        int bottom = terminals[i].y / row_height;
        int top;
        if((terminals[i].y + terminals[i].height) % row_height == 0)
            top = (terminals[i].y + terminals[i].height) / row_height;
        else
            top = (terminals[i].y + terminals[i].height) / row_height + 1;
        for(int j = bottom; j < top; j++)
            row_tmp[j].push_back(make_pair(terminals[i].x, terminals[i].x + terminals[i].width));
    }

    for(int i=0; i<row_number; i++)
    {
        int start = 0;
        int end = 0;
        int height = i * row_height;
        for(int j=0; j<row_tmp[i].size(); j++)
        {
            end = row_tmp[i][j].first;
            if(start == end)
            {
                start = row_tmp[i][j].second;
                continue;
            }

            if(start > end)
            {
                if(row_tmp[i][j].second > start)
                    start = row_tmp[i][j].second;
                continue;
            }
            vector<CLUSTER> c;
            row.push_back(make_pair(ROW_INFO(start, end, height), c));

            start = row_tmp[i][j].second;
        }
        end = chip_width;
        if(start != end)
        {
            vector<CLUSTER> c;
            row.push_back(make_pair(ROW_INFO(start, end, height), c));
        }
    }
}

int Placement::Determine_cost(pair<ROW_INFO, vector<CLUSTER> > *origin_r, pair<ROW_INFO, vector<CLUSTER> > *new_r)
{
    int origin_cost = 0;
    int new_cost = 0;
    for(int i=0; i<origin_r->second.size(); i++)
    {
        int x_pos = origin_r->second[i].x_c;
        for(int j=0; j<origin_r->second[i].id.size(); j++)
        {
            int current_cell = origin_r->second[i].id[j];
            origin_cost = origin_cost + abs(x_pos - cells[current_cell].x) + abs(origin_r->first.y - cells[current_cell].y);
            x_pos += cells[current_cell].width;
        }
    }

    for(int i=0; i<new_r->second.size(); i++)
    {
        int x_pos = new_r->second[i].x_c;
        for(int j=0; j<new_r->second[i].id.size(); j++)
        {
            int current_cell = new_r->second[i].id[j];
            new_cost = new_cost + abs(x_pos - cells[current_cell].x) + abs(new_r->first.y - cells[current_cell].y);
            x_pos += cells[current_cell].width;
        }
    }

    return (new_cost - origin_cost);
}