#include <stdio.h>

// Recursive Algorithm
void recursiveShuffle(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Recursively shuffle the two halves
        recursiveShuffle(arr, left, mid);
        recursiveShuffle(arr, mid + 1, right);
        
        int i = left;
        int j = mid + 1;

        // Merge the two halves in a sorted manner
        while (i <= mid && j <= right) {
            // Move pointers i and j to the first odd and even elements, respectively
            while (i <= mid && arr[i] % 2 != 0) {
                i++;
            }
            while (j <= right && arr[j] % 2 == 0) {
                j++;
            }

            // Swap elements at indices i and j if both pointers are within their respective halves
            if (i <= mid && j <= right) {
                int temp = arr[j];
                for (int k = j; k > i; k--) {
                    arr[k] = arr[k - 1];
                }
                arr[i] = temp;
                i++;
                j++;
                mid++;
            }
        }
    }
}

// Iterative Algorithm
void iterativeShuffle(int arr[], int n) {
    int i = 0;
    int j = 0;

    // Iterate through the array
    while (i < n) {
        // If the current element is even, move to the next element
        if (arr[i] % 2 == 0) {
            i++;
        } else {
            // If the current element is odd, swap it with the first even element
            int temp = arr[i];
            for (int k = i; k > j; k--) {
                arr[k] = arr[k - 1];
            }
            arr[j] = temp;
            i++;
            j++;
        }
    }
}

int main() {
    // Example array
    int arr[] = {1, 2, 3, 8, 5, 12, 9, 7, 4, 6, 15, 24, 100};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Recursive Shuffle
    recursiveShuffle(arr, 0, n - 1);

    printf("Recursive Shuffled array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Reset the array
    int arr2[] = {1, 2, 3, 8, 5, 12, 9, 7, 4, 6, 15, 24, 100};

    // Iterative Shuffle
    iterativeShuffle(arr2, n);

    printf("Iterative Shuffled array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr2[i]);
    }

    return 0;
}
