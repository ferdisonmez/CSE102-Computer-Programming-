#include<stdio.h>
#include<string.h>
#define SUTUN 250
#define SATIR 100
void dikey_bak(char d[],int x,int z,char e[][SUTUN],int satir,FILE *output1){	/* text is scanned vertically in this function  */
		int m=0,t=0,k=0,i=satir;
			for(t=0;t<z-1;t++){
			    for(m=0;m<i;m++){				
				   k=0;
				   if(e[m][t]==d[k]){				/*checks the first letter */
					 k++;
						while(e[k+m][t]==d[k]){		/* checks next letter */
							k++;				
							if(k==x){
							fprintf(output1,"%s (%d,%d) vertical\n",d,m+1,t+1);	/* printed to file */
							break;

							}
						}
				}
			}	
		}
}
void yatay_bak(char d[],int x,char e[][SUTUN],int satir,int sutun,FILE *output1){	/*  text is scanned horizontal in this function    */
	int i=satir,j=0,k=0,a=x;		
		for(j=0;j<sutun;j++){
				k=0;
				if(e[i][j]==d[k]){				/*checks the first letter */
					k++;
					while(d[k]==e[i][k+j]){		/* checks next letter */
					k++;							
						if(k==a){
							fprintf(output1,"%s (%d,%d) horizontal\n",d,i+1,j+1);	/* printed to file */
							break;					
						}
					}
				}
		}			
}
int main(){
	FILE *input,*output,*output1;
	char x[SATIR][SUTUN]={0};									/* 0 assigned to the first values of the array */
	char y[11]={0};												/* 0 assigned to the first values of the array */
	int i=0,j=0,h=0,c=0,sutun_sayac=0,a=0,b,s=0,f=0,enb=0;		
	input=fopen("input1.txt","r");
	output=fopen("input2.txt","r");									/* opened files */
	output1=fopen("output.txt","w");
		while(a!=EOF){
				a=fscanf(output,"%c",&x[i][j]);						/*moved to array in the file */
				if(x[i][j]=='\n'){
					i++;											/* lines counted  */
					j=0;	
				}
				else{					
					j++;					
				}			
		}	
	while(b!=EOF){

		b=fscanf(input,"%s",y);							/* moved to array in the file */
			h++;
			if(b==EOF){
				break;
			}			
		for(s=0;s<i;s++){
			sutun_sayac=0;
				for(c=0;x[s][c]!='\0';c++){				/* number of letters in column */
				sutun_sayac++;
					if(sutun_sayac>enb){				/* largest row*/
					enb=sutun_sayac;
					}
			}
			f=strlen(y);								/*size of the lines */
			yatay_bak(y,f,x,s,sutun_sayac-1,output1);	/*function called    */
		}			
			a=strlen(y);								/*size of the lines */
			dikey_bak(y,a,enb,x,i,output1);				/*function called    */
	}
	return 0;	
}	
