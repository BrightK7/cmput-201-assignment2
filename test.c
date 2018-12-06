#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
void random_instance(int instance, int mach_num, int job_num, int min, int max, FILE *fp);
int main(int argc, char const *argv[])
{
	for (int i = 1; i < 11; i++){
        char title[25];
		sprintf(title,"instancem_n_t1_t2_%d.txt",i);
        FILE *fp = fopen(title,"w");
		for (int x = 0; x < 22; x++){
		//general file base one each instance
		//char instance_char = i + '0';
		for (int j = 1; j < 11; j++){
			//char t1 = '1',t2 = j * 10 +'0';
			for (int k = 1; k < 21; k++){
				//char jobs = k*10 +'0';
				for (int l = 1; l < 21;l++){
					//char mach = l +'0';
					random_instance(i,l,k*10,1,j*10,fp);
				}
			}
		    }
	    }
        free(fp);
    }
    return 0;
}



void random_instance(int instance, int mach_num, int job_num, int min, int max, FILE *fp){
    	//printf out the random job_time
		int ran;
		fprintf(fp,"#instance %d_%d_%d.txt\n",mach_num,job_num,instance);
		for (int n = 1; n < (job_num*3)+1 ; n ++){								
			ran = (rand() % (max + 1 - min)) + min;							// get the random be equaly change
			fprintf(fp,"%d ", ran);
			if (n % 3 == 0)
				fprintf(fp,"\n");
		}
		fprintf(fp,"#end of instance\n");
        return;
}
