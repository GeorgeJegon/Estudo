#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#define Length(x) (sizeof(x)/sizeof(x[0]))

/*Cálculos*/
double fat(int n);
double taylorEulerExpDupla(int x, int n);
//double taylorEulerExpLoop(int x, int n);
double taylorEulerExpDuplaSimplify(int x, int n);
double taylorEulerExpDuplaSimplifyLoop(int x, int n);
double taylorEulerExpDuplaInfinito(int x, int n,double r);
double taylorEulerExpDuplaInfinitoLoop(int x);
double simplifyExpAndFat(int b,int e,int f);


/*COLTRO*/
double theCutter(int base, int fat){
        int potencia[fat];
        int fatorial[fat];
        double pote=1 , fato=1;

        int i=0, j=0;

        for(i=0; i<fat; i++){
                fatorial[i] = fat - i;
                potencia[i] = base;
        }

        for(i=0; i<fat; i++){
                for(j=0; j<fat; j++){
                        if(fatorial[i]%potencia[j]==0 && potencia[j]!=1){
                                fatorial[i] /= potencia[j];
                                potencia[j] = 1;
                        }
                }
        }

        for(i=0; i<fat; i++){
                pote *= potencia[i];
                fato *= fatorial[i];
        }


        return pote/fato;
}
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
    double a,b,c,d,e;
    int x = 75, n = 164;
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
    system("pause");
}//END FUNCTION

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
       return r;
    }//END IF
    return taylorEulerExpDuplaInfinito(x,++n,t+r);
}//END FUNCTION

double taylorEulerExpDuplaInfinitoLoop(int x){
    double s = 1, check = 0;
    for(int i=1,c=1;c==1;i++){
        check = (s + simplifyExpAndFat(x,i,i));
        if(check==s){
            c = 0;
        }else{
            s = check;
        }//END IF
    }//END FOR
    return s;
}//END FUNCTION

double taylorEulerExpDupla(int x, int n){
    if(n<=1){
        return 1;
    }//END IF
    n--;
    return (pow((double)x,(double)n)/fat(n)) + taylorEulerExpDupla(x,n);
}//END FUNCTION

double taylorEulerExpDuplaSimplify(int x, int n){
    if(n--<=1){
        return 1;
    }//END IF
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
                if((fat[j]%pot[i])==0){
                   fat[j] /= pot[i];
                   pot[i] = 1;
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

double fat(int n){
    if(n<=1){
         return 1;
    }//END IF
    return n * fat(n-1);
}//END FUNCTION
