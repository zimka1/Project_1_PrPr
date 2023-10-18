#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 1000

void checkOpenFile(FILE **Dataloger, int *kol_v, int kol_n, int *numberOfRecords, char ***ID, char ***pozicia, char ***typ, double **hodnota, char ***cas, int **datum)
{

    if (*kol_v == 0)
    {
        *Dataloger = fopen("dataloger.txt", "r");
        *kol_v = 1;
    }

    if (*Dataloger == NULL)
    {
        printf("Neotvoreny subor\n");
        return;
    }

    if (kol_n == 1)
    {

        for (int i = 0; i < *numberOfRecords; i++)
        {
            printf("ID. mer. modulu: %s\n", (*ID)[i]);
            printf("poziciaícia modulu: %s\n", (*pozicia)[i]);
            printf("Typ mer. veliciny: %s\n", (*typ)[i]);
            printf("hodnotanota: %lf\n", (*hodnota)[i]);
            printf("Cas merania: %s\n", (*cas)[i]);
            printf("Datum merania: %d\n", (*datum)[i]);
            printf("\n");
        }
    }
    else{
        while (1){

            char s[20];
            int w;
            double d;
            if (fscanf(*Dataloger, "%s", s) != EOF){
                printf("ID. mer. modulu: %s\n", s);
                
                if (fscanf(*Dataloger, "%s", s) != EOF){
                    printf("poziciaícia modulu: %s\n", s);
                    
                    if (fscanf(*Dataloger, "%s", s) != EOF){
                        printf("poziciaícia modulu: %s\n", s);
                            
                        if (fscanf(*Dataloger, "%s", s) != EOF){
                            printf("Typ mer. veliciny: %s\n", s);
                            
                            if (fscanf(*Dataloger, "%lf",&d) != EOF){
                                printf("hodnotanota: %lf\n", d);

                                if (fscanf(*Dataloger, "%s", s) != EOF){
                                    printf("Cas merania: %s\n", s);

                                    if (fscanf(*Dataloger, "%d", &w) != EOF){
                                        printf("Cas merania: %d\n", w);
                                        
                                    }
                                }
                            }
                        }
                    }
                    
                }
            
            }
            else if (s[0] == '\n')
            {
                continue;
            }
            else
            {
                break;
            }
            printf("\n");
            
        }
        *Dataloger = fopen("dataloger.txt", "r");
    }   
}

void freeArrays(char **ID, char **pozicia, char **typ, char **cas, double *hodnota, int *datum, int numberOfRecords)
{
    for (int i = 0; i < numberOfRecords; i++)
    {
        free(ID[i]);
        free(pozicia[i]);
        free(typ[i]);
        free(cas[i]);
    }

    free(ID);
    free(pozicia);
    free(typ);
    free(cas);
    free(hodnota);
    free(datum);
}

void createArrays(FILE **Dataloger, int *kol_n, int *numberOfRecords, char ***ID, char ***pozicia, char ***typ, double **hodnota, char ***cas, int **datum)
{

    if (*Dataloger == NULL)
    {
        printf("Neotvoreny subor\n");
        return;
    }
    if (*kol_n == 1)
    {
        freeArrays(*ID, *pozicia, *typ, *cas, *hodnota, *datum, *numberOfRecords);
        *Dataloger = fopen("dataloger.txt", "r");
        *numberOfRecords = 0;
    }

    double d;
    int w;

    *ID = (char **)malloc(sizeof(char *));
    *pozicia = (char **)malloc(sizeof(char *));
    *typ = (char **)malloc(sizeof(char *));
    *hodnota = (double *)malloc(sizeof(double));
    *cas = (char **)malloc(sizeof(char *));
    *datum = (int *)malloc(sizeof(int));

    while (1)
    {

        char s[6], s1[15], s2[3], s3[5];

        if (fscanf(*Dataloger, "%s", s) != EOF && s[0] != '\n')
        {

            *ID = (char **)realloc(*ID, (*numberOfRecords + 1) * sizeof(char *));
            *pozicia = (char **)realloc(*pozicia, (*numberOfRecords + 1) * sizeof(char *));
            *typ = (char **)realloc(*typ, (*numberOfRecords + 1) * sizeof(char *));
            *hodnota = (double *)realloc(*hodnota, (*numberOfRecords + 1) * sizeof(double));
            *cas = (char **)realloc(*cas, (*numberOfRecords + 1) * sizeof(char *));
            *datum = (int *)realloc(*datum, (*numberOfRecords + 1) * sizeof(int));

            (*numberOfRecords)++;
            (*ID)[*numberOfRecords - 1] = strdup(s);
            // printf("%d ID %s\n", *numberOfRecords, (*ID)[(*numberOfRecords) - 1]);

            if (fscanf(*Dataloger, "%s", s1) != EOF)
            {
                (*pozicia)[*numberOfRecords - 1] = strdup(s1);
                // printf("%d pozicia %s\n", *numberOfRecords, (*pozicia)[(*numberOfRecords) - 1]);

                if (fscanf(*Dataloger, "%s", s2) != EOF)
                {
                    (*typ)[*numberOfRecords - 1] = strdup(s2);
                    // printf("%d TYP %s\n", *numberOfRecords, (*typ)[(*numberOfRecords) - 1]);

                    if (fscanf(*Dataloger, "%lf", &d) != EOF)
                    {
                        (*hodnota)[*numberOfRecords - 1] = d;
                        // printf("%d hodnota %lf\n", *numberOfRecords, (*hodnota)[(*numberOfRecords) - 1]);

                        if (fscanf(*Dataloger, "%s", s3) != EOF)
                        {
                            (*cas)[*numberOfRecords - 1] = strdup(s3);
                            // printf("%d CAS %s\n", *numberOfRecords, (*cas)[(*numberOfRecords) - 1]);

                            if (fscanf(*Dataloger, "%d", &w) != EOF)
                            {
                                (*datum)[*numberOfRecords - 1] = w;
                                // printf("%d DAT %d\n", *numberOfRecords, (*datum)[(*numberOfRecords) - 1]);
                            }
                        }
                    }
                }
            }
        }
        else if (s[0] == '\n')
        {
            continue;
        }
        else
        {
            break;
        }
    }
    *kol_n = 1;
}

