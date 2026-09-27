# Study Management System

A console-based study topic manager written in C, built around a **doubly linked list** with **priority-based sorted insertion**, search, filters, and file persistence. Created as a learning project to practice core data structure operations beyond textbook basics.

## Features

- **Add topics** — front, back, or automatically by priority
- **Priority-sorted insertion** — new topics are automatically placed in the correct position
- **Search topics** — case-insensitive lookup by subject and chapter (supports multi-word input)
- **Update topics** — change priority (auto re-sorts the list) or completion status after finding a topic via search
- **Delete topics** — front, back, anywhere in the middle, or directly from a search result
- **Filter topics** — view pending only, completed only, or by specific priority (High/Medium/Low)
- **Interactive menu** — full CLI menu connecting every feature
- **File persistence** — data is automatically saved to `data.txt` on every insert, update, and delete, and loaded back on startup

## Architecture

```
StudyManager/
├── topic.h          # struct Topic, extern head/tail, all function prototypes
├── globals.c         # actual definitions of head and tail
├── insert.c          # insert_init, insertfront, insertback, insert_any,
│                      # insert_node_by_priority, insert_prior, remove_node
├── delete.c          # pop, popfront, popback, popany
├── search.c           # case-insensitive search (CI), search_topic, searched_action
├── update.c           # update_priority (with re-sort), update_status
├── filters.c          # filter_via — pending/completed/priority filters
├── filehandling.c      # save_data, load_data
├── display.c           # print_topic, print_all
└── main.c              # interactive menu, program entry point
```

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

A **doubly linked list** was used so deletion and reinsertion (for priority updates) can be done in O(1) once the position is found, without tracking a separate "previous" pointer during traversal.

## Key design decisions

**Priority-sorted insertion (`insert_prior`)** — walks the list comparing priorities and inserts the new node in the correct position automatically, rather than requiring the user to choose front/back.

**Reposition without reallocating (`update_priority`)** — when a topic's priority changes, the existing node is detached with `remove_node()` (not freed) and reinserted via `insert_node_by_priority()`. This avoids a memory leak and an unnecessary `malloc`, keeping exactly one allocation per topic for its lifetime.

**Multi-word input handling** — subject and chapter fields accept spaces (e.g. "Fourier series") using `scanf(" %49[^\n]", ...)` instead of `%s`, which stops at the first space.

**File persistence** — the list is saved to `data.txt` as comma-separated lines after every structural change (insert/update/delete), and reloaded automatically when the program starts, so data survives between runs.

## Build & Run

```bash
gcc *.c -o study_manager
./study_manager        # Linux/macOS
.\study_manager.exe    # Windows PowerShell
```

## Usage

Running the program loads any previously saved topics, then presents a menu:

```
1. Add Topic
2. Search / Update / Delete a Topic
3. Delete Topic (front/back/anywhere)
4. Display All Topics
5. Filter Topics
6. Save & Exit
```

Searching a topic opens an action menu to view details, update priority/status, delete it, or cancel — all operating on the node found by the search.

## Roadmap

- [x] Search by subject/chapter (case-insensitive, multi-word)
- [x] Update priority (auto re-sorts the list) and status
- [x] Filters (pending/completed/priority)
- [x] Interactive master menu
- [x] File-based persistence (save/load)
- [ ] Separate study-session Priority Queue (distinct from the master topic list)
- [ ] Subtopic support via a `child` pointer
- [ ] Progress statistics (percentage complete, pending count)
- [ ] WebAssembly build for a browser-based frontend

## Tech

- Language: C
- No external libraries — only `stdio.h`, `stdlib.h`, `string.h`
- Compiled and tested with `gcc`