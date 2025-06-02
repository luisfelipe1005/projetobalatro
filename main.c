#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
void shuffle(char **array, size_t n);
bool isflush(char **array, size_t n);
int ismultiple(char **array, size_t n);
bool issequence(char **array, size_t n);
int comparador(const void *a, const void *b);
void numerar_baralho(char **array, size_t n,int* maonumerada);
int main()
{

  char *baralho[] = {
 "AO", "AE", "AC", "AP", "2O", "2E", "2C", "2P","3O", "3E", "3C", "3P","4O", "4E", "4C", "4P","5O", "5E", "5C", "5P","6O", "6E", "6C", "6P","7O", "7E", "7C", "7P","8O", "8E", "8C", "8P","9O", "9E", "9C", "9P","0O", "0E", "0C", "0P","VO", "VE", "VC", "VP","DO", "DE", "DC", "DP","RO", "RE", "RC", "RP"
};
  char *mao[7];

    int size = sizeof(baralho) / sizeof(baralho[0]);
   
    printf("sua mão é:\n");

    srand(time(NULL));
        shuffle(baralho,size);


for(int i=0;i<5;i++){
  mao[i]=baralho[i];
    printf("%s ",mao[i]);
}


       bool flush=isflush(mao, 5);
   int multiplos=ismultiple(mao, 5);
  bool sequencia=issequence(mao, 5);
   int fichas,mult;
   printf("\n");
   
    if(flush && sequencia){
       printf("straight flush");
       fichas = 100;
       mult=8;
   }
    else if(multiplos==4){
       printf("Quadra");
       fichas = 60;
       mult=7;
   }
    else if(multiplos==7){
       printf("Full house");
       fichas = 40;
       mult=4;
   }
    else if(flush){
       printf("Flush");
       fichas = 35;
       mult=4;
       
   }else if(sequencia){
       printf("straight");
       fichas = 30;
       mult=4;
       
   }
    else if(multiplos==3){
       printf("Trinca");
       fichas = 30;
       mult=3;
   }
    else if(multiplos==6){
       printf("Dois pares");
       fichas = 20;
       mult=2;
   }
    else if(multiplos==2){
       printf("par");
       fichas = 10;
       mult=2;
   }
   else{
       printf("carta alta");
       fichas = 5;
       mult=1;
   }
   
   
   printf("\n Sua pontuacao e: %d", fichas*mult);


    return 0;
}


void shuffle(char **array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          char *t =  array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}


bool isflush(char **array, size_t n){
    int i;
for(i=1; i<n;i++){
    if(array[i-1][1] != array[i][1]){
        return false;
    }
}

    return true;

}

int ismultiple(char **array, size_t n) {

char charr[5] = {0},ra;

int count[5] = {0},ir, nmrd = 0;

bool encontrado,par=false,dpares=false,trinca=false,fullhouse=false;



for (int i = 0; i < n; i++) {
ra = array[i][0];
encontrado = false;
ir = -1;

for (int j = 0; j < nmrd; j++) {
 if (charr[j] == ra) {
encontrado = true;
ir = j;
break;
}
}

if (encontrado) {
count[ir]++;
} else {
if (nmrd < 5) {
charr[nmrd] = ra;
count[nmrd] = 1;
nmrd++;
}
}

}


int maior=1;

for(int k = 0; k < nmrd; k++) {
    if(count[k] > maior) {
        maior = count[k];
    }
    if(count[k] == 2 && par==false) {
        par=true;
    }
    else if(count[k] == 2 && par==true) {
        dpares=true;
    } 
    else if (count[k] == 3) {
        trinca=true;
    }
    if(trinca==true&&par==true){
        fullhouse=true;
    }


}

if(fullhouse && maior <4){
return 7; //7 é o codigo para fullhouse
}
else if(dpares){
return 6; //6 é o codigo para dois pares
}
else{
return maior;
}
}


bool issequence(char **array, size_t n){
    int mao[5]; 
    numerar_baralho(array, 5,mao);
    bool sequencia=true;
    
    
qsort(mao, n, sizeof(int), comparador);

     	for(int k = 0; k < n-1; k++) {
if(mao[k]+1!=mao[k+1]){
    sequencia=false;
    break;
}

}

    return sequencia;
}




int comparador(const void *a, const void *b) {
   return ( *(int*)a - *(int*)b );
}




void numerar_baralho(char **array, size_t n, int* maonumerada){
    
    for(int i=0;i<n;i++){
    if(array[i][0]=='0')
       maonumerada[i]=10;
    else if(array[i][0]=='V')
        maonumerada[i]=11;
    else if(array[i][0]=='D')
        maonumerada[i]=12;
    else if(array[i][0]=='R')
        maonumerada[i]=13;
    else if(array[i][0]=='A')
        maonumerada[i]=14;
    
    else{
        maonumerada[i]=array[i][0]  - '0';
    }
    }
}
