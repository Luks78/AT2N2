#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {
    OUROS, COPAS, ESPADAS, PAUS
} Naipe;

typedef enum {
    AS = 1, DOIS, TRES, QUATRO, CINCO, SEIS, SETE, OITO, NOVE, DEZ, VALETE, DAMA, REI
} Valor;

typedef struct {
    Naipe naipe;
    Valor valor;
} Carta;

typedef struct NoCarta {
    Carta carta;
    struct NoCarta *prox;
} NoCarta;

typedef struct {
    char nome[50];
    int pontos;
    NoCarta *mao; 
} Jogador;

Carta criar_carta(Naipe naipe, Valor valor) {
    Carta c;
    c.naipe = naipe;
    c.valor = valor;
    return c;
}

void adicionar_carta(NoCarta **lista, Carta carta) {
    NoCarta *novo = malloc(sizeof(NoCarta));
    novo->carta = carta;
    novo->prox = *lista;
    *lista = novo;
}

void liberar_lista(NoCarta *lista) {
    while (lista) {
        NoCarta *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

NoCarta* criar_baralho() {
    NoCarta *baralho = NULL;
    for (int n = OUROS; n <= PAUS; n++) {
        for (int v = AS; v <= REI; v++) {
            Carta c = criar_carta((Naipe)n, (Valor)v);
            adicionar_carta(&baralho, c);
        }
    }
    return baralho;
}

Carta sortear_carta(NoCarta **baralho) {
    int tamanho = 0;
    NoCarta *tmp = *baralho;
    while (tmp) {
        tamanho++;
        tmp = tmp->prox;
    }
    int idx = rand() % tamanho;
    NoCarta *anterior = NULL;
    tmp = *baralho;
    for (int i = 0; i < idx; i++) {
        anterior = tmp;
        tmp = tmp->prox;
    }
    Carta c = tmp->carta;
    if (anterior) {
        anterior->prox = tmp->prox;
    } else {
        *baralho = tmp->prox;
    }
    free(tmp);
    return c;
}

void registrar_pontuacao(const char *nome, int pontos) {
    FILE *f = fopen("placar.txt", "a");
    if (f) {
        fprintf(f, "%s: %d\n", nome, pontos);
        fclose(f);
    }
}

void exibir_placar() {
    FILE *f = fopen("placar.txt", "r");
    if (!f) {
        printf("Nenhum placar registrado ainda.\n");
        return;
    }
    char linha[100];
    printf("=== Placar ===\n");
    while (fgets(linha, sizeof(linha), f)) {
        printf("%s", linha);
    }
    fclose(f);
}

const char* nome_naipe(Naipe n) {
    switch (n) {
        case OUROS: return "Ouros";
        case COPAS: return "Copas";
        case ESPADAS: return "Espadas";
        case PAUS: return "Paus";
        default: return "Desconhecido";
    }
}

const char* nome_valor(Valor v) {
    switch (v) {
        case AS: return "As";
        case VALETE: return "Valete";
        case DAMA: return "Dama";
        case REI: return "Rei";
        default: {
            static char buf[3];
            snprintf(buf, sizeof(buf), "%d", v);
            return buf;
        }
    }
}

void jogar() {
    char nome[50];
    printf("\nDigite seu nome: ");
    scanf("%49s", nome);

    Jogador jogador;
    strcpy(jogador.nome, nome);
    jogador.pontos = 0;
    jogador.mao = NULL;

    NoCarta *baralho = criar_baralho();
    srand(time(NULL));

    printf("\nOla, %s! Vamos comecar!\n", jogador.nome);
    printf("Tente adivinhar o valor da carta sorteada.\n");
    printf("Lembrando que os valores sao de 1 a 13 sendo: 1=As, 11=Valete, 12=Dama, 13=Rei\n");

    for (int rodada = 1; rodada <= 5; rodada++) {
        Carta sorteada = sortear_carta(&baralho);
        int palpite;
        printf("\nRodada %d de 5\n", rodada);
        printf("Qual o seu palpite para o valor da carta? ");
        scanf("%d", &palpite);
        printf("A carta sorteada foi: %s de %s\n", nome_valor(sorteada.valor), nome_naipe(sorteada.naipe));
        if (palpite == sorteada.valor) {
            printf("Parabens! Voce acertou!\n");
            jogador.pontos++;
        } else {
            printf("Eita, voce errou. :(\n");
        }
    }
    printf("\nPontuacao final de %s: %d ponto(s)\n", jogador.nome, jogador.pontos);
    registrar_pontuacao(jogador.nome, jogador.pontos);
    liberar_lista(baralho);
}

int main() {
    int opcao;
    do {
        printf("\n=== Ola, seja bem-vindo ao Jogo de Adivinhacao de Cartas! ===\n");
        printf("escolha uma opcao\n");
        printf("1. Jogar\n2. Exibir placar\n3. Sair\n");
        printf("Digite o numero da opcao desejada: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: 
                printf("\nVamos comecar uma nova partida!\n");
                jogar(); 
                break;
            case 2: 
                printf("\nExibindo o placar dos jogadores:\n");
                exibir_placar(); 
                break;
            case 3: 
                printf("\nObrigado por jogar! Ate a proxima!\n"); 
                break;
            default: 
                printf("\nOpcao invalida! Por favor, escolha 1, 2 ou 3.\n");
        }
    } while (opcao != 3);
    return 0;
}