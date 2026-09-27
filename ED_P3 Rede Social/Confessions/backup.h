#ifndef BACKUP_H
#define BACKUP_H

#include "cadastro.h"
#include "rede_amizade.h"
#include "postagem.h"
#include "historico.h"

int salvar_backup(SistemaCadastro* sis, Grafo* g, PilhaHistorico* pi);
int carregar_backup(SistemaCadastro* sis, Grafo* g, PilhaHistorico* pi);

#endif