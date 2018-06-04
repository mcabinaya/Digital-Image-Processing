//
//  main.cpp
//  hw_1_prob_3_a
//
//  Created by Abinaya Manimaran on 1/27/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <string>
#include "DIP_MyHeaderFile.h"

using namespace std;

unsigned char ** lowPassFilter(unsigned char ** image2DDenoised, unsigned char ** image2D,int ROW, int COL,int N) {
    signed int startN = - floor(N/2.0);
    signed int endN =  floor(N/2.0);

    for (int i = 0; i < ROW; i ++) {
        for (int j = 0; j < COL; j++) {
            // Take each pixel from the image and get the N*N pixels surrounding it
            unsigned int tempSum = 0;
            float tempAvergae = 0;
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
                    unsigned char tempPixel = image2D[rowIndex][colIndex];
                    tempSum = tempSum + tempPixel;
                }
            }
            tempAvergae = ((float)tempSum) / ((float)(N*N));
            image2DDenoised[i][j] = floor(tempAvergae);
        }
    }
    return image2DDenoised;
}

unsigned char ** medianFilter(unsigned char ** image2DDenoised, unsigned char ** image2D,int ROW, int COL,int N) {
    signed int startN = - floor(N/2.0);
    signed int endN =  floor(N/2.0);
    int midValue = ceil((N*N)/2);
    
    for (int i = 0; i < ROW; i ++) {
        for (int j = 0; j < COL; j++) {
            unsigned char tempArray[N*N];
            int tempCount = 0;
            for(signed int p = startN ; p <= endN ; p ++) {
                for(signed int q = startN ; q <= endN ; q ++) {
                    // Take each pixel from the image and get the N*N pixels surrounding it
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
                    unsigned char tempPixel = image2D[rowIndex][colIndex];
                    tempArray[tempCount] = tempPixel;
                    tempCount = tempCount + 1;
                }
            }
            int tempSortElement;
            for(int l = 0; l < N*N ; l++){
                for(int m = 0; m < (N*N)-1; m++) {
                    if (tempArray[m] > tempArray[m+1]) {
                        tempSortElement = tempArray[m];
                        tempArray[m] = tempArray[m+1];
                        tempArray[m+1] = tempSortElement;
                    }
                }
            }
            image2DDenoised[i][j] = tempArray[midValue];
        }
    }
    return image2DDenoised;
}

unsigned char ** gaussianFilter(unsigned char ** image2DDenoised, unsigned char ** image2D,int ROW, int COL,int N){
    signed int startN = - floor(N/2.0);
    signed int endN =  floor(N/2.0);
    
    // Designing gaussian mask and storing it in 1-D array (N*N
    double *gaussianMask = new double [N*N]();
    float sigma = 1.0;
    int tempMaskCount = 0;
    double maskSum = 0;
    for(int i=0; i < N ; i++){
        for(int j = 0; j < N; j++) {
            int l = i - ((N-1) / 2);
            int m = j - ((N-1) / 2);
            gaussianMask[tempMaskCount] = ((1.0) /((2*3.14*pow(sigma,2)))) * exp( - ((pow(l,2) + pow(m,2)) / (2* pow(sigma,2))));
            maskSum = maskSum + gaussianMask[tempMaskCount];
            tempMaskCount ++ ;
        }
    }
    // Normalize the gaussian mask by dividing each value by the total sum
    for(int i= 0; i < N*N ; i++) {
        gaussianMask[i] = ((float)gaussianMask[i]) / ((float)maskSum);
     }
    
    
    for (int i = 0; i < ROW; i ++) {
        for (int j = 0; j < COL; j++) {
            // Take each pixel from the image and get the N*N pixels surrounding it
            unsigned char tempArray[N*N];
            int tempCount = 0;
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
                    unsigned char tempPixel = image2D[rowIndex][colIndex];
                    tempArray[tempCount] = tempPixel;
                    tempCount = tempCount + 1;
                }
            }
            double tempMaskedPixel = 0.0;
            for(int l = 0; l < (N*N); l++){
                tempMaskedPixel = tempMaskedPixel + (tempArray[l] * gaussianMask[l]);
            }
            image2DDenoised[i][j] = (unsigned char) tempMaskedPixel;
        }
    }
    return image2DDenoised;
}

