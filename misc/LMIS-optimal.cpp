/**
 * 	author: satyajith
 *
 * 	program: compute the longest monotonically increasing (LMI)
 * 	subsequence Z for the input sequence X -> O (n lg(n))
 */

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

void compute_lmis(vector< int > &);
void print_lmis(vector< int > &, vector< int > &, int);

int main(int argc, char const *argv[]) {
	vector< int > X({9, 2, 5, 3, 7, 11, 8, 10, 13, 6});
	compute_lmis(X);
	return 0;
}

// recursive routine to print the LMIS of X
void print_lmis(vector< int > &X, vector< int > &P, int l) {
	if (l == 0)
		return;

	print_lmis(X, P, P[ l ]);
	cout << X[ l ] << ", ";
}

// O(n lg(n)) routine
void compute_lmis(vector< int > &X) {
	int n = X.size();
	vector< int > M(n + 1, 0);
	vector< int > P(n, 0);	// preceeding index

	int low, high, mid, L, newL, i;

	L = 0;	// length of longest increasing subsequence
	for (i = 0; i < n; i++) {
		low = 1;
		high = L;

		// this binary separation routine quickly checks whether
		// we have a new subsequence of longer or shorter length
		// than L
		while (low <= high) {
			mid = ceil((low + high) / 2);
			if (X[ M[ mid ] ] < X[ i ])
				low = mid + 1;
			else
				high = mid - 1;
		}

		newL = low;	// X[i] belongs to an increasing subsequence of length 'low'

		P[ i ] = M[ newL - 1 ];
		M[ newL ] = i;

		// update length of LMIS ascertained so far
		if (newL > L)
			L = newL;
	}

	cout << "> length of LMI subsequence: " << L << endl;
	cout << "> LMI: ";
	print_lmis(X, P, M[ L ]);	// start with index at LMIS of length L
}