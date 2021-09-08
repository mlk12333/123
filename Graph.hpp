//
//  Graph.hpp
//  index11
//
//  Created by 孟令凯 on 2021/5/9.
//
#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include "string"
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <algorithm>
#include <map>
#include <list> 
#include <unordered_map>
#include <unordered_set>
#include "HashSet.hpp"
struct point{
    int vertex;
    float value;
};

using namespace std;

class Graph{
private:
    string str;//图数据
    unsigned int n,m,edge_m;
    int max_degree;
    int *max_degree_num;
    int *degree;//每个点邻居数目
    int *pstart,*out_pstart,*in_pstart; //offset of neighbors of nodes 节点相邻点偏移量
    unsigned int *out_edges,*in_edges; //adjacent ids of edges 相邻边
    unsigned int *edges;
    unsigned int *reverse, *reverse_out; //the position of reverse edge in edges 反向边在边中的位置
    unsigned int *num_c, *num_f, *num_out_c, *num_out_f;
//    float ***core_order_c, ***core_order_f, **neighbor_order_c, **neighbor_order_f;
    point **core_order_c2, **core_order_f2, *neighbor_order_c2, *neighbor_order_f2;
    bool *reverse_out_bool;
    vector<multimap<float, int, greater<float>>> cores_mp_c;
    vector<multimap<float, int, greater<float>>> nbr_mp_c;
    vector<multimap<float, int, greater<float>>> cores_mp_f;
    vector<multimap<float, int, greater<float>>> nbr_mp_f;
    vector<int> update_degree, update_max_degree_num, update_in_num, update_out_num;
    vector<vector<int>> update_in_edges, update_out_edges;
    vector<vector<float>> nbr_order_old_c, nbr_order_old_f;
public:
    Graph(const char *_dir);
    ~Graph();
    void readGraph();
    void creatIndex();
    void readIndex();
    int readGraph_update();
    void readIndex_update();
    void query(float parameter1,float parameter2, int parameterNum);
    int insert(int u, int v);
    void remove(int u, int v);
    
    int insert_c(int u, int v);
    void remove_c(int u, int v);
    int insert_f(int u, int v);
    void remove_f(int u, int v);
    
    void readIndex_update_c();
    void readIndex_update_f();
    void release_readIndex_update_c();
    void release_readIndex_update_f();
    
    void readIndex_update_degree(vector<int> all_begin_v, vector<int> all_end_v);
    
    int insert3(int u, int v, char c_or_f);
    void remove3(int u, int v, char c_or_f);
    
    void update_write();
private:
    void getDegree();
    void getTti();
    void getFlowTti();
    int intersection_f(unsigned int *A, unsigned int *B, unsigned int a1, unsigned int a2, unsigned int b1, unsigned int b2, int double_);
    int intersection_c(unsigned int *A, unsigned int *B, unsigned int a1,unsigned int a2,unsigned int b1,unsigned int b2, int u);
    unsigned int binary_search(const unsigned int *array, int b, int e, int val) ;
    void initReverse();
    void initReverse_out();
    void getNeighborOrder();
    void getCoreOrder();
    void writeIndex();
    void getAllNei(float parameter1, float parameter2, int v, int *all_nei, int &all_nei_num);
    int BinarySearch(int *a, int value, int n);
    int BinarySearch2(int *a, int value, int b, int e);
    int BinarySearch3(vector<int> a, int value);
    unsigned int BinarySearch4(unsigned int *a,unsigned int value, unsigned int b, unsigned int e);
    
    void get_add_c_and_f(HashSet &add_c, HashSet &add_f, int u, int v, int &all_c, int &all_f);
    void update_nei1(HashSet &add_c, HashSet &add_f, int all_c, int all_f, int u, int v);//有邻居增加
    void update_nei2(HashSet &add_c, HashSet &add_f, int all_c, int all_f, int u, int v);//无邻居增加
    void update_nei_order_c(int v, int w, float old_sim, float new_sim);
    void update_nei_order_f(int v, int w, float old_sim, float new_sim);
    void update_core_c(int u, float low, float high);//flog = 0:nei_order变长
    void update_core_f(int u, float low, float high);
    
    void delete_update_nei1(HashSet &add_c, HashSet &add_f, int all_c, int all_f, int u, int v);//有邻居减少
    void delete_update_nei2(HashSet &add_c, HashSet &add_f, int all_c, int all_f, int u, int v);//无邻居减少
    
    /**
     分开计算2
     */
    
    void update_nei1_c(HashSet &add_c,int all_c, int u, int v);//有邻居增加
    void update_nei2_c(HashSet &add_c,int all_c, int u, int v);//无邻居增加
    
    void delete_update_nei1_c(HashSet &add_c,int all_c, int u, int v);//有邻居减少
    void delete_update_nei2_c(HashSet &add_c, int all_c, int u, int v);//无邻居减少
    
    void update_nei1_f(HashSet &add_f,int all_f, int u, int v);//有邻居增加
    void update_nei2_f(HashSet &add_f,int all_f, int u, int v);//无邻居增加
    
    void delete_update_nei1_f(HashSet &add_f,int all_f, int u, int v);//有邻居减少
    void delete_update_nei2_f(HashSet &add_f, int all_f, int u, int v);//无邻居减少
    
    void get_add_c(HashSet &add_c, int u, int v, int &all_c);
    void get_add_f(HashSet &add_f, int u, int v, int &all_f);
    
    /**
     分开计算3
     */
    
    void update_nei1_3(HashSet &add_c, HashSet &add_f, int all_c, int all_f, int u, int v, char c_or_f);//有邻居增加
    void update_nei2_3(HashSet &add_c, HashSet &add_f, int all_c, int all_f, int u, int v, char c_or_f);//无邻居增加
    
    void delete_update_nei1_3(HashSet &add_c, HashSet &add_f, int all_c, int all_f, int u, int v, char c_or_f);//有邻居减少
    void delete_update_nei2_3(HashSet &add_c, HashSet &add_f, int all_c, int all_f, int u, int v, char c_or_f);//无邻居减少
    
};
#endif /* Graph_hpp */



