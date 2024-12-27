#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
#include <ctime>
#include <stack>

using namespace std;

int main()
{
	//vec:
	std::vector <int> array1 = {8,11,1,3,4,5,7,9,12};

	cout << "The elements in the arrays are ";
	for (int i = 0; i < array1.size(); i++)
	{
		cout << array1[i] << "\t";
	}

	//seal vec in stack:
	std::stack<int, std::vector<int>> stack1(array1);
	//using stack:
	cout << "\nCurrent top element is: " << stack1.top() << endl;
	stack1.pop();
	stack1.push(99);
	cout << "Now top element is: " << stack1.top() << endl;
	cout << stack1.size() << "elements\nbits:" << sizeof(stack1) << endl;
	std::stack<int,std::vector<int>> stack2 = stack1;
	while (!stack2.empty())
	{
		std::cout << stack2.top() << " ";
		stack2.pop();
	}

	//using queue:
	std::queue<int> queue1; // using default container std::deque while using vector will report error (not support front().)
	for (int num : array1) 
	{
		queue1.push(num);
	}
	queue1.push(100);
	queue1.pop();
	std::queue<int> queue2 = queue1;
	while (!queue2.empty()) 
	{
		std::cout << queue2.front() << " ";
		queue2.pop();
	}

	//sort:
	sort(array1.begin(),array1.end());
	cout << "\nSorted elements: ";
	for (int i = 0; i < array1.size(); i++)
	{
		cout << array1[i] << " ";
	}

	//shuffle:
	std::default_random_engine engine(std::time(0));
	std::shuffle(array1.begin(), array1.end(), engine);
	cout << "\nShuffled elements: ";
	for (int i = 0; i < array1.size(); i++)
	{
		cout << array1[i] << " ";
	}

	char input;
	cin >> input;
	return 0;
}