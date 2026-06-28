#include <stdio.h>
#include <direct.h>

void criar_pasta_output(void)
{
    _mkdir("output");
}

void gerar_nome_saida(char *nome)
{
    FILE *teste;
    int numero = 0;

    while (1)
    {
        if (numero == 0)
            sprintf(nome, "output/saida.txt");
        else
            sprintf(nome, "output/saida%d.txt", numero);

        teste = fopen(nome, "r");

        if (teste == NULL)
            break;

        fclose(teste);
        numero++;
    }
}