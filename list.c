#include "list.h"

#include <stdlib.h>
#include <string.h>

List list_init(int element_size)
{
    List list;
    list.head = NULL;
    list.size = 0;
    list.element_size = element_size;
    return list;
}


void list_add(List* list, const void* data)
{
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    new_node->data = malloc(list->element_size);
    memcpy(new_node->data, data, list->element_size);

    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

// Remove the first element matching data (by comparing memory)
bool list_remove(List* list, const void* data)
{
    ListNode* current = list->head;
    ListNode* prev = NULL;

    while (current != NULL)
    {
        if (memcmp(current->data, data, list->element_size) == 0)
        {
            if (prev == NULL)
            {
                list->head = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            free(current->data);
            free(current);
            list->size--;
            return true;
        }

        prev = current;
        current = current->next;
    }

    return false;
}


void free_list(List* list)
{
    ListNode* current = list->head;
    ListNode* next;

    while (current != NULL)
    {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    list->head = NULL;
    list->size = 0;
}