#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "cadastro.h"
#include "postagem.h"

int cor(NoLLRB* H) {
    if (H == NULL) return BLACK;
    return H->cor;
}

void trocaCor(NoLLRB* H) {
    H->cor = !H->cor;
    if (H->esq != NULL) H->esq->cor = !H->esq->cor;
    if (H->dir != NULL) H->dir->cor = !H->dir->cor;
}

NoLLRB* rotacionaEsquerda(NoLLRB* A) {
    NoLLRB* B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

NoLLRB* rotacionaDireita(NoLLRB* A) {
    NoLLRB* B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

NoLLRB* insereNO_LLRB(NoLLRB* H, Usuario* user, int* resp) {
    if (H == NULL) {
        NoLLRB* novo = (NoLLRB*)malloc(sizeof(NoLLRB));
        novo->user = user;
        novo->cor = RED;
        novo->esq = NULL;
        novo->dir = NULL;
        *resp = 1;
        return novo;
    }

    if (user->id == H->user->id) {
        *resp = 0; 
    } else if (user->id < H->user->id) {
        H->esq = insereNO_LLRB(H->esq, user, resp);
    } else {
        H->dir = insereNO_LLRB(H->dir, user, resp);
    }

    if (cor(H->dir) == RED && cor(H->esq) == BLACK) H = rotacionaEsquerda(H);
    if (cor(H->esq) == RED && cor(H->esq->esq) == RED) H = rotacionaDireita(H);
    if (cor(H->esq) == RED && cor(H->dir) == RED) trocaCor(H);

    return H;
}

int funcao_hash_nome(const char* nome) {
    unsigned long hash = 5381;
    int c;
    while ((c = *nome++)) {
        hash = ((hash << 5) + hash) + c; 
    }
    return hash % TAM_HASH;
}

SistemaCadastro* inicializar_cadastro() {
    SistemaCadastro* sis = (SistemaCadastro*) malloc(sizeof(SistemaCadastro));
    if (sis != NULL) {
        sis->qtd_usuarios = 0;
        sis->raiz_llrb = NULL;
        for (int i = 0; i < TAM_HASH; i++) {
            sis->tabela[i] = NULL;
        }
    }
    return sis;
}

Usuario* buscar_por_id(SistemaCadastro* sis, int id) {
    if (sis == NULL) return NULL;
    NoLLRB* atual = sis->raiz_llrb;
    while (atual != NULL) {
        if (id == atual->user->id) return atual->user;
        if (id < atual->user->id) atual = atual->esq;
        else atual = atual->dir;
    }
    return NULL;
}

Usuario* buscar_por_nome(SistemaCadastro* sis, const char* nome) {
    if (sis == NULL || nome == NULL) return NULL;
    int indice = funcao_hash_nome(nome);
    NoHash* atual = sis->tabela[indice];
    while (atual != NULL) {
        if (strcasecmp(atual->user->nome, nome) == 0) {
            return atual->user;
        }
        atual = atual->prox;
    }
    return NULL;
}

int cadastrar_usuario(SistemaCadastro* sis, int id, const char* nome, const char* login) {
    if (sis == NULL) return 0;

    if (buscar_por_id(sis, id) != NULL) return 0;

    for (int i = 0; i < TAM_HASH; i++) {
        NoHash* atual = sis->tabela[i];
        while (atual != NULL) {
            if (strcmp(atual->user->login, login) == 0) return -1;
            if (strcasecmp(atual->user->nome, nome) == 0) return -2;
            atual = atual->prox;
        }
    }

    Usuario* novo_user = (Usuario*) malloc(sizeof(Usuario));
    novo_user->id = id;
    strncpy(novo_user->nome, nome, MAX_NOME - 1);
    novo_user->nome[MAX_NOME - 1] = '\0';
    strncpy(novo_user->login, login, MAX_LOGIN - 1);
    novo_user->login[MAX_LOGIN - 1] = '\0';
    novo_user->publicacoes = inicializar_publicacoes();

    int resp = 0;
    sis->raiz_llrb = insereNO_LLRB(sis->raiz_llrb, novo_user, &resp);
    if (sis->raiz_llrb != NULL) sis->raiz_llrb->cor = BLACK;

    int indice = funcao_hash_nome(nome);
    NoHash* novo_no = (NoHash*) malloc(sizeof(NoHash));
    novo_no->user = novo_user;
    novo_no->prox = sis->tabela[indice];
    sis->tabela[indice] = novo_no;

    sis->qtd_usuarios++;
    return 1;
}

void liberar_llrb(NoLLRB* raiz) {
    if (raiz != NULL) {
        liberar_llrb(raiz->esq);
        liberar_llrb(raiz->dir);
        free(raiz); 
    }
}

void liberar_cadastro(SistemaCadastro* sis) {
    if (sis == NULL) return;

    liberar_llrb(sis->raiz_llrb); 

    for (int i = 0; i < TAM_HASH; i++) {
        NoHash* atual = sis->tabela[i];
        while (atual != NULL) {
            NoHash* temp = atual;
            atual = atual->prox;
            
            if (temp->user != NULL) {
                if (temp->user->publicacoes != NULL) {
                    liberar_publicacoes(temp->user->publicacoes);
                }
                free(temp->user); 
            }
            free(temp); 
        }
    }
    free(sis);
}