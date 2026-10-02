#include "topic.h"

void print_menu(){
    printf("\n========================================\n");
    printf("      STUDY MANAGEMENT SYSTEM\n");
    printf("========================================\n");

    printf("Choose what you want to do:\n\n");

    printf("--- Master Topic List ---\n");
    printf("1. Add Topic\n");
    printf("2. Search / Update / Delete a Topic\n");
    printf("3. Delete Topic (front/back/anywhere)\n");
    printf("4. Display All Topics\n");
    printf("5. Filter Topics\n");

    printf("--- Today's Study Queue ---\n");
    printf("6. Add Topics to Today's Queue\n");
    printf("7. Show Today's Queue\n");
    printf("8. Study Next Topic (Dequeue)\n");

    printf("--- Progress ---\n");
    printf("9. Show Progress (Master List)\n");
    printf("10. Show Progress (Today's Queue)\n");

    printf("--- Study Plan ---\n");
    printf("11. Create Plan\n");
    printf("12. Check Plan\n");
    printf("13. Update Plan\n");
    printf("14. Delete Plan\n");
    printf("15. Fill Today's Queue from Plan\n");

    printf("--- Program ---\n");
    printf("16. Save & Exit\n");

    printf("========================================\n");
    printf("Choose option 1 to 16\n");
    printf("Enter your choice: ");
}


