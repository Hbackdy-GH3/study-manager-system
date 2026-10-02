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
                    if(enqueue(temp) == 1)
                        i++;
                }
                temp=temp->next;
            }
        }
        break;
    }
    currMode=save_queue;
    save_data();
    currMode=save_master;
    printf("Tasks added in queue as per your requirement!");
}

int enqueue(Topic* node){
    QueueNode* newNode=(QueueNode*)malloc(sizeof(QueueNode));
    if(newNode==NULL){
        printf("Today memory session empty");
        return 0;
    }

    newNode->topic=node;
    newNode->next=NULL;
    if (front==NULL){
        front=back=newNode;
        return 1;
    }
    QueueNode* temp=front;
    while(temp!=NULL){
        if(temp->topic==node){
            printf("This aready exist");
            free(newNode);
            return 0;
        }
        temp = temp->next;
    }
    back->next=newNode;
    back=newNode;
    return 1;
    
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
    printf("Do you have completed it ?\n");
    printf("Y for yes\nN for No\n");
    char ask;
    while(1){
        scanf(" %c",&ask);
        if(ask=='y' || ask=='Y'){
            front->topic->is_done=1;
            currMode=save_master;
            save_data();
            break;
        }else{
            break;
        }
    }

    if(front->next==NULL){
        // print_topic(front->topic);
        free(front);
        front=NULL;
        back=NULL;
        printf("Removed from queue!\n");
        currMode = save_queue;
        save_data();
        currMode=save_master;
        return;
    }
    
    QueueNode* temp=front->next;
    free(front);
    front=temp;
    currMode=save_queue;
    save_data();
    currMode=save_master;
    printf("Removed from queue!\n");

}