void checkMonthes(int kol_v, int kol_n, int *numberOfRecords, char ***ID, int **datum)
{
    if (kol_n == 0)
    {
        printf("Polia nie su vytvorene\n");
        return;
    }
    else if (kol_v == 0)
    {
        printf("Neotvoreny subor\n");
        return;
    }
    int y;
    scanf("%d", &y);
    FILE *ciachovanie = fopen("ciachovanie.txt", "r");

    while (1)
    {
        char c_ID[6];
        int c_datum;
        int mamAleboNemam = 0;
        if (fscanf(ciachovanie, "%s", c_ID) != EOF)
        {
            // printf("%s\n", c_ID);
            fscanf(ciachovanie, "%d", &c_datum);
            // printf("%d\n", c_datum);
            for (int i = 0; i < *numberOfRecords; i++)
            {
                // printf("prve %s\n", (*ID)[i]);
                // printf("druhe %s\n", c_ID);
                if (strcmp(c_ID, (*ID)[i]) == 0)
                {
                    // printf("Nájdené zhodné ID: %s\n", c_ID);
                    mamAleboNemam = 1;

                    int c_mesiac = 0, c_den = 0, c_rok = 0, mesiac = 0, den = 0, rok = 0;
                    c_mesiac = c_datum % 10000 / 100;
                    c_den = c_datum % 100;
                    c_rok = c_datum / 10000;
                    mesiac = (*datum)[i] % 10000 / 100;
                    den = (*datum)[i] % 100;
                    rok = (*datum)[i] / 10000;

                    // printf("c_datum %d %d %d\n", c_rok, c_mesiac, c_den);
                    // printf("datum %d %d %d\n", rok, mesiac, den);

                    int months1 = c_rok * 12 + c_mesiac;
                    int months2 = rok * 12 + mesiac;
                    int difference = abs(months1 - months2);

                    if (difference > y)
                    {
                        printf("ID. mer. modulu [%s] má %d mesiacov od ciachovania.\n", (*ID)[i], difference);
                    }
                }
            }
        }
        else if (c_ID[0] == '\n')
        {
            continue;
        }
        else
        {
            break;
        }
        if (mamAleboNemam == 0)
        {
            printf("ID. mer. modulu [%s] nie je ciachovany.\n", c_ID);
        }
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int *sortNajdeneArray(int *najdene, char **najdene_datumCas, int k, int *ans_k)
{
    int *ans = (int *)malloc(sizeof(int));
    for (int i = 0; i < k; i++)
    {
        int zap = -1;
        for (int j = 0; j < *ans_k; j++)
        {
            if (najdene_datumCas[ans[j]] > najdene_datumCas[najdene[i]])
            {
                zap = j;
            }
        }
        if (zap != -1)
        {
            int scet = zap;
            int zap1 = najdene[i];
            // printf("swap %d %d\n", zap1, ans[scet]);
            while (scet < *ans_k)
            {
                swap(&zap1, &ans[scet]);
                scet++;
            }
            ans = (int *)realloc(ans, (*ans_k + 1) * sizeof(int));
            (*ans_k)++;
            ans[*ans_k - 1] = zap1;
        }
        else
        {
            ans = (int *)realloc(ans, (*ans_k + 1) * sizeof(int));
            (*ans_k)++;
            ans[*ans_k - 1] = najdene[i];
        }
    }
    return ans;
}

void sortArray(int numberOfRecords, int kol_n, char **ID, char **typ, int *datum, char **cas, double *hodnota, char **pozicia)
{
    if (kol_n == 0)
    {
        printf("Polia nie su vytvorene\n");
        return;
    }
    FILE *vystup_s = fopen("vystup_S.txt", "w"); 

    if (vystup_s == NULL){
        printf("Pre dany vstup nie je vytvoreny txt subor.\n");
        return;
    }

    char s_id[6], s_typ[3];
    scanf("%s %s", s_id, s_typ);

    int *najdene = (int *)malloc(numberOfRecords * sizeof(int));
    char **najdene_datumCas = (char **)malloc(numberOfRecords * sizeof(char *));
    char **ALLnajdene_datumCas = (char **)malloc(numberOfRecords * sizeof(char *));
    int k = 0;

    for (int i = 0; i < numberOfRecords; i++)
    {

        if (strcmp(s_id, ID[i]) == 0 && strcmp(s_typ, typ[i]) == 0)
        {
            // printf("Najsel %s\n", ID[i]);
            najdene[k] = i;

            // Выделяем память и копируем строку с датой и временем
            char str[9];
            sprintf(str, "%d", datum[i]);
            najdene_datumCas[k] = (char *)malloc(strlen(str) + strlen(cas[i]) + 1);

            strcpy(najdene_datumCas[k], str);
            strcat(najdene_datumCas[k], cas[i]);

            k++;
        }
        char str[9];
        sprintf(str, "%d", datum[i]);
        ALLnajdene_datumCas[i] = (char *)malloc(strlen(str) + strlen(cas[i]) + 1);
        strcpy(ALLnajdene_datumCas[i], str);
        strcat(ALLnajdene_datumCas[i], cas[i]);
    }
    // for (int i = 0; i < numberOfRecords; i++)
    // {
    //     printf("%d %s\n", najdene[i], najdene_datumCas[i]);
    // }
    int ans_k = 0;
    int *ans = sortNajdeneArray(najdene, najdene_datumCas, k, &ans_k);
    char **poz1 = (char **)malloc(numberOfRecords * sizeof(char *));
    char **poz2 = (char **)malloc(numberOfRecords * sizeof(char *));

    for (int i = 0; i < numberOfRecords; i++)
    {
        poz1[i] = (char *)malloc(20);
        poz2[i] = (char *)malloc(20);
        int k1 = 0, k2 = 0;
        for (int j = 0; j < 15; j++)
        {
            if (j < 7)
            {
                poz1[i][k1] = pozicia[i][j];
                k1++;
            }
            if (k1 == 3)
            {
                poz1[i][k1] = '.';
                k1++;
            }
            if (j >= 7)
            {
                poz2[i][k2] = pozicia[i][j];
                k2++;
            }
            if (k2 == 3)
            {
                poz2[i][k2] = '.';
                k2++;
            }
        }
    }

    for (int i = 0; i < ans_k; i++)
    {
        fprintf(vystup_s, "%s %.5lf %s %s\n", ALLnajdene_datumCas[ans[i]], hodnota[ans[i]], poz1[ans[i]], poz2[ans[i]]);
    }
    printf("Pre dany vstup je vytvoreny txt subor.\n");

    for (int i = 0; i < k; i++)
    {
        free(najdene_datumCas[i]);
    }

    free(najdene_datumCas);
    free(najdene);
    free(ALLnajdene_datumCas);

    for (int i = 0; i < numberOfRecords; i++)
    {
        free(poz1[i]);
        free(poz2[i]);
    }
    free(poz1);
    free(poz2);

    fclose(vystup_s);
}



int main()
{

    FILE *Dataloger;
    int numberOfRecords = 0;
    int kol_v = 0, kol_n = 0;
    char **ID;
    char **pozicia;
    char **typ;
    double *hodnota;
    char **cas;
    int *datum;

    char command;

    while (command != '0')
    {
        scanf("%c", &command);

        if (command == 'v')
        {
            checkOpenFile(&Dataloger, &kol_v, kol_n, &numberOfRecords, &ID, &pozicia, &typ, &hodnota, &cas, &datum);
        }

        if (command == 'n')
        {
            createArrays(&Dataloger, &kol_n, &numberOfRecords, &ID, &pozicia, &typ, &hodnota, &cas, &datum);
        }
        if (command == 'c')
        {
            checkMonthes(kol_v, kol_n, &numberOfRecords, &ID, &datum);
        }
        if (command == 's')
        {
            sortArray(numberOfRecords, kol_n, ID, typ, datum, cas, hodnota, pozicia);
        }
    }
}