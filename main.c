#include <stdio.h>
#include <stdlib.h>
void shuffle(char **array, size_t n);
int main()
{
  char *baralho[] = {
    "As de ouros", "As de espadas", "As de paus", "As de copas",
    "2 de ouros", "2 de espadas", "2 de copas", "2 de paus",
    "3 de ouros", "3 de espadas", "3 de copas", "3 de paus",
    "4 de ouros", "4 de espadas", "4 de copas", "4 de paus",
    "5 de ouros", "5 de espadas", "5 de copas", "5 de paus",
    "6 de ouros", "6 de espadas", "6 de copas", "6 de paus",
    "7 de ouros", "7 de espadas", "7 de copas", "7 de paus",
    "8 de ouros", "8 de espadas", "8 de copas", "8 de paus",
    "9 de ouros", "9 de espadas", "9 de copas", "9 de paus",
    "Valete de ouros", "Valete de espadas", "Valete de copas", "Valete de paus",
    "Dama de ouros", "Dama de espadas", "Dama de copas", "Dama de paus",
    "Rei de ouros", "Rei de espadas", "Rei de copas", "Rei de paus"
};


    int size = sizeof(baralho) / sizeof(baralho[0]);
    shuffle(baralho, size);
    printf("sua mão é:\n");

for(int i=0;i<=7;i++){
    printf("%s\n",baralho[i]);
}


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
