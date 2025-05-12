#include <stdio.h>
#include <stdlib.h>

int main()
{
    char baralho[]={ 'AO', 'AE', 'AC', 'AP', '2O', '2E', '2C', '2P','3O', '3E', '3C', '3P','4O', '4E', '4C', '4P','5O', '5E', '5C', '5P','6O', '6E', '6C', '6P','7O', '7E', '7C', '7P','8O', '8E', '8C', '8P','9O', '9E', '9C', '9P','VO', 'VE', 'VC', 'VP','DO', 'DE', 'DC', 'DP','RO', 'RE', 'RC', 'RP',} ;

    int size = sizeof(baralho) / sizeof(baralho[0]);
    shuffle(baralho,size);
    printf("sua mão é:\n");

for(i=0;i<=5;i++){
    printf("%c",baralho[x]);
}


    return 0;
}


void shuffle(char *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}
