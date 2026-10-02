#include "topic.h"
#define case_insensitive  CI

Topic* head=NULL;
Topic* tail=NULL;

QueueNode* front=NULL;
QueueNode* back=NULL;

Plan plan;

enum SaveMode currMode=save_master;
enum when2save askYN = saveY;


int CI(char *a, char *b){
    while(*a && *b){
        if(tolower(*a) != tolower(*b)){
            return 0;
        }
        a++;
        b++;
    }
    return (*a == '\0' && *b == '\0');
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
