#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <map>
#include <string>

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

//1. Commonly used functions in C++:
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



//2. smart pointers:
		//a. unique_ptr:
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

		//b. shared_ptr:
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

		//c. weak_ptr:
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



//3. lambda functions:
		//a. basic syntax: 
	// [capture-list] (parameters) mutable(optional) ->(optional) return_type(optional) {function body}
	// simple example:
	std::vector<int> nums{ 1, 2, 3, 4, 5 };
	std::for_each(nums.begin(), nums.end(), [](int& n) 
		{
			n += 10;
		});
	std::for_each(nums.begin(), nums.end(), [](int n) 
		{
		std::cout << n << " ";
		});

		//b. capture list: 
	// [] (no capture)
	// [=] (capture all by value): the lambda function can access all the outside variables in the scope as a copy (only able to read, if change it, only the copy will be change which won't affect the outside variable)
	int x = 10;
	auto f = [=]() { x + 10; };	//auto represent the type of the lambda function which can't explicitly specify in compiler
	std::cout << "\nthe value of x is " << x << endl;	//10
	// [&] (capture all by reference): the lambda function can access all the outside variables in the scope by reference (able to read and write)
	// explicitly capture: [x] (capture x by value), [&x] (capture x by reference), [&, x] (capture all by reference except x by value), [=, &x] (capture all by value except x by reference), [a, &b] (capture a by value and b by reference)
	// [this] (capture the elements of the object that the lambda function is a member of (when using = or &, it's this by default) )
	
		//c. mutable:
	// by default, the lambda function capture by value can't change the copy of the outside variables, if you want to change it, add "mutable" keyword
	int y = 10;
	auto f2 = [=]() mutable 
		{ 
			y ++;
			std::cout << "The value of y in the lambda is " << y << endl;	//11
		};
	f2();
	std::cout << "The value of y is " << y << endl;	//10
		
		//d. return type:
	// by default, the return type is deduced by the compiler, if you want to specify the return type, add "-> return_type"

		//e. convert to function pointer:
	// a non-capturing lambda function (empty capture list: []) can be converted to a function pointer:
	auto f3 = [](int x, int y) { return x + y; };
	int(*funcPtr)(int, int) = f3;
	std::cout << "The result of the function pointer is " << funcPtr(10, 20) << endl;
	// a capturing lambda function is a "closure object", can't be converted to a function pointer
	// It stores the copy or reference of the outside variables, make it able to be capture by outside
	int base = 10;
	function<int(int)> addBase = [base](int x) { return base + x; };
	std::cout << "The result of the closure object is " << addBase(20) << endl;	//30
	
		//f. pass lambda as a parameter:
	// following above, it can be passed as a parameter to another function
	auto add = [](int x, int y) { return x + y; };
	auto multiply = [](int x, int y) { return x * y; };
	auto calculate = [](int x, int y, function<int(int, int)> func) { return func(x, y); };
	std::cout << "The result of the calculate function is " << calculate(10, 20, add) << endl;	//30
	std::cout << "The result of the calculate function is " << calculate(10, 20, multiply) << endl;	//200



//4. Vectors (why using one instead of another):
		//a. vector:
	// a dynamic array, can be resized, the elements are stored in contiguous memory
	// when the size of the vector is changed, the memory is reallocated, the old elements are copied to the new memory area
	// so when insert or delete elements in the vector, the pointer/reference to the elements may be changed. However, the pointer to the vector itself won't be changed
	vector<int> vec1;
	vec1.push_back(10);	//add an element to the end of the vector
	vec1.pop_back();	//remove the last element
	vec1.size();	//get the size of the vector
	vec1.empty();	//check if the vector is empty
	vec1.clear();	//remove all the elements
	vec1.erase(vec1.begin() + 1);	//remove the element at the position 1
	vec1.insert(vec1.begin() + 1, 100);	//insert an element at the position 1
	vec1.resize(10);	//resize the vector to 10 elements
	vec1.crbegin();	//get the reverse iterator to the beginning of the vector
	vec1.crend();	//get the reverse iterator to the end of the vector
	// when to use: when the size of the array is unknown or need to be changed, when the elements need to be added or removed frequently
		//b. array:
	// a fixed-size array, the size is determined at compile time, the elements are stored in contiguous memory
	// when the size of the array is changed, the memory is reallocated, the old elements are copied to the new memory area
	// so when insert or delete elements in the array, the pointer/reference to the elements may be changed. However, the pointer to the array itself won't be changed
	// when to use: when the size of the array is known and fixed, when the elements need to be accessed frequently
		//c. list:
	// a doubly linked list, the elements are stored in non-contiguous memory
	// when insert or delete elements in the list, the pointer/reference to the elements won't be changed
	// so when the size of the list is changed, the memory is not reallocated, the old elements are not copied to the new memory area
	// when to use: when the elements need to be added or removed frequently, when the elements need to be accessed randomly
		//e. map (it's like dictionary in other languages):
	// a key-value pair, the elements are stored in a tree structure
	// all keys are stored in order, the elements are sorted by the key
	// all keys are unique, the elements are sorted by the key
	// when to use: when the elements need to be accessed by key, when the elements need to be sorted by key
	map<string, string> map1;
	map1["key1"] = "value1";	//if "key1" doesn't exist, it will be created, and the value is "value1"
	map1["key2"] = "value2";
	auto result = map1.insert(make_pair("key3", "value3"));	//insert a key-value pair
	//the return value of the insert method is a pair, the first element is an iterator to the inserted element, the second element is a bool value to indicate if the insertion is successful:
	cout << "The value successfully insert? " << result.second << endl;
	//using iterator to access the elements in the map:
	for (auto it = map1.begin(); it != map1.end(); ++it) 
	{
		std::cout << it->first << ": " << it->second << "\n";
	}
	//using buffer to access the elements in the map:
	cout << "The value of key1 is " << map1["key1"] << endl;
	//find & delete:
	auto itFind = map1.find("key1");
	if (itFind != map1.end())
	{
		cout << "found the key1: " << itFind->second << endl;
		map1.erase(itFind);	//delete the found pair in the map
	}
		//f. unordered_map:
	// a key-value pair, the elements are stored in a hash table
	// all keys are stored in random order, the elements are not sorted by the key



//5. Concurrency:
		//a. Threads:
	int passingValue = 10;
	thread threadName(aFunction, passingValue);	//creat a thread
	std::cout << "Main thread is running!" << endl;	//the work in main thread
	threadName.join();	//let the main thread wait until the thread is finished

		//b. task-level Concurrency:
	future<int> result = async(launch::async, compute);	//creat a task
	std::cout << "Main thread is running!" << endl;	//the work in main thread
	int value = result.get();	//get the result of the task
	std::cout << "The result is: " << value << endl;

		//c. synchronization & mutual exclusion (to avoid "race condition" when multiple threads need to access one data at a same time):
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