#include "topic.h"

void filter_via(){
    int ask;
    printf("1. Show Pending works");
    printf("2. Show Completed works");
    printf("3. Show specific priority (High/Medium/Low)");
    printf("Enter your choice: \n");
    scanf("%d", &ask);
    while(1){
        switch (ask){
            case 1: {
                Topic* temp=head;
                while(temp!=NULL){
                    if(temp->is_done==0){
                        print_topic(temp);
                    }
                    temp=temp->next;
                }
            }
                break;
            case 2: {
                Topic* temp=head;
                while(temp!=NULL){
                    if(temp->is_done==1){
                        print_topic(temp);
                    }
                    temp=temp->next;
                }
            }
                break;
            case 3: {
                int choice;
                printf("1 for High\n");
                printf("0 for Medium\n");
                printf("-1 for Low\n");
                printf("Enter you choice: \n");
                while(1){
                    scanf("%d", &choice);
                    switch (choice){
                        case 1: {
                            Topic* temp=head;
                            while(temp!=NULL){
                                if(temp->priority==1){
                                    print_topic(temp);
                                }
                                temp=temp->next;
                            }
                        }
                            break;
                        case 0: {
                            Topic* temp=head;
                            while(temp!=NULL){
                                if(temp->priority==0){
                                    print_topic(temp);
                                }
                                temp=temp->next;
                            }
                        }
                            break;
                        case -1: {
                            Topic* temp=head;
                            while(temp!=NULL){
                                if(temp->priority==-1){
                                    print_topic(temp);
                                }
                                temp=temp->next;
                            }
                        }
                            break;
                        default:
                            printf("Please Enter valid number: 1 0 -1");
                            continue;
                    }
                    break;
                }
            }
            break;
            default:
                printf("Please Enter valid number: 1 to 3");
                continue;
        }
        break;
    }
}