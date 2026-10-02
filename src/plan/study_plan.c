#include "topic.h"

void creation_plan()
{
    if (plan.exists == 0)
    {   add_topic_plan();
        cal_start_totals();
        if(plan.start_totals==0){
            printf("No topics selected, plan not created");
            return;
        }
        
        printf("What's the plan name?\n");
        scanf(" %49[^\n]", plan.plan_name);
        while (1)
        {
            printf("What's the plan start date? FORMAT: YYYYMMDD\n");
            while (1)
            {
                scanf("%d", &(plan.start_date));
                if (valid_date(plan.start_date) == 0)
                {
                    break;
                }
                else
                {
                    continue;
                }
            }

            printf("What's the plan end date? FORMAT: YYYYMMDD\n");
            while (1)
            {
                scanf("%d", &(plan.end_date));
                if (valid_date(plan.end_date) == 0)
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
            if (start_end() == 0)
            {
                cal_start_totals();
                int rem=plan_validity();
                plan.base_pace=(plan.start_totals+rem-1)/rem;
                plan.exists=1;
                break;
            }
            else
            {
                continue;
            }
        }
        currMode = save_master;
        save_data();

        currMode = save_plan;
        save_data();

        currMode = save_master;
    } else{
        printf("Plan exist!");
    }
}

int plan_validity()
{
    int today = today_ymd();

    if (plan.end_date < today)
    {
        return -1;                      
    }
    else if (today < plan.start_date)
    {
  
        return day_number(plan.end_date) - day_number(plan.start_date) + 1;
    }
    else
    {
       
        return day_number(plan.end_date) - day_number(today) + 1;
    }
}

int start_end()
{
    if (plan.end_date <= plan.start_date)
    {
        printf("End date must be greater than start date\n");
        return 1;
    }
    return 0;
}


void check_plan(){
    if(plan.exists==1){
        status_plan();
        filter_plan();
        display_plan_details();
        show_progress_plan();
        }
    else{
        printf("Sorry you have no plan yet");
        }
}

void display_plan_details(){
    if(plan.exists==1){
        printf("Plan name: %s", plan.plan_name);
        printf("Start date: %s",display_date(plan.start_date));
        printf("End date: %s",display_date(plan.end_date));
        printf("Total planned topics: %d", plan.start_totals);
        printf("Base pace: %d", plan.base_pace);
    }else{
        printf("Sorry you dont have active plan");
    }
}

void display_plan_topic(){
    if(plan.exists==1){
        Topic* temp=head;
        int count=0;
        while(temp!=NULL){
            if(temp->in_plan==1){
                print_topic(temp);
                count+=1;
            }
            temp=temp->next;
        }
        if(count==0){
            printf("You have zero topics in plan");
        }
    } else{
        printf("Sorry you dont have active plan");
    }
}

void status_plan(){
    int rem=plan_validity();
    int today=today_ymd();
    int n1=0,n2=0;
    filter_plan_via_status(&n1,&n2);
    if(plan.exists==1){
        if(rem==-1){
            printf("Your plan has ended");
            if((n2-n1)==0){
                printf("Yes, hurray! you have completed your plan with zero topics left out!");
            } else{
                printf("Yes, hurray! you have not completed your plan with %d topics left out!", (n2-n1));
                printf("do you want to extend the plan?");
                printf("Y for yes\nN for no\n");
                char ask;
                scanf(" %c",&ask);
                if(ask=='Y' || ask=='y'){
                    int new_end_date;
                    printf("Enter new End date: (format: YYYYMMDD");
                    while(1){
                        scanf("%d",&new_end_date);
                        if((valid_date(new_end_date)==0) && plan.end_date<new_end_date){
                            plan.end_date=new_end_date;
                            display_plan_details();
                            currMode=save_plan;
                            save_data();
                            currMode = save_master;
                            return;
                        } else{
                            printf("Invalid data");
                            continue;
                        }
                    }
                } else{
                    delete_plan();
                }
                // if yes then update the end date
                // else plan.exists=0
            }
       }else{
            if(today<plan.start_date){
                // int totals=rem+(day_number(plan.start_date)-day_number(today));
                printf("Your plan is not started\n");
                printf("You have %d days left from onwards %s", rem, display_date(plan.start_date));

            }else{
                printf("You have %d days left!", rem);
                if(rem!=1){
                
                    printf("Your today target is to completes this many topics: %d", ((n2-n1) + rem - 1) / rem);
                }else{
                    printf("Today is your last date so target is to completes this many topics: %d", (n2-n1));
                }
            }
    

        }

    }
}

void update_plan(){
    if(plan.exists==1){
        int ask;
        while(1){
            printf("\n===== Update Plan =====\n");
            printf("1. Add topics to plan\n");
            printf("2. Remove topics from plan\n");
            printf("3. Show plan topics\n");
            printf("4. Fill topics in queue\n");
            printf("0. Done\n");
            printf("What do you want to do? ");
            printf("please choose amongs 1/2/3/0");
            if (scanf("%d", &ask) != 1) {          
                while (getchar() != '\n');
                printf("Please enter a number (0/1/2/3/4)\n");
                continue;
            }
            switch (ask){
                case 1:
                    add_topic_plan();
                    break;
                case 2:
                    remove_topic_plan();
                    break;
                case 3:
                    display_plan_topic();
                    break;
                case 4:
                    fill_queue_from_plan();
                    break;
                case 0:
                    cal_start_totals();
                    currMode = save_master;
                    save_data();

                    currMode = save_plan;
                    save_data();

                    currMode = save_master;
                    return;
                default:
                    printf("invalid input");
                    continue;
            }
        }
    }
}

void delete_plan(){
    if(plan.exists==0){
        printf("Sorry you dont have active plan\n");
        return;
    } else{
        display_plan_details();
        printf("Do you want to delete the plan?\n");
        printf("Y for Yes\nN for No");
        char ask;
        scanf(" %c", &ask);
        if(ask=='Y' || ask=='y'){
            Topic* temp=head;
            while(temp!=NULL){
                temp->in_plan = 0;
                temp=temp->next;
            }
            plan.plan_name[0] = '\0';
            plan.base_pace=0;
            plan.start_date=0;
            plan.end_date=0;
            plan.start_totals=0;
            plan.exists=0;
        } else{
            return;
        }
        currMode = save_master;
        save_data();

        currMode = save_plan;
        save_data();

        currMode = save_master;
    }
    printf("Your plan has successfully deleted");
}


void fill_queue_from_plan(){
    Topic* temp=head;
    int target=today_target();
    int already=0;
    QueueNode* temp1=front;
    while(temp1!=NULL){
        if(temp1->topic->in_plan==1 && temp1->topic->is_done==0){
            already+=1;
        }
        temp1=temp1->next;
    }
    target=target-already;
    if(target<0){
        printf("Already all topics are in queue");
        return;
    }
    int count=0;
    while(temp!=NULL && count!=target){
        if((temp->in_plan==1) && (temp->is_done==0)){
            int added=enqueue(temp);
            if(added==1){
                count+=1;
            }
        }
        temp=temp->next;
    }
    printf("You have added %d topics from plan to queue", count);
    currMode=save_queue;
    save_data();
    currMode=save_master;
}

int today_target(){
    int today=today_ymd();
    int n1=0,n2=0;
    int rem=plan_validity();
    if(rem==-1 || today<plan.start_date){
        return 0;
    }
    filter_plan_via_status(&n1,&n2);
    return ((n2-n1) + rem - 1) / rem;
}