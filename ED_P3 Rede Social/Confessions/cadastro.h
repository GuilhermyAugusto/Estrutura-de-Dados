#ifndef CADASTRO_H
#define CADASTRO_H

#include "dados_usuario.h"

#define TAM_HASH 10
#define RED 1
#define BLACK 0

typedef struct no_llrb {
    Usuario* user;
    int cor;
    struct no_llrb *esq, *dir;
} NoLLRB;

typedef struct no_hash {
    Usuario* user;
    struct no_hash* prox;
} NoHash;

struct sistema_cadastro {
    NoLLRB* raiz_llrb;
    NoHash* tabela[TAM_HASH];
    int qtd_usuarios;
};

typedef struct sistema_cadastro SistemaCadastro;

SistemaCadastro* inicializar_cadastro();
int cadastrar_usuario(SistemaCadastro* sis, int id, const char* nome, const char* login);
Usuario* buscar_por_id(SistemaCadastro* sis, int id);
Usuario* buscar_por_nome(SistemaCadastro* sis, const char* nome);
void liberar_cadastro(SistemaCadastro* sis);

#endif