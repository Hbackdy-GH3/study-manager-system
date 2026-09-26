#include "topic.h"

int main() {
    printf("########## PHASE 1: PRIORITY INSERTS ##########\n");
    insert_prior("Physics", "Optics", 0, 0);
    insert_prior("Maths", "Calculus", 1, 0);
    insert_prior("Chemistry", "Bonding", -1, 0);
    insert_prior("Biology", "Genetics", 0, 0);

    printf("\n########## PHASE 2: DIRECT insertfront/insertback ##########\n");
    Topic* t1 = insert_init("CS", "Sorting", 1, 0);
    insertfront(t1);

    Topic* t2 = insert_init("English", "Grammar", -1, 0);
    insertback(t2);

    printf("\n########## CURRENT FULL LIST ##########\n");
    print_all();

    printf("\n########## PHASE 3: popfront() ##########\n");
    popfront();
    // jab poochhe "delete karna hai?", 1 (Yes) dena

    printf("\n########## PHASE 4: popback() ##########\n");
    popback();
    // jab poochhe, 1 (Yes) dena

    printf("\n########## PHASE 5: popany() (middle deletion) ##########\n");
    popany();
    // list dikhegi, koi middle-wala number choose karna (1 ya last mat karna)

    printf("\n########## FINAL LIST AFTER ALL DELETIONS ##########\n");
    print_all();

    return 0;
}