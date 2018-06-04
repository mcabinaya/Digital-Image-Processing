//
//  main.cpp
//  hw_1_prob_2_a_methodA
//
//  Created by Abinaya Manimaran on 1/20/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include "DIP_MyHeaderFile.h"

using namespace std;

int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 15){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [row] [col] [bytesPerPixel] [input image path] [raw output image 1 path] [text output histogram R] [text output histogram G] [text output histogram B]  [text transfer function R] [text transfer function G] [text transfer function B] [text output Hist Equalized R] [text output Hist Equalized G] [text output Hist Equalized B]" << endl;
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
    
    unsigned int *histRChannel = new unsigned int [256]();
    unsigned int *histGChannel = new unsigned int [256]();
    unsigned int *histBChannel = new unsigned int [256]();
    float *histTempRChannel = new float [256]();
    float *histTempGChannel = new float [256]();
    float *histTempBChannel = new float [256]();
    unsigned int *histMappingRChannel = new unsigned int [256]();
    unsigned int *histMappingGChannel = new unsigned int [256]();
    unsigned int *histMappingBChannel = new unsigned int [256]();
    unsigned int *histEqualizedRChannel = new unsigned int [256]();
    unsigned int *histEqualizedGChannel = new unsigned int [256]();
    unsigned int *histEqualizedBChannel = new unsigned int [256]();
    
    // Transfer-function-based histogram equalization method --------
    // Calculate Histograms of original image --------
    histogram2DImage(image2DRChannel, histRChannel, row, col);
    histogram2DImage(image2DGChannel, histGChannel, row, col);
    histogram2DImage(image2DBChannel, histBChannel, row, col);
    
    // Calculate normalized histogram --------
    for(int i=0; i < 256;i++){
        histTempRChannel[i] = histRChannel[i] / (((float)(row))*((float)(col)));
        histTempGChannel[i] = histGChannel[i] / (((float)(row))*((float)(col)));
        histTempBChannel[i] = histBChannel[i] / (((float)(row))*((float)(col)));
        //cout << histTempRChannel[i] << ' ' << histTempGChannel[i] << ' ' << histTempBChannel[i] << endl;
    }
    
    cout << "cdf ---" << endl;
    // Calculate cdf
    for(int i=0; i< 256; i++) {
        if(i == 0) {
            histTempRChannel[i] = histTempRChannel[i];
            histTempGChannel[i] = histTempGChannel[i];
            histTempBChannel[i] = histTempBChannel[i];

        }
        else{
            histTempRChannel[i] = histTempRChannel[i] + histTempRChannel[i-1];
            histTempGChannel[i] = histTempGChannel[i] + histTempGChannel[i-1];
            histTempBChannel[i] = histTempBChannel[i] + histTempBChannel[i-1];
        }
        //cout << histTempRChannel[i] << ' ' << histTempGChannel[i] << ' ' << histTempBChannel[i] << endl;
    }
    
    cout << "Mulyiply by 255 ---" << endl;
    // Multiply cdf by the scaling factor
    float scalingFactor = 255.0;
    for(int i=0; i < 256; i++) {
        histTempRChannel[i] = histTempRChannel[i] * scalingFactor;
        histTempGChannel[i] = histTempGChannel[i] * scalingFactor;
        histTempBChannel[i] = histTempBChannel[i] * scalingFactor;
        //cout << histTempRChannel[i] << ' ' << histTempGChannel[i] << ' ' << histTempBChannel[i] << endl;

    }
    
    cout << "rounded off ---" << endl;
    // Round the decimal values to lower intger values
    for(int i=0; i < 256; i++) {
        histMappingRChannel[i] = floor(histTempRChannel[i]);
        histMappingGChannel[i] = floor(histTempGChannel[i]);
        histMappingBChannel[i] = floor(histTempBChannel[i]);
    }
    
    // Mapping the pixel values based on Histogram equalization for each channel
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            unsigned int rPixel = image2DRChannel[i][j];
            image2DRChannelHistEqualized[i][j] = (unsigned char) histMappingRChannel[rPixel];
            
            unsigned int gPixel = image2DGChannel[i][j];
            image2DGChannelHistEqualized[i][j] = (unsigned char) histMappingGChannel[gPixel];
            
            unsigned int bPixel = image2DBChannel[i][j];
            image2DBChannelHistEqualized[i][j] = (unsigned char) histMappingBChannel[bPixel];
            
        }
    }
    // Calculate histogram of the Equalized R, G and B image
    histogram2DImage(image2DRChannelHistEqualized, histEqualizedRChannel, row, col);
    histogram2DImage(image2DGChannelHistEqualized, histEqualizedGChannel, row, col);
    histogram2DImage(image2DBChannelHistEqualized, histEqualizedBChannel, row, col);
    
    // Form 3D image from Histogram Equalized R, G, B - 2D images
    image3DHistEqualized = combineChannels(image3DHistEqualized, image2DRChannelHistEqualized, image2DGChannelHistEqualized, image2DBChannelHistEqualized, row, col, bytesPerPixel);
    
    // Write outputs to the Raw files --------
    image3Dto1D(image3DHistEqualized, imageToFile, row, col, bytesPerPixel);
    fileWrite(argv[5], imageToFile, imageLen);
    
    // Write output histograms of original and equalized image and transfer function --------
    fileWriteHist(argv[6], histRChannel);
    fileWriteHist(argv[7], histGChannel);
    fileWriteHist(argv[8], histBChannel);
    fileWriteHist(argv[9], histMappingRChannel);
    fileWriteHist(argv[10], histMappingRChannel);
    fileWriteHist(argv[11], histMappingRChannel);
    fileWriteHist(argv[12], histEqualizedRChannel);
    fileWriteHist(argv[13], histEqualizedRChannel);
    fileWriteHist(argv[14], histEqualizedRChannel);

    // Deallocate all the other memories used --------
    freeMemory3D(image3D, row, col, bytesPerPixel);
    freeMemory3D(image3DHistEqualized, row, col, bytesPerPixel);
    freeMemory2D(image2DRChannel, row, col);
    freeMemory2D(image2DGChannel, row, col);
    freeMemory2D(image2DBChannel, row, col);
    freeMemory2D(image2DRChannelHistEqualized, row, col);
    freeMemory2D(image2DGChannelHistEqualized, row, col);
    freeMemory2D(image2DBChannelHistEqualized, row, col);

    delete[] histRChannel;
    delete[] histGChannel;
    delete[] histBChannel;
    delete[] histTempRChannel;
    delete[] histTempGChannel;
    delete[] histTempBChannel;
    delete[] histMappingRChannel;
    delete[] histMappingGChannel;
    delete[] histMappingBChannel;
    delete[] histEqualizedRChannel;
    delete[] histEqualizedGChannel;
    delete[] histEqualizedBChannel;
    
    delete[] imageFromFile;
    delete[] imageToFile;
}
