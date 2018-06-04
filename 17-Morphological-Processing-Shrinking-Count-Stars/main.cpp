//
//  main.cpp
//  hw_2_prob_3_a
//
//  Created by Abinaya Manimaran on 2/17/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include "DIP_MyHeaderFile.h"
#include "STKMasks.h"

using namespace std;

int compareWithMask(unsigned char ** masks, unsigned char * tempPixelArray, int MASKSIZE, int noOfMasks) {
    int checkFlag = 0;
    int orFlag = 0;
    int orCheckFlag = 0;
    for(int l=0; l < noOfMasks; l++){
        checkFlag = 1;
        //cout << "loop begins " << checkFlag <<  ' ' << l << endl;
        orFlag = 0;
        orCheckFlag = 0;
        for(int m=0; m < MASKSIZE*MASKSIZE; m++) {
            //cout << "Mask index " << m << endl;
            //cout << (int)tempPixelArray[m] << ' ' << (int)masks[l][m] << endl;
            if(masks[l][m] != 'd') {
                if((masks[l][m] == 'a') or (masks[l][m] == 'b') or (masks[l][m] == 'c')) {
                    orFlag = orFlag or tempPixelArray[m];
                    orCheckFlag = 1;
                    //cout << "Or flag true " << orFlag << endl;

                }
                else {
                    if(tempPixelArray[m] != masks[l][m]) {
                        checkFlag = 0; break;
                    }
                }
            }
        }
        if ((orCheckFlag == 1)  & (orFlag != 1)) { checkFlag = 0; }
        //cout << "loop ends " << checkFlag << endl;
        if (checkFlag == 1){
            break;
        }
    }
    //cout << "Final " << checkFlag<< endl;
    return checkFlag;
}

unsigned char ** returnFirstStage(unsigned char ** image2DInterMed, unsigned char ** image2DBinary, int ROW, int COL ) {
    int MASKSIZE = 3;
    signed int startN = - floor(MASKSIZE/2.0);
    signed int endN =  floor(MASKSIZE/2.0);
    
    for(int i=0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            //int i = 180;
            //int j = 9;
            unsigned char * tempPixelArray = new unsigned char [MASKSIZE*MASKSIZE]();
            unsigned int count = 0;
            if(image2DBinary[i][j] != 0) {
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
                        tempPixelArray[count] = image2DBinary[rowIndex][colIndex];
                        //cout << (int) tempPixelArray[count] << endl;
                        count ++ ;
                    }
                }
                int bondValue = returnBondValue(tempPixelArray);
                //cout << bondValue << endl;
                int bondSize = returnShrinkBondSize(bondValue);
                unsigned char ** conditionalMasks = NULL;
                //cout << bondSize << endl;
                if(bondSize != 0) {
                    conditionalMasks = returnShrinkConditionalMasks(bondValue);
                    //cout << "----" << endl;
                    int hitOrMiss = compareWithMask(conditionalMasks, tempPixelArray, MASKSIZE, bondSize);
                    image2DInterMed[i][j] = hitOrMiss;
                }
                else { image2DInterMed[i][j] = 0;}
                //cout << "Final " << (int) image2DInterMed[i][j] << endl;
            }
            else{image2DInterMed[i][j] = 0;}
        }
    }
    return image2DInterMed;
}


unsigned char ** returnSecondStage(unsigned char ** image2DOutput, unsigned char ** image2DInterMed, int ROW, int COL ) {
    int MASKSIZE = 3;
    signed int startN = - floor(MASKSIZE/2.0);
    signed int endN =  floor(MASKSIZE/2.0);
    
    for(int i=0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            //cout << "Second stage --" << endl;
            //int i = 178;
            //int j = 10;
            unsigned char * tempPixelArray = new unsigned char [MASKSIZE*MASKSIZE]();
            unsigned int count = 0;
            if(image2DInterMed[i][j] != 0) {
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
                        tempPixelArray[count] = image2DInterMed[rowIndex][colIndex];
                        //cout << (int) tempPixelArray[count] << endl;
                        count ++ ;
                    }
                }
                unsigned char ** unConditionalMasks = NULL;
                unConditionalMasks = returnShrinkThinUnconditionalMasks();
                //cout << "----" << endl;
                int hitOrMiss = compareWithMask(unConditionalMasks, tempPixelArray, MASKSIZE, 37);
                if(hitOrMiss == 0) {
                   image2DOutput[i][j] = 0;
                }
                
                //cout << "Final " << hitOrMiss << ' ' << (int) image2DOutput[i][j] << endl;
            }
        }
    }
    return image2DOutput;
}

