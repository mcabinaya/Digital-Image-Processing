//
//  main.cpp
//  hw_2_prob_2_a
//
//  Created by Abinaya Manimaran on 2/13/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include "DIP_MyHeaderFile.h"
using namespace std;


unsigned char ** fixedThresholding(unsigned char ** image2DFixedThr, unsigned char ** image2D, unsigned char THRESHOLD, int ROW, int COL) {
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++) {
            if(image2D[i][j] < THRESHOLD) { image2DFixedThr[i][j] = 0;}
            else{ image2DFixedThr[i][j] = 255; }
            //cout << (int) THRESHOLD << ' ' << (int)image2D[i][j] << ' ' << (int)image2DFixedThr[i][j] << endl;
        }
    }
    return image2DFixedThr;
}

unsigned char ** randomThresholding(unsigned char ** image2DRandThr, unsigned char ** image2D, int ROW, int COL){
    for(int i = 0; i < ROW; i++) {
        for(int j=0; j < COL; j++) {
            unsigned char randomNumber = rand() % 256;
            if (randomNumber <= image2D[i][j]) { image2DRandThr[i][j] = 255; }
            else { image2DRandThr[i][j] = 0; }
            //cout << (int) randomNumber << ' ' << (int) image2D[i][j] << ' ' << (int) image2DRandThr[i][j] << endl;
        }
    }
    return image2DRandThr;
}

long double ** formIndexMatrix(long double ** indexMatrix, long double * indexMatrix1D, int N){
    unsigned int tempCount = 0;
    indexMatrix = new long double * [N]();
    for(int i=0; i < N; i++) {
        indexMatrix[i] = new long double [N]();
        for(int j=0; j < N; j++){
            indexMatrix[i][j] = (indexMatrix1D[tempCount] + 0.5)/(N*N);;
            tempCount ++;
            //cout << indexMatrix[i][j] << endl;
        }
    }
    return indexMatrix;
}


unsigned char ** dithering2Intensities(unsigned char ** image2DDithered, unsigned char ** image2D, long double ** indexMatrix, int N, int ROW, int COL) {
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            int x = i % N;
            int y = j % N;
            if (((float)image2D[i][j]/255.0) > indexMatrix[x][y]) { image2DDithered[i][j] = 255; }
            else { image2DDithered[i][j] = 0; }
            //cout << indexMatrix[x][y] << ' ' << (int) image2D[i][j] << ' ' << (int)image2DDithered[i][j] << endl;
        }
    }
    return image2DDithered;
}

unsigned char ** dithering4Intensities(unsigned char ** image2DDithered, unsigned char ** image2D, long double ** indexMatrix, int N, int ROW, int COL) {
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            int x = i % N;
            int y = j % N;
            long double pixel = ((long double)image2D[i][j]/255.0);
            if ((pixel >= 0) and (pixel <= (indexMatrix[x][y] / 2.0))){
                image2DDithered[i][j] = 0; }
            else if ((pixel > (indexMatrix[x][y] / 2.0)) and (pixel <= indexMatrix[x][y])){
                image2DDithered[i][j] = 85; }
            else if ((pixel > indexMatrix[x][y]) and (pixel <= (indexMatrix[x][y] + (indexMatrix[x][y] / 2.0)))){
                image2DDithered[i][j] = 170;}
            else{
                image2DDithered[i][j] = 255;}
            }
            //cout << indexMatrix[x][y] << ' ' << (int) image2D[i][j] << ' ' << (int)image2DDithered[i][j] << endl;
        }
    return image2DDithered;
}


