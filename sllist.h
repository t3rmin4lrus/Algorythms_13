#include <stdio.h>
#include <stdlib.h>
#include "./sllist.h"

void initialList(SLList *list)
{
        list->head = NULL;
        list->size = 0;
}

int push(SLList *stack, int data)
{
        Node *node = (Node *)malloc(sizeof(Node));
        if (node == NULL) {
                fprintf(stderr, "Stack overflow!\n");
                return 0;
        }
        node->data = data;
        node->next = stack->head;
        stack->head = node;
        stack->size++;

        return 1;
}

int pop(SLList *list)
{
        int data;
        Node *tmp;

        if (list->size == 0)
                return -1;
        data = list->head->data;
        tmp = list->head;
        list->size--;
        if (list->size == 0) {
                list->head = NULL;
        } else {
                list->head = list->head->next;
        }
        free(tmp);

        return data;
}

void freeList(SLList *list)
{
        Node *tmp;

        while (list->size > 0) {
                tmp = list->head;
                list->size--;
                if (list->size > 0)
                        list->head = list->head->next;
                free(tmp);
        }
        free(list);
}
