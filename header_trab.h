//definicao de dados
#include<stdio.h>
#include<stdlib.h>

struct TNodoA
{
    char palavra[50];
    float escore;
    int FB;
    struct TNodoA *esq;
    struct TNodoA *dir;
    int altura;
};
typedef struct TNodoA pNodoA;

pNodoA* cria_arvore(void);
void preFixadoEsq(pNodoA* a);
pNodoA* rotacao_direita(pNodoA* p);
pNodoA* rotacao_esquerda(pNodoA* p);
pNodoA* rotacao_dupla_direita(pNodoA* p);
pNodoA* rotacao_dupla_esquerda(pNodoA* p);
//-------------------------------------------
pNodoA* InsereAVL(pNodoA* a, char* palavra, float escore, int* ok);
float consultaAVL(pNodoA* a, char* chave);
pNodoA* Caso1(pNodoA* a, int* ok);
pNodoA* Caso2(pNodoA* a, int* ok);
int Altura (pNodoA* a);
//--------------------------------------------
void imprimeIndentado(pNodoA* a, int nivel);
