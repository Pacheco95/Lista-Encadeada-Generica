#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

void ShowList (LinkedList *list);

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



    LinkedList_Insert(&list, &x, LAST_POS);

    if (LinkedList_IsEmpty(&list))
        printf("Lista vazia!\n");
    else
        printf("Lista nao vazia!\n");

    ShowList(&list);
    x++;
    LinkedList_Insert(&list, &x, LAST_POS);
	
    ShowList(&list);
    x++;
    LinkedList_Insert(&list, &x, LAST_POS);
    ShowList(&list);
    x++;
    LinkedList_Insert(&list, &x, LAST_POS);
    ShowList(&list);
    x++;
    LinkedList_Insert(&list, &x, LAST_POS);
    ShowList(&list);
    x = 10;

    printf("Todos os elementos foram inseridos...\n");
    printf("Tamanho da lista: %d\n", LinkedList_GetSize(&list));


    int *backup = (int*) malloc(sizeof (int));
    printf("Elemento a ser removido: %d\n", *(  (int*) LinkedList_Get(&list, 0)  ));
    LinkedList_Remove(&list, 0, backup);

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

