/**
 * 	author: satyajith
 * 	program: compute the longest monotonically increasing (LMI)
 * 	subsequence Z for the input sequence X -> quadratic run-time
 * 	(hint: perform LCS on X and sorted(X))
 */

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

void compute_LCS(vector< unsigned int > &, vector< unsigned int > &);
void print_LCS(vector< unsigned int > &, vector< unsigned int > &,
			   vector< vector< unsigned int > > &, size_t, size_t);

int main(int argc, char const *argv[]) {
	vector< unsigned int > X({9, 2, 5, 3, 7, 11, 8, 10, 13, 6});
	vector< unsigned int > sX(X.begin(), X.end());
	sort(sX.begin(), sX.end());	// sorted sequence

	X.insert(X.begin(), UINT_MAX);	// for simplifying computation
	sX.insert(sX.begin(), UINT_MAX);

	compute_LCS(X, sX);
	return 0;
}

// print the LCS - recursive
void print_LCS(vector< unsigned int > &X, vector< unsigned int > &sX,
			   vector< vector< unsigned int > > &len, size_t i, size_t j) {
	// base case
	if (i == 0 || j == 0)
		return;

	if (X[ i ] == sX[ j ]) {
		print_LCS(X, sX, len, i - 1, j - 1);
		cout << X[ i ] << " ";
	} else if (len[ i - 1 ][ j ] >= len[ i ][ j - 1 ]) {
		print_LCS(X, sX, len, i - 1, j);
	} else {
		print_LCS(X, sX, len, i, j - 1);
	}
}

// determine the LMI subsequence of X
void compute_LCS(vector< unsigned int > &X, vector< unsigned int > &sX) {
	int m = X.size();
	size_t i, j;
	vector< vector< unsigned int > > len(m);

	for (i = 0; i < m; ++i)
		len[ i ].reserve(m);

	for (i = 0; i < m; ++i)
		len[ i ][ 0 ] = len[ 0 ][ i ] = 0;

	for (i = 1; i < m; ++i) {
		for (j = 1; j < m; ++j)
			if (X[ i ] == sX[ j ])
				len[ i ][ j ] = len[ i - 1 ][ j - 1 ] + 1;
			else if (len[ i - 1 ][ j ] >= len[ i ][ j - 1 ])
				len[ i ][ j ] = len[ i - 1 ][ j ];
			else
				len[ i ][ j ] = len[ i ][ j - 1 ];
	}

	cout << "> length of LCS of given sequences: " << len[ m - 1 ][ m - 1 ] << endl;
	cout << "> longest common subsequence: ";
	print_LCS(X, sX, len, m - 1, m - 1);
}