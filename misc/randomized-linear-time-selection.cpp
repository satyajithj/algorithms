/*
	author: satyajith
	algorithm: randomized linear time selection,
			   kth order statistic

	complexity: O (n)
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

int select_k(vector<int> *, int ,int, int k);

int main(int argc, char* argv[]) {

	srand(time(NULL));

	int k = 11;

	int arr[] = {21,3,8,2,13,64,1,9,4,7,6, 5,11,18};
	// int arr[] = {3,8,2,1,4,7,6,5};
	// int arr[] = {3, 2};
	vector<int> *vec = new vector<int> (arr, arr + sizeof(arr)/sizeof(int));
	ostream_iterator<int> output(cout, " ");

	copy(vec->begin(), vec->end(), output);
	NEWLINE;
	cout << "kth smallest is: " << select_k(vec, 0, vec->size(), k);

	NEWLINE;
	return 0;
}

int select_k(vector<int> *x, int s, int e, int k) {

	int size = e-s;
	// base case
	if (size <= 2) {
		if((*x)[e-1] < (*x)[s] && size > 0)
			swap((*x)[e-1], (*x)[s]);

		if (k == e)
			return (*x)[e-1];
		return (*x)[s];
	}

	int i,j;
	// random pivot
	swap((*x)[s + rand() % size], (*x)[s]);
	for (i = s+1, j = i; i < e; i++)
		if ((*x)[i] < (*x)[s])
			swap((*x)[i], (*x)[j++]);
	swap((*x)[j-1], (*x)[s]);

	if (j == k)
		return (*x)[j-1];
	if (k < j)
		return select_k(x, s, j, k);

	return select_k(x, j, e, k);
}