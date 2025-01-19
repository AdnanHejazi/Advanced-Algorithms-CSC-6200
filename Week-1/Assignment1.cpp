#include <iostream>

void twoSum(int arr[], int size, int target) {
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] + arr[j] == target) {
                std::cout << "Output: [" << i << ", " << j << "]\n";
                return;
            }
        }
    }
}

int main() {
    // Example
    int arr1[] = {2, 7, 11, 15};
    int target1 = 9;
    twoSum(arr1, 4, target1);

    int arr2[] = {3, 2, 4};
    int target2 = 6;
    twoSum(arr2, 3, target2);

    int arr3[] = {3, 3};
    int target3 = 6;
    twoSum(arr3, 2, target3);

    return 0;
}
