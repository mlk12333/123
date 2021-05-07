//
//  Graph.cpp
//  index10(one_pointer2)
//
//  Created by 孟令凯 on 2021/4/29.
//

#include "Graph.hpp"
#include <algorithm>
#include "math.h"

Graph::Graph(const char *_dir){
    this->str = string(_dir);
    n = m = edge_m = max_degree = 0;
    degree = NULL;
    pstart = NULL;
    out_pstart = NULL;
    in_pstart = NULL;
    edges= NULL;
    out_edges= NULL;
    in_edges= NULL;
    reverse= NULL;
    reverse_out= NULL;
    num_c= NULL;
    num_f= NULL;
    num_out_c= NULL;
    num_out_f= NULL;
//    core_order_c= NULL;
//    core_order_f= NULL;
//    neighbor_order_c= NULL;
//    neighbor_order_f= NULL;
    core_order_c2= NULL;
    core_order_f2= NULL;
    neighbor_order_c2= NULL;
    neighbor_order_f2= NULL;
    max_degree_num = NULL;
}
Graph::~Graph(){
    if(degree!=NULL){
        delete [] degree;
        degree = NULL;
    }
    if(pstart!=NULL){
        delete [] pstart;
        pstart = NULL;
    }
    if(out_pstart!=NULL){
        delete [] out_pstart;
        out_pstart = NULL;
    }
    if(in_pstart!=NULL){
        delete [] in_pstart;
        in_pstart = NULL;
    }
    if(edges!=NULL){
        delete [] edges;
        edges = NULL;
    }
    if(out_edges!=NULL){
        delete [] out_edges;
        out_edges = NULL;
    }
    if(in_edges!=NULL){
        delete [] in_edges;
        in_edges = NULL;
    }
    if(reverse!=NULL){
        delete [] reverse;
        reverse = NULL;
    }
    if(reverse_out!=NULL){
        delete [] reverse_out;
        reverse_out = NULL;
    }
    if(num_c!=NULL){
        delete [] num_c;
        num_c = NULL;
    }
    if(num_f!=NULL){
        delete [] num_f;
        num_f = NULL;
    }
    if(num_out_c!=NULL){
        delete [] num_out_c;
        num_out_c = NULL;
    }
    if(num_out_f!=NULL){
        delete [] num_out_f;
        num_out_f = NULL;
    }
    if(core_order_c2!=NULL){
        for (int i = 0; i < max_degree; i++) {
//            for (int j = 0; j < max_degree_num[i]; j++) {
//                delete[] core_order_c[i][j];
//                core_order_c[i][j] = NULL;
//            }
            delete[] core_order_c2[i];
            core_order_c2[i] = NULL;
         }
         delete[] core_order_c2;
         core_order_c2 = NULL;
    }
    if(core_order_f2!=NULL){
        for (int i = 0; i < max_degree; i++) {
//            for (int j = 0; j < max_degree_num[i]; j++) {
//                delete[] core_order_f[i][j];
//                core_order_f[i][j] = NULL;
//            }
            delete[] core_order_f2[i];
            core_order_f2[i] = NULL;
         }
         delete[] core_order_f2;
         core_order_f2 = NULL;
    }
   
    if(neighbor_order_f2!=NULL){
//        delete[] neighbor_order_f[0];
//        for (int i = 0; i < edge_m; i++) {
//            neighbor_order_f[i] = NULL;
//        }
        delete[] neighbor_order_f2;
        neighbor_order_f2 = NULL;
    }
    if(max_degree_num!=NULL){
        delete [] max_degree_num;
        max_degree_num = NULL;
    }
    
    if(neighbor_order_c2!=NULL){
//        delete[] neighbor_order_c[0];
//        for (int i = 0; i < edge_m; i++) {
//            neighbor_order_c[i] = NULL;
//        }
        delete[] neighbor_order_c2;
        neighbor_order_c2 = NULL;
    }
    
}

void Graph::readGraph(){
    ifstream infile;   //输入流
    
    infile.open(str+"/degree.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open degree file failure"<<endl;
        exit(0);
    }
    infile>>n>>m;
    
    if(out_pstart == NULL) out_pstart = new int[n+1];
    if(in_pstart == NULL) in_pstart = new int[n+1];
    if(out_edges == NULL) out_edges = new unsigned int[m];
    if(in_edges == NULL) in_edges = new unsigned int[m];
    
     
    out_pstart[0] = 0;
    in_pstart[0] = 0;
    
    int outD, inD, starti = 0;
    
    while (!infile.eof())            // 若未到文件结束一直循环
    {
        infile >> outD >> inD;
        out_pstart[starti+1] = outD + out_pstart[starti];
        in_pstart[starti+1] = inD + in_pstart[starti];
        starti++;
    }
    infile.close();
    
    infile.open(str+"/out_edges.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open out_edges file failure"<<endl;
        exit(0);
    }
    int mm_;
    infile >> mm_;
    int outi = 0;
    while (!infile.eof())            // 若未到文件结束一直循环
    {
        infile >> out_edges[outi];
        outi++;
    }
    infile.close();
    
    infile.open(str+"/in_edges.txt", ios::in);
    
    if (!infile.is_open()){
        cout<<"Open in_edges file failure"<<endl;
        exit(0);
    }
    int ini = 0;
    infile >> mm_;
    while (!infile.eof())            // 若未到文件结束一直循环
    {
        infile >> in_edges[ini];
        ini++;
    }
    infile.close();
    
    cout<<"read!"<<endl;
    getDegree();
    
    cout<<"getDegree!"<<endl;
}

void Graph::readGraph_update(){
    ifstream infile;   //输入流
    
    infile.open(str+"/degree.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open degree file failure"<<endl;
        exit(0);
    }
    infile>>n>>m;
    
    update_in_num.resize(n);
    update_out_num.resize(n);
    update_in_edges.resize(n);
    update_out_edges.resize(n);
    int starti = 0;
    while (!infile.eof())            // 若未到文件结束一直循环
    {
        infile >> update_out_num[starti] >> update_in_num[starti];
        starti++;
    }
    infile.close();
    
    infile.open(str+"/out_edges.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open out_edges file failure"<<endl;
        exit(0);
    }
    int point;
    int mm_;
    infile >> mm_;
    for(int i = 0;i<n;i++){
        for(int j = 0;j<update_out_num[i];j++){
            infile >> point;
            update_out_edges[i].push_back(point);
        }
    }
    infile.close();
    
    infile.open(str+"/in_edges.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open in_edges file failure"<<endl;
        exit(0);
    }
    infile >> mm_;
    for(int i = 0;i<n;i++){
        for(int j = 0;j<update_in_num[i];j++){
            infile >> point;
            update_in_edges[i].push_back(point);
        }
    }
    infile.close();
    
    cout<<"read!"<<endl;
    
}

void Graph::creatIndex(){
    clock_t startTime,endTime1,endTime2;
    startTime = clock();//计时开始
    
    getTti();
    
    endTime1 = clock();//计时结束
    cout << "The getTtie time is: " <<(float)(endTime1 - startTime) / CLOCKS_PER_SEC << "s" << endl;
    

    if(in_pstart!=NULL){
        delete [] in_pstart;
        in_pstart = NULL;
    }

    if(in_edges!=NULL){
        delete [] in_edges;
        in_edges = NULL;
    }
    
    getNeighborOrder();
    
    endTime1 = clock();//计时结束
    cout << "The getNeighborOrder time is: " <<(float)(endTime1 - startTime) / CLOCKS_PER_SEC << "s" << endl;
    
    if(out_edges!=NULL){
        delete [] out_edges;
        out_edges = NULL;
    }
    
    
    if(out_pstart!=NULL){
        delete [] out_pstart;
        out_pstart = NULL;
    }
    
    if(reverse!=NULL){
        delete [] reverse;
        reverse = NULL;
    }

    if(num_out_c!=NULL){
        delete [] num_out_c;
        num_out_c = NULL;
    }
    if(num_out_f!=NULL){
        delete [] num_out_f;
        num_out_f = NULL;
    }
    getCoreOrder();
    
    endTime1 = clock();//计时结束
    cout << "The index create time is: " <<(float)(endTime1 - startTime) / CLOCKS_PER_SEC << "s" << endl;
    
    //writeIndex();
    
    endTime2 = clock();//计时结束
    cout << "The write time is: " <<(float)(endTime2 - endTime1) / CLOCKS_PER_SEC << "s" << endl;
}


