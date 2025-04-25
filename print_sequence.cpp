// Print Numbers in Sequence

// Multiple threads print numbers in a specific order (e.g., Thread 1 prints 1, Thread 2 prints 2, etc., in a loop).

// Variation: Print 1, 2, 3, 1, 2, 3, ... using 3 threads.


#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;

int maximum=10;
mutex m;
condition_variable cv;
int count=1;
void fun(int id){
    for(int i=0;i<maximum;i++){
        unique_lock<mutex> locker(m);
        cv.wait(locker,[id]() {
            return count % 3 == id % 3; 
        });
        cout<< id<<":"<<count<<endl;
        count++;;
        locker.unlock();
        cv.notify_all();
    }
}
int main(){
    thread t1(fun,1);
    thread t2(fun,2);
    thread t3(fun,3);
    t1.join();
    t2.join();
    t3.join();
    cout<<"All threads finished execution."<<endl;
    return 0;
}



// PS C:\Users\HP\Documents\C++\projects\helloworld\Multithreading_Problems> g++ print_sequence.cpp -o print_sequence    
// PS C:\Users\HP\Documents\C++\projects\helloworld\Multithreading_Problems> ./print_sequence.exe
// 1:1
// 2:2
// 3:3
// 1:4
// 2:5
// 3:6
// 1:7
// 2:8
// 3:9
// 1:10
// 2:11
// 3:12
// 1:13
// 2:14
// 3:15
// 1:16
// 2:17
// 3:18
// 1:19
// 2:20
// 3:21
// 1:22
// 2:23
// 3:24
// 1:25
// 2:26
// 3:27
// 1:28
// 2:29
// 3:30
// All threads finished execution.