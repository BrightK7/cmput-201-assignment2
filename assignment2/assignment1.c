/* CMPUT 201 (A2 + A3) Assignments */
/* Dues: */
/* #1: 11:55pm, October 8, 2018; */
/* #2: 11:55pm, November 12, 2018; */
/* #3: 11:55pm, December 7, 2018 */
/*
Submiting student:  Bo Li
Collaborating classmates: None
Other collaborators: None
References (excluding textbook and lecture slides): https://stackoverflow.com/questions/17909215/c-random-numbers-between-10-and-30
													https://www.tutorialspoint.com/c_standard_library/string_h.htm
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv){

	int mach_num, job_num,min,max,instance,pro_time[30];

	if (argc != 2){										// if input != 2 printf the error in stderr
		fprintf(stderr,"./my program -i|-r\n");
		return 0;
	}

	if(strcmp(argv[1],"-i") ==0){						// if the instrucion is "-i"
		instance = 1;
		printf("Enter the number of machines in stage 1: ");
		if((scanf("%d",&mach_num))!= 1){
			fprintf(stderr,"Error in reading the instance! \n");
			return -1;
		}
		printf("Enter the number of jobs ");
		if((scanf("%d",&job_num))!= 1){
			printf("Error in reading the instance! \n");
			return -1;
		}
		printf("Enter in each line the processing times for a job:\n");

		for (int i = 0,c = 0; i < job_num; i++,c += 3){									// read the job time 3 in a row and with space between them
			if((scanf("%d %d %d",&pro_time[c],&pro_time[c+1],&pro_time[c+2]))!= 3){
				printf("Error in reading the instance! \n");
				return 0;
			}
		}
		printf("#instance %d_%d_%d.txt\n",mach_num,job_num,instance);
		printf("#number of machines in stage 1\n %d\n",mach_num);						// print out the whole instance
		printf("#number of jobs\n %d\n",job_num);
		for (int i = 0; i < instance; i++){
			printf("#job processing times\n");
		for (int n = 0; n < job_num; n += 3)
			printf("%d %d %d\n",pro_time[n],pro_time[n+1],pro_time[n+2]);
			}
		printf("End of instance\n");
     	}

	else if(strcmp(argv[1],"-r") ==0){												// if the instruction is "-r"
		srand(time(NULL));
		printf("Generating random instances ...\n");
		printf("Enter the number of machines in stage 1: ");
		if((scanf("%d",&mach_num))!= 1){											// Ask user enter data for instance
			printf("Error in reading the instance! \n");
			return -1;
		}
		printf("Enter the number of jobs ");
		if((scanf("%d",&job_num))!= 1){
			printf("Error in reading the instance! \n");
			return -1;
		}
		printf("Enter the processing time interval [t_1, t_2]: ");
		if ((scanf("%d %d",&min,&max))!= 2){
			printf("Error in reading the instance! \n");
			return -1;
		}
		printf("Enter the number of instances to be generated:");
		if((scanf("%d",&instance))!= 1){									
			printf("Error in reading the instance! \n");
			return -1;
		}
		for (int i = 1; i < instance + 1; i++){									//printf out the random job_time
			int ran;
			printf("#instance %d_%d_%d.txt\n",mach_num,job_num,i);
			for (int n = 1; n < (job_num*3)+1 ; n ++){								
				ran = (rand() % (max + 1 - min)) + min;							// get the random be equaly change
				printf("%d ", ran);
				if (n % 3 == 0)
					printf("\n");
			}
			printf("#end of instance\n");
		}
	}
	else
		fprintf(stderr,"./my program -i|-r\n");
	return 0;
}

void fpt(int job_num,int jobs[job_num],int tim_num[]) {

}