void Graph::getDegree(){
    if(pstart == NULL) pstart = new int[n+1];
    if(degree == NULL) degree = new int[n];
    pstart[0] = 0;
    edges = new unsigned int[(long)2*m];
    int edgesi = 0;
    for(int i = 0;i<n;i++){
        int l1 = out_pstart[i+1] - out_pstart[i];
        int l2 = in_pstart[i+1] - in_pstart[i];
        int i1 = 0, i2 = 0, num = 0;
        while(i1<l1 && i2<l2){
            
            if(out_edges[out_pstart[i] + i1] == in_edges[in_pstart[i] + i2]){
                edges[edgesi] = out_edges[out_pstart[i] + i1];
                edgesi++;
                i1++;
                i2++;
                num++;
            }else if(out_edges[out_pstart[i] + i1] < in_edges[in_pstart[i] + i2]){
                edges[edgesi] = out_edges[out_pstart[i] + i1];
                edgesi++;
                i1++;
                num++;
            }else{
                edges[edgesi] = in_edges[in_pstart[i] + i2];
                edgesi++;
                i2++;
                num++;
            }
        }
        while(i1<l1){
            edges[edgesi] = out_edges[out_pstart[i] + i1];
            edgesi++;
            i1++;
            num++;
        }
        while(i2<l2){
            edges[edgesi] = in_edges[in_pstart[i] + i2];
            edgesi++;
            i2++;
            num++;
        }
        
        if(num>max_degree) max_degree = num;
        
        degree[i] = num;
        edge_m = edge_m + num;
        pstart[i+1] = pstart[i] + num;
    }
    
    reverse = new unsigned int[(long)edge_m];
    reverse_out = new unsigned int[(long)(m+1)];
//    num_c = new unsigned int[(long)edge_m];
//    num_f = new unsigned int[(long)edge_m];
    num_out_c = new unsigned int[(long)(m+1)];
    num_out_f = new unsigned int[(long)(m+1)];
    for(unsigned int i = 0;i<m;i++) {
        num_out_c[i] = 0;
        num_out_f[i] = 0;
        reverse_out[i] = m;
    }
    num_out_c[m] = 0;
    num_out_f[m] = 0;
    initReverse();
    initReverse_out();
}

int Graph::intersection_f(unsigned int *A, unsigned int *B,unsigned int a1, unsigned int a2, unsigned int b1, unsigned int b2){
    int outi = 0;
    int i = a1, j = b1;
    while(i<a2 && j<b2){
        if(A[i] == B[j]){
            num_out_f[i]++;
            num_out_f[j]++;
            outi++;
            i++;
            j++;
        }else if(A[i]<B[j]){
            i++;
        }else{
            j++;
        }
    }
    
    return outi;
    
}

int Graph::intersection_c(unsigned int *A, unsigned int *B,unsigned int a1,unsigned int a2,unsigned int b1,unsigned int b2, int u){
    int outi = 0;
    int i = a1, j = b1;
    while(i<a2 && j<b2){
        if(A[i] == B[j]){
            if(u<A[i]){
                int v = in_edges[i];
                num_out_c[binary_search(out_edges,out_pstart[v],out_pstart[v+1],u)]++;
                num_out_c[j]++;
                outi++;
            }
            i++;
            j++;
        }else if(A[i]<B[j]){
            i++;
        }else{
            j++;
        }
    }
    
    return outi;
    
}

unsigned int Graph::binary_search(const unsigned int *array, int b, int e, int val) {
#ifdef _DEBUG_
    if(e < b) printf("??? WA1 in binary_search\n");
#endif
    -- e;
    if(array[e] < val) return e+1;
    while(b < e) {
        int mid = b + (e-b)/2;
        if(array[mid] >= val) e = mid;
        else b = mid+1;
    }
#ifdef _DEBUG_
    if(array[e] < val) printf("??? WA2 in binary_search\n");
#endif
    return e;
}


int Graph::BinarySearch(int *a, int value, int n){
    int low, high, mid;
    low = 0;
    high = n-1;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(a[mid]==value)
            return 1;
        if(a[mid]>value)
            high = mid-1;
        if(a[mid]<value)
            low = mid+1;
    }
    return 0;
}

int Graph::BinarySearch2(int *a, int value, int b, int e){
    int low, high, mid;
    low = b;
    high = e-1;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(a[mid]==value)
            return 1;
        if(a[mid]>value)
            high = mid-1;
        if(a[mid]<value)
            low = mid+1;
    }
    return 0;
}
unsigned int Graph::BinarySearch4(unsigned int *a,unsigned int value,unsigned int b, unsigned int e){
    long low, high, mid;
//    if(e == 14){
//        ;
//    }
    low = b;
    high = e-1;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(a[mid]==value)
            return (unsigned int)mid;
        if(a[mid]>value)
            high = mid-1;
        if(a[mid]<value)
            low = mid+1;
    }
    return m;
}

int Graph::BinarySearch3(vector<int> a, int value){
    int low, high, mid;
    low = 0;
    high = (int)a.size()-1;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(a[mid]==value)
            return 1;
        if(a[mid]>value)
            high = mid-1;
        if(a[mid]<value)
            low = mid+1;
    }
    return 0;
}

void Graph::initReverse(){
    for(unsigned int i = 0;i<n;i++){
        for(unsigned int j = pstart[i]; j<pstart[i+1];j++){
            unsigned int v = edges[j];
            if(v<i) continue;
            unsigned int reverse_edge_id = binary_search(edges, pstart[v], pstart[v+1], i);
            reverse[j] = reverse_edge_id;
            reverse[reverse_edge_id] = j;
        }
    }
}

void Graph::initReverse_out(){
    for(unsigned int i = 0;i<n;i++){
        for(unsigned int j = out_pstart[i]; j<out_pstart[i+1];j++){
            unsigned int v = out_edges[j];
            if(v<i) continue;
            unsigned int reverse_edge_id = BinarySearch4(out_edges, i, out_pstart[v], out_pstart[v+1]);
            if(reverse_edge_id < m){
                reverse_out[j] = reverse_edge_id;
                reverse_out[reverse_edge_id] = j;
            }
            
        }
    }
}

void Graph::getTti(){
   //unsigned int *commonV = new unsigned int[max_degree+1];
    for(int i = 0; i < n; i++){
        if(i%10000 == 0) cout<<i<<endl;
        for(unsigned int j = out_pstart[i]; j<out_pstart[i+1]; j++){
            unsigned int v = out_edges[j];
            if(degree[i]/degree[v]>100||degree[v]/degree[i]>100) continue;
            int num = intersection_f(out_edges, out_edges, out_pstart[i],  out_pstart[i+1], out_pstart[v], out_pstart[v+1]);
            num_out_f[j] = num_out_f[j] + num;
            if(i < v){
                int num = intersection_c(in_edges, out_edges, in_pstart[i],  in_pstart[i+1], out_pstart[v], out_pstart[v+1], i);
                num_out_c[j] = num_out_c[j] + num;
            }
            
        }
    }
//    if(commonV!=NULL){
//        delete[] commonV; commonV = NULL;
//    }
               
}

bool comp(float* s1,float* s2){//相似度从大到小
    
    return s1[1]>s2[1];
}


bool comp2(float* s1,float* s2){//相邻点从小到大
    
    return s1[0]<s2[0];
}

bool comp3(point s1,point s2){//相似度从大到小
    
    return s1.value>s2.value;
}

