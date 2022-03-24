
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

                         

void swap(int* a, int* b)  //Function to swap two numbers
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int arr[], int start, int end )  // Function to partition the array based on pivot
{
	
	int pivot = arr[end]; // We have initialised the pivot as the last element of array
	int i = (start - 1);  // Index of smaller element

	for (int j = start; j <= end - 1; j++) {

		if (arr[j] < pivot) {   // If current element is smaller than the pivot
			i++;           //we increment the index of smaller element 
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[end]);
	return (i + 1);  // Returning the index of partition
}


void quicksort(int arr[], int start, int end)
{
	
	int index;

	if (start < end) {

	
		index = partition(arr, start, end); // Getting the index of partitioned element 

		#pragma omp parallel sections   // sections construct ditributes the block between existing threads. Each block should be independent.  
		{
			#pragma omp section    //section marks different blocks which represents a task
			{
				
				quicksort(arr, start, index - 1); //sorting the left half of the array
			}
			#pragma omp section
			{
				
				quicksort(arr, index + 1, end);  //sorting the right half of the array
			}
		}
	}
}


int main()
{
	
	int n;

	cout<<"Enter the size of the array: "<<endl;
        cin>>n;
	
	int arr[n];;

	
	for (int i = 0; i < n; i++) {
		cout<<"Enter the array element: "<<endl;
		cin >> arr[i];
	}

	quicksort(arr, 0, n-1); //sorting the array

	cout << "Array elements  after sorting is: "<<endl;

	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}

	
}

