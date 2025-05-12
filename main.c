#include <stdio.h>
#include <stdlib.h>

int main()
{
    
    char baralho[]={ 'A', '2','3','5','5'} ;
    printf("sua mão é:\n");
          
for(i=0;i<=)
          
        
    return 0;
}


void shuffle(int *array, size_t n)
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
