#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

typedef struct Topic{
    char subject[50];
    char chapter[50];
    int priority;
    int is_done;
    int in_plan;
    struct Topic* next;
    struct Topic* prev;

}Topic;

extern Topic* head;
extern Topic* tail;

typedef struct QueueNode{
    Topic* topic;
    struct QueueNode* next;
}QueueNode;

extern QueueNode* front;
extern QueueNode* back;

enum SaveMode {save_master, save_queue, save_plan};
extern enum SaveMode currMode;

enum when2save {saveY, saveN};
extern enum when2save askYN;

typedef struct Plan{
    int exists;
    char plan_name[50];
    int start_date;
    int end_date;
    int start_totals;
    int base_pace;

}Plan;

extern Plan plan;


#define case_insensitive CI
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int CI(char *a, char *b);

Topic* insert_init(char subject[], char chapter[], int priority, int is_done);
Topic* insert_prior(char subject[], char chapter[], int priority, int is_done);
void insertfront(Topic* node);
void insertback(Topic* node);
void insert_any(Topic* node, Topic* temp);
void insert_node_by_priority(Topic* node);

void pop();
void popfront();
void popback();
void popany(Topic* node);
void remove_node(Topic* node);

void search_topic();
void searched_action(Topic* node);
void update_priority(Topic* node);
void update_status(Topic* node);
void update_plan();

void filter_via();
int filter(int* prior, int* stat);
void filter_plan();
void filter_plan_via_status(int* n1,int* n2);

void enqueue_ask();
int enqueue(Topic* node);
void display_queue();
void dequeue();
void data_enqueue(char subject[], char chapter[]);

void show_progress();
void show_progress_queue();
void status_plan();
void show_progress_plan();

int today_ymd(void);
int valid_date(int date);
int start_end(void);
int plan_validity(void);
int day_number(int date);
int month_days(int month, int year);
int leap_year(int year);


void save_data();
void load_data();

void print_topic(Topic* node);
void print_all();
char* display_date(int date);
void display_plan_details();
void display_plan_topic();

void creation_plan();
void check_plan();
void delete_plan();
void add_topic_plan();
void remove_topic_plan();
int curr_base_pace();
void cal_start_totals();
void fill_queue_from_plan();
int today_target();