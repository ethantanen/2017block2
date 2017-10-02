//
//  traffic.h
//  
//
//  Created by Ethan Tanen on 10/1/17.
//
//

#ifndef traffic_h
#define traffic_h



typedef struct LinkedRecord{
    int year;
    int stops;
    struct LinkedRecord *next;
    
}LinkedRecord;

LinkedRecord *list_find(LinkedRecord *head, int year);
int parse_line(char *line);
void print_list(LinkedRecord * head);





#endif /* traffic_h */
