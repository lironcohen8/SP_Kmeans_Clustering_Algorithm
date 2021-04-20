#include <stdio.h>
#include <assert.h>
void *calloc(size_t nitems, size_t size);
char *strtok(char * str, const char *delim);
double atof(const char * str);

int calcDimension(char buffer[]) {
    int i, dimension;
    char c;
    dimension = 0;
    i = 0;
    c = buffer[i];
    while (c != '\n') {
        if (c == ',') {
            dimension++;
        }
        c= buffer[++i];
    }
    buffer[i] = '\0';
    return dimension+1;
}

int main(int argc, char *argv[]) {
    int k, max_iter, dimension, numOfPoints = 0, i, j;
    char *input_path, buffer[1000], *pointStr;
    float *point;
    float **points;
    FILE *input_file;

    sscanf(argv[1], "%d", &k);
    max_iter = 200;
    if (argc == 4) {
        sscanf(argv[2], "%d", &max_iter);
        input_path = argv[3];
    }
    else {
        input_path = argv[2];
    }

    input_file = fopen(input_path,"r");
    printf("%d %d %s\n", k, max_iter, input_path);

    while (fgets(buffer,1000,input_file) != NULL) { 
        if (numOfPoints == 0) {
            dimension = calcDimension(buffer);
        }
        numOfPoints++;
    }
    fclose(input_file);

    pointStr = (char *)calloc(dimension, 100*sizeof(char));
    point = (float *)calloc(dimension, sizeof(float)); 
    points = (float **)calloc(numOfPoints, sizeof(point));
    
    input_file = fopen(input_path,"r");

    for (i = 0; i < numOfPoints; i++) {
        fgets(buffer,1000,input_file);
        pointStr = strtok(buffer, ",");
        j = 0;
        while (pointStr != NULL) {
            point[j] = atof(pointStr);
            pointStr = strtok(NULL, ",");
            j++;
        }
        points[i] = point;
    }
    return 0;
}