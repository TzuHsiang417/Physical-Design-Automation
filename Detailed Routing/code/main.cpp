#include <iostream>
#include <string>
#include "router.h"

using namespace std;

int main(int argc, char *argv[])
{
    clock_t t1 = clock();
    srand(SEED);
    Router *route = new Router();
    if(!route->ReadFile(argv[1]))
    {
        cout << "File can not be open !!!" << endl;
    }

    route->Left_edge();
    route->CreateOutputFile(argv[argc-1]);

    // route->debug_out();

    clock_t t2 = clock();

    cout << "Finished Channel Routing" << endl;
    cout << "Spend " << (float)(t2 - t1)/CLOCKS_PER_SEC << "sec" << endl;

    return 0;
}