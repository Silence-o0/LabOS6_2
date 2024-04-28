#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

atomic<int> shared_variable(0);

void thread_function() {
    for (int i = 0; i < 1000000000; ++i) {
        shared_variable.fetch_add(1);
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

    cout << "Shared variable: " << shared_variable.load() << endl;
    cout << "time: " << time << endl;
    return 0;
}