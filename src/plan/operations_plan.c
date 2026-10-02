#include "topic.h"


void add_topic_plan(){
    Topic* temp=head;
    int ask;
    printf("Enter your plan as: \n");
    printf("1 for to take in plan \n");
    printf("0 for to remove from plan \n");
    while(temp!=NULL){
        if(temp->is_done==0){
            if(temp->in_plan==0){
                print_topic(temp);
                while(1){
                    if (scanf("%d", &ask) != 1) {          
                        while (getchar() != '\n');
                        printf("Please enter a number (0 or 1)\n");
                        continue;
                    }
                    switch (ask){
                        case 1:
                            temp->in_plan=ask;
                            break;
                        case 0:
                            temp->in_plan=ask;
                            break;
                        default:
                            printf("Please enter valid number 0 or 1");
                            continue;
                        }
                    if(ask==1 || ask==0){
                        break;
                    }
                }
            }
        }
        temp=temp->next;
    }
}


void remove_topic_plan(){
    if(plan.exists==1){
        Topic* temp=head;
        while(temp!=NULL){
            if(temp->in_plan==1){
                print_topic(temp);
                int ask;
                printf("Enter your choice as: \n");
                printf("1 for to keep in plan \n");
                printf("0 for to remove from plan \n");
                if (scanf("%d", &ask) != 1) {          
                    while (getchar() != '\n');
                    printf("Please enter a number (0 or 1)\n");
                    continue;
                    }
                switch (ask){
                    case 1:
                        break;
                    case 0:
                        temp->in_plan=0;
                        break;
                    default:
                        printf("Please enter valid number 0 or 1");
                        continue;
                }
            }
            temp=temp->next;
        }
    }
}


void cal_start_totals(){
    
        int n1=0,n2=0;
        filter_plan_via_status(&n1,&n2);
        plan.start_totals=n2;
}

int curr_base_pace(){
        int rem=plan_validity();
        int curr_pace;
        if(rem==-1){
            printf("your plan has expired");
            return 0;
        }
        int n1=0,n2=0;
        filter_plan_via_status(&n1,&n2);
        return curr_pace=(((n2-n1)+rem-1)/rem)-plan.base_pace;
}