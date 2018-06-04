//
//  main.cpp
//  hw_3_prob_1_c
//
//  Created by Abinaya Manimaran on 3/19/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <time.h>
#include "DIP_MyHeaderFile.h"
#include <fstream>
using namespace std;

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

void fileReadEnergy(char *fileName, long double *dataFromFile, long int DATALEN ) {
    fstream file;
    file.open(fileName,ios::in);
    long double x;
    for(int i=0; i< DATALEN;i++){
        file>>x;
        dataFromFile[i] = x;
        //cout<<x<< ' ' << dataFromFile[i] << '\n';
    }
}


class textureSegmentation {
public:
    int ROW;
    int COL;
    int FILTERCOUNT;
    int FILTERSIZE;
    int CLUSTERCOUNT;
    long double ** image2D;
    long double *** filtersStacked;
    long double *** imageFeatureStack;
    long double ** energyFeatureExtracted;
    long double ** kmeansCentroids;
    unsigned int * kmeansCluster;
    unsigned char ** image2DOutput;
    int ROWFEATURES;
    int COLFEATURES;
    
    
    textureSegmentation(long double ** inpImage, long double *** inpFilters, int inpROW, int inpCOL, int inpFILTERCOUNT, int inpFILTERSIZE, int inpCLUSTERCOUNT, int inpROWFEATURES, int inpCOLFEATURES)
    {
        image2D = inpImage;
        filtersStacked = inpFilters;
        
        ROW = inpROW;
        COL = inpCOL;
        FILTERCOUNT = inpFILTERCOUNT;
        FILTERSIZE = inpFILTERSIZE;
        CLUSTERCOUNT = inpCLUSTERCOUNT;
        ROWFEATURES = inpROWFEATURES;
        COLFEATURES = inpCOLFEATURES;
        
        imageFeatureStack = allocMemory3DLongDouble(imageFeatureStack, ROW, COL, FILTERCOUNT*FILTERCOUNT);
        energyFeatureExtracted = allocMemory2DLongDouble(energyFeatureExtracted, ROW*COL, FILTERCOUNT*FILTERCOUNT);
        kmeansCentroids = allocMemory2DLongDouble(kmeansCentroids, CLUSTERCOUNT, COLFEATURES);
        kmeansCluster = new unsigned int [ROW*COL]();
        image2DOutput = allocMemory2D(image2DOutput, ROW, COL);
        
    }
    
