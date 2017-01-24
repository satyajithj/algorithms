/**
 * 	author: satyajith
 * 	program: rod cutting; dynamic programming top-down approach; memoized
 *
 * 	question: Given a rod of length 'n' units and a table of prices P(i) for
 * 	i = 1,2,...,n determine the maximum revenue r(n) obtainable by cutting up
 * 	the rod and selling the pieces.
 *
 * 	compile using: g++ -O3 <file-name> -std=c++11
 */

#include <climits>
#include <iostream>
#include <vector>

using namespace std;

void rod_cut_memoized(vector< int > &);
int rod_cut_memoized_aux(int, vector< int > &, vector< int > &, vector< int > &);

int main(int argc, char const *argv[]) {
	vector< int > price({0, 1, 5, 8, 9, 10, 17, 17, 20});
	// use push_back for a larger input from a file
	rod_cut_memoized(price);
	return 0;
}

// rod-cut memoized call
void rod_cut_memoized(vector< int > &p) {
	// revenue and solution vectors
	int n = p.size();
	vector< int > r(n), solution(n);

	for (int i = 0; i < n; ++i)
		r.at(i) = solution.at(i) = INT_MIN;	// initialize all values to 0

	int max_rev = rod_cut_memoized_aux(--n, p, r, solution);

	printf("max revenue: %d\n", max_rev);
	printf("solution: ");

	while (n > 0) {
		cout << solution.at(n) << ", ";
		n -= solution.at(n);
	}
}

// aux rod-cut memoized routine
int rod_cut_memoized_aux(int n, vector< int > &p, vector< int > &r, vector< int > &s) {
	// base case
	if (r.at(n) >= 0)
		return r.at(n);

	int temp_rev = INT_MIN;
	int temp = 0;

	if (n == 0)
		temp_rev = 0;

	else
		for (int i = 1; i <= n; ++i) {
			temp = p.at(i) + rod_cut_memoized_aux(n - i, p, r, s);
			if (temp > temp_rev) {
				temp_rev = temp;
				s.at(n) = i;	// for a 'n' units rod, first cut at 'i' units
			}
		}

	r.at(n) = temp_rev;
	return temp_rev;
}