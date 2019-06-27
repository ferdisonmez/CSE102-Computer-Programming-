#include <stdio.h> 
#define Sabit 1000
#define p1 0.5
#define p2 20.0
 double bul(double a[],int c,int d){	/*  Function that finds the average of numbers        */
 	double toplam=0.0;
 	int i;
 	for(i=c;i<=d;i++){
 		
 		toplam=toplam+a[i];
	 }
 	toplam=toplam/(d-c+1);
 	
 	return toplam;
 }
 void siralama (double dizi[],int elemansayisi) /* function that sequence small from big of numbers                */
{
     int i,j,enkucuk;
     double temp;
     for (i=0;i<elemansayisi-1;i++)
     {
         enkucuk=i;
         for(j=i+1;j<elemansayisi;j++)
         {
             if(dizi[j]<dizi[enkucuk])
             enkucuk=j;      
         }
         temp=dizi[i];
         dizi[i]=dizi[enkucuk];
         dizi[enkucuk]=temp;
          
     }
}
  int main(){   
       FILE *dosya;
	   FILE *output; 							
       double arr[Sabit],ort[Sabit],ub[Sabit];      	/* variables and arrays are defined  */	
	   double n=0,a=0,b=0;    
       int status,i=0,counter=0,c[Sabit],h=0,j,k=0; 
       dosya=fopen("input.txt","r");
	   output=fopen("output.txt","w"); 
       if(dosya==0) 
            printf("File Not Found "); 
       else { 
            status = fscanf(dosya,"%lf",&arr[i]); /*  reads data from file   */
            while( status!= EOF && status!=0){    /*  check condition    */
  			   counter++; 
                 i++; 
                 status = fscanf(dosya,"%lf",&arr[i]); 
            }   
        } 
       fclose(dosya);	/* closes the file  */ 
       i=0;
       j=i+1;
       while(j<=counter){     			
       		n=arr[j]; 
       		a=bul(arr,i,j-1);  /*  sends data to function   */
		    b=bul(arr,i,j);	   /*   sends data to function  */	 	   
    if(!(b > a*(1+p1) || b < a*(1-p1) || a > n*p2 || a < n/p2)){  /*check condition  */
       		j++;   				
	    }
	else{			
		   ort[h]=a;
		   h++;             /* I counted how much  entered  */
		   c[k]=i;         /* I saved the coordinates  */
		   c[k+1]=j-1;     /* I saved the coordinates  */
		   k=k+2;
		   i=j;
		   j=j+1;		 				 			
		   }   
	}  	  
	   for(i=0;i<h;i++){   /*  I have recorded the sequence before sorting the sequence */
	   	ub[i]=ort[i];
	   }
	   siralama(ort,h);		/* I've listed the sequence from small to large */
	   for(i=0;i<h;i=i+1){
	      	for(j=0;j<h;j++){
	   		
	        if(ort[i]==ub[j]){   /*I compared the order of the ordered average to the unordered  */
	   		
	   		    for(k=c[2*j];k<=c[2*j+1]; k++){  /* I printed the elements of the array using the coordinates */
	   			fprintf(output,"%.4lf\t",arr[k]);  /* this is writing values to file  */
	   			
			    }
			    fprintf(output,"\n");
		    }	    
       	}
   	
	   }
	   fclose(output);	  /* closes the file  */   
   return 0; 
}
