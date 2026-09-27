#ifndef HISTORICO_H
#define HISTORICO_H

#define MAX_HISTORICO 100 
#define TAM_DESC 255      

typedef struct {
    char descricao[TAM_DESC];
} Atividade;

typedef struct pilha_hist PilhaHistorico;

struct pilha_hist {
    Atividade dados[MAX_HISTORICO];
    int qtd;
};

PilhaHistorico* inicializar_historico();
int registrar_atividade(PilhaHistorico* pi, const char* desc);
void exibir_historico(PilhaHistorico* pi);
void liberar_historico(PilhaHistorico* pi);

#endif