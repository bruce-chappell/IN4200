#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, *ptr, sum = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("val n = %d \n", n);
    printf("address n = %d \n", &n);

    ptr = (int*) malloc(n * sizeof(int));
    if(ptr == NULL)
    {
        printf("Error! memory not allocated.");
        exit(0);
    }

    printf("pointer addresses \n");
    printf("%d \n", &ptr[0]);
    printf("%d \n", &ptr[1]);
    printf("%d \n", &ptr[2]);
    printf("%d \n", &ptr[3]);
    printf("%d \n", &ptr[4]);
    printf("%d \n", &ptr[5]);
    printf("%d \n", &ptr[6]);


    // printf("Enter elements: ");
    // for(i = 0; i < n; ++i)
    // {
    //     scanf("%d", ptr + i);
    //     sum += *(ptr + i);
    // }
    //
    // printf("Sum = %d\n", sum);
    free(ptr);
    return 0;
}
