#include "partition.h"

class CLUSTER{
    int w_c;
    int x_c, q_c, e_c;
    vector<int> id;
    friend class Placement;
};

class ROW_INFO{
    int x_start;
    int x_end;
    int y;
    friend class Placement;

    public:
        ROW_INFO() {}
        ROW_INFO(int a, int b, int c): x_start(a), x_end(b), y(c){}
};

class Placement{
    int chip_width, chip_height;
    int row_height, row_number;
    int num_terminal, num_cell;
    vector<CELL> cells;
    vector<TERMINAL> terminals;
    vector<pair<ROW_INFO, vector<CLUSTER> > > row;

    public:
        Placement() {}
        bool ReadFile(char *argv);
        void legalization();
        void Abacus(vector<int> &cell_in_layer);
        void Bubble_sort(vector<int> &cell_in_layer);
        void Setting_Row();
        pair<ROW_INFO, vector<CLUSTER> > PlaceRow_trial(int r, int current_cell);
        void PlaceRow(int r, int current_cell);
        void AddCell(CLUSTER *c, int i, int y_pos);
        void AddCluster(CLUSTER *predecessor_c, CLUSTER *c);
        void Collapse(CLUSTER *c, int x_min, int x_max, int id_cluster, pair<ROW_INFO, vector<CLUSTER> > *r);
        int Determine_cost(pair<ROW_INFO, vector<CLUSTER> > *origin_r, pair<ROW_INFO, vector<CLUSTER> > *new_r);
        void CreateDrawingFile(char *argv);
};