//
//  main.cpp
//  hw_3_prob_1_a
//
//  Created by Abinaya Manimaran on 3/11/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <time.h>
#include "DIP_MyHeaderFile.h"

using namespace std;

long double *** stackImages(long double *** image3DStacked, unsigned char *image1D, int row, int col, int stackNo) {
    long int temp_count = 0;
    for(int i=0; i < row; i++) {
        for(int j=0; j < col; j++) {
            image3DStacked[i][j][stackNo] = (long double) image1D[temp_count];
            temp_count = temp_count + 1;
        }
    }
    return image3DStacked;
}

void fileWriteEnergy(char* fileName, long double *dataToWrite, long int DATALEN) {
    FILE *file;
    file = fopen(fileName, "w");
    if (file != NULL)
    {
        for (int i = 0; i < DATALEN;  i++)
        {
            fprintf(file, "%d\t%Lf\n", i, dataToWrite[i]);
        }
        fclose(file);
        //cout << "File " << fileName << " written successfully !!!" << endl;
    }
    else
    {
        cout << "Cannot open file " << fileName << endl;
    }
}
class textureClassification {
    public:
    int ROW;
    int COL;
    int IMAGECOUNT;
    int FILTERCOUNT;
    int FILTERSIZE;
    int CLUSTERCOUNT;
    int ITERATIONCOUNT;
    long double *** image3DStacked;
    long double *** filtersStacked;
    long double *** imageFeatureStack;
    long double ** energyFeatureExtracted;
    long double ** kmeansCentroids;
    unsigned int * kmeansCluster;

    
    textureClassification(long double *** inpImage, long double *** inpFilters, int inpROW, int inpCOL, int inpIMAGECOUNT, int inpFILTERCOUNT, int inpFILTERSIZE, int inpCLUSTERCOUNT, int inpITERATIONCOUNT)
    {
        image3DStacked = inpImage;
        filtersStacked = inpFilters;
        
        ROW = inpROW;
        COL = inpCOL;
        IMAGECOUNT = inpIMAGECOUNT;
        FILTERCOUNT = inpFILTERCOUNT;
        FILTERSIZE = inpFILTERSIZE;
        CLUSTERCOUNT = inpCLUSTERCOUNT;
        ITERATIONCOUNT = inpITERATIONCOUNT;
        
        imageFeatureStack = allocMemory3DLongDouble(imageFeatureStack, ROW, COL, FILTERCOUNT*FILTERCOUNT);
        energyFeatureExtracted = allocMemory2DLongDouble(energyFeatureExtracted, IMAGECOUNT, FILTERCOUNT*FILTERCOUNT);
        kmeansCentroids = allocMemory2DLongDouble(kmeansCentroids, CLUSTERCOUNT, FILTERCOUNT*FILTERCOUNT);
        kmeansCluster = new unsigned int [IMAGECOUNT]();

    }
    
    void subtractMean() {
        for(int imageNo=0; imageNo < IMAGECOUNT; imageNo++) {
            // Calculate Mean
            long double tempAvg = 0;
            for (int i = 0; i < ROW; i ++){
                for (int j = 0; j < COL; j++) {
                    tempAvg = tempAvg + image3DStacked[i][j][imageNo];
                }
            }
            tempAvg = tempAvg / (ROW*COL);
            //cout << "Average " << imageNo << ' ' << tempAvg << endl;
            // Subtract Mean
            for (int i = 0; i < ROW; i ++){
                for (int j = 0; j < COL; j++) {
                   image3DStacked[i][j][imageNo] = image3DStacked[i][j][imageNo] - tempAvg;
                   //cout << "Sub " << image3DStacked[i][j][imageNo] << endl;
                }
            }
        }
    }
    
