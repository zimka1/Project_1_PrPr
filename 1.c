//127318_2023_CV_4_9
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 1000

void checkOpenFile(FILE **Dataloger, int kol_v, int kol_n, int *numberOfRecords, char ***ID, char ***pozicia, char ***typ, double **hodnota, char ***cas, int **datum){

    if (kol_v == 0) {
        *Dataloger = fopen("dataloger.txt", "r");
    }

    if (*Dataloger == NULL) {
        printf("Neotvoreny subor\n");
        return;
    }

    if (kol_n == 1){
       
        for (int i = 0; i < *numberOfRecords; i++){
            printf("ID. mer. modulu: %s\n", (*ID)[i]);
            printf("poziciaícia modulu: %s\n", (*pozicia)[i]);
            printf("Typ mer. veliciny: %s\n", (*typ)[i]);
            printf("hodnotanota: %lf\n", (*hodnota)[i]);
            printf("Cas merania: %s\n", (*cas)[i]);
            printf("Datum merania: %d\n", (*datum)[i]);
            printf("\n");
        }
    }
    
}

void freeArrays(char **ID, char **pozicia, char **typ, char **cas, double *hodnota, int *datum, int numberOfRecords) {
    for (int i = 0; i < numberOfRecords; i++) {
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

void createArrays(FILE **Dataloger, int kol_n, int *numberOfRecords, char ***ID, char ***pozicia, char ***typ, double **hodnota, char ***cas, int **datum) {
    
    if (kol_n == 1){
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
    
    while(1){

        char s[6], s1[15], s2[3], s3[5];
        
        if (fscanf(*Dataloger, "%s", s) != EOF && s[0] != '\n') {
            
            *ID = (char **)realloc(*ID, (*numberOfRecords + 1) * sizeof(char *));
            *pozicia = (char **)realloc(*pozicia, (*numberOfRecords + 1) * sizeof(char *)); 
            *typ = (char **)realloc(*typ, (*numberOfRecords + 1) * sizeof(char *));
            *hodnota = (double *)realloc(*hodnota, (*numberOfRecords + 1) * sizeof(double));
            *cas = (char **)realloc(*cas, (*numberOfRecords + 1) * sizeof(char *));
            *datum = (int *)realloc(*datum, (*numberOfRecords + 1) * sizeof(int));

            (*numberOfRecords)++;
            (*ID)[*numberOfRecords - 1] = strdup(s);
            // printf("%d ID %s\n", *numberOfRecords, (*ID)[(*numberOfRecords) - 1]);

            if (fscanf(*Dataloger, "%s", s1) != EOF){
                (*pozicia)[*numberOfRecords - 1] = strdup(s1);
                // printf("%d pozicia %s\n", *numberOfRecords, (*pozicia)[(*numberOfRecords) - 1]);
                
                if (fscanf(*Dataloger, "%s", s2) != EOF){
                    (*typ)[*numberOfRecords - 1] = strdup(s2);
                    // printf("%d TYP %s\n", *numberOfRecords, (*typ)[(*numberOfRecords) - 1]);

                    if (fscanf(*Dataloger, "%lf", &d) != EOF){
                        (*hodnota)[*numberOfRecords - 1] = d;
                        // printf("%d hodnota %lf\n", *numberOfRecords, (*hodnota)[(*numberOfRecords) - 1]);
                        
                        if (fscanf(*Dataloger, "%s", s3) != EOF){
                            (*cas)[*numberOfRecords - 1] = strdup(s3);
                            // printf("%d CAS %s\n", *numberOfRecords, (*cas)[(*numberOfRecords) - 1]);
                            
                            if (fscanf(*Dataloger, "%d", &w) != EOF){
                                (*datum)[*numberOfRecords - 1] = w;
                                // printf("%d DAT %d\n", *numberOfRecords, (*datum)[(*numberOfRecords) - 1]);
                            }
                        }
                    }
                }
            }
        }
        else if (s[0] == '\n'){
            continue;
        } else {
            break;
        }
    }
}

void checkMonthes(int y, int *numberOfRecords, char ***ID, int **datum) {
    FILE * ciachovanie = fopen("ciachovanie.txt", "r");
    while (1){
        char c_ID[6];
        int c_datum;
        int mamAleboNemam = 0;
        if (fscanf(ciachovanie, "%s", c_ID) != EOF){
            // printf("%s\n", c_ID);
            fscanf(ciachovanie, "%d", &c_datum);
            // printf("%d\n", c_datum);
            for (int i = 0; i < *numberOfRecords; i++){
                // printf("prve %s\n", (*ID)[i]);
                // printf("druhe %s\n", c_ID);
                if (strcmp(c_ID, (*ID)[i]) == 0) {
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
                    
                    if (difference > y){
                        printf("ID. mer. modulu [%s] má %d mesiacov od ciachovania.\n", (*ID)[i], difference);
                    }
                }

            }
        }
        else if (c_ID[0] == '\n'){
            continue;
        }
        else{
            break;
        }
        if (mamAleboNemam == 0){
            printf("ID. mer. modulu [%s] nie je ciachovany.\n", c_ID);
        }
        
    }

}


int main() {



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

    while (command != '0'){
        scanf("%c", &command);
        
        if ( command == 'v'){
            checkOpenFile(&Dataloger, kol_v, kol_n, &numberOfRecords, &ID, &pozicia, &typ, &hodnota, &cas, &datum);
            kol_v = 1;
        }

        if (command == 'n'){
            if (Dataloger == NULL){
                printf("Neotvoreny subor\n");
            } else {
                createArrays(&Dataloger, kol_n, &numberOfRecords, &ID, &pozicia, &typ, &hodnota, &cas, &datum);
                kol_n = 1;
            }
        }
        if (command == 'c'){
            if (kol_n == 0){
                printf("Polia nie su vytvorene\n");
            } else if (Dataloger == NULL){
                printf("Neotvoreny subor\n");
            } else {
                int y;
                scanf("%d", &y);
                checkMonthes(y, &numberOfRecords, &ID, &datum);
            }
        }

    }
    
    

}