void Graph::getNeighborOrder(){
    
    neighbor_order_c2 = new point[edge_m];
    neighbor_order_f2 = new point[edge_m];
    for(int i = 0;i<n;i++){
        
        unsigned int j, out_j;
        
        for(j = pstart[i], out_j = out_pstart[i];j<pstart[i+1];){
            int v = edges[j], out_v = out_edges[out_j];
            if(v<i){
                if(v == out_v){
                    j++;
                    out_j++;
                }else{
                    j++;
                }
                continue;
            }
            
            if(v == out_v){
                neighbor_order_c2[reverse[j]].value = neighbor_order_c2[j].value = (num_out_c[out_j] + num_out_c[reverse_out[out_j]] + 4) / (2*(float)pow((long)((long)(degree[i]+1) * (long)(degree[v]+1)),0.5));
                neighbor_order_c2[j].vertex = v;
                neighbor_order_c2[reverse[j]].vertex = i;
                neighbor_order_f2[reverse[j]].value = neighbor_order_f2[j].value = (num_out_f[out_j] + num_out_f[reverse_out[out_j]]+ 12) / (6*(float)pow((long)((long)(degree[i]+1) * (long)(degree[v]+1)),0.5));
                neighbor_order_f2[j].vertex = v;
                neighbor_order_f2[reverse[j]].vertex = i;
                j++;
                out_j++;
            }else{
                neighbor_order_c2[reverse[j]].value = neighbor_order_c2[j].value = (num_out_c[reverse_out[out_j]] + 4) / (2*(float)pow((long)((long)(degree[i]+1) * (long)(degree[v]+1)),0.5));
                neighbor_order_c2[j].vertex = v;
                neighbor_order_c2[reverse[j]].vertex = i;
                neighbor_order_f2[reverse[j]].value = neighbor_order_f2[j].value = (num_out_f[reverse_out[out_j]]+ 12) / (6*(float)pow((long)((long)(degree[i]+1) * (long)(degree[v]+1)),0.5));
                neighbor_order_f2[j].vertex = v;
                neighbor_order_f2[reverse[j]].vertex = i;
                j++;
            }
            
            
        }
        sort(neighbor_order_c2+pstart[i], neighbor_order_c2+pstart[i+1],comp3);
        sort(neighbor_order_f2+pstart[i], neighbor_order_f2+pstart[i+1],comp3);
    }
}

void Graph::getCoreOrder(){
    cout<<"max_degree:"<<max_degree<<endl;
    core_order_c2 = new point*[max_degree];
    core_order_f2 = new point*[max_degree];
    max_degree_num = new int[max_degree];
    
    int *core_degree = new int[n];
    int *circulate_core = new int[n];
    int circulate_corei = 0;
    
    for(int i = 0;i<n;i++){
        core_degree[i] = degree[i];
        if(degree[i] > 0)
            circulate_core[circulate_corei++] = i;
    }
    int circulate = 0;
    int corei, circulate_corei2;
    for(int i = 0;i<max_degree;i++){
        if(i%10 == 0 && i<10000) cout<<i<<endl;
        corei = 0;
        core_order_c2[i] = new point[circulate_corei];
        core_order_f2[i] = new point[circulate_corei];
        max_degree_num[circulate] = circulate_corei;
        circulate_corei2 = circulate_corei;
        circulate_corei = 0;
        for(int j2 = 0;j2<circulate_corei2;j2++){
            int j = circulate_core[j2];
            core_order_c2[i][corei].vertex = j;
            core_order_c2[i][corei].value = neighbor_order_c2[pstart[j] + circulate].value;
            
            core_order_f2[i][corei].vertex = j;
            core_order_f2[i][corei].value = neighbor_order_f2[pstart[j] + circulate].value;
            
            core_degree[j]--;
            if(core_degree[j] > 0) circulate_core[circulate_corei++] = j;
            corei++;
                
        }
        
        sort(core_order_c2[i],core_order_c2[i]+corei,comp3);
        sort(core_order_f2[i],core_order_f2[i]+corei,comp3);
        
        circulate++;
    }
    if(core_degree!=NULL){
        delete[] core_degree; core_degree = NULL;
    }
    if(circulate_core!=NULL){
        delete[] circulate_core; circulate_core = NULL;
    }
    
}

void Graph::writeIndex(){
    ofstream fout(str+"/index/degree.txt",ios::out); //创建待写入数据文件
    fout<<n<<" "<<m<<" "<<edge_m<<" "<<max_degree<<"\n";
    for(int i = 0; i< n-1;i++) fout<<(long)degree[i]<<"\n";
    fout<<(long)degree[n-1];
    fout.close();
    
    ofstream fout2(str+"/index/nei_order_c.txt",ios::out); //创建待写入数据文件
    for(int i = 0; i< n-1;i++){
        for(int j = pstart[i]; j<pstart[i+1]; j++){
            fout2<<(long)neighbor_order_c2[j].vertex<<" "<<neighbor_order_c2[j].value<<"\n";
        }
    }
    for(int j = pstart[n-1]; j<pstart[n]-1; j++){
        fout2<<(long)neighbor_order_c2[j].vertex<<" "<<neighbor_order_c2[j].value<<"\n";
    }
    fout2<<(long)neighbor_order_c2[pstart[n]-1].vertex<<" "<<neighbor_order_c2[pstart[n]-1].value;
    fout2.close();
    
    ofstream fout3(str+"/index/nei_order_f.txt",ios::out); //创建待写入数据文件
    for(int i = 0; i< n-1;i++){
        for(int j = pstart[i]; j<pstart[i+1]; j++){
            fout3<<(long)neighbor_order_f2[j].vertex<<" "<<neighbor_order_f2[j].value<<"\n";
        }
    }
    for(int j = pstart[n-1]; j<pstart[n]-1; j++){
        fout3<<(long)neighbor_order_f2[j].vertex<<" "<<neighbor_order_f2[j].value<<"\n";
    }
    fout3<<(long)neighbor_order_f2[pstart[n]-1].vertex<<" "<<neighbor_order_f2[pstart[n]-1].value;
    fout3.close();
    
    ofstream fout4(str+"/index/core_order_c.txt",ios::out); //创建待写入数据文件
    for(int i = 0;i<max_degree-1;i++){
        fout4<<i+2<<" "<<max_degree_num[i]<<"\n";
        for(int j = 0;j<max_degree_num[i];j++){
            fout4<<(long)core_order_c2[i][j].vertex<<" "<<core_order_c2[i][j].value<<"\n";
        }
    }
    fout4<<max_degree+1<<" "<<max_degree_num[max_degree-1]<<"\n";
    for(int j = 0;j<max_degree_num[max_degree-1]-1;j++)
        fout4<<(long)core_order_c2[max_degree-1][j].vertex<<" "<<core_order_c2[max_degree-1][j].value<<"\n";
    fout4<<(long)core_order_c2[max_degree-1][max_degree_num[max_degree-1]-1].vertex<<" "<<core_order_c2[max_degree-1][max_degree_num[max_degree-1]-1].value;
    fout4.close();
    
    ofstream fout5(str+"/index/core_order_f.txt",ios::out); //创建待写入数据文件
    for(int i = 0;i<max_degree-1;i++){
        fout5<<i+2<<" "<<max_degree_num[i]<<"\n";
        for(int j = 0;j<max_degree_num[i];j++)
            fout5<<(long)core_order_f2[i][j].vertex<<" "<<core_order_f2[i][j].value<<"\n";
    }
    fout5<<max_degree+1<<" "<<max_degree_num[max_degree-1]<<"\n";
    for(int j = 0;j<max_degree_num[max_degree-1]-1;j++)
        fout5<<(long)core_order_f2[max_degree-1][j].vertex<<" "<<core_order_f2[max_degree-1][j].value<<"\n";
    fout5<<(long)core_order_f2[max_degree-1][max_degree_num[max_degree-1]-1].vertex<<" "<<core_order_f2[max_degree-1][max_degree_num[max_degree-1]-1].value;
    fout5.close();
}

