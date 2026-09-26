#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Topic{
    char subject[50];
    char chapter[50];
    int priority;
    int is_done;
    struct Topic* next;
    struct Topic* prev;

}Topic;

extern Topic* head;
extern Topic* tail;

Topic* insert_init(char subject[], char chapter[], int priority, int is_done);
void insert_prior(char subject[], char chapter[], int priority, int is_done);
void insertfront(Topic* node);
void insertback(Topic* node);
void insert_any(Topic* node, Topic* temp);

void pop();
void popfront();
void popback();
void popany();

void print_topic(Topic* node);
void print_all();