int main(){

    /* load order matters: master first, queue and plan depend on its topics */
    currMode = save_master;
    load_data();

    currMode = save_queue;
    load_data();

    currMode = save_plan;
    load_data();

    currMode = save_master;     /* back to default */

    /* safety: no plan exists, so no topic should be marked in_plan
       (happens if the program was closed with Ctrl+C or plan_data.txt was deleted) */
    if(plan.exists == 0){
        int changed = 0;
        Topic* temp = head;
        while(temp != NULL){
            if(temp->in_plan == 1){
                temp->in_plan = 0;
                changed = 1;
            }
            temp = temp->next;
        }
        if(changed == 1){
            currMode = save_master;
            save_data();
        }
    }

    if(plan.exists == 1){
        printf("\n--- Your Study Plan ---\n");
        status_plan();
        printf("\n");
    }

    int choice;
    char subject[50], chapter[50];
    int priority;

    while(1){

        print_menu();
        scanf("%d",&choice);

        switch(choice){

            /* ================= ADD TOPIC ================= */

            case 1: {
                int add_choice;

                printf("\nYou selected: Add Topic\n");

                printf("\nChoose where you want to add the topic:\n");
                printf("1. Add at Front\n");
                printf("2. Add at Back\n");
                printf("3. Add by Priority (recommended)\n");

                printf("\nChoose option 1, 2 or 3\n");
                printf("Enter your choice: ");
                scanf("%d",&add_choice);

                printf("\nEnter topic details:\n");

                printf("Enter subject: ");
                scanf(" %49[^\n]",subject);

                printf("Enter chapter: ");
                scanf(" %49[^\n]",chapter);

                printf("\nChoose priority:\n");
                printf("1 = High\n");
                printf("0 = Medium\n");
                printf("-1 = Low\n");

                printf("Choose priority 1, 0 or -1\n");
                printf("Enter priority: ");
                scanf("%d",&priority);

                switch(add_choice){

                    case 1: {
                        Topic* node = insert_init(
                            subject,
                            chapter,
                            priority,
                            0
                        );

                        if(node != NULL){
                            insertfront(node);
                        }
                        break;
                    }

                    case 2: {
                        Topic* node = insert_init(
                            subject,
                            chapter,
                            priority,
                            0
                        );

                        if(node != NULL){
                            insertback(node);
                        }
                        break;
                    }

                    case 3:
                        insert_prior(
                            subject,
                            chapter,
                            priority,
                            0
                        );
                        break;

                    default:
                        printf("\nChoose option 1, 2 or 3 only.\n");
                }

                printf("\nAdd Topic operation completed.\n");
                printf("Now choose your next option from the main menu.\n");

                break;
            }


            /* ================= SEARCH / UPDATE / DELETE ================= */

            case 2:

                printf("\nYou selected: Search / Update / Delete a Topic\n");
                printf("Choose this option to search a topic first.\n");

                if(head == NULL){
                    printf("List is empty. Nothing to search.\n");
                }
                else{
                    search_topic();
                }

                printf("\nNow choose your next option from the main menu.\n");

                break;


            /* ================= DELETE ================= */

            case 3:

                printf("\nYou selected: Delete Topic\n");

                if(head == NULL){
                    printf("List is empty. Nothing to delete.\n");
                }
                else{
                    printf("\nChoose where you want to delete:\n");
                    printf("1. Front\n");
                    printf("2. Back\n");
                    printf("3. Anywhere in between\n");

                    printf("\nChoose option 1, 2 or 3 inside delete menu.\n");

                    pop();
                }

                printf("\nNow choose your next option from the main menu.\n");

                break;


            /* ================= DISPLAY ================= */

            case 4:

                printf("\nYou selected: Display All Topics\n");
                printf("Choose this option to see all topics in the master list.\n");

                if(head == NULL){
                    printf("List is empty.\n");
                }
                else{
                    print_all();
                }

                printf("\nNow choose your next option from the main menu.\n");

                break;


            /* ================= FILTER ================= */

            case 5:

                printf("\nYou selected: Filter Topics\n");
                printf("Choose the filter you want:\n");
                printf("1. Pending\n");
                printf("2. Completed\n");
                printf("3. Specific Priority\n");

                printf("\nChoose option 1, 2 or 3 inside filter menu.\n");

                if(head == NULL){
                    printf("List is empty. Nothing to filter.\n");
                }
                else{
                    filter_via();
                }

                printf("\nNow choose your next option from the main menu.\n");

                break;


            /* ================= ENQUEUE ================= */

            case 6:

                printf("\nYou selected: Add Topics to Today's Queue\n");

                if(head == NULL){
                    printf("Master list is empty, nothing to add to queue.\n");
                }
                else{
                    printf("Choose Pending/Completed first.\n");
                    printf("Then choose High/Medium/Low.\n");
                    printf("Then enter how many tasks you want to study.\n");

                    enqueue_ask();
                }

                printf("\nNow choose your next option from the main menu.\n");

                break;


            /* ================= DISPLAY QUEUE ================= */

            case 7:

                printf("\nYou selected: Show Today's Queue\n");
                printf("Choose this option to display your current study queue.\n");

                display_queue();

                printf("\nNow choose your next option from the main menu.\n");

                break;


            /* ================= DEQUEUE ================= */

            case 8:

                printf("\nYou selected: Study Next Topic\n");
                printf("Choose this option to remove and study the first topic in today's queue.\n");

                dequeue();

                printf("\nNow choose your next option from the main menu.\n");

                break;


            /* ================= MASTER PROGRESS ================= */

            case 9:

                printf("\nYou selected: Show Progress (Master List)\n");
                printf("Choose this option to see progress of the complete master list.\n");

                show_progress();

                printf("\nNow choose your next option from the main menu.\n");

                break;


            /* ================= QUEUE PROGRESS ================= */

            case 10:

                printf("\nYou selected: Show Progress (Today's Queue)\n");
                printf("Choose this option to see progress of today's study queue.\n");

                show_progress_queue();

                printf("\nNow choose your next option from the main menu.\n");

                break;


            /* ================= CREATE PLAN ================= */

            case 11:

                printf("\nYou selected: Create Plan\n");

                if(head == NULL){
                    printf("Master list is empty. Add topics first.\n");
                }
                else{
                    creation_plan();
                }

                printf("\nNow choose your next option from the main menu.\n");

                break;


            /* ================= CHECK PLAN ================= */

            case 12:

                printf("\nYou selected: Check Plan\n");

                check_plan();

                printf("\nNow choose your next option from the main menu.\n");

                break;


            /* ================= UPDATE PLAN ================= */

            case 13:

                printf("\nYou selected: Update Plan\n");

                update_plan();

                printf("\nNow choose your next option from the main menu.\n");

                break;


            /* ================= DELETE PLAN ================= */

            case 14:

                printf("\nYou selected: Delete Plan\n");

                delete_plan();

                printf("\nNow choose your next option from the main menu.\n");

                break;


            /* ================= FILL QUEUE FROM PLAN ================= */

            case 15:

                printf("\nYou selected: Fill Today's Queue from Plan\n");

                if(plan.exists == 0){
                    printf("You have no plan yet. Create one first (option 11).\n");
                }
                else{
                    fill_queue_from_plan();
                }

                printf("\nNow choose your next option from the main menu.\n");

                break;


            /* ================= SAVE & EXIT ================= */

            case 16:

                printf("\nYou selected: Save & Exit\n");
                printf("Saving all current data...\n");

                currMode = save_master;
                save_data();

                currMode = save_queue;
                save_data();

                currMode = save_plan;
                save_data();

                printf("Data saved successfully.\n");
                printf("Exiting Study Management System. Goodbye!\n");

                return 0;


            /* ================= INVALID ================= */

            default:

                printf("\nInvalid choice.\n");
                printf("Choose option from 1 to 16 only.\n");

                break;
        }

        printf("\nPress Enter and then choose your next option...\n");
        getchar();
        getchar();
    }

    return 0;
}