void Graph::readIndex(){
    ifstream infile;   //输入流
    int i = 0;
    
    infile.open(str+"/index/degree.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open degree file failure"<<endl;
        exit(0);
    }

    infile >> n >> m >> edge_m >> max_degree;
    cout << n<<" "<< m <<" "<< edge_m <<" "<< max_degree<<endl;

    if(pstart == NULL) pstart = new int[n+1];
    if(degree == NULL) degree = new int[n];

    pstart[0] = 0;

    
    while (!infile.eof())            // 若未到文件结束一直循环
    {
        infile >> degree[i];
        pstart[i+1] = degree[i] + pstart[i];
        i++;
    }
    infile.close();
    
    neighbor_order_c2 = new point[edge_m];
    
    neighbor_order_f2 = new point[edge_m];
    
    infile.open(str+"/index/nei_order_c.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open nei_order_c file failure"<<endl;
        exit(0);
    }
    i=0;
    while (!infile.eof())            // 若未到文件结束一直循环
    {
        infile >> neighbor_order_c2[i].vertex >> neighbor_order_c2[i].value;
        i++;
    }
    infile.close();
    
    infile.open(str+"/index/nei_order_f.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open nei_order_f file failure"<<endl;
        exit(0);
    }
    i=0;
    while (!infile.eof())            // 若未到文件结束一直循环
    {
        infile >> neighbor_order_f2[i].vertex >> neighbor_order_f2[i].value;
        i++;
    }
    infile.close();
    
    if(core_order_c2 == NULL) core_order_c2 = new point*[max_degree];
    if(core_order_f2 == NULL) core_order_f2 = new point*[max_degree];
    
    infile.open(str+"/index/core_order_c.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open core_order_c file failure"<<endl;
        exit(0);
    }
    if(max_degree_num == NULL) max_degree_num = new int[max_degree];
    int core;
    for(int j = 0;j<max_degree;j++){
        infile >> core >> max_degree_num[j];
        core_order_c2[j] = new point[max_degree_num[j]];
        for(int k = 0;k<max_degree_num[j];k++){
            infile >> core_order_c2[j][k].vertex >> core_order_c2[j][k].value;
        }
    }
    infile.close();
    
    infile.open(str+"/index/core_order_f.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open core_order_f file failure"<<endl;
        exit(0);
    }
    for(int j = 0;j<max_degree;j++){
        infile >> core >> core;
        core_order_f2[j] = new point[max_degree_num[j]];
        //for(int k2 = 0;k2<max_degree_num[j];k2++) core_order_f[j][k2] = new float[2];
        for(int k = 0;k<max_degree_num[j];k++){
            infile >> core_order_f2[j][k].vertex >> core_order_f2[j][k].value;
        }
    }
    infile.close();
}

void Graph::query(float parameter1,float parameter2, int parameterNum){
    if(parameterNum-1>max_degree) {
        cout<<"!!!";
        return;
    }
    int *core = new int[2*max_degree_num[parameterNum-2] + 1];
    int corei = 0;
    for(int i = 0;i<max_degree_num[parameterNum-2];i++){
//        cout<<core_order_c[parameterNum-2][i][1]<<endl;
        if(core_order_c2[parameterNum-2][i].value>=parameter1){
            core[corei] = core_order_c2[parameterNum-2][i].vertex;
            corei++;
        }else break;
    }
    for(int i = 0;i<max_degree_num[parameterNum-2];i++){
        if(core_order_f2[parameterNum-2][i].value>=parameter2){
            core[corei] = core_order_f2[parameterNum-2][i].vertex;
            corei++;
        }else break;
    }
    sort(core, core + corei);
    
    int *all_core = new int[corei];
    
    int all_corei = 0;
    
    for(int i = 0;i<corei-1;i++){
        if(core[i] == core[i+1]){
            all_core[all_corei] = core[i];
            i++;
            all_corei++;
        }
    }
    if(core!=NULL){
        delete [] core; core = NULL;
    }
    
     
    bool *visited = new bool[n];
    for(int i = 0;i<n;i++) visited[i] = true;
    int ***cluster = new int**[all_corei];
    int clusterNum = 0;
    int *all_nei = new int[max_degree+1];
    for(int i = 0;i<all_corei;i++){
        //cout<<i<<" "<<all_core[i]<<endl;
        if(!visited[all_core[i]]) continue;
        
        int *n_core = new int[n];
        int n_corei = 0;
        
        visited[all_core[i]] = false;
        
        queue<int> q;
        q.push(all_core[i]);
        
        cluster[clusterNum] = new int*[n+1];
        int clusteri = 0;
        
        
        while(!q.empty()){
            int q_m = q.front();
            
            cluster[clusterNum][clusteri] = new int[2];
            cluster[clusterNum][clusteri][0] = q_m;
            cluster[clusterNum][clusteri][1] = 1;
            clusteri++;
            
            q.pop();
            int all_nei_num = 0;
            
            getAllNei(parameter1, parameter2, q_m, all_nei,all_nei_num);
            for(int all_neii = 0;all_neii<all_nei_num;all_neii++){
                //int a = all_nei[all_neii];
                if(visited[all_nei[all_neii]]){
                    if(BinarySearch(all_core, all_nei[all_neii], all_corei)){
                        q.push(all_nei[all_neii]);
                        visited[all_nei[all_neii]] = false;
                    }else{
                        visited[all_nei[all_neii]] = false;
                        
                        n_core[n_corei] = all_nei[all_neii];
                        //cout<<n_corei<<" "<<n_core[n_corei]<<endl;
                        n_corei++;
                        
                        cluster[clusterNum][clusteri] = new int[2];
                        cluster[clusterNum][clusteri][0] = all_nei[all_neii];
                        cluster[clusterNum][clusteri][1] = 0;
                        clusteri++;
                        
                    }
                }
            }
        }
        
        for(int k = 0;k<n_corei;k++){
            visited[n_core[k]] = true;
        }
        cluster[clusterNum][clusteri] = new int[2];
        cluster[clusterNum][clusteri][0] = -1;
        cluster[clusterNum][clusteri][1] = -1;
        clusteri++;
        cluster[clusterNum][clusteri] = NULL;
        
        clusterNum++;
    }
    cluster[clusterNum] = NULL;
    
    if(all_core!=NULL){
        delete [] all_core; all_core = NULL;
    }
    
    if(visited!=NULL){
        delete [] visited; visited = NULL;
    }
    if(all_nei!=NULL){
       delete [] all_nei; all_nei = NULL;
    }
    if(cluster!=NULL){
        for (int i = 0; i < clusterNum; i++) {
            for (int j = 0; j < n; j++) {
                if(cluster[i][j]!=NULL){
                    delete[] cluster[i][j];
                    cluster[i][j] = NULL;
                }else break;
                
            }
            if(cluster[i]!=NULL){
                delete[] cluster[i];
                cluster[i] = NULL;
            }else break;
            
         }
         delete[] cluster;
         cluster = NULL;
    }
    
}

void Graph::getAllNei(float parameter1, float parameter2, int v, int *all_nei, int &all_nei_num){
    int *nei = new int[2*degree[v]];
    int neii = 0;
    for(int i = pstart[v];i<pstart[v+1];i++){
        if(neighbor_order_c2[i].value>=parameter1){
            nei[neii] = neighbor_order_c2[i].vertex;
            neii++;
        }else break;
    }
    for(int i = pstart[v];i<pstart[v+1];i++){
        if(neighbor_order_f2[i].value>=parameter2){
            nei[neii] = neighbor_order_f2[i].vertex;
            neii++;
        }else break;
    }
    sort(nei, nei + neii);
    
    for(int i = 0;i<neii-1;i++){
        if(nei[i] == nei[i+1]){
            all_nei[all_nei_num] = nei[i];
            i++;
            all_nei_num++;
        }
    }
    delete [] nei; nei = NULL;
}

