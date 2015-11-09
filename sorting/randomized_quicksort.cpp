#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

#include <stdlib.h>
#include <time.h>

using namespace std;

#define DEBUG cout << "DEBUG" << endl
#define NEWLINE cout << endl

void quick_sort(vector<int>, 
	vector<int>::iterator, 
	vector<int>::iterator);

int main(int argc, char* argv[]) {

	srand(time(NULL));

	int arr[] = {21, 3,8,2,13,1,9,4,7,6, 5,11,18};
	vector<int> vec(arr, arr + sizeof(arr)/sizeof(int));
	ostream_iterator<int> output(cout, " ");

	copy(vec.begin(), vec.end(), output);
	quick_sort(vec, vec.begin(), vec.end());
	NEWLINE;
	copy(vec.begin(), vec.end(), output);
	
	NEWLINE;
	return 0;
}

void quick_sort(vector<int> x, 
	vector<int>::iterator start, 
	vector<int>::iterator end) {

	int size = end - start;
	if (size <= 2) {
		if(*(end - 1) < *start && size > 0)
			swap(*(end - 1), *start);
		return;
	}

	swap(*(start + rand() % size), *(start));
	vector<int>::iterator i = start;
	vector<int>::iterator j = i + 1;

	for ( ; i != end; i++)
		if (*i < *start)
			swap(*i, *start);

	swap(*(j-1), *start);

	quick_sort(x, start, j-1);	// left partition
	quick_sort(x, j, end);	// right partition
}