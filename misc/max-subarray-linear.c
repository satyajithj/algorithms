/**
 *	author: satyajith
 *	program: maximum subarray problem (Kadane's algorithm)
 *	time complexity:	theta(n)
 */

#include <stdio.h>
#include <limits.h>

void find_max_subarray(int[], int);

int main(int argc, char const *argv[]) {

	int n = 16;
	int arr[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};

	find_max_subarray(arr, n);
	return 0;
}

// linear time max subarray routine
void find_max_subarray(int arr[], int n) {
	int l_index = 0, r_index = 0;
	int max_sum = INT_MIN;
	int sum = 0, l = 0;

	for (int i = 0; i < n; i++) {

		sum += arr[i];

		if (sum > max_sum) {
			l_index = l;			// max subarray's left index
			r_index = i;			// max subarray's right index
			max_sum = sum;			// the max sum
		}

		if (sum < 0) {
			sum = 0;
			l = i + 1;
		}
	}

	printf("max subarray at [%d, %d] with sum %d\n", l_index, r_index, max_sum);
}