void Graph::readIndex_update(){
   
    
    ifstream infile;   //输入流
    
    infile.open(str+"/index/degree.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open degree file failure"<<endl;
        exit(0);
    }

    infile >> n >> m >> edge_m >> max_degree;
    cout << n<<" "<< m <<" "<< edge_m <<" "<< max_degree<<endl;
    
    nbr_mp_c.resize(n);
    cores_mp_c.resize(max_degree);
    nbr_mp_f.resize(n);
    cores_mp_f.resize(max_degree);
    update_degree.resize(n);
    nbr_order_old_c.resize(n);
    nbr_order_old_f.resize(n);
    
    int degreei = 0;
    while (!infile.eof())            // 若未到文件结束一直循环
    {
        infile >> update_degree[degreei];
        degreei++;
    }
    infile.close();
    
    
    int n_;
    float val_;
    infile.open(str+"/index/nei_order_c.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open nei_order_c file failure"<<endl;
        exit(0);
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<update_degree[i];j++){
            infile >> n_ >> val_;
            nbr_mp_c[i].insert(make_pair(val_, n_));
            nbr_order_old_c[i].push_back(val_);
        }
    }
    infile.close();
    
    infile.open(str+"/index/nei_order_f.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open nei_order_f file failure"<<endl;
        exit(0);
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<update_degree[i];j++){
            infile >> n_ >> val_;
            nbr_mp_f[i].insert(make_pair(val_, n_));
            nbr_order_old_f[i].push_back(val_);
        }
    }
    infile.close();
    
    infile.open(str+"/index/core_order_c.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open core_order_c file failure"<<endl;
        exit(0);
    }
//    if(max_degree_num == NULL) max_degree_num = new int[max_degree];
    update_max_degree_num.resize(max_degree);
    int core;
    for(int j = 0;j<max_degree;j++){
        infile >> core >> update_max_degree_num[j];
        for(int k = 0;k<update_max_degree_num[j];k++){
            infile >> n_ >> val_;
            cores_mp_c[j].insert(make_pair(val_, n_));
        }
    }
    infile.close();
    
    infile.open(str+"/index/core_order_f.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open core_order_f file failure"<<endl;
        exit(0);
    }
    for(int j = 0;j<max_degree;j++){
        infile >> core >> core;
        for(int k = 0;k<update_max_degree_num[j];k++){
            infile >> n_ >> val_;
            cores_mp_f[j].insert(make_pair(val_, n_));
        }
    }
    infile.close();
}

void Graph::insert(int u, int v){
    clock_t startTime,endTime;
    
    m++;
    edge_m++;
    
    unordered_map<int,int> add_c;
    unordered_map<int,int> add_f;
    int all_c = 0, all_f = 0;
    
    if(u>=n && v>=n){
        cout<<"case 1"<<endl;
        if(u<v) n = v+1;
        else n = u+1;
        update_degree.resize(n);
        nbr_mp_c.resize(n);
        nbr_mp_f.resize(n);
        
        nbr_order_old_c.resize(n);
        nbr_order_old_f.resize(n);
        
        update_in_num.resize(n);
        update_out_num.resize(n);
        update_in_edges.resize(n);
        update_out_edges.resize(n);
        
        update_in_num[v] = 1;
        update_out_num[u] = 1;
        update_in_edges[v].push_back(u);
        update_out_edges[u].push_back(v);
        
        update_degree[u] = 1;
        update_degree[v] = 1;
        nbr_mp_c[u].insert(make_pair(1, v));
        nbr_mp_c[v].insert(make_pair(1, u));
        nbr_mp_f[u].insert(make_pair(1, v));
        nbr_mp_f[v].insert(make_pair(1, u));
        
        nbr_order_old_c[u].push_back(1);
        nbr_order_old_f[u].push_back(1);
        
        nbr_order_old_c[v].push_back(1);
        nbr_order_old_f[v].push_back(1);
        
        cores_mp_c[0].insert(make_pair(1, u));
        cores_mp_c[0].insert(make_pair(1, v));
        cores_mp_f[0].insert(make_pair(1, u));
        cores_mp_f[0].insert(make_pair(1, v));
    }else if(u>=n || v>=n){
        cout<<"case 2"<<endl;
        if(u<v) n = v+1;
        else n = u+1;
        
//        startTime = clock();//计时开始
        
        update_degree.resize(n);
        nbr_mp_c.resize(n);
        nbr_mp_f.resize(n);
        nbr_order_old_c.resize(n);
        nbr_order_old_f.resize(n);
        update_in_num.resize(n);
        update_out_num.resize(n);
        update_in_edges.resize(n);
        update_out_edges.resize(n);
        
//        endTime = clock();//计时结束
//        cout << "The pdate_in_edges.resize(n) time is: " <<(float)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
        
        
        update_in_num[v]++;
        update_out_num[u]++;
        update_in_edges[v].push_back(u);
        update_out_edges[u].push_back(v);
        
        sort(update_in_edges[v].begin(), update_in_edges[v].end());
        sort(update_out_edges[u].begin(), update_out_edges[u].end());
        
        if(u<v) swap(u, v);
        
        update_degree[u] = 1;
        update_degree[v]++;
        
        if(update_degree[v]>max_degree){
            max_degree++;
            update_max_degree_num.resize(max_degree);
            update_max_degree_num[max_degree-1] = 1;
            cores_mp_c.resize(max_degree);
            cores_mp_f.resize(max_degree);
        }
        
        float sim_c = (float)4/(2*(pow(update_degree[u]*update_degree[v],0.5)));
        float sim_f = (float)12/(6*(pow(update_degree[u]*update_degree[v],0.5)));
        
        nbr_mp_c[u].insert(make_pair(sim_c, v));
        nbr_mp_f[u].insert(make_pair(sim_f, v));
        nbr_order_old_c[u].push_back(sim_c);
        nbr_order_old_f[u].push_back(sim_f);
        
//        startTime = clock();//计时开始
        update_nei1(add_c,add_f,0,0,v,u);
//        endTime = clock();//计时结束
//        cout << "The update_nei1 time is: " <<(float)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
        
        cores_mp_c[0].insert(make_pair(sim_c, u));
        cores_mp_f[0].insert(make_pair(sim_f, u));
    }else{
        if(BinarySearch3(update_out_edges[u], v)){
            cout<<u<<"->"<<v<<" exist!!!"<<endl;
            m--;
            return;
        }
        get_add_c_and_f(add_c,add_f,u,v,all_c,all_f);
        update_in_num[v]++;
        update_out_num[u]++;
        update_in_edges[v].push_back(u);
        update_out_edges[u].push_back(v);
        sort(update_in_edges[v].begin(), update_in_edges[v].end());
        sort(update_out_edges[u].begin(), update_out_edges[u].end());
        
        if(BinarySearch3(update_out_edges[v], u)){
            edge_m--;
            cout<<"case 3"<<endl;
            update_nei2(add_c,add_f,all_c,all_f,v,u);
            update_nei2(add_c,add_f,all_c,all_f,u,v);
        }else{
            cout<<"case 4"<<endl;
            update_degree[u]++;
            update_degree[v]++;
            if(update_degree[v]>max_degree || update_degree[u]>max_degree){
                max_degree++;
                update_max_degree_num.resize(max_degree);
                
                cores_mp_c.resize(max_degree);
                cores_mp_f.resize(max_degree);
                
                update_max_degree_num[max_degree-1]++;
                
                if(update_degree[v] == max_degree && update_degree[u] == max_degree) update_max_degree_num[max_degree-1]++;
            }
            update_nei1(add_c,add_f,all_c,all_f,v,u);
            update_nei1(add_c,add_f,all_c,all_f,u,v);
        }
    }
}

