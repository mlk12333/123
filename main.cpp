//
//  main.cpp
//  index11
//
//  Created by 孟令凯 on 2021/5/9.
//

#include <iostream>
#include "string"
#include <fstream>
#include "Graph.hpp"
#include <ctime>
using namespace std;

int main(int argc, const char * argv[]) {
    if(argc<2) return 1;
    // insert code here...
    string str = "/Users/milk/test_data/zata/wiki";
    argv[0] = &str[0];
    clock_t startTime,endTime;
    
    Graph *graph = new Graph(argv[1]);
//    Graph *graph = new Graph(str);
    srand((int)time(0));
    
    startTime = clock();//计时开始
    int n_ = graph->readGraph_update();
    endTime = clock();//计时结束
    cout << "The readGraph_update time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    
    int a;

    cout<<"choose:";

    cin>>a;
//
//    vector<int> all_begin_v, all_end_v;
//
//    for(int i = 0;i<1000;i++){
//        int begin_v = rand()%(n_-1);
//        int end_v = rand()%(n_-1);
//        all_begin_v.push_back(begin_v);
//        all_end_v.push_back(end_v);
//    }
    
    if(a == 1){
        startTime = clock();//计时开始
        graph->readIndex_update();
        endTime = clock();//计时结束
        cout << "The readIndex_update time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
        
        vector<int> all_begin_v, all_end_v;

        for(int i = 0;i<1000;i++){
            int begin_v = rand()%(n_-1);
            int end_v = rand()%(n_-1);
            all_begin_v.push_back(begin_v);
            all_end_v.push_back(end_v);
        }
        
        double all_time_insert = 0, all_time_remove = 0;
        for(int i = 0;i<1000;i++){
//            int begin_v = rand()%(n_-1);
//            int end_v = rand()%(n_-1);
//
//            cout<<i<<" "<<begin_v<<" "<<end_v<<endl;
            
            startTime = clock();//计时开始
            int judge = graph->insert(all_begin_v[i],all_end_v[i]);
            endTime = clock();//计时结束
            cout << "The insert time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
            
            if(judge){
//                i--;
                continue;
            }
            all_time_insert = all_time_insert + (double)(endTime - startTime);
            
            startTime = clock();//计时开始
            graph->remove(all_begin_v[i],all_end_v[i]);
            endTime = clock();//计时结束
            cout << "The remove time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
            all_time_remove = all_time_remove + (double)(endTime - startTime);
            
        }
        
        cout << "The all insert time is: " << all_time_insert / CLOCKS_PER_SEC << "s" << endl;
        cout << "The all remove time is: " << all_time_remove / CLOCKS_PER_SEC << "s" << endl;
        
        
    }else if(a ==2){
        startTime = clock();//计时开始
        graph->readIndex_update_c();
        endTime = clock();//计时结束
        cout << "The readIndex_update time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
        
        double all_time_insert2 = 0, all_time_remove2 = 0;
        
        
        
        vector<int> all_begin_v, all_end_v;

        for(int i = 0;i<1000;i++){
            int begin_v = rand()%(n_-1);
            int end_v = rand()%(n_-1);
            all_begin_v.push_back(begin_v);
            all_end_v.push_back(end_v);
        }
        
        for(int i = 0;i<1000;i++){
            
            startTime = clock();//计时开始
            int judge = graph->insert_c(all_begin_v[i],all_end_v[i]);
            endTime = clock();//计时结束
            cout << "The insert time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
            
            if(judge){
                continue;
            }
            
            all_time_insert2 = all_time_insert2 + (double)(endTime - startTime);
            
            startTime = clock();//计时开始
            graph->remove_c(all_begin_v[i],all_end_v[i]);
            endTime = clock();//计时结束
            cout << "The remove time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
            all_time_remove2 = all_time_remove2 + (double)(endTime - startTime);
            
        }
        
        graph->release_readIndex_update_c();
        
        startTime = clock();//计时开始
        graph->readIndex_update_f();
        endTime = clock();//计时结束
        cout << "The readIndex_update time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
//
        for(int i = 0;i<1000;i++){
            
            startTime = clock();//计时开始
            int judge = graph->insert_f(all_begin_v[i],all_end_v[i]);
            endTime = clock();//计时结束
            cout << "The insert time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
            
            if(judge){
                continue;
            }
            
            all_time_insert2 = all_time_insert2 + (double)(endTime - startTime);
            
            startTime = clock();//计时开始
            graph->remove_f(all_begin_v[i],all_end_v[i]);
            endTime = clock();//计时结束
            cout << "The remove time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
            all_time_remove2 = all_time_remove2 + (double)(endTime - startTime);
        }
        
        graph->release_readIndex_update_f();
        
        cout << "The all insert time is: " << all_time_insert2 / CLOCKS_PER_SEC << "s" << endl;
        cout << "The all remove time is: " << all_time_remove2 / CLOCKS_PER_SEC << "s" << endl;
    }
    else if(a == 3){
        
        vector<int> all_begin_v, all_end_v;
        for(int i = 0;i<1000;i++){
            int begin_v = rand()%(n_-1);
            int end_v = rand()%(n_-1);
            all_begin_v.push_back(begin_v);
            all_end_v.push_back(end_v);
        }
        
        graph->readIndex_update_degree(all_begin_v, all_end_v);
    }
    
    return 0;
}




