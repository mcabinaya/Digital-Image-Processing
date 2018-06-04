//
//  main.cpp
//  hw_3_prob_2_a
//
//  Created by Abinaya Manimaran on 3/17/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include "DIP_MyHeaderFile.h"
using namespace std;

class sobelEdgeDetection {
    public:
    int ROW;
    int COL;
    int BYTESPERPIXEL;
    unsigned char *** image3D;
    unsigned char ** image2D;
    long double * gXMask;
    long double * gYMask;
    int MASKSIZE;
    
    long double ** image2DXGradient;
    long double ** image2DYGradient;
    long double ** image2DGradientMagnitude;
    unsigned char ** image2DXGradientNormalized;
    unsigned char ** image2DYGradientNormalized;
    unsigned char ** image2DGradientMagnitudeNormalized;
    unsigned char ** image2DEdges;

    sobelEdgeDetection(unsigned char *** inpImage3D, long double *inpgXMask, long double *inpgyMask, int inpMASKSIZE, int inpROW, int inpCOL, int inpBYTESPERPIXEL) {
        ROW = inpROW;
        COL = inpCOL;
        BYTESPERPIXEL = inpBYTESPERPIXEL;
        image3D = inpImage3D;
        image2D = allocMemory2D(image2D, ROW, COL);
        gXMask = inpgXMask;
        gYMask = inpgyMask;
        MASKSIZE = inpMASKSIZE;
        
        image2DXGradient = allocMemory2DLongDouble(image2DXGradient, ROW, COL);
        image2DYGradient = allocMemory2DLongDouble(image2DYGradient, ROW, COL);
        image2DGradientMagnitude = allocMemory2DLongDouble(image2DGradientMagnitude, ROW, COL);
        image2DXGradientNormalized = allocMemory2D(image2DXGradientNormalized, ROW, COL);
        image2DYGradientNormalized = allocMemory2D(image2DYGradientNormalized, ROW, COL);
        image2DGradientMagnitudeNormalized = allocMemory2D(image2DGradientMagnitudeNormalized, ROW, COL);
        image2DEdges = allocMemory2D(image2DEdges, ROW, COL);
    }
    
    void convertToGrayScale() {
        // Gray scale conversion by Luminosity
        for(int i=0; i<ROW; i++){
            for(int j=0; j< COL; j++) {
                long double rValue = image3D[i][j][0];
                long double gValue = image3D[i][j][1];
                long double bValue = image3D[i][j][2];
                image2D[i][j] = (unsigned char) (0.21 * rValue + 0.72 * gValue+ 0.07 * bValue);
                //cout << (int) image3D[i][j][0] << ' ' << (int) image3D[i][j][1] << ' ' << (int) image3D[i][j][2] << ' '  << (int) image2D[i][j] <<endl;
            }
        }
    }
    
