#include "omp.h"
#include<iostream>
using namespace std;

int main(){
	cout<<"The number of processors are: "<<omp_get_num_procs();



}
