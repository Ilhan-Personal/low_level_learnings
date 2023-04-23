#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

// function to split string by space and returns the array of tokens

char** tokenize_string(char *line){
    char **tokens = (char**)malloc(MAX_NUM_TOKENS * sizeof(char *));
    char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
    int i, tokenIndex = 0,tokenNo=0;
    for(i=0;i<strlen(line);i++){
        char readChar = line[i];
        if(readChar==' ' || readChar== '\n' || readChar=='\t'){
            token[tokenIndex]='\0';
            if(tokenIndex!=0){//means a command was read
                tokens[tokenNo]=(char *)malloc(MAX_TOKEN_SIZE*sizeof(char));
                strcpy(tokens[tokenNo++],token);
                tokenIndex=0;
            }
        }
        else{
            token[tokenIndex++]=readChar;
        }
    }
    free(token);
    tokens[tokenNo]=NULL; // terminate with NULL
    return tokens;
}


int main(int argc, char* argv[]){
    printf("Welcome to Custom Shell!\n\n");
    char line[MAX_INPUT_SIZE];
    char **tokens;
    int i;
    while(1){
        memset(line,0,sizeof(line));
        printf("$ ");
        scanf("%[^\n]",line);
        getchar();
        //terminate with newline
        line[strlen(line)] = '\n';
        tokens = tokenize_string(line);
        if(tokens[0]==NULL){
            continue;
        }
        int ret = fork();
        if(ret<0){
            fprintf(stderr,"%s\n","Sorry failed to create a child process!\n");  // there are three streams mainly stdin for input, stdout for output and stderr for diagonistic messages such as this
        }
        else if(ret==0){
            execvp(tokens[0],tokens);//if successful new memory image for child process is allocated respective to the command
            printf("Sorry failed to execute command!\n"); //control reaches here if execvp fails
            _exit(1); // _exit terminates the calling process 
        }
        else{
            int waitc = wait(NULL);
        }
        for(i=0;tokens[i]!=NULL;i++){
            free(tokens[i]);
        }
        free(tokens);
    }
    return 0;
}

