# Study Management System

A console-based study topic manager written in C, built around a **doubly linked list** with **priority-based sorted insertion**. Created as a learning project to practice core data structure operations beyond textbook basics — insertion at any position, priority-ordered insertion, and safe deletion from the front, back, or middle of a list.

## Features

- **Add topics** — front, back, or automatically by priority
- **Priority-sorted insertion** — new topics are automatically placed in the correct position so the list stays ordered from highest to lowest priority, without the user choosing where
- **Delete topics** — from the front, the back, or any position in the middle, with confirmation prompts
- **Display all topics** — formatted, readable output showing subject, chapter, priority, and completion status
- **Single-user, in-memory** — all data lives in the linked list during runtime (persistence via file save/load is a planned addition)

## Architecture

The project is split into focused files, each with a single responsibility:

```
StudyManager/
├── topic.h       # struct Topic definition, extern head/tail, all function prototypes
├── globals.c      # actual definitions of head and tail
├── insert.c       # insert_init, insertfront, insertback, insert_any, insert_prior
├── delete.c       # pop, popfront, popback, popany
├── display.c      # print_topic, print_all
└── main.c         # program entry point
```

**Why split this way:** `topic.h` acts as the shared "contract" — every other file includes it to know about the `Topic` struct and available functions, without needing to see each other's implementation details.

## Data structure

```c
typedef struct Topic {
    char subject[50];
    char chapter[50];
    int priority;           // 1 = High, 0 = Medium, -1 = Low
    int is_done;             // 0 = Pending, 1 = Completed
    struct Topic *next;
    struct Topic *prev;
} Topic;
```

A **doubly linked list** was chosen (over a singly linked list) so that deletion from the back and insertion before a given node can be done in O(1) once the position is found, without needing to track a separate "previous" pointer during traversal.

## Key function: `insert_prior()`

This is the core piece of logic in the project — it takes a new topic and finds its correct sorted position automatically:

1. If the list is empty, insert at the front.
2. Otherwise, walk the list while the new topic's priority is lower than or equal to the current node's priority.
3. If the walk reaches the end (`NULL`), append at the back.
4. Otherwise, insert the new node **before** the node where the walk stopped, using `insert_any()` — which rewires four pointers (`node`, `temp`, and their neighbors) and correctly updates `head` if the insertion happens at the very front.

## Build & Run

**Compile all source files together:**
```bash
gcc *.c -o study_manager
```

**Run:**
```bash
./study_manager        # Linux/macOS
.\study_manager.exe    # Windows PowerShell
```

## Usage

The current `main.c` runs a scripted demonstration exercising every operation — priority inserts, direct front/back inserts, full-list display, and all three deletion modes. A menu-driven interface (`switch`-based, similar to the existing `pop()` menu) is the next planned addition so the program can be used interactively.

## Roadmap

- [ ] Interactive master menu for insert/delete/display (switch-based)
- [ ] File-based persistence (save/load topic list on exit/startup)
- [ ] Subtopic support via a `child` pointer (tree-like structure for topics with subtopics)
- [ ] Study session queue separate from the master topic list
- [ ] Progress statistics (percentage complete, pending count)

## Tech

- Language: C
- No external libraries — only `stdio.h`, `stdlib.h`, `string.h`
- Compiled and tested with `gcc`