# include "topic.h"

void save_data(){
    FILE* fptr;
    if(currMode==save_master){
        Topic* temp=head;
        fptr=fopen("data/data.txt", "w");
        while(temp!=NULL){
            fprintf(fptr, "%s,%s,%d,%d,%d\n", temp->subject, temp->chapter, temp->priority, temp->is_done,temp->in_plan);
            temp=temp->next;
        }
    } else if(currMode==save_queue){
        QueueNode* temp=front;
        fptr=fopen("data/queue_data.txt", "w");
        while(temp!=NULL){
            fprintf(fptr, "%s,%s,%d,%d\n", temp->topic->subject, temp->topic->chapter, temp->topic->priority, temp->topic->is_done);
            temp=temp->next;
        }

    }
    else{
        fptr=fopen("data/plan_data.txt", "w");
        if(plan.exists==1){
            fprintf(fptr, "%d,%d,%d,%d,%s\n", plan.start_date, plan.end_date, plan.start_totals, plan.base_pace,plan.plan_name);
        }
    }

    fclose(fptr);
    printf("Data saved!");
}

void load_data(){
    FILE* fptr;
    if(currMode==save_master){
        fptr=fopen("data/data.txt", "r");
        if(fptr==NULL){
            printf("Data not found!");
            return;
        }
        char subject[50], chapter[50];
        int priority, is_done, in_plan;

        enum when2save oldAskYN = askYN;
        askYN = saveN;

        while(fscanf(fptr, "%49[^,],%49[^,],%d,%d,%d\n",subject,chapter, &priority, &is_done, &in_plan)==5){
            Topic* node=insert_prior(subject, chapter, priority, is_done);
            if(node!=NULL){
                node->in_plan=in_plan;
            }
        }

        askYN = oldAskYN;
        printf("Data load succesfully!");
    }else  if(currMode==save_queue){
        fptr=fopen("data/queue_data.txt", "r");
        if(fptr==NULL){
            printf("Data not found!");
            return;
        }
        char subject[50], chapter[50];
        int priority, is_done;
        
        while(fscanf(fptr, "%49[^,],%49[^,],%d,%d\n",subject,chapter,&priority,&is_done)==4){
            
            data_enqueue(subject, chapter);
        }
        display_queue();
        printf("Data load succesfully!");
    }
    else{
        fptr=fopen("data/plan_data.txt", "r");
        if(fptr==NULL){
            printf("Data not found!");
            return;
        }
        char plan_name[50];
        int start_date,end_date,start_totals,base_pace;

        enum when2save oldAskYN = askYN;
        askYN = saveN;

        if(fscanf(fptr, "%d,%d,%d,%d,%49[^\n]",&start_date,&end_date, &start_totals,&base_pace,plan_name)==5){
            plan.exists=1;
            plan.start_date=start_date;
            plan.end_date=end_date;
            plan.start_totals=start_totals;
            plan.base_pace=base_pace;
            strcpy(plan.plan_name, plan_name);

        }   
        askYN=oldAskYN;
    }
    fclose(fptr);

}

void data_enqueue(char subject[], char chapter[]){
    Topic* temp1=head;
    while(temp1!=NULL){
        if (CI(subject,temp1->subject) && CI(chapter,temp1->chapter)){
            enqueue(temp1);
        }
        temp1=temp1->next;
    }
    printf("Queue data loaded successfully");
    display_queue();
}


