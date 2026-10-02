#include "topic.h"

void show_progress(){
    if(head==NULL){
        printf("Data not available!");
        return;
    }
    int total=0, completed=0, pending=0;
    Topic* temp=head;
    while(temp!=NULL){
        if(temp->is_done==1){
            completed++;
        } else{
            pending++;
        }
        temp=temp->next;
        total++;
    }
    float percentage = (completed * 100.0) / total;

    printf("\n===== PROGRESS SUMMARY =====\n");
    printf("Total Topics    : %d\n", total);
    printf("Completed       : %d\n", completed);
    printf("Pending         : %d\n", pending);
    printf("Progress        : %.1f%%\n", percentage);
    printf("=============================\n");
}

void show_progress_queue(){
    if(front==NULL){
        printf("Data not available for today session!");
        return;
    }
    QueueNode* temp=front;
    int total=0;
    while(temp!=NULL){
        temp=temp->next;
        total++;
    }
    printf("Your total task is in queue: %d",total);
    
}

void show_progress_plan(){
    int n1=0,n2=0;
    int today=today_ymd();
    int rem=plan_validity();
    filter_plan_via_status(&n1,&n2);
    int total_days=day_number(plan.end_date)-day_number(plan.start_date)+1;
    int rem_days=day_number(plan.end_date)-day_number(today)+1;

    printf("\n===== Plan Progress: %s =====\n", plan.plan_name);
    printf("Total topics : %d\n", n2);
    printf("Completed    : %d\n", n1);
    printf("Pending      : %d\n", n2-n1);
    if(n2>0){
        printf("Progress     : %d%%\n", (n1*100)/n2);
    }
    printf("Total days   : %d\n", total_days);

    if(rem==-1){
        printf("Status       : Plan ended\n");
        return;
    }
    if(today<plan.start_date){
        printf("Status       : Not started yet\n");
        return;
    }

    printf("Days left    : %d\n", rem_days);

    int diff=curr_base_pace();
    if(diff>0){
        printf("Status       : Behind by %d topic(s)/day\n", diff);
    } else if(diff<0){
        printf("Status       : Ahead by %d topic(s)/day\n", -diff);
    } else{
        printf("Status       : On track\n");
    }
}