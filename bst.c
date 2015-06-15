#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel.h"
#include <unistd.h>
#include <sys/param.h>
#define arraysize 256000 
#include <time.h>
#define NSECPERSEC 1000000000L
/* Correctly extract the number of nanoseconds from the two time structures */
long int get_nanosecs( struct timespec start_time, struct timespec end_time) {
   long int nanosecs;
   if ((end_time.tv_nsec-start_time.tv_nsec)<0) nanosecs =
      ((((long int) end_time.tv_sec- (long int) start_time.tv_sec )-1)*NSECPERSEC ) +
      ( NSECPERSEC + (long int) end_time.tv_nsec - (long int) start_time.tv_nsec) ;
   else nanosecs =
      (((long int) end_time.tv_sec- (long int) start_time.tv_sec )*NSECPERSEC ) +
      ( (long int) end_time.tv_nsec - (long int) start_time.tv_nsec );
   return nanosecs;
}
typedef struct Node {

        int data;
        struct Node* left;
        struct Node* right;


}treenode;

treenode* insert(treenode* node,int data)
{
        treenode* current;
        if(node == NULL)
        {
                current = (treenode*)malloc(sizeof(treenode));
                current->data=data;
                current->left= NULL;
                current->right= NULL;
                return current;
        }

        if(data < node->data)
                node->left=insert(node->left,data);
        else 
                node->right=insert(node->right,data);
        return (node);
}
void print(treenode* root)
{
        if(root==NULL)
           return;
        print(root->left);
        printf("%d\n",root->data);
        print(root->right);

}

int main(int argc, char* argv[]) {

        int a[arraysize],output[arraysize]={2},output1[arraysize]={2};
        int i,j,k,l,m,n;
        struct timespec start_time, end_time;
	struct timespec start_time1, end_time1;
	double nanosecs, nanosecs1;
        for(i=0;i<arraysize;i++)
        {
                a[i]=(rand() % 10000) +1;
        }
        
        treenode *ptr=NULL;
        

        for(j=0;j<arraysize;j++)
        {
                ptr=insert(ptr,a[j]);
        }
	//print(ptr);
    	int b[arraysize];
	for(k=0;k<arraysize;k++)
        {
                b[k]=(rand() % 10000) +1;
        }
	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start_time);	
	Launch_params_t lparm={.ndim=1, .gdims={arraysize}, .ldims={256}};
        Find(ptr,output,b,lparm);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end_time);
	nanosecs = get_nanosecs(start_time,end_time);
	printf("HSA : %f\n",(float)nanosecs);
	/*
	for(l=0;l<arraysize;l++)
	{
		if(output[l]==1)
		printf("%d is in bst\n",b[l]);
		}*/
	
	 clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&start_time1);
	
	for(m=0;m<arraysize;m++)
	{
		struct Node* tmp = ptr ;
		while (tmp != NULL) {

                if (b[m] > tmp->data) {

                        tmp = tmp->right;

                } else if (b[m] < tmp->data){

                        tmp = tmp->left;
                } else{
			output1[m]=1;
                         break;
                }
                
		}	
	}
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end_time1);
	nanosecs1 = get_nanosecs(start_time1,end_time1);
        printf("for loop : %f\n",(float)nanosecs1);	
	
	for(n=0;n<arraysize;n++)
	{
		if(output[n]!=output1[n])
		printf("gg");
	}
        return 0;
}	

