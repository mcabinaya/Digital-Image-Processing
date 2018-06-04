//
//  main.cpp
//  hw_1_prob_2_b
//
//  Created by Abinaya Manimaran on 1/23/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include "DIP_MyHeaderFile.h"
using namespace std;

unsigned char ** quantize2DImage(unsigned char ** image2D, unsigned char ** image2DQuantized, int row, int col, int quantizationLevelsPerChannel) {
    
    // Form 3 1D-arrays to track row, col, pixel values
    unsigned int *trackRowIndex = new unsigned int [row*col]();
    unsigned int *trackColIndex = new unsigned int [row*col]();
    unsigned char *trackPixel = new unsigned char [row*col]();
    
    unsigned int tempIndex = 0;
    for(int pixel = 0; pixel < 256; pixel++) {
        for(int i = 0; i < row ; i++) {
            for(int j=0; j < col; j++) {
                if(image2D[i][j] == pixel) {
                    trackRowIndex[tempIndex] = i;
                    trackColIndex[tempIndex] = j;
                    trackPixel[tempIndex] = pixel;
                    tempIndex = tempIndex + 1;
                }
            }
        }
    }
    
    // Get the mean value for every bin and assign it back to all the pixels of that bin
    unsigned int binSize = floor((float)(row*col) / ((float)quantizationLevelsPerChannel));
    
    for(unsigned int level = 0; level < (row*col); level = level+binSize) {
        float tempSum = 0.0;
        unsigned int tempCount = 0;
        for(int i = level; i < level+binSize; i++) {
            tempSum = tempSum + trackPixel[i];
            tempCount = tempCount + 1;
        }
        unsigned int binAverage = ceil(tempSum/(float)(tempCount));
        for(int i = level; i < level+binSize; i++) {
            trackPixel[i] = (unsigned char) binAverage;
        }
    }
    
    // Track the pixels back from 1D array to 2D array
    unsigned int tempRowIndex;
    unsigned int tempColIndex;
    for(int i=0; i < (row*col); i++) {
        tempRowIndex = trackRowIndex[i];
        tempColIndex = trackColIndex[i];
        image2DQuantized[tempRowIndex][tempColIndex] = trackPixel[i];
    }
    
    delete [] trackRowIndex;
    delete [] trackColIndex;
    delete [] trackPixel;

    return image2DQuantized;
}

unsigned char ** oilEffectImage2D(unsigned char ** image2DOilEffect, unsigned char ** image2D, int row, int col, int N) {
    signed int startN = - floor(N/2.0);
    signed int endN =  floor(N/2.0);
    
    // Traverse for N*N neighborhood and find the count of pixels occuring
    for (int i = 0; i < row; i ++){
        for (int j = 0; j < col; j++) {
            unsigned char * tempCountPixel = new unsigned char [256]();
            
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
                        if(rowIndex > row-1) {
                            rowIndex = row-1;
                        }
                        if(colIndex > col-1) {
                            colIndex = col-1;
                        }
                        unsigned char tempPixel = image2D[rowIndex][colIndex];
                        tempCountPixel[tempPixel] ++ ;
                }
            }
            // Find the maximum occuring neigborhood pixel
            unsigned char tempMaxCount = tempCountPixel[0];
            int tempMaxPixel = 0;
            for (int k = 1; k < 256; k++){
                if(tempMaxCount < tempCountPixel[k]) {
                    tempMaxCount = tempCountPixel[k];
                    tempMaxPixel = k;
                }
            }
            delete[] tempCountPixel;
            image2DOilEffect[i][j] = tempMaxPixel;
        }
    }
    return image2DOilEffect;
}


