#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define YUZ 101
typedef struct{						/*  new type defined    */
	char isim[YUZ];
    double fiyat;
	int sayisi;	
}object;
int say(char arr[]){				/* gaps counted */
	int i=0,y=0;
	while(arr[i]!='\0'){		
		if(arr[i]==' '){
			y++;			
		}		
		i++;
	}	
	return y;	
}
char temizle(char ad[]){			/* \ n statements have been cleared   */
	int i=0;
	while(ad[i]!='\0'){
		
		if(ad[i]=='\n'){
			ad[i]='\0';
		}
		
		i++;	
	}
	return *ad;	
}

double f(object *name,char pre[]){
	object *blank=(object*)malloc(sizeof(object));		/* variables defined  */
	object *nesne;
	char sayi[YUZ],karakter[YUZ],ch;	
	int len=0,m=0,count=0,c=0,d=0,subset=0,y=0,yas=0;
	int i=0,j=0,k=0,sayac=0;
	int d1=0;
	double d2=0,result=0;	
	
		if(pre[0]==0){
		printf("define %s\n",name->isim);			
		}	
		fgets(name->isim,YUZ,stdin);
	    temizle(name->isim);

	while(name->isim[c]!='\0'){							/* deletes excess spaces */
		
			if(name->isim[c] ==' '){
		 		int temp=c+1;
	 			if(name->isim[temp]!='\0'){
	 		
					while(name->isim[temp]==' ' && name->isim[temp]!='\0'){
					
						if(name->isim[temp]==' '){
						c++;
						}					
						temp++;															
					}	 		
	 		
		 		}
							
			}
			blank->isim[d]=name->isim[c];
			c++;
			d++;								
	}
	blank->isim[d]='\0';			
	len=strlen(blank->isim);
	for(m=0;m<len;m++){									/* looks at the numbers in   */	
	
            if(blank->isim[m]>= 46 && blank->isim[m]<= 57)    
            {
                  count++;
            }
		
	}
	if(count==len){							         /* if only number        */
		sscanf(blank->isim,"%lf",&d2);
		return d2;
	}		
	else if(count!=len){							 /* no number */
		yas=(say(blank->isim)+1)/2;
		nesne=(object*)malloc(sizeof(object)*yas);    /* allocates new space        */		
		while(blank->isim[i]!='\0'){												
			k=0;
			j=0;
			sayi[0]=0;
			karakter[0]=0;						
			while(blank->isim[i]!=' ' && blank->isim[i]!='\0'){
				sayac=subset/2;				
				if(blank->isim[i]>=46 && blank->isim[i]<=57 && blank->isim[i]!='\0'){	/* looks at the numbers  */				
					sayi[k]=blank->isim[i];					
					k++;
					sayi[k]=0;
					if(blank->isim[i+1]>=48 && blank->isim[i+1]<=57){	
											
					}					
					else{						
					sscanf(sayi,"%d",&d1);					
					nesne[sayac].sayisi=d1;
					subset++;
				
					}																			
				}				
				else if((blank->isim[i]>=65 && blank->isim[i]<=90) || (blank->isim[i]>=97 && blank->isim[i]<=122)&& blank->isim[i]!='\0') {	/*  looks at the letter */
					ch=blank->isim[i];					
					nesne[sayac].isim[j]=ch;			
					j++;
					nesne[sayac].isim[j]=0;
					if(blank->isim[i+1]==' '){
						subset++;
					}
																		
				}
					
					i++;							   			 																				
			}
				if(blank->isim[i]=='\0'){
					break;
				}
				
			i++;
																																																																																										
		}
		free(blank);		/* clears areas   */
											
	for(y=0;y<yas;y++){									/* function calls    */			
	result+=f(&nesne[y],pre)*nesne[y].sayisi;		
	}
	
	free(nesne);			/* clears areas   */
	return result;									
	}				
}

int main(){
	char name[YUZ]={0};
    object b;
    b.sayisi=1;
    printf("Name the object\n");
	fgets(b.isim,YUZ,stdin);			
	temizle(b.isim);

	printf("%lf",f(&b,name));		/* screen print   */
 
	return 0;
}
