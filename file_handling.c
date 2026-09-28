# include "topic.h"

void save_data(){
    FILE* fptr;
    if(currMode==save_master){
        Topic* temp=head;
        fptr=fopen("data.txt", "w");
        while(temp!=NULL){
            fprintf(fptr, "%s,%s,%d,%d\n", temp->subject, temp->chapter, temp->priority, temp->is_done);
            temp=temp->next;
        }
    } else{
        QueueNode* temp=front;
        fptr=fopen("queue_data.txt", "w");
        while(temp!=NULL){
            fprintf(fptr, "%s,%s,%d,%d\n", temp->topic->subject, temp->topic->chapter, temp->topic->priority, temp->topic->is_done);
            temp=temp->next;
        }

    }

    fclose(fptr);
    printf("Data saved!");
}

void load_data(){
    FILE* fptr;
    if(currMode==save_master){
        fptr=fopen("data.txt", "r");
        if(fptr==NULL){
            printf("Data not found!");
            return;
        }
        char subject[50], chapter[50];
        int priority, is_done;

        enum when2save oldAskYN = askYN;
        askYN = saveN;

        while(fscanf(fptr, "%49[^,],%49[^,],%d,%d\n",subject,chapter, &priority, &is_done)==4){
            insert_prior(subject, chapter, priority, is_done);
        }
        askYN = oldAskYN;
        printf("Data load succesfully!");
    }else{
        fptr=fopen("queue_data.txt", "r");
        if(fptr==NULL){
            printf("Data not found!");
            return;
        }
        char subject[50], chapter[50];
        int priority, is_done;
        
        while(fscanf(fptr, "%49[^,],%49[^,]",subject,chapter)==2){
            
            data_enqueue(subject, chapter);
        }
        display_queue();
        printf("Data load succesfully!");
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


