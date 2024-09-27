#include "model.c"

void sortingID()
    {
        load_data(processos, &total_processos);

        ID_sort(processos);
        
        save_data_IDOrder(processos);

        printf("Dados Organizados! (pelo ID, em ordem crescente)\n\n");
    }

void sortingDate()
    {
        load_data(processos, &total_processos);

        date_sort(processos);

        save_data_DateOrder(processos);

        printf("Dados Organizados! (pelas data, em ordem decrescente)\n\n");
    }

void countingClass(int input)
    {
        load_data(processos, &total_processos);

        int counter = get_classes_count(input);

        printf("\nO numero de processos registrados\nna classe de ID - %d, foi de %d\n\n", input, counter);
    }

void countingSubjects()
    {
        load_data(processos, &total_processos);

        int counter = get_subjects_count();

        printf("\nO numero de assuntos (IDs de assuntos)\nregistrados, foi de %d IDs de assunto\n\n", counter);
    }

void countDaysDate(int input)
    {
        load_data(processos, &total_processos);

        int days = get_day_count(input);

        if(days == -1)
            {
                printf("\nHouve um erro ao processar a data do processo!\n");
                return;
            }
        
        printf("\n O processo esta tramitando faz %d dias.\n\n", days);
    }