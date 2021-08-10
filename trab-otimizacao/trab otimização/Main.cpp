#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;

//----------Definição de estruturas-----------
typedef struct
{
    int cordX;
    int cordY;
    int peso;
    int numCliente;
} Cliente;

Cliente vet_cliente[120];
Cliente vet_solucao[120];
const int max_veiculos = 14;
int qtd_clientes;
int qtd_veiculos;
int capacidade;

typedef struct
{
    int matriz_solucao[max_veiculos][110];
    int vet_carroCliente[max_veiculos];
    int vet_carroPeso[max_veiculos];
    int resultado;
} Solucao;

int matriz_custo[110][110];
//--------------------------------------------

//--------Função para calcular o custo--------
void calc_custo()
{
    memset(matriz_custo, 0, sizeof(matriz_custo));
    for (int i = 0; i < qtd_clientes; i++)
    {
        for (int j = 0; j < qtd_clientes; j++)
        {
<<<<<<< HEAD
            
                matriz_custo[i][j] = sqrt((pow(vet_cliente[i].cordX - vet_cliente[j].cordX, 2) + pow(vet_cliente[i].cordY - vet_cliente[j].cordY, 2)));
            
=======
            matriz_custo[i][j] = sqrt((pow(vet_cliente[i].cordX - vet_cliente[j].cordX, 2) + pow(vet_cliente[i].cordY - vet_cliente[j].cordY, 2)));
>>>>>>> alef
        }
    }
}
//--------------------------------------------

//---Função para criar uma solução inicial----
//----Foi utilizada a Heurística Aleatória----
void calc_heuristica(Solucao &Solucao)
{
    memset(Solucao.vet_carroCliente, 0, sizeof(Solucao.vet_carroCliente));
    memset(Solucao.vet_carroPeso, 0, sizeof(Solucao.vet_carroPeso));
    memset(Solucao.matriz_solucao, 0, sizeof(Solucao.matriz_solucao));
    int carro;
    for (int i = 1; i <= qtd_clientes; i++)
    {
        carro = rand() % qtd_veiculos;
        if (Solucao.vet_carroPeso[carro] + vet_cliente[i].peso <= capacidade)
        {
            Solucao.matriz_solucao[carro][Solucao.vet_carroCliente[carro]] = vet_cliente[i].numCliente;
            Solucao.vet_carroPeso[carro] = vet_cliente[i].peso;
            Solucao.vet_carroCliente[carro]++;
        }
    }
}
//--------------------------------------------

//----Função para calcular o valor da F0------
void calc_fo(Solucao &Solucao)
{
    Solucao.resultado = 0;
    for (int i = 0; i < qtd_veiculos; i++)
    {
        Solucao.resultado += matriz_custo[0][Solucao.matriz_solucao[i][0] - 1];
        for (int j = 0; j < Solucao.vet_carroCliente[i] - 2; j++)
        {
            Solucao.resultado += matriz_custo[Solucao.matriz_solucao[i][j] - 1][Solucao.matriz_solucao[i][j + 1] - 1];
        }
        Solucao.resultado += matriz_custo[Solucao.matriz_solucao[i][Solucao.vet_carroCliente[i] - 1] - 1][0];
    }
}
//--------------------------------------------

//--Função para buscar quantidade de carros---
int num_carros(const string &fileName)
{
    size_t pos = fileName.rfind("-k");
    if (pos != string::npos)
    {
        string numeroCarros = fileName.substr(pos + 2);
        pos = numeroCarros.find(".");
        if (pos != string::npos)
        {
            return atoi(numeroCarros.substr(0, pos).c_str());
        }
    }
    throw std::runtime_error("Erro na entrada do numero de carros");
    return -1;
}
//--------------------------------------------

