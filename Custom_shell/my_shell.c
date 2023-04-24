#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

// function to split string by space and returns the array of tokens

#define MAX_NUM_COMMANDS 7
#define MAX_COMMAND_SIZE 16

char valid_commands[MAX_NUM_COMMANDS][MAX_COMMAND_SIZE] = {
    "ls",
    "cd",
    "pwd",
    "echo",
    "rm",
    "rmdir",
    "mkdir"
};

// function to compute Levenshtein distance between two strings
int levenshtein_distance(const char *s1, const char *s2) {
    int s1len = strlen(s1);
    int s2len = strlen(s2);
    int matrix[s1len + 1][s2len + 1];

    matrix[0][0] = 0;
    for (int i = 1; i <= s1len; i++) {
        matrix[i][0] = i;
    }
    for (int j = 1; j <= s2len; j++) {
        matrix[0][j] = j;
    }

    for (int j = 1; j <= s2len; j++) {
        for (int i = 1; i <= s1len; i++) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            matrix[i][j] = fmin(fmin(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1), matrix[i - 1][j - 1] + cost);
        }
    }

    return matrix[s1len][s2len];
}


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
        printf("Custom shell > ");
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
            printf("%s",tokens[1]);
            execvp(tokens[0],tokens);
		
            
            int closest_index = -1;
	    int closest_distance = INT_MAX;

	    for (int i = 0; i < MAX_NUM_COMMANDS; i++) {
		int distance = levenshtein_distance(tokens[0], valid_commands[i]);
		if (distance < closest_distance) {
		    closest_distance = distance;
		    closest_index = i;
		}
	    }

	    if (closest_distance <= 2) {
		printf("Did you mean '%s'?\n", valid_commands[closest_index]);
	    } else {
		printf("%c",tokens[0][0]);
		printf("Invalid command.\n");
	    } 
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

