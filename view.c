#include "controller.c"

typedef void (*options)(void);

void mainMenu()
    {
        processInput(getInput(menuOptions));
    }

int getInput(options op)
    {
        system("cls");
        int x;

        while(1)
            {
                op(); 
                fflush(stdin);
                if(scanf("%d", &x) == 1) return x;
                system("cls");
                printf("Houve um erro processando o input, tente novamente\n\n");
            }
    }

void processInput(int input)
    {
        do
            {
                switch (input)
                    {
                        case 1:
                            sortingID();
                            break;
                        case 2:
                            sortingDate();
                            break;
                        case 3:
                            countingClass(getInput(classOption));
                            break;
                        case 4:
                            countingSubjects();
                            break;
                        case 5:
                            countDaysDate(getInput(dateOption));
                            break;
                    }

                if (input < 0 || input > 5) printf("\nOpcao escolhida nao disponivel!\n");
                
                printf("(Pressione enter para continuar.)");
                fflush(stdin);
                while (getchar() != '\n');

                input = getInput(menuOptions);
            }
        while (input != 0);
    };

    
void menuOptions()
    {
        printf("Menu principal - Selecione a sua opcao [1-5]\n");
        printf("(Use 0 para sair do sistema)\n\n");
        printf("1 - Ordenar pelo ID (ordem crescente)\n");
        printf("2 - Ordenar pela data (ordem decrescente)\n");
        printf("3 - Contagem de processos vinculados a uma classe (id_classe)\n");
        printf("4 - Contagem de quantos IDs de assuntos constam nos processos\n");
        printf("5 - Indicar a quantos dias um processo esta em tramitacao\n");
    }

void classOption()
    {
        printf("Insira uma classe (id de uma classe), para verifacacao \n");
        printf("de quantos processos estao associados a essa:\n\n");
    }

void dateOption()
    {
        printf("Insira o ID de um processo, para verificacao de\nquantos dias o processo esta em tramitando\n\n");
    }