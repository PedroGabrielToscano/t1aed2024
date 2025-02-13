#include <stdio.h>
#include "livro.h"
#include "arquivo.h"
#include "util.h"

int main() {
    char nome_arquivo[] = "livraria.bin";
    inicializarArquivo(nome_arquivo);

    int opcao;
    do {
        printf("----- Menu de Opera��es -----\n");
        printf("1. Cadastrar Livro\n");
        printf("2. Remover Livro\n");
        printf("3. Imprimir Dados de um Livro\n");
        printf("4. Listar Todos os Livros\n");
        printf("5. Buscar por Autor\n");
        printf("6. Buscar por T�tulo\n");
        printf("7. Calcular Total de Livros\n");
        printf("8. Carregar Dados de um Arquivo Texto\n");
        printf("9. Imprimir Lista de Registros Livres\n");
        printf("0. Sair\n");
        printf("----------------------------\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        int codigo;
        char titulo[MAX_TITULO], autor[MAX_AUTOR];
        Livro livro;

        switch (opcao) {
            case 1:
                printf("Digite os dados do livro:\n");
                printf("C�digo: ");
                scanf("%d", &livro.codigo);
                printf("T�tulo: ");
                scanf(" %[^\n]", livro.titulo);
                printf("Autor: ");
                scanf(" %[^\n]", livro.autor);
                printf("Editora: ");
                scanf(" %[^\n]", livro.editora);
                printf("Edi��o: ");
                scanf("%d", &livro.edicao);
                printf("Ano de Publica��o: ");
                scanf("%d", &livro.ano_publicacao);
                printf("Pre�o: ");
                scanf("%f", &livro.preco);
                printf("Quantidade em Estoque: ");
                scanf("%d", &livro.quantidade_estoque);
                cadastrarLivro(nome_arquivo, livro);
                break;

            case 2:
                printf("Digite o c�digo do livro a ser removido: ");
                scanf("%d", &codigo);
                removerLivro(nome_arquivo, codigo);
                break;

            case 3:
                printf("Digite o c�digo do livro: ");
                scanf("%d", &codigo);
                imprimirLivro(nome_arquivo, codigo);
                break;

            case 4:
                listarTodosLivros(nome_arquivo);
                break;

            case 5:
                printf("Digite o nome do autor: ");
                scanf(" %[^\n]", autor);
                buscarPorAutor(nome_arquivo, autor);
                break;

            case 6:
                printf("Digite o t�tulo do livro: ");
                scanf(" %[^\n]", titulo);
                buscarPorTitulo(nome_arquivo, titulo);
                break;

            case 7:
                printf("Total de livros cadastrados: %d\n", calcularTotalLivros(nome_arquivo));
                break;

            case 8: {
                char arquivo_txt[100];
                printf("Digite o nome do arquivo de texto: ");
                scanf("%s", arquivo_txt);
                carregarArquivoDados(nome_arquivo, arquivo_txt);
                break;
            }

            case 9:
                imprimirListaLivres(nome_arquivo);
                break;

            case 0:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Op��o inv�lida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
