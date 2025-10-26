#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node {
    double value;
    struct node* prox;
} Node;

typedef struct {
    Node* topo;
} Stack;

Stack* createStack() {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->topo = NULL;
    return stack;
}

int isEmpty(Stack* stack) {
    return (stack->topo == NULL);
}

void push(Stack* stack, double value) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->value = value;
    new_node->prox = stack->topo;
    stack->topo = new_node;
}

double pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Erro: Tentativa de pop em pilha vazia (expressao malformada).\n");
        exit(1);
    }
    Node* temp = stack->topo;
    double valor_retorno = temp->value;
    stack->topo = temp->prox;
    free(temp);
    return valor_retorno;
}

void freeStack(Stack* stack) {
    while (!isEmpty(stack)) {
        pop(stack);
    }
    free(stack);
}

int isNumber(const char *str) {
    int i = 0;
    if (str[0] == '-' && str[1] != '\0') i = 1;
    for (; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '.') return 0;
    }
    return 1;
}

double evaluateRPN(char* expression) {
    Stack* pilha = createStack();
    char* token = strtok(expression, " ");

    while (token != NULL) {

        if (strcmp(token, "+") == 0 ||
            strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 ||
            strcmp(token, "/") == 0) {

            double val2 = pop(pilha);
            double val1 = pop(pilha);

            if (strcmp(token, "+") == 0) push(pilha, val1 + val2);
            else if (strcmp(token, "-") == 0) push(pilha, val1 - val2);
            else if (strcmp(token, "*") == 0) push(pilha, val1 * val2);
            else if (strcmp(token, "/") == 0) {
                if (val2 == 0) {
                    printf("Erro: divisao por zero.\n");
                    freeStack(pilha);
                    exit(1);
                }
                push(pilha, val1 / val2);
            }

        } else if (isNumber(token)) {
            push(pilha, atof(token));
        } else {
            printf("Erro: token invalido encontrado: '%s'\n", token);
            freeStack(pilha);
            exit(1);
        }

        token = strtok(NULL, " ");
    }

    double resultado_final = pop(pilha);

    if (!isEmpty(pilha)) {
        printf("Erro: Expressao malformada (operandos demais).\n");
        freeStack(pilha);
        exit(1);
    }

    freeStack(pilha);
    return resultado_final;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Erro: Use o formato: %s \"<expressao>\"\n", argv[0]);
        return 1;
    }

    char expressao[256];
    strcpy(expressao, argv[1]);

    double resultado = evaluateRPN(expressao);
    printf("Resultado: %.2f\n", resultado);

    return 0;
}

