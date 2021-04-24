#include <stdio.h>
#include <assert.h>
int k, max_iter, dimension, numOfVectors = 0;
float **vectors, **centroids;
int **clusters, *clustersSizes;
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
        c = buffer[++i];
    }
    buffer[i] = '\0';
    return dimension+1;
}

void initCentroids() {
    int i,j;
    centroids = (float **)calloc(k, dimension*sizeof(float));
    for (i = 0; i < k; i++) {
        centroids[i] = (float *)calloc(dimension, sizeof(float)); 
        for (j = 0; j < dimension; j++) {
            centroids[i][j] = vectors[i][j];
        }
    }
}

float distance(float *vector1, float *vector2) {
    float dis = 0;
    int i;
    for (i = 0; i < dimension; i++) {
        dis += (vector1[i]-vector2[i])*(vector1[i]-vector2[i]);
    }
    return dis;
}

int closestCentroid(float *vector) {
    float minDis, dis;
    int minCenInd,i;
    minDis = distance(vector, centroids[0]);
    minCenInd = 0;
    
    for (i = 0; i < k; i++) {
        dis = distance(vector, centroids[i]);
        if (dis < minDis) {
            minDis = dis;
            minCenInd = i;
        }
    }   
    return minCenInd;
}

void assignVectorToCluster() {
    int i, newCentroidInd;
    clustersSizes = (int *)calloc(k, sizeof(int));
    for (i = 0; i < k; i++) {
        clusters[i] = (int *)calloc(numOfVectors, sizeof(int));
    }
        
    for (i = 0; i < numOfVectors; i++) {
        newCentroidInd = closestCentroid(vectors[i]);
        clusters[newCentroidInd][clustersSizes[newCentroidInd]++] = i;
    }
}

void calcCentroidForCluster(cluster):
    numOfVectors = len(cluster)
    sumVector = [sum(elts) for elts in zip(*cluster)]
    for i in range(len(sumVector)):
        sumVector[i] = float("{:.4f}".format(sumVector[i]/numOfVectors))
        
    return sumVector

int main(int argc, char *argv[]) {
    int i, j;
    char *input_path, buffer[1000], *vectorStr;
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
        if (numOfVectors == 0) {
            dimension = calcDimension(buffer);
        }
        numOfVectors++;
    }
    fclose(input_file);

    vectorStr = (char *)calloc(dimension, 100*sizeof(char));
    vectors = (float **)calloc(numOfVectors, dimension*sizeof(float));
    
    input_file = fopen(input_path,"r");

    for (i = 0; i < numOfVectors; i++) {
        fgets(buffer,1000,input_file);
        vectorStr = strtok(buffer, ",");
        j = 0;
        vectors[i] = (float *)calloc(dimension, sizeof(float)); 
        while (vectorStr != NULL) {
            vectors[i][j] = atof(vectorStr);
            vectorStr = strtok(NULL, ",");
            j++;
        }
    }
    initCentroids();
    clusters = (int **)calloc(k, numOfVectors*sizeof(int));
    return 0;
}