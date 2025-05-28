#include <iostream>
#include "placement.h"

void Placement::legalization()
{
    PT_time = 300 - ((double)num_cell / 45000) * ((double)num_cell / 45000) * 20 - 20;
    cout << "Partioning" << endl;

    Partition PT(num_cell, cells);
    cout << "Spend " << (clock()-t1)/((double)(CLOCKS_PER_SEC)) << " s" << endl;
    cout << endl;

    cout << "Doing FM Algorithm" << endl;
    cells = PT.FM_Algorithm();
    cout << "Spend " << (clock()-t1)/((double)(CLOCKS_PER_SEC)) << " s" << endl;
    cout << endl;

    cout << "Complete Partioning" << endl;
    cout << "Spend " << (clock()-t1)/((double)(CLOCKS_PER_SEC)) << " s" << endl;
    cout << endl;

    vector<int> cells_in_layer0;
    vector<int> cells_in_layer1;

    for(int i=0; i<num_cell; i++)
    {
        if(cells[i].layer == 0)
            cells_in_layer0.push_back(i);
        else
            cells_in_layer1.push_back(i);
    }

    sort(terminals.begin(), terminals.end(), [](TERMINAL a, TERMINAL b){
        return a.x < b.x;
    });

    cout << "Legalization layer 0" << endl;
    Abacus(cells_in_layer0);
    cout << "Complete layer 0" << endl;
    cout << "Spend " << (clock()-t1)/((double)(CLOCKS_PER_SEC)) << " s" << endl;
    cout << endl;

    cout << "Legalization layer 1" << endl;
    Abacus(cells_in_layer1);
    cout << "Complete layer 1" << endl;
    cout << "Spend " << (clock()-t1)/((double)(CLOCKS_PER_SEC)) << " s" << endl;
    cout << endl;

    return;
}