/**
 * 	author: satyajith
 * 	program: optimization of matrix-chain multiplication; bottom-up
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

void matrix_chain_mult(vector< int > &);
void print_optimal_paren(vector< vector< int > > &, int, int);

int main(int argc, char const *argv[]) {
	vector< int > p({30, 35, 15, 5, 10, 20, 25});	// 4 matrices; answer = 15125

	matrix_chain_mult(p);
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

void matrix_chain_mult(vector< int > &p) {
	int n = p.size() - 1;	// number of matrices

	vector< vector< int > > cost(n);		// space for computing costs
	vector< vector< int > > solution(n);	// indices of separation

	int i = 0, j = 0, k = 0, l = 0;
	int temp_cost = 0;

	// initialize cost and solution storage
	for (i = 0; i < n; ++i) {
		solution[ i ].reserve(i + 1);
		cost[ i ].reserve(i + 1);
		cost[ i ][ i ] = 0;
	}

	// here is where the magic happens
	for (l = 2; l <= n; ++l) {
		for (i = 0; i < (n - l + 1); ++i) {
			j = i + l - 1;
			cost[ j ][ i ] = INT_MAX;

			for (k = i; k < j; ++k) {
				temp_cost = cost[ k ][ i ] + cost[ j ][ k + 1 ] +
							(p[ i ] * p[ k + 1 ] * p[ j + 1 ]);
				if (temp_cost < cost[ j ][ i ]) {
					cost[ j ][ i ] = temp_cost;
					solution[ j ][ i ] = k;
				}
				temp_cost = 0;	// reset temp_cost
			}
		}	// end of procedure for current length
	}

	cout << "optimal cost: " << cost[ n - 1 ][ 0 ] << endl;
	cout << "solution: ";
	print_optimal_paren(solution, 0, n - 1);
}
