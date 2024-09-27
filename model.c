#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void menuOptions();
int getInput();
void processInput(int input);
void classOption();
void dateOption();

typedef struct
    {
        int id;
        char numero[35];
        char data_ajuizamento[35];
        int id_classe[2];
        int id_assunto[2];
        int ano_eleicao;
    } Processo;

Processo processos[100000];
int total_processos;

void load_data(Processo processos[], int *total_processos)
    {
        FILE *file = fopen("dados.csv", "r");
        if (file == NULL)
            {
                printf("Houve um erro ao abrir arquivo");
                return;
            }

        char line[200];
        *total_processos = 0;
        int i = 0;
        while (fgets(line, sizeof(line), file))
            {
                if (i == 0)
                    {
                        i++;
                        continue;
                    }

                Processo p;
                p.id_classe[1] = 0;
                p.id_assunto[1] = 0;

                if (sscanf(line,"%d,\"%[^\"]\",%[^,],{%d},{%d},%d",
                &p.id, p.numero,
                p.data_ajuizamento,
                &p.id_classe[0],
                &p.id_assunto[0],
                &p.ano_eleicao) == 6)
                    {
                        processos[(*total_processos)++] = p;
                        continue;
                    }

                if (sscanf(line,"%d,\"%[^\"]\",%[^,],\"{%d,%d}\",{%d},%d",
                &p.id,
                p.numero,
                p.data_ajuizamento,
                &p.id_classe[0],
                &p.id_classe[1],
                &p.id_assunto[0],
                &p.ano_eleicao) == 7)
                    {
                        processos[(*total_processos)++] = p;
                        continue;
                    }

                if (sscanf(line,"%d,\"%[^\"]\",%[^,],{%d},\"{%d,%d}\",%d",
                &p.id,
                p.numero,
                p.data_ajuizamento,
                &p.id_classe[0],
                &p.id_assunto[0],
                &p.id_assunto[1],
                &p.ano_eleicao) == 7)
                    {
                        processos[(*total_processos)++] = p;
                        continue;
                    }


            }
        fclose(file);
    }

int compareID(const void *a, const void *b)
    {
        Processo *x1 = (Processo *)a;
        Processo *x2 = (Processo *)b;

        return (x1->id - x2->id);
    }

void ID_sort(Processo processos[])
    {
        qsort(processos, total_processos, sizeof(Processo), compareID);
    }

void save_data(Processo processos[], const char* filename)
    {
        FILE *file = fopen(filename, "w");
        if (file == NULL)
                {
                    printf("Houve um erro ao abrir arquivo");
                    return;
                }

        fprintf(file, "\"id\",\"numero\",\"data_ajuizamento\",\"id_classe\",\"id_assunto\",\"ano_eleicao\"\n");
        for (int i = 0; i < total_processos; i++)
            {
                Processo p = processos[i];

                if (p.id_classe[1] == 0 && p.id_assunto[1] == 0)
                    {
                        fprintf(file, "%d,\"%s\",%s,{%d},{%d},%d\n",
                            p.id,
                            p.numero,
                            p.data_ajuizamento,
                            p.id_classe[0],
                            p.id_assunto[0],
                            p.ano_eleicao);
                    }

                if (p.id_classe[1] != 0 && p.id_assunto[1] == 0)
                    {
                        fprintf(file, "%d,\"%s\",%s,\"{%d,%d}\",{%d},%d\n",
                            p.id,
                            p.numero,
                            p.data_ajuizamento,
                            p.id_classe[0],
                            p.id_classe[1],
                            p.id_assunto[0],
                            p.ano_eleicao);
                    }

                if (p.id_classe[1] == 0 && p.id_assunto[1] != 0)
                    {
                        fprintf(file, "%d,\"%s\",%s,{%d},\"{%d,%d}\",%d\n",
                            p.id,
                            p.numero,
                            p.data_ajuizamento,
                            p.id_classe[0],
                            p.id_assunto[0],
                            p.id_assunto[1],
                            p.ano_eleicao);
                    }

            }

        fclose(file);
    }

void save_data_IDOrder(Processo processos[])
    {
        save_data(processos, "resultado_1.csv");
    }

int compareDate(const void *a, const void *b)
    {
        Processo *A = (Processo *)a;
        Processo *B = (Processo *)b;

        return strcmp(B->data_ajuizamento, A->data_ajuizamento);
    }

void date_sort()
    {
        qsort(processos, total_processos, sizeof(Processo), compareDate);
    }

void save_data_DateOrder(Processo processos[])
    {
        save_data(processos, "resultado_2.csv");
    }

int get_classes_count(int input)
    {
        int counter = 0;

        for (int i = 0; i < total_processos; i++)
            if(processos[i].id_classe[0] == input || processos[i].id_classe[1] == input) 
                counter++;

        return counter;
    }

int get_subjects_count()
    {
        int counter = 0;
        int seenIDs[(sizeof(processos)/sizeof(processos[0]))];
        
        int isUniqueA;
        int isUniqueB;

        for (int i = 0; i < total_processos; i++)
            {
                isUniqueA = 1;
                isUniqueB = 1;

                for (int j = 0; j < counter; j++)
                    {
                        if (processos[i].id_assunto[0] == seenIDs[j])
                            {
                                isUniqueA = 0; 
                                break;
                            }
                    }

                if (isUniqueA)
                    {
                        seenIDs[counter++] = processos[i].id_assunto[0];
                    }

                for (int j = 0; j < counter; j++)
                    {
                        if (processos[i].id_assunto[1] == seenIDs[j])
                            {
                                isUniqueB = 0; 
                                break;
                            }
                    }

                if (isUniqueB)
                    {
                        seenIDs[counter++] = processos[i].id_assunto[1];
                    }
            }

        return counter;
    }

int get_day_count(int input)
    {
        Processo p;
        p.id = -1;

        for (int i; i<total_processos; i++)
            {
                if (processos[i].id == input)
                    {
                        p = processos[i];
                        break;
                    }
            }

        if (p.id == -1)
            {
                printf("\nNenhum processo foi encontrado com esse ID!\n\n");
                return -1;
            }

        struct tm tm = {0};
        sscanf(p.data_ajuizamento, "%d-%d-%d %d:%d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
        tm.tm_year -= 1900;
        tm.tm_mon -= 1;

        return (time(NULL) - mktime(&tm)) / (60 * 60 * 24);
    }