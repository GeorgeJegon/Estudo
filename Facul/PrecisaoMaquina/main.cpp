#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define Length(x) (sizeof(x)/sizeof(x[0]))

double fat(double n);
void taylorEulerExpTest(int x);
float taylorEulerExpSimples(int x, int n);
double taylorEulerExpDupla(int x, int n);
float precisaoMaquinaSimples(int n);
double precisaoMaquinaDupla(int n);
void precisaoMaquinaArray(int n[],int ni);

main(){
   /*int ArrayRefs[] = {1,10,17,100,184,1000,1575,10000,17893};
   precisaoMaquinaArray(ArrayRefs,Length(ArrayRefs));*/
   taylorEulerExpTest(5);
   //printf("Valor euler por Taylor usando Float: %f\n",taylorEulerExpSimples(5,15));
   printf("Valor euler por Taylor usando Double: %lf\n",taylorEulerExpDupla(5,15));
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

double fat(double n){
    if(n<=1){
         return 1;
    }//END IF
    return n * fat(n-1);
}//END FUNCTION

void taylorEulerExpTest(int x){
     printf("Valor de e^x: %e\n",pow(M_E,x));
}//END FUNCTION

float taylorEulerExpSimples(int x, int n){
    float r;
    if(n<=1){
         return 1;
    }//END IF
    r = taylorEulerExpSimples(x,n-1)+(pow(x,n-1)/fat(n-1));
    printf("Fatorial: %d\n",fat(n-1));
    printf("Potencia: %lf\n",pow(x,n-1));
    printf("%f\n",r);
    return r;
}//END FUNCTION

double taylorEulerExpDupla(int x, int n){
    double r;
    if(n<=1){
        return 1;
    }//END IF
    r = taylorEulerExpDupla(x,n-1)+(pow(x,n-1)/fat(n-1));
    printf("Fatorial: %d\n",fat(n-1));
    printf("Potencia: %lf\n",pow(x,n-1));
    printf("%f\n",r);
}//END FUNCTION
