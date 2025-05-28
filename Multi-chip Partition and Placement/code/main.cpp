#include <iostream>
#include "parameter.h"
#include "placement.h"

using namespace std;

int main(int argc, char *argv[])
{
    t1 = clock();
    srand(SEED);

    Placement *PM = new Placement();

    cout << "hello" << endl;

    if(!PM->ReadFile(argv[1]))
    {
        cout << "File can not be OPENED!!!" << endl;
        return 0;
    }

    cout << "File is read successfully" << endl;

    PM->legalization();
    PM->CreateDrawingFile(argv[argc-1]);

    clock_t t2 = clock();

    cout << "Complete execution." << endl;
    cout << "\nSpend " << (t2-t1)/((double)(CLOCKS_PER_SEC)) << " s" << endl;

    return 0;
}