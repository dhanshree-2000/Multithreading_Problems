#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<deque>
using namespace std;

deque<int> buffer;
int maxsize=5;
mutex m;
condition_variable cv;
void producer(int value){
    while(value){
        unique_lock<mutex> locker(m);
        cv.wait(locker,[](){return buffer.size()<maxsize;});
        buffer.push_back(value);
        cout<<"Produced: "<<value<<endl;
        locker.unlock();
        cv.notify_all();
        value--;
        }
}

void consumer(){
    while(true){
        unique_lock<mutex> locker(m);
        cv.wait(locker,[](){return !buffer.empty();});
        int value=buffer.front();
        buffer.pop_front();
        cout<<"Consumed: "<<value<<endl;
        locker.unlock();
        cv.notify_all();
    }
}

int main(){
    thread t1(producer,10);
    thread t2(consumer);

    t1.join();
    t2.join();
    return 0;
    }