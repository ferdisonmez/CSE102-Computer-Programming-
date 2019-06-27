#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define IKIYUZ 250
typedef enum{
	and = 1,
	or = 2,
	not = 3,
	flipflop = 4,
}type;
typedef struct gate{		
	int type;
	char input1[10];
	char input2[10];
	int output;
	char name[10];
	int index1;
	int index2;
}gate;
void temiz(char h[]){
	int i=0;
	while(h[i]!='\n' && h[i]!=0){
		if(h[i]==' '){
			h[i]='\0';
		}
		i++;
	}
	h[i]=0;
}
int hesap(gate *g,gate arr[]){
	int result;
	if(g->type==-2){
		return g->output;
	}
	else if(g->type==1){
		result=hesap(&arr[g->index1],arr) && hesap(&arr[g->index2],arr);
	}
	else if(g->type==2){
		result=hesap(&arr[g->index1],arr) || hesap(&arr[g->index2],arr);
	}
	else if(g->type==3){
		result=!(hesap(&arr[g->index1],arr));
	}
	else if(g->type==4){
	}
	return result;
}
int main(){

	FILE *fp,*fp1,*output;
	int i=0,j=0,row=0,column=0,k=0,say=0;
	int columnindex = 0,counter = 0,status=0;
	char num,ch;
	char str[IKIYUZ];
	char strTemp[IKIYUZ];
	struct gate *gateArr;
	char *token;
	int columnNumber=0;
	int rowNumber=0;
	char transactionName[20];
	int bx;
	struct gate *pointer;
	output=fopen("output.txt","w");
	fp1 = fopen("circuit.txt","r");
	while(fscanf(fp1,"%c",&ch) != EOF){		
		if(ch == '\n'){
			counter++;
		}
	}
	fclose(fp1);
	fp1 = fopen("circuit.txt","r");
	fgets(str, IKIYUZ, fp1);
	while(str[i]!='\n'){
			if(str[i]==' ')
			say++;
	    	i++;	
		}
		fclose(fp1);
	gateArr = (struct gate*)malloc((counter+say)*sizeof(gate));		
	fp1 = fopen("circuit.txt","r");
	while (fgets(str, IKIYUZ, fp1)){		
			
		strcpy(strTemp,str);
		token = strtok(str, " \n");  
		strcpy(transactionName,str);
	   	while( token != NULL ) {
	   		if(strcmp(transactionName, "AND")==0 ){		
	   			if(columnNumber == 0){
	   				gateArr[rowNumber-1].type = and;
	   				gateArr[rowNumber-1].output = -1;
	   			}
	   			else if(columnNumber == 1)
	   				strcpy(gateArr[rowNumber-1].name,token);	
	   			else if(columnNumber == 2)
	   				strcpy(gateArr[rowNumber-1].input1,token);	
	   			else if(columnNumber == 3)
	   				strcpy(gateArr[rowNumber-1].input2,token);
		   	}

		   	else if(strcmp(transactionName, "OR")==0){	
		   		if(columnNumber == 0){
	   				gateArr[rowNumber-1].type = or;
	   				gateArr[rowNumber-1].output = -1;
		   		}
	   			else if(columnNumber == 1)
	   				strcpy(gateArr[rowNumber-1].name,token);
	   			else if(columnNumber == 2)
	   				strcpy(gateArr[rowNumber-1].input1,token);
	   			else if(columnNumber == 3)
	   				strcpy(gateArr[rowNumber-1].input2,token);
		   	}

		   	else if(strcmp(transactionName, "NOT")==0){
		   		if(columnNumber == 0){
	   				gateArr[rowNumber-1].type = not;
	   				gateArr[rowNumber-1].output = -1;
		   		}
	   			else if(columnNumber == 1)
	   				strcpy(gateArr[rowNumber-1].name,token);
	   			else if(columnNumber == 2)
	   				strcpy(gateArr[rowNumber-1].input1,token);
		   	}

		   	else if(strcmp(transactionName, "FLIPFLOP")==0){
		   		if(columnNumber == 0){
	   				gateArr[rowNumber-1].type = flipflop;
	   				gateArr[rowNumber-1].output = -1;
		   		}
	   			else if(columnNumber == 1)
	   				strcpy(gateArr[rowNumber-1].name,token);
	   			else if(columnNumber == 2)
	   				strcpy(gateArr[rowNumber-1].input1,token);
		   	}

	      	token = strtok(NULL, " \n");
	      	columnNumber++;
	   	}
	   	
		if(strcmp(transactionName, "INPUT")==0 && columnNumber != 0){
   			token = strtok(strTemp, " \n");
   			while( token != NULL ) {
   				token = strtok(NULL, " \n");
   				if(token != NULL){
   					strcpy(gateArr[rowNumber].name,token);
   					gateArr[rowNumber].type=-2;
   					gateArr[rowNumber].index1=-1;
   					gateArr[rowNumber].index2=-1;
   					gateArr[rowNumber].input1[0]=0;
   					gateArr[rowNumber].input2[0]=0;   				 					
   					(rowNumber)++;
   					
   				}
   			}
	   	}
	   	columnNumber=0;
	   	rowNumber++;
	   
	}
	
	for (i=0; i<counter+say ;i++)
	{	
		for (j = 0; j<i; j++)
		{
				temiz(gateArr[j].name);
				temiz(gateArr[j].input2);	
				if (strcmp(gateArr[j].name,gateArr[i].input1)==0){		
				gateArr[i].index1=j;
				
				}
		
				if (strcmp(gateArr[j].name,gateArr[i].input2)==0){		
				gateArr[i].index2=j;
				
				}
		}		
		
	}
	fp=fopen("input.txt","r");
	while(status!=EOF){
		for (i = 0; i < counter; ++i)
	{
		status=fscanf(fp,"%d",&bx);
		if(status==EOF){
			break;
		}
		gateArr[i].output=bx;
	}
		pointer=gateArr;
		(pointer+counter+say-1);
		fprintf(output,"%d\n",hesap(pointer,gateArr));

	}
	fclose(output);
	fclose(fp);
	fclose(fp1);
	free(gateArr);
	return 0;
}
