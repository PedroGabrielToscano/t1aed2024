#ifndef LIVRO_H
#define LIVRO_H

#include <stdio.h>

// Definições para tamanhos máximos dos campos de string
#define MAX_TITULO 150
#define MAX_AUTOR 200
#define MAX_EDITORA 50

// Estrutura do Registro de Livro
typedef struct Livro {
    int codigo;                        // Código do livro, único para cada livro
    char titulo[MAX_TITULO];           // Título do livro
    char autor[MAX_AUTOR];             // Autor do livro
    char editora[MAX_EDITORA];         // Editora do livro
    int edicao;                        // Edição do livro
    int ano_publicacao;                // Ano de publicação do livro
    float preco;                       // Preço do livro
    int quantidade_estoque;            // Quantidade em estoque
    int prox_registro;                 // Ponteiro para o próximo registro na lista encadeada
} Livro;

// Funções relacionadas aos livros

// Cadastra um livro no arquivo binário
// pre-condicao: arquivo deve estar aberto para leitura e escrita
// pos-condicao: livro cadastrado no arquivo binário
// Entrada: nome do arquivo binário e estrutura Livro contendo as informações do livro
// Retorno: nenhum
void cadastrarLivro(const char *nome_arquivo, Livro livro);

// Remove um livro do arquivo binário
// pre-condicao: arquivo deve estar aberto para leitura e escrita
// pos-condicao: livro removido do arquivo binário, e posição adicionada à lista de registros livres
// Entrada: nome do arquivo binário e código do livro a ser removido
// Retorno: nenhum
void removerLivro(const char *nome_arquivo, int codigo);

// Imprime os dados de um livro específico
// pre-condicao: arquivo deve estar aberto para leitura
// pos-condicao: dados do livro impressos na tela
// Entrada: nome do arquivo binário e código do livro a ser impresso
// Retorno: nenhum
void imprimirLivro(const char *nome_arquivo, int codigo);

// Lista todos os livros cadastrados no sistema
// pre-condicao: arquivo deve estar aberto para leitura
// pos-condicao: lista de livros impressa na tela
// Entrada: nome do arquivo binário
// Retorno: nenhum
void listarTodosLivros(const char *nome_arquivo);

// Busca livros por autor
// pre-condicao: arquivo deve estar aberto para leitura
// pos-condicao: títulos dos livros do autor impressos na tela
// Entrada: nome do arquivo binário e nome do autor a ser buscado
// Retorno: nenhum
void buscarPorAutor(const char *nome_arquivo, const char *autor);

// Busca livros por título
// pre-condicao: arquivo deve estar aberto para leitura
// pos-condicao: dados do livro com o título fornecido impressos na tela
// Entrada: nome do arquivo binário e título do livro a ser buscado
// Retorno: nenhum
void buscarPorTitulo(const char *nome_arquivo, const char *titulo);

#endif
