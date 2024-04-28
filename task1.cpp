#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;
int shared_variable = 0;

void thread_function() {
    for (int i = 0; i < 1000000000; ++i) {
        mtx.lock();
        ++shared_variable;
        mtx.unlock();
    }
}

int main() {
    thread t1(thread_function);
    thread t2(thread_function);
    auto start_time = chrono::high_resolution_clock::now();

    t1.join();
    t2.join();

    auto end_time = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();

    cout << "Shared variable: " << shared_variable << endl;
    cout << "time: " << time << endl;
    return 0;
}