/*
	author: Satyajith
	algorithm: insertion sort

	complexity: O(n^2), worst, average
*/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

#define DEBUG cout << "DEBUG" << endl
#define NEWLINE cout << endl

void insertion_sort(vector<int>*);

int main(int argc, char* argv[]) {


	int arr[] = {21, 3, 8, 2, 13, 67, 1, 9, 4, 7, 6, 5};

	vector<int> *vec = new vector<int> (arr, arr + sizeof(arr)/sizeof(int));
	ostream_iterator<int> output(cout, " ");

	copy(vec->begin(), vec->end(), output);
	insertion_sort(vec);							// call to insertion sort
	NEWLINE;
	copy(vec->begin(), vec->end(), output);
	
	NEWLINE;
	return 0;
}

void insertion_sort(vector<int> *x) {

	int j, key = -1;
	for (int i = 1 ; i < x->size(); i++) {
		for (j = i - 1, key = (*x)[i]; j >= 0; j--)
			if ((*x)[j] > key)
				(*x)[j+1] = (*x)[j];
			else
				break;
		(*x)[j+1] = key;
	}
}