#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>

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


	//smart pointers:
//1. unique_ptr:
	/* only one unique pointer point to one particular memory area*/
	auto test = []()
	{
		unique_ptr <int> ptr1 = make_unique<int>(10);	//creat a unique pointer
		std::cout << "The unique pointer is created! Value is " << *ptr1 << endl;

		//unable to copy the unique pointer, but can move it
		std::unique_ptr<int> ptr2 = std::move(ptr1);
		std::cout << "The unique pointer Has been moved! Value is " << *ptr2 << endl;
	};
	test();
	//when the scope of the unique pointer ends, the memory is automatically released (delete the pointer)
	//It's deleter can be customized by passing a lambda function to the unique_ptr constructor

//2. shared_ptr:
	//when to use: when a heap-allocated object is shared among multiple objects
	//shared_ptr keeps a reference count counting how many share_ptr pointing to it, when the reference count is 0, the memory is released
	shared_ptr<float> ptrPI = make_shared<float>(3.1415926);
	cout << "Now there are " << ptrPI.use_count() << " share pointers points to this" << endl;	//get the reference count
	{
		shared_ptr<float> ptrPI2 = ptrPI;
		//the share pointer they share the same memory area and same control block:
		cout << "Now there are " << ptrPI2.use_count() << " share pointers points to this" << endl;	//2
		cout << "Now there are " << ptrPI.use_count() << " share pointers points to this" << endl;	//2
	}
	//when out of the scope, the reference count is 1, ptrPI2 is released
	cout << "Now there are " << ptrPI.use_count() << " share pointers points to this" << endl;	//1
	//deleter can be customized

//3. weak_ptr:
	//use with shared_ptr, it Won't increase the reference count, it doesn't own the object and doesn't have a deleter, only an observer
	//when to use: to avoid circular reference/ reference cycle (two objects using share_ptr to point to each other, the reference count will never be 0)
	//weak_ptr doesn't control the lifetime of the object, it only keeps a pointer to the object which is managed by the shared_ptr
	//it's expired() method can be used to check if the object is still alive. if so, the weak_ptr is expired
	shared_ptr <int> sp1 = make_shared<int>(1000);
	weak_ptr<int> wp = sp1;
	cout << "The weak pointer is expired? " << wp.expired() << endl;	//0
	//using lock() to get a shared_ptr from a weak_ptr
	shared_ptr<int> sp2 = wp.lock();
	cout << "Now there are " << sp1.use_count() << " share pointers points to sp1" << endl;	//2
	sp1.reset();	//release the object

	//lambda functions:



	//Vectors (why using one instead of another):



	//Concurrency:
//1. Threads:
	int passingValue = 10;
	thread threadName(aFunction, passingValue);	//creat a thread
	std::cout << "Main thread is running!" << endl;	//the work in main thread
	threadName.join();	//let the main thread wait until the thread is finished

//2. task-level Concurrency:
	future<int> result = async(launch::async, compute);	//creat a task
	std::cout << "Main thread is running!" << endl;	//the work in main thread
	int value = result.get();	//get the result of the task
	std::cout << "The result is: " << value << endl;

//3. synchronization & mutual exclusion (to avoid "race condition" when multiple threads need to access one data at a same time):
	thread thread1(aFunctionWithMutex);
	thread thread2(aFunctionWithMutex);	//lock the globalVariableA, ensure that only one thread can access the critical section at a time
	thread1.join();
	thread2.join();
	std::cout << "The global variable is: " << globalVariableA << endl;

	return 0;
}

void aFunction(int x)
{
	std::cout << "a function is running! Passed with a value " << x << endl;
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