#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "header_trab.h"

int main(int argc, char *argv[]) //argc conta o numero de parametros e argv armazena as strings correspondentes aos paramentros digitados
{
    //int comp = 0;       //variavel global, conta as comparações

    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados

    clock_t start, end;  //para contar o tempo decorrido

    FILE * lexico;
    FILE * sentencas;       // dicionario entrada, lexico a ser utilizado
    FILE * saida;

    char *palavra, linha[10000]; // linhas a serem lidas do arquivo
    char separador[]= {" &*%\?!;/-'@\"$#=><()][}{:\n\t"};//.,

    //4 parametros:
    // 0 - executavel
    // 1 - lexico
    // 2 - sentencas
    // 3 - arq saida

    if (argc!=4)
    {
        printf ("Numero incorreto de parametros.\n Para chamar o programa digite: exemplo <arq_lexico> <arq_entrada> <arq_saida>\n");
        return 1;
    }
    else
    {

        lexico = fopen(argv[1], "r");         // informa arquivo com os lexicos
        if (lexico == NULL) //se nao conseguiu abrir o arquivo...informa erro
        {
            printf ("Erro ao abrir o arquivo %s",argv[1]);
            return 1;
        }else{

            sentencas = fopen (argv[2], "r"); //informa arquivo com as sentencas
            if (sentencas == NULL) //se nao conseguiu abrir o arquivo...
            {
                printf ("Erro ao abrir o arquivo %s",argv[2]);
                return 1;
            }else{

                saida = fopen (argv[3], "w"); //informa arquivo de saida

                start = clock();

                //---------------------------------------------

                pNodoA *Arvore_AVL;

                Arvore_AVL = cria_arvore();

                int *ok;
                int nivel = 0;
                float escore;

                while(!(feof(lexico)))
                {

                    if(fgets(linha,sizeof(linha),lexico) != NULL)
                    {
                        char lex[100];

                        // Usar sscanf para ler a palavra e o valor diretamente da linha
                        if (sscanf(linha, "%s %f", lex, &escore) == 2)
                        {
                            Arvore_AVL = InsereAVL(Arvore_AVL, lex, escore, &ok);
                            //Imprimir a palavra e o escore
                            //printf("\n palavra: %s\nescore: %.2f\n", lex, escore);
                        }
                    }

                }

                printf("\n\n");
                //imprimeIndentado(Arvore_AVL, nivel);
                printf("\n");

                char sentenca_completa[10000] = ""; // Inicialize com uma string vazia


                while(!(feof(sentencas)))
                {
                    while (fgets(linha,sizeof(linha),sentencas) != NULL)
                    {
                        //printf("LINHA: %s \n", linha);
                        char* sentenca = strtok (linha, separador);
                        float escore_sentenca = 0.0;
                        float score = 0.0;

                        // Inicialize a sentença completa como vazia para cada nova linha
                        strcpy(sentenca_completa, "");

                        while (sentenca != NULL)
                        {
                            score = consultaAVL(Arvore_AVL, sentenca);
                            escore_sentenca += score;
                            //printf("palavra: %s, score: %.2f \n", sentenca, score);

                            // Caso contrário, adicione um espaço à sentença completa
                            strcat(sentenca_completa, sentenca);
                            strcat(sentenca_completa, " ");

                            sentenca = strtok (NULL, separador);
                        }
                        // Imprima o escore da sentença e a sentença completa no arquivo de saída
                        if (strlen(sentenca_completa) > 0)
                        {
                            setlocale(LC_NUMERIC, "C");
                            fprintf(saida, "%.2f %s\n", escore_sentenca, sentenca_completa);
                        }

                    }
                }

                //printf("comparacoes: %d", comp);

                printf("\nArquivo %s gerado com sucesso.\n",argv[3]);

                end = clock();
                float miliseconds = (float)(end - start) / CLOCKS_PER_SEC * 10000;
                printf("Tempo: %.5f ms\n",miliseconds);
            }
        }
        fclose(lexico);
        fclose (sentencas);
        fclose (saida);
        return 0;
    }
}
