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
void read();
void general();
void random_instance(int instance, int mach_num, int job_num, int min, int max, FILE *fp);
int lpt(int *time, int par_jobs[],int length,int jobs[],int mach_work[],int mach_num);
void slowsort(int a[], int b[],int x);
void johnson_sort(int jobs[][2], int john_order[],int length,int left[]);
int johnson(int *start_time,int johnson_order[],int work[],int work_num,int work_time[][2]);
void fill(int input[],int list[][4],int group,int index,int cindex);

int main(int argc, char** argv){
	if (argc != 2){										// if input != 2 printf the error in stderr
		fprintf(stderr,"./my program -i|-r\n");
		return 0;
	}
	if(strcmp(argv[1],"-i") ==0){						// if the instrucion is "-i"
        read();
    }
    else if(strcmp(argv[1],"-r") ==0){
        general();
    }
    else
	    fprintf(stderr,"./my program -i|-r\n");
	return 0;
}


void read(){
    int mach_num, job_num,start_time = 0; 
    int *pro_time;
	printf("Enter the number of machines in stage 1: ");
	if((scanf("%d",&mach_num))!= 1){
		fprintf(stderr,"Error in reading the instance! \n");
		return;
	}

	int mach_work[mach_num];
	int b_c_work[2];
	for (int i = 0; i< 2; i++){
		b_c_work[i] = 0;
	}
	for (int i = 0; i<mach_num; i++){
		mach_work[i] = 0;
	}

	printf("Enter the number of jobs ");
	if((scanf("%d",&job_num))!= 1){
		printf("Error in reading the instance! \n");
		return;
	}
    pro_time = (int*)malloc((job_num * 3) * sizeof(int));
	printf("Enter in each line the processing times for a job:\n");

	for (int i = 0; i < job_num*3; i++){									// read the job time 3 in a row and with space between them
		if(scanf("%d",&pro_time[i])!= 1){
			printf("Error in reading the instance! \n");
			return;
		}
	}
	int jobs[job_num];
	int jon_array[job_num][2];
	for (int i = 0,j = 0 ,k = 0; i < job_num *3; i++){
		if (i % 3 == 0){
			jobs[j] = pro_time[i];
			//printf("jobs [%d] is %d \n",jobs[j],j);
			j++;
		}
		else if(i % 3 == 1)
			jon_array[j-1][0] = pro_time[i];

		else{
			jon_array[j-1][1] = pro_time[i];
			k++;
		}

	}
	//for (int i = 0; i < job_num; i++){
	//	for (int j = 0; j < 2; j++){
	//		printf("aaaa is %d \n",jon_array[i][j]);
	//	}
	//}

    int lrt_order[job_num];
    int lpt_array[job_num];
	int job_list[job_num];
	for(int i = 0; i < job_num; i++){
		job_list[i] = jobs[i];
	}

    slowsort(jobs,lrt_order,job_num);

	int johnson_order[job_num];
	for (int i = 0; i < job_num; i++){
		johnson_order[i] = 0;
	}
	int left[job_num];
	if (mach_num > job_num)
		mach_num = job_num;
	for (int i = 0; i < mach_num; i++){
        lpt_array[i] = lrt_order[i];
	}
	for (int i = 0; i < job_num - mach_num; i++){
		left[i] = lrt_order[mach_num+i];
		//printf("left is %d \n",left[i]);
	}
	johnson_sort(jon_array,johnson_order,job_num - mach_num,left);
	int lpt_lifespan = 0;
	int johnson_lifespan = 0;
	lpt_lifespan = lpt(&start_time,lpt_array,mach_num,job_list,mach_work,mach_num);
	if (mach_num < job_num)
		johnson_lifespan = johnson(&start_time,johnson_order,b_c_work,job_num - mach_num,jon_array);
	for (int i = 0; i < job_num; i++){
		johnson_order[i] = 0;
	}
	if (lpt_lifespan > johnson_lifespan){
		start_time = lpt_lifespan;
	}
	else{
		start_time = johnson_lifespan;
		for (int i = 0; i < mach_num;i++){
			mach_work[i] = start_time;
		}
	}
	johnson_sort(jon_array,johnson_order,mach_num,lpt_array);
	//johnson(&start_time,lpt_array,mach_num,jon_array,mach_work,mach_num);
	for ( int i = 0; i < job_num - mach_num; i++){
		lpt_array[i] = lrt_order[mach_num+i];
	}
	//printf("The start_time is %d ---------------------",start_time);
	if (mach_num < job_num)
    	lpt_lifespan = lpt(&start_time,lpt_array,(job_num-mach_num),job_list,mach_work,mach_num);
	johnson_lifespan = johnson(&start_time,johnson_order,b_c_work,mach_num,jon_array);
		if (lpt_lifespan > johnson_lifespan){
		start_time = lpt_lifespan;
	}
	else{
		start_time = johnson_lifespan;
	}
	printf("The LPT-johnson schedule has overall makespan %d",start_time);
}