int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 13){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [row] [col] [bytesPerPixel]  [input color checker image path] [output image path - fixed thresholding] [output image path - random thresholding] [output image path - dithering (N=2)] [output image path - dithering (N=4)] [output image path - dithering (N=8)] [output image path - 4 Intensity dithering (N=2)] [output image path - 4 Intensity dithering (N=4)] [output image path - 4 Intensity dithering (N=8)]" << endl;
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
    unsigned char *imageToFileFixedThr = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileRandThr = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileDithering2N = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileDithering4N = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileDithering8N = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileDithering2N4Intensity = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileDithering4N4Intensity = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileDithering8N4Intensity = new unsigned char [IMAGELEN]();

    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFile, IMAGELEN);
    
    // Declare and allocate memoory for the images --------
    unsigned char ** image2D = NULL;
    image2D = image1Dto2D(image2D, imageFromFile, ROW, COL);
    
    unsigned char ** image2DFixedThr = NULL;
    image2DFixedThr = allocMemory2D(image2DFixedThr, ROW, COL);
    
    unsigned char ** image2DRandThr = NULL;
    image2DRandThr = allocMemory2D(image2DRandThr, ROW, COL);
    
    unsigned char ** image2DDithered2N = NULL;
    image2DDithered2N = allocMemory2D(image2DDithered2N, ROW, COL);
    
    unsigned char ** image2DDithered4N = NULL;
    image2DDithered4N = allocMemory2D(image2DDithered4N, ROW, COL);
    
    unsigned char ** image2DDithered8N = NULL;
    image2DDithered8N = allocMemory2D(image2DDithered8N, ROW, COL);

    unsigned char ** image2DDithered2N4Intensity = NULL;
    image2DDithered2N4Intensity = allocMemory2D(image2DDithered2N4Intensity, ROW, COL);
    
    unsigned char ** image2DDithered4N4Intensity = NULL;
    image2DDithered4N4Intensity = allocMemory2D(image2DDithered4N4Intensity, ROW, COL);
    
    unsigned char ** image2DDithered8N4Intensity = NULL;
    image2DDithered8N4Intensity = allocMemory2D(image2DDithered8N4Intensity, ROW, COL);

    // Fixed Thresholding
    unsigned char THRESHOLD = 127;
    image2DFixedThr = fixedThresholding(image2DFixedThr, image2D, THRESHOLD, ROW, COL);
   
    // Random Thresholding
    image2DRandThr = randomThresholding(image2DRandThr, image2D, ROW, COL);
    
    // Dithering
    long double * indexMatrix1D2N = new long double [4]{1, 2, 3, 0};
    long double * indexMatrix1D4N = new long double [16]{5, 9, 6, 10, 13, 1, 14, 2, 7, 11, 4, 8, 15, 3, 12, 0};
    long double * indexMatrix1D8N = new long double [64]{21, 37, 25, 41, 22, 38, 26, 42, 53, 5, 57, 9, 54, 6, 58, 10, 29, 45, 17, 33,  30, 46, 18, 34, 61,    13, 49, 1, 62, 14, 50, 2, 23, 39, 27, 43, 20, 36, 24, 40, 55, 7, 59, 11, 52, 4, 56, 8, 31, 47, 19, 35, 28, 44, 16, 32, 63, 15, 51, 3, 60, 12, 48, 0};


    long double ** indexMatrix2N = NULL;
    indexMatrix2N = formIndexMatrix(indexMatrix2N, indexMatrix1D2N, 2 );
    
    long double ** indexMatrix4N = NULL;
    indexMatrix4N = formIndexMatrix(indexMatrix4N, indexMatrix1D4N, 4 );
    
    long double ** indexMatrix8N = NULL;
    indexMatrix8N = formIndexMatrix(indexMatrix8N, indexMatrix1D8N, 8 );
    
    
    image2DDithered2N =  dithering2Intensities(image2DDithered2N, image2D, indexMatrix2N, 2, ROW, COL);
    image2DDithered4N =  dithering2Intensities(image2DDithered4N, image2D, indexMatrix4N, 4, ROW, COL);
    image2DDithered8N =  dithering2Intensities(image2DDithered8N, image2D, indexMatrix8N, 8, ROW, COL);
    
    image2DDithered2N4Intensity =  dithering4Intensities(image2DDithered2N4Intensity, image2D, indexMatrix2N, 2, ROW, COL);
    image2DDithered4N4Intensity =  dithering4Intensities(image2DDithered4N4Intensity, image2D, indexMatrix4N, 4, ROW, COL);
    image2DDithered8N4Intensity =  dithering4Intensities(image2DDithered8N4Intensity, image2D, indexMatrix8N, 8, ROW, COL);
    
    // Write outputs to the Raw files --------
    image2Dto1D(image2DFixedThr, imageToFileFixedThr, ROW, COL);
    fileWrite(argv[5], imageToFileFixedThr, IMAGELEN);
    
    image2Dto1D(image2DRandThr, imageToFileRandThr, ROW, COL);
    fileWrite(argv[6], imageToFileRandThr, IMAGELEN);

    image2Dto1D(image2DDithered2N, imageToFileDithering2N, ROW, COL);
    fileWrite(argv[7], imageToFileDithering2N, IMAGELEN);

    image2Dto1D(image2DDithered4N, imageToFileDithering4N, ROW, COL);
    fileWrite(argv[8], imageToFileDithering4N, IMAGELEN);

    image2Dto1D(image2DDithered8N, imageToFileDithering8N, ROW, COL);
    fileWrite(argv[9], imageToFileDithering8N, IMAGELEN);

    image2Dto1D(image2DDithered2N4Intensity, imageToFileDithering2N4Intensity, ROW, COL);
    fileWrite(argv[10], imageToFileDithering2N4Intensity, IMAGELEN);
    
    image2Dto1D(image2DDithered4N4Intensity, imageToFileDithering4N4Intensity, ROW, COL);
    fileWrite(argv[11], imageToFileDithering4N4Intensity, IMAGELEN);
    
    image2Dto1D(image2DDithered8N4Intensity, imageToFileDithering8N4Intensity, ROW, COL);
    fileWrite(argv[12], imageToFileDithering8N4Intensity, IMAGELEN);

    // Deallocate all the memories
    freeMemory2D(image2D, ROW, COL);
    freeMemory2D(image2DFixedThr, ROW, COL);
    freeMemory2D(image2DRandThr, ROW, COL);
    freeMemory2D(image2DDithered2N, ROW, COL);
    freeMemory2D(image2DDithered4N, ROW, COL);
    freeMemory2D(image2DDithered8N, ROW, COL);
    
    delete [] imageFromFile;
    delete [] imageToFileFixedThr;
    delete [] imageToFileRandThr;
    delete [] imageToFileDithering2N;
    delete [] imageToFileDithering4N;
    delete [] imageToFileDithering8N;
}

