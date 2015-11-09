/*
	author: Satyajith
	algorithm: randomized quick sort

	complexity: O (n log(n)), average case performance
				O (n^2), worst case
*/
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

#include <stdlib.h>
#include <time.h>

using namespace std;

#define DEBUG cout << "DEBUG" << endl
#define NEWLINE cout << endl

void quick_sort(vector<int> *, 
	int ,int );

int main(int argc, char* argv[]) {

	srand(time(NULL));

	int arr[] = {21,3,8,2,13,64,1,9,4,7,6, 5,11,18};
	// int arr[] = {3,8,2,1,4,7,6,5};
	vector<int> *vec = new vector<int> (arr, arr + sizeof(arr)/sizeof(int));
	ostream_iterator<int> output(cout, " ");

	copy(vec->begin(), vec->end(), output);
	quick_sort(vec, 0, vec->size());
	NEWLINE;
	copy(vec->begin(), vec->end(), output);
	
	NEWLINE;
	return 0;
}

void quick_sort(vector<int> *x, int s, int e) {

	int size = e-s;
	// base case
	if (size-1 < 2) {
		if((*x)[e-1] < (*x)[s] && size > 0)
			swap((*x)[e-1], (*x)[s]);
		return;
	}

	// random pivot
	swap((*x)[s + rand() % size], (*x)[s]);

	int i,j;
	for (i = s+1, j = i; i < e; i++)
		if ((*x)[i] < (*x)[s])
			swap((*x)[i], (*x)[j++]);

	swap((*x)[j-1], (*x)[s]);

	quick_sort(x, s, j-1);
	quick_sort(x, j, e);	// right partition
}