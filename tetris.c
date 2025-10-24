#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

typedef struct {
    char tipo;
    int id;
} Peca;

typedef struct {
    Peca elementos[MAX];
    int frente;
    int tras;
    int tamanho;
    int proximoId;
} Fila;

void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
    f->proximoId = 0;
}

int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

int filaCheia(Fila *f) {
    return f->tamanho == MAX;
}

void enqueue(Fila *f, Peca peca) {
    if (filaCheia(f)) {
        printf("Erro: Fila cheia!\n");
        return;
    }
    
    f->tras = (f->tras + 1) % MAX;
    f->elementos[f->tras] = peca;
    f->tamanho++;
}

Peca dequeue(Fila *f) {
    Peca pecaVazia = {'?', -1};
    
    if (filaVazia(f)) {
        printf("Erro: Fila vazia!\n");
        return pecaVazia;
    }
    
    Peca pecaRemovida = f->elementos[f->frente];
    f->frente = (f->frente + 1) % MAX;
    f->tamanho--;
    
    return pecaRemovida;
}

char gerarTipoAleatorio() {
    char tipos[] = {'T', 'O', 'L', 'I', 'S', 'Z', 'J'};
    int indice = rand() % 7;
    return tipos[indice];
}

Peca criarPeca(int id) {
    Peca novaPeca;
    novaPeca.tipo = gerarTipoAleatorio();
    novaPeca.id = id;
    return novaPeca;
}

void mostrarFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }
    
    printf("Fila de Pecas: ");
    
    int i = f->frente;
    int count = 0;
    
    while (count < f->tamanho) {
        printf("[%c %d]", f->elementos[i].tipo, f->elementos[i].id);
        i = (i + 1) % MAX;
        count++;
        
        if (count < f->tamanho) {
            printf(" ");
        }
    }
    printf("\n");
}

void preencherFilaInicial(Fila *f) {
    while (!filaCheia(f)) {
        Peca novaPeca = criarPeca(f->proximoId++);
        enqueue(f, novaPeca);
    }
}

void jogarPecas(Fila *f) {
    if (!filaVazia(f)) {
        Peca pecaRemovida = dequeue(f);
        printf("Peca jogada: [%c %d]\n", pecaRemovida.tipo, pecaRemovida.id);
        
        // Adiciona nova peça automaticamente
        Peca novaPeca = criarPeca(f->proximoId++);
        enqueue(f, novaPeca);
        printf("Nova peca adicionada: [%c %d]\n", novaPeca.tipo, novaPeca.id);
    } else {
        printf("Nao ha pecas para jogar!\n");
    }
}

void inserirNovaPeca(Fila *f) {
    if (!filaCheia(f)) {
        Peca novaPeca = criarPeca(f->proximoId++);
        enqueue(f, novaPeca);
        printf("Nova peca inserida: [%c %d]\n", novaPeca.tipo, novaPeca.id);
    } else {
        printf("Fila cheia! Nao e possivel inserir nova peca.\n");
    }
}

int main() {
    srand(time(NULL));
    
    Fila fila;
    inicializarFila(&fila);
    preencherFilaInicial(&fila);
    
    int opcao;

    do {
        printf("\n---------------\n");
        printf("--- TETRIS ---\n");
        printf("---------------\n");
        mostrarFila(&fila);
        printf("\n1. Jogar Peca\n");
        printf("2. Inserir nova peca\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao); // Corrigido: faltava o &

        switch (opcao) {
            case 1:
                jogarPecas(&fila);
                break;
                
            case 2:
                inserirNovaPeca(&fila);
                break;
                
            case 0:
                printf("Saindo...\n");
                break;
                
            default:
                printf("Opcao invalida!\n");
                break;
        }
        
    } while (opcao != 0);

    return 0;
}
