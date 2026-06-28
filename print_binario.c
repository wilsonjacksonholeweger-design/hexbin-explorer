#include <stdio.h>
#include <string.h>
#include "arquivo.h"

int main() {
    char nome_arquivo[256];
    
    printf("Digite o nome do arquivo que deseja analisar: ");
    if (fgets(nome_arquivo, sizeof(nome_arquivo), stdin) != NULL) {
        nome_arquivo[strcspn(nome_arquivo, "\n")] = 0;
    }

    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) {
        printf("Erro ao abrir arquivo '%s'.\n", nome_arquivo);
        return 1;
    }

    char nome_saida[256];

    criar_pasta_output();
    gerar_nome_saida(nome_saida);

    FILE *saida = fopen(nome_saida, "w");
    if (!saida) {
        printf("Erro ao criar arquivo de saida.\n");
        fclose(arquivo);
        return 1;
    }

    unsigned char buffer[16];
    long offset = 0;
    size_t bytes_lidos;

    fprintf(saida, "Offset   | Hexadecimal\n");
    fprintf(saida, "------------------------\n");

    while ((bytes_lidos = fread(buffer, 1, 16, arquivo)) > 0) {
        fprintf(saida, "%08lX | ", offset);

        for (size_t i = 0; i < bytes_lidos; i++) {
            fprintf(saida, "%02X ", buffer[i]);
        }
        fprintf(saida, "\n");

        offset += bytes_lidos;
    }

    fclose(arquivo);
    fclose(saida);

    printf("Analise finalizada. Resultados salvos em '%s'.\n", nome_saida);
    return 0;
}