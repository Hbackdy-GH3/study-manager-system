#include "topic.h"

void print_menu(){
    printf("\n========================================\n");
    printf("      STUDY MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Add Topic\n");
    printf("2. Search / Update / Delete a Topic\n");
    printf("3. Delete Topic (front/back/anywhere)\n");
    printf("4. Display All Topics\n");
    printf("5. Filter Topics\n");
    printf("6. Save & Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}

int main() {
    load_data();   // program start hote hi purana saved data wapas le aao

    int choice;
    char subject[50], chapter[50];
    int priority;

    while(1) {
        print_menu();
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                int add_choice;
                printf("\n--- Add Topic ---\n");
                printf("1. Add at Front\n");
                printf("2. Add at Back\n");
                printf("3. Add by Priority (recommended)\n");
                printf("Enter your choice: ");
                scanf("%d", &add_choice);

                printf("Enter subject: ");
                scanf(" %49[^\n]", subject);
                printf("Enter chapter: ");
                scanf(" %49[^\n]", chapter);
                printf("Enter priority (1=High, 0=Medium, -1=Low): ");
                scanf("%d", &priority);

                switch(add_choice) {
                    case 1: {
                        Topic* node = insert_init(subject, chapter, priority, 0);
                        if(node != NULL) insertfront(node);
                        break;
                    }
                    case 2: {
                        Topic* node = insert_init(subject, chapter, priority, 0);
                        if(node != NULL) insertback(node);
                        break;
                    }
                    case 3:
                        insert_prior(subject, chapter, priority, 0);
                        break;
                    default:
                        printf("Invalid choice, nothing added.\n");
                }
                break;
            }

            case 2:
                if(head == NULL){
                    printf("List is empty. Nothing to search.\n");
                } else {
                    search_topic();
                }
                break;

            case 3:
                if(head == NULL){
                    printf("List is empty. Nothing to delete.\n");
                } else {
                    pop();
                }
                break;

            case 4:
                if(head == NULL){
                    printf("List is empty.\n");
                } else {
                    print_all();
                }
                break;

            case 5:
                if(head == NULL){
                    printf("List is empty. Nothing to filter.\n");
                } else {
                    filter_via();
                }
                break;

            case 6:
                save_data();
                printf("Data saved. Exiting Study Management System. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please enter 1 to 6.\n");
        }
    }

    return 0;
}