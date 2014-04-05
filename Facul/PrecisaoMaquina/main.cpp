#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#define Length(x) (sizeof(x)/sizeof(x[0]))

/*Cálculos*/
void precisaoMaquinaArray(int n[],int ni);
float precisaoMaquinaSimples(int n);
double precisaoMaquinaDupla(int n);
double fat(int n);
double taylorEulerExpDupla(int x, int n);
double taylorEulerExpDuplaInversa(int x,int n);
double taylorEulerExpDuplaSimplify(int x, int n);
double taylorEulerExpDuplaSimplifyLoop(int x, int n);
double taylorEulerExpDuplaInfinito(int x, int n,double r);
double taylorEulerExpDuplaInfinitoLoop(int x);
double simplifyExpAndFat(int b,int e,int f);

/*Tools*/
void smartSpaces(int n,int r);
int numberLength(int n);

/*Exercícios - Resoluções e Testes*/
void resolucaoExercicio1();
void resolucaoExercicio2a();
void resolucaoExercicio2b();
void resolucaoExercicio2aTest();
void taylorEulerExpTest(int x);
void taylorVariasFuncoesTest(int x,int n);

/*COLTRO*/

double theCutter(int base, int fat){
    int potencia[fat], fatorial[fat],i=0, j=0;
    double pote=1 , fato=1;
    for(i=0; i<fat; i++){
        fatorial[i] = fat - i;
        potencia[i] = base;
    }//END FOR
    
    for(i=0; i<fat; i++){
        for(j=0; j<fat; j++){
            if(fatorial[i]%potencia[j]==0 && potencia[j]!=1){
                fatorial[i] /= potencia[j];
                potencia[j] = 1;
            }//END IF
        }//END FOR
    }//END FOR
    
    for(i=0; i<fat; i++){
        pote *= potencia[i];
        fato *= fatorial[i];
    }//END FOR
    return pote/fato;
}//END FUNCTION

double serieTaylorTest(double x){
	int i, c = 1;
	double sum =0,test =0;
	for(i=0;c==1; i++){
        test = (sum+theCutter((int) x, i));            
        //printf("n: %i | r: %0.17e | next r: %0.17e\n",i,sum,test);
        if(test==sum){
           c = 0; 
        }else{
           sum += theCutter((int) x, i);
        }//END IF
	}//END FOR
	return sum;
}//END FUNCTION

/*COLTRO*/

main(){
    int x = 80, n = 156;
    //taylorVariasFuncoesTest(x,n);
    taylorEulerExpTest(x);
    printf("%0.17e\n",taylorEulerExpDuplaInfinitoLoop(x));
    //printf("%0.17e\n",taylorEulerExpDuplaSimplify(x,n));
    //printf("%0.17e\n",taylorEulerExpDupla(x,n));
    system("pause");
}//END FUNCTION

/*TESTE E RESOLUÇÕES*/
void taylorVariasFuncoesTest(int x,int n){
    double a,b,c,d,e;
    a = taylorEulerExpDuplaSimplify(x,n);
    b = taylorEulerExpDuplaSimplifyLoop(x,n);
    c = taylorEulerExpDuplaInfinitoLoop(x);
    d = taylorEulerExpDuplaInfinito(x,0,0);
    e = serieTaylorTest(x);
    printf("Evitando Overflow(recursiva):\n%0.17e\n",a);
    printf("\n----------------------------------------------------------------\n");
    printf("Evitando Overflow(loop):\n%0.17e\n",b);
    printf("\n----------------------------------------------------------------\n");
    printf("Sem determinar N(loop):\n%0.17e\n",c);
    printf("\n----------------------------------------------------------------\n");
    printf("Sem determinar N(recursiva):\n%0.17e\n",d);
    printf("\n----------------------------------------------------------------\n");
    printf("Testando a do coltro(loop):\n%0.17e\n",e);
}//END FUNCTION

void taylorEulerExpTest(int x){
     printf("Valor de e^x: %0.17e\n",pow(M_E,x));
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

/*TESTES E RESOLUÇÕES*/

double taylorEulerExpDuplaInfinito(int x, int n,double r){
    double t;
    n = (n<0)?0:n;
    if(n==0){
        t = 1;
    }else if(n==1){
        t = x;
    }else{
        t = simplifyExpAndFat(x,n,n);
    }//END IF
    if((r+t)==r){
       printf("n = %i | r: %0.17e | new r: %0.17e\n",n,r,r+t);
       return r;
    }//END IF
    printf("n = %i | r: %0.17e | new r: %0.17e\n",n,r,r+t);
    return taylorEulerExpDuplaInfinito(x,++n,t+r);
}//END FUNCTION

double taylorEulerExpDuplaInfinitoLoop(int x){
    double s = 1, check = 0;
    for(int i=1,c=1;c==1;i++){
        check = (s + simplifyExpAndFat(x,i,i));
        printf("n = %i | r: %0.17e | new r: %0.17e | new r - r: %0.17e\n",i,s,check,(check-s));
        if((check-s) < 0.00000001){
           printf("aQUI PORRA: %0.17e\n",s);
        }//END IF
        if(check==s){
            c = 0;
        }else{
            s = check;
        }//END IF
    }//END FOR
    return s;
}//END FUNCTION

double taylorEulerExpDupla(int x, int n){
    if(n<=1){ return 1; }//END IF
    n--;
    return (pow((double)x,(double)n)/fat(n)) + taylorEulerExpDupla(x,n);
}//END FUNCTION

double taylorEulerExpDuplaSimplify(int x, int n){
    if(n--<=1){ return 1; }//END IF
    return simplifyExpAndFat(x,n,n) + taylorEulerExpDuplaSimplify(x,n);
}//END FUNCTION

double taylorEulerExpDuplaSimplifyLoop(int x, int n){
    double s = 1;
    n = (n<=1)?1:n;
    for(int i=1;i<n;i++){
        s += (i==1)?x:simplifyExpAndFat(x,i,i);
    }//END FOR
    return s;
}//END FUNCTION

double taylorEulerExpDuplaInversa(int x,int n){
    return 1/taylorEulerExpDuplaSimplify(abs(x),n);
}//END FUNCTION

double fat(int n){
    if(n<=1){
         return 1;
    }//END IF
    return n * fat(n-1);
}//END FUNCTION

double simplifyExpAndFat(int b,int e,int f){
    int maxf=(f-1),max=std::max(e,f),pot[e],fat[maxf];
    double rp = 1, rf = 1;
    
    //inicializando os array's
    for(int i=0;i<max;i++){
        if(i<e){ pot[i] = b; }//END IF
        if(i<maxf){ fat[i] = (f-i); }//END IF
    }//END FOR

    for(int i=0;i<e;i++){
        for(int j=0;j<maxf;j++){
            if(pot[i]!=1){
                if((fat[j]%pot[i])==0){
                   fat[j] /= pot[i];
                   pot[i] = 1;
                }//END IF
            }//END IF    
        }//END FOR            
    }//END FOR
    
    // calculando os valores finais
    for(int i=0;i<max;i++){
        if(i<e){ rp *= pot[i]; }//END IF
        if(i<maxf){ rf *= fat[i]; }//END IF
    }//END FOR
    return rp/rf;
}//END FUNCTION

/*PRECISÃO MÁQUINA*/
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
/*PRECISÃO MÁQUINA*/

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
