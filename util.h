#ifndef UTIL_H
#define UTIL_H

// Funções auxiliares

// Calcula o total de livros cadastrados
// pre-condicao: arquivo deve estar aberto para leitura
// pos-condicao: total de livros cadastrado retornado
// Entrada: nome do arquivo binário
// Retorno: número total de livros cadastrados no sistema
int calcularTotalLivros(const char *nome_arquivo);
int buscarLivroPorCodigo(const char *nome_arquivo, int codigo);
#endif
