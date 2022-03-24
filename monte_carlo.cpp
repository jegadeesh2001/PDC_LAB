#include<omp.h>
#include<bits/stdc++.h>
using namespace std;

void find_pi(){
	double x,y;
	double d;
	int cntcirc=0;
	int cntsq=0;
	int i=0;
	#pragma omp parallel firstprivate(x,y,d,i) reduction(+ : cntcirc,cntsq) num_threads(5)
	{
		srand((int)time(NULL));
		for(i=0;i<1000;i++){
			x=(double)drand48();
			y=(double)drand48();
			d=((x*x)+(y*y));
			if(d<=1){
				cntcirc++;
			}
			cntsq++;
		}
	}
	double pi=4.0*((double)cntcirc/(double)cntsq);
        cout<<"PI: "<<pi;
}
int main(){
	find_pi();
}
