#include "records.h"

void RECORDS::sort_records_insertion(int start_index, int end_index) {
	// Insertion sort
	for (int i = start_index + 1; i <= end_index; i++) {
		RECORD tmp = records[i];
		int j = i;
		while ((j > start_index) && (compare_keys((const void*)&tmp, (const void*)(&records[j - 1])) < 0)) {
			records[j] = records[j - 1];
			j--;
		}
		records[j] = tmp;
	}
}

void RECORDS::sort_records_heap(int start_index, int end_index) {
	// Classic heap sort

	int size = end_index - start_index + 1;

	// Heapify first (Max Heap)
	// Bottom-up Process
	// Starts with the last parent node level
	for (int i = (size / 2) - 1 + start_index; i >= start_index; i--) {
		max_heapify(i, end_index);
	}

	for (int i = end_index; i > start_index; i--) {

		// Move the largest value to the last
		// Swap
		RECORD temp = records[start_index];
		records[start_index] = records[i];
		records[i] = temp;

		// Re-heapify the remaining
		max_heapify(start_index, i - 1);
	}
}

void RECORDS::sort_records_weird(int start_index, int end_index) {
	// A weird sort with a make-heap operation followed by insertion sort

	// 1. Make min heap
	int size = end_index - start_index + 1;

	// Bottom-up Process
	// Starts with the last parent node
	for (int i = (size / 2) - 1 + start_index; i >= start_index; i--) {
		min_heapify(i, end_index);
	}

	// 2. Insertion Sort
	sort_records_insertion(start_index, end_index);
}

void RECORDS::sort_records_quick_classic(int start_index, int end_index) {
	// Classic quick sort without any optimization techniques applied

	if (start_index < end_index) {
		int pivot_index = partition(start_index, end_index);

		// Iteration (each side)
		sort_records_quick_classic(start_index, pivot_index - 1);
		sort_records_quick_classic(pivot_index + 1, end_index);
	}
}

void RECORDS::sort_records_intro(int start_index, int end_index) {
	// Introsort described in https://en.wikipedia.org/wiki/Introsort

	// Calculate maximum depth as ⌊log2(n)⌋ * 2
	int size = end_index - start_index + 1;
	int max_depth = 0;

	int n = size;
	while (size > 1) {

		// Right shift to divide by 2
		size >>= 1;
		max_depth += 1;
	}

	max_depth *= 2;

	// Call introsort with max depth
	introsort(start_index, end_index, max_depth);
	introsort(start_index, end_index, max_depth);
}

void RECORDS::sort_records_merge_with_insertion(int start_index, int end_index) {
	// Merge sort optimized by insertion sort only

	int size = end_index - start_index + 1;

	// Insertion sort
	if (size <= 16) {
		sort_records_insertion(start_index, end_index);
		return;
	}

	// Merge Sort
	if (start_index < end_index) {
		int mid_index = start_index + (end_index - start_index) / 2;

		// Recursively sort the two halves
		sort_records_merge_with_insertion(start_index, mid_index);
		sort_records_merge_with_insertion(mid_index + 1, end_index);

		// Merge the sorted halves
		int left_size = mid_index - start_index + 1;
		int right_size = end_index - mid_index;

		// Temp arrays for merging
		RECORD* left_temp = new RECORD[left_size];
		RECORD* right_temp = new RECORD[right_size];

		// Copy data to temporary arrays
		for (int i = 0; i < left_size; i++) {
			left_temp[i] = records[start_index + i];
		}
		for (int j = 0; j < right_size; j++) {
			right_temp[j] = records[mid_index + 1 + j];
		}

		// Merge the temp arrays back into records
		int i = 0, j = 0, k = start_index;
		while (i < left_size && j < right_size) {
			if (compare_keys((const void*)&left_temp[i], (const void*)&right_temp[j]) < 0) {
				records[k] = left_temp[i];
				k += 1;
				i += 1;
			}
			else {
				records[k] = right_temp[j];
				k += 1;
				j += 1;
			}
		}

		// Copy remaining elements of left and right
		while (i < left_size) {
			records[k] = left_temp[i];
			k += 1;
			i += 1;
		}
		while (j < right_size) {
			records[k] = right_temp[j];
			k += 1;
			j += 1;
		}

		// Clean up temp arrays
		delete[] left_temp;
		delete[] right_temp;
	}
}

