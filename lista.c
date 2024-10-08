#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "estruturas.h"

lista* lista_criar (int k){//dupla linked list;
    lista *list = (lista*) malloc (sizeof (lista));
    
    if (list == NULL){
        printf ("erro pra alocar\n");
        exit(1);
    }

    list->tamanho = 0;
    list->max = k;
    list->nodulo1 = NULL;

    return list;
}

void lista_apagar (lista *list){//sentido = início -> fim;
    while (list->nodulo1 != NULL){//livra os ponteiros com as diferenças;
        while (list->nodulo1->nodulo2 != NULL){//livra os ponteiros com os nomes;
            free (list->nodulo1->nodulo2->nome);
            list->nodulo1->nodulo2->nome = NULL;
            
            pessoa *tmp;
            tmp = list->nodulo1->nodulo2->next2;

            list->nodulo1->nodulo2->next2 = NULL;
            free (list->nodulo1->nodulo2);
            list->nodulo1->nodulo2 = tmp;
            tmp = NULL;
        }
        nota *tmp;
        tmp = list->nodulo1->next;

        list->nodulo1->next = NULL;
        free (list->nodulo1);

        list->nodulo1 = tmp;
        tmp = NULL;
    }
    free (list);
    list = NULL;
}

void lista_inserir (char *aluno, int diff, lista *list){
    nota *tmp;
    nota *tmp2 = NULL;
    tmp = list->nodulo1;
    bool flag = true;

    if ((list->tamanho) == 0){//se vazia, inserir diretamente;
        list->nodulo1 = (nota*) malloc (sizeof (nota));
        tmp = list->nodulo1;

        tmp->diferenca = diff;
        tmp->next = NULL;

        tmp->nodulo2 = (pessoa*) malloc (sizeof (pessoa));
        tmp->nodulo2->nome = (char*) malloc (sizeof(char) * 51);

        strcpy (tmp->nodulo2->nome, aluno);
        tmp->nodulo2->next2 = NULL;

        tmp = NULL;
        tmp2 = NULL;
    }else{
        while (diff < tmp->diferenca){//introduzir ordenadamente na lista;
            flag = false;
            if (tmp->next != NULL){
                tmp2 = tmp;
                tmp = tmp->next;
            }else{  
                break;
            }
        }
        if (diff == tmp->diferenca){//se igual, criar novo nódulo2 (nome) e inserir lexicograficamente;
            pessoa *new = (pessoa*) malloc (sizeof (pessoa));
            pessoa *tmp3 = NULL;
            new->nome = (char*) malloc (sizeof (char)*51);
            strcpy (new->nome, aluno);
            new->next2 = tmp->nodulo2;
            bool flag2 = true;

            while ((new->next2 != NULL) && (strcmp (aluno, new->next2->nome) > 0)){
                flag2 = false;
                tmp3 = new->next2;
                new->next2 = new->next2->next2;
            }
            if (tmp3 != NULL){
                tmp3->next2 = new;
            }

            if (flag2 == true){
                tmp->nodulo2 = new;
            }

            tmp2 = NULL;
            tmp3 = NULL;
            tmp = NULL;
        }else{//se diferente, criar novo nódulo1 (nota) e inserir a pessoa;
            nota *new = (nota*) malloc (sizeof (nota));
            new->diferenca = diff;

            if ((flag == false) && (tmp->next != NULL)){//se tu estiver no meio da lista;
                tmp2->next = new;
                new->next = tmp;
            }

            if ((tmp->next == NULL) && (flag == false)){//se for o que vai cair por último na fila ou  estiver no meio;
                if (diff > tmp->diferenca){//vai pro meio;
                    tmp2->next = new;
                    new->next = tmp;
                }else{//vai pro fim
                    tmp->next = new;
                    new->next = NULL;
                }
            }

            new->nodulo2 = (pessoa*) malloc (sizeof (pessoa));
            new->nodulo2->next2 = NULL;
            new->nodulo2->nome = (char*) malloc (sizeof(char) * 51);
            strcpy (new->nodulo2->nome, aluno);

            if (flag == true){//se voce for o maior da lista;
                list->nodulo1 = new;
                new->next = tmp;
            }

            tmp = NULL;
            tmp2 = NULL;
        }
    }

    list->tamanho++;
}
