//
//  main.cpp
//  hw_3_prob_2_a2
//
//  Created by Abinaya Manimaran on 3/18/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <map>
#include "DIP_MyHeaderFile.h"
using namespace std;

class zeroCrossingEdgeDetection {
public:
    int ROW;
    int COL;
    int BYTESPERPIXEL;
    unsigned char *** image3D;
    unsigned char ** image2D;
    long double * lOGMask;
    int MASKSIZE;
    
    long double ** image2DGradientMagnitude;
    unsigned char ** image2DGradientMagnitudeNormalized;
    long double ** image2DThresholded;
    unsigned char ** image2DThresholdedGraylevel;
    unsigned char ** image2DEdges;

    zeroCrossingEdgeDetection(unsigned char *** inpImage3D, long double *inplOGMask,  int inpMASKSIZE, int inpROW, int inpCOL, int inpBYTESPERPIXEL) {
        ROW = inpROW;
        COL = inpCOL;
        BYTESPERPIXEL = inpBYTESPERPIXEL;
        image3D = inpImage3D;
        image2D = allocMemory2D(image2D, ROW, COL);
        lOGMask = inplOGMask;
        MASKSIZE = inpMASKSIZE;
        
        image2DGradientMagnitude = allocMemory2DLongDouble(image2DGradientMagnitude, ROW, COL);
        image2DGradientMagnitudeNormalized = allocMemory2D(image2DGradientMagnitudeNormalized, ROW, COL);
        image2DThresholded = allocMemory2DLongDouble(image2DThresholded, ROW, COL);
        image2DThresholdedGraylevel = allocMemory2D(image2DThresholdedGraylevel, ROW, COL);
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
    
    void getGradientMagnitude() {
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
                long double tempConvolveSum = 0;
                for(int l=0; l<MASKSIZE*MASKSIZE; l++) {
                    tempConvolveSum = tempConvolveSum + (tempPixelArray[l] * lOGMask[(MASKSIZE*MASKSIZE)-l-1]);
                }
                image2DGradientMagnitude[i][j] = tempConvolveSum;
                //cout << image2DGradientMagnitude[i][j] << endl;
            }
        }
    }
    
    void normalizeGradients(){
        long double minGradientMagnitude = image2DGradientMagnitude[0][0];
        long double maxGradientMagnitude = image2DGradientMagnitude[0][0];
        for(int i=0; i<ROW; i++) {
            for(int j=0; j<COL; j++) {
                if(image2DGradientMagnitude[i][j] < minGradientMagnitude) {
                    minGradientMagnitude = image2DGradientMagnitude[i][j];
                }
                if(image2DGradientMagnitude[i][j] > maxGradientMagnitude) {
                    maxGradientMagnitude = image2DGradientMagnitude[i][j];
                }
                
            }
        }
        cout << "Min Max " << minGradientMagnitude << ' ' << maxGradientMagnitude << endl;
        for(int i=0; i<ROW; i++) {
            for(int j=0; j<COL; j++) {
                image2DGradientMagnitudeNormalized[i][j] = (unsigned char)(((image2DGradientMagnitude[i][j] - minGradientMagnitude)/(maxGradientMagnitude - minGradientMagnitude)) * 255.0);
            }
        }
    }
    
    void getDoubleThresholdedImage(int THRESHOLD1, int THRESHOLD2) {
        for(int i=0; i<ROW; i++) {
            for(int j=0; j<COL; j++) {
                if(image2DGradientMagnitudeNormalized[i][j] <= THRESHOLD1) {
                    image2DThresholded[i][j] = -1;
                    image2DThresholdedGraylevel[i][j] = 64;
                }
                else if((image2DGradientMagnitudeNormalized[i][j] > THRESHOLD1) and (image2DGradientMagnitudeNormalized[i][j] <= THRESHOLD2)) {
                    image2DThresholded[i][j] = 0;
                    image2DThresholdedGraylevel[i][j] = 128;
                }
                else{
                    image2DThresholded[i][j] = 1;
                    image2DThresholdedGraylevel[i][j] = 192;
                }
            }
        }
    }
    
    void detectZeroCrossing_book(){
        map < int, int > oppIndex;
        oppIndex[0] = 8;
        oppIndex[1] = 7;
        oppIndex[2] = 6;
        oppIndex[3] = 5;
        
        signed int startN = - floor(3/2.0);
        signed int endN =  floor(3/2.0);
        
        for(int i=1; i<ROW-1; i++) {
            for(int j=1; j<COL-1; j++) {
                long double * tempPixelArray = new long double [9]();
                int tempCount = 0;
                image2DEdges[i][j] = 255;
                // Get the 5*5 sub matrices and store it in 1D
                for(signed int p = startN ; p <= endN ; p ++) {
                    for(signed int q = startN ; q <= endN ; q ++) {
                        signed int rowIndex = i + p;
                        signed int colIndex = j + q;
                        long double tempPixel;
                        //if((rowIndex < 0) or (colIndex < 0) or (rowIndex > ROW-1) or (colIndex > COL-1)){
                         //   tempPixel = 0;}
                        //else{
                            tempPixel = image2DThresholded[rowIndex][colIndex];
                        
                          // }
                        tempPixelArray[tempCount] = tempPixel;
                        //cout << "TempArr " << tempPixel << ' ' << tempPixelArray[tempCount] << endl;
                        tempCount++;
                    }
                }
                if(image2DThresholded[i][j] >= 0) {
                    if((tempPixelArray[1]>0) and (tempPixelArray[3]>0) and (tempPixelArray[5]<0) and (tempPixelArray[7]>0)) {
                        //cout << image2DGradientMagnitude[i][j] << ' ' << tempPixelArray[1] << ' ' << tempPixelArray[3] << ' ' << tempPixelArray[5] << ' ' << tempPixelArray[7] << endl;
                        image2DEdges[i][j] = 0;}
                    if((tempPixelArray[1]<0) and (tempPixelArray[3]>0) and (tempPixelArray[5]>0) and (tempPixelArray[7]>0)) {
                        image2DEdges[i][j] = 0;}
                    if((tempPixelArray[1]>0) and (tempPixelArray[3]<0) and (tempPixelArray[5]>0) and (tempPixelArray[7]>0)) {
                        image2DEdges[i][j] = 0;}
                    if((tempPixelArray[1]>0) and (tempPixelArray[3]>0) and (tempPixelArray[5]>0) and (tempPixelArray[7]<0)) {
                        image2DEdges[i][j] = 0;}
                    
                    if((tempPixelArray[1]<0) and (tempPixelArray[3]>0) and (tempPixelArray[5]<0) and (tempPixelArray[7]>0)) {
                        image2DEdges[i][j] = 0;}
                    if((tempPixelArray[1]<0) and (tempPixelArray[3]<0) and (tempPixelArray[5]>0) and (tempPixelArray[7]>0)) {
                        image2DEdges[i][j] = 0;}
                    if((tempPixelArray[1]>0) and (tempPixelArray[3]<0) and (tempPixelArray[5]>0) and (tempPixelArray[7]<0)) {
                        image2DEdges[i][j] = 0;}
                    if((tempPixelArray[1]>0) and (tempPixelArray[3]>0) and (tempPixelArray[5]<0) and (tempPixelArray[7]<0)) {
                        image2DEdges[i][j] = 0;}
                    
                    if((tempPixelArray[1]<0) and (tempPixelArray[3]>0) and (tempPixelArray[5]<0) and (tempPixelArray[7]<0)) {
                        image2DEdges[i][j] = 0;}
                    if((tempPixelArray[1]<0) and (tempPixelArray[3]<0) and (tempPixelArray[5]<0) and (tempPixelArray[7]>0)) {
                        image2DEdges[i][j] = 0;}
                    if((tempPixelArray[1]<0) and (tempPixelArray[3]<0) and (tempPixelArray[5]>0) and (tempPixelArray[7]<0)) {
                        image2DEdges[i][j] = 0;}
                    if((tempPixelArray[1]>0) and (tempPixelArray[3]<0) and (tempPixelArray[5]<0) and (tempPixelArray[7]<0)) {
                        image2DEdges[i][j] = 0;}
                }
                else if(image2DThresholded[i][j] < 0){
                    if((tempPixelArray[1]<0) and (tempPixelArray[3]>0) and (tempPixelArray[5]<0) and (tempPixelArray[7]<0)) {
                        image2DEdges[i][j] = 0;}
                    if((tempPixelArray[1]<0) and (tempPixelArray[3]<0) and (tempPixelArray[5]<0) and (tempPixelArray[7]>0)) {
                        image2DEdges[i][j] = 0;}
                    if((tempPixelArray[1]<0) and (tempPixelArray[3]<0) and (tempPixelArray[5]>0) and (tempPixelArray[7]<0)) {
                        image2DEdges[i][j] = 0;}
                    if((tempPixelArray[1]>0) and (tempPixelArray[3]<0) and (tempPixelArray[5]<0) and (tempPixelArray[7]<0)) {
                        image2DEdges[i][j] = 0;}
                }
            }
        }
    }
    
    
    void detectZeroCrossing(){
        signed int startN = - floor(3/2.0);
        signed int endN =  floor(3/2.0);
        
        for(int i=1; i<ROW-1; i++) {
            for(int j=1; j<COL-1; j++) {
                image2DEdges[i][j] = 255;
                if (image2DThresholded[i][j] == 0) {
                    long double * tempPixelArray = new long double [9]();
                    int tempCount = 0;
                    image2DEdges[i][j] = 255;
                    // Get the 5*5 sub matrices and store it in 1D
                    for(signed int p = startN ; p <= endN ; p ++) {
                        for(signed int q = startN ; q <= endN ; q ++) {
                            signed int rowIndex = i + p;
                            signed int colIndex = j + q;
                            long double tempPixel;
                            tempPixel = image2DThresholded[rowIndex][colIndex];
                            tempPixelArray[tempCount] = tempPixel;
                            //cout << "TempArr " << tempPixel << ' ' << tempPixelArray[tempCount] << endl;
                            tempCount++;
                        }
                    }
                    for(int l=0; l<9; l++) {
                        if(tempPixelArray[l] != 0) {
                            image2DEdges[i][j] = 0;
                            break;
                        }
                    }
                }
            }
        }
    }
    
    
    
};

