#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define Length(x) (sizeof(x)/sizeof(x[0]))

double fat(int n);
void taylorEulerExpTest(int x);
void precisaoMaquinaArray(int n[],int ni);
float precisaoMaquinaSimples(int n);
double precisaoMaquinaDupla(int n);
double taylorEulerExpDupla(int x, int n);

main(){
   /*int ArrayRefs[] = {1,10,17,100,184,1000,1575,10000,17893};
   precisaoMaquinaArray(ArrayRefs,Length(ArrayRefs));*/
   taylorEulerExpTest(5);
   printf("Valor euler por Taylor usando Double: %0.17e\n",taylorEulerExpDupla(2,10));
   system("pause");
}//END FUNCTION

float precisaoMaquinaSimples(int n){
   float a = 1, s = n+a;
   while(s>n){
      a = a / 2;
      s = n + a;
   }//END WHILE
   return 2*a;
}//END FUNCTION

double precisaoMaquinaDupla(int n){
   double a = 1, s = n+a;
   while(s>n){
      a = a / 2;
      s = n + a;
   }//END WHILE
   return 2*a;
}//END FUNCTION

void precisaoMaquinaArray(int n[],int ni){
  for(int i=0;i<ni;i++){
    printf("Valor de referencia: %i\n",n[i]);                        
    printf("Precisao Simples da Maquina: %e\n",precisaoMaquinaSimples(n[i]));
    printf("Precisao Dupla da Maquina: %e\n",precisaoMaquinaDupla(n[i]));
    printf("--------------------------------------------------\n");
  }//END FOR
}//END FUNCTION

double fat(int n){
    if(n<=1){
         return 1;
    }//END IF
    return n * fat(n-1);
}//END FUNCTION

void taylorEulerExpTest(int x){
     printf("Valor de e^x: %e\n",pow(M_E,x));
}//END FUNCTION

double taylorEulerExpDupla(int x, int n){
    double r;
    if(n<=1){
        return 1;
    }//END IF
    r = (pow((double)x,(double)n-1)/fat(n-1)) + taylorEulerExpDupla(x,n-1);
    printf("Fatorial: %0.17e\n",fat(n-1));
    printf("Potencia: %.017e\n",pow(x,n-1));
    printf("%0.17e",r);
    printf("\n--------------------------------------------------\n");
    return r;
}//END FUNCTION
