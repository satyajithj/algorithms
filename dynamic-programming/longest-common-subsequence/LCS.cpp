/**
 * 	author: satyajith
 * 	program: compute the longest common subsequence Z of two
 * 	input sequences X and Y (dynamic programming; bottom-up)
 */

#include <iostream>
#include <vector>

using namespace std;

void compute_LCS(vector< char > &, vector< char > &);
void print_LCS(vector< char > &, vector< char > &, vector< vector< unsigned int > > &,
			   size_t, size_t);

int main(int argc, char const *argv[]) {
	vector< char > S1({'\0', 'A', 'C', 'C', 'G', 'G', 'T', 'C', 'G', 'A',
					   'G',  'T', 'G', 'C', 'G', 'C', 'G', 'G', 'A', 'A',
					   'G',  'C', 'C', 'G', 'G', 'C', 'C', 'G', 'A', 'A'});

	vector< char > S2({'\0', 'G', 'T', 'C', 'G', 'T', 'T', 'C', 'G', 'G',
					   'A',  'A', 'T', 'G', 'C', 'C', 'G', 'T', 'T', 'G',
					   'C',  'T', 'C', 'T', 'G', 'T', 'A', 'A', 'A'});

	compute_LCS(S1, S2);	// solution is 'GTCGTCGGAAGCCGGCCGAA'
	return 0;
}

// print the LCS - recursive
void print_LCS(vector< char > &X, vector< char > &Y,
			   vector< vector< unsigned int > > &len, size_t i, size_t j) {
	// base case
	if (i == 0 || j == 0)
		return;

	if (X[ i ] == Y[ j ]) {
		print_LCS(X, Y, len, i - 1, j - 1);
		cout << X[ i ];
	} else if (len[ i - 1 ][ j ] >= len[ i ][ j - 1 ]) {
		print_LCS(X, Y, len, i - 1, j);
	} else {
		print_LCS(X, Y, len, i, j - 1);
	}
}

// determine the LCS of X and Y and display the solution
void compute_LCS(vector< char > &X, vector< char > &Y) {
	int m = X.size();
	int n = Y.size();

	size_t i, j;
	vector< vector< unsigned int > > len(m);

	for (i = 0; i < m; ++i)
		len[ i ].reserve(n);

	for (i = 1; i < m; ++i)
		len[ i ][ 0 ] = 0;
	for (j = 0; j < n; ++j)
		len[ 0 ][ j ] = 0;

	for (i = 1; i < m; ++i) {
		for (j = 1; j < n; ++j)
			if (X[ i ] == Y[ j ])
				len[ i ][ j ] = len[ i - 1 ][ j - 1 ] + 1;
			else if (len[ i - 1 ][ j ] >= len[ i ][ j - 1 ])
				len[ i ][ j ] = len[ i - 1 ][ j ];
			else
				len[ i ][ j ] = len[ i ][ j - 1 ];
	}

	cout << "> length of LCS of given sequences: " << len[ m - 1 ][ n - 1 ] << endl;
	cout << "> longest common subsequence: ";
	print_LCS(X, Y, len, m - 1, n - 1);
}