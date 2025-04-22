#include <stdio.h>
#include <stdlib.h>
#include "cidades.h"

int main()
{

    Estrada *data = getEstrada("cidades.txt");

    if (data == NULL) {
        printf("Erro ao ler o arquivo. Os dados do arquivo devem seguir a regra a seguir:\n"
               "3 ≤ T ≤ 1.000.000 e 2 ≤ N ≤ 10.000\n"
               "0 < Xi < T, para 1 ≤ i ≤ N\n"
               "Xi ≠ Xj, para todo par 1 ≤ i, j ≤ N\n");
    }else{
        double menorVizinhanca = calcularMenorVizinhanca("cidades.txt");

        if(menorVizinhanca == -1)
        {
            printf("Não foi possível calcular a menor vizinhança");
        }else
        {
            printf("A menor vizinhanca e de %.2f\n", menorVizinhanca);
        }

        char *nome = cidadeMenorVizinhanca("cidades.txt");


        if(nome == NULL)
        {
            printf("Não foi possível calcular a menor vizinhança");
        }else
        {
            printf("A cidade com a menor vizinhanca e: %s", nome);
        }
        
        free(nome);
    }

    return 0;
}