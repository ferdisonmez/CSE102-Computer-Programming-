#include<stdio.h>
#define M 10
#define G 0.00001

int main(){
	double x,y,a,b,f,h,n;
	double average_x1=0,average_y1=0,average_x2=0,average_y2=0;
	int j,i;
	double orta_nx,orta_ny;
	double egim,egim_d;
	int donus=2;
	
	for(j=0;j<M;j++){
					
		printf("%d.enter coordinates:",j);
		if((scanf("%lf",&x)!=1) || (scanf("%lf",&y))!=1){         /*    I checked the coordinates     */
			printf("check coordinates");
			return 0;
		}		
		average_x1+=x;  /*I have collected the values received */
		average_y1+=y;		
	}
	
	for(i=0;i<M;i++){
			
		printf("%d.enter coordinates:\n",i);
	if((scanf("%lf",&a)!=1) ||  (scanf("%lf",&b)!=1)){      /*    I checked the coordinates     */
		printf("check coordinates");
		return 0;
	}
		average_x2+=a;                /*I have collected the values received */
		average_y2+=b;	
	}
	
	average_x1=average_x1/M;     /*     The average of the x coordinates of the numbers was calculated                                                   */    
	average_y1=average_y1/M;	/*  The average of the y coordinates of the numbers was calculated               */
	
	average_x2=average_x2/M;    /*      The average of the x coordinates of the numbers was calculated                */
	average_y2=average_y2/M;	/* The average of the y coordinates of the numbers was calculated                 */
	
	orta_nx=(average_x1+average_x2)/2.0;  /*    midpoint of coordinates found         */
	orta_ny=(average_y1+average_y2)/2.0;
		
		if(average_x2-average_x1==0){  
	egim=(average_y2-average_y1)/((average_x2-average_x1)+G);	/* if the numbers are the same, look at whether the expression is defined        */
	}
		else{
		egim=(average_y2-average_y1)/(average_x2-average_x1);	/*   slope is calculated        */
	}
	
		if(egim==0){          /*   If the slope is 0, the macro value is added      */
		egim=egim+G;
	}
	egim_d=(-1)/egim;           /* The slope of the line was calculated         */
	
	orta_ny=(egim_d)*orta_nx+n;
		
	while(donus==2){
		
	printf("enter the test point:");
    donus=scanf("%lf %lf",&f,&h);   /*  whether the coordinates are entered correctly was controled     */
		if(donus!=2){
			printf("check coordinates");
			break;
		}
	if(h>(egim_d)*f+n){                           /*  checked the location of the test point    */
			if((average_y1<((egim_d)*average_x1+n))){
		printf("clas2\n");
	}
		   else if(average_y1>((egim_d)*average_x1+n)){
			printf("clas1\n");
		}
	}
	if(h<(egim_d)*f+n){                      /*  checked the location of the test point   */
			
		  if((average_y1<((egim_d)*average_x1+n))){
		printf("clas1\n");
	}
		  else if(average_y1>((egim_d)*average_x1+n)){
			printf("clas2\n");
		}
			
	}
}	
	return 0;
}
