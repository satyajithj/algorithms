/*
	author: Satyajith
	algorithm: selection sort

	complexity: O(n^2), worst, best, average
*/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

#define DEBUG cout << "DEBUG" << endl
#define NEWLINE cout << endl

void selection_sort(vector<int>*);

int main(int argc, char* argv[]) {


	int arr[] = {21, 3, 8, 2, 13, 67, 1, 9, 4, 7, 6, 5};

	vector<int> *vec = new vector<int> (arr, arr + sizeof(arr)/sizeof(int));
	ostream_iterator<int> output(cout, " ");

	copy(vec->begin(), vec->end(), output);
	selection_sort(vec);							// call to selection sort
	NEWLINE;
	copy(vec->begin(), vec->end(), output);
	
	NEWLINE;
	return 0;
}

void selection_sort(vector<int> *x) {

	int min_index;
	for (int i = 0 ; i < x->size(); i++) {
		min_index = i;
		for (int j = i+1; j < x->size(); j++)
			if ((*x)[j] < (*x)[min_index])
				min_index = j;
		
		swap((*x)[min_index], (*x)[i]);
	}
}