#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//===================================
/*The idea behind it is that, for a second order filter to work, we just need to know the output of
the two previous values, both the filtered and unfiltered one and the current one, but just the unfiltered (the filtered one is the output of our
 computation). Once the filter order is
defined, then with FILTER_ORDER + 1 sample we can compute the current filtered output*/
//===================================


#define FILTER_ORDER 2
//store filter coefficient
typedef struct Filter {
    float a;
    float b;
} Filter;

typedef struct Signal {
    //store original value
    float val;
    //store timestamp
    float time;
    //store filtered output
    float filt_out;
} signal;


//Return a flot, correspondent to the filtered signal
float ButterFilter(Filter *filter, signal *signal) {
    float output = 0;
    for (int i = 0; i < FILTER_ORDER + 1; ++i) {
        //general filter formulation
        output = output + (signal[i].val * filter[i].b) - (signal[i].filt_out * filter[i].a);
    }
    return output;
}

//read the filter coefficient from a file and insert them in the Filter struct, where the coefficient are stored
void ReadFilter(Filter *filter, char *FilterFileName) {
    FILE *fp;
    fp = fopen(FilterFileName, "r");
    if (fp == NULL) {
        printf("Can't find the file");
        return;
    }
    printf("File trovato\n");
    int i = 0;
    char *buf = (char *) malloc(256);
    while (fgets(buf, 256, fp)) {
        sscanf(buf, "%f,%f", &filter[i].a, &filter[i].b);
        printf("Valori di a e b per il filtro %f, %f\n", filter[i].a, filter[i].b);
        i++;
    }
    fclose(fp);
}


//Part that read the input singal, and apply the filter to it
void ReadSignal(char *ReadFileName, signal *signal, Filter *filter) {

    FILE *fw;
    fw = fopen("C:\\Users\\utente\\CLionProjects\\Digital_Filter\\csv_output.csv", "w");
    if (fw == NULL) {
        printf("Can't find the file to write");
        return;
    }
    printf("File trovato\n");


    FILE *fp;
    fp = fopen(ReadFileName, "r");
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
    while (fgets(buf, 256, fp)) {
        sscanf(buf, "%f,%f", &signal[0].val, &signal[0].time);
        //printf("original value read %f\n",signal[0].val);

        //Apply the filter
        signal[0].filt_out = ButterFilter(filter, signal);
        //Print to a file the filtered output and the corresponding timestamp
        fprintf(fw, "%f,%f\n", signal[0].filt_out, signal[0].time);



        //The input signal is shifted to the right to make space for a new sample
        for (int i = FILTER_ORDER - 1; i >= 0; i--) {
            signal[i + 1].val = signal[i].val;
            signal[i + 1].time = signal[i].time;
            signal[i + 1].filt_out = signal[i].filt_out;
        }
        //Set the first value to zero, since every value is shifted to the right, then the first value can be any number
        signal[0].val = 0;
        signal[0].time = 0;
        signal[0].filt_out = 0;
    }
    //Close read and write file
    fclose(fp);
    fclose(fw);
}


int main() {

    char *ReadFileName = "C:\\Users\\utente\\CLionProjects\\Digital_Filter\\csv_prova.csv";
    char *FilterFileName = "C:\\Users\\utente\\CLionProjects\\Digital_Filter\\butter_filter.csv";
    Filter filter[FILTER_ORDER + 1];
    signal signal[FILTER_ORDER + 1];
    ReadFilter(filter, FilterFileName);
    ReadSignal(ReadFileName, signal, filter);
    return 0;
}
