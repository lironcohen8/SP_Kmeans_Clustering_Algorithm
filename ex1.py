import sys

global didCentroidsChange
didCentroidsChange = True

global vectors 
vectors = []

global clusters 
clusters = {}

global centroids 
centroids = []

def distance(vector1, vector2):
    dis = 0
    for i in range(len(vector1)):
        dis += (vector1[i]-vector2[i])**2
    
    return dis
    

def closestCentroid(vector):
    minDis = distance(vector, centroids[0])
    minCenInd = 0
    
    for i in range(len(centroids)):
        dis = distance(vector, centroids[i])
        if dis < minDis:
            minDis = dis
            minCenInd = i
            
    return minCenInd
 

def assignVectorToCluster():
    for i in range(len(clusters)):
        clusters[i] = []
        
    for vector in vectors:
        newCentroidInd = closestCentroid(vector)
        clusters[newCentroidInd].append(vector)


def calcCentroidForCluster(cluster):
    numOfVectors = len(cluster)
    sumVector = [sum(elts) for elts in zip(*cluster)]
    for i in range(len(sumVector)):
        sumVector[i] = float("{:.4f}".format(sumVector[i]/numOfVectors))
        
    return sumVector


def updateCentroidValue():
    changes = 0
    
    for i in range(len(clusters)):
        newValue = calcCentroidForCluster(clusters[i])

        if newValue != centroids[i]:
            changes += 1
            
        centroids[i] = newValue
    
    return changes!=0
        


def readFile(filePath):
    with open(filePath, "r") as f:
        lines = f.readlines()
        for line in lines:
            line = line[:-1]
            vector = line.split(",")
            for i in range(len(vector)):
                vector[i] = float(vector[i])
            vectors.append(vector)


def initclusters(k):
    for i in range(k):
        centroids.append(vectors[i])
        clusters[i] = []    


def printResult():
    for centroid in centroids:
        print(centroid)

        

def main():
    numOfArgs = len(sys.argv)
    
    k = int(sys.argv[1])
    if numOfArgs == 4:
        max_iter = int(sys.argv[2])
        filePath = sys.argv[3]
    elif numOfArgs == 3:
        max_iter = 200
        filePath = sys.argv[2]
    else:
        """error"""
        pass 
        
    print(k,max_iter,filePath)
    
    readFile(filePath)
    initclusters(k)

    counter = 1
    didCentroidsChange = True
    
    while (counter<=max_iter) and (didCentroidsChange):
        assignVectorToCluster()
        didCentroidsChange = updateCentroidValue()
        counter += 1
        
    printResult()

if __name__ == "__main__":
    main()
    
