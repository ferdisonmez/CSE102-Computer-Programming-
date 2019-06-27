#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 100
#define MAX_CH 250

void clear_space(char a[]){
	
	int i,j;	
	int counter_start=0;
	int counter_end=0,len;
	char temp[MAX_CH];
	i=0;
	while(a[i]!='\n' && a[i]!=0){
		i++;
	}
	a[i]=0;
	
	i=0;
	while(a[i]==' '){
		
		counter_start++;
		i++;
	}
	
	if(counter_start!=0){
		j=0;
		while(a[i]!=0){
			a[j]=a[i];
			j++;
			i++;
		}
		a[j]=0;
	}
	len=strlen(a);
	len=len-1;
	
	while(a[len]==' '){
		counter_end++;
		len--;
	}
	a[len+1]=0;
		
}

struct part{
	int number;
	double prime;
	char *part_name;
};

int check_string(char a[]){/*This function checks that string is numeric or alphabetic*/
	
	int i=0,counter=0;
	
	for(i=0; a[i]!=0; i++){
		
		if((a[i]>='0' && a[i]<='9') || a[i]=='.'){
			counter++;
		}
	}
	
	if(counter==strlen(a)){
		return 1;
	}
	else{
		return 0;
	}
}

int number_of_part(char a[]){/*Finding number of part in a string*/
	
	int i=0,number=0,counter=0;

	while(a[i]!=0){

		for(number=i; a[number]!=' ' && a[number]!=0; number++){ }
		i=number;
		for(number=i; a[number]==' '; number++){ }
		i=number;
		counter++;	
	}
	return counter/2;
}

double price_object(struct part *p,struct part *s){
	
	int a,e,f,h,i,state,value_str,counter_str=0;
	double result=0,number_part,prime,value_part;
	char temp_str_value[MAX_LEN],str[MAX_CH],*p_temp;
	struct part *part_p;
	
	if(s==0){
		printf("Define %s?:\n",p->part_name);
	}
	
	else{	
	printf("Define %s in %s?:\n",p->part_name,s->part_name);
	}
	
	fgets(str,MAX_CH+1,stdin);
	clear_space(str);
	state=check_string(str);/*Checking string is numeric or alphabetic*/
	
	if(state==1){/*If user enter only number. This value is prime of part*/
		
		sscanf(str,"%lf",&p->prime);	
	}
	
	else if(state==0){/*If user enter number and part name*/
		
		number_part=number_of_part(str);
		part_p=(struct part*)calloc(number_part,sizeof(struct part));
		h=0;
		
		for(i=0; i<number_part; i++){/*This loop creates structures by using string, and assignes information to these structures*/
		
			a=0;
			for(e=h; str[e]!=' ' ; e++){/*Number of the part is assigned to  number value of this structure */
				temp_str_value[a]=str[e];
				a++;
			}
			
			h=e;
			sscanf(temp_str_value,"%d",&part_p[i].number);
			
			for(f=0; temp_str_value[f]!=0; f++){
				temp_str_value[f]=0;
			}
			
			for(e=h; str[e]==' '; e++){/*Skip spaces*/}		
			h=e;
			
			counter_str=0;
			for(e=h; (str[e]!=' ' && str[e]!=0); e++){
				counter_str++;
			}
			
			part_p[i].part_name=(char*)calloc(counter_str+1,sizeof(char));
			e=h;
			a=0;
			for(e=h; (str[e]!=' ' && str[e]!=0); e++){
				part_p[i].part_name[a]=str[e];
				a++;
			}
			
			h=e;
			for(e=h; str[e]==' '; e++){/*Skip spaces*/}	
			h=e;		
		}
	}

	if(state==0){
		
		for(i=0; i<number_part; i++){
			
			result=result+part_p[i].number*price_object(&part_p[i],p);	
		}
	}
	
	if(state==1){
		
		number_part=p->number;
		prime=p->prime;
		return prime;
	}
	
	for(i=0; i<number_part; i++){
		
		p_temp=part_p[i].part_name;
		free(p_temp);	
	}
	
	free(part_p);
	return result;	
}

int main(){
	
	struct part object,*empty=0;
	char part_name[MAX_LEN];
	
	printf("Name the object:\n");
	gets(part_name);/*Takes object name*/
	object.part_name=&part_name[0];
	object.number=1;
	printf("Total cost of %s is %.2lf",object.part_name,price_object(&object,empty));
	
	return 0;
}

