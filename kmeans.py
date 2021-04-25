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
    '''Claculates the distance between two vectors'''
    dis = 0
    for i in range(len(vector1)): #Runs for each dimension
        dis += (vector1[i]-vector2[i])**2 
    
    return dis
    

def closestCentroid(vector):
    '''Finds the closest centroid to a vector by the distance function'''
    minDis = distance(vector, centroids[0]) #Initiate the minimum distance to be the distance from the first centroid
    minCenInd = 0 #Initiate the closest centroid to be the first one
    
    for i in range(len(centroids)): #For each centroid (there are K)
        dis = distance(vector, centroids[i])
        if dis < minDis:
            minDis = dis
            minCenInd = i
            
    return minCenInd
 

def assignVectorToCluster():
    '''Finds the closest centroid for each vector and adds
    the vector to the centroids cluster'''
    for i in range(len(clusters)): #Clearing all clusters (we do not want to remmember what was here)
        clusters[i] = []
        
    for vector in vectors:
        newCentroidInd = closestCentroid(vector) #Finds the closest centroid
        clusters[newCentroidInd].append(vector) #Adds the vector to the appropriate cluster 


def calcCentroidForCluster(cluster):
    '''Calculates the centroid for a given cluster'''
    numOfVectors = len(cluster) #Checks how many vectors are in the cluster
    sumVector = [sum(elts) for elts in zip(*cluster)] #Sums all the vectors (seperated for each dimension)
    for i in range(len(sumVector)):
        sumVector[i] = float(sumVector[i]/numOfVectors) #Replace the sum with the average
    return sumVector


def updateCentroidValue():
    '''Updates the centroid value for each cluster and checks if 
    it is different then what we had before'''
    changes = 0
    
    for i in range(len(clusters)):
        newValue = calcCentroidForCluster(clusters[i])

        if newValue != centroids[i]: #If the centroid changed
            changes += 1
            
        centroids[i] = newValue
    
    return changes!=0
        


def readFile():
    '''Reading the input file and put the data into the 'vectors' list'''
    for line in sys.stdin:
        stripped = line.strip()
        if not stripped: 
            break
        vector = line.split(",")
        for i in range(len(vector)):
            vector[i] = float(vector[i])
        vectors.append(vector)


def initclusters(k):
    '''Initialize the clusters and their centroids from the first K vectors'''
    for i in range(k):
        centroids.append(vectors[i])
        clusters[i] = []    


def printResult():
    '''Prints the centroids'''
    for centroid in centroids:
        for i in range(len(centroid)):
            centroid[i] = "{:.4f}".format(centroid[i]) #Format the floats precision to 4 digits 

    for centroid in centroids:
        print(','.join(map(str,centroid))) #Prints the floats as strings


def main():
    numOfArgs = len(sys.argv)
    k = int(sys.argv[1])
    if numOfArgs == 3:
        max_iter = int(sys.argv[2])
    elif numOfArgs == 2:
        max_iter = 200
    else:
        """error"""
        pass 
    
    readFile()
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
    
