#include<string.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    int fd = open("myfile.txt",O_RDWR | O_CREAT, S_IRWXU);
    //open new file with Read and write file, create flag if it doesnt exist
    // O_TRUNC is used to clear contents if already file already exists I've opted to remove it
    // S_IRWXU is used 
    // O_TMPFILE flag for some reason throws an error saying it is undeclared, Maybe required filesystem support? I'll get to this
    if(fd<0){
        printf("Sorry unable to open file\n");
        exit(1);
    }
    else{
        printf("File opened  with file descriptor = %d\n",fd);
    }
    
    char *c = (char *) malloc(100*sizeof(char));
    int sz = read(fd,c,50);

    if(sz<0){
        printf("Sorry unable to read from file\n");
        exit(1);
    } 
    else if(sz==0)
        printf("File is empty\n");
    else{
        printf("%d bytes were read to file descriptor %d\n",sz,fd);
        c[sz]='\0';
        printf("Contents read : %s",c);

    }
    
  
    //Now we write to the file
    char *data = (char *)malloc(100*sizeof(char));
    printf("Content to write into file : ");
    scanf("%[^\n]%*c",data);
    write(fd,"\n",1); // Newline so that new content written into file is in next line
    sz = write(fd,data,strlen(data));
    if(sz<0){
        printf("Sorry unable to write to file\n");
        exit(1);
    }
    else{
        printf("Wrote %d bytes to file descriptor %d\n",sz,fd);
    }

    lseek(fd,0,SEEK_SET);
    //reset offsest to zero SEEK_SET means we set offset to absolute value specified in arguments
    sz = read(fd,c,50);
    if(sz<0){
        printf("Sorry unable to read from file\n");
        exit(1);
    } 
    else if(sz==0)
        printf("File is empty\n");
    else{
        printf("%d bytes were read to file descriptor %d\n",sz,fd);
    }
    c[sz]='\0';
    printf("Contents read : %s\n",c);

    int cls = close(fd);
    if(cls<0){
        printf("Sorry unable to close file\n");
        exit(1);
    }
    else{
        printf("File close with file descriptor %d",fd);
    }
    return 0;
}