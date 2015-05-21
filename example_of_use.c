#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

void ShowList (LinkedList *list) {
    for (register int i = 0; i < LinkedList_GetSize(list); ++i) {
        int x = *( (int*) LinkedList_Get(list, i) );
		printf("%d ", x);
    }
    printf("\n");
}

int main() {
    LinkedList list;
    LinkedList_Init(&list, sizeof(int));

    if (LinkedList_IsEmpty(&list))
        printf("Lista vazia!\n");
        
    else
        printf("Lista nao vazia!\n");


    int x = 10;

    LinkedList_PushBack(&list, &x);

    if (LinkedList_IsEmpty(&list))
        printf("Lista vazia!\n");
    else
        printf("Lista nao vazia!\n");

    ShowList(&list);
    x++;
    LinkedList_PushBack(&list, &x);
	
    ShowList(&list);
    x++;
    LinkedList_PushBack(&list, &x);
    ShowList(&list);
    x++;
    LinkedList_PushBack(&list, &x);
    ShowList(&list);
    x++;
    LinkedList_PushBack(&list, &x);
    ShowList(&list);
    x = 10;

    printf("Todos os elementos foram inseridos...\n");
    printf("Tamanho da lista: %d\n", LinkedList_GetSize(&list));


    int *backup = (int*) malloc(sizeof (int));
    printf("Elemento a ser removido: %d\n", *(  (int*) LinkedList_GetLast(&list)  ));
    LinkedList_PopBack(&list, backup);

    printf("O elemento removido foi salvo na variavel backup: %d\n", *backup);
    ShowList(&list);

    printf("Tamanho da lista: %d\n", LinkedList_GetSize(&list));

    puts("Limpando a lista...");
    LinkedList_Clear(&list);

    if (LinkedList_IsEmpty(&list))
        puts("Lista vazia!");
    else
        puts("Lista nao vazia!"), ShowList(&list);

    free(backup);
    return 0;
}

