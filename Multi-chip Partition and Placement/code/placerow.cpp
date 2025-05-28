#include "placement.h"

pair<ROW_INFO, vector<CLUSTER> > Placement::PlaceRow_trial(int r, int current_cell)
{
    pair<ROW_INFO, vector<CLUSTER> > current_row = row[r];
    int last = current_row.second.size() - 1;
    CLUSTER* last_cluster;
    
    if(last >= 0)
        last_cluster = &current_row.second[last];

    

    if(current_row.second.size() == 0 || (last_cluster->x_c + last_cluster->w_c < cells[current_cell].x && current_row.first.x_end - (last_cluster->x_c + last_cluster->w_c) > cells[current_cell].width))
    {
        CLUSTER new_cluster;
        new_cluster.q_c = 0;
        new_cluster.w_c = 0;
        new_cluster.e_c = 0;
        if(cells[current_cell].x < current_row.first.x_start)
            new_cluster.x_c = current_row.first.x_start;
        else if(cells[current_cell].x + cells[current_cell].width > current_row.first.x_end)
            new_cluster.x_c = current_row.first.x_end - cells[current_cell].width;
        else
            new_cluster.x_c = cells[current_cell].x;

        current_row.second.push_back(new_cluster);
        last_cluster = &current_row.second[last+1];
        AddCell(last_cluster, current_cell, current_row.first.y);
    }
    else
    {
        AddCell(last_cluster, current_cell, current_row.first.y);
        Collapse(last_cluster, current_row.first.x_start, current_row.first.x_end, last, &current_row);
    }

    return current_row;
}

void Placement::AddCell(CLUSTER *c, int i, int y_pos)
{
    c->id.push_back(i);
    c->e_c += (abs(cells[i].y - y_pos) / row_height + 1) * (abs(cells[i].y - y_pos) / row_height + 1);//(cells[i].width * cells[i].height); //abs(cells[i].y - y_pos);
    c->q_c += (cells[i].width * cells[i].height * (cells[i].x - c->w_c));
    c->w_c += cells[i].width;
}

void Placement::AddCluster(CLUSTER *predecessor_c, CLUSTER *c)
{
    for(int i=0; i<c->id.size(); i++)
        predecessor_c->id.push_back(c->id[i]);

    predecessor_c->e_c += c->e_c;
    predecessor_c->q_c = predecessor_c->q_c + c->q_c - c->e_c * predecessor_c->w_c;
    predecessor_c->w_c += c->w_c;
}

void Placement::Collapse(CLUSTER *c, int x_min, int x_max, int id_cluster, pair<ROW_INFO, vector<CLUSTER> > *r)
{
    c->x_c = c->q_c / c->e_c;
    
    if(c->x_c < x_min)
        c->x_c = x_min;
    if(c->x_c > x_max - c->w_c)
        c->x_c = x_max - c->w_c;
    
    if(id_cluster > 0)
    {
        CLUSTER *prdecessor_c = &(r->second[id_cluster - 1]);

        if(prdecessor_c->x_c + prdecessor_c->w_c > c->x_c)
        {
            AddCluster(prdecessor_c, c);
            c = NULL;
            r->second.pop_back();
            Collapse(prdecessor_c, x_min, x_max, id_cluster-1, r);
        }
    }
}