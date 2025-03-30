#include <stdio.h>
#include <stdlib.h>

// Definicoes dos macros no escopo global
#define CARTA1 1
#define CARTA2 2

// Função para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para ler um número inteiro com validação e retorno unsigned long int
unsigned long int lerInteiro(char* mensagem) {
    int numero;
    char entrada[100];
    while (1) {
        printf("%s", mensagem);
        if (fgets(entrada, sizeof(entrada), stdin)) {
            if (sscanf(entrada, "%d", &numero) == 1) {
                limparBuffer();
                if (numero >= 0) {
                    return (unsigned long int)numero; // Conversão explícita
                } else {
                    printf("Entrada invalida. Insira um valor positivo.\n");
                }
            } else {
                printf("Entrada invalida. Tente novamente.\n");
            }
        } else {
            exit(1); // Erro de leitura
        }
    }
}

// Função para ler um número de ponto flutuante com validação
float lerFloat(char* mensagem) {
    float numero;
    char entrada[100];
    while (1) {
        printf("%s", mensagem);
        if (fgets(entrada, sizeof(entrada), stdin)) {
            if (sscanf(entrada, "%f", &numero) == 1) {
                limparBuffer();
                return numero;
            } else {
                printf("Entrada invalida. Tente novamente.\n");
            }
        } else {
            exit(1); // Erro de leitura
        }
    }
}

// Função para ler uma string
void lerString(char* mensagem, char* string, int tamanho) {
    printf("%s", mensagem);
    fgets(string, tamanho, stdin);
    // Remover o caractere de nova linha, se presente
    for (int i = 0; i < tamanho; i++) {
        if (string[i] == '\n') {
            string[i] = '\0';
            break;
        }
    }
}

// Função para ler os dados de uma carta
void lerCarta(int numeroCarta, char* estado, char* codigoCarta, char* nomeCidade, unsigned long int* populacao, int* numeroPontosTuristicos, float* areaEmKm, float* pib) {
    printf("\nDigite os dados da Carta %d:\n", numeroCarta);
    printf("Estado: ");
    scanf(" %c", estado);
    limparBuffer();
    lerString("Codigo da carta: ", codigoCarta, 4);
    lerString("Nome da Cidade: ", nomeCidade, 50);
    *populacao = lerInteiro("Populacao: ");
    *areaEmKm = lerFloat("Area em km²: ");
    *pib = lerFloat("PIB: ");
    *numeroPontosTuristicos = lerInteiro("Numero de pontos turisticos: ");
}

// Função para calcular os atributos de uma carta
void calcularAtributos(unsigned long int populacao, float areaEmKm, float pib, int numeroPontosTuristicos, float* densidadePopulacional, float* pibPerCapita, float* superPoder) {
    *densidadePopulacional = areaEmKm != 0 ? (float)populacao / areaEmKm : 0;
    *pibPerCapita = populacao != 0 ? pib / (float)populacao : 0;
    *superPoder = (float)populacao + areaEmKm + pib + (float)numeroPontosTuristicos + *pibPerCapita + (*densidadePopulacional != 0 ? 1 / *densidadePopulacional : 0);
}

// Função para exibir o resultado da comparação
void exibirResultado(char* atributo, int vencedor, int resultado) {
    printf("%s: Carta %d venceu (%s)\n", atributo, vencedor, resultado ? "Sim" : "Nao");
}

int main() {
    // Dados para cadastro carta 01
    char estado1;
    char codigocarta1[4], nomedacidade1[50];
    unsigned long int populacao1;
    int numeropontosturistico1;
    float areaemkm1, pib1;
    float densidadePopulacional1, pibPerCapita1, superPoder1;

    // Dados para cadastro carta 02
    char estado2;
    char codigocarta2[4], nomedacidade2[50];
    unsigned long int populacao2;
    int numeropontosturistico2;
    float areaemkm2, pib2;
    float densidadePopulacional2, pibPerCapita2, superPoder2;

    // Ler dados das cartas
    lerCarta(CARTA1, &estado1, codigocarta1, nomedacidade1, &populacao1, &numeropontosturistico1, &areaemkm1, &pib1);
    lerCarta(CARTA2, &estado2, codigocarta2, nomedacidade2, &populacao2, &numeropontosturistico2, &areaemkm2, &pib2);

    // Calcular atributos das cartas
    calcularAtributos(populacao1, areaemkm1, pib1, numeropontosturistico1, &densidadePopulacional1, &pibPerCapita1, &superPoder1);
    calcularAtributos(populacao2, areaemkm2, pib2, numeropontosturistico2, &densidadePopulacional2, &pibPerCapita2, &superPoder2);

    // Comparar as Cartas e Exibir Resultados
    printf("\nComparacao de Cartas:\n");

    exibirResultado("Populacao", populacao1 > populacao2 ? CARTA1 : CARTA2, populacao1 > populacao2);
    exibirResultado("Area", areaemkm1 > areaemkm2 ? CARTA1 : CARTA2, areaemkm1 > areaemkm2);
    exibirResultado("PIB", pib1 > pib2 ? CARTA1 : CARTA2, pib1 > pib2);
    exibirResultado("Pontos Turisticos", numeropontosturistico1 > numeropontosturistico2 ? CARTA1 : CARTA2, numeropontosturistico1 > numeropontosturistico2);
    exibirResultado("Densidade Populacional", densidadePopulacional1 < densidadePopulacional2 ? CARTA1 : CARTA2, densidadePopulacional1 < densidadePopulacional2);
    exibirResultado("PIB per Capita", pibPerCapita1 > pibPerCapita2 ? CARTA1 : CARTA2, pibPerCapita1 > pibPerCapita2);
    exibirResultado("Super Poder", superPoder1 > superPoder2 ? CARTA1 : CARTA2, superPoder1 > superPoder2);

    return 0;
}