    void getGradients() {
        signed int startN = - floor(MASKSIZE/2.0);
        signed int endN =  floor(MASKSIZE/2.0);
        
        // Traverse through ROW and COL of every image
        for (int i = 0; i < ROW; i ++){
            for (int j = 0; j < COL; j++) {
                //int i=0; int j=2;
                long double * tempPixelArray = new long double [MASKSIZE*MASKSIZE]();
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
                        long double tempPixel = (long double) image2D[rowIndex][colIndex];
                        tempPixelArray[tempCount] = tempPixel;
                        //cout << "TempArr " << tempPixel << ' ' << tempPixelArray[tempCount] << endl;
                        tempCount++;
                    }
                }
                
                // Convolute with X Filter
                long double tempConvolvegXSum = 0;
                long double tempConvolvegYSum = 0;
                for(int l=0; l<MASKSIZE*MASKSIZE; l++) {
                    tempConvolvegXSum = tempConvolvegXSum + (tempPixelArray[l] * gXMask[(MASKSIZE*MASKSIZE)-l-1]);
                    tempConvolvegYSum = tempConvolvegYSum + (tempPixelArray[l] * gYMask[(MASKSIZE*MASKSIZE)-l-1]);
                }
                image2DXGradient[i][j] = tempConvolvegXSum;
                image2DYGradient[i][j] = tempConvolvegYSum;
                //cout << image2DXGradient[i][j] << ' ' << image2DYGradient[i][j] << endl;
            }
        }
    }
    
    void getGradientMagnitude(){
        for (int i = 0; i < ROW; i ++){
            for (int j = 0; j < COL; j++) {
                image2DGradientMagnitude[i][j] = sqrt((pow(image2DXGradient[i][j],2) + pow(image2DYGradient[i][j], 2)));
                //cout << i << ' ' << j << ' ' << image2DXGradient[i][j] << ' ' << image2DYGradient[i][j] << ' ' << image2DGradientMagnitude[i][j] << endl;
            }
        }
    }
    
    void normalizeGradients(){
        long double minXGradient = image2DXGradient[0][0];
        long double maxXGradient = image2DXGradient[0][0];
        long double minYGradient = image2DYGradient[0][0];
        long double maxYGradient = image2DYGradient[0][0];
        long double minGradientMagnitude = image2DGradientMagnitude[0][0];
        long double maxGradientMagnitude = image2DGradientMagnitude[0][0];
        for(int i=0; i<ROW; i++) {
            for(int j=0; j<COL; j++) {
                if(image2DXGradient[i][j] < minXGradient) {
                    minXGradient = image2DXGradient[i][j];
                }
                if(image2DXGradient[i][j] > maxXGradient) {
                    maxXGradient = image2DXGradient[i][j];
                }
                if(image2DYGradient[i][j] < minYGradient) {
                    minYGradient = image2DYGradient[i][j];
                }
                if(image2DYGradient[i][j] > maxYGradient) {
                    maxYGradient = image2DYGradient[i][j];
                }
                if(image2DGradientMagnitude[i][j] < minGradientMagnitude) {
                    minGradientMagnitude = image2DGradientMagnitude[i][j];
                }
                if(image2DGradientMagnitude[i][j] > maxGradientMagnitude) {
                    maxGradientMagnitude = image2DGradientMagnitude[i][j];
                }
                
            }
        }
        cout << "Min Max " << minXGradient << ' ' << maxXGradient << endl;
        cout << "Min Max " << minYGradient << ' ' << maxYGradient << endl;
        cout << "Min Max " << minGradientMagnitude << ' ' << maxGradientMagnitude << endl;
        for(int i=0; i<ROW; i++) {
            for(int j=0; j<COL; j++) {
                image2DXGradientNormalized[i][j] = (unsigned char)(((image2DXGradient[i][j] - minXGradient)/(maxXGradient - minXGradient)) * 255.0);
                image2DYGradientNormalized[i][j] = (unsigned char)(((image2DYGradient[i][j] - minYGradient)/(maxYGradient - minYGradient)) * 255.0);
                image2DGradientMagnitudeNormalized[i][j] = (unsigned char)(((image2DGradientMagnitude[i][j] - minGradientMagnitude)/(maxGradientMagnitude - minGradientMagnitude)) * 255.0);
            }
        }
    }
    
    void thresholdForEdges(unsigned char THRESHOLD){
        cout << "Chosen Threshold " << (int)THRESHOLD << endl;
        for(int i=0; i<ROW; i++) {
            for(int j=0; j<COL; j++) {
                if(image2DGradientMagnitudeNormalized[i][j] > THRESHOLD) {
                    image2DEdges[i][j] = 0;
                 }
                else { image2DEdges[i][j] = 255;}
            }
        }
        
    }
    
    
    
};

