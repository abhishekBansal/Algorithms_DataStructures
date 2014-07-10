/*
Abhishek Bansal
Program to find r combinations from n element unsorted array
Ref: http://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
*/

#include <iostream>
#include <cstdlib>

void findCombinations(int arr[], int resArr[], int start, int end, int index, int r)
{
    if(index == r)
    {
        for(int i=0; i < r; i++)
            std::cout << resArr[i];

        std::cout << std::endl;
        return;
    }

    // we fix first elemnt of array and recurse for others
    for(int i = start; i < end; i++)
    {
        resArr[index] = arr[i];
        findCombinations(arr, resArr, i+1, end, index + 1, r);

        // for handling arrays with duplicate no's
        while (arr[i] == arr[i+1])
             i++;
    }
}

void printCombinations(int arr[], int n, int r)
{
    int *resArr = new int[r];
    findCombinations(arr, resArr, 0, n, 0, r);
}

/* Following function is needed for library function qsort(). Refer
   http://www.cplusplus.com/reference/clibrary/cstdlib/qsort/ */
int comp(const void* a, const void* b)
{  
    return *(int*)a > *(int*)b ; 
}

int main()
{
    int arr1[] = {5, 2, 6, 7, 8 ,9};
    int arr2[] = {6, 2, 6, 7, 6 ,9};
    int r = 3;

    // for handling arrays with duplicate no's
    qsort(arr1, sizeof(arr1)/sizeof(arr1[0]), sizeof(arr1[0]), comp);

    printCombinations(arr1, sizeof(arr1)/sizeof(arr1[0]), r);
    
    std::cout << std::endl << std::endl;

    qsort(arr2, sizeof(arr2)/sizeof(arr2[0]), sizeof(arr2[0]), comp);

    printCombinations(arr2, sizeof(arr2)/sizeof(arr2[0]), r);

    return 0;
}