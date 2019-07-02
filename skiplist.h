typedef struct no *No;

typedef struct lista *Lista;


Lista cria_lista();
int lista_vazia(Lista Vetorzin);
int num_aleatorio();
int insere(Lista Vetorzin, int elem);
int busca_elem(Lista Vetorzin, int x);
int imprime_lista(Lista Vetorzin, int nivel);
int tamanho_lista(Lista Vetorzin);
void libera_lista(Lista Vetorzin);
int remove_elem(Lista Vetorzin,int x);
int insere_elem(Lista Vetorzin, int x);
