#include <stdio.h>
int randperm(int *, int);

int main()
{
        int some_array[52],i;
        for (i=0;i<52;i++)
        {
                some_array[i]=i;
        }
        printf("********************BEFORE****************\n");
        for (i=0;i<52;i++)
        {
                printf("%d ", some_array[i]);
        }
        printf("\n");
        printf("********************AFTER****************\n");
        randperm(some_array,52);

        for (i=0;i<52;i++)
        {
                printf("%d ", some_array[i]);
        }
        printf("\n");
        return 0;
}