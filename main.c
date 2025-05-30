#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
void shuffle(char **array, size_t n);
bool isflush(char **array, size_t n);
int ismultiple(char **array, size_t n);
bool issequence(char **array, size_t n);
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
    printf("%s\n",mao[i]);
}


   if(isflush(mao, 5)==true){
    printf("e um flush");
   };
   printf("Seu maior par é: %d", ismultiple(mao, 5));
   
printf("sua mão é %d sequencia",issequence(mao, 5));



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
        printf("nao é flush\n");
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
else if(dpares && maior <2){
return 6; //6 é o codigo para dois pares
}
else{
return maior;
}
}


bool issequence(char **array, size_t n){
    int mao[n];
    for(int i=0;i<n;i++){
    if(array[i][0]=='V')
        mao[i]=11;
    else if(array[i][0]=='D')
        mao[i]=12;
    else if(array[i][0]=='R')
        mao[i]=13;
    else{
        mao[i]=ord(array[i][0] ) - ord('0')
    }
    
    }
    qsort
    return true;
}


