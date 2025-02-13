#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "util.h"

// Implementação das funções relacionadas ao arquivo binário

// Inicializa o arquivo binário
// Escreve o cabeçalho inicial no arquivo caso ele não exista
// pre-condicao: nome_arquivo deve ser um nome de arquivo válido
// pos-condicao: arquivo binário criado e cabeçalho inicializado, ou arquivo existente aberto para leitura/escrita
// Entrada: nome do arquivo binário
// Retorno: nenhum
void inicializarArquivo(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "rb+");
    if (!arquivo) {
        printf("Arquivo binário não encontrado. Criando um novo arquivo.\n");
        arquivo = fopen(nome_arquivo, "wb+");
        if (!arquivo) {
            perror("Erro ao criar o arquivo binário");
            exit(EXIT_FAILURE);
        }

        Cabecalho cabecalho = { -1, -1, -1 };
        fwrite(&cabecalho, sizeof(Cabecalho), 1, arquivo);
    } else {
        printf("Arquivo binário existente encontrado.\n");
    }
    fclose(arquivo);
}

// Carrega dados de um arquivo texto e cadastra no sistema
// Lê um arquivo texto com dados de livros e cadastra cada livro no sistema, evitando duplicatas
// pre-condicao: arquivo de texto deve estar no formato correto
// pos-condicao: dados do arquivo texto carregados e cadastrados no sistema
// Entrada: nome do arquivo binário e nome do arquivo texto
// Retorno: nenhum
void carregarArquivoDados(const char *nome_arquivo, const char *arquivo_txt) {
    FILE *arquivo = fopen(arquivo_txt, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de texto");
        exit(EXIT_FAILURE);
    }

    char linha[512];
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Remove a nova linha (\n) no final da string
        linha[strcspn(linha, "\n")] = '\0';

        Livro livro;
        char *token;

        // Tratamento da linha para remover espaços em branco
        removerEspacos(linha);

        // Primeiro token: código do livro
        token = strtok(linha, ";");
        removerEspacos(token);
        livro.codigo = atoi(token);

        // Verifica se o livro já existe pelo código
        if (buscarLivroPorCodigo(nome_arquivo, livro.codigo)) {
            printf("Livro com código %d já existe.\n", livro.codigo);
            continue;
        }

        // Segundo token: título
        token = strtok(NULL, ";");
        removerEspacos(token);
        strcpy(livro.titulo, token);

        // Terceiro token: autor
        token = strtok(NULL, ";");
        removerEspacos(token);
        strcpy(livro.autor, token);

        // Quarto token: editora
        token = strtok(NULL, ";");
        removerEspacos(token);
        strcpy(livro.editora, token);

        // Quinto token: edição
        token = strtok(NULL, ";");
        removerEspacos(token);
        livro.edicao = atoi(token);

        // Sexto token: ano de publicação
        token = strtok(NULL, ";");
        removerEspacos(token);
        livro.ano_publicacao = atoi(token);

        // Sétimo token: preço
        token = strtok(NULL, ";");
        removerEspacos(token);
        substituirVirgulaPorPonto(token);
        livro.preco = atof(token);

        // Oitavo token: quantidade em estoque
        token = strtok(NULL, ";");
        removerEspacos(token);
        livro.quantidade_estoque = atoi(token);

        // Inicializando o campo prox_registro
        livro.prox_registro = -1;

        // Cadastrando o livro
        cadastrarLivro(nome_arquivo, livro);
    }

    fclose(arquivo);
}

// Imprime a lista de registros livres
// Exibe as posições dos registros que foram removidos e estão disponíveis para reutilização
// pre-condicao: arquivo deve estar aberto para leitura
// pos-condicao: posições livres impressas na tela
// Entrada: nome do arquivo binário
// Retorno: nenhum
void imprimirListaLivres(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo binário");
        exit(EXIT_FAILURE);
    }

    Cabecalho cabecalho;
    fread(&cabecalho, sizeof(Cabecalho), 1, arquivo);

    int posicao_livre = cabecalho.posicao_primeiro_livre;
    Livro livro;

    printf("Lista de registros livres:\n");
    while (posicao_livre != -1) {
        fseek(arquivo, posicao_livre, SEEK_SET);
        fread(&livro, sizeof(Livro), 1, arquivo);
        printf("Posição Livre: %d\n", posicao_livre);
        posicao_livre = livro.prox_registro;
    }

    fclose(arquivo);
}



// Função para substituir vírgulas por pontos em strings de números
void substituirVirgulaPorPonto(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
}

// Função para remover espaços em branco no início e fim de uma string
void removerEspacos(char *str) {
    // Remove espaços à direita
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        len--;
    }
    str[len] = '\0';

    // Remove espaços à esquerda
    int start = 0;
    while (str[start] != '\0' && isspace((unsigned char)str[start])) {
        start++;
    }

    if (start > 0) {
        memmove(str, str + start, len - start + 1);
    }
}
