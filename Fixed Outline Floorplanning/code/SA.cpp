#include "floorplan.h"

void FloorPlanning::Simulated_Annealing()   //SA Algorithm
{
    in_fixed_outline = 0; 

    vector<Block> best_info = block_info;      //儲存最好的tree
    vector<Block> old_info = block_info;   //儲存改變後的tree
    int best_root = root;
    int old_root = root;
    vector<Btree> best_tree = tree;
    vector<Btree> old_tree = tree;
    Cost_info best_cost = cost();   //最好的cost
    Cost_info old_cost = cost();     //移動前的cost
    double T0 = fabs(best_cost.cost * num_block / log(0.95));             //initial temprature
    int Op = 0;                      //M：M1、M2、M3
    int MT = 0;                     //移動次數
    int uphill = 0;                 //uphill
    int reject = 0;                 //reject
    int N = K*num_block;           //N=K*n
    double T = T0;    
    int penalty = 0;              

    time_t t1, t2;
    t1 = time(NULL);

    cout << "tree: " << tree.size() << " block: " << block_info.size() << endl;
    cout << "initial cost: " << old_cost.cost << " " << old_cost.width << " " << old_cost.height << endl;
    cout << "T is " << T << endl;
    
    
    do{
        reject = 0;             //初始化
        MT = 0;
        uphill = 0;

        do{
            Op = rand()%5 + 1;   //任意做Op1、Op2或Op3

            switch(Op)
            {
            case 1:     //rotate
                Op1();
                break;
            case 2:     //move           
                Op2();
                break;
            case 3:     //swap
                Op3();
                break;
            case 4:     //swap with left child
                Op4();
                break;
            case 5:     //swap with right child
                Op5();
                break;
            }

            MT++;               //移動次數++

            Cost_info new_cost = cost();             //移動後的cost

            
            if(new_cost.width <= outline_width && new_cost.height <= outline_height && !in_fixed_outline)
            {
                in_fixed_outline = 1;
                int root_tmp = root;
                vector<Btree> tree_tmp = tree;

                root = old_root;
                tree = old_tree;
                old_cost = cost();
                old_info = block_info;

                root = best_root;
                tree = best_tree;
                best_cost = cost();
                best_info = block_info;

                root = root_tmp;
                tree = tree_tmp;
                new_cost = cost();
            }

            int delta_ratio;
            if(in_fixed_outline)
                delta_ratio = 1;
            else
                delta_ratio = ((new_cost.width - outline_width)*(new_cost.width - outline_width) + (new_cost.height - outline_height)*(new_cost.height - outline_height)) - ((old_cost.width - outline_width)*(old_cost.width - outline_width) + (old_cost.height - outline_height)*(old_cost.height - outline_height));
                
            if((float)outline_height/(float)outline_width > 1)
            {
                if((float)new_cost.height/(float)new_cost.width < 1)
                    delta_ratio = abs(delta_ratio);
            }
            else if((float)outline_height/(float)outline_width < 1)
            {
                if((float)new_cost.height/(float)new_cost.width >= 1)
                    delta_ratio = abs(delta_ratio);
            }

    
            double delta_cost = (double)new_cost.cost - (double)old_cost.cost;     //cost的變化
            if(!in_fixed_outline)
                delta_cost = delta_ratio;

            double probability = (double)rand()/RAND_MAX;           //隨機在0到1之間取值

            if((delta_cost<=0 && in_fixed_outline) || delta_ratio<=0 || probability<exp(-1*delta_cost/T))   //如果cost變化為負或是probability小於exp(-delta_cost/T)
            {
                if(delta_cost > 0)          //如果cost變化量大於0，uphill++
                    uphill++;
                old_info = block_info;              //update NPE
                old_cost = new_cost;   
                old_root = root;
                old_tree = tree;

                int update_ratio = ((new_cost.width - outline_width)*(new_cost.width - outline_width) + (new_cost.height - outline_height)*(new_cost.height - outline_height)) - ((best_cost.width - outline_width)*(best_cost.width - outline_width) + (best_cost.height - outline_height)*(best_cost.height - outline_height));

                if((update_ratio<=0 /*|| new_cost.cost < best_cost.cost*/) && !in_fixed_outline)    //如果新的花費比best花費更小
                {
                    best_info = block_info;         //update best
                    best_cost = new_cost; //update best_cost
                    best_root = root;
                    best_tree = tree;
                    penalty = 0;

                    //cout << "best cost: " << best_cost.cost << " " << best_cost.width << " " << best_cost.height << " " << best_cost.wirelength << endl;
                }
                else if(in_fixed_outline && new_cost.cost < best_cost.cost && new_cost.width <= outline_width && new_cost.height <= outline_height)
                {
                    best_info = block_info;         //update best
                    best_cost = new_cost; //update best_cost
                    best_root = root;
                    best_tree = tree;
                    penalty = 0;

                    //cout << "best cost: " << best_cost.cost << " " << best_cost.width << " " << best_cost.height << " " << best_cost.wirelength << endl;
                }
            }
            else
            {
                reject++;
                penalty++;
            }


            if(penalty < num_block * 1.5)
            {
                penalty = 0;
                old_info = block_info = best_info;
                old_cost = best_cost;
                old_root = root = best_root;
                old_tree = tree = best_tree;
            }
            else
            {
                block_info = old_info;
                root = old_root;
                tree = old_tree;
            }

            t2 = time(NULL);

            if((t2-t1)>=TIME_LIMIT)         //檢查是否超時
                break;
        } while(uphill<=N && MT<=2*N);
        
        /*if(T>30)        //若T小於30，則讓其快速冷卻
            T = RATIO*T;
        else
            T = FROZEN_RATIO*T;*/
        if(in_fixed_outline)
            T = RATIO*T;

        t2 = time(NULL);
    } while((reject/MT)<=0.95 && T>=EPSILON && (t2-t1)<TIME_LIMIT);
    block_info = best_info;
    root = best_root;
    tree = best_tree;
    result_cost = cost();

    cout << "Finish SA algorithm" << endl;
    cout << "temp: " << T << endl;
    cout << "best cost: " << best_cost.cost << endl;
    cout << "width: " << best_cost.width << " height: " << best_cost.height << endl;

    return;
}