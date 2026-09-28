#include "topic.h"

void enqueue_ask(){
    int n,t,stat,prior;
    Topic* temp=head;
    t=filter(&prior,&stat);
    printf("Enter no. of task to study ?");
    while(1){
        scanf("%d", &n);
        if(n < 0 || n > t){
            printf("Sorry please type in between 0 and %d \n", t);
            continue;
        }
        else {
            int i=0;
            while(temp!=NULL && i<n){
                if(temp->priority==prior && temp->is_done==stat){
                    enqueue(temp);
                    i++;
                }
                temp=temp->next;
            }
        }
        break;
    }
    currMode=save_queue;
    save_data();
    printf("Tasks added in queue as per your requirement!");
}

void enqueue(Topic* node){
    QueueNode* newNode=(QueueNode*)malloc(sizeof(QueueNode));
    if(newNode==NULL){
        printf("Today memory session empty");
        return;
    }
    newNode->topic=node;
    newNode->next=NULL;
    if (front==NULL){
        front=back=newNode;
    }
    else{
        back->next=newNode;
        back=newNode;
    }
}


void display_queue(){
    QueueNode* temp=front;
    if(front==NULL){
        printf("Today Session topic list is empty!");
        return;
    }
    while(temp!=NULL){
        print_topic(temp->topic);
        temp=temp->next;
    }
}

void dequeue(){
    if(front==NULL){
        printf("Today Session topic list is empty!");
        return;
    }
    printf("Now study this:\n");
    print_topic(front->topic);
    
    if(front->next==NULL){
        print_topic(front->topic);
        free(front);
        front=NULL;
        back=NULL;
        printf("Removed from queue!\n");
        currMode = save_queue;
        save_data();
        return;
    }
    
    QueueNode* temp=front->next;
    free(front);
    front=temp;
    currMode=save_queue;
    save_data();
    printf("Removed from queue!\n");

}