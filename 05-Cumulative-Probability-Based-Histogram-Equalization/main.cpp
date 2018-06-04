//
//  main.cpp
//  hw_1_prob_2_a_methodB
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

unsigned char ** histEqualizationCDFBased(unsigned char ** image2D, unsigned char ** image2DHistEqualized, int row, int col, unsigned int bucketSize) {
    
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
    
    // Change the pixel array acccording to bucket size
    unsigned int tempCount = 0;
    unsigned char tempPixel = 0;
    unsigned int tempArrayIndex = 0;
    for(int i = 0; i < (row*col) ; i++) {
        if(tempCount != bucketSize) {
            trackPixel[tempArrayIndex] = tempPixel;
            tempArrayIndex = tempArrayIndex + 1;
            tempCount = tempCount + 1;
        }
        else{
            tempPixel = tempPixel + 1;
            tempCount = 0;
        }
    }
    
    // Track back the changed pixel values to a 2D array
    unsigned int tempRowIndex;
    unsigned int tempColIndex;
    for(int i=0; i < (row*col); i++) {
        tempRowIndex = trackRowIndex[i];
        tempColIndex = trackColIndex[i];
        image2DHistEqualized[tempRowIndex][tempColIndex] = trackPixel[i];
    }
    
    delete [] trackRowIndex;
    delete [] trackColIndex;
    delete [] trackPixel;
    
    return image2DHistEqualized;
}


int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 12){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [row] [col] [bytesPerPixel] [input image path] [raw output image 1 path] [text output Hist Equalized R] [text output Hist Equalized G] [text output Hist Equalized B] [text output CDF Equalized R] [text output CDF Equalized G] [text output CDF Equalized B]" << endl;
        return 0;
    }
    
    // Store the required arguments --------
    int row = atoi(argv[1]);
    int col = atoi(argv[2]);
    int bytesPerPixel = atoi(argv[3]);
    long int imageLen = row*col*bytesPerPixel;
    
    cout << "Number of arguments passed: " << argc << endl;
    cout << "BytesPerPixel: " << bytesPerPixel << endl;
    cout << "Row: " << row << endl;
    cout << "Col: " << col << endl;
    cout << "File length: " << imageLen << endl;
    cout << "Processing File: " << argv[4] << endl;
    cout << "-----------------------" << endl;
    
    // Declare required input and output datastructures ---------
    unsigned char *imageFromFile = new unsigned char [imageLen]();
    unsigned char *imageToFile = new unsigned char [imageLen]();
    
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
    
    unsigned char ** image2DRChannelHistEqualized = NULL;
    image2DRChannelHistEqualized = allocMemory2D(image2DRChannelHistEqualized, row, col);
    
    unsigned char ** image2DGChannelHistEqualized = NULL;
    image2DGChannelHistEqualized = allocMemory2D(image2DGChannelHistEqualized, row, col);
    
    unsigned char ** image2DBChannelHistEqualized = NULL;
    image2DBChannelHistEqualized = allocMemory2D(image2DBChannelHistEqualized, row, col);
    
    unsigned char *** image3DHistEqualized = NULL;
    image3DHistEqualized = allocMemory3D(image3DHistEqualized, row, col, bytesPerPixel);
    
    unsigned int *histEqualizedRChannel = new unsigned int [256]();
    unsigned int *histEqualizedGChannel = new unsigned int [256]();
    unsigned int *histEqualizedBChannel = new unsigned int [256]();
    unsigned int *CDFEqualizedRChannel = new unsigned int [256]();
    unsigned int *CDFEqualizedGChannel = new unsigned int [256]();
    unsigned int *CDFEqualizedBChannel = new unsigned int [256]();
    
    // Cumulative-probability-based histogram equalization method --------
    // Calculate bucket size
    unsigned int bucketSize = ceil(((float)(row*col) / 256.0));
    
    image2DRChannelHistEqualized = histEqualizationCDFBased(image2DRChannel, image2DRChannelHistEqualized, row,col, bucketSize);
    image2DGChannelHistEqualized = histEqualizationCDFBased(image2DGChannel, image2DGChannelHistEqualized, row,col, bucketSize);
    image2DBChannelHistEqualized = histEqualizationCDFBased(image2DBChannel, image2DBChannelHistEqualized, row,col, bucketSize);
    
    // Calculate histogram of the Equalized R, G and B image
    histogram2DImage(image2DRChannelHistEqualized, histEqualizedRChannel, row, col);
    histogram2DImage(image2DGChannelHistEqualized, histEqualizedGChannel, row, col);
    histogram2DImage(image2DBChannelHistEqualized, histEqualizedBChannel, row, col);
    
    // Calculate cdf of Equalized R, G and B image
    for(int i=0; i< 256; i++) {
        if(i == 0) {
            CDFEqualizedRChannel[i] = histEqualizedRChannel[i];
            CDFEqualizedGChannel[i] = histEqualizedGChannel[i];
            CDFEqualizedBChannel[i] = histEqualizedBChannel[i];
            
        }
        else{
            CDFEqualizedRChannel[i] = CDFEqualizedRChannel[i-1] + histEqualizedRChannel[i];
            CDFEqualizedGChannel[i] = CDFEqualizedGChannel[i-1] + histEqualizedRChannel[i];
            CDFEqualizedBChannel[i] = CDFEqualizedBChannel[i-1] + histEqualizedRChannel[i];
        }
        //cout << i << ' ' << CDFEqualizedRChannel[i] << ' ' << CDFEqualizedGChannel[i] << ' ' << CDFEqualizedBChannel[i] << endl;
    }
    
    // Form 3D image from Histogram Equalized R, G, B - 2D images
    image3DHistEqualized = combineChannels(image3DHistEqualized, image2DRChannelHistEqualized, image2DGChannelHistEqualized, image2DBChannelHistEqualized, row, col, bytesPerPixel);

    // Write outputs to the Raw files --------
    image3Dto1D(image3DHistEqualized, imageToFile, row, col, bytesPerPixel);
    fileWrite(argv[5], imageToFile, imageLen);
    
    fileWriteHist(argv[6], histEqualizedRChannel);
    fileWriteHist(argv[7], histEqualizedGChannel);
    fileWriteHist(argv[8], histEqualizedBChannel);
    fileWriteHist(argv[9], CDFEqualizedRChannel);
    fileWriteHist(argv[10], CDFEqualizedGChannel);
    fileWriteHist(argv[11], CDFEqualizedBChannel);
    

    // Deallocate all the other memories used --------
    freeMemory3D(image3D, row, col, bytesPerPixel);
    freeMemory3D(image3DHistEqualized, row, col, bytesPerPixel);
    freeMemory2D(image2DRChannel, row, col);
    freeMemory2D(image2DGChannel, row, col);
    freeMemory2D(image2DBChannel, row, col);
    freeMemory2D(image2DRChannelHistEqualized, row, col);
    freeMemory2D(image2DGChannelHistEqualized, row, col);
    freeMemory2D(image2DBChannelHistEqualized, row, col);
    
    delete[] histEqualizedRChannel;
    delete[] histEqualizedGChannel;
    delete[] histEqualizedBChannel;
    delete[] CDFEqualizedRChannel;
    delete[] CDFEqualizedGChannel;
    delete[] CDFEqualizedBChannel;

    delete[] imageFromFile;
    delete[] imageToFile;

}
