#include <stdio.h>
#include <stdlib.h>

int* cria_vetor(int n) {
    int* vetor = (int*) malloc(n * sizeof(int));
    if (vetor == NULL) {
        printf("Erro: Nao foi possivel alocar memoria!\n");
        exit(1);
    }
    printf("Vetor de %d posicoes criado!\n", n);
    return vetor;
}

void imprime_vetor(int* vetor, int n) {
    printf("\n--- Imprimindo Vetor ---\n");
    for (int i = 0; i < n; i++) {
        printf("Posicao %d: %d\n", i, vetor[i]);
    }
}

void libera_vetor(int* vetor) {
    free(vetor);
    printf("\nMemoria liberada!\n");
}

int main() {
    int n;
    int* meu_vetor;
    
    printf("Digite o tamanho do vetor (N): ");
    scanf("%d", &n);
    
    meu_vetor = cria_vetor(n);
    
    printf("\nDigite os %d elementos do vetor:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Elemento %d: ", i);
        scanf("%d", &meu_vetor[i]);
    }
    
    imprime_vetor(meu_vetor, n);
    libera_vetor(meu_vetor);
    
    return 0;
}

