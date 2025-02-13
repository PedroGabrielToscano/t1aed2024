#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "arquivo.h"

// Implementação das funções auxiliares

// Calcula o total de livros cadastrados
// Conta e retorna o número total de livros cadastrados no arquivo binário
// pre-condicao: arquivo deve estar aberto para leitura
// pos-condicao: total de livros cadastrado retornado
// Entrada: nome do arquivo binário
// Retorno: número total de livros cadastrados no sistema
int calcularTotalLivros(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo binário");
        exit(EXIT_FAILURE);
    }

    Cabecalho cabecalho;
    fread(&cabecalho, sizeof(Cabecalho), 1, arquivo);

    int posicao_atual = cabecalho.posicao_inicio_lista;
    int total_livros = 0;
    Livro livro;

    while (posicao_atual != -1) {
        fseek(arquivo, posicao_atual, SEEK_SET);
        fread(&livro, sizeof(Livro), 1, arquivo);
        total_livros++;
        posicao_atual = livro.prox_registro;
    }

    fclose(arquivo);
    return total_livros;
}

int buscarLivroPorCodigo(const char *nome_arquivo, int codigo) {
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo binário");
        exit(EXIT_FAILURE);
    }

    Cabecalho cabecalho;
    fread(&cabecalho, sizeof(Cabecalho), 1, arquivo);

    int posicao_atual = cabecalho.posicao_inicio_lista;
    Livro livro;

    while (posicao_atual != -1) {
        fseek(arquivo, posicao_atual, SEEK_SET);
        fread(&livro, sizeof(Livro), 1, arquivo);
        if (livro.codigo == codigo) {
            fclose(arquivo);
            return 1;
        }
        posicao_atual = livro.prox_registro;
    }

    fclose(arquivo);
    return 0;
}