    void energyFeatureExtraction() {
        
        signed int startN = - floor(FILTERSIZE/2.0);
        signed int endN =  floor(FILTERSIZE/2.0);
        
        // Traverse through every emage
        for(int imageNo=0; imageNo < IMAGECOUNT; imageNo++) {
        //int imageNo = 0;
            // Traverse through ROW and COL of every image
            for (int i = 0; i < ROW; i ++){
                for (int j = 0; j < COL; j++) {
        //int i=0; int j=0;
                    long double * tempPixelArray = new long double [FILTERSIZE*FILTERSIZE]();
                    int tempCount = 0;
                    
                    // Get the 5*5 sub matrices and store it in 1D
                    for(signed int p = startN ; p <= endN ; p ++) {
                        for(signed int q = startN ; q <= endN ; q ++) {
                            signed int rowIndex = i + p;
                            signed int colIndex = j + q;
                            if(rowIndex < 0) {
                                rowIndex = 0;
                            }
                            if(colIndex < 0) {
                                colIndex = 0;
                            }
                            if(rowIndex > ROW-1) {
                                rowIndex = ROW-1;
                            }
                            if(colIndex > COL-1) {
                                colIndex = COL-1;
                            }
                            long double tempPixel = image3DStacked[rowIndex][colIndex][imageNo];
                            tempPixelArray[tempCount] = tempPixel;
                            //cout << "TempArr " << tempPixel << ' ' << tempPixelArray[tempCount] << endl;
                            tempCount++;
                        }
                    }
                    
                    // Convolute with every Filter (Total:9)
                    for(int maskNo = 0; maskNo < FILTERCOUNT*FILTERCOUNT; maskNo++) {
                        //cout << maskNo << "-----------" << endl;
                        int tempCount2 = 0;
                        long double tempSum = 0;
                        for(int l=0; l< FILTERSIZE; l++){
                            for(int m=0; m < FILTERSIZE; m++) {
                                tempSum = tempSum + (filtersStacked[l][m][maskNo] * tempPixelArray[tempCount2]);
                                //cout << filtersStacked[l][m][maskNo] << ' '<<  tempPixelArray[tempCount] << ' ' <<  tempSum << endl;
                                tempCount2++;
                            }
                        }
                        imageFeatureStack[i][j][maskNo] = tempSum;
                        //cout << "energy " << imageFeatureStack[i][j][maskNo] << endl;
                    }
                }
            }
            
            // Calculate Energy for 9 feature images
            for(int maskNo = 0; maskNo < FILTERCOUNT*FILTERCOUNT; maskNo++) {
                long double tempEnergySum = 0;
                
                for (int i = 0; i < ROW; i ++){
                    for (int j = 0; j < COL; j++) {
                        tempEnergySum = tempEnergySum + pow(abs(imageFeatureStack[i][j][maskNo]),2);
                    }
                }
                //cout << "sum " << tempEnergySum << endl;
                tempEnergySum = tempEnergySum / (ROW*COL);
                energyFeatureExtracted[imageNo][maskNo] = tempEnergySum;
                //cout << energyFeatureExtracted[imageNo][maskNo] << endl;
           }
                
        }
    }
    
    void initializeKmeansCentroidsbkup() {
        //srand(time(NULL));
        //Initialize first centroid as the first data point
        for(int j=0; j<FILTERCOUNT*FILTERCOUNT; j++) {
            kmeansCentroids[0][j] = energyFeatureExtracted[0][j];}
        
        // For other clusters
        for(int clusterNo=1; clusterNo < CLUSTERCOUNT; clusterNo++) {
            cout << "Cluster " << clusterNo << endl;
            long double * distArray = new long double [IMAGECOUNT]();
            long double sumDist = 0;
            int chosenIndex = 0;
            
            // Get distance
            for(int imageNo=0; imageNo < IMAGECOUNT; imageNo++) {
                long double * tempDistArray = new long double [clusterNo]();
                
                for(int prevCluster=0; prevCluster < clusterNo; prevCluster++) {
                    long double tempSum = 0;
                    for(int i=0; i< FILTERCOUNT*FILTERCOUNT; i++) {
                        long double tempValue = kmeansCentroids[prevCluster][i] - energyFeatureExtracted[imageNo][i];
                        tempSum = tempSum +  (tempValue*tempValue);
                    }
                    tempDistArray[prevCluster] = tempSum;
                    //cout << tempDistArray[prevCluster] << endl;
                }
                int minDist = tempDistArray[0];
                for(int i=1; i< clusterNo; i++) {
                    if(tempDistArray[i] < minDist) {
                        minDist = tempDistArray[i];
                    }
                }
                distArray[imageNo] = minDist;
                sumDist = sumDist + distArray[imageNo];
                //cout << distArray[imageNo] << endl;
            }
            
            // Divide distance by total sum distance - probability
            for(int imageNo=0; imageNo < IMAGECOUNT; imageNo++) {
                distArray[imageNo] = distArray[imageNo] / sumDist;}
            
            // Calculate cumulative probability
            for(int imageNo=1; imageNo < IMAGECOUNT; imageNo++) {
                distArray[imageNo] = distArray[imageNo] + distArray[imageNo-1]; }
            
            // Generate random number
            long double randomNumber = ((long double) rand()) / ((long double)RAND_MAX);
            cout << randomNumber << endl;
            // Get the feature index for next cluster centroid
            for(int imageNo=1; imageNo < IMAGECOUNT; imageNo++) {
                if( randomNumber < distArray[imageNo]) {
                    chosenIndex = imageNo;
                    cout << chosenIndex << endl;
                    break;
                }
            }
            
            // Assign data point as cluster
            for(int j=0; j<FILTERCOUNT*FILTERCOUNT; j++) {
                kmeansCentroids[clusterNo][j] = energyFeatureExtracted[chosenIndex][j];}
        }
        
        
        
        
    }
    void initializeKmeansCentroids(){
        // Initialize random numbers between 100 and 1000 of size 4*9
        //int randomStart =100;
        //int randomEnd = 1000;
        for(int i=0; i< CLUSTERCOUNT; i++) {
            for(int j=0; j<FILTERCOUNT*FILTERCOUNT; j++) {
                //kmeansCentroids[i][j] = rand()%((randomEnd - randomStart) + 1) + randomStart;
                //kmeansCentroids[i][j] = rand();
                if(i==0) {
                    kmeansCentroids[i][j] = energyFeatureExtracted[0][j];
                }
                else if(i==1) {
                    kmeansCentroids[i][j] = energyFeatureExtracted[1][j];
                }
                else if(i==2) {
                    kmeansCentroids[i][j] = energyFeatureExtracted[2][j];
                }
                else if(i==3) {
                    kmeansCentroids[i][j] = energyFeatureExtracted[6][j];
                }
                //cout << kmeansCentroids[i][j] << endl;
            }
        }
    }
    
