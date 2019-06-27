#include <stdio.h>
#include <string.h>
#define LEN 250
int tree_ciz(char dizi[LEN],int gosterge,int tut,FILE *dosya){
	int temp;
	temp=tut;
	if(dizi[0]=='\0'){				/* end point of recursive function */
		return 0;
	}
	else if(dizi[0]=='('){			/*  (	counting */
		tut++;
	}
	else if(dizi[0]==')'){			/*  )	counting */
		tut--;
	}
	else if(dizi[0]==','){			/* change to a new line if a comma  */
		fprintf(dosya,"\n");
		gosterge=0;
	}
	else{
		if(gosterge==0){
			while(temp>0){
				fprintf(dosya,"-");		/*  -  put until the (sign     */
				temp--;
			}
		}
		fprintf(dosya,"%c",dizi[0]);
		gosterge=1;
	}
tree_ciz(dizi+1,gosterge,tut,dosya);	/* callback function  */

return 0;
}
int main(){
FILE *input,*output;
input=fopen("input.txt","r");			/* file opening process */   
output=fopen("output.txt","w");				/* file opening process */ 
char text[LEN],ab[LEN];						/* define variables  */
int a,i=0,byrk=0,cizgi=0,j=0,b=0,k=0;		/* define variables  */
	while(a!=EOF){
		a=fscanf(input,"%c",&text[i]);
		if (a==EOF)
		{
			while(text[i]!=' '){		/* the process of deleting trailing spaces */
				i--;
			}
			i++;		
			text[i]='\0';
			break;
		}
		i++;
	}
for(j=0;text[j]!='\0';j++){		/*deletion of leading spaces */
	if(text[j]!=' '){
		break;
	}
}
for (k=j;text[k]!='\0';k++){	/*deletion of leading spaces */
	ab[b]=text[k];
	b++;
}
	ab[b]='\0';
tree_ciz(ab,byrk,cizgi,output);
fclose(input);

	return 0;
}