void Graph::get_add_c_and_f(unordered_map<int,int> &add_c, unordered_map<int,int> &add_f, int u, int v, int &all_c, int &all_f){
    
    int ui = 0, vi = 0, ul = update_out_num[u], vl = update_out_num[v];
    
    while(ui<ul && vi < vl){
        
        if(update_out_edges[u][ui] == update_out_edges[v][vi]){
            add_f[update_out_edges[u][ui]]++;
            all_f++;
            ui++;
            vi++;
        }
        else if(update_out_edges[u][ui] < update_out_edges[v][vi]) ui++;
        else vi++;
    }
    
    ui = 0;
    vi = 0;
    vl = update_in_num[v];
    while(ui<ul && vi < vl){
        
        if(update_out_edges[u][ui] == update_in_edges[v][vi]){
            add_f[update_out_edges[u][ui]]++;
            all_f++;
            ui++;
            vi++;
        }
        else if(update_out_edges[u][ui] < update_in_edges[v][vi]) ui++;
        else vi++;
    }
    
    ui = 0;
    vi = 0;
    ul = update_in_num[u];
    while(ui<ul && vi < vl){
        
        if(update_in_edges[u][ui] == update_in_edges[v][vi]){
            add_f[update_in_edges[u][ui]]++;
            all_f++;
            ui++;
            vi++;
        }
        else if(update_in_edges[u][ui] < update_in_edges[v][vi]) ui++;
        else vi++;
    }
    
    ui = 0;
    vi = 0;
    vl = update_out_num[v];
    
    while(ui<ul && vi < vl){
        
        if(update_in_edges[u][ui] == update_out_edges[v][vi]){
            add_c[update_in_edges[u][ui]]++;
            all_c++;
            ui++;
            vi++;
        }
        else if(update_in_edges[u][ui] < update_out_edges[v][vi]) ui++;
        else vi++;
    }
}

void Graph::update_nei_order_c(int v, int w, float old_sim, float new_sim){
    auto pr = nbr_mp_c[v].equal_range(old_sim);
    if(pr.first != end(nbr_mp_c[v]))
    {
        for (auto iter = pr.first ; iter != pr.second; ++iter){
            if(iter->second == w){
                nbr_mp_c[v].erase(pr.first);
                nbr_mp_c[v].insert(make_pair(new_sim, w));
                break;
            }
        }
    }
    
}
void Graph::update_nei_order_f(int v, int w, float old_sim, float new_sim){
    auto pr = nbr_mp_f[v].equal_range(old_sim);
    if(pr.first != end(nbr_mp_f[v]))
    {
        for (auto iter = pr.first ; iter != pr.second; ++iter){
            if(iter->second == w){
                nbr_mp_f[v].erase(pr.first);
                nbr_mp_f[v].insert(make_pair(new_sim, w));
                break;
            }
        }
    }
}

void Graph::update_nei1(unordered_map<int,int> &add_c, unordered_map<int,int> &add_f, int all_c, int all_f, int u, int v){
    multimap<float, int, greater<float>> single = nbr_mp_c[u];
    nbr_mp_c[u].clear();
    for(multimap<float, int, greater<float>>::iterator it = single.begin();it!=single.end();++it){
        if(add_c.find(it->second)!=add_c.end()){
            int old_sim = round(it->first*2*(pow((update_degree[u]-1)*update_degree[it->second],0.5)));
            float new_sim = (float)(old_sim+add_c[it->second])/(2*(pow(update_degree[u]*update_degree[it->second],0.5)));
            float old_ = it->first;
            update_nei_order_c(it->second, u, old_, new_sim);
            nbr_mp_c[u].insert(make_pair(new_sim, it->second));
            update_core_c(it->second, old_, new_sim);
        }else{
            int old_sim = round(it->first*2*(pow((update_degree[u]-1)*update_degree[it->second],0.5)));
            float new_sim = (float)(old_sim)/(2*(pow(update_degree[u]*update_degree[it->second],0.5)));
            float old_ = it->first;
            update_nei_order_c(it->second, u, old_, new_sim);
            nbr_mp_c[u].insert(make_pair(new_sim, it->second));
            update_core_c(it->second, old_, new_sim);
        }
    }
    nbr_mp_c[u].insert(make_pair((float)(all_c+4)/(2*(pow(update_degree[u]*update_degree[v],0.5))), v));
    nbr_order_old_c[u].push_back(0);
    update_core_c(u, 0, 1);
    
    multimap<float, int, greater<float>> single2 = nbr_mp_f[u];
    nbr_mp_f[u].clear();
    for(multimap<float, int, greater<float>>::iterator it = single2.begin();it!=single2.end();++it){
        if(add_f.find(it->second)!=add_f.end()){
            int old_sim = round(it->first*2*(pow((update_degree[u]-1)*update_degree[it->second],0.5)));
            float new_sim = (float)(old_sim+add_f[it->second])/(2*(pow(update_degree[u]*update_degree[it->second],0.5)));
            float old_ = it->first;
            update_nei_order_f(it->second, u, it->first, new_sim);
            nbr_mp_f[u].insert(make_pair(new_sim, it->second));
            update_core_f(it->second, old_, new_sim);
        }else{
            int old_sim = round(it->first*2*(pow((update_degree[u]-1)*update_degree[it->second],0.5)));
            float new_sim = (float)(old_sim)/(2*(pow(update_degree[u]*update_degree[it->second],0.5)));
            float old_ = it->first;
            update_nei_order_f(it->second, u, it->first, new_sim);
            nbr_mp_f[u].insert(make_pair(new_sim, it->second));
            update_core_f(it->second, old_, new_sim);
        }
    }
    nbr_mp_f[u].insert(make_pair((float)(all_c+12)/(2*(pow(update_degree[u]*update_degree[v],0.5))), v));
    nbr_order_old_c[u].push_back(0);
    update_core_f(u, 0, 1);
}
void Graph::update_nei2(unordered_map<int,int> &add_c, unordered_map<int,int> &add_f, int all_c, int all_f, int u, int v){
    multimap<float, int, greater<float>> single = nbr_mp_c[u];
    nbr_mp_c[u].clear();
    for(multimap<float, int, greater<float>>::iterator it = single.begin();it!=single.end();++it){
        if(it->second == v){
            int old_sim = round(it->first*2*(pow((update_degree[u])*update_degree[it->second],0.5)));
            float new_sim = (float)(old_sim+all_c)/(2*(pow(update_degree[u]*update_degree[it->second],0.5)));
            nbr_mp_c[u].insert(make_pair(new_sim, it->second));
            continue;
        }
        if(add_c.find(it->second)!=add_c.end()){
            int old_sim = round(it->first*2*(pow((update_degree[u])*update_degree[it->second],0.5)));
            float new_sim = (float)(old_sim+add_c[it->second])/(2*(pow(update_degree[u]*update_degree[it->second],0.5)));
            float old_ = it->first;
            update_nei_order_c(it->second, u, it->first, new_sim);
            nbr_mp_c[u].insert(make_pair(new_sim, it->second));
            update_core_c(it->second, old_, new_sim);
        }else{
            nbr_mp_c[u].insert(make_pair(it->first, it->second));
        }
    }
    update_core_c(u, 0, 1);
    
    multimap<float, int, greater<float>> single2 = nbr_mp_f[u];
    nbr_mp_f[u].clear();
    for(multimap<float, int, greater<float>>::iterator it = single2.begin();it!=single2.end();++it){
        if(it->second == v){
            int old_sim = round(it->first*2*(pow((update_degree[u])*update_degree[it->second],0.5)));
            float new_sim = (float)(old_sim+all_f)/(2*(pow(update_degree[u]*update_degree[it->second],0.5)));
            nbr_mp_f[u].insert(make_pair(new_sim, it->second));
            continue;
        }
        if(add_f.find(it->second)!=add_f.end()){
            int old_sim = round(it->first*2*(pow((update_degree[u])*update_degree[it->second],0.5)));
            float new_sim = (float)(old_sim+add_f[it->second])/(2*(pow(update_degree[u]*update_degree[it->second],0.5)));
            float old_ = it->first;
            update_nei_order_f(it->second, u, it->first, new_sim);
            nbr_mp_f[u].insert(make_pair(new_sim, it->second));
            update_core_f(it->second, old_, new_sim);
        }else{
            nbr_mp_f[u].insert(make_pair(it->first, it->second));
        }
    }
    update_core_f(u, 0, 1);
}

