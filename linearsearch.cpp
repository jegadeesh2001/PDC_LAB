#include<omp.h>
#include<iostream>

using namespace std;


int linearsearch(int A[],int k,int n){
	int index=-1;
	
	#pragma omp parallel for
	for(int i=0;i<n;i++){
		if(A[i]==k)
		   index=i;
	}
	return index;
}









int main(){
	int n;
	cout<<"enter the number of elements in the array: "<<endl;
	cin>>n;
	int A[n];
	for(int i=0;i<n;i++){
		cout<<"Enter the element of array: "<<endl;
		cin>>A[i];
	}
	int k;
	cout<<"Enter the key value to be found in the array: "<<endl;
	cin>>k;
	int ans=linearsearch(A,k,n);
	if(ans==-1)
	  cout<<"Element not found in the array"<<endl;
	else
	  cout<<"Element found ath the index: "<<ans;
}
