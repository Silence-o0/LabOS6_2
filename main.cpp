#include <iostream>
#include <thread>
#include <barrier>

using namespace std;

int shared_variable = 0;
barrier sync_point(2);

void thread_function() {
    for (int i = 0; i < 1000; ++i) {
        int copy = shared_variable;
        sync_point.arrive_and_wait();
        shared_variable = copy + 1;
        sync_point.arrive_and_wait();
    }
}

int main() {
    thread t1(thread_function);
    thread t2(thread_function);

    t1.join();
    t2.join();

    cout << "Shared variable: " << shared_variable << endl;

    return 0;
}







