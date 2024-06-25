#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "header_trab.h"

//incializa arvore
pNodoA* cria_arvore()
{
    return NULL;
}

void preFixadoEsq(pNodoA* a)
{
    if(a != NULL)
    {
        printf("a palavra e: %s \n e seu escore e: %f\n", a->palavra, a->escore);
        preFixadoEsq(a->esq);
        preFixadoEsq(a->dir);
    }
}

pNodoA* rotacao_direita(pNodoA* p)
{
    pNodoA *u;

    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;

    return p;
}

pNodoA* rotacao_esquerda(pNodoA *p)
{
    pNodoA *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
}

pNodoA* rotacao_dupla_direita(pNodoA* p)
{
    pNodoA *u, *v;

    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;

    if(v->FB == 1)
        p->FB = -1;
    else
        p->FB = 0;
    if(v->FB == -1)
        u->FB = 1;
    else
        u->FB = 0;

    p = v;

    return p;
}

pNodoA* rotacao_dupla_esquerda(pNodoA* p)
{
    pNodoA *z, *y;

    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir =y->esq;
    y->esq = p;

    if(y->FB == -1)
        p->FB = 1;
    else
        p->FB = 0;
    if(y->FB == 1)
        z->FB = -1;
    else
        z->FB = 0;

    p = y;

    return p;
}

//------------------------------------------------------------------------

// Função para inserir o lexico na avl
pNodoA* InsereAVL(pNodoA* a, char* palavra, float escore, int* ok) {

    //enquanto a nao for null
    if (a == NULL) {

        a = (pNodoA*)malloc(sizeof(pNodoA)); //aloca
        strcpy(a->palavra, palavra); //pega palavra passada nada main
        a->escore = escore;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
        a->altura = 1;

        //stricmp compara duas palavras, e ve qual eh maior, sem case sentive
    }else if (stricmp(a->palavra, palavra) > 0)     //nova palavra eh menor q a palavra (raiz), entao aloca na esquerda
    {
        a->esq = InsereAVL(a->esq, palavra, escore, ok);

        if(*ok)
        {
            switch (a->FB)
            {
            case -1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = 1;
                break;
            case 1:
                a = Caso1(a,ok);
                break;
            }
        }

    } else {

        a->dir = InsereAVL(a->dir, palavra, escore, ok);

        if(*ok)
        {
            switch(a->FB)
            {
            case 1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = -1;
                break;
            case -1:
                a = Caso2(a,ok);
                break;
            }
        }
    }

    return a;

}

// Função para buscar o escore de polaridade de uma palavra na AVL
float consultaAVL (pNodoA* a, char* chave)
{
    if( a == NULL)
    {
        return 0.00;

    }else if(stricmp(a->palavra, chave) == 0)
    {
        return a->escore;
    }else if (stricmp(a->palavra, chave) > 0){
        consultaAVL(a->esq, chave);
    }else{
        consultaAVL(a->dir, chave);
    }

}


//----------------------------------------------------
pNodoA* Caso1(pNodoA* a, int* ok)
{
    pNodoA *z;

    z =a->esq;

    if(z->FB == 1)
        a = rotacao_direita(a);
    else
        a = rotacao_dupla_direita(a);

    a->FB = 0;
    ok = 0;
    return a;
}

pNodoA* Caso2(pNodoA* a, int* ok)
{
    pNodoA *z;

    z = a->dir;
    if(z->FB == -1)
        a = rotacao_esquerda(a);
    else
        a = rotacao_dupla_esquerda(a);

    a->FB = 0;
    ok = 0;

    return a;
}
//----------------------------------------------------

int Altura (pNodoA* a)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
        return 0;
    else
    {
        Alt_Esq = Altura(a->esq);
        Alt_Dir = Altura(a->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}

void imprimeIndentado(pNodoA *a, int nivel)
{
    if (a != NULL)
    {
        for (int i = 0; i < nivel; i++)
        {
            printf("=");
        }
        printf("=%s %.2f\n", a->palavra, a->escore);
        imprimeIndentado(a->esq, nivel + 1);
        imprimeIndentado(a->dir, nivel + 1);
    }
}

//-----------------------------------------------------------





