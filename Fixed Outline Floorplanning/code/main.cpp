#include "parameter.h"
#include "floorplan.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout.setf(ios::fixed); 
    t1 = clock();

    if(argc < 5)
    {
        cout << "The execution procedure is ./Lab2 [α value] [input.block name] [input.net name] [output name]" << endl;
        cout << "Please enter the correct information." << endl;
        return 0;
    }

    FloorPlanning *FP = new FloorPlanning(atof(argv[1]));
    if(!FP->ReadFile(argv[2], argv[3]))
    {
        cout << "File can not be OPENED!!!" << endl;
        return 0;
    }
    

    FP->InitialBtree();

    srand(SEED);
    FP->Simulated_Annealing();
    FP->CreateOutputFile(argv[4]);

    if(argc >= 6)
        FP->CreateDrawingFile(argv[5]);

    t2 = clock();
    cout << "\nSpend " << (t2-t1)/((double)(CLOCKS_PER_SEC)) << " s" << endl;

    return 0;
}