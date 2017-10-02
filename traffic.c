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


//TODO: check syntax

LinkedRecord *list_find(LinkedRecord *head, int year){
    
    //check to see if head is null
    //create first node in list
    
    printf("HERE");
    
    if(head == NULL){
        
        printf("HEAD WAS NULL");

        LinkedRecord *node;//= malloc(sizeof(LinkedRecord));
        
        node->year = year;
        node->stops = 0;
        node->next = NULL;
        
        
        
        
        printf("also here:");
        
        //free(node);
        return node;
    }
    
    if(head->year == year){
        return head;
    }
    
    return(list_find(head->next,year));
    
}

int parse_line(char *line){
    
    printf("just before free\n"); fflush(stdout);

    
    char *line_text = (char *)malloc(sizeof(char)*10);
    
    printf("after issue:\n"); fflush(stdout);
    
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
    
    printf("%d had %d stops",head->year,head->stops);
    
    print_list(head->next);
}

int main(int argc, char**argv){
    
    
    //check arg. count
    if(argc < 2){
        printf("Usage: %s <traffic data> \n Exiting... \n",argv[0]);
        return 0;
    }
    
    
    
    //created output list ptr
    LinkedRecord *out_list;
    
    
    //create and open file
    FILE *f;
    f = fopen(argv[1],"r");
    

    //toss the heaader line
    char *header_line = malloc(sizeof(char)*100);
    fgets(header_line,INT_MAX,f);//large number to ensure newline char is hit before # of requested bytes
    free(header_line);

    
    
    char *line;
    size_t read;
    size_t len = 0;
    
    
    printf("just bf node \n");

    
    
    LinkedRecord *node = malloc(sizeof(LinkedRecord));
    
    printf("created node \n");
    
    while ((read = getline(&line, &len, f)) != -1) {
        
        printf("here");
        
        puts(line);
        
        int year = parse_line(line);

        
        
        printf("just before listfind, year: %d",year);
        //node = list_find(out_list,year);
        
        //printf("past listfind");
        //node->stops +=1;
    
        
    }
   
    
    fclose(f);
    
    //print_list(out_list);
    
    
    return 1;
    
    
    
}
























