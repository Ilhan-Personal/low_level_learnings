/*
    Memory manipulation and comparison functions
    
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define BUFFER 10
int main(int argc, char *argv[]){
    char arr1[BUFFER];
    char arr2[BUFFER];
    scanf("%s",arr1);
    scanf("%s",arr2);
    int length = (strlen(arr1)<strlen(arr2))? strlen(arr1):strlen(arr2);
    if(!memcmp(arr1,arr2,length))
        printf("Arrays are same");
    else
        printf("Arrays are not same");
    return 0;
}
