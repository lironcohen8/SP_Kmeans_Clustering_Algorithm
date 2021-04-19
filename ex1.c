#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    int k = argv[0];
    int max_iter = 200;
    char *input_file_name = argv[2];
    if (argc == 3) {
        max_iter = argv[1];
    }

    FILE *input_file = fopen(input_file_name,'rb');
    char buffer[1000];
    char *point;
    char ch;
    int d;
    while (fgets(buffer,1000,input_file) != NULL) {   
        for (int i = 0; i < 1000; i++) {
            if (buffer[i] == ',') {
                d++;
            }
        }
        float vector[d+1];
        
        for (int i = 0; i < d+1; i++) {
            point = strtok(buffer, ',');
            vector[i] = atof(point);
        }
    }

}