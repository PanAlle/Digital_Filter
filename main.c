#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define FILTER_ORDER 2

typedef struct Filter{
    float a;
    float b;
}Filter;

typedef struct Signal{
    float val;
    float time;
    float filt_out;
}signal;



float ButterFilter(Filter *filter, signal *signal) {
    float output = 0;
    for (int i = 0; i < FILTER_ORDER+1; ++i) {
        //printf("Valore del segnale%f\n", signal[i].val);
        output = output + (signal[i].val * filter[i].b) - (signal[i].filt_out * filter[i].a);
    }
    return output;
}

void ReadFilter(Filter *filter, char* FilterFileName){
    FILE *fp;
    fp = fopen( FilterFileName, "r");
    if (fp == NULL) {
        printf("Can't find the file");
        return;
    }
    printf("File trovato\n");
    int i = 0;
    char *buf = (char *) malloc(256);
    while (fgets(buf, 256, fp)){
        sscanf(buf, "%f,%f", &filter[i].a, &filter[i].b);
        printf("Valori di a e b per il filtro %f, %f\n", filter[i].a, filter[i].b);
        i++;
    }
    fclose(fp);
}
/*
void WriteSignal (float filtered_sig, float timerstamp){
    FILE *fw;
    fw = fopen( "C:\\Users\\utente\\CLionProjects\\Digital_Filter\\csv_output.csv", "w");
    if (fw == NULL) {
        printf("Can't find the file to write");
        return;
    }
    printf("File trovato\n");

    fprintf(fw, "%f,%f\n", filtered_sig, timerstamp );
    fclose(fw);
}*/


void ReadSignal (char *ReadFileName, signal* signal, Filter *filter){

    FILE *fw;
    fw = fopen( "C:\\Users\\utente\\CLionProjects\\Digital_Filter\\csv_output.csv", "w");
    if (fw == NULL) {
        printf("Can't find the file to write");
        return;
    }
    printf("File trovato\n");


    FILE *fp;
    fp = fopen( ReadFileName, "r");
    if (fp == NULL) {
        printf("Can't find the file");
        return;
    }
    printf("File trovato\n");

    for (int j = 0; j < FILTER_ORDER + 1; ++j) {
        signal[j].val = 0;
        signal[j].time = 0;
        signal[j].filt_out = 0;
    }


    char *buf = (char *) malloc(256);
    while (fgets(buf, 256, fp)){
        sscanf(buf, "%f,%f", &signal[0].val, &signal[0].time);
        //printf("original value read %f\n",signal[0].val);

    //APPLY FILTER;
    signal[0].filt_out = ButterFilter(filter, signal);
    //printf("current output value %f\n", y_filt);
    fprintf(fw, "%f,%f\n", signal[0].filt_out, signal[0].time);
    //WRITE OUTPUT TO FILE

    //ITERATE

    for (int i = FILTER_ORDER - 1; i >= 0;  i--) {
        signal[i+1].val = signal[i].val;
        signal[i+1].time = signal[i].time;
        signal[i+1].filt_out = signal[i].filt_out;
    }
        signal[0].val = 0;
        signal[0].time = 0;
        signal[0].filt_out = 0;

        //printf("valore finale è y:%f, x:%f\n", signal[FILTER_ORDER-1].val, signal[FILTER_ORDER-1].time);
    }
    fclose(fp);
    fclose(fw);
}




int main() {

    char *ReadFileName = "C:\\Users\\utente\\CLionProjects\\Digital_Filter\\csv_prova.csv";
    char *FilterFileName = "C:\\Users\\utente\\CLionProjects\\Digital_Filter\\butter_filter.csv";
    //ButterFilter(filter);
    Filter filter[FILTER_ORDER + 1];
    signal signal[FILTER_ORDER + 1];
    ReadFilter(filter, FilterFileName);
    ReadSignal(ReadFileName, signal, filter);
    return 0;
}
