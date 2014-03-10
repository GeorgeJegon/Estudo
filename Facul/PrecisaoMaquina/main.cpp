#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#define Length(x) (sizeof(x)/sizeof(x[0]))

/*Cálculos*/
double fat(int n);
void taylorEulerExpTest(int x);
void precisaoMaquinaArray(int n[],int ni);
float precisaoMaquinaSimples(int n);
double precisaoMaquinaDupla(int n);
double taylorEulerExpDupla(int x, int n);
double taylorEulerExpDuplaInversa(int x,int n);
double taylorEulerExpDuplaSimplify(int x, int n);
double simplifyExpAndFat(int b,int e,int f);

/*Tools*/
void smartSpaces(int n,int r);
int numberLength(int n);

/*Exercícios*/
void resolucaoExercicio1();
void resolucaoExercicio2a();
void resolucaoExercicio2aTest();
void resolucaoExercicio2b();

main(){
   //resolucaoExercicio1();
   //resolucaoExercicio2a();
   //resolucaoExercicio2b();
   //printf("Resultado usando Simplificacao de Fracao: %e\n",taylorEulerExpDuplaSimplify(2,91));
   double r = taylorEulerExpDupla(2,23), t = simplifyExpAndFat(2,22,22);
   printf("Resultado usando calculo normal: %0.17e\n",taylorEulerExpDupla(2,22));
   printf("Resultado usando calculo normal: %0.17e\n",r);
   printf("Resultado usando calculo normal: %0.17e\n",r+t);
   printf("%0.17e\n",t);
   //printf("%e\n",simplifyExpAndFat(2,21,21));
   //taylorEulerExpTest(100);
   //printf("Resultado usando calculo normal: %0.17e\n",taylorEulerExpDuplaSimplify(100,156));
   //resolucaoExercicio2aTest();
   system("pause");
}//END FUNCTION

void resolucaoExercicio2a(){
     int ArrayX[] = {1,2,5,10,25,45,65,85,99,100},
         ArrayN[] = {1,10,20,30,40,50,60,70,80,90,100,150,155};
     printf("x | n | Resutado\n");
     for(int a=0,b=Length(ArrayX);a<b;a++){
         for(int c=0,d=Length(ArrayN);c<d;c++){
             int x = ArrayX[a], n = ArrayN[c];
             printf("%i",x);
             smartSpaces(numberLength(x),4);
             printf("| %i",n);
             smartSpaces(numberLength(n),4);
             printf("| `%0.17e`",taylorEulerExpDupla(x,n));
             printf("\n");
         }//END FUNCTION
     }//END FOR
}//END FUNCTION

void resolucaoExercicio2aTest(){
     int ArrayX[] = {1,2,5,10,25,45,65,85,99,100},
         ArrayN[] = {1,10,20,30,40,50,60,70,80,90,100,150,155,156,157};
     printf("x | n | Resutado\n");
     for(int a=0,b=Length(ArrayX);a<b;a++){
         for(int c=0,d=Length(ArrayN);c<d;c++){
             int x = ArrayX[a], n = ArrayN[c];
             printf("%i",x);
             smartSpaces(numberLength(x),4);
             printf("| %i",n);
             smartSpaces(numberLength(n),4);
             printf("| `%0.17e`",taylorEulerExpDuplaSimplify(x,n));
             printf("\n");
         }//END FUNCTION
     }//END FOR
}//END FUNCTION

void resolucaoExercicio2b(){
     /*int ArrayX[] = {1,2,49,50,99,100},
         ArrayN[] = {1,11,21,31,41,51,61,71,81,91};*/
     int ArrayX[] = {1,2,5,10,25,45,65,85,99,100},
         ArrayN[] = {1,10,20,30,40,50,60,70,80,90,100,150,155};
     printf("x | n | Resutado\n");
     for(int a=0,b=Length(ArrayX);a<b;a++){
         for(int c=0,d=Length(ArrayN);c<d;c++){
             int x = -ArrayX[a], n = ArrayN[c];
             double r = taylorEulerExpDupla(x,n),
                    ir = taylorEulerExpDuplaInversa(x,n),
                    diff = (r - ir);
             printf("%i",x);
             smartSpaces(numberLength(x),4);
             printf("| %i",n);
             smartSpaces(numberLength(n),4);
             printf("| `%0.17e` ",r);
             printf("| `%0.17e` ",ir);
             printf("| `%0.17e` ",diff);
             printf("\n");
         }//END FUNCTION
     }//END FOR
}//END FUNCTION

void resolucaoExercicio1(){
   int ArrayRefs[] = {1,10,17,100,184,1000,1575,10000,17893};
   precisaoMaquinaArray(ArrayRefs,Length(ArrayRefs));
}//END FUNCTION

void precisaoMaquinaArray(int n[],int ni){
  for(int i=0;i<ni;i++){
    printf("Valor de referencia: %i\n",n[i]);                        
    printf("Precisao Simples da Maquina: %e\n",precisaoMaquinaSimples(n[i]));
    printf("Precisao Dupla da Maquina: %e\n",precisaoMaquinaDupla(n[i]));
    printf("--------------------------------------------------\n");
  }//END FOR
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

double fat(int n){
    if(n<=1){
         return 1;
    }//END IF
    return n * fat(n-1);
}//END FUNCTION

void taylorEulerExpTest(int x){
     printf("Valor de e^x: %0.17e\n",pow(M_E,x));
}//END FUNCTION

double taylorEulerExpDupla(int x, int n){
    if(n<=1){
        return 1;
    }//END IF
    return (pow((double)x,(double)n-1)/fat(n-1)) + taylorEulerExpDupla(x,n-1);
}//END FUNCTION

double taylorEulerExpDuplaSimplify(int x, int n){
    if(n--<=1){
        return 1;
    }//END IF
    return simplifyExpAndFat(x,n,n) + taylorEulerExpDuplaSimplify(x,n);
}//END FUNCTION

double taylorEulerExpDuplaInversa(int x,int n){
    return 1/taylorEulerExpDupla(abs(x),n);
}//END FUNCTION

double simplifyExpAndFat(int b,int e,int f){
    int maxf=(f-1),max=std::max(e,f),pot[e],fat[maxf];
    double rp = 1, rf = 1;
    
    //inicializando os array's
    for(int i=0;i<max;i++){
        if(i<e){ 
            pot[i] = b;
        }//END IF
        if(i<maxf){
            fat[i] = (f-i);
        }//END IF
    }//END FOR

    for(int i=0;i<e;i++){
        for(int j=0;j<maxf;j++){
            if(pot[i]!=1){
                if(fat[j]>=pot[i] && (fat[j]%pot[i])==0){
                   fat[j] /= pot[i];
                   pot[i] = 1;
                }else if(pot[i]>fat[j] && (pot[i]%fat[j])==0){
                   fat[j] = 1;
                   pot[i] /= fat[j];
                }//END IF
            }//END IF    
        }//END FOR            
    }//END FOR
    
    // calculando os valores finais
    for(int i=0;i<max;i++){
        if(i<e){ 
            rp *= pot[i];
        }//END IF
        if(i<maxf){ 
            rf *= fat[i];
        }//END IF
    }//END FOR
    return rp/rf;
}//END FUNCTION

/*Tools Definition's*/
void smartSpaces(int n,int r){
     int j = (r - n);
     for(int i = 0;i<j;i++){
         printf(" ");
     }//END FOR
}//END FUNCTION

int numberLength(int n){
    int l = 1, b = 10;
    n = (n<0)?-n:n;
    while(n>=b){
        b *=10;
        l++;
    }//END WHILE
    return l;
}//END FUNCTION
