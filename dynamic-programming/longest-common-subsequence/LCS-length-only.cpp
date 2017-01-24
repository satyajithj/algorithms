/**
 * 	author: satyajith
 *
 * 	program: compute the length of the longest common subsequence
 * 	Z of two input sequences X(size m) and Y(size n), using an
 * 	additional space of min(m, n) + O(1) only
 *
 *	compile using: g++ <file-name> -std=c++11
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int compute_lcs_length(vector< char > &, vector< char > &);

int main(int argc, char const *argv[]) {
	vector< char > S1({'\0', 'A', 'C', 'C', 'G', 'G', 'T', 'C', 'G', 'A',
					   'G',  'T', 'G', 'C', 'G', 'C', 'G', 'G', 'A', 'A',
					   'G',  'C', 'C', 'G', 'G', 'C', 'C', 'G', 'A', 'A'});

	vector< char > S2({'\0', 'G', 'T', 'C', 'G', 'T', 'T', 'C', 'G', 'G',
					   'A',  'A', 'T', 'G', 'C', 'C', 'G', 'T', 'T', 'G',
					   'C',  'T', 'C', 'T', 'G', 'T', 'A', 'A', 'A'});

	int length;
	if (min(S1.size(), S2.size()) == S1.size())
		length = compute_lcs_length(S1, S2);
	else
		length = compute_lcs_length(S2, S1);

	cout << "> length of LCS: " << length;	// solution is 20
	return 0;
}

// compute and return the length of LCS using min(m, n) + O(1) space
int compute_lcs_length(vector< char > &X, vector< char > &Y) {
	int m = X.size();
	int n = Y.size();

	size_t i, j;
	int d_curr = 0, d_next = 0;	// len[i-1][j-1] needs to be maintained

	vector< unsigned int > len(m);
	for (i = 0; i < m; i++)
		len[ i ] = 0;

	for (i = 1; i < n; i++) {
		d_curr = len[ 0 ];
		for (j = 1; j < m; j++) {
			d_next = len[ j ];
			if (X[ j ] == Y[ i ])
				len[ j ] = d_curr + 1;
			else
				len[ j ] = ((len[ j ] >= len[ j - 1 ]) ? len[ j ] : len[ j - 1 ]);
			// when using 1 row, len[i-1][j] from 2 row is len[j]
			// and len[i][j-1] is len[j-1]
			d_curr = d_next;
		}
	}
	return len[ m - 1 ];
}