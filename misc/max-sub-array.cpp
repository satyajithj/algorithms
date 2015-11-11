/*
	author: satyajith
	algorithm: max sub-array in linear time (kadane's algorithm)

	complexity: O(n)
*/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <climits>

using namespace std;

#define DEBUG cout << "DEBUG" << endl
#define NEWLINE cout << endl

void max_sub_array(vector<int>*);

int main(int argc, char* argv[]) {


	int arr[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7
		, 12, -5, -22, 15, -4, 7};

	vector<int> *vec = new vector<int> (arr,
		arr + sizeof(arr)/sizeof(int));
	max_sub_array(vec);				// call to max sub array
	
	NEWLINE;
	return 0;
}

void max_sub_array(vector<int> *x) {

	ostream_iterator<int> output(cout, " ");
	copy(x->begin(), x->end(), output);
	NEWLINE;

	int s, max_s, max_e;
	max_s = max_e = s = 0;

	int max_sum = INT_MIN;
	int curr_sum = 0;

	for (int i = 0; i < x->size(); i++) {

		curr_sum += (*x)[i];
		
		if (curr_sum > max_sum) {
			max_e = i;
			max_s = s;
			max_sum = curr_sum;
		}

		if (curr_sum < 0) {
			curr_sum = 0;
			s = i+1;
		}
	}

	cout << "max sub array: ";
	copy(x->begin() + max_s, x->begin() + max_e + 1, output);
	NEWLINE;
	cout << "max sum: " << max_sum;
}