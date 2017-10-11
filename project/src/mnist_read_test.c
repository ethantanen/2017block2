#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main (int argc, char **argv){
    
    //open data set
    FILE *f;
    f = fopen(argv[1],"r");
    
    if(f == NULL){
        printf("Error opening file...");
        return 1;
    }
    
    char *line;
    
    
    int *key = malloc(sizeof(int)*60000);
    int **images = malloc (sizeof(int) * 60000* 785);
    
    
    size_t len = 0;
    
    int char_count= 0;
    
    for(int i=0; i<60000;i++){
        
        char_count = getline(&line,&len,f);
        char *tok = strtok(line, ",");
        
        int j=0;
        
        while (tok != NULL) {
            images[i][j] = atoi(tok);
            tok = strtok(NULL, ",");
            j++;
        }
    }
    
    
    
    return 1;
    
}
