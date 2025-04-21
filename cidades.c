#include "cidades.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nome[256];
    double vizinhanca;
    int posicao;
} Vizinhanca;

void OrdenedByPosition(Cidade *data, int tamanho)
{
    int i, j;

    for (i = 0; i < tamanho - 1; i++)
    {
        for (j = i + 1; j < tamanho; j++)
        {
            if (data[i].Posicao > data[j].Posicao)
            {
                Cidade aux = data[i];

                data[i] = data[j];

                data[j] = aux;
            }
        }
    }
}

Estrada *readFile(const char *nomeArquivo)
{
    FILE *arq = fopen(nomeArquivo, "r");

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo");
        return NULL;
    }

    Estrada *data = (Estrada *)malloc(sizeof(Estrada));

    if(fscanf(arq, "%d", &data->T) != 1)
    {
        free(data);
        fclose(arq);
        return NULL;
    }

    if (data->T <= 3 || data->T >= 1000000)
    {
        free(data);
        fclose(arq);
        return NULL;
    }

    if(fscanf(arq, "%d", &data->N) != 1)
    {
        free(data);
        fclose(arq);
        return NULL;
    }

    if (data->N <= 2 || data->N >= 10000)
    {
        free(data);
        fclose(arq);
        return NULL;
    }

    int i = 0;

    data->C = (Cidade *)malloc(sizeof(Cidade) * data->N);

    for (i = 0; i < data->N; i++)
    {
        if (fscanf(arq, "%d %[^\n]", &data->C[i].Posicao, data->C[i].Nome) != 2)
        {
            free(data->C);
            free(data);
            fclose(arq);
            return NULL;
        }

        if (data->C[i].Posicao <= 0 || data->C[i].Posicao >= data->T)
        {
            free(data->C);
            free(data);
            fclose(arq);
            return NULL;
        }

        int j;

        for (j = 0; j < i; j++)
        {
            if (data->C[i].Posicao == data->C[j].Posicao)
            {
                free(data->C);
                free(data);
                fclose(arq);
                return NULL;
            }

            if (strcmp(data->C[i].Nome, data->C[j].Nome) == 0)
            {
                free(data->C);
                free(data);
                fclose(arq);
                return NULL;
            }
        }
    }

    fclose(arq);

    OrdenedByPosition(data->C, data->N);

    return data;
}

Estrada *getEstrada(const char *nomeArquivo)
{
    Estrada *data = readFile(nomeArquivo);
    
    return data;
}

Vizinhanca *menorVizinhanca(Estrada *data)
{
    Vizinhanca *vizinhancas = (Vizinhanca *)malloc(sizeof(Vizinhanca) * data->N);

    int i;

    double soma = 0;

    for (i = 0; i < data->N; i++)
    {
        double vizinhanca = 0;

        if (i == data->N - 1)
        {
            vizinhanca = (float)(data->T - soma);

            vizinhancas[i].vizinhanca = vizinhanca;

            strcpy(vizinhancas[i].nome, data->C[i].Nome);

            vizinhancas[i].posicao = data->C[i].Posicao;

            break;
        }

        vizinhanca = ((data->C[i].Posicao + data->C[i + 1].Posicao) / 2.0) - soma;

        vizinhancas[i].vizinhanca = vizinhanca;

        strcpy(vizinhancas[i].nome, data->C[i].Nome);

        vizinhancas[i].posicao = data->C[i].Posicao;

        soma += vizinhanca;
    }

    double menorVizinhanca = vizinhancas[0].vizinhanca;

    int indice = 0;

    for (i = 0; i < data->N; i++)
    {
        if (vizinhancas[i].vizinhanca < menorVizinhanca)
        {
            menorVizinhanca = vizinhancas[i].vizinhanca;

            indice = i;
        }
    }

    Vizinhanca *resultado = (Vizinhanca*) malloc(sizeof(Vizinhanca));
    
    *resultado = vizinhancas[indice];

    free(vizinhancas);

    return resultado;
}

double calcularMenorVizinhanca(const char *nomeArquivo)
{
    Estrada *data = readFile(nomeArquivo);

    Vizinhanca *cidadeMenor = menorVizinhanca(data);

    double menorVizinhanca = cidadeMenor->vizinhanca;

    free(cidadeMenor);

    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo)
{
    Estrada *data = readFile(nomeArquivo);

    Vizinhanca *cidadeMenor = menorVizinhanca(data);

    char *nome = strdup(cidadeMenor->nome);

    free(cidadeMenor);

    return nome;
}