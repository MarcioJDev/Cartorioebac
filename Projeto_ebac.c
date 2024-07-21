#include <stdio.h> // biblioteca de comunica��o com o usu�rio
#include <stdlib.h> // biblioteca de aloca��o de espa�o em mem�ria
#include <locale.h> // biblioteca de aloca��es de texto por regi�o
#include <string.h> // biblioteca respons�vel por cuidar das strings

// Fun��o para criar backup de dados
void criarBackup(char *arquivo) {
    char backupNome[45];
    strcpy(backupNome, arquivo);
    strcat(backupNome, "_backup");

    FILE *arquivoOriginal = fopen(arquivo, "r");
    FILE *arquivoBackup = fopen(backupNome, "w");

    if (arquivoOriginal == NULL || arquivoBackup == NULL) {
        if (arquivoOriginal != NULL) fclose(arquivoOriginal);
        if (arquivoBackup != NULL) fclose(arquivoBackup);
        return;
    }

    char c;
    while ((c = fgetc(arquivoOriginal)) != EOF) {
        fputc(c, arquivoBackup);
    }

    fclose(arquivoOriginal);
    fclose(arquivoBackup);
}

// Fun��o para registrar um novo usu�rio
int registro() {
    char arquivo[40];
    char cpf[40];
    char nome[40];
    char sobrenome[40];
    char cargo[40];
    
    printf("Digite o CPF a ser cadastrado: ");
    scanf("%s", cpf);
    
    strcpy(arquivo, cpf);
    
    FILE *file = fopen(arquivo, "w"); // cria arquivo para o CPF
    if (file == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 1;
    }
    fprintf(file, cpf);
    fclose(file);
    
    file = fopen(arquivo, "a");
    fprintf(file, ",");
    fclose(file);
    
    printf("Digite o nome a ser cadastrado: ");
    scanf("%s", nome);
    
    file = fopen(arquivo, "a");
    fprintf(file, nome);
    fclose(file);
    
    file = fopen(arquivo, "a");
    fprintf(file, ",");
    fclose(file);
    
    printf("Digite o sobrenome a ser cadastrado: ");
    scanf("%s", sobrenome);
    
    file = fopen(arquivo, "a");
    fprintf(file, sobrenome);
    fclose(file);
    
    file = fopen(arquivo, "a");
    fprintf(file, ",");
    fclose(file);
    
    printf("Digite o cargo a ser cadastrado: ");
    scanf("%s", cargo);
    
    file = fopen(arquivo, "a");
    fprintf(file, cargo);
    fclose(file);
    
    system("pause");
    return 0;
}

// Fun��o para consultar informa��es de um usu�rio
int consulta() {
    setlocale(LC_ALL, "Portuguese");
    
    char cpf[40];
    char conteudo[100];
    
    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);
    
    FILE *file = fopen(cpf, "r");
    
    if (file == NULL) {
        printf("N�o foi poss�vel abrir o arquivo, n�o localizado!\n");
        return 1;
    }
    
    printf("\nEssas s�o as informa��es do usu�rio:\n");
    while (fgets(conteudo, 100, file) != NULL) {
        printf("%s", conteudo);
    }
    printf("\n\n");

    fclose(file);
    system("pause");
    return 0;
}

// Fun��o para deletar um usu�rio
int deletar() {
    char cpf[40];
    
    printf("Digite o CPF do usu�rio a ser deletado: ");
    scanf("%s", cpf);
    
    FILE *file = fopen(cpf, "r"); // verifica se o arquivo existe
    
    if (file == NULL) {
        printf("O usu�rio n�o se encontra no sistema!\n");
    } else {
        fclose(file); // fecha o arquivo
        criarBackup(cpf); // cria backup do arquivo
        if (remove(cpf) == 0) { // tenta remover o arquivo
            printf("Usu�rio deletado com sucesso!\n");
        } else {
            printf("Erro ao deletar o usu�rio.\n");
        }
    }
    
    system("pause");
    return 0;
}

// Fun��o principal
int main() {
    int opcao = 0;
    
    while (1) {
        system("cls");
        
        setlocale(LC_ALL, "portuguese"); // define a linguagem
        
        printf(" ####### Cart�rio EBAC #######\n\n");
        printf("Escolha a op��o desejada do menu:\n\n");
        printf("\t1 - Registrar nomes\n");
        printf("\t2 - Consultar nomes\n");
        printf("\t3 - Deletar nomes\n");
        printf("Op��o: ");
        
        scanf("%d", &opcao); // l� a escolha do usu�rio

        system("cls");
        
        switch (opcao) {
            case 1:
                registro(); // chama a fun��o de registro
                break;
            case 2:
                consulta(); // chama a fun��o de consulta
                break;
            case 3:
                deletar(); // chama a fun��o de deletar
                break;
            default:
                printf("Essa op��o n�o est� dispon�vel!\n");
                system("pause");
                break;
        }
    }
    return 0;
}