void Graph::update_core_c(int u, float low, float high){
    if(low>high) swap(low, high);
    int i = -1;
    for(multimap<float, int, greater<float>>::iterator it = nbr_mp_c[u].begin();it!=nbr_mp_c[u].end();++it){
        i++;
        if(it->first>high) continue;
        if(it->first<low) break;
        auto pr = cores_mp_c[i].equal_range(nbr_order_old_c[u][i]);
        //cout<<nbr_order_old_c[u][i]<<endl;
        int judge = 1;
        if(pr.first != end(cores_mp_c[i]))
        {
            for (auto iter = pr.first ; iter != pr.second; ++iter){
                if(iter->second == u){
                    judge = 0;
                    cores_mp_c[i].erase(iter);
                    cores_mp_c[i].insert(make_pair(it->first, u));
                    nbr_order_old_c[u][i] = it->first;
                    break;
                }
            }
        }
        if(judge){
            cores_mp_c[i].insert(make_pair(it->first, u));
            nbr_order_old_c[u][i] = it->first;
        }
    }
}

void Graph::update_core_f(int u, float low, float high){
    if(low>high) swap(low, high);
    int i = -1;
    for(multimap<float, int, greater<float>>::iterator it = nbr_mp_f[u].begin();it!=nbr_mp_f[u].end();++it){
        i++;
        if(it->first>high) continue;
        if(it->first<low) break;
        auto pr = cores_mp_f[i].equal_range(nbr_order_old_f[u][i]);
        int judge = 1;
        if(pr.first != end(cores_mp_f[i]))
        {
            for (auto iter = pr.first ; iter != pr.second; ++iter){
                if(iter->second == u){
                    judge = 0;
                    cores_mp_f[i].erase(iter);
                    cores_mp_f[i].insert(make_pair(it->first, u));
                    nbr_order_old_f[u][i] = it->first;
                    break;
                }
            }
        }
        if(judge){
            cores_mp_f[i].insert(make_pair(it->first, u));
            nbr_order_old_f[u][i] = it->first;
        }
    }
}

void Graph::remove(int u, int v){
    if(!BinarySearch3(update_out_edges[u], v)){
        cout<<u<<"->"<<v<<" not exist!!!"<<endl;
        return;
    }
    m--;
    unordered_map<int,int> add_c;
    unordered_map<int,int> add_f;
    int all_c = 0, all_f = 0;
    
    get_add_c_and_f(add_c,add_f,u,v,all_c,all_f);
    
    update_in_num[v]--;
    update_out_num[u]--;
    update_in_edges[v].erase(std::remove(update_in_edges[v].begin(),update_in_edges[v].end(),u),update_in_edges[v].end());
    update_out_edges[u].erase(std::remove(update_out_edges[u].begin(),update_out_edges[u].end(),v),update_out_edges[u].end());
    
    if(BinarySearch3(update_out_edges[v], u)){
        delete_update_nei2(add_c,add_f,all_c,all_f,u,v);
        delete_update_nei2(add_c,add_f,all_c,all_f,v,u);
    }else{
        edge_m--;
        update_degree[u]--;
        update_degree[v]--;
        
        update_max_degree_num[update_degree[v]]--;
        update_max_degree_num[update_degree[u]]--;
     
        if(update_max_degree_num[update_degree[u]] == 0) max_degree = update_degree[u];
        else{
            if(update_max_degree_num[update_degree[v]] == 0) max_degree = update_degree[v];
        }
        
        auto pr = cores_mp_f[update_degree[v]].equal_range(nbr_order_old_f[v][update_degree[v]]);
        if(pr.first != end(cores_mp_f[update_degree[v]]))
        {
            for (auto iter = pr.first ; iter != pr.second; ++iter){
                if(iter->second == v){
                    cores_mp_f[update_degree[v]].erase(iter);
                    break;
                }
            }
        }
        auto pr2 = cores_mp_f[update_degree[u]].equal_range(nbr_order_old_f[u][update_degree[u]]);
        if(pr2.first != end(cores_mp_f[update_degree[u]]))
        {
            for (auto iter = pr2.first ; iter != pr2.second; ++iter){
                if(iter->second == u){
                    cores_mp_f[update_degree[u]].erase(iter);
                    break;
                }
            }
        }
        auto pr3 = cores_mp_c[update_degree[v]].equal_range(nbr_order_old_c[v][update_degree[v]]);
        if(pr3.first != end(cores_mp_c[update_degree[v]]))
        {
            for (auto iter = pr3.first ; iter != pr3.second; ++iter){
                if(iter->second == v){
                    cores_mp_c[update_degree[v]].erase(iter);
                    break;
                }
            }
        }
        auto pr4 = cores_mp_c[update_degree[u]].equal_range(nbr_order_old_c[u][update_degree[u]]);
        if(pr4.first != end(cores_mp_c[update_degree[u]]))
        {
            for (auto iter = pr4.first ; iter != pr4.second; ++iter){
                if(iter->second == u){
                    cores_mp_c[update_degree[u]].erase(iter);
                    break;
                }
            }
        }
        
        delete_update_nei1(add_c,add_f,all_c,all_f,u,v);
        delete_update_nei1(add_c,add_f,all_c,all_f,v,u);
    }
}

