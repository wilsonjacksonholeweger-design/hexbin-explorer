#include <stdio.h>
#include <string.h> // Necessário para tratar a quebra de linha

void print_binario(unsigned char byte) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (byte >> i) & 1);
    }
}

int main() {
    char nome_arquivo[256];
    
    printf("Digite o nome do arquivo que deseja analisar (ex: jogo.nes): ");
    // Lê o nome do arquivo digitado pelo usuário
    if (fgets(nome_arquivo, sizeof(nome_arquivo), stdin) != NULL) {
        // Remove o caractere de nova linha que o fgets adiciona
        nome_arquivo[strcspn(nome_arquivo, "\n")] = 0;
    }

    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) {
        printf("Erro: Nao foi possivel abrir o arquivo '%s'. Verifique se ele esta na mesma pasta.\n", nome_arquivo);
        return 1;
    }

    unsigned char buffer;
    int contador = 0;

    printf("\nOffset | Hex | Binario\n");
    printf("---------------------------\n");

    while (fread(&buffer, sizeof(unsigned char), 1, arquivo) == 1) {
        printf("%06X | %02X  | ", contador, buffer);
        print_binario(buffer);
        printf("\n");
        contador++;
        
        // Pausa a cada 20 bytes para não encher a tela de uma vez
        if (contador % 20 == 0) {
            printf("\n--- Pressione Enter para continuar... ---\n");
            getchar(); 
        }
    }

    fclose(arquivo);
    printf("\nLeitura finalizada.\n");
    return 0;
}