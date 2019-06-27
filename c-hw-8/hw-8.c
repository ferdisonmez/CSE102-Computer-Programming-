#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#define a 5
#define b 5

void scan(int arr[a+2][b+2],int row,int col,int count){
	
	if(col>=1 && col<b+1 && arr[row][col]==1 && arr[row][col+1]!=0){   // column move forward
		arr[row][col]=count;
		scan(arr,row,col+1,count);
	} 
	if(row>=1 && row<a+1 && arr[row][col]==1 && arr[row+1][col]==1){	 // row move forward
		arr[row][col]=count;
		scan(arr,row+1,col,count);
	}
	if(col>=1 && col<b+1 && arr[row][col]==1 && arr[row][col-1]==1){		// columns are hovered back	
		arr[row][col]=count;
		scan(arr,row,col-1,count);
	}
	if(row>=1 && row<a+1 && arr[row][col]==1 && arr[row-1][col]==1){		//row are hovered back
		arr[row][col]=count;
		scan(arr,row-1,col,count);
	}
	if(arr[row][col]==1){
		arr[row][col]=count;
		scan(arr,row,col,count);
	}	
}
int main()
{
	FILE *input,*output;
	input=fopen("input.txt","r");
	output=fopen("output.txt","w");
	int hx[a+2][b+2]={0},i=0,num=0,j=0,count=2;
	const rlim_t kStackSize = 16 * 1024 * 1024;  // min stack size = 16 MB
	struct rlimit rl;
	int result;
	result = getrlimit(RLIMIT_STACK, &rl);
if (result == 0)
{
	if (rl.rlim_cur < kStackSize)
	{
	rl.rlim_cur = kStackSize;
	result = setrlimit(RLIMIT_STACK, &rl);
		if (result != 0)
		{

		}
	}
}
	fscanf(input,"%d",&num);
	for (i=1;i<a+1;i++)		//file read read hx saved
	{
		for (j=1;j<b+1;j++)
		{			
			fscanf(input,"%d",&hx[i][j]);			
			if(hx[i][j]>num){
				(hx[i][j]=1);
			}
			else{
				(hx[i][j]=0);
			}			
		}
	}
	fclose(input);
	for (i=0;i<a+2;i++)		
	{
		for (j=0;j<b+2;j++)
		{		
			if(hx[i][j]==1){
				scan(hx,i,j,count);
				count++;				
			}			
		}	
	}
fprintf(output,"number of island=%d\n",count-3);			// number of islands
	count=2;
	for (i=0;i<a+2;i++)		
		{
			for (j=0;j<b+2;j++)
			{	
				if(hx[i][j]==count){
					fprintf(output,"x_coordinate%d y_coordinate%d\n",i,j);
					scan(hx,i,j,count);	
					count++;				
				}
				
			}	
	}	
	return 0;
}
