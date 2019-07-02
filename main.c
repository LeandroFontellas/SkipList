#include <stdio.h>
#include <stdlib.h>
#include "skiplist.h"

int main()
{
  	Lista sl;

	sl = cria_lista();
    /*remove n funciona*/
    insere_elem(sl, 2);
    insere_elem(sl, 3);
    insere_elem(sl, 1);
    insere_elem(sl, 10);
    insere_elem(sl, 5);
    imprime_lista(sl, 4);
    printf("\n");
    imprime_lista(sl, 3);
    printf("\n");
    imprime_lista(sl, 2);
    printf("\n");
    imprime_lista(sl, 1);
    printf("\n");
    imprime_lista(sl, 0);


    libera_lista(sl);

    return 0;
}
