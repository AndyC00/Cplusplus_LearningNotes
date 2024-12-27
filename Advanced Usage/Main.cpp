#include <iostream>
#include <cstdlib>

//Concurrency library:
#include <thread>
#include <future>
#include <mutex>

using namespace std;

void aFunction(int x);
int compute();
void aFunctionWithMutex();

int globalVariableA = 0;
mutex mtx;	//creat a mutex object to lock the critical section

int main()
{
		//Commonly used functions in C++:
	/*
	cout, cin, endl, cerr (print error info)
	string: size(), length(), find(), empty(), replace(), c_str()
	cmath: sqrt(), pow(), sin(), cos(), tan()
	algorithm: sort(begin, end), reverse(), find(), count(), for_each(), transform()
	vector: push_back(), pop_back(), size(), empty(), clear(), erase(), insert(), resize()
	chrono (time and date): sleep_for(), duration, time_point
	thread: thread, async, launch, future, mutex, lock_guard, unique_lock, condition_variable
	memory: delete, new, shared_ptr, unique_ptr, weak_ptr
	*/

	//unique_ptr:

	//shared_ptr:

	//smart pointers:

	//weak_ptr:

	//lambda functions:

	//Vectors (why using one instead of another):

		//Concurrency:
	//1. Threads:
	int passingValue = 10;
	thread threadName(aFunction, passingValue);	//creat a thread
	cout << "Main thread is running!" << endl;	//the work in main thread
	threadName.join();	//let the main thread wait until the thread is finished

	//2. task-level Concurrency:
	future<int> result = async(launch::async, compute);	//creat a task
	cout << "Main thread is running!" << endl;	//the work in main thread
	int value = result.get();	//get the result of the task
	cout << "The result is: " << value << endl;

	//3. synchronization & mutual exclusion (to avoid "race condition" when multiple threads need to access one data at a same time):
	thread thread1(aFunctionWithMutex);
	thread thread2(aFunctionWithMutex);	//lock the globalVariableA, ensure that only one thread can access the critical section at a time
	thread1.join();
	thread2.join();
	cout << "The global variable is: " << globalVariableA << endl;

	return 0;
}

void aFunction(int x)
{
	cout << "a function is running! Passed with a value " << x << endl;
}

int compute()
{
	this_thread::sleep_for(chrono::seconds(1));
	return 1000;
}

void aFunctionWithMutex()
{
	for (int i = 0; i < 100; i++)
	{
		lock_guard<mutex> guard(mtx);	//locked, only threads with the lock can access the critical section
		globalVariableA++;
		//when the scope of the lock_guard object ends, the lock is released
	}
}