#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int fat(int n);
float precisaoMaquinaSimples(int n);
void precisaoMaquinaSimplesArray(int n[],int ni);
double precisaoMaquinaDupla(int n);
void precisaoMaquinaDuplaArray(int n[],int ni);

main(){
   int ArrayRefs[] = {10,17,100,184,1000,1575,10000,17893};
   printf("A precisao simples desta Maquina eh de: %1.25e\n",precisaoMaquinaSimples(1));
   printf("A precisao dupla desta Maquina eh de: %1.25e\n",precisaoMaquinaDupla(1));
   /*printf("Precisao Simples:");
   printf("\n-----------------------\n");
   precisaoMaquinaSimplesArray(ArrayRefs,8);
   printf("Precisao Dupla:");
   printf("\n-----------------------\n");
   precisaoMaquinaDuplaArray(ArrayRefs,8);*/
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

void precisaoMaquinaSimplesArray(int n[],int ni){ 
  for(int i=0;i<ni;i++){
    printf("Valor para ref: %i, Precisao: %e\n",n[i],precisaoMaquinaSimples(n[i]));
  }//END FOR 
}//END FUNCTION

double precisaoMaquinaDupla(int n){
   double a = 1, s = n+a;
   while(s>n){
      a = a / 2;
      s = n + a;
   }//END WHILE
   return 2*a;
}//END FUNCTION

void precisaoMaquinaDuplaArray(int n[],int ni){
  for(int i=0;i<ni;i++){
    printf("Valor para ref: %i, Precisao: %e\n",n[i],precisaoMaquinaDupla(n[i]));
  }//END FOR 
}//END FUNCTION

int fat(int n){
    if(n<=1){
         return 1;
    }//END IF
    return n * fat(n-1);
}//END FUNCTION
