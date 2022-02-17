#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> //Defines symbolic constants
#include<sys/mman.h> //For mmap
#include<string.h> 
#include<signal.h> //For signal handling

char *location;
size_t pageSize;
int noOfPages;
void handler(int dummy){
    int unmap_result = munmap(location,noOfPages*pageSize);//Unmapping from memory
    if(unmap_result!=0){
        printf("Could not unmap !\n");
        exit(1);
    }
    printf("Unmapped !\n");
    exit(0);
}

int main(void){
    signal(SIGINT,handler);
    pageSize = getpagesize();//usually page size is 4096KB
    int pid = getpid();
    printf("Enter number of pages : \n");
    scanf("%d",&noOfPages);
    printf("Page size is %zu bytes\n",pageSize);
    printf("Process ID is %d\n",pid);
    location = mmap(NULL, noOfPages*pageSize,PROT_READ|PROT_WRITE,MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
    if(location== MAP_FAILED){ //value of MAP_FAILED is ((void *)-1)
        perror("Could not map\n");
        return 1;
    }
    else{
        printf("Mapped %d pages at address %p\n",noOfPages,location);
    }
    while(1){//This while(1) is used for analyzing purposes to check if we access all the pages
        int sum=0;
        for(int i=0;i<noOfPages;i++){
            sum+=location[i*pageSize];
        }
        sleep(2);

    }
    return 0;
}