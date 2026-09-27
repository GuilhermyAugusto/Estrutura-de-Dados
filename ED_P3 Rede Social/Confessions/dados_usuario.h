#ifndef DADOS_USUARIO_H
#define DADOS_USUARIO_H

#define MAX_NOME 50
#define MAX_LOGIN 20

typedef struct lista_publi ListaPubli;

typedef struct usuario {
    int id;
    char nome[MAX_NOME];
    char login[MAX_LOGIN];
    ListaPubli* publicacoes;
} Usuario;

#endif