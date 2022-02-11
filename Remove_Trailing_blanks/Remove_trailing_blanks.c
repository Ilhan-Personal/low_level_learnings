#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int main(){
    FILE *read_file;
    bool space=false;
    read_file = fopen("Source.txt","r");
    FILE *write_file = fopen("Destination.txt","w");
    if(read_file == NULL || write_file == NULL){
        printf("One or more of the files don't exist");
        return 404;
    }
    char c;
    while((c=fgetc(read_file))!=EOF){
        if(c==' ' && space ==false){
            space=true;
        }
        else if(c==' ' && space==true){
            continue;
        } 
        else if(space==true){
            space=false;
        }
        fputc(c,write_file);
    }
    fclose(read_file);
    fclose(write_file);
    return 0;
}