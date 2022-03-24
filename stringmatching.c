#include<stdio.h>
#include<omp.h>
#include<string.h>


int main(int argc,char** argv){
	int num_threads=4;
	omp_set_num_threads(num_threads);
	if(argc!=3){
		printf("Enter valid number of arguements");
		return 0;
	}

	char* pattern=argv[1];
	char* text=argv[2];
	int pat_len=strlen(pattern);
	int txt_len=strlen(text);
	int local_steps = txt_len / num_threads + 1;

    double start = omp_get_wtime();
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        // start of chunk index
        long a = local_steps * ID;
        // end of chunk index
        long b = local_steps * (ID + 1);
        // do naive comparison
        int i = a;
        for (i; i < b; i++)
        {
            if (strncmp(pattern, &text[i], pat_len) == 0)
            {
                printf("%d\n", i);
            }
        }
    }		

}
