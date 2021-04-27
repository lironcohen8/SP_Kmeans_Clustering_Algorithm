#include <stdio.h>
#include <assert.h>
int k, max_iter, dimension, numOfVectors = 0, changes = 1;
float rawK, rawMaxIter;
double **vectors, **centroids;
int **clusters, *clustersSizes;
void *calloc(size_t nitems, size_t size);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
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

void readFile() {
    int j;
    char *vectorStr, buffer[1000];
    double **tmp;
    vectorStr = (char *)calloc(dimension, 100*sizeof(char));
    assert(vectorStr != NULL);
    vectors = (double **)malloc(1 * sizeof(*vectors));
    assert(vectors != NULL);
    fgets(buffer,1000,stdin);
    dimension = calcDimension(buffer);
    do {
        tmp = realloc(vectors, (numOfVectors + 1) * sizeof(*vectors));
        assert(tmp != NULL);
        vectors = tmp;
        vectorStr = strtok(buffer, ",");
        j = 0;
        vectors[numOfVectors] = (double *)calloc(dimension, sizeof(double)); 
        assert(vectors[numOfVectors] != NULL);
        while (vectorStr != NULL) {
            vectors[numOfVectors][j] = atof(vectorStr);
            vectorStr = strtok(NULL, ",");
            j++;
        }
        numOfVectors++;
    }
    while (fgets(buffer,1000,stdin) != NULL);
}

void initCentroids() {
    int i,j;
    centroids = (double **)calloc(k, dimension*sizeof(double));
    assert(centroids != NULL);
    assert(k < numOfVectors);
    for (i = 0; i < k; i++) {
        centroids[i] = (double *)calloc(dimension, sizeof(double)); 
        assert(centroids[i] != NULL);
        for (j = 0; j < dimension; j++) {
            centroids[i][j] = vectors[i][j];
        }
    }
}

double distance(double *vector1, double *vector2) {
    double dis = 0;
    int i;
    for (i = 0; i < dimension; i++) {
        dis += (vector1[i]-vector2[i])*(vector1[i]-vector2[i]);
    }
    return dis;
}

int closestCentroid(double *vector) {
    double minDis, dis;
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
    assert(clustersSizes != NULL);

    for (i = 0; i < k; i++) { 
        clusters[i] = (int *)calloc(numOfVectors, sizeof(int));
        assert(clusters[i] != NULL);
    }
        
    for (i = 0; i < numOfVectors; i++) {
        newCentroidInd = closestCentroid(vectors[i]);
        cluster = clusters[newCentroidInd];
        clusterSize = clustersSizes[newCentroidInd];
        cluster[clusterSize] = i;
        clustersSizes[newCentroidInd]++;
    }
}

double * calcCentroidForCluster(int clusterInd) {
    int numOfVectorsInCluster, i, j;
    double * sumVector = (double *)calloc(dimension, sizeof(double));
    assert(sumVector != NULL);
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
    }
    return sumVector;
}

void updateCentroidValue() {
    int i, j;
    double * newValue;
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
    int counter = 1;
    assert(argc == 3 || argc == 2);

    assert(sscanf(argv[1], "%f", &rawK) == 1);
    k = (int)rawK;
    assert(rawK - k == 0 && k > 0);

    max_iter = 200;
    if (argc == 3) {
        assert(sscanf(argv[2], "%f", &rawMaxIter) == 1);
        max_iter = (int)rawMaxIter;
        assert(rawMaxIter - max_iter == 0 && max_iter > 0);
    }
    
    readFile();
    initCentroids();
    
    clusters = (int **)calloc(k, numOfVectors*sizeof(int));
    assert(clusters != NULL);
    while ((counter<=max_iter) && (changes > 0)) {
        assignVectorToCluster();
        updateCentroidValue();
        counter += 1;
    }

    printResult();
    return 0;
}