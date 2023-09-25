#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <pthread.h>

using namespace std;

mutex mtx;

void func_increse(int& x){
    lock_guard<mutex> lck(mtx);
    for(int i=0;i<10000000;i++){
        x++;
    }
}

void func_decrease(int& x){
    lock_guard<mutex> lck(mtx);
    for(int i=0;i<10000000;i++){
        x--;
    }
}

int main(){
    vector<int> vt;
    for(int i=0;i<100;i++){
        int num=0;
        thread t1(func_increse,ref(num));
        thread t2(func_decrease,ref(num));
        t1.join();
        t2.join();
        vt.push_back(num);
    }
    for(auto i:vt){
        cout<<i<<" ";
    }
    return 0;
}