    void subtractLocalMean(int SUBTRACTFILTERSIZE) {
        signed int startN = - floor(SUBTRACTFILTERSIZE/2.0);
        signed int endN =  floor(SUBTRACTFILTERSIZE/2.0);
        
        for (int i = 0; i < ROW; i ++){
            for (int j = 0; j < COL; j++) {
                long double * tempPixelArray = new long double [SUBTRACTFILTERSIZE*SUBTRACTFILTERSIZE]();
                int tempCount = 0;
                long double tempSum = 0;
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
                        long double tempPixel = image2D[rowIndex][colIndex];
                        tempPixelArray[tempCount] = tempPixel;
                        tempSum = tempSum + tempPixel;
                        //cout << "TempArr " << tempPixel << ' ' << tempPixelArray[tempCount] << endl;
                        tempCount++;
                    }
                }
                
                image2D[i][j] = image2D[i][j] - (tempSum/(SUBTRACTFILTERSIZE*SUBTRACTFILTERSIZE));
                //cout << "Sub " << image2D[i][j] << endl;
            }
        }
    }
    
    void energyFeatureExtraction(int ENERGYFILTERSIZE) {
        
        signed int startN = - floor(FILTERSIZE/2.0);
        signed int endN =  floor(FILTERSIZE/2.0);
        
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
                        long double tempPixel = image2D[rowIndex][colIndex];
                        tempPixelArray[tempCount] = tempPixel;
                        //cout << "TempArr " << tempPixel << ' ' << tempPixelArray[tempCount] << endl;
                        tempCount++;
                    }
                }
                
                // Convolute with every Filter (Total:9)
                for(int maskNo = 0; maskNo < FILTERCOUNT*FILTERCOUNT; maskNo++) {
                    //cout << maskNo << "-----------" << endl;
                    int tempCount = 0;
                    long double tempSum = 0;
                    for(int l=0; l< FILTERSIZE; l++){
                        for(int m=0; m < FILTERSIZE; m++) {
                            tempSum = tempSum + (filtersStacked[l][m][maskNo] * tempPixelArray[tempCount]);
                            //cout << filtersStacked[l][m][maskNo] << ' '<<  tempPixelArray[tempCount] << ' ' <<  tempSum << endl;
                            tempCount++;
                        }
                    }
                    imageFeatureStack[i][j][maskNo] = tempSum;
                }
            }
        }
        
        // Calculate Energy for 9 feature images for every pixel
        startN = - floor(ENERGYFILTERSIZE/2.0);
        endN =  floor(ENERGYFILTERSIZE/2.0);
        
        unsigned long int pixelCount = 0;
        for (int i = 0; i < ROW; i ++){
            for (int j = 0; j < COL; j++) {
                
                for(int maskNo=0; maskNo < FILTERCOUNT*FILTERCOUNT; maskNo++) {
                    long double * tempPixelArray = new long double [ENERGYFILTERSIZE*ENERGYFILTERSIZE]();
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
                            long double tempPixel = imageFeatureStack[rowIndex][colIndex][maskNo];
                            tempPixelArray[tempCount] = tempPixel;
                            //cout << "TempArr " << tempPixel << ' ' << tempPixelArray[tempCount] << endl;
                            tempCount++;
                        }
                    }
                    
                    // Calculate energy
                    long double tempEnergySum = 0;
                    for(int l=0; l< ENERGYFILTERSIZE*ENERGYFILTERSIZE; l++) {
                        tempEnergySum = tempEnergySum + pow(abs(tempPixelArray[l]),2);
                    }
                    tempEnergySum = tempEnergySum / (ENERGYFILTERSIZE*ENERGYFILTERSIZE);
                    energyFeatureExtracted[pixelCount][maskNo] = tempEnergySum;
                    //cout << pixelCount << ' ' << maskNo << ' ' << energyFeatureExtracted[pixelCount][maskNo] << endl;
                }
                pixelCount++;
            }
        }
        //cout << energyFeatureExtracted[24895][4] << endl;
        cout << "total " << pixelCount << endl;
    }
    
    void initializeKmeansCentroids(long double ** features){
        for(int i=0; i< CLUSTERCOUNT; i++) {
            for(int j=0; j<COLFEATURES; j++) {
                if(i==0) {
                    kmeansCentroids[i][j] = features[21095][j];
                }
                else if(i==1) {
                    kmeansCentroids[i][j] = features[24895][j];
                }
                else if(i==2) {
                    kmeansCentroids[i][j] = features[55093][j];
                }
                else if(i==3) {
                    kmeansCentroids[i][j] = features[132891][j];
                }
                else if(i==4) {
                    kmeansCentroids[i][j] = features[222680][j];
                }
                else if(i==5) {
                    kmeansCentroids[i][j] = features[218883][j];
                }
                //cout << kmeansCentroids[i][j] << endl;
            }
        }
    }
    
    void kmeansClustering(long double ** features, int ITERATIONCOUNT){
        
        for(int iterationNO=0; iterationNO < ITERATIONCOUNT; iterationNO++) {
            cout << "iteration :" << iterationNO << endl;
            for(int pixelNo=0; pixelNo < ROWFEATURES; pixelNo++) {
                long double * tempDistance = new long double [CLUSTERCOUNT]();
                
                // Get Euclidean Distance from data point to all the cluster centroids
                for (int clusterNo=0; clusterNo < CLUSTERCOUNT; clusterNo++) {
                    long double tempSum = 0;
                    for (int i = 0; i < COLFEATURES; i ++){
                        tempSum = tempSum + pow((features[pixelNo][i] - kmeansCentroids[clusterNo][i]) , 2);
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
                kmeansCluster[pixelNo] = minDistCluster;
                //cout << pixelNo << ' ' << kmeansCluster[pixelNo] << endl;
            }
            
            
            //Update Centroids
            for(int clusterNo=0; clusterNo < CLUSTERCOUNT; clusterNo++) {
                
                int updateCount = 0;
                for(int pixelNo=0; pixelNo < ROWFEATURES; pixelNo++) {
                    if( kmeansCluster[pixelNo] == clusterNo) {
                        if( updateCount == 0) {
                            for(int i=0; i < COLFEATURES; i++) {
                                kmeansCentroids[clusterNo][i] = features[pixelNo][i];
                                //cout << kmeansCentroids[clusterNo][i] << endl;
                            }
                        }
                        else {
                            for(int i=0; i < COLFEATURES; i++) {
                                kmeansCentroids[clusterNo][i] = kmeansCentroids[clusterNo][i] + features[pixelNo][i];
                                //cout << kmeansCentroids[clusterNo][i] << endl;
                            }
                        }
                        updateCount++;
                    }
                }
                
                for(int i=0; i < COLFEATURES; i++) {
                    if(updateCount > 0){
                        kmeansCentroids[clusterNo][i] = kmeansCentroids[clusterNo][i] / ((long double) (updateCount));
                    }
                    //cout << kmeansCentroids[clusterNo][i] << endl;
                }
            }
        }
    }
    
    
    void clustersToGraylevels(unsigned char * graylevel) {
        unsigned long int tempCount = 0;
        for(int i=0; i<ROW; i++){
            for(int j=0; j<COL; j++){
                //cout << kmeansCluster[tempCount] << endl;
                for(int k=0; k < CLUSTERCOUNT; k++) {
                    if(kmeansCluster[tempCount] == k) {
                        image2DOutput[i][j] = graylevel[k];
                        //cout << kmeansCluster[tempCount] << ' ' << (int)graylevel[k] << endl;
                    }
                }
                tempCount++;
            }
        }
    }
    
    ~textureSegmentation() {
        freeMemory3DLongDouble(imageFeatureStack, ROW, COL, FILTERCOUNT*FILTERCOUNT);
        freeMemory2DLongDouble(energyFeatureExtracted, ROW*COL, FILTERCOUNT*FILTERCOUNT);
        freeMemory2DLongDouble(kmeansCentroids, CLUSTERCOUNT, COLFEATURES);
        delete [] kmeansCluster;
        freeMemory2D(image2DOutput, ROW, COL);
    }
    
    
};

int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 8){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [ROW] [COL] [BYTESPERPIXEL] [input image paths] [output image path]" << endl;
        return 0;
    }
    
    // Store the required arguments --------
    int ROW = atoi(argv[1]);
    int COL = atoi(argv[2]);
    int BYTESPERPIXEL = atoi(argv[3]);
    long int IMAGELEN = ROW*COL*BYTESPERPIXEL;
    
    cout << "Number of arguments passed: " << argc << endl;
    cout << "BYTESPERPIXEL: " << BYTESPERPIXEL << endl;
    cout << "ROW: " << ROW << endl;
    cout << "COL: " << COL << endl;
    cout << "File length: " << IMAGELEN << endl;
    cout << "Processing File: " << argv[4] << endl;
    cout << "-----------------------" << endl;
    
    // Declare required input and output datastructures ---------
    unsigned char *imageFromFile = new unsigned char [IMAGELEN]();
    unsigned char *imageToFile = new unsigned char [IMAGELEN]();
    
    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFile, IMAGELEN);
    
    // Declare and allocate memoory for the images --------
    long double ** image2D = NULL;
    image2D = new long double *[ROW]();
    long int temp_count = 0;
    for(int i=0; i < ROW; i++) {
        image2D[i] = new long double [COL]();
        for(int j=0; j < COL; j++) {
            image2D[i][j] = imageFromFile[temp_count];
            temp_count = temp_count + 1;
        }
    }
    
    // Get Laws Filter
    const int FILTERCOUNT = 5;
    const int FILTERSIZE = 5;
    long double * L5 = new long double [FILTERSIZE]{1.0/16.0, 4.0/16.0, 6.0/16.0, 4.0/16.0, 1.0/16.0};
    long double * E5 = new long double [FILTERSIZE]{-1.0/6.0, -2.0/6.0, 0, 2.0/6.0, 1.0/6.0};
    long double * S5 = new long double [FILTERSIZE]{-1.0/4.0, 0, 2.0/4.0, 0, -1.0/4.0};
    long double * W5 = new long double [FILTERSIZE]{-1.0/6.0, 2.0/6.0, 0, -2.0/6.0, 1.0/6.0};
    long double * R5 = new long double [FILTERSIZE]{1.0/16.0, -4.0/16.0, 6.0/16.0, -4.0/16.0, 1.0/16.0};

    long double ** lawsFilter = NULL;
    lawsFilter = new long double *[FILTERCOUNT]();
    lawsFilter[0] = L5;
    lawsFilter[1] = E5;
    lawsFilter[2] = S5;
    lawsFilter[3] = W5;
    lawsFilter[4] = R5;

    long double *** lawsFilterCombn = NULL;
    lawsFilterCombn = allocMemory3DLongDouble(lawsFilterCombn, FILTERSIZE, FILTERSIZE, FILTERSIZE*FILTERSIZE);
    
    int tempCount = 0;
    for(int i = 0; i < FILTERCOUNT; i++) {
        for(int j= 0; j < FILTERCOUNT; j++) {
            //cout << "Colvolved Filter " << tempCount << endl;
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
    int CLUSTERCOUNT = 6;
    int PCADIM = 5	;

    textureSegmentation segmentTextures = textureSegmentation(image2D, lawsFilterCombn, ROW, COL, FILTERCOUNT, FILTERSIZE, CLUSTERCOUNT, ROW*COL, PCADIM);
    /*
    segmentTextures.subtractLocalMean(13);
    segmentTextures.energyFeatureExtraction(13);
    
    // Write to a file for PCA Reduction
    long double * energyToFile = new long double [ROW*COL*FILTERCOUNT*FILTERCOUNT];
    energyToFile = image2Dto1DLongDouble(segmentTextures.energyFeatureExtracted, energyToFile, ROW*COL, FILTERCOUNT*FILTERCOUNT);
    fileWriteEnergy(argv[5], energyToFile, ROW*COL*FILTERCOUNT*FILTERCOUNT);
    */
    
    // Get PCA reduced energy features
    long double * energyFeaturesPCA1D = new long double [ROW*COL*FILTERCOUNT*PCADIM];
    fileReadEnergy(argv[6], energyFeaturesPCA1D, ROW*COL*PCADIM);
    long double ** energyFeaturesPCA = NULL;
    energyFeaturesPCA =  convert1DtoMatrixLongDouble(energyFeaturesPCA, energyFeaturesPCA1D, ROW*COL, PCADIM);
    
    // Kmeans clustering
    segmentTextures.initializeKmeansCentroids(energyFeaturesPCA);
    segmentTextures.kmeansClustering(energyFeaturesPCA, 20);
    
    unsigned char * graylevel = new unsigned char [CLUSTERCOUNT]{0,51,103,153,204,255};
    segmentTextures.clustersToGraylevels(graylevel);
    
    image2Dto1D(segmentTextures.image2DOutput, imageToFile, ROW, COL);
    fileWrite(argv[7], imageToFile, IMAGELEN);
    
    //Deallocate Memories
    freeMemory2DLongDouble(image2D, ROW, COL);
    freeMemory3DLongDouble(lawsFilterCombn, FILTERSIZE, FILTERSIZE, FILTERSIZE*FILTERSIZE);
    freeMemory2DLongDouble(energyFeaturesPCA,  ROW*COL, PCADIM);
    delete [] energyFeaturesPCA1D;
    delete [] L5;
    delete [] E5;
    delete [] S5;
    delete [] W5;
    delete [] R5;
}
