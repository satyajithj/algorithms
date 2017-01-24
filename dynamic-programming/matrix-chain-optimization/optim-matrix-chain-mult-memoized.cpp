/**
 * 	author: satyajith
 * 	program: optimization of matrix-chain multiplication; top-down memoized
 *
 *	question: given a chain A(1),A(2),...,A(n) of 'n' matrices, where for i = 1,2,...,n
 *	matrix A(i) has dimension [p(i-1) x p(i)], fully parenthesize the product
 *	A(1)xA(2)x...xA(n) in a way that minimizes the number of scalar multiplications.
 *
 * 	compile using: g++ -O3 <file-name> -std=c++11
 */

#include <climits>
#include <iostream>
#include <vector>

using namespace std;

void opt_matrix_chain_mult(vector< int > &);
int opt_matrix_chain_mult_aux(vector< int > &, vector< vector< int > > &,
							  vector< vector< int > > &, int, int);
void print_optimal_paren(vector< vector< int > > &, int, int);

int main(int argc, char const *argv[]) {
	vector< int > p({30, 35, 15, 5, 10, 20, 25});	// 4 matrices; answer = 15125

	opt_matrix_chain_mult(p);
	return 0;
}

// print the solution - recursive method
void print_optimal_paren(vector< vector< int > > &s, int i, int j) {
	if (i == j)
		cout << "A[" << i << "]";
	else {
		cout << "(";
		print_optimal_paren(s, i, s[ j ][ i ]);
		print_optimal_paren(s, s[ j ][ i ] + 1, j);
		cout << ")";
	}
}

// initialize computation
void opt_matrix_chain_mult(vector< int > &p) {
	int n = p.size() - 1;	// number of matrices

	vector< vector< int > > cost(n);		// space for computing costs
	vector< vector< int > > solution(n);	// indices of separation

	int i, j;
	// initialize cost and solution storage
	for (i = 0; i < n; ++i) {
		solution[ i ].reserve(i + 1);
		cost[ i ].reserve(i + 1);
		for (j = 0; j < i + 1; ++j) {
			cost[ i ][ j ] = INT_MAX;
		}
	}

	int optimized_cost = opt_matrix_chain_mult_aux(p, cost, solution, 0, n - 1);

	cout << optimized_cost << endl;
	cout << "solution: ";
	print_optimal_paren(solution, 0, n - 1);
}

// recursive routine with, a tabularized look up for solved subproblems
int opt_matrix_chain_mult_aux(vector< int > &p, vector< vector< int > > &cost,
							  vector< vector< int > > &s, int i, int j) {
	if (cost[ j ][ i ] != INT_MAX)
		return cost[ j ][ i ];

	if (i == j)
		cost[ j ][ i ] = 0;

	else {
		int temp_cost = 0;
		for (int k = i; k < j; ++k) {
			// recursive calls
			temp_cost = opt_matrix_chain_mult_aux(p, cost, s, i, k) +
						opt_matrix_chain_mult_aux(p, cost, s, k + 1, j) +
						(p[ i ] * p[ k + 1 ] * p[ j + 1 ]);
			// cost check
			if (temp_cost < cost[ j ][ i ]) {
				cost[ j ][ i ] = temp_cost;
				s[ j ][ i ] = k;
			}
		}
	}

	return cost[ j ][ i ];
}