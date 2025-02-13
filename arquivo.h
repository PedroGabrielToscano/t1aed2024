#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdio.h>
#include "livro.h"

// Estrutura do Cabeçalho do Arquivo Binário
typedef struct Cabecalho {
    int posicao_inicio_lista;          // Posição inicial da lista encadeada de livros
    int posicao_primeiro_livre;        // Posição do primeiro registro livre no arquivo
    int posicao_lista_livres;          // Posição do início da lista de registros removidos (livres)
} Cabecalho;

// Funções relacionadas ao gerenciamento do arquivo binário

// Inicializa o arquivo binário
// pre-condicao: nome_arquivo deve ser um nome de arquivo válido
// pos-condicao: arquivo binário criado e cabeçalho inicializado, ou arquivo existente aberto para leitura/escrita
// Entrada: nome do arquivo binário
// Retorno: nenhum
void inicializarArquivo(const char *nome_arquivo);

// Carrega dados de um arquivo texto e cadastra no sistema
// pre-condicao: arquivo de texto deve estar no formato correto
// pos-condicao: dados do arquivo texto carregados e cadastrados no sistema
// Entrada: nome do arquivo binário e nome do arquivo texto
// Retorno: nenhum
void carregarArquivoDados(const char *nome_arquivo, const char *arquivo_txt);

// Imprime a lista de registros livres
// pre-condicao: arquivo deve estar aberto para leitura
// pos-condicao: posições livres impressas na tela
// Entrada: nome do arquivo binário
// Retorno: nenhum
void imprimirListaLivres(const char *nome_arquivo);
void substituirVirgulaPorPonto(char *str);
void removerEspacos(char *str);

#endif