int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 9){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [row] [col] [bytesPerPixel] [input image path] [raw output image 1 path] [raw output image 2 path] [Number of Quantization levels] [N - for N*N neighborhood]" << endl;
        return 0;
    }
    
    // Store the required arguments --------
    int row = atoi(argv[1]);
    int col = atoi(argv[2]);
    int bytesPerPixel = atoi(argv[3]);
    long int imageLen = row*col*bytesPerPixel;
    int quantizationLevels = atoi(argv[7]);
    int N = atoi(argv[8]);
    
    cout << "Number of arguments passed: " << argc << endl;
    cout << "BytesPerPixel: " << bytesPerPixel << endl;
    cout << "Row: " << row << endl;
    cout << "Col: " << col << endl;
    cout << "File length: " << imageLen << endl;
    cout << "Processing File: " << argv[4] << endl;
    cout << "-----------------------" << endl;
    
    // Declare required input and output datastructures ---------
    unsigned char *imageFromFile = new unsigned char [imageLen]();
    unsigned char *imageToFileQuantized = new unsigned char [imageLen]();
    unsigned char *imageToFileOilEffect = new unsigned char [imageLen]();
    
    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFile, imageLen);
    
    // Declare and allocate memoory for the images --------
    unsigned char *** image3D = NULL;
    image3D = image1Dto3D(image3D, imageFromFile, row, col, bytesPerPixel);
    
    // Declare and allocate memoory for the required data types --------
    
    unsigned char ** image2DRChannel = NULL;
    image2DRChannel = seperateChannels(image3D, image2DRChannel, row, col, 0);
    
    unsigned char ** image2DGChannel = NULL;
    image2DGChannel = seperateChannels(image3D, image2DGChannel, row, col, 1);
    
    unsigned char ** image2DBChannel = NULL;
    image2DBChannel = seperateChannels(image3D, image2DBChannel, row, col, 2);
    
    unsigned char ** image2DRQuantized = NULL;
    image2DRQuantized = allocMemory2D(image2DRQuantized, row, col);
    
    unsigned char ** image2DGQuantized = NULL;
    image2DGQuantized = allocMemory2D(image2DGQuantized, row, col);
    
    unsigned char ** image2DBQuantized = NULL;
    image2DBQuantized = allocMemory2D(image2DBQuantized, row, col);

    unsigned char ** image2DROilEffect = NULL;
    image2DROilEffect = allocMemory2D(image2DROilEffect, row, col);
    
    unsigned char ** image2DGOilEffect = NULL;
    image2DGOilEffect = allocMemory2D(image2DGOilEffect, row, col);
    
    unsigned char ** image2DBOilEffect = NULL;
    image2DBOilEffect = allocMemory2D(image2DBOilEffect, row, col);

    unsigned char *** image3DQuantized = NULL;
    image3DQuantized = allocMemory3D(image3DQuantized, row, col, bytesPerPixel);

    unsigned char *** image3DOilEffect = NULL;
    image3DOilEffect = allocMemory3D(image3DOilEffect, row, col, bytesPerPixel);
    
    // Quantization for every Channel
    float quantizationLevelsPerChannel = pow(quantizationLevels, (1.0/((float)(bytesPerPixel))));
    
    image2DRQuantized = quantize2DImage(image2DRChannel, image2DRQuantized, row, col, quantizationLevelsPerChannel);
    image2DGQuantized = quantize2DImage(image2DGChannel, image2DGQuantized, row, col, quantizationLevelsPerChannel);
    image2DBQuantized = quantize2DImage(image2DBChannel, image2DBQuantized, row, col, quantizationLevelsPerChannel);
    
    image3DQuantized = combineChannels(image3DQuantized, image2DRQuantized, image2DGQuantized, image2DBQuantized, row, col, bytesPerPixel);
    
    // Oil Painting Effect after Quantization
    image2DROilEffect = oilEffectImage2D(image2DROilEffect, image2DRQuantized, row, col, N);
    image2DGOilEffect = oilEffectImage2D(image2DGOilEffect, image2DGQuantized, row, col, N);
    image2DBOilEffect = oilEffectImage2D(image2DBOilEffect, image2DBQuantized, row, col, N);

    image3DOilEffect = combineChannels(image3DQuantized, image2DROilEffect, image2DGOilEffect, image2DBOilEffect, row, col, bytesPerPixel);

    // Write outputs to the Raw files --------
    image3Dto1D(image3DQuantized, imageToFileQuantized, row, col, bytesPerPixel);
    fileWrite(argv[5], imageToFileQuantized, imageLen);
    
    // Write outputs to the Raw files --------
    image3Dto1D(image3DOilEffect, imageToFileOilEffect, row, col, bytesPerPixel);
    fileWrite(argv[6], imageToFileOilEffect, imageLen);
    
    freeMemory3D(image3D, row, col, bytesPerPixel);
    freeMemory3D(image3DQuantized, row, col, bytesPerPixel);
    freeMemory3D(image3DOilEffect, row, col, bytesPerPixel);
    freeMemory2D(image2DRChannel, row, col);
    freeMemory2D(image2DGChannel, row, col);
    freeMemory2D(image2DBChannel, row, col);
    freeMemory2D(image2DRQuantized, row, col);
    freeMemory2D(image2DGQuantized, row, col);
    freeMemory2D(image2DBQuantized, row, col);
    freeMemory2D(image2DROilEffect, row, col);
    freeMemory2D(image2DGOilEffect, row, col);
    freeMemory2D(image2DBOilEffect, row, col);
    
    delete[] imageFromFile;
    delete[] imageToFileQuantized;
    delete[] imageToFileOilEffect;

}
