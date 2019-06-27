#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 50
#define MAX_CH 10

void string_clear(char a[]){

	int i=0;
	for(i=0; a[i]!=0; i++){
		a[i]=0;
	}
}
void clear_newline(char line[]){

	int i;
	for(i=0; (line[i]!=0 && line[i]!='\n'); i++);
	line[i]=0;
}

int gate_type(char a[]){

	int result=0;
	result=strcmp(a,"AND");
	if(result==0){return 1;}

	result=strcmp(a,"OR");	
	if(result==0){return 2;}

	result=strcmp(a,"NOT");	
	if(result==0){return 3;}

	result=strcmp(a,"FLIPFLOP");	
	if(result==0){return 4;}
}

typedef struct gate{/*Gate struct*/
	
	char gate_name[MAX_CH];
	int gate_type;/*kapinin türü*/
	int one_input;
	int second_input;
	int output;
	struct gate *left;
	struct gate *right;

}gate;

int tree_output(gate *head){/*Find output by scanning tree*/

	int output;
	if(head->gate_type==0){

		return head->output;
	}

	if(head->left!=0 && head->right!=0){

		if(head->gate_type==1){/*And*/
			
		}
		else if(head->gate_type==2){/*Or*/

		}
		else if(head->gate_type==3){/*Not*/

		}
		else if(head->gate_type==4){/*Flipflop*/

		}

	}

	else{



	}

	return output;

}
/*Node sayisini bulup döndürür*/
int number_of_node(){

	FILE *input;
	char line[MAX_LINE+1];
	int i,counter_node=0;

	input=fopen("circle.txt","r");
	fgets(line,MAX_LINE+1,input);

	for(i=0; (line[i]!=0 && line[i]!='\n'); i++){/*First line is scanned*/
		if(line[i]==' '){
			counter_node++;
		}
	}

	while(fgets(line,MAX_LINE+1,input)!=0){
		counter_node++;
	}

	fclose(input);
	return counter_node;
}

gate **circuit_tree(){/*Agaci oluşturan fonksiyon*/

	FILE *input;
	gate **circuit_p;/*struct adreslerini içeren dizi*/
	gate *temp_struct;
	char line[MAX_LINE+1],gate_name[MAX_LINE+1],gate_type_str[MAX_LINE+1];/*string almak için geçiciler*/
	int i=0,j=0,k=0,struct_index=0,arr_index=0,gate_type_value,control_gate_name=10,left_rigt_control=0;


	input=fopen("circle.txt","r");

	circuit_p=(gate**)malloc((number_of_node())*sizeof(gate));

	fgets(line,MAX_LINE+1,input);
	clear_newline(line);

	for(i=0; line[i]!=' '; i++){/*INPUT stringini atla*/
		j++;
	}
	j++;

	for(i=j; line[i]!=0; i++){/*ilk satırdaki input nameleri atayan fonksiyon*/

		if(line[i]==' '){
			circuit_p[struct_index]=(gate*)malloc(sizeof(gate));
			strcpy(circuit_p[struct_index]->gate_name,gate_name);
			struct_index++;
			arr_index=0;
			string_clear(gate_name);
		}

		else{

			gate_name[arr_index]=line[i];
			arr_index++;
		}

		if (line[i+1]==0)
		{
			circuit_p[struct_index]=(gate*)malloc(sizeof(gate));
			strcpy(circuit_p[struct_index]->gate_name,gate_name);
			struct_index++;
			arr_index=0;
			string_clear(gate_name);

		}
	}

	for (i=0; i<struct_index; i++)
	{
		circuit_p[i]->gate_type=0;/*input type which number is 0*/
	}
	
	string_clear(line);

	while(fgets(line,MAX_LINE+1,input)!=NULL){/*Diğer satırları okutan fonksiyon->and-1,or-2,not-3,flipflop-4*/
		
		clear_newline(line);

		circuit_p[struct_index]=(gate*)malloc(sizeof(gate));/*işlem için aalan ayrıldı node için*/

		j=0;
		string_clear(gate_type_str);

		for(i=0; line[i]!=' '; i++){/*satır başındaki ifade okunup kapı türü structun kapı türü bilgisine atandı.*/
			gate_type_str[i]=line[i];
			j++;
		}

		j++;
		circuit_p[struct_index]->gate_type=gate_type(gate_type_str);/*Atandı kapı türü bilgisi*/

		string_clear(gate_name);

		for(i=j; line[i]!=' '; i++){/*Kapı ismi atandı*/
			gate_name[i]=line[i];
			
		}
		i++;
		j=i;
		strcpy(circuit_p[struct_index]->gate_name,gate_name);
		string_clear(gate_name);
		//-----------
		arr_index=0;
		control_gate_name=10;
		left_rigt_control=0;
		for(i=j; line[i]!=0; i++){

			if(line[i]==' '){

				for(k=0; k<struct_index; k++){
					control_gate_name=strcmp(circuit_p[k]->gate_name,gate_name);	
					if(control_gate_name==0){
						circuit_p[struct_index]->left=circuit_p[k];
						left_rigt_control=1;
						control_gate_name=10;
					}
				}

				arr_index=0;
			}
			else{
				gate_name[arr_index]=line[i];
				arr_index++;
			}
			if(line[i+1]==0){

				if(left_rigt_control==1){

					for(k=0; k<struct_index; k++){

						control_gate_name=strcmp(circuit_p[k]->gate_name,gate_name);
						if(control_gate_name==0){
							circuit_p[struct_index]->right=circuit_p[k];
							control_gate_name=10;
						}
					}
				}

				else{
					for(k=0; k<struct_index; k++){

						control_gate_name=strcmp(circuit_p[k]->gate_name,gate_name);
						if(control_gate_name==0){
							circuit_p[struct_index]->left=circuit_p[k];
							control_gate_name=10;
						}
					}
				}
			}
		}
		//------------------
		struct_index++;
		string_clear(line);
	}
	
	return circuit_p;
}


int main(){
	
	/*File opening*/
	FILE *input,*circuit,*output;
	input=fopen("input.txt","r");
	circuit=fopen("circuit.txt","r");
	output=fopen("output.txt","w");
	/*--------*/
	gate **p;
	gate *head;
	char input_line[MAX_LINE];
	int i,input_counter,*input_arr;
		
	/*while(fgets(input_line,MAX_LINE+1,input)!=0){/*input.txt line loop//
		
		input_counter=0;
		for(i=0; input_line[i]!='\n'; i++){
			if(input_line[i]!=' '){
				input_counter++;
			}
		}

		input_arr=malloc(input_counter*sizeof(int));
		input_counter=0;
		for(i=0; input_line[i]!='\n'; i++){
			if(input_line[i]!=' '){
				input_arr[input_counter]=input_line[i];
				input_counter++;
			}
			
		}
	}*/
	
	p=circuit_tree();
	head=p[8];
	printf("%d",p[1]->gate_type);
	return 0;
}
