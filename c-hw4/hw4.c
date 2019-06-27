#include <stdio.h>
#include <math.h>
#include <string.h>
#define BIN 1000
#define YUZ 100
void birlestir(char a[],double x,FILE *dosya){
	int i=0,j=0,k=0,us=0,f=0,h=0,m=0,z=0,count=0;			/*  variables defined  */
	char isaret[BIN],str[BIN],b=0;
	double d1=0,sonuc1=0,sonuc2=0,d3=0;
	int d2=0;
	while(a[i]!='\0'){			
		if(a[i]=='+' || a[i]=='-'){			/* control   + -     */
			k=0;
			while(j<i){

				isaret[k]=a[j];
				k++;
				j++;				
			}
			isaret[k]='\0';					/*   assignment of the array   */
			sscanf(isaret,"%lf",&d1);					
				h=0;
				while(isaret[h]!='\0'){		/*  control the array end     */
					if(isaret[h]=='x'){
						break;
					}
					h++;					
					if(isaret[h]=='\0' && isaret[h]!='x'){
						
						sscanf(isaret,"%lf",&d3);
						sonuc1=sonuc1+d3;							
					}					
				}
				while(isaret[z]!='\0'){
					if(isaret[z]=='^'){				/*  control the sign    */      
						count++;					
					}					
						z++;				
				}
		if(count==0){								/* control the sign    */

					if(isaret[1]=='x' && isaret[0]=='+'){
						d1=1.0;
					}
					else if(isaret[0]=='-' && isaret[1]=='x'){
						d1=-1.0;
					}
					else if(isaret[0]=='x'){
						d1=1.0;
					}
					sonuc1=sonuc1+(d1*x);
			    }

		else{		
				f=0;
			while(isaret[f]!='\0'){					/*  control the array end      */
				
				if(isaret[f]=='^'){					/* control the sign    */
					f++;
					b=0;
					while(isaret[f]!='\0'){

						str[b]=isaret[f];					
						b++;
						f=f+1;
					}
					sscanf(str,"%d",&d2);
				
					break;
				}
				else{
					f++;
				}

			}
					if(isaret[1]=='x' && isaret[0]=='+'){
						d1=1.0;
					}													/*control the coefficient   */

					else if(isaret[0]=='-' && isaret[1]=='x'){
						d1=-1.0;
					}												   /*control the coefficient   */
					else if(isaret[0]=='x'){
						d1=1.0;
					}

					sonuc1=sonuc1+d1*pow(x,d2);
		}							
				str[0]=0;
				isaret[0]=0;				
		}			
		i++;			
			if(a[i]=='\0'){						/* control the array end   */
				count=0;
				d1=0;
				d2=0;
				i--;				
				k=0;
			while(j<=i){		
				isaret[k]=a[j];			
				k++;
				j++;								
			}			
			isaret[k]=0;		
			sscanf(isaret,"%lf",&d1);			/* read numbers in array     */
				z=0;
				while(isaret[z]!='\0'){
					if(isaret[z]=='^'){
						count++;					
					}					
						z++;
				}
		if(count==0){  										/*control the coefficient   */
					if(isaret[1]=='x' && isaret[0]=='+'){
						d1=1.0;
					}

					else if(isaret[0]=='-' && isaret[1]=='x'){
						d1=-1.0;												
					}
					else if(isaret[0]=='x'){
						d1=1.0;
					}
					sonuc2=sonuc2+(d1*x);		/* result calculated      */
				}

		else{		
				f=0;
			while(isaret[f]!='\0'){				
				if(isaret[f]=='^'){
					f++;
					b=0;
					while(isaret[f]!='\0'){

						str[b]=isaret[f];					
						b++;
						f=f+1;
					}
					sscanf(str,"%d",&d2);				
					break;
				}
				else{									/*control the coefficient   */
					f++;
				}

			}
					if(isaret[1]=='x' && isaret[0]=='+'){				/*control the coefficient   */
						d1=1.0;
					}
					else if(isaret[0]=='-' && isaret[1]=='x'){
						d1=-1.0;
					}
					else if(isaret[0]=='x'){
						d1=1.0;
					}
					f=0;
			while(isaret[f]!='\0'){			
				if(isaret[f]=='^'){
					f++;
					b=0;
					while(isaret[f]!='\0'){
					str[b]=isaret[f];					
					b++;
					f=f+1;
				}
					sscanf(str,"%d",&d2);				
					break;				
				}
				else{
					f++;
				}
			}
			sonuc2=sonuc2+d1*(pow(x,d2));			/* result calculated        */
		}			
				h=0;
				while(isaret[h]!='\0'){
					if(isaret[h]=='x'){
						break;
					}
					h++;
					if(isaret[h]=='\0' && isaret[h]!='x'){						
						sscanf(isaret,"%lf",&d3);
						sonuc2=sonuc2+d3;						
					}					
				}			
				i++;
				str[0]=0;					
		}		
		isaret[0]=0;				
	}		
	fprintf(dosya,"%.2lf\n",sonuc1+sonuc2);				/* result calculated        */
}
	int main(){
	FILE *values,*polynomial,*evaluations;				/*  variables defined  */
	values=fopen("values.txt","r");
	polynomial=fopen("polynomial.txt","r");				/*  read the values ??in the file  */	
	evaluations=fopen("evaluations.txt","w");
	int a,i=0,b,j=0,k=0,c=0,temp=0,d=0;
	double val[YUZ];
	char kar[BIN]={0},text[BIN];
	
	while(b!=EOF){
		b=fscanf(polynomial,"%c",&kar[j]);				/* values transferred to array   */
		if(b=='\n'){
			break;
		}					
		j++;
	}
		while(kar[c]!='\0'){								/*gaps in file deleted  */
			if(kar[c]==' '){
				temp=c;
				if(kar[temp]!='\0'){

					while(kar[temp]==' ' && kar[temp]!='\0'){

						if(kar[temp]==' '){
							c++;
						}
						temp++;
					}
				}
			}
			text[d]=kar[c];			
			c++;
			d++;

		}
		text[d]='\0';
		while(a!=EOF){
			a=fscanf(values,"%lf",&val[i]);			/* values transferred to array  */
			if(a==EOF){
			break;
		}				
			birlestir(text,val[i],evaluations);		/*called the function  */
			i++;
	}
	return 0;
}