//------Função para leitura da instância------
void ler_arquivo()
{
    ifstream arquivoE;
    arquivoE.open("Instancias\\E-n101-k14.vrp");
    const char *file = "Instancias\\E-n101-k14.vrp";
    string str;
    char *comparador;
    char *palavra_lida;
    int numero_nos;
    int numero_clientes;
    int capacidade_maxima;
    qtd_veiculos = num_carros(file);
    if (!arquivoE.is_open())
    {
        throw std::runtime_error("Arquivo nao pode ser aberto");
    }
    while (true)
    {
        getline(arquivoE, str);
        palavra_lida = strdup(str.c_str());
        comparador = strtok(palavra_lida, " : ");
        if (strcmp(comparador, "DIMENSION") == 0)
        {
            comparador = strtok(NULL, " :");
            numero_nos = atoi(comparador);
            numero_clientes = numero_nos - 1;
        }
        else if (strcmp(comparador, "CAPACITY") == 0)
        {
            comparador = strtok(NULL, " :");
            capacidade_maxima = atoi(comparador);
        }
        else if (strcmp(comparador, "EDGE_WEIGHT_TYPE") == 0)
        {
            comparador = strtok(NULL, " :");
            if (strcmp(comparador, "EUC_2D") != 0)
            {
                throw std::runtime_error("Apenas o Tipo EUC_2D e suportado");
            }
        }

        else if (strcmp(comparador, "NODE_COORD_SECTION") == 0)
        {
            break;
        }
    }
    for (int n = 1; n <= numero_nos; n++)
    {
        int id;
        arquivoE >> id;
        if (id != n)
        {
            throw std::runtime_error("Erro");
        }
        if (n == 1)
        {
<<<<<<< HEAD
            arquivoE >> depositoX;
            vet_cliente[n - 1].cordX = depositoX;
            arquivoE >> depositoY;
            vet_cliente[n - 1].numCliente = n;
            vet_cliente[n - 1].cordY = depositoY;
=======
            arquivoE >> vet_cliente[n - 1].cordX;
            arquivoE >> vet_cliente[n - 1].cordY;
            vet_cliente[n - 1].numCliente = n;
>>>>>>> alef
        }
        else
        {
            arquivoE >> vet_cliente[n - 1].cordX;
            vet_cliente[n - 1].numCliente = n;
            arquivoE >> vet_cliente[n - 1].cordY;
        }
    }

    getline(arquivoE, str); // Fim da última linha
    getline(arquivoE, str);
    palavra_lida = strdup(str.c_str());
    comparador = strtok(palavra_lida, " :");

    if (strcmp(comparador, "DEMAND_SECTION") != 0)
    {
        throw std::runtime_error("DEMAND_SECTION não encontrado");
    }
    for (int n = 1; n <= numero_nos; n++)
    {
        int id;
        arquivoE >> id;
        if (id != n)
        {
            throw std::runtime_error("Unexpected index");
        }
        int demand;
        arquivoE >> demand;
        if (n == 1)
        {
            if (demand != 0)
            {
                throw std::runtime_error("Valor deveria ser O");
            }
        }
        else
        {
            vet_cliente[n - 1].peso = demand;
        }
    }
    capacidade = capacidade_maxima;

    //print para confirmar que os dados foram armazenados

    cout << "Coordenadas X STRUCT" << endl;
    for (int i = 0; i <= numero_clientes; i++)
    {
        printf("%d ", vet_cliente[i].cordX);
    }
    cout << endl;
    cout << "Coordenadas Y STRUCT" << endl;
    for (int i = 0; i <= numero_clientes; i++)
    {
        printf("%d ", vet_cliente[i].cordY);
    }
    cout << endl;
    cout << "PESO STRUCT" << endl;
    for (int i = 0; i <= numero_clientes; i++)
    {
        printf("%d ", vet_cliente[i].peso);
    }
    cout << endl;
<<<<<<< HEAD
    cout << "Coordenadas X" << endl;
    for (int i = 0; i <= numero_clientes; i++)
    {
        printf("%d ", coordenadasX[i]);
    }
    cout << endl;
    cout << "Coordenadas Y" << endl;
    for (int o = 0; o <= numero_clientes; o++)
    {
        printf("%d ", coordenadasY[o]);
    }
    cout << endl;
    cout << "Peso veiculos" << endl;
    for (int u = 0; u <= numero_clientes; u++)
    {
        printf("%d ", peso_veiculos[u]);
    }
=======
>>>>>>> alef
    cout << endl;
    cout << "NUMERO DO CLIENTE" << endl;
    for (int i = 0; i <= numero_clientes; i++)
    {
        printf("%d ", vet_cliente[i].numCliente);
    }
    cout << endl;
    cout << numero_nos << endl;
    cout << capacidade_maxima << endl;
    qtd_clientes = numero_clientes;
    cout << qtd_clientes << endl;
    arquivoE.close();
}
//--------------------------------------------
int main(int argc, char *argv[])
{
    Solucao Solucao;
    ler_arquivo();
    calc_custo();
<<<<<<< HEAD
    char str[80] = "This is - www.tutorialspoint.com - website";
    const char s[2] = "-";
    char *token;

    token = strtok(str, s);

    while (token != NULL)
    {
        printf(" %s\n", token);

        token = strtok(NULL, s);
    }

    return (0);
}
void busca_gulosa(int capacidade_maxima, int numero_nos)
{
    int peso_atual = 0;
    int custo_total;
    for (int i = 0; i < numero_nos; i++)
=======
    calc_heuristica(Solucao);
    calc_fo(Solucao);
    cout << endl;
    cout << "numero de carros: ";
    cout << qtd_veiculos << endl;
    for (int i = 0; i < qtd_veiculos; i++)
>>>>>>> alef
    {
        cout << "1; ";
        for (int j = 0; j < Solucao.vet_carroCliente[i]; j++)
        {
            cout << Solucao.matriz_solucao[i][j] << "; ";
        }
        cout << endl;
    }
    cout << "valor da solucao: ";
    cout << Solucao.resultado;
    return (0);
}