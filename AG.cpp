#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "Util.h"
#include "AG.h"
#include "Construcao.h"
//#include "GRASP.h"
#include "Descida.h"

using namespace std;

float AG(int n,
         std::vector<int> *s,
         float **d,
         int nind,
         float max_desvio,
         double prob_crossover,
         double prob_mutacao,
         int tipo_operador)
{
    vector< vector<int> > pop; // populacao
    vector<float> fo_pop; // funcao objetivo corrente de um dado individuo da populacao
    vector< vector<int> > pop_sobrev; // populacao sobrevivente
    vector<float> fo_pop_sobrev; // funcao objetivo corrente de um dado individuo da populacao sobrevivente
    vector<int> s_star;   // vetor que contem a melhor solucao gerada
    float fo, fo_star;   // valor da melhor solucao gerada

    fo_star = INT_MAX;
    if (nind % 2 != 0){
        printf("Numero de individuos deve ser par!\n");
        printf("Vou aumentar o numero de individuos ...\n");
        getchar();
        nind++;
    }
    nind = nind * 2;

    //cria a matriz pop[nind,n]
    pop.resize(nind, vector<int>(n));


    //cria a matriz pop_sobrev[nind/2, n]
    pop_sobrev.resize(nind/2, vector<int>(n));

    fo_pop.resize(nind);
    fo_pop_sobrev.resize(nind/2);

    /*
     *
     *
     * Implementar
     *
     *
     *
     */

    return fo;
}

/* Esta rotina devolve o individuo escolhido pelo mecanismo da roleta */
int roleta(int nind, std::vector<float> *fo_pop)
{
    int j;
    float aux;
    vector<float> escala;
    vector<float> fracao;
    vector<float> faptidao;
    float tg_alfa, soma, fo_max, fo_min;
    int escolhido;

    soma = 0;
    fo_min = INT_MAX;
    fo_max = INT_MIN;

    for (int j = 0; j < nind; j++){
        if (fo_pop->at(j) < fo_min) fo_min = fo_pop->at(j);
        if (fo_pop->at(j) > fo_max) fo_max = fo_pop->at(j);
    }

    tg_alfa = 100 / (fo_max - fo_min);

    for (int j = 0; j < nind; j++){
        faptidao.push_back( tg_alfa * (fo_max - fo_pop->at(j)) );
        soma += faptidao[j];
    }

    for (int j = 0; j < nind; j++)
        fracao.push_back( faptidao[j] / soma );

    escala.push_back(fracao[0]);

    for (int j = 1; j < nind; j++)
        escala.push_back( escala[j-1] + fracao[j] );

    aux = randomico(0,1);
    j = 0;
    while (escala[j] < aux) j++;
    escolhido = j;

    return escolhido;
}


void mutacao(vector<int> *s, int n)
{
    int i, j;

    i = rand()%n;
    do {
        j = rand()%n;
    } while (i == j);

    swap(s->at(i),s->at(j));
}

/* Operador Crossover OX */
void crossover_OX(vector<int> *pai1,
                  vector<int> *pai2,
                  vector<int> *filho1,
                  vector<int> *filho2,
                  int n)
{

    int ponto_de_corte_1, ponto_de_corte_2, i, j;
    bool existe;
    vector<int> lista_pai1, lista_pai2;

    ponto_de_corte_1 = randomico(2,(n-1)/2);
    ponto_de_corte_2 = randomico((n+1)/2,n-3);

    /* Copia os genes entre os 2 pontos de corte em cada filho */
    for (int i = ponto_de_corte_1; i <= ponto_de_corte_2; i++) {
        filho1->at(i) = pai1->at(i);
        filho2->at(i) = pai2->at(i);
    }

    int tam_lista = n - (ponto_de_corte_2 - ponto_de_corte_1 + 1);

    i = ponto_de_corte_2 + 1;
    j = 0;
    do {
        /* procura a cidade pai1[i] no filho2*/
        existe = false;
        for(int k = ponto_de_corte_1; k <= ponto_de_corte_2; k++) {
            if (filho2->at(k) == pai1->at(i)) existe = true;
        }
        if (! existe) {
            lista_pai1.push_back(pai1->at(i));
            j++;
        }
        if (i == (n-1)) i = 0;
        else i++;

    } while(j < tam_lista);

    i = ponto_de_corte_2 + 1;
    j = 0;
    do {
        /* procura a cidade pai2[i] no filho1*/
        existe = false;
        for(int k = ponto_de_corte_1; k <= ponto_de_corte_2; k++) {
            if (filho1->at(k) == pai2->at(i)) existe = true;
        }
        if (! existe) {
            lista_pai2.push_back(pai2->at(i));
            j++;
        }

        if (i == (n-1)) i = 0;
        else i++;

    } while(j < tam_lista);

    /* Completa os genes que faltam */
    i = 0;
    j = ponto_de_corte_2 + 1;
    do {
        filho1->at(j) = lista_pai2[i];
        filho2->at(j) = lista_pai1[i];
        i++;
        if (j == (n-1)) j = 0;
        else j++;
    } while (i < tam_lista);

}

///* Operador Crossover ERX */
//void crossover_ERX(int *pai1,
//                   int *pai2,
//                   int *filho1,
//                   int *filho2,
//                   int n)
//{
//}
