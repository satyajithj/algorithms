/*
	author: Satyajith
	algorithm: merge sort

	complexity: O(n log(n))
*/
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

#define DEBUG cout << "DEBUG" << endl
#define NEWLINE cout << endl

void merge_sort(vector<int> *, int, int);
void merge(vector<int>*, int, int);

int main(int argc, char* argv[]) {

	int arr[] = {21, 3,8,2,13,1,9,4,7,6, 5,11,18};
	// int arr[] = {6, 7, 1, 2, 3, 8, 5, 4};
	vector<int> *vec = new vector<int> (arr, arr + sizeof(arr)/sizeof(int));
	ostream_iterator<int> output(cout, " ");

	copy(vec->begin(), vec->end(), output);
	NEWLINE;
	merge_sort(vec, 0, vec->size());		// call to merge sort
	NEWLINE;
	copy(vec->begin(), vec->end(), output);
	
	NEWLINE;
	return 0;
}

void merge_sort(vector<int> *x, int s, int e) {

	int size = (e-s);
	cout << s << " " << e << " " << size << endl;

	// base case
	if (size <= 2) {
		if ((*x)[e-1] < (*x)[s])
			swap((*x)[s], (*x)[e-1]);
		return;
	}

	merge_sort(x, s, (e+s)/2);
	merge_sort(x, (e+s)/2, e);
	merge(x, s, e);
}

void merge(vector<int>* x, int s, int e) {

	vector<int> A(x->begin()+s, x->begin()+(e+s)/2);
	vector<int> B(x->begin()+(e+s)/2, x->begin()+e);

	int i, j, k;
	i = j = 0;
	k = s;

	while (i != A.size() && j != B.size()) {
		if (A[i] <= B[j])
			(*x)[k++] = A[i++];
		else
			(*x)[k++] = B[j++];
	}

	if (i == A.size())
		while (j != B.size())
			(*x)[k++] = B[j++];
	if (j == B.size())
		while (i != A.size())
			(*x)[k++] = A[i++];
}
