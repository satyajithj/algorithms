/*
	author: Satyajith
	algorithm: merge sort

	complexity: 
*/
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

#define DEBUG cout << "DEBUG" << endl
#define NEWLINE cout << endl

void merge_sort(vector<int> *, 
	vector<int>::iterator, 
	vector<int>::iterator);

int main(int argc, char* argv[]) {

	int arr[] = {21, 3,8,2,13,1,9,4,7,6, 5,11,18};
	vector<int> *vec = new vector<int> (arr, arr + sizeof(arr)/sizeof(int));
	ostream_iterator<int> output(cout, " ");

	copy(vec->begin(), vec->end(), output);
	merge_sort(vec, vec->begin(), vec->end());		// call to merge sort
	NEWLINE;
	copy(vec->begin(), vec->end(), output);
	
	NEWLINE;
	return 0;
}

void merge_sort(vector<int> *x, 
	vector<int>::iterator start, 
	vector<int>::iterator end) {

	int size = (end - start);

	// base case
	if (size < 2) {
		if (*start < *end)
			swap(*start, *end);
	}	
}