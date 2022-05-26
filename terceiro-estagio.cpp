/*

Projeto desenvolvido pelos alunos:

Bruno Henrique Araújo da Costa - 20170017750
Gabriel Lucena Camboim - 20170128992

IMPORTANTE: Para mudar o arquivo, deve-se alterar o define ARQUIVO

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>
#include <iostream>

#define ARQUIVO "P-n55-k7.txt"

using namespace std;

typedef struct Rotas
{
    int *rota;
    int tamanhoRota;
    int custoTotal;
} Rotas;

void LeituraArquivo(void);
void VizinhoMaisProximo(void);
void Swap(void);
void TwoOpt(void);
void Reinsertion(void);
void VND(void);

int dimensao;
int capacidade;
int *demandas;
int **custo;
Rotas *rotas;
int numeroRotas = 0; // numero de rotas do arquivo
int entrouSwap = 0, entrouTwoOpt = 0, entrouReinsertion = 0;

int main(void)
{
    int i, j, custoTotal = 0; // serve apenas para realizar os prints

    LeituraArquivo(); // Realiza a leitura do arquivo

    VizinhoMaisProximo(); // Roda o vizinho mais próximo
    cout << "|--------------------|" << endl;
    cout << "|VIZINHO MAIS PRÓXIMO|" << endl;
    cout << "|--------------------|" << endl
         << endl;
    custoTotal = 0;

    for (j = 0; j < numeroRotas; j++) // For responsável por prints
    {
        cout << "Custo: " << rotas[j].custoTotal;
        if (rotas[j].custoTotal < 10)
            cout << "   -------   ";
        if (rotas[j].custoTotal < 100)
            cout << "  -------   ";
        else
            cout << " -------   ";

        for (i = 0; i < rotas[j].tamanhoRota; i++)
        {

            cout << rotas[j].rota[i];
            cout << "--";
        }
        cout << "0 " << endl;

        custoTotal += rotas[j].custoTotal;
    }

    cout << endl
         << "|------------------|" << endl;
    cout << "| Custo Total: " << custoTotal << " |" << endl;
    cout << "|------------------|" << endl
         << endl;

    VND();

    cout << "|----|" << endl;
    cout << "|VND |" << endl;
    cout << "|----|" << endl
         << endl;
    custoTotal = 0;

    for (j = 0; j < numeroRotas; j++) // For responsável por prints
    {
        cout << "Custo: " << rotas[j].custoTotal;
        if (rotas[j].custoTotal < 10)
            cout << "   -------   ";
        if (rotas[j].custoTotal < 100)
            cout << "  -------   ";
        else
            cout << " -------   ";

        for (i = 0; i < rotas[j].tamanhoRota; i++)
        {

            cout << rotas[j].rota[i];
            cout << "--";
        }
        cout << "0" << endl;
        custoTotal += rotas[j].custoTotal;
    }
    cout << endl
         << "|------------------|" << endl;
    cout << "| Custo Total: " << custoTotal << " |" << endl;
    cout << "|------------------|" << endl
         << endl;

    return 0;
}

void LeituraArquivo(void)
{
    int i, j;
    ifstream arq;
    arq.open(ARQUIVO);
    string buffer;

    for (i = 0; i < 3; i++)
        arq >> buffer; // Variavel apenas para controle de leitura

    arq >> dimensao; // Pega o tamanho de dimensão presente no arquivo

    demandas = (int *)malloc(dimensao * sizeof(int));

    custo = (int **)malloc(dimensao * sizeof(int));

    for (i = 0; i < dimensao; i++) //Cria o array bidimensional
        custo[i] = (int *)malloc(dimensao * sizeof(int));

    arq >> buffer;
    arq >> capacidade; // Pega a capacidade presente no arquivo

    for (i = 0; i < 2; i++)
        arq >> buffer;

    for (i = 0; i < dimensao; i++) // Realiza a leitura das demandas
    {
        arq >> demandas[i];
        arq >> buffer;
    }

    for (j = 0; j < dimensao; j++) // Realiza a leitura das dimensao
        for (i = 0; i < dimensao; i++)
            arq >> custo[i][j];

    arq.close();
}

void VizinhoMaisProximo(void)
{
    int capacidadeAtual = capacidade;
    int *flag = (int *)malloc(dimensao * sizeof(int));
    int i;
    int cidadeAtual = 0;
    int melhorCusto;
    int melhorCidade = 1;
    int cidadesVisitadas = 0;
    int cont = 0;
    int cont2 = 0;
    int cidadeAntiga;
    int tamanhoRota = 0;

    rotas = (Rotas *)malloc(dimensao * sizeof(Rotas));

    for (i = 0; i < dimensao; i++) // Aloca espaço p/ rota equivalente à dimensão
        rotas[i].rota = (int *)malloc(dimensao * sizeof(int));

    for (i = 0; i < dimensao; i++) // Inicializa o custo de todas as rotas com 0
        rotas[i].custoTotal = 0;

    while (1)
    {
        if ((capacidadeAtual - demandas[cidadeAtual]) < 0) // Se a capacidade for menor que a demanda
        {
            rotas[cont].custoTotal += custo[cidadeAtual][0];
            rotas[cont].tamanhoRota = tamanhoRota;

            cont++;
            cont2 = 0;
            tamanhoRota = 0;
            rotas[cont].custoTotal = 0;
            cidadeAtual = 0;
            capacidadeAtual = capacidade;
            numeroRotas++;
        }
        else // Se capacidade for maior que a demanda
        {
            capacidadeAtual -= demandas[cidadeAtual];
            melhorCusto = 9999;
            rotas[cont].rota[cont2] = cidadeAtual;

            tamanhoRota++;
            cont2++;

            if (flag[cidadeAtual] == 0) // Coloca a cidade como visitada
            {
                cidadesVisitadas++;
                flag[cidadeAtual] = 1;
            }

            if (cidadesVisitadas == dimensao) // Caso visitar todas as cidades
            {
                numeroRotas++;
                rotas[cont].tamanhoRota = tamanhoRota;
                rotas[cont].custoTotal += custo[cidadeAtual][0];

                break;
            }

            for (i = 0; i < dimensao; i++)
            {
                if (flag[i] == 0 && custo[cidadeAtual][i] < melhorCusto && custo[cidadeAtual][i] > 0 && (capacidadeAtual - demandas[i]) >= 0)
                {
                    melhorCusto = custo[cidadeAtual][i];
                    melhorCidade = i;
                }
            }
            cidadeAntiga = cidadeAtual;

            cidadeAtual = melhorCidade;
            rotas[cont].custoTotal += custo[cidadeAntiga][cidadeAtual];
        }
    }

    free(flag);
}

void Swap(void)
{
    int i, j, k;
    int melhori = -1, melhorj = -1, melhork = -1;
    int custoDaRota;
    int aux;
    int custoDETUDO = 0;
    int cidadeAtual = 0;

    // Guarda o valor da rota antiga
    for (i = 0; i < numeroRotas; i++)
        custoDETUDO += rotas[i].custoTotal;

    custoDaRota = custoDETUDO; // Guarda o valor da rota antiga em custoDaRota

    for (i = 0; i < numeroRotas; i++)
    {

        if (rotas[i].tamanhoRota >= 4) // Só tentará realizar alguma mudança a partir de 4
        {

            for (j = 1; j < rotas[i].tamanhoRota - 1; j++)
            {

                for (k = j + 1; k < rotas[i].tamanhoRota; k++) // Simula as mudanças de aresta
                {

                    if (k != j + 1)
                        aux = custoDETUDO - custo[rotas[i].rota[j - 1]][rotas[i].rota[j]] - custo[rotas[i].rota[j]][rotas[i].rota[j + 1]] - custo[rotas[i].rota[k - 1]][rotas[i].rota[k]] - custo[rotas[i].rota[k]][rotas[i].rota[k + 1]] + custo[rotas[i].rota[j - 1]][rotas[i].rota[k]] + custo[rotas[i].rota[k]][rotas[i].rota[j + 1]] + custo[rotas[i].rota[k - 1]][rotas[i].rota[j]] + custo[rotas[i].rota[j]][rotas[i].rota[k + 1]];
                    else
                    {
                        aux = custoDETUDO - custo[rotas[i].rota[j - 1]][rotas[i].rota[j]] - custo[rotas[i].rota[k]][rotas[i].rota[k + 1]] + custo[rotas[i].rota[j - 1]][rotas[i].rota[k]] + custo[rotas[i].rota[j]][rotas[i].rota[k + 1]];
                    }

                    if (aux < custoDaRota) // Guarda os valores das variáveis
                    {
                        custoDaRota = aux;
                        melhori = i;
                        melhorj = j;
                        melhork = k;
                    }
                }
            }
        }
    }

    if (melhori != -1 && melhorj != -1 && melhork && -1) // Realiza a troca de fato
    {

        aux = rotas[melhori].rota[melhorj];
        rotas[melhori].rota[melhorj] = rotas[melhori].rota[melhork];
        rotas[melhori].rota[melhork] = aux;

        rotas[melhori].custoTotal = 0;

        for (i = 0; i < rotas[melhori].tamanhoRota; i++)
        {
            rotas[melhori].custoTotal += custo[cidadeAtual][rotas[melhori].rota[i]];
            cidadeAtual = rotas[melhori].rota[i];
        }

        rotas[melhori].custoTotal += custo[cidadeAtual][0];
        entrouSwap = 1;
    }
}

void TwoOpt(void)
{
    int i, j, k, w;
    int melhori = -1, melhorj = -1, melhork = -1;
    int custoDaRota;
    int aux;
    int custoDETUDO = 0;
    int cidadeAtual = 0;
    int inversor;

    for (i = 0; i < numeroRotas; i++)
    {
        custoDETUDO += rotas[i].custoTotal;
    }

    custoDaRota = custoDETUDO;

    for (i = 0; i < numeroRotas; i++)
    {

        if (rotas[i].tamanhoRota >= 4)
        {

            for (j = 1; j < rotas[i].tamanhoRota - 1; j++)
            {

                for (k = j + 3; k < rotas[i].tamanhoRota; k++) // Simula as mudanças de aresta
                {

                    aux = custoDETUDO - (custo[rotas[i].rota[j - 1]][rotas[i].rota[j]]) - (custo[rotas[i].rota[k]][rotas[i].rota[k + 1]]) + custo[rotas[i].rota[j - 1]][rotas[i].rota[k]] + custo[rotas[i].rota[j]][rotas[i].rota[k + 1]];

                    if (aux < custoDaRota)
                    {
                        custoDaRota = aux;
                        melhori = i;
                        melhorj = j;
                        melhork = k;
                    }
                }
            }
        }
    }

    if (melhori != -1 && melhorj != -1 && melhork != -1) // Realiza a troca de fato
    {
        inversor = melhork;

        for (w = melhorj; w < melhork + 1; w++)
        {
            if (inversor <= w)
                break;

            aux = rotas[melhori].rota[w];
            rotas[melhori].rota[w] = rotas[melhori].rota[inversor];
            rotas[melhori].rota[inversor] = aux;
            inversor--;
        }

        rotas[melhori].custoTotal = 0;

        for (i = 0; i < rotas[melhori].tamanhoRota; i++)
        {
            rotas[melhori].custoTotal += custo[cidadeAtual][rotas[melhori].rota[i]];
            cidadeAtual = rotas[melhori].rota[i];
        }

        rotas[melhori].custoTotal += custo[cidadeAtual][0];
        entrouTwoOpt = 1;
    }
}

void Reinsertion(void)
{
    int i, j, k, w;
    int melhori = -1, melhorj = -1, melhork = -1;
    int custoDaRota;
    int aux;
    int *aux2;
    int custoDETUDO = 0;
    int cidadeAtual = 0;

    for (i = 0; i < numeroRotas; i++)
        custoDETUDO += rotas[i].custoTotal;

    custoDaRota = custoDETUDO;

    for (i = 0; i < numeroRotas; i++)
    {

        if (rotas[i].tamanhoRota >= 4)
        {

            for (j = 1; j < rotas[i].tamanhoRota - 1; j++)
            {

                for (k = 1; k < rotas[i].tamanhoRota; k++) // Simula as mudanças de aresta
                {

                    if (j == k || j == k - 1 || j == k + 1)
                        continue;

                    aux = custoDETUDO - custo[rotas[i].rota[j - 1]][rotas[i].rota[j]] - custo[rotas[i].rota[j]][rotas[i].rota[j + 1]] - custo[rotas[i].rota[k]][rotas[i].rota[k + 1]] + custo[rotas[i].rota[j - 1]][rotas[i].rota[j + 1]] + custo[rotas[i].rota[k]][rotas[i].rota[j]] + custo[rotas[i].rota[j]][rotas[i].rota[k + 1]];

                    if (aux < custoDaRota)
                    {
                        custoDaRota = aux;
                        melhori = i;
                        melhorj = j;
                        melhork = k;
                    }
                }
            }
        }
    }

    if (melhori != -1 && melhorj != -1 && melhork && -1) // Realiza a troca de fato
    {

        aux2 = (int *)malloc(rotas[melhori].tamanhoRota * sizeof(int));

        for (j = 0; j < rotas[melhori].tamanhoRota; j++) // Coloca em aux a rota atual
        {
            aux2[j] = rotas[melhori].rota[j];
        }

        aux2[melhork] = rotas[melhori].rota[melhorj];

        if (melhork > melhorj)
        {
            for (w = melhork; w > melhorj; w--)
            { // For que passa os números pra trás
                aux2[w - 1] = rotas[melhori].rota[w];
            }
        }

        else
        {
            for (w = melhork; w > melhorj; w++)
            { // For que passa os números pra frente
                aux2[w + 1] = rotas[melhori].rota[w];
            }
        }

        for (w = 0; w < rotas[melhori].tamanhoRota; w++)
        {
            rotas[melhori].rota[w] = aux2[w];
        }

        rotas[melhori].custoTotal = 0;

        for (i = 0; i < rotas[melhori].tamanhoRota; i++)
        {
            rotas[melhori].custoTotal += custo[cidadeAtual][rotas[melhori].rota[i]];
            cidadeAtual = rotas[melhori].rota[i];
        }

        rotas[melhori].custoTotal += custo[cidadeAtual][0];
        entrouReinsertion = 1;
        free(aux2);
    }
}

void VND(void)
{
    int k = 1;
    int r = 3;

    while (k <= r)
    {
        Swap();
        if (entrouSwap == 1)
        {
            entrouSwap = 0;
            k = 1;
            continue;
        }

        else k++;

        TwoOpt();

        if (entrouTwoOpt == 1)
        {
            entrouTwoOpt = 0;
            k = 1;
            continue;
        }

        else k++;

        Reinsertion();

        if (entrouReinsertion == 0) k++;
        else{
            entrouReinsertion = 0;
            k = 1;
            continue;
        }   
    }
}