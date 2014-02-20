#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int fat(int n);
double precisaoMaquina(int n);

main(){
   printf("A precisao desta Maquina eh de: %lf\n",precisaoMaquina(1));
   system("pause");
}//END FUNCTION

double precisaoMaquina(int n){
   double a = 1, s = 1+a;
   while(s>1){
      printf("%lf\n",a);        
      a = a / 2;
      s = 1 + a;
   }//END WHILE
   printf("%lf",a);
   return 2*a;
}//END FUNCTION

int fat(int n){
    if(n<=1){
         return 1;
    }//END IF
    return n * fat(n-1);
}//END FUNCTION
