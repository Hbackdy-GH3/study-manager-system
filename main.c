#include "topic.h"

int main() {
    printf("########## SETUP ##########\n");
    insert_prior("Physics", "Optics", 0, 0);
    insert_prior("Maths", "Calculus", 1, 0);
    insert_prior("Chemistry", "Bonding", -1, 0);
    insert_prior("Biology", "Genetics", 0, 0);

    printf("\n########## INITIAL LIST (High -> Low expected) ##########\n");
    print_all();

    printf("\n########## Updating Chemistry's priority from Low to High ##########\n");
    // search_topic() input: subject "Chemistry", chapter "Bonding"
    // then choice 2 (update priority), then enter 1 (High)
    search_topic();

    printf("\n########## LIST AFTER UPDATE (Chemistry should now be near the TOP) ##########\n");
    print_all();

    printf("\n########## Updating Maths's priority from High to Low ##########\n");
    // search_topic() input: subject "Maths", chapter "Calculus"
    // then choice 2 (update priority), then enter -1 (Low)
    search_topic();

    printf("\n########## LIST AFTER UPDATE (Maths should now be near the BOTTOM) ##########\n");
    print_all();

    return 0;
}