int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 12){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [ROW] [COL] [BYTESPERPIXEL] [input 1 image path] [input 2 image path] [output 1 image path 1] [output 1 image path 2] [output 1 image path 3]  [output 2 image path 1] [output 2 image path 2] [output 2 image path 3]" << endl;
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

    
    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFile1, IMAGELEN);
    fileRead(argv[5], imageFromFile2, IMAGELEN);
    
    // Declare input and output datastructures
    unsigned char *** image3D = NULL;
    image3D = image1Dto3D(image3D, imageFromFile1, ROW, COL, BYTESPERPIXEL);

    unsigned char *** image3DNoisy = NULL;
    image3DNoisy = image1Dto3D(image3DNoisy, imageFromFile2, ROW, COL, BYTESPERPIXEL);
    
    // Declare Masks
    //int MASKSIZE = 3;
    //long double *lOGMask = new long double [MASKSIZE*MASKSIZE]{0.0, -1.0, 0.0, -1.0, 4.0, -1.0, 0.0, -1.0, 0.0};
    //int MASKSIZE = 5;
    //long double *lOGMask = new long double [MASKSIZE*MASKSIZE]{0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 2.0, 1.0, 0.0, 1.0, 2.0, -16.0, 2.0, 1.0, 0.0, 1.0, 2.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    int MASKSIZE = 9;
    long double *lOGMask = new long double [MASKSIZE*MASKSIZE]{0.0, 1.0, 1.0, 2.0, 2.0, 2.0, 1.0, 1.0, 0.0,
                                                               1.0, 2.0, 4.0, 5.0, 5.0, 5.0, 4.0, 2.0, 1.0,
                                                               1.0, 4.0, 5.0, 3.0, 0.0, 3.0, 5.0, 4.0, 1.0,
                                                               2.0, 5.0, 3.0, -12.0, -24.0, -12.0, 3.0, 5.0, 2.0,
                                                               2.0, 5.0, 0.0, -24.0, -40.0, -24.0, 0.0, 5.0, 2.0,
                                                               2.0, 5.0, 3.0, -12.0, -24.0, -12.0, 3.0, 5.0, 2.0,
                                                               1.0, 4.0, 5.0, 3.0, 0.0, 3.0, 5.0, 4.0, 1.0,
                                                               1.0, 2.0, 4.0, 5.0, 5.0, 5.0, 4.0, 2.0, 1.0,
                                                               0.0, 1.0, 1.0, 2.0, 2.0, 2.0, 1.0, 1.0, 0.0,};

    // Declare objects and call functions of Class
    zeroCrossingEdgeDetection boatEdgeDetect = zeroCrossingEdgeDetection(image3D, lOGMask, MASKSIZE, ROW,COL,BYTESPERPIXEL);
    boatEdgeDetect.convertToGrayScale();
    boatEdgeDetect.getGradientMagnitude();
    boatEdgeDetect.normalizeGradients();
    //boatEdgeDetect.getDoubleThresholdedImage(95,103);
    //boatEdgeDetect.getDoubleThresholdedImage(132,160); // 4%
    //boatEdgeDetect.getDoubleThresholdedImage(108,187); // 1%
    //boatEdgeDetect.getDoubleThresholdedImage(143,154); // 10%
    //boatEdgeDetect.getDoubleThresholdedImage(138,156);
    //boatEdgeDetect.getDoubleThresholdedImage(116,165); // 9 mask 4%
    //boatEdgeDetect.getDoubleThresholdedImage(120,160); // 9 mask 5%
    //boatEdgeDetect.getDoubleThresholdedImage(124,158); // 9 mask 6%
    //boatEdgeDetect.getDoubleThresholdedImage(126,154); // 9 mask 7%
    //boatEdgeDetect.getDoubleThresholdedImage(128,148); // 9 mask 8%
    boatEdgeDetect.getDoubleThresholdedImage(118,147); //Animal

    boatEdgeDetect.detectZeroCrossing();
    
    // Write outputs
    image2Dto1D(boatEdgeDetect.image2DGradientMagnitudeNormalized, imageToFile1, ROW, COL);
    fileWrite(argv[6], imageToFile1, ROW*COL);
    
    image2Dto1D(boatEdgeDetect.image2DThresholdedGraylevel, imageToFile2, ROW, COL);
    fileWrite(argv[7], imageToFile2, ROW*COL);
    
    image2Dto1D(boatEdgeDetect.image2DEdges, imageToFile3, ROW, COL);
    fileWrite(argv[8], imageToFile3, ROW*COL);
    
    // Declare objects and call functions of Class -- Noisy image
    zeroCrossingEdgeDetection boatEdgeDetectNoisy = zeroCrossingEdgeDetection(image3DNoisy, lOGMask, MASKSIZE, ROW,COL,BYTESPERPIXEL);
    boatEdgeDetectNoisy.convertToGrayScale();
    boatEdgeDetectNoisy.getGradientMagnitude();
    boatEdgeDetectNoisy.normalizeGradients();
    //boatEdgeDetectNoisy.getDoubleThresholdedImage(118,157); // 9 mask 5%
    //boatEdgeDetectNoisy.getDoubleThresholdedImage(121,154); // 9 mask 6%
    //boatEdgeDetectNoisy.getDoubleThresholdedImage(124,151); // 9 mask 7%
    //boatEdgeDetectNoisy.getDoubleThresholdedImage(126,149); // 9 mask 8%
    boatEdgeDetectNoisy.getDoubleThresholdedImage(115,147); //House
    boatEdgeDetectNoisy.detectZeroCrossing();
    
    // Write outputs
    image2Dto1D(boatEdgeDetectNoisy.image2DGradientMagnitudeNormalized, imageToFile4, ROW, COL);
    fileWrite(argv[9], imageToFile4, ROW*COL);
    
    image2Dto1D(boatEdgeDetectNoisy.image2DThresholdedGraylevel, imageToFile5, ROW, COL);
    fileWrite(argv[10], imageToFile5, ROW*COL);
    
    image2Dto1D(boatEdgeDetectNoisy.image2DEdges, imageToFile6, ROW, COL);
    fileWrite(argv[11], imageToFile6, ROW*COL);
    
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
    delete [] lOGMask;

    
}

