/**
 *	author: satyajith
 *	algorithm: maximum subarray (recursive)
 *	time complexity: theta(n lg(n))
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
	int l_index;
	int r_index;
	int sum;
} DataList;

DataList *left, *right, *cross, *result;

void find_max_subarray(int[], int, int, DataList *);
void find_max_crossing_subarray(int[], int, int, int, DataList *);
void update_list(DataList *, int, int, int);

int main(int argc, char const *argv[]) {

	int n = 16;
	int arr[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};

	left = (DataList *) malloc(sizeof(DataList));
	right = (DataList *) malloc(sizeof(DataList));
	cross = (DataList *) malloc(sizeof(DataList));
	result = (DataList *) malloc(sizeof(DataList));

	left->l_index = left->r_index = left->sum = 0;
	*right = *left;
	*cross = *left;
	*result = *left;

	find_max_subarray(arr, 0, n-1, result);
	printf("max subarray from index %d to index %d, with sum %d",
			result->l_index, result->r_index, result->sum);

	free(left);	left = NULL;
	free(right); right = NULL;
	free(cross); cross = NULL;
	free(result); result = NULL;

	return 0;
}

// update the datalist structure x
void update_list(DataList *x, int l, int r, int sum) {
	x->l_index = l;
	x->r_index = r;
	x->sum = sum;
}

// find max subarray
void find_max_subarray(int arr[], int s, int e, DataList *x) {
	// base case
	if (s == e) {
		update_list(x, s, e, arr[s]);
		return;
	}

	else {
		int mid = (s+e)/2;

		find_max_subarray(arr, s, mid, left);					// left subarray
		find_max_subarray(arr, mid + 1, e, right);				// right subarray
		find_max_crossing_subarray(arr, s, mid, e, cross);		// crossing subarray

		if ((left->sum > right->sum) && (left->sum > cross->sum))
			update_list(result, left->l_index, left->r_index, left->sum);
		else if ((right->sum > left->sum) && (right->sum > cross->sum))
			update_list(result, right->l_index, right->r_index, right->sum);
		else
			update_list(result, cross->l_index, cross->r_index, cross->sum);
	}
}

// find max subarray over a crossing point of divisions
void find_max_crossing_subarray(int arr[], int s, int m, int e, DataList *x) {
	int left_sum = INT_MIN;
	int right_sum = INT_MIN;
	int sum = 0;
	int max_left = m;
	int max_right = m + 1;

	for (int i = max_left; i >= s ; i--) {
		sum += arr[i];
		if (sum > left_sum) {
			left_sum = sum;
			max_left = i;
		}
	}

	sum = 0;

	for (int i = max_right; i <= e ; i++) {
		sum += arr[i];
		if (sum > right_sum) {
			right_sum = sum;
			max_right = i;
		}
	}

	update_list(x, max_left, max_right, left_sum+right_sum);
}