void RECORDS::max_heapify(int start_index, int end_index) {
	// Heapify (Max Heap)

	int largest_index = start_index;
	int largest_child = 2 * start_index + 1;
	

	// Compare the left child and right child of largest_index
	if (largest_child < end_index && compare_keys((const void*)&records[largest_child + 1], (const void*)&records[largest_child]) > 0) {
		largest_child += 1;
	}

	// Compare the largest child and largest_index
	if (largest_child <= end_index && compare_keys((const void*)&records[largest_child], (const void*)&records[largest_index]) > 0) {
		largest_index = largest_child;

		// Now largest_index != start_index
		// Swap
		RECORD temp = records[start_index];
		records[start_index] = records[largest_index];
		records[largest_index] = temp;

		//Iteration
		max_heapify(largest_index, end_index);
	}
}

void RECORDS::min_heapify(int start_index, int end_index) {
	// Heapify (Min Heap)

	int smallest_index = start_index;
	int smallest_child = 2 * start_index + 1;


	// Compare the left child and right child of smallest_index
	if (smallest_child < end_index && compare_keys((const void*)&records[smallest_child + 1], (const void*)&records[smallest_child]) < 0) {
		smallest_child += 1;
	}

	// Compare the smallest child and smallest_index
	if (smallest_child <= end_index && compare_keys((const void*)&records[smallest_child], (const void*)&records[smallest_index]) < 0) {
		smallest_index = smallest_child;

		// Now smallest_index != start_index
		// Swap
		RECORD temp = records[start_index];
		records[start_index] = records[smallest_index];
		records[smallest_index] = temp;

		//Iteration
		min_heapify(smallest_index, end_index);
	}
}

int RECORDS::median_of_three(int start_index, int end_index) {
	int mid_index = start_index + (end_index - start_index) / 2;

	int indices[3] = { start_index, mid_index, end_index };

	// Bubble Sort
	// Sort to find the median of three
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2 - i; j++) {
			if (compare_keys((const void*)&records[indices[j]], (const void*)&records[indices[j + 1]]) > 0) {

				// Swap
				int temp = indices[j];
				indices[j] = indices[j + 1];
				indices[j + 1] = temp;
			}
		}
	}

	return indices[1];
}

int RECORDS::partition(int start_index, int end_index) {

	// Get pivot from the function 'median_of_three'
	int pivot_index = median_of_three(start_index, end_index);

	// Move pivot to the last index
	// Swap
	RECORD temp = records[end_index];
	records[end_index] = records[pivot_index];
	records[pivot_index] = temp;

	RECORD pivot = records[end_index];

	int i = start_index - 1;
	for (int j = start_index; j < end_index; j++) {
		if (compare_keys((const void*)&records[j], (const void*)&pivot) <= 0) {
			i += 1;

			// Swap
			temp = records[i];
			records[i] = records[j];
			records[j] = temp;
		}
	}

	// Move pivot to sorted position
	// Swap
	records[end_index] = records[i + 1];
	records[i + 1] = pivot;

	return i + 1;
}

void RECORDS::introsort(int start_index, int end_index, int max_depth) {
	int size = end_index - start_index + 1;

	// Use Insertion Sort if the partition size is less than 16
	if (size < 16) {
		sort_records_insertion(start_index, end_index);
		return;
	}

	// Switch to Heap Sort if maximum depth is reached
	if (max_depth == 0) {
		sort_records_heap(start_index, end_index);
		return;
	}

	// Use Quick Sort's partitioning
	int pivot_index = partition(start_index, end_index);

	// Recur for left and right partitions
	introsort(start_index, pivot_index - 1, max_depth - 1);
	introsort(pivot_index + 1, end_index, max_depth - 1);
}