unsigned int checkCount(unsigned char ** image2D, int ROW, int COL) {
    int MASKSIZE = 3;
    signed int startN = - floor(MASKSIZE/2.0);
    signed int endN =  floor(MASKSIZE/2.0);
    unsigned int iterCount = 0;
    for(int i=0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            unsigned int count = 0;
            if(image2D[i][j] != 0) {
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
                        unsigned char temppixel = image2D[rowIndex][colIndex];
                        if (temppixel == 1) { count ++; }
                    }
                }
                if( count == 1) { iterCount ++; }
            }
        }
    }
    return iterCount;
}




int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 8){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [row] [col] [bytesPerPixel]  [input stars image path] [output Binary image path] [output First Stage image path] [output Second Stage image path]" << endl;
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
    unsigned char *imageToFileBinary = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileInterMed = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileFinal = new unsigned char [IMAGELEN]();

    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFile, IMAGELEN);
    
    // Declare and allocate memoory for the images --------
    unsigned char ** image2D = NULL;
    image2D = image1Dto2D(image2D, imageFromFile, ROW, COL);
    
    unsigned char ** image2DBinary = NULL;
    image2DBinary = allocMemory2D(image2DBinary, ROW, COL);
    
    unsigned char ** image2DInterMed = NULL;
    image2DInterMed = allocMemory2D(image2DInterMed, ROW, COL);
    
    // Binarize the Image by Fixed Thresholding
    int THRESHOLD = 127;
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            if (image2D[i][j] <= THRESHOLD) {
                image2DBinary[i][j] = 0;
            }
            else { image2DBinary[i][j] = 255;}
        }
    }
    
    // Write Binary output to the Raw files --------
    image2Dto1D(image2DBinary, imageToFileBinary, ROW, COL);
    fileWrite(argv[5], imageToFileBinary, IMAGELEN);

    // Converting the Image to 0's and 1's for the algorithm to work
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            if( image2DBinary[i][j] == 255) {
                image2DBinary[i][j] = 1; }
        }
    }
   
    int ITERATIONS = 15;
    unsigned int * totalCount = new unsigned int [ITERATIONS]();
    unsigned int * iterationsCount = new unsigned int [ITERATIONS]();
    for(int i = 0; i < ITERATIONS; i++) {
        image2DInterMed = returnFirstStage(image2DInterMed, image2DBinary, ROW, COL);
        image2DBinary = returnSecondStage(image2DBinary,image2DInterMed,ROW,COL);
        unsigned int tempCount = checkCount(image2DBinary, ROW, COL);
        iterationsCount[i] = tempCount;
        if (i != 0) {
            totalCount[i] = tempCount - iterationsCount[i-1]; }
        else { totalCount[i] = tempCount; }
        cout << "---------" << endl;
        cout << "Star size: " << i+1 << ' ' << "Count: " << totalCount[i] << endl;
        cout << "Total count until this iteration: " << iterationsCount[i] << endl;
    }
    
   
    // Changeing 1's to 255 for viewing purpose
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            if( image2DBinary[i][j] == 1) {
                image2DBinary[i][j] = 255; }
            if(image2DInterMed[i][j] == 1) {
                image2DInterMed[i][j] = 255;
            }
        }
    }
    
   
    // Writing the Final iteration First stage and Second Stage output
    image2Dto1D(image2DInterMed, imageToFileInterMed, ROW, COL);
    fileWrite(argv[6], imageToFileInterMed, IMAGELEN);
    
    image2Dto1D(image2DBinary, imageToFileFinal, ROW, COL);
    fileWrite(argv[7], imageToFileFinal, IMAGELEN);
 
    // De allocate all the memories
    delete [] imageFromFile;
    delete [] imageToFileBinary;
    delete [] imageToFileInterMed;
    delete [] imageToFileFinal;
    delete []  totalCount;
    delete [] iterationsCount;
    
    freeMemory2D(image2D, ROW, COL);
    freeMemory2D(image2DBinary, ROW, COL);
    freeMemory2D(image2DInterMed, ROW, COL);

}