void Graph::delete_update_nei1(unordered_map<int,int> &add_c, unordered_map<int,int> &add_f, int all_c, int all_f, int u, int v){//不存在v->u
    multimap<float, int, greater<float>> single = nbr_mp_c[u];
    nbr_mp_c[u].clear();
    for(multimap<float, int, greater<float>>::iterator it = single.begin();it!=single.end();++it){
        if(it->second == v){
            continue;
        }
        if(add_c.find(it->second)!=add_c.end()){
            int old_sim = round(it->first*2*(pow((update_degree[u]+1)*update_degree[it->second],0.5)));
            float new_sim = (float)(old_sim-add_c[it->second])/(2*(pow(update_degree[u]*update_degree[it->second],0.5)));
            float old_ = it->first;
            update_nei_order_c(it->second, u, old_, new_sim);
            nbr_mp_c[u].insert(make_pair(new_sim, it->second));
            update_core_c(it->second, old_, new_sim);
        }else{
            int old_sim = round(it->first*2*(pow((update_degree[u]+1)*update_degree[it->second],0.5)));
            float new_sim = (float)(old_sim)/(2*(pow(update_degree[u]*update_degree[it->second],0.5)));
            float old_ = it->first;
            update_nei_order_c(it->second, u, old_, new_sim);
            nbr_mp_c[u].insert(make_pair(new_sim, it->second));
            update_core_c(it->second, old_, new_sim);
        }
    }
    nbr_order_old_c[u].pop_back();
    update_core_c(u, 0, 1);

    multimap<float, int, greater<float>> single2 = nbr_mp_f[u];
    nbr_mp_f[u].clear();
    for(multimap<float, int, greater<float>>::iterator it = single2.begin();it!=single2.end();++it){
        if(it->second == v){
            continue;
        }
        if(add_f.find(it->second)!=add_f.end()){
            int old_sim = round(it->first*2*(pow((update_degree[u]+1)*update_degree[it->second],0.5)));
            float new_sim = (float)(old_sim+add_f[it->second])/(2*(pow(update_degree[u]*update_degree[it->second],0.5)));
            float old_ = it->first;
            update_nei_order_f(it->second, u, it->first, new_sim);
            nbr_mp_f[u].insert(make_pair(new_sim, it->second));
            update_core_f(it->second, old_, new_sim);
        }else{
            int old_sim = round(it->first*2*(pow((update_degree[u]+1)*update_degree[it->second],0.5)));
            float new_sim = (float)(old_sim)/(2*(pow(update_degree[u]*update_degree[it->second],0.5)));
            float old_ = it->first;
            update_nei_order_f(it->second, u, it->first, new_sim);
            nbr_mp_f[u].insert(make_pair(new_sim, it->second));
            update_core_f(it->second, old_, new_sim);
        }
    }
    nbr_order_old_f[u].pop_back();
    update_core_f(u, 0, 1);
}
void Graph::delete_update_nei2(unordered_map<int,int> &add_c, unordered_map<int,int> &add_f, int all_c, int all_f, int u, int v){
    multimap<float, int, greater<float>> single = nbr_mp_c[u];
    nbr_mp_c[u].clear();
    for(multimap<float, int, greater<float>>::iterator it = single.begin();it!=single.end();++it){
        if(it->second == v){
            int old_sim = round(it->first*2*(pow((update_degree[u])*update_degree[it->second],0.5)));
            float new_sim = (float)(old_sim-all_c)/(2*(pow(update_degree[u]*update_degree[it->second],0.5)));
            nbr_mp_c[u].insert(make_pair(new_sim, it->second));
            continue;
        }
        if(add_c.find(it->second)!=add_c.end()){
            int old_sim = round(it->first*2*(pow((update_degree[u])*update_degree[it->second],0.5)));
            float new_sim = (float)(old_sim-add_c[it->second])/(2*(pow(update_degree[u]*update_degree[it->second],0.5)));
            float old_ = it->first;
            update_nei_order_c(it->second, u, it->first, new_sim);
            nbr_mp_c[u].insert(make_pair(new_sim, it->second));
            update_core_c(it->second, old_, new_sim);
        }else{
            nbr_mp_c[u].insert(make_pair(it->first, it->second));
        }
    }
    update_core_c(u, 0, 1);

    multimap<float, int, greater<float>> single2 = nbr_mp_f[u];
    nbr_mp_f[u].clear();
    for(multimap<float, int, greater<float>>::iterator it = single2.begin();it!=single2.end();++it){
        if(it->second == v){
            int old_sim = round(it->first*2*(pow((update_degree[u])*update_degree[it->second],0.5)));
            float new_sim = (float)(old_sim-all_f)/(2*(pow(update_degree[u]*update_degree[it->second],0.5)));
            nbr_mp_f[u].insert(make_pair(new_sim, it->second));
            continue;
        }
        if(add_f.find(it->second)!=add_f.end()){
            int old_sim = round(it->first*2*(pow((update_degree[u])*update_degree[it->second],0.5)));
            float new_sim = (float)(old_sim-add_f[it->second])/(2*(pow(update_degree[u]*update_degree[it->second],0.5)));
            float old_ = it->first;
            update_nei_order_f(it->second, u, it->first, new_sim);
            nbr_mp_f[u].insert(make_pair(new_sim, it->second));
            update_core_f(it->second, old_, new_sim);
        }else{
            nbr_mp_f[u].insert(make_pair(it->first, it->second));
        }
    }
    update_core_f(u, 0, 1);
}

void Graph::update_write(){
    ofstream degree_(str+"/index/degree.txt",ios::out); //创建待写入数据文件
    degree_<<(long)n<<" "<<(long)m<<" "<<(long)edge_m<<" "<<(long)max_degree;
    for(int i = 0; i< n;i++) degree_<<"\n"<<(long)update_degree[i];
    degree_.close();
    
    ofstream infile(str+"/degree.txt", ios::out);
    if (!infile.is_open()){
        cout<<"Open degree file failure"<<endl;
        exit(0);
    }
    infile<<n<<" "<<m;
    for(int i = 0; i<n;i++){
        infile<<"\n"<<(long)update_out_num[i]<<" "<<(long)update_in_num[i];
    }
    infile.close();
    
    ofstream write_in_edge(str+"/in_edges.txt", ios::out);
    write_in_edge<<m;
    for(int i = 0;i<n;i++){
        for(int j = 0;j<update_in_edges[i].size();j++){
            write_in_edge<<"\n"<<(long)update_in_edges[i][j];
        }
    }
    write_in_edge.close();
    
    ofstream write_out_edge(str+"/out_edges.txt", ios::out);
    write_out_edge<<m;
    for(int i = 0;i<n;i++){
        for(int j = 0;j<update_out_edges[i].size();j++){
            write_out_edge<<"\n"<<(long)update_out_edges[i][j];
        }
    }
    write_out_edge.close();
    
    
    ofstream fout2(str+"/index/nei_order_c.txt",ios::out); //创建待写入数据文件
    for(int i = 0; i< n-1;i++){
        for(multimap<float, int, greater<float>>::iterator it = nbr_mp_c[i].begin();it!=nbr_mp_c[i].end();++it){
            fout2<<(long)it->second<<" "<<it->first<<"\n";
        }
    }
    int nbr_mp_ci = update_degree[n-1];
    for(multimap<float, int, greater<float>>::iterator it = nbr_mp_c[n-1].begin();it!=nbr_mp_c[n-1].end();++it){
        if(nbr_mp_ci > 1)
            fout2<<(long)it->second<<" "<<it->first<<"\n";
        else
            fout2<<(long)it->second<<" "<<it->first;
        nbr_mp_ci--;
    }
    fout2.close();
    
    ofstream fout3(str+"/index/nei_order_f.txt",ios::out); //创建待写入数据文件
    for(int i = 0; i< n-1;i++){
        for(multimap<float, int, greater<float>>::iterator it = nbr_mp_f[i].begin();it!=nbr_mp_f[i].end();++it){
            fout2<<(long)it->second<<" "<<it->first<<"\n";
        }
    }
    int nbr_mp_fi = update_degree[n-1];
    for(multimap<float, int, greater<float>>::iterator it = nbr_mp_f[n-1].begin();it!=nbr_mp_f[n-1].end();++it){
        if(nbr_mp_fi > 1)
            fout2<<(long)it->second<<" "<<it->first<<"\n";
        else
            fout2<<(long)it->second<<" "<<it->first;
        nbr_mp_fi--;
    }
    fout3.close();
    
    ofstream fout4(str+"/index/core_order_c.txt",ios::out); //创建待写入数据文件
    for(int i = 0;i<max_degree-1;i++){
        fout4<<i+2<<" "<<update_max_degree_num[i]<<"\n";
        for(multimap<float, int, greater<float>>::iterator it = cores_mp_c[i].begin();it!=cores_mp_c[i].end();++it){
            fout4<<(long)it->second<<" "<<it->first<<"\n";
        }
    }
    fout4<<max_degree+1<<" "<<update_max_degree_num[max_degree-1]<<"\n";
    int cores_mp_ci = update_max_degree_num[max_degree-1];
    for(multimap<float, int, greater<float>>::iterator it = cores_mp_c[max_degree-1].begin();it!=cores_mp_c[max_degree-1].end();++it){
        if(cores_mp_ci > 1)
            fout4<<(long)it->second<<" "<<it->first<<"\n";
        else
            fout4<<(long)it->second<<" "<<it->first;
        cores_mp_ci--;
    }
    fout4.close();
    
    ofstream fout5(str+"/index/core_order_f.txt",ios::out); //创建待写入数据文件
    for(int i = 0;i<max_degree-1;i++){
        fout5<<i+2<<" "<<update_max_degree_num[i]<<"\n";
        for(multimap<float, int, greater<float>>::iterator it = cores_mp_f[i].begin();it!=cores_mp_f[i].end();++it){
            fout5<<(long)it->second<<" "<<it->first<<"\n";
        }
    }
    fout5<<max_degree+1<<" "<<update_max_degree_num[max_degree-1]<<"\n";
    int cores_mp_fi = update_max_degree_num[max_degree-1];
    for(multimap<float, int, greater<float>>::iterator it = cores_mp_f[max_degree-1].begin();it!=cores_mp_f[max_degree-1].end();++it){
        if(cores_mp_ci > 1)
            fout5<<(long)it->second<<" "<<it->first<<"\n";
        else
            fout5<<(long)it->second<<" "<<it->first;
        cores_mp_fi--;
    }
    fout5.close();
    
}



