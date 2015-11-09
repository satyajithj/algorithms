/*
	author: Satyajith
	algorithm: bubble sort

	complexity: O(n^2), worst, average
				O(n), best (when already sorted)
*/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

#define DEBUG cout << "DEBUG" << endl
#define NEWLINE cout << endl

void bubble_sort(vector<int>*);

int main(int argc, char* argv[]) {


	int arr[] = {21, 3, 8, 2, 13, 67, 1, 9, 4, 7, 6, 5};

	vector<int> *vec = new vector<int> (arr, arr + sizeof(arr)/sizeof(int));
	ostream_iterator<int> output(cout, " ");

	copy(vec->begin(), vec->end(), output);
	bubble_sort(vec);							// call to bubble sort
	NEWLINE;
	copy(vec->begin(), vec->end(), output);
	
	NEWLINE;
	return 0;
}

void bubble_sort(vector<int> *x) {

	for (int i = 0 ; i < x->size() - 1; i++) {
		for (int j = 0; j < (x->size() - 1 - i); j++)
			if ((*x)[j + 1] < (*x)[j])
				swap((*x)[j], (*x)[j + 1]);
	}
}