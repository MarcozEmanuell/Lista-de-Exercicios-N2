#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia;
    int mes;
} Data;

typedef struct {
    char nome[40];
    char telefone[15];
    char celular[15];
    char email[40];
    Data dataAniversario;
} Contato;

typedef struct elemento {
    Contato info;
    struct elemento* prox;
} Elemento;


Elemento* cria_agenda() {
    return NULL;
}

void limparBufferTeclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Elemento* insere_contato(Elemento* lista) {
    Elemento* novo_elemento = (Elemento*) malloc(sizeof(Elemento));
    
    printf("\n--- Novo Contato ---\n");
    printf("Nome: ");
    scanf(" %39[^\n]", novo_elemento->info.nome); 
    
    printf("Telefone: ");
    scanf(" %14[^\n]", novo_elemento->info.telefone);
    
    printf("Celular: ");
    scanf(" %14[^\n]", novo_elemento->info.celular);
    
    printf("Email: ");
    scanf(" %39[^\n]", novo_elemento->info.email);
    
    printf("Aniversario (DD MM): ");
    scanf("%d %d", &novo_elemento->info.dataAniversario.dia, &novo_elemento->info.dataAniversario.mes);
    
    novo_elemento->prox = NULL;
    
    if (lista == NULL) {
        printf("Contato salvo!\n");
        return novo_elemento; 
    }
    
    Elemento* atual = lista;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    
    atual->prox = novo_elemento;
    
    printf("Contato salvo!\n");
    return lista;
}

void lista_contatos(Elemento* lista) {
    if (lista == NULL) {
        printf("\nAgenda vazia.\n");
        return;
    }
    
    Elemento* atual = lista;
    
    printf("\n--- Lista de Contatos ---\n");
    while (atual != NULL) {
        printf("Nome: %s\n", atual->info.nome);
        printf("Telefone: %s\n", atual->info.telefone);
        printf("Celular: %s\n", atual->info.celular);
        printf("Email: %s\n", atual->info.email);
        printf("Aniversario: %d/%d\n", atual->info.dataAniversario.dia, atual->info.dataAniversario.mes);
        printf("---------------------------\n");
        
        atual = atual->prox; 
    }
}

Elemento* busca_contato(Elemento* lista, char* nome_busca) {
    Elemento* atual = lista;
    
    while (atual != NULL) {
        if (strcmp(atual->info.nome, nome_busca) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    
    return NULL; 
}

Elemento* remove_contato(Elemento* lista) {
    char nome_busca[40];
    printf("\nQual nome deseja remover? ");
    scanf(" %39[^\n]", nome_busca);
    
    Elemento* anterior = NULL;
    Elemento* atual = lista;
    
    while (atual != NULL && strcmp(atual->info.nome, nome_busca) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    
    if (atual == NULL) {
        printf("Erro: Contato '%s' nao encontrado.\n", nome_busca);
        return lista;
    }
    
    if (anterior == NULL) {
        lista = atual->prox;
    } 
    else {
        anterior->prox = atual->prox;
    }
    
    free(atual);
    printf("Contato '%s' removido com sucesso!\n", nome_busca);
    
    return lista;
}

void atualiza_contato(Elemento* lista) {
    char nome_busca[40];
    printf("\nQual nome deseja editar? ");
    scanf(" %39[^\n]", nome_busca);
    
    Elemento* contato_encontrado = busca_contato(lista, nome_busca);
    
    if (contato_encontrado == NULL) {
        printf("Erro: Contato '%s' nao encontrado.\n", nome_busca);
        return;
    }
    
    printf("Editando contato: %s\n", contato_encontrado->info.nome);
    printf("Novo Nome: ");
    scanf(" %39[^\n]", contato_encontrado->info.nome);
    
    printf("Novo Telefone: ");
    scanf(" %14[^\n]", contato_encontrado->info.telefone);
    
    printf("Novo Celular: ");
    scanf(" %14[^\n]", contato_encontrado->info.celular);
    
    printf("Novo Email: ");
    scanf(" %39[^\n]", contato_encontrado->info.email);
    
    printf("Novo Aniversario (DD MM): ");
    scanf("%d %d", &contato_encontrado->info.dataAniversario.dia, &contato_encontrado->info.dataAniversario.mes);
    
    printf("Contato atualizado com sucesso!\n");
}


int main() {
    Elemento* minha_agenda = cria_agenda();
    int opcao = 0;
    
    do {
        printf("\n--- AGENDA TELEFONICA ---\n");
        printf("1. Inserir Contato\n");
        printf("2. Listar Contatos\n");
        printf("3. Buscar Contato\n");
        printf("4. Editar Contato\n");
        printf("5. Remover Contato\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        limparBufferTeclado();

        switch(opcao) {
            case 1:
                minha_agenda = insere_contato(minha_agenda);
                break;
            
            case 2:
                lista_contatos(minha_agenda);
                break;
                
            case 3: {
                char nome_busca[40];
                printf("Qual nome deseja buscar? ");
                scanf(" %39[^\n]", nome_busca);
                
                Elemento* contato_encontrado = busca_contato(minha_agenda, nome_busca);
                
                if (contato_encontrado != NULL) {
                    printf("\n--- Contato Encontrado ---\n");
                    printf("Nome: %s\n", contato_encontrado->info.nome);
                    printf("Telefone: %s\n", contato_encontrado->info.telefone);
                    printf("Celular: %s\n", contato_encontrado->info.celular);
                } else {
                    printf("Contato '%s' nao encontrado.\n", nome_busca);
                }
                break;
            }
                
            case 4:
                atualiza_contato(minha_agenda);
                break;
                
            case 5:
                minha_agenda = remove_contato(minha_agenda);
                break;
                
            case 6:
                printf("Saindo... Tchau!\n");
                break;
                
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        
        if (opcao != 6) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
        
    } while (opcao != 6);
    
    return 0;
}
