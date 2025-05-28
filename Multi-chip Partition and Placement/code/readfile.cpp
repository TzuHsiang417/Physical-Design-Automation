#include <fstream>
#include "placement.h"

bool Placement::ReadFile(char *argv)
{
    ifstream ifile(argv, ios::in);
    string title1, title2, title3;

    if(!ifile)
    {
        ifile.close();
        return 0;
    }
    else
    {
        ifile >> title1 >> chip_width >> chip_height;
        ifile >> title2 >> row_height >> row_number;
        ifile >> title3 >> num_terminal;

        string name;
        int width, height;
        int x_coordinate, y_coordinate;

        for (int i=0; i<num_terminal; i++)
        {
            ifile >> name >> x_coordinate >> y_coordinate >> width >> height;
            terminals.push_back(TERMINAL(x_coordinate, y_coordinate, width, height));
        }
        
        ifile >> title3 >> num_cell;

        for (int i=0; i<num_cell; i++)
        {
            ifile >> name >> x_coordinate >> y_coordinate >> width >> height;
            cells.push_back(CELL(x_coordinate, y_coordinate, width, height));
        }
        
        ifile.close();
    }

    return 1;
}

void Placement::CreateDrawingFile(char *argv)    //create output file
{
    ofstream ofile(argv, ios::out);

    if(ofile.is_open())
    {
        for(int i=0; i<cells.size(); i++)
        {
            ofile << "C" << i << " ";
            ofile << cells[i].x << " " << cells[i].y << " ";
            ofile << cells[i].layer << endl;
        }
        
    }
    ofile.close();

    return;
}