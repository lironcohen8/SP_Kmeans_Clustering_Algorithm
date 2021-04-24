#include <stdio.h>
#include <assert.h>
int k, max_iter, dimension, numOfVectors = 0, changes = 1;
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
    int i, newCentroidInd, clusterSize;
    int * cluster;
    clustersSizes = (int *)calloc(k, sizeof(int));

    for (i = 0; i < k; i++) { 
        clusters[i] = (int *)calloc(numOfVectors, sizeof(int));
    }
        
    for (i = 0; i < numOfVectors; i++) {
        newCentroidInd = closestCentroid(vectors[i]);
        cluster = clusters[newCentroidInd];
        clusterSize = clustersSizes[newCentroidInd];
        cluster[clusterSize] = i;
        clustersSizes[newCentroidInd]++;
    }
}

float * calcCentroidForCluster(int clusterInd) {
    int numOfVectorsInCluster, i, j;
    float * sumVector = (float *)calloc(dimension, sizeof(float));
    int * cluster;
    numOfVectorsInCluster = clustersSizes[clusterInd];
    cluster = clusters[clusterInd];
    
    for (i = 0; i < dimension; i++) {
        for (j = 0; j < numOfVectorsInCluster; j++) {
            sumVector[i] += (vectors[cluster[j]])[i];
        }
    }

    for (i = 0; i < dimension; i++) {
        sumVector[i] /= numOfVectorsInCluster;
        /*sumVector[i] = (((int)(10000*sumVector[i])) * 1.0)/10000;*/
    }
    return sumVector;
}

void updateCentroidValue() {
    int i, j;
    float * newValue;
    changes = 0;
    for (i = 0; i < k; i++) {
        newValue = calcCentroidForCluster(i);
        for (j = 0; j < dimension; j++) {
            if (newValue[j] != centroids[i][j]) {
                changes += 1;
            }    
            centroids[i][j] = newValue[j];
        }
    }
}

void printResult() {
    int i, j;
    for (i = 0; i < k; i++) {
        for (j = 0; j < dimension; j++) {
            printf("%.4f", centroids[i][j]);
            if (j < dimension - 1) {
                printf(",");
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int i, j, counter = 1;
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
    while ((counter<=max_iter) && (changes > 0)) {
        assignVectorToCluster();
        updateCentroidValue();
        counter += 1;
    }
    printResult();
    return 0;
}