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

typedef struct Data
{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct NoArvore
{
    int ID;
    char cliente[50];
    char vendedor[50];
    char matricula[4];
    Data dataTransacao;
    float valorVenda;
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
    printf("ID: %d| Vendedor: %s| Matrícula: %s| Cliente: %s| Data de Transacao: %d/%d/%d| Valor(R$): %f", a1->ID, a1->vendedor, a1->matricula,
           a1->dataTransacao.dia, a1->dataTransacao.mes, a1->dataTransacao.ano);
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
    printf("ID: %d| Vendedor: %s| Matrícula: %s| Cliente: %s| Data de Transacao: %d/%d/%d| Valor(R$): %f", a1->ID, a1->vendedor, a1->matricula,
           a1->dataTransacao.dia, a1->dataTransacao.mes, a1->dataTransacao.ano);
}

void inOrder(NoArv *a1)
{
    if (a1->dir != NULL)
    {
        inOrder(a1->dir);
    }
    printf("ID: %d| Vendedor: %s| Matrícula: %s| Cliente: %s| Data de Transacao: %d/%d/%d| Valor(R$): %f", a1->ID, a1->vendedor, a1->matricula,
           a1->dataTransacao.dia, a1->dataTransacao.mes, a1->dataTransacao.ano);
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
    if (pai->ID == num)
    {
        return 1;
    }
    if (num > pai->ID)
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

NoArv *aux_insere(NoArv *no, int num, char cliente[], char vendedor[], Data dataV, float venda, char matricula[])
{
    int flag;
    NoArv *Pai;
    NoArv *novo = (NoArv*)malloc(sizeof(NoArv));
    novo->ID = num;
    strcpy(novo->cliente, cliente);
    strcpy(novo->vendedor, vendedor);
    novo->dataTransacao = dataV;
    novo->valorVenda = venda;
    strcpy(novo->matricula, matricula);

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
            if (Pai->ID == num)
            {
                printf("\nNumero repetido.");
                free(novo);
                return no;
            }
            if (num > Pai->ID)
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
                if (num < Pai->ID)
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

void insereArv(Arv *arvore, int num, char cliente[], char vendedor[], Data dataV, float venda, char matricula[])
{
    arvore->raiz = aux_insere(arvore->raiz,num, cliente, vendedor, dataV, venda, matricula);
}

NoArv *remover_aux(NoArv *Pai, int num)
{
    if (Pai == NULL)
    {
        printf("\nNúmero não encontrado na árvore.\n");
        return NULL;
    }

    if (num > Pai->ID)
    {
        Pai->dir = remover_aux(Pai->dir, num);
    }
    else
    {
        if (num < Pai->ID)
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

                        Pai->ID = aux->ID;
                        Pai->esq = remover_aux(Pai->esq, aux->ID);
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
    if (aux->ID == num && aux->dir == NULL && aux->esq == NULL)
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
