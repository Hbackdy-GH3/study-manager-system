# Study Management System

A console-based study topic manager written in C, built around a **doubly linked list** with **priority-based sorted insertion**. Created as a learning project to practice core data structure operations beyond textbook basics — insertion at any position, priority-ordered insertion, and safe deletion from the front, back, or middle of a list.

## Features

- **Add topics** — front, back, or automatically by priority
- **Priority-sorted insertion** — new topics are automatically placed in the correct position so the list stays ordered from highest to lowest priority, without the user choosing where
- **Search topics** — case-insensitive lookup by subject and chapter, returning a pointer to the matching node for reuse by other features
- **Update topics** — change a topic's priority or completion status after finding it via search; a priority change automatically **re-sorts the list** by detaching and reinserting the same node (no memory reallocated, no data duplicated)
- **Delete topics** — from the front, the back, any position in the middle, or directly from a search result — with confirmation prompts
- **Display all topics** — formatted, readable output showing subject, chapter, priority, and completion status
- **Single-user, in-memory** — all data lives in the linked list during runtime (persistence via file save/load is a planned addition)

## Architecture

The project is split into focused files, each with a single responsibility:

```
StudyManager/
├── topic.h       # struct Topic definition, extern head/tail, all function prototypes
├── globals.c      # actual definitions of head and tail
├── insert.c       # insert_init, insertfront, insertback, insert_any,
│                   # insert_node_by_priority, insert_prior, remove_node
├── delete.c       # pop, popfront, popback, popany
├── search.c       # case-insensitive search (CI), search_topic, searched_action
├── update.c       # update_priority (with re-sort), update_status
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

## Key function: `update_priority()` — reposition without reallocating

Changing a topic's priority needs the list to stay sorted, but naively removing and re-`malloc`ing a new node would leak the old one and waste an allocation for data that hasn't actually changed. Instead:

1. `remove_node()` detaches the existing node from the list (handles head, tail, and middle cases) — the node itself is **not** freed, since it's about to be reinserted.
2. The node's `priority` field is updated in place.
3. `insert_node_by_priority()` — a helper shared with `insert_prior()` — walks the list and reinserts the *same* node at its new correct position.

This keeps exactly one allocation per topic for its entire lifetime, whether it's newly created or repeatedly re-prioritized.

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

The current `main.c` runs a scripted demonstration exercising every operation — priority inserts, direct front/back inserts, search, update, full-list display, and all deletion modes (front/back/middle/via-search). A menu-driven interface (`switch`-based, similar to the existing `pop()` menu) is the next planned addition so the program can be used interactively.

Searching a topic (`search_topic()`) opens an action menu (`searched_action()`) letting the user view details, update priority, update status, delete the topic, or cancel — all operating on the same node found by the search, without re-traversing the list.

## Roadmap

- [x] Search by subject/chapter (case-insensitive)
- [x] Update priority (auto re-sorts the list) and status
- [ ] Filters — show pending/completed topics, or filter by priority
- [ ] Interactive master menu for insert/delete/search/display (switch-based)
- [ ] File-based persistence (save/load topic list on exit/startup)
- [ ] Subtopic support via a `child` pointer (tree-like structure for topics with subtopics)
- [ ] Study session queue separate from the master topic list
- [ ] Progress statistics (percentage complete, pending count)

## Tech

- Language: C
- No external libraries — only `stdio.h`, `stdlib.h`, `string.h`
- Compiled and tested with `gcc`