void general(){
    int mach_num, job_num,min,max,instance;
    srand(time(NULL));
	printf("Generating random instances ...\n");
	printf("Enter the number of machines in stage 1: ");
	if((scanf("%d",&mach_num))!= 1){											// Ask user enter data for instance
		printf("Error in reading the instance! \n");
		return;
	}
	printf("Enter the number of jobs ");
	if((scanf("%d",&job_num))!= 1){
		printf("Error in reading the instance! \n");
		return;
	}
	printf("Enter the processing time interval [t_1, t_2]: ");
	if ((scanf("%d %d",&min,&max))!= 2){
		printf("Error in reading the instance! \n");
		return;
	}
	printf("Enter the number of instances to be generated:");
	if((scanf("%d",&instance))!= 1){									
		printf("Error in reading the instance! \n");
		return;
	}
	
	for (int i = 1; i < 101; i++){
		for (int x = 0; x < 22; x++){
		char title[25];
		sprintf(title,"instancem_n_t1_t2_%d",i);
        FILE *fp = fopen(title,"w");
		//general file base one each instance
		//char instance_char = i + '0';
		for (int j = 1; j < 11; j++){
			//char t1 = '1',t2 = j * 10 +'0';
			for (int k = 1; k < 21; k++){
				//char jobs = k*10 +'0';
				for (int l = 1; l < 21;l++){
					//char mach = l +'0';
					random_instance(i,l,k*10,1,j*10,fp);
					fclose(fp);
				}
			}
		}
	}
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

void slowsort(int jobs[], int lpt_order[],int length){
    int count = 0, order_index = 0;
	while (count != length){
		int max = 0;
		for (int i = 0;  i < length; i++){
			if (jobs[i] > max){
				max = jobs[i];
				order_index = i;
			}
		}
		//printf("max is %d \n",max);
		lpt_order[count] = order_index;
		jobs[order_index] = 0;
		count +=1;
	}	
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
	
}


int lpt(int* times, int lpt_array[],int length,int jobs[],int mach_work[],int mach_num){
	int min = 9999,max = 0;
    int start = mach_work[0];
	//printf("length is 111 %d \n",length);
   // for (int i = 0; i < mach_num; i++){
    //    if (mach_work[i] < start)
    //        start = mach_work[i];
    //}

	int saved[mach_num];
	for (int i = 0; i < mach_num; i++){
		saved[i] = mach_work[i];
	}

	printf("The lpt order are: ");
	for (int i = 0; i < length; i++){
		printf(" %d",lpt_array[i]+1);
	}
	printf("\n");

	
	fprintf(stdout,"Job information: \n");
    int machines_work_list[mach_num][length];
    for (int i = 0; i < mach_num; i++){
        for (int j = 0; j < length; j++){
            machines_work_list[i][j] = 0;
        }
    }



	for (int j = 0; j < length; j++){
        int index = 0;
        for (int i = 0; i < mach_num; i++){
            if(min > mach_work [i]){
                min = mach_work[i];
                index = i;
            }
		}
        for ( int k = 0; k < length; k++){
            if (machines_work_list[index][k] == 0){
                machines_work_list[index][k] = lpt_array[j]+1;
				break;
			}
        }
        fprintf(stdout,"Job %d is processed on A_%d starting %d \n",lpt_array[j]+1,index+1,mach_work[index]);
        mach_work[index] += jobs[lpt_array[j]];
		min = 999;
		//printf("index is %d the first is %d and second is %d \n",index,lpt_array[j],jobs[lpt_array[j]]);
        }


    fprintf(stdout,"Machine information: \n");
    for (int i = 0; i < mach_num; i++){
		fprintf(stdout,"A-%d is process ",i+1);
		for (int j = 0; j < length; j++){
			if (machines_work_list[i][j] > 0){
				fprintf(stdout," job %d at %d",machines_work_list[i][j],saved[i]);
				saved[i] += jobs[lpt_array[j]];
			}
		}
		fprintf(stdout,".\n");
    }
    for (int i = 0; i < mach_num; i++){
        if (mach_work[i] > max)
            max = mach_work[i];
    }
	
	fprintf(stdout,"The job processing time is [%d , %d], and the makespan is %d \n",start,max,max - start);
	return max;
}



void johnson_sort(int jobs[][2], int john_order[],int length,int job_list[]){
	int saved[length][3];
	int init_array[length][4];
	int min = 999,index = 0, b_or_c = 0;
	for (int i = 0; i < length; i++){
		//printf("joblist is %d \n",job_list[i]);
		for (int j = 0; j < 4;j++){
			init_array[i][j] = 0;
		}
		for (int j = 0; j < 2; j++){
			saved[i][j] = 0;
		}
	}

	for (int i = 0; i < length; i++){
		for (int j = 0; j < 2;j++){
			saved[i][j] = jobs[job_list[i]][j];
		}
		saved[i][2] = job_list[i]+1;
		//printf("saved is %d %d and %d\n",saved[i][0],saved[i][1],saved[i][2]);
	}
			
			
	int bindex = 0, cindex = 0,jindex = 0;
	for (int k = 0; k < length; k++){
		for (int i = 0; i < length; i++){
			for (int j = 0; j < 2;j++){
				if(saved[i][j] < min){
					min = saved[i][j];
					bindex = i;
					cindex = j;
					if (j == 0)
					{
						jindex = j+1;
						index = i;
						b_or_c = 1;
					}
					else
					{
						jindex = 0;
						index = i;
						b_or_c = 2;
					}
				
				}		
			}
		}
		//printf("min is %d");
		saved[bindex][jindex] = 9999;
		saved[bindex][cindex] = 9999;
		min = 999;
		fill(saved[index],init_array,b_or_c,length,cindex);
	}
	for (int i = 0; i < length; i++){
		john_order[i] = init_array[i][2];
		//printf("plase work %d \n",init_array[i][2]);
	}



}

void fill(int input[],int list[][4],int group,int length,int cindex){
	int	b_w = 0;
	b_w = length - 1;
	
	//printf("the pramater is %d \n",input[2]);
	
	if (cindex == 0){
		for (int i = 0; i < length; i++){
			if (list[i][0] == 0){
				list[i][0] = input[0];
				list[i][1] = input[1];
				list[i][2] = input[2];
				list[i][3] = group;
				//printf("1111 is %d and group is %d\n",list[i][2],group);
				return;
			}
		}
	}

	else if (cindex == 1){
		for (int i = b_w; i >= 0; i--){
			if (list[i][0] == 0){
				list[i][0] = input[0];
				list[i][1] = input[1];
				list[i][2] = input[2];
				list[i][3] = group;
				//printf("222 is %d and group is %d\n",list[i][2],group);
				return;
			}			
		}
	}
	

}

int johnson(int *start_time,int johnson_order[],int work[],int work_num,int work_time[][2]){
	printf("The johnson's oder are: ");
	int b_work[work_num][2];
	int c_work[work_num][2];
	for (int i = 0; i < work_num;i++){
		printf(" %d",johnson_order[i]);
	}
	printf("\n");
	work[0] = *start_time;
	work[1] = work_time[johnson_order[0]-1][0]+ *start_time;
	int saved[2];
	saved[0] = work[0];
	saved[1] = work[1];
	fprintf(stdout,"job information : \n");
	fprintf(stdout,"job %d is processed on B starting %d, on c starting %d \n",johnson_order[0],saved[0],saved[1]);
	b_work[0][1] = saved[0];
	b_work[0][0] = johnson_order[0];
	c_work[0][1] = saved[1];
	c_work[0][0] = johnson_order[0];

	for (int i = 0; i < work_num-1;i++){
		//printf("The adding time are %d and %d \n",work_time[johnson_order[i]-1][0],work_time[johnson_order[i]-1][1]);
		saved[0] += work_time[johnson_order[i]-1][0];
		saved[1] += work_time[johnson_order[i]-1][1];
		if (saved[1] < saved[0] + work_time[johnson_order[i+1]-1][0] && i < work_num)
			saved[1] = saved[0] + work_time[johnson_order[i+1]-1][0]; 
		fprintf(stdout,"job %d is processed on B starting %d, on c starting %d \n",johnson_order[i],saved[0],saved[1]);
		b_work[i+1][1] = saved[0];
		b_work[i+1][0] = johnson_order[i+1];
		c_work[i+1][1] = saved[1]; 
		c_work[i+1][0] = johnson_order[i+1];
	}
	saved[0] += work_time[johnson_order[work_num-1]-1][0];
	saved[1] += work_time[johnson_order[work_num-1]-1][1];
	
	fprintf(stdout,"Machine information : \n");
	fprintf(stdout,"B process ");
	for (int i = 0; i < work_num; i++){
		fprintf(stdout," job %d at %d ",b_work[i][0],b_work[i][1]);
	}
	fprintf(stdout,"\n");
	fprintf(stdout,"A process ");
	for (int i = 0; i < work_num; i++){
		fprintf(stdout," job %d at %d ",c_work[i][0],c_work[i][1]);
	}
	fprintf(stdout,"\n");
	fprintf(stdout,"The job processing time is [%d , %d], and the makespan is %d \n",*start_time,saved[1],saved[1] - *start_time);
	if (saved [0] > saved[1])
		return saved[0];
	return saved[1];
	
}