    void kmeansClustering(){
        for(int iterationNO=0; iterationNO < ITERATIONCOUNT; iterationNO++) {
            cout << "Iteration " << iterationNO << endl;
            for(int imageNo=0; imageNo < IMAGECOUNT; imageNo++) {
                long double * tempDistance = new long double [CLUSTERCOUNT]();
                
                // Get Euclidean Distance from data point to all the cluster centroids
                for (int clusterNo=0; clusterNo < CLUSTERCOUNT; clusterNo++) {
                    long double tempSum = 0;
                    for (int i = 0; i < FILTERCOUNT*FILTERCOUNT; i ++){
                        tempSum = tempSum + pow((energyFeatureExtracted[imageNo][i] - kmeansCentroids[clusterNo][i]) , 2);
                    }
                    tempSum = sqrt(tempSum);
                    tempDistance[clusterNo] = tempSum;
                    //cout << tempDistance[clusterNo] << endl;
                }
                
                // Get Minimum Distance and assign that cluster
                long double minDist = tempDistance[0];
                int minDistCluster = 0;
                for(int i=1; i< CLUSTERCOUNT; i++) {
                    if( tempDistance[i] < minDist ) {
                        minDist = tempDistance[i];
                        minDistCluster = i;
                    }
                }
                kmeansCluster[imageNo] = minDistCluster;
            }
            
            
            //Update Centroids
            for(int clusterNo=0; clusterNo < CLUSTERCOUNT; clusterNo++) {
                
                int updateCount = 0;
                for(int imageNo=0; imageNo < IMAGECOUNT; imageNo++) {
                    if( kmeansCluster[imageNo] == clusterNo) {
                        if( updateCount == 0) {
                            for(int i=0; i < FILTERCOUNT*FILTERCOUNT; i++) {
                                kmeansCentroids[clusterNo][i] = energyFeatureExtracted[imageNo][i];
                                //cout << kmeansCentroids[clusterNo][i] << endl;
                            }
                        }
                        else {
                            for(int i=0; i < FILTERCOUNT*FILTERCOUNT; i++) {
                                kmeansCentroids[clusterNo][i] = kmeansCentroids[clusterNo][i] + energyFeatureExtracted[imageNo][i];
                                //cout << kmeansCentroids[clusterNo][i] << endl;
                            }
                        }
                        updateCount++;
                    }
                }
                
                for(int i=0; i < FILTERCOUNT*FILTERCOUNT; i++) {
                    if(updateCount > 0){
                        kmeansCentroids[clusterNo][i] = kmeansCentroids[clusterNo][i] / ((long double) (updateCount));
                    }
                    //cout << kmeansCentroids[clusterNo][i] << endl;
                }
            }
        }
    }
};

