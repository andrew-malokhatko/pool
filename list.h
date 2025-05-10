#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct ListNode
{
    void* data;
    struct ListNode* next;
} ListNode;

typedef struct List
{
    ListNode* head;
    int size;
    int element_size;
} List;


List list_init(int element_size);

void list_add(List* list, const void* data);

// Remove the first element matching data (by comparing memory)
bool list_remove(List* list, const void* data);


void free_list(List* list);

#endif