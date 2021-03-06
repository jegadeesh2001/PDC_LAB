#include<omp.h>
#include<iostream>
using namespace std;


void swap(int* num1,int* num2){
	int temp=*num1;
	*num1=*num2;
	*num2=temp;
}

void bubblesort(int* arr,int n){
	int i,j;
	for(i=0;i<n-1;i++){
		#pragma omp parallel for default(none),shared(arr,n,i)
		
			for(j=0;j<n-i-1;j++){
				if(arr[j]>arr[j+1])
					swap(&arr[j],&arr[j+1]);
			}
		

	}
}


int main(){
	int n;
	cout<<"Enter the size of Array: "<<endl;
	cin>>n;
	int A[n];
	for(int i=0;i<n;i++){
		cout<<"Enter the array element: "<<endl;
		cin>>A[i];

	}
	bubblesort(A,n);
	cout<<"The array elements after sorting is: "<<endl;
	for(int i=0;i<n;i++){
		cout<<A[i]<<" ";
	}






}
