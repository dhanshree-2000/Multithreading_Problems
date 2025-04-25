// Print Even and Odd Numbers Alternately

// Thread 1 prints even numbers, Thread 2 prints odd numbers in order.

#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;
condition_variable cv;
mutex m;
int count=0;
void even_odd(int id){
    for(int i=0;i<10;i++){
        unique_lock<mutex> locker(m);
        cv.wait(locker,[id]() {
            return count % 2 == id % 2; 
        });
        cout<< id<<":"<<count<<endl;
        count++;
        locker.unlock();
        cv.notify_all();
    }
}
int main(){
    thread t1(even_odd,0);
    thread t2(even_odd,1);
    t1.join();
    t2.join();
    cout<<"All threads finished execution."<<endl;
    return 0;
}



// PS C:\Users\HP\Documents\C++\projects\helloworld\Multithreading_Problems> g++ print_even_odd.cpp -o print_even_odd
// PS C:\Users\HP\Documents\C++\projects\helloworld\Multithreading_Problems> ./print_even_odd.exe
// 0:0
// 1:1
// 0:2
// 1:3
// 0:4
// 1:5
// 0:6
// 1:7
// 0:8
// 1:9
// 0:10
// 1:11
// 0:12
// 1:13
// 0:14
// 1:15
// 0:16
// 1:17
// 0:18
// 1:19
// All threads finished execution.