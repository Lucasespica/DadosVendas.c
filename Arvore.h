#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

//As bibliotecas ja estao inclusas, nao precisa no main
//precisamos alterar as coisas na biblioteca
//e tirar os comentarios no final
typedef struct NoArvore
{
    int info;
    struct NoArvore *esq;
    struct NoArvore *dir;

}NoArv;

typedef struct Arvore
{
    NoArv *raiz;

}Arv;

Arv *criaArv()
{
    Arv *a1;
    a1 = (Arv*)malloc(sizeof (Arv));
    a1->raiz = NULL;
    return a1;
}

void preOrder(NoArv *a1)
{
    printf("%d ", a1->info);
    if (a1->dir != NULL)
    {
        preOrder(a1->dir);
    }
    if (a1->esq != NULL)
    {
        preOrder(a1->esq);
    }
}

void posOrder(NoArv *a1)
{
    if (a1->dir != NULL)
    {
        posOrder(a1->dir);
    }
    if (a1->esq != NULL)
    {
        posOrder(a1->esq);
    }
    printf("%d ", a1->info);
}

void inOrder(NoArv *a1)
{
    if (a1->dir != NULL)
    {
        inOrder(a1->dir);
    }
    printf("%d ", a1->info);
    if (a1->esq != NULL)
    {
        inOrder(a1->esq);
    }
}

int Arv_vazia(Arv *a1)
{
    if (a1->raiz == NULL){
        return 1;
    }
    return 0;
}

int Busca(NoArv *a1, int num)
{
    NoArv *pai = a1;
    if (pai->info == num)
    {
        return 1;
    }
    if (num > pai->info)
    {
        if (pai->dir != NULL)
        {
            return Busca(pai->dir, num);
        }
        return 0;
    }
    if (pai->esq != NULL)
    {
        return Busca(pai->esq, num);
    }
    return 0;
}

NoArv *aux_insere(NoArv *no, int num)
{
    int flag;
    NoArv *Pai;
    NoArv *novo = (NoArv*)malloc(sizeof(NoArv));
    novo->info = num;
    novo->dir = NULL;
    novo->esq = NULL;
    if (no == NULL)
    {
        return novo;
    }
    else
    {
        Pai = no;
        flag = 0;
        while (flag == 0)
        {
            if (Pai->info == num)
            {
                printf("\nNumero repetido.");
                free(novo);
                return no;
            }
            if (num > Pai->info)
            {
                if (Pai->dir == NULL)
                {
                    Pai->dir = novo;
                    flag = 1;
                }
                else
                {
                    Pai = Pai->dir;
                }
            }
            else
            {
                if (num < Pai->info)
                {
                    if (Pai->esq == NULL)
                    {
                        Pai->esq = novo;
                        flag = 1;
                    }
                    else
                    {
                        Pai = Pai->esq;
                    }
                }
            }
        }
    }
    return no;
}

void insereArv(Arv *arvore, int num)
{
    arvore->raiz = aux_insere(arvore->raiz,num);
}

NoArv *remover_aux(NoArv *Pai, int num)
{
    if (Pai == NULL)
    {
        printf("\nNúmero não encontrado na árvore.\n");
        return NULL;
    }

    if (num > Pai->info)
    {
        Pai->dir = remover_aux(Pai->dir, num);
    }
    else
    {
        if (num < Pai->info)
        {
            Pai->esq = remover_aux(Pai->esq, num);
        }
        else
        {
            if (Pai->dir == NULL && Pai->esq == NULL)
            {
                free(Pai);
                return NULL;
            }
            else
            {
                if (Pai->esq == NULL)
                {
                    NoArv *aux = Pai;
                    Pai = Pai->dir;
                    free(aux);
                }
                else
                {
                    if (Pai->dir == NULL)
                    {
                        NoArv *aux = Pai;
                        Pai = Pai->esq;
                        free(aux);
                    }
                    else
                    {
                        NoArv *aux = Pai->esq;
                        while (aux->dir != NULL)
                        {
                            aux = aux->dir;
                        }

                        Pai->info = aux->info;
                        Pai->esq = remover_aux(Pai->esq, aux->info);
                    }
                }
            }
        }
    }
    return Pai;
}


Arv *remover(Arv *RAIZ, int num)
{
    NoArv *aux = RAIZ->raiz;
    if (aux->info == num && aux->dir == NULL && aux->esq == NULL)
    {
        free(aux);
        free(RAIZ);
        return NULL;
    }
    RAIZ->raiz = remover_aux(RAIZ->raiz, num);
    return RAIZ;
}

NoArv *liberaArv(NoArv *a1)
{
    if (a1 == NULL)
    {
        return NULL;
    }
    if (a1->dir != NULL)
    {
        liberaArv(a1->dir);
    }
    if (a1->esq != NULL)
    {
        liberaArv(a1->esq);
    }
    free(a1);
    return NULL;
}

#endif // ARVORE_H_INCLUDED
