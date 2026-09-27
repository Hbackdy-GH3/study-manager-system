# Study Management System

A console-based study topic manager written in C, built around a **doubly linked list** with **priority-based sorted insertion**, search, filters, a separate study-session priority queue, and file persistence. Created as a learning project to practice core data structure operations beyond textbook basics.

## Features

**Master Topic List (Doubly Linked List)**
- Add topics — front, back, or automatically by priority
- Priority-sorted insertion — new topics are placed in the correct position automatically
- Search topics — case-insensitive lookup by subject and chapter (supports multi-word input)
- Update topics — change priority (auto re-sorts the list) or completion status
- Delete topics — front, back, anywhere in the middle, or directly from a search result
- Filter topics — pending only, completed only, or by specific priority
- Progress summary — total, completed, pending counts and completion percentage

**Today's Study Queue (separate Priority Queue, independent of the master list)**
- Enqueue — filter the master list by status + priority, then pull N matching topics into today's queue (nodes reference the original master-list topics, not copies)
- Dequeue — pop the next topic to study from the front of the queue
- Display — view everything currently queued for today
- Task count — see how many topics remain in today's queue

**Persistence**
- The master list is automatically saved to `data.txt` after every insert, update, and delete, and reloaded on startup. The study queue is intentionally session-only and is not persisted.

## Architecture

```
StudyManager/
├── topic.h            # Topic & QueueNode structs, extern head/tail/front/back, all prototypes
├── globals.c           # actual definitions of head, tail, front, back
├── insert.c            # insert_init, insertfront, insertback, insert_any,
│                        # insert_node_by_priority, insert_prior, remove_node
├── delete.c            # pop, popfront, popback, popany
├── search.c             # case-insensitive search (CI), search_topic, searched_action
├── update.c             # update_priority (with re-sort), update_status
├── filters.c            # filter_via — pending/completed/priority filters
├── progress.c            # show_progress, show_progress_queue
├── queue.c               # filter (for enqueue), enqueue, dequeue, display_queue
├── file_handling.c        # save_data, load_data
├── display.c              # print_topic, print_all
└── main.c                 # interactive menu, program entry point
```

## Data structures

```c
typedef struct Topic {
    char subject[50];
    char chapter[50];
    int priority;           // 1 = High, 0 = Medium, -1 = Low
    int is_done;             // 0 = Pending, 1 = Completed
    struct Topic *next;
    struct Topic *prev;
} Topic;

typedef struct QueueNode {
    Topic* topic;             // pointer into the master list — no data duplication
    struct QueueNode *next;
} QueueNode;
```

The master list is a **doubly linked list** so deletion and reinsertion (for priority updates) can be done in O(1) once the position is found. The study queue is a simpler **singly linked list** with front/back pointers, since it only needs enqueue/dequeue, not arbitrary deletion.

## Key design decisions

**Priority-sorted insertion** — `insert_prior()` walks the master list and inserts new topics in the correct position automatically.

**Reposition without reallocating** — `update_priority()` detaches the existing node with `remove_node()` (not freed) and reinserts it via `insert_node_by_priority()`, avoiding a memory leak and an unnecessary allocation.

**Study queue references, not copies** — `QueueNode` stores a `Topic*` pointing back into the master list, so the queue always reflects the latest data without duplicating it.

**Filtered enqueue** — `enqueue()` uses a query-like `filter()` helper (status + priority) to pull a chosen number of matching topics into today's queue, similar to a database `WHERE` clause.

**Multi-word input handling** — subject and chapter fields accept spaces using `scanf(" %49[^\n]", ...)` instead of `%s`.

## Build & Run

```bash
gcc *.c -o study_manager
./study_manager        # Linux/macOS
.\study_manager.exe    # Windows PowerShell
```

## Menu

```
--- Master Topic List ---
1. Add Topic
2. Search / Update / Delete a Topic
3. Delete Topic (front/back/anywhere)
4. Display All Topics
5. Filter Topics
--- Today's Study Queue ---
6. Add Topics to Today's Queue
7. Show Today's Queue
8. Study Next Topic (Dequeue)
--- Progress ---
9. Show Progress (Master List)
10. Show Progress (Today's Queue)
--- Program ---
11. Save & Exit
```

Run through every option at least once to sanity-check the full system: add a few topics, search/update/delete one, filter, enqueue a batch by status+priority, display and dequeue the queue, check both progress views, then save & exit and relaunch to confirm the master list persisted (the queue should reset, by design).

## Roadmap

- [x] Search, update (with auto re-sort), filters
- [x] Interactive master menu
- [x] File-based persistence
- [x] Separate study-session priority queue (enqueue/dequeue/display)
- [x] Progress statistics (master list and queue)
- [ ] Subtopic support via a `child` pointer
- [ ] WebAssembly build for a browser-based frontend

## Tech

- Language: C
- No external libraries — only `stdio.h`, `stdlib.h`, `string.h`
- Compiled and tested with `gcc`