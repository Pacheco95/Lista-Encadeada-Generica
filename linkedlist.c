/*
*	Implementação de uma lista encadeada
*
*	Autor: Michael Douglas Pacheco
*	Data: 19/05/2015
*	Hora: 21:04
*/

#include "linkedlist.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool LinkedList_Init(LinkedList *list, int dataTypeSizeInBytes) {
    if (!list)
        return false;
    list->first = list->last = NULL;
    list->size = 0;
    list->dataTypeSizeInBytes = dataTypeSizeInBytes;
    return true;
}

bool LinkedList_IsEmpty (const LinkedList *list) {
    if (!list)
        return true;
    return (list->size == 0);
}

int LinkedList_GetSize (const LinkedList *list) {
    if (!list)
        return -1;
    return list->size;
}

void* LinkedList_Get (const LinkedList *list, int pos) {
    if (!list) // A lista é nula
        return NULL;
    if (pos < 0) // Posição inválida
        return NULL;
    if (list->size <= 0) // Lista vazia
        return NULL;
    if (pos >= list->size && pos != LAST_POS) // Posição inválida
        return NULL;

    if (pos == 0)
        return list->first->data;

    if (pos == LAST_POS || pos == list->size - 1) {
        return list->last->data;
    }

    Cell *f;
    for (register int i = 0; i < pos; i++) {
        if (i == 0)
            f = list->first;
        else
            f = f->next;
    }

    return f->next->data;
}

bool LinkedList_GetCopyOf (const LinkedList *list, int pos, void *backup) {
    if (!list) // A lista é nula
        return false;
    if (pos < 0) // Posição inválida
        return false;
    if (list->size <= 0) // Lista vazia
        return false;
    if (pos >= list->size && pos != LAST_POS) // Posição inválida
        return false;

    if (pos == 0) {
        memcpy(backup, list->first->data, list->dataTypeSizeInBytes);
        return true;
    }

    if (pos == LAST_POS || pos == list->size - 1) {
        memcpy(backup, list->first->data, list->dataTypeSizeInBytes);
        return true;
    }

    Cell *f;
    for (register int i = 0; i < pos; i++) {
        if (i == 0)
            f = list->first;
        else
            f = f->next;
    }

    memcpy(backup, f->next->data, list->dataTypeSizeInBytes);
    return true;
}

bool LinkedList_Insert (LinkedList *list, void *data, int pos) {
    if (!list)
        return false;

    if (pos == LAST_POS)
        pos = list->size;

    if (pos < 0 || pos > list->size) // Lista nula ou posição inválida
        return false;

    if (pos == 0) { // Insere na primeira posição

        Cell *temp = (Cell*) malloc(sizeof (Cell));

        temp->data = malloc(list->dataTypeSizeInBytes);
        memcpy(temp->data, data, list->dataTypeSizeInBytes);

        if (list->size == 0) {
            list->first = list->last = temp;
            temp->next = NULL;
            list->size++;
            return true;
        }

        temp->next = list->first;
        list->first = temp;
        list->size++;
        return true;
    }

    if (pos == list->size) { // Insere na última posição
        Cell *temp = (Cell*) malloc(sizeof (Cell));
        temp->data = malloc(list->dataTypeSizeInBytes);
        memcpy(temp->data, data, list->dataTypeSizeInBytes);

        if (list->size == 0) {
            list->first = list->last = temp;
            temp->next = NULL;
            list->size++;
            return true;
        } else {
            list->last->next = temp;
            list->last = temp;
            list->last->next = NULL;
        }

        list->size++;
        return true;
    }

    // Insere no meio
    Cell *f;
    for (register int i = 0; i < pos; i++) {
        if (i == 0)
            f = list->first;
        else
            f = f->next;
    }
    // Nesse momento 'f' aponta para a posição anterior à que será inserido o elemento

    Cell *temp = (Cell*) malloc(sizeof (Cell));
    temp->data = malloc(list->dataTypeSizeInBytes);
    memcpy(temp->data, data, list->dataTypeSizeInBytes);

    temp->next = f->next;
    f->next = temp;
    list->size++;
    return true;
}

bool LinkedList_Remove (LinkedList *list, int pos, void *backup) {
    if (!list) // A lista é nula
        return false;

    if (pos == LAST_POS)
        pos = list->size - 1;

    if (list->size <= 0) // Lista vazia
        return false;

    if (pos < 0 || pos >= list->size) // Posição inválida
        return false;

    // Remove da última posição
    if (pos == list->size - 1) {
        // Se a lista tiver apenas 1 elemento
        if (list->size == 1) {
            memcpy(backup, list->first->data, list->dataTypeSizeInBytes);
            LinkedList_Clear(list);
        }
        // A lista possui mais de um elemento
        else {
            Cell *f, *last;
            memcpy(backup, list->first->data, list->dataTypeSizeInBytes);

            // Percorre a lista até encontrar o penúltimo elemento da lista
            for (f = list->first; f != list->last; f = f->next)
                last = f;

            // Nesse momento 'last' aponta para o penúltimo elemeto da lista

            free(list->last->data); // Remove o dado do último elemento
            free(list->last); // Remove o último elemento
            list->last = last; // Agora o último elemento se torna 'last'
            list->last->next = NULL; // Portanto last->next deve ser NULL
            list->size--;
        }
        return true;
    }

    // O usiário deseja remover um elemento do início
    if (pos == 0) {
        if (list->size == 1) {
            memcpy(backup, list->first->data, list->dataTypeSizeInBytes);

            LinkedList_Clear(list); // Portanto, apenas limpe a lista!
        } else {
            Cell *nextCpy = list->first->next;
            memcpy(backup, list->first->data, list->dataTypeSizeInBytes);

            free(list->first->data);
            free(list->first);
            list->first = nextCpy;
            list->size--;
        }
        return true;
    }

    // O usuário quer remover algum elemento no MEIO da lista, ou seja, não é nem o primeiro nem o último
    Cell *f, *nextCpy;
    for (register int i = 0; i < pos; i++) {
        if (i == 0)
            f = list->first;
        else
            f = f->next;
    }
    // Nesse momento 'f' aponta para o elemento anterior ao que será removido

    nextCpy = f->next->next; // 'nextCpy' aponta para o elemento posterior ao que será removido
    memcpy(backup, f->next->data, list->dataTypeSizeInBytes);

    free(f->next->data); // Remove o VALOR do elemento (Célula) entre 'f' e 'nextCpy', que pertence justamente o elemento que o usuário deseja remover
    free(f->next); // Remove o ELEMENTO entre 'f' e 'nextCpy', que é justamente o elemento que o usuário deseja remover
    f->next = nextCpy; // Portanto lique 'f' em 'nextCpy'
    list->size--;
    return true;
}

void LinkedList_Clear (LinkedList *list) {
    if (list->size <= 0 || list->first == NULL)
        return;

    // 'curr' iniciará apontando para o primeiro elemento da lista e next para o segundo
    // (que pode ser nulo caso a lista possua apenas um elemento)

    register Cell *next;
    for (register Cell *p = list->first; p != NULL;) {
        next = p->next;
        free(p->data);
        free(p);
        p = next;
    }

    list->first = NULL;
    list->last = NULL;
    list->size = 0;
}

LinkedList* LinkedList_Duplicate (const LinkedList *list) {
    LinkedList *temp = (LinkedList*) malloc(list->dataTypeSizeInBytes);
    LinkedList_Init(temp, list->dataTypeSizeInBytes);
    for (Cell *p = list->first; p != NULL; p = p->next)
        LinkedList_Insert(temp, p->data, LAST_POS);
    return temp;
}
