#include <stdio.h>
#include <string.h>

int main() {
    char nome_arquivo[256];
    
    printf("Digite o nome do arquivo que deseja analisar: ");
    if (fgets(nome_arquivo, sizeof(nome_arquivo), stdin) != NULL) {
        nome_arquivo[strcspn(nome_arquivo, "\n")] = 0;
    }

    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) {
        printf("Erro: Nao foi possivel abrir o arquivo '%s'.\n", nome_arquivo);
        return 1;
    }

    FILE *saida = fopen("saida.txt", "w");
    if (!saida) {
        printf("Erro ao criar arquivo de saida.\n");
        fclose(arquivo);
        return 1;
    }

    // Apenas UMA declaração de buffer
    unsigned char buffer[16];
    long offset = 0;
    size_t bytes_lidos;

    fprintf(saida, "Offset   | Hexadecimal\n");
    fprintf(saida, "------------------------\n");

    // Lê o arquivo em blocos de 16 bytes
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

    printf("\nAnalise finalizada. Resultados salvos em 'saida.txt'.\n");
    return 0;
}