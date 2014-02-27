#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int fat(int n);
float precisaoMaquinaSimples(int n);
double precisaoMaquinaDupla(int n);

main(){
   printf("A precisao simples desta Maquina eh de: %e\n",precisaoMaquinaSimples(1));
   printf("A precisao dupla desta Maquina eh de: %e\n",precisaoMaquinaDupla(1));
   system("pause");
}//END FUNCTION

float precisaoMaquinaSimples(int n){
   float a = 1, s = 1+a;
   while(s>1){
      a = a / 2;
      s = 1 + a;
   }//END WHILE
   return 2*a;
}//END FUNCTION

double precisaoMaquinaDupla(int n){
   double a = 1, s = 1+a;
   while(s>1){
      a = a / 2;
      s = 1 + a;
   }//END WHILE
   return 2*a;
}//END FUNCTION

int fat(int n){
    if(n<=1){
         return 1;
    }//END IF
    return n * fat(n-1);
}//END FUNCTION
