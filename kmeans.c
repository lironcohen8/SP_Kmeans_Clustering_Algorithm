#include <stdio.h>
#include <assert.h>
void *calloc(size_t nitems, size_t size);
char *strtok(char * str, const char *delim);
double atof(const char * str);

int main(int argc, char *argv[]) {
    int k, max_iter, d, N, i;
    char *input_path, buffer[1000], *point, ch;
    float *vector;
    FILE *input_file;

    sscanf(argv[0], "%d", &k);
    max_iter = 200;
    if (argc == 3) {
        sscanf(argv[1], "%d", &max_iter);
        input_path = argv[2];
    }
    else {
        input_path = argv[1];
    }

    input_file = fopen(input_path,"r");
    
    while (fgets(buffer,1000,input_file) != NULL) {   
        N++;
    }
    while (fgets(buffer,1000,input_file) != NULL) {   
        for (i = 0; i < 1000; i++) {
            if (buffer[i] == ',') {
                d++;
            }
        }
        vector = (float *)calloc(d, sizeof(float));
        
        for (i = 0; i < d+1; i++) {
            point = strtok(buffer, ",");
            vector[i] = atof(point);
        }
    }
return 0;
}