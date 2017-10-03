/*
 * traffic.c
 *
 *  Created on: Sep 30, 2017
 *      Author: ethantanen
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "traffic.h"



LinkedRecord *list_find(LinkedRecord *head, int year){
    
    
    
    
    if(head->year == 0){
        
        head->year = year;
        head->stops = 0;
        
        head->next = malloc(sizeof(LinkedRecord));
        head->next->year = 0;
        head->next->stops= 0;
        head->next->next = 0;
        
        return head;
    }
    
    if(head->year == year){
        return head;
    }
    
    return(list_find(head->next,year));
    
}

int parse_line(char *line){
    
    
    char *line_text = (char *)malloc(sizeof(char)*10);
    
    
    strncpy(line_text,line+6,4);
    
    int toInt = atoi(line_text);
    
    
    
    free(line_text);
    
    if(toInt){
        return toInt;
    }
    
    return -1;
    
    
}

void print_list(LinkedRecord *head){
    
    
    if(head == NULL){
        return;
    }
    
    printf("%d had %d stops \n",head->year,head->stops);
    
    print_list(head->next);
}

int main(int argc, char**argv){
    
    
    //check arg. count
    if(argc < 2){
        printf("Usage: %s <traffic data> \n Exiting... \n",argv[0]);
        return 0;
    }
    
    
    
    //created output list ptr
    LinkedRecord *out_list = malloc(sizeof(LinkedRecord));
    
    
    //create and open file
    FILE *f;
    f = fopen(argv[1],"r");

    
    
    char *line;
    size_t read;
    size_t len = 0;
    
    
    getline(&line, &len, f);//move through header
    
    
    LinkedRecord *node = malloc(sizeof(LinkedRecord));
    
    
    while ((read = getline(&line, &len, f)) != -1) {
        
        
        
        int year = parse_line(line);

        
        node = list_find(out_list,year);
        
        node->stops +=1;
    
        
        
    }
   
    
    fclose(f);
    
    print_list(out_list);
    
    
    return 1;
    
    
    
}
























