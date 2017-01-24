/**
 * 	author: satyajith
 * 	program: compute the longest common subsequence Z of two
 * 	input sequences X and Y (dynamic programming; top-down memoized)
 */

#include <climits>
#include <iostream>
#include <vector>

using namespace std;


void compute_LCS(vector< char > &, vector< char > &);
int compute_LCS_aux(vector< char > &, vector< char > &,
					vector< vector< unsigned int > > &, int, int);
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

// LCS compute call
void compute_LCS(vector< char > &X, vector< char > &Y) {
	int m = X.size();
	int n = Y.size();

	vector< vector< unsigned int > > len(m);
	size_t i, j;

	for (int i = 0; i < m; ++i)
		len[ i ].reserve(n);

	for (i = 0; i < m; ++i)
		for (j = 0; j < n; ++j)
			len[ i ][ j ] = UINT_MAX;

	int length_LCS = compute_LCS_aux(X, Y, len, m - 1, n - 1);

	cout << "> length of LCS of given sequences: " << length_LCS << endl;
	cout << "> longest common subsequence: ";
	print_LCS(X, Y, len, m - 1, n - 1);
}

// recursive memoized version
int compute_LCS_aux(vector< char > &X, vector< char > &Y,
					vector< vector< unsigned int > > &len, int i, int j) {
	if (len[ i ][ j ] != UINT_MAX)
		return len[ i ][ j ];	// if already computed

	else {
		if (i == 0 || j == 0)
			len[ i ][ j ] = 0;	// one sequence is of length 0

		else if (X[ i ] == Y[ j ])
			len[ i ][ j ] = 1 + compute_LCS_aux(X, Y, len, i - 1, j - 1);
		else {
			int a = compute_LCS_aux(X, Y, len, i - 1, j);
			int b = compute_LCS_aux(X, Y, len, i, j - 1);
			len[ i ][ j ] = ((a >= b) ? a : b);
		}
	}

	return len[ i ][ j ];
}