int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 14){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [ROW] [COL] [BYTESPERPIXEL] [input 1 image path] [output 1 image path 1] [output 1 image path 2] [output 1 image path 3] [output 1 image path 4] [input 2 image path] [output 2 image path 1] [output 2 image path 2] [output 2 image path 3] [output 2 image path 4]" << endl;
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
    unsigned char *imageFromFile1 = new unsigned char [IMAGELEN]();
    unsigned char *imageFromFile2 = new unsigned char [IMAGELEN]();
    unsigned char *imageToFile1 = new unsigned char [IMAGELEN]();
    unsigned char *imageToFile2 = new unsigned char [IMAGELEN]();
    unsigned char *imageToFile3 = new unsigned char [IMAGELEN]();
    unsigned char *imageToFile4 = new unsigned char [IMAGELEN]();
    unsigned char *imageToFile5 = new unsigned char [IMAGELEN]();
    unsigned char *imageToFile6 = new unsigned char [IMAGELEN]();
    unsigned char *imageToFile7 = new unsigned char [IMAGELEN]();
    unsigned char *imageToFile8 = new unsigned char [IMAGELEN]();

    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFile1, IMAGELEN);
    fileRead(argv[9], imageFromFile2, IMAGELEN);

    // Declare input and output datastructures
    unsigned char *** image3D = NULL;
    image3D = image1Dto3D(image3D, imageFromFile1, ROW, COL, BYTESPERPIXEL);
    
    unsigned char *** image3DNoisy = NULL;
    image3DNoisy = image1Dto3D(image3DNoisy, imageFromFile2, ROW, COL, BYTESPERPIXEL);
    
    // Declare Masks
    int MASKSIZE = 3;
    long double *gXMask = new long double [MASKSIZE*MASKSIZE]{-1.0, 0.0, 1.0, -2.0, 0.0, 2.0, -1.0, 0.0, 1.0};
    long double *gYMask = new long double [MASKSIZE*MASKSIZE]{1.0, 2.0, 1.0, 0.0, 0.0, 0.0, -1.0, -2.0, -1.0};
    
    // Declare objects and call functions of Class
    sobelEdgeDetection boatEdgeDetect = sobelEdgeDetection(image3D,gXMask, gYMask, MASKSIZE, ROW,COL,BYTESPERPIXEL);
    boatEdgeDetect.convertToGrayScale();
    boatEdgeDetect.getGradients();
    boatEdgeDetect.getGradientMagnitude();
    boatEdgeDetect.normalizeGradients();
    //boatEdgeDetect.thresholdForEdges(130);
    boatEdgeDetect.thresholdForEdges(38);

    
    sobelEdgeDetection boatNoisyEdgeDetect = sobelEdgeDetection(image3DNoisy,gXMask, gYMask, MASKSIZE, ROW,COL,BYTESPERPIXEL);
    boatNoisyEdgeDetect.convertToGrayScale();
    boatNoisyEdgeDetect.getGradients();
    boatNoisyEdgeDetect.getGradientMagnitude();
    boatNoisyEdgeDetect.normalizeGradients();
    //boatNoisyEdgeDetect.thresholdForEdges(132);
    boatNoisyEdgeDetect.thresholdForEdges(44);

    
    // Write outputs
    image2Dto1D(boatEdgeDetect.image2DXGradientNormalized, imageToFile1, ROW, COL);
    fileWrite(argv[5], imageToFile1, IMAGELEN);
    
    image2Dto1D(boatEdgeDetect.image2DYGradientNormalized, imageToFile2, ROW, COL);
    fileWrite(argv[6], imageToFile2, IMAGELEN);
    
    image2Dto1D(boatEdgeDetect.image2DGradientMagnitudeNormalized, imageToFile3, ROW, COL);
    fileWrite(argv[7], imageToFile3, IMAGELEN);
    
    image2Dto1D(boatEdgeDetect.image2DEdges, imageToFile4, ROW, COL);
    fileWrite(argv[8], imageToFile4, IMAGELEN);
    
    image2Dto1D(boatNoisyEdgeDetect.image2DXGradientNormalized, imageToFile5, ROW, COL);
    fileWrite(argv[10], imageToFile5, IMAGELEN);
    
    image2Dto1D(boatNoisyEdgeDetect.image2DYGradientNormalized, imageToFile6, ROW, COL);
    fileWrite(argv[11], imageToFile6, IMAGELEN);
    
    image2Dto1D(boatNoisyEdgeDetect.image2DGradientMagnitudeNormalized, imageToFile7, ROW, COL);
    fileWrite(argv[12], imageToFile7, IMAGELEN);
    
    image2Dto1D(boatNoisyEdgeDetect.image2DEdges, imageToFile8, ROW, COL);
    fileWrite(argv[13], imageToFile8, IMAGELEN);
    
    // Free allocated Memories
    freeMemory3D(image3D, ROW, COL, BYTESPERPIXEL);
    freeMemory3D(image3DNoisy, ROW, COL, BYTESPERPIXEL);
    delete [] imageFromFile1;
    delete [] imageFromFile2;
    delete [] imageToFile1;
    delete [] imageToFile2;
    delete [] imageToFile3;
    delete [] imageToFile4;
    delete [] imageToFile5;
    delete [] imageToFile6;
    delete [] imageToFile7;
    delete [] imageToFile8;
    delete [] gXMask;
    delete [] gYMask;
}