int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 17){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [ROW] [COL] [BYTESPERPIXEL] [input 12 image paths] [output energy feature file path]" << endl;
        return 0;
    }
    
    // Store the required arguments --------
    int ROW = atoi(argv[1]);
    int COL = atoi(argv[2]);
    int BYTESPERPIXEL = atoi(argv[3]);
    long int IMAGELEN = ROW*COL*BYTESPERPIXEL;
    int IMAGECOUNT = 12;
    
    cout << "Number of arguments passed: " << argc << endl;
    cout << "BYTESPERPIXEL: " << BYTESPERPIXEL << endl;
    cout << "ROW: " << ROW << endl;
    cout << "COL: " << COL << endl;
    cout << "File length: " << IMAGELEN << endl;
    cout << "Processing File: " << argv[4] << endl;
    cout << "-----------------------" << endl;
    
    // Declare required input and output datastructures ---------
    unsigned char *imageFromFile = new unsigned char [IMAGELEN]();

    long double *** inpImage3DStacked = NULL;
    inpImage3DStacked = allocMemory3DLongDouble(inpImage3DStacked, ROW, COL, IMAGECOUNT);
    
    // Stack all 12 images in one 3D array of size ROW*COL*IMAGECOUNT
    int tempImageCount = 0;
    for(int i=4; i < 16; i++) {
        fileRead(argv[i], imageFromFile, IMAGELEN);
        inpImage3DStacked = stackImages(inpImage3DStacked, imageFromFile, ROW, COL, tempImageCount);
        tempImageCount++;
    }
    
    // Get Laws Filter
    const int FILTERCOUNT = 3;
    const int FILTERSIZE = 5;
    long double * E5 = new long double [FILTERSIZE]{-1.0/6.0, -2.0/6.0, 0, 2.0/6.0, 1.0/6.0};
    long double * S5 = new long double [FILTERSIZE]{-1.0/4.0, 0, 2.0/4.0, 0, -1.0/4.0};
    long double * W5 = new long double [FILTERSIZE]{-1.0/6.0, 2.0/6.0, 0, -2.0/6.0, 1.0/6.0};
    
    long double ** lawsFilter = NULL;
    lawsFilter = new long double *[3]();
    lawsFilter[0] = E5;
    lawsFilter[1] = S5;
    lawsFilter[2] = W5;
    
    long double *** lawsFilterCombn = NULL;
    lawsFilterCombn = allocMemory3DLongDouble(lawsFilterCombn, FILTERSIZE, FILTERSIZE, FILTERSIZE*FILTERSIZE);
    
    int tempCount = 0;
    for(int i = 0; i < FILTERCOUNT; i++) {
        for(int j= 0; j < FILTERCOUNT; j++) {
            for (int l=0; l < FILTERSIZE; l++) {
                for(int m=0; m < FILTERSIZE; m++) {
                    lawsFilterCombn[l][m][tempCount] = lawsFilter[i][l] * lawsFilter[j][m];
                    //cout << lawsFilterCombn[l][m][tempCount] << endl;
                }
            }
            tempCount++;
        }
    }

    // Declare class object
    int CLUSTERCOUNT = 4;
    textureClassification classifyTextures = textureClassification(inpImage3DStacked, lawsFilterCombn, ROW, COL, IMAGECOUNT, FILTERCOUNT, FILTERSIZE, CLUSTERCOUNT, 20);
    classifyTextures.subtractMean();
    cout << "--- Subtraction of Global Mean done ---" << endl;
    classifyTextures.energyFeatureExtraction();
    cout << "--- Energy Features Extracted ---" << endl;
    classifyTextures.initializeKmeansCentroids();
    cout << "Initialization of Centroids for K-Means done ---" << endl;
    cout << "K-Means Clustering begins ---" << endl;
    classifyTextures.kmeansClustering();
    cout << "K-Means Clustering ends ---" << endl;
    
    // Print output
    for(int i=0; i<IMAGECOUNT; i++) {
        cout << "Figure " << i+1 << " belongs to Cluster " << classifyTextures.kmeansCluster[i] << endl;
    }

    // Write energy feature values to a file for inspection
    long double * energyFeatures1D = new long double [IMAGECOUNT*FILTERCOUNT*FILTERCOUNT]();
    int featureCount = 0;
    for(int i=0; i<IMAGECOUNT; i++) {
        for(int j=0; j<FILTERCOUNT*FILTERCOUNT; j++) {
            energyFeatures1D[featureCount] =  classifyTextures.energyFeatureExtracted[i][j];
            //cout <<energyFeatures1D[featureCount] << endl;
            featureCount ++;
        }
    }
    fileWriteEnergy(argv[16], energyFeatures1D, IMAGECOUNT*FILTERCOUNT*FILTERCOUNT);
    
    // Delete all allocated memories
    freeMemory3DLongDouble(inpImage3DStacked, ROW, COL, 12);
    freeMemory3DLongDouble(lawsFilterCombn, FILTERSIZE, FILTERSIZE, FILTERCOUNT*FILTERCOUNT);
    delete [] E5;
    delete [] S5;
    delete [] W5;
    delete [] imageFromFile;
    delete[] energyFeatures1D;
}