float calculatePSNR3D(unsigned char *** image3DTarget, unsigned char *** image3D, int ROW,int COL,int BYTESPERPIXEL) {
    unsigned int tempSum = 0;
    double psnr;
    for(int i=0; i < ROW ; i++){
        for(int j=0; j < COL; j++) {
            for(int k=0; k < BYTESPERPIXEL; k++){
                tempSum = tempSum+(pow((image3DTarget[i][j][k] - image3D[i][j][k]),2));
            }
        }
    }
    psnr = 10 * (log10((255*255)/(tempSum / ((float)(ROW * COL * BYTESPERPIXEL)))));
    return psnr;
}

float calculatePSNR2D(unsigned char ** image2DTarget, unsigned char ** image2D, int ROW,int COL) {
    unsigned int tempSum = 0;
    float psnr;
    for(int i=0; i < ROW ; i++){
        for(int j=0; j < COL; j++) {
                tempSum = tempSum+(pow((image2DTarget[i][j] - image2D[i][j]),2));
        }
    }
    psnr = 10*(log10((255*255)/(tempSum / ((float)(ROW * COL)))));
    return psnr;
}





int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 11){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [row] [col] [bytesPerPixel] [input Noise free image path]  [input Noisy image path] [output image path] [N - mask size] [Filter Name 1] [Filter Name 2] [Filter Name 3] (filter names: medianFilter, lowPassFilter, gaussianFilter, give 0 if no need of filters)" << endl;
        return 0;
    }
    
    // Store the required arguments --------
    int ROW = atoi(argv[1]);
    int COL = atoi(argv[2]);
    int BYTESPERPIXEL = atoi(argv[3]);
    long int IMAGELEN = ROW*COL*BYTESPERPIXEL;
    
    int N = atoi(argv[7]);
    
    cout << "Number of arguments passed: " << argc << endl;
    cout << "BytesPerPixel: " << BYTESPERPIXEL << endl;
    cout << "Row: " << ROW << endl;
    cout << "Col: " << COL << endl;
    cout << "File length: " << IMAGELEN << endl;
    cout << "Processing File: " << argv[4] << endl;
    cout << "-----------------------" << endl;
    
    // Declare required input and output datastructures ---------
    unsigned char *imageFromFileTarget = new unsigned char [IMAGELEN]();
    unsigned char *imageFromFile = new unsigned char [IMAGELEN]();
    unsigned char *imageToFile = new unsigned char [IMAGELEN]();
    
    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFileTarget, IMAGELEN);
    fileRead(argv[5], imageFromFile, IMAGELEN);
    
    // Declare and allocate memoory for the images --------
    unsigned char *** image3D = NULL;
    image3D = image1Dto3D(image3D, imageFromFile, ROW, COL, BYTESPERPIXEL);

    unsigned char *** image3DTarget = NULL;
    image3DTarget = image1Dto3D(image3DTarget, imageFromFileTarget, ROW, COL, BYTESPERPIXEL);

    unsigned char *** image3DDenoised = NULL;
    image3DDenoised = allocMemory3D(image3DDenoised, ROW, COL, BYTESPERPIXEL);
    
    unsigned char ** image2DRChannel = NULL;
    image2DRChannel = seperateChannels(image3D, image2DRChannel, ROW, COL, 0);
    
    unsigned char ** image2DGChannel = NULL;
    image2DGChannel = seperateChannels(image3D, image2DGChannel, ROW, COL, 1);
    
    unsigned char ** image2DBChannel = NULL;
    image2DBChannel = seperateChannels(image3D, image2DBChannel, ROW, COL, 2);
    
    unsigned char ** image2DRChannelTarget = NULL;
    image2DRChannelTarget = seperateChannels(image3DTarget, image2DRChannelTarget, ROW, COL, 0);
    
    unsigned char ** image2DGChannelTarget = NULL;
    image2DGChannelTarget = seperateChannels(image3DTarget, image2DGChannelTarget, ROW, COL, 1);
    
    unsigned char ** image2DBChannelTarget = NULL;
    image2DBChannelTarget = seperateChannels(image3DTarget, image2DBChannelTarget, ROW, COL, 2);
    
    unsigned char ** image2DRChannelDenoised = NULL;
    image2DRChannelDenoised = allocMemory2D( image2DRChannelDenoised, ROW, COL);
    
    unsigned char ** image2DGChannelDenoised = NULL;
    image2DGChannelDenoised = allocMemory2D(image2DGChannelDenoised, ROW, COL);
    
    unsigned char ** image2DBChannelDenoised = NULL;
    image2DBChannelDenoised = allocMemory2D(image2DBChannelDenoised, ROW, COL);

    // Masking using Filters
    // Temporarily assigning image pixel values to denoised image arrays
    for(int i=0; i< ROW; i++) {
        for(int j=0; j < COL; j++) {
            image2DRChannelDenoised[i][j] = image2DRChannel[i][j];
            image2DGChannelDenoised[i][j] = image2DGChannel[i][j];
            image2DBChannelDenoised[i][j] = image2DBChannel[i][j];
        }
    }
    
    cout << " Denoising begins -- Mask size given: " << N << endl;
    for(int filterNameIndex = 8; filterNameIndex <= 10; filterNameIndex++) {
        if(strcmp(argv[filterNameIndex],"medianFilter") == 0){
            cout << "Denoising Using Median Filter ---" << endl;
            image2DRChannelDenoised = medianFilter(image2DRChannelDenoised, image2DRChannelDenoised, ROW, COL, N);
            image2DGChannelDenoised = medianFilter(image2DGChannelDenoised, image2DGChannelDenoised, ROW, COL, N);
            image2DBChannelDenoised = medianFilter(image2DBChannelDenoised, image2DBChannelDenoised, ROW, COL, N);
        }
        else if(strcmp(argv[filterNameIndex],"lowPassFilter") == 0){
            cout << "Denoising Using Low Pass Filter Filter ---" << endl;
            image2DRChannelDenoised = lowPassFilter(image2DRChannelDenoised, image2DRChannelDenoised, ROW, COL, N);
            image2DGChannelDenoised = lowPassFilter(image2DGChannelDenoised, image2DGChannelDenoised, ROW, COL, N);
            image2DBChannelDenoised = lowPassFilter(image2DBChannelDenoised, image2DBChannelDenoised, ROW, COL, N);
        }
        else if(strcmp(argv[filterNameIndex],"gaussianFilter") == 0) {
            cout << "Denoising Using Gaussian Filter ---" << endl;
            image2DRChannelDenoised = gaussianFilter(image2DRChannelDenoised, image2DRChannelDenoised, ROW, COL, N);
            image2DGChannelDenoised = gaussianFilter(image2DGChannelDenoised, image2DGChannelDenoised, ROW, COL, N);
            image2DBChannelDenoised = gaussianFilter(image2DBChannelDenoised, image2DBChannelDenoised, ROW, COL, N);
        }
    }
    
    // Form 3D image from Denoised R, G, B - 2D images
    image3DDenoised = combineChannels(image3DDenoised, image2DRChannelDenoised, image2DGChannelDenoised, image2DBChannelDenoised, ROW, COL, BYTESPERPIXEL);
    
    float psnr_rchannel;
    float psnr_gchannel;
    float psnr_bchannel;
    float psnr;
    psnr_rchannel = calculatePSNR2D(image2DRChannelTarget, image2DRChannelDenoised, ROW,COL);
    psnr_gchannel = calculatePSNR2D(image2DGChannelTarget, image2DGChannelDenoised, ROW,COL);
    psnr_bchannel = calculatePSNR2D(image2DBChannelTarget, image2DBChannelDenoised, ROW,COL);
    psnr = calculatePSNR3D(image3DTarget, image3DDenoised, ROW,COL,BYTESPERPIXEL);
    cout << "PSNR of R Channel: " << psnr_rchannel << endl;
    cout << "PSNR of G Channel: " << psnr_gchannel << endl;
    cout << "PSNR of B Channel: " << psnr_bchannel << endl;
    cout << "PSNR of the Image: " << psnr << endl;
    
    
    // Write outputs to the Raw files --------
    image3Dto1D(image3DDenoised, imageToFile, ROW, COL, BYTESPERPIXEL);
    fileWrite(argv[6], imageToFile, IMAGELEN);
    
}

