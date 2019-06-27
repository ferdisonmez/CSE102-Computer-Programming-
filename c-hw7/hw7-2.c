#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef enum type{
	and = 1,
	or = 2,
	not = 3,
	flipflop = 4,
}type;
struct gate{//her kapinin bilgilerinin tutulan structi
	int type;
	char input1[10];
	char input2[10];
	int output;
	char name[10];
}gate;
struct value{//input.txt bilgileri tutulur
	int inputValue;
	char valueName[10];
}value;

int andOperation(int firstInput, int secondInput);
int orOperation(int firstInput, int secondInput);
int notOperation(int input);
int flipFlopOperation(int firstInput, int secondInput);
int getInputValue(struct gate *gates,struct value *values,int gateCount, int valueCount, char targetInputName[20]);
int gateCalculation(struct gate *gates,struct value *values,int gateCount, int valueCount, int * flipflopVal);
int main(){

	FILE *fp,*fp1;
	int i=0,j=0,row=0,column=0,k=0;
	int columnindex = 0,counter = 0;
	int temp =0;
	char num,ch;
	char str[80];
	char strTemp[80];
	int read;
	struct gate *gateArr;
	struct value *inputArr;
	char *token;
	int columnNumber = 0;
	int rowNumber = 0;
	char transactionName[20];
	int inputIndex = 0;
	int flipflopVal = 0;
	int result = 0;

	fp1 = fopen("circuit.txt","r");
	
	while(fscanf(fp1,"%c",&ch) != EOF){//dosyayi okuyup ne kadar kapi oldugunu buluyorum
		if(ch == '\n'){
			counter++;
		}
	}
	fclose(fp1);
	gateArr = (struct gate*)malloc((counter-1)*sizeof(gate));//kapi sayisina gore struct arrayi olusturuyorum
	fp1 = fopen("circuit.txt","r");
	while (fgets(str, 80, fp1)){//satir satir okunur
		//printf("%s", str);
		strcpy(strTemp,str);
		token = strtok(str, " \n");   //her satiri bosluk ve \n gorene kadar boler
		strcpy(transactionName,str);
		
	   /* walk through other tokens */
	   	while( token != NULL ) {
	   		if(strcmp(transactionName, "AND")==0 ){//hangi kapi oldugunu bulur ve gerekli atamalari yapar
	   			if(columnNumber == 0){
	   				gateArr[rowNumber-1].type = and;
	   				gateArr[rowNumber-1].output = -1;
	   			}
	   			else if(columnNumber == 1)
	   				strcpy(gateArr[rowNumber-1].name,token);//kapinin ismini atar
	   			else if(columnNumber == 2)
	   				strcpy(gateArr[rowNumber-1].input1,token);//inputlari atar
	   			else if(columnNumber == 3)
	   				strcpy(gateArr[rowNumber-1].input2,token);//inputlari atar
		   	}else if(strcmp(transactionName, "OR")==0){//hangi kapi oldugunu bulur ve gerekli atamalari yapar
		   		if(columnNumber == 0){
	   				gateArr[rowNumber-1].type = or;
	   				gateArr[rowNumber-1].output = -1;
		   		}
	   			else if(columnNumber == 1)
	   				strcpy(gateArr[rowNumber-1].name,token);//kapinin ismini atar
	   			else if(columnNumber == 2)
	   				strcpy(gateArr[rowNumber-1].input1,token);//inputlari atar
	   			else if(columnNumber == 3)
	   				strcpy(gateArr[rowNumber-1].input2,token);//inputlari atar
		   	}else if(strcmp(transactionName, "NOT")==0){//hangi kapi oldugunu bulur ve gerekli atamalari yapar
		   		if(columnNumber == 0){
	   				gateArr[rowNumber-1].type = not;
	   				gateArr[rowNumber-1].output = -1;
		   		}
	   			else if(columnNumber == 1)
	   				strcpy(gateArr[rowNumber-1].name,token);//kapinin ismini atar
	   			else if(columnNumber == 2)
	   				strcpy(gateArr[rowNumber-1].input1,token);//inputlari atar
		   	}else if(strcmp(transactionName, "FLIPFLOP")==0){//hangi kapi oldugunu bulur ve gerekli atamalari yapar
		   		if(columnNumber == 0){
	   				gateArr[rowNumber-1].type = flipflop;
	   				gateArr[rowNumber-1].output = -1;
		   		}
	   			else if(columnNumber == 1)
	   				strcpy(gateArr[rowNumber-1].name,token);//kapi ismini atar
	   			else if(columnNumber == 2)
	   				strcpy(gateArr[rowNumber-1].input1,token);//inputlari atar
		   	}
	      	token = strtok(NULL, " \n");
	      	columnNumber++;
	   	}
	   	if(strcmp(transactionName, "INPUT")==0 && columnNumber != 0){
   			inputArr = (struct value*)malloc((columnNumber-1)*sizeof(value));//input degerleri icin yer ayirir
   			token = strtok(strTemp, " \n");
   			while( token != NULL ) {
   				token = strtok(NULL, " \n");
   				if(token != NULL){
   					strcpy(inputArr[inputIndex].valueName,token);//input degerleri atanir
   					inputIndex++;
   				}
   			}
	   	}
	   	columnNumber=0;
	   	rowNumber++;
	   	printf("%d",rowNumber);
	}
	fp = fopen("input.txt","r");
	
	while(fscanf(fp,"%c",&num) != EOF){
		if(num != ' ' && num != '\n' && row == 0){
			column++;
		} 
		if(num != ' ' && num != '\n'){
			inputArr[columnindex].inputValue = num - '0';
			columnindex++;
		}
		if(num == '\n'){
			result = gateCalculation(gateArr,inputArr,counter-1,inputIndex,&flipflopVal);//hesaplama islemi yapilir
			if(result != -1)
				printf("%d\n", result);
			else 
				break;
			columnindex = 0;
			row++;
		}
	}
	fclose(fp1);
	fclose(fp);
	free(gateArr);
	free(inputArr);
	return 0;
}
int gateCalculation(struct gate *gates,struct value *values,int gateCount, int valueCount, int * flipflopVal){
	int i;
	int firstOp = 0, secondOp = 0;
	//*flipflopVal = 0;
	for (i = 0; i < gateCount; ++i){
		if(gates[i].type == and){
			firstOp = getInputValue(gates, values, gateCount,valueCount, gates[i].input1);//inputa degerlerini atar
			secondOp = getInputValue(gates, values, gateCount,valueCount, gates[i].input2);//inputa degerlerini atar
			//printf("firstOp :%d / secondOp :%d\n",firstOp, secondOp );
			if (firstOp == -1 || secondOp == -1){
				fprintf(stderr, "Wrong input in line = %d, AND operation, program shut down!\n", (i+1));
				return -1;
			}
			else
				gates[i].output =  andOperation(firstOp,secondOp);
		}else if(gates[i].type == or){
			firstOp = getInputValue(gates, values, gateCount,valueCount, gates[i].input1);//inputa degerlerini atar
			secondOp = getInputValue(gates, values, gateCount,valueCount, gates[i].input2);//inputa degerlerini atar
			//printf("firstOp :%d / secondOp :%d\n",firstOp, secondOp );
			if (firstOp == -1 || secondOp == -1){
				fprintf(stderr, "Wrong input in line = %d, OR operation, program shut down!\n", (i+1));
				return -1;
			}
			else
				gates[i].output = orOperation(firstOp,secondOp);
		}else if(gates[i].type == not){
			firstOp = getInputValue(gates, values, gateCount,valueCount, gates[i].input1);//inputa degerlerini atar
			//printf("firstOp :%d \n",firstOp );
			if (firstOp == -1){
				fprintf(stderr, "Wrong input in line = %d, NOT operation, program shut down!\n", (i+1));
				return -1;
			}
			else
				gates[i].output = notOperation(firstOp);
		}else if(gates[i].type == flipflop){
			firstOp = getInputValue(gates, values, gateCount,valueCount, gates[i].input1);//inputa degerlerini atar
			secondOp = *flipflopVal;//inputa degerlerini atar
			if (firstOp == -1 || secondOp == -1){
				fprintf(stderr, "Wrong input in line = %d, OR operation, program shut down!\n", (i+1));
				return -1;
			}
			else{
				gates[i].output = flipFlopOperation(firstOp,secondOp);
				(*flipflopVal) = gates[i].output;
			}
		}
	}
	return gates[gateCount-1].output;
}
int getInputValue(struct gate *gates,struct value *values,int gateCount, int valueCount, char targetInputName[20]){
	int i;

	for (i = 0; i < valueCount; ++i)
		if(strcmp(values[i].valueName,targetInputName)==0)							//start input taken
			return values[i].inputValue;
	for (i = 0; i < gateCount; ++i)
		if(strcmp(gates[i].name,targetInputName)==0 && gates[i].output != -1)		//other output is input now taken
			return gates[i].output;
	return -1;																		//wrong input style
}
int andOperation(int firstInput, int secondInput){
	return firstInput && secondInput;
}
int orOperation(int firstInput, int secondInput){
	return firstInput || secondInput;
}
int notOperation(int input){
	return !input;
}
int flipFlopOperation(int firstInput, int secondInput){
	if(firstInput == secondInput)
		return 0;
	return 1;
}
