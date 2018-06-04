//
//  main.cpp
//  hw_2_prob_3_b
//
//  Created by Abinaya Manimaran on 2/18/18.
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
                int bondSize = returnThinBondSize(bondValue);
                //cout << bondSize << endl;
                unsigned char ** conditionalMasks = NULL;
                if (bondSize != 0) {
                    conditionalMasks = returnThinConditionalMasks(bondValue);
                    //cout << "----" << endl;
                    //if(conditionalMasks != NULL) {
                    int hitOrMiss = compareWithMask(conditionalMasks, tempPixelArray, MASKSIZE, bondSize);
                    image2DInterMed[i][j] = hitOrMiss;
                    //cout << "Final " << (int) image2DInterMed[i][j] << endl;
                }
                else { image2DInterMed[i][j] = 0;}
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
            //int j = 9;
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
unsigned char ** returnBridgedImage(unsigned char ** image2DBinary, int ROW, int COL) {
    int MASKSIZE = 3;
    signed int startN = - floor(MASKSIZE/2.0);
    signed int endN =  floor(MASKSIZE/2.0);
    
    for(int i=0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            //cout << "Second stage --" << endl;
            //int i = 178;
            //int j = 9;
            unsigned char * tempPixelArray = new unsigned char [MASKSIZE*MASKSIZE]();
            unsigned int count = 0;
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
            unsigned char X0 = tempPixelArray[5];
            unsigned char X1 = tempPixelArray[2];
            unsigned char X2 = tempPixelArray[1];
            unsigned char X3 = tempPixelArray[0];
            unsigned char X4 = tempPixelArray[3];
            unsigned char X5 = tempPixelArray[6];
            unsigned char X6 = tempPixelArray[7];
            unsigned char X7 = tempPixelArray[8];
            unsigned char X = tempPixelArray[4];
            
            unsigned char L1 = (not X) and (not X0)  and X1  and (not X2)  and X3  and (not X4)  and (not X5)  and (not X6)  and (not X7);
            unsigned char L2 = (not X) and (not X0)  and (not X1)  and (not X2)  and X3  and (not X4)  and X5  and (not X6)  and (not X7);
            unsigned char L3 = (not X) and (not X0)  and (not X1)  and (not X2)  and (not X3)  and (not X4)  and X5  and (not X6)  and X7;
            unsigned char L4 = (not X) and (not X0)  and X1  and (not X2)  and (not X3)  and (not X4)  and (not X5)  and (not X6)  and X7;
            
            unsigned char PQ = L1 or L2 or L3 or L4;
            
            unsigned char P1 = (not X2) and (not X6) and (X3 or X4 or X5) and (X0 or X1 or X7) and (not PQ);
            unsigned char P2 = (not X0) and (not X4) and (X1 or X2 or X3) and (X5 or X6 or X7) and (not PQ);
            unsigned char P3 = (not X0) and (not X6) and X7 and (X2 or X3 or X4);
            unsigned char P4 = (not X0) and (not X2) and X1 and (X4 or X5 or X6);
            unsigned char P5 = (not X2) and (not X4) and X3 and (X0 or X6 or X7);
            unsigned char P6 = (not X4) and (not X6) and X5 and (X0 or X1 or X2);
            
            image2DBinary[i][j] = X or (P1 or P2 or P3 or P4 or P5 or P6);
        }
    }
    return image2DBinary;
}


int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 8){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [row] [col] [bytesPerPixel]  [input Jigsaw image path] [output Binary image path] [output First Stage image path] [output Second Stage image path]" << endl;
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
    
    //Invert the Image since the Algorithm works with 1's as FG and 0's as BG
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            if( image2DBinary[i][j] == 255) {
                image2DBinary[i][j] = 0; }
            else { image2DBinary[i][j] = 1;}
        }
    }
    
    //First stage and Second stage implementation
    int ITERATIONS = 35;
    for(int i = 0; i < ITERATIONS; i++) {
        image2DInterMed = returnFirstStage(image2DInterMed, image2DBinary, ROW, COL);
        image2DBinary = returnSecondStage(image2DBinary,image2DInterMed,ROW,COL);
    }
    
    // Bridging
    image2DBinary = returnBridgedImage(image2DBinary, ROW, COL);
    
    
    // Changeing 1's to 255 for viewing purpose
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            //if( image2DBinary[i][j] == 0) {
              //  image2DBinary[i][j] = 255; }
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
    
    //Deallocate all memories
    freeMemory2D(image2D, ROW, COL);
    freeMemory2D(image2DBinary, ROW, COL);
    freeMemory2D(image2DInterMed, ROW, COL);
    
    delete [] imageFromFile;
    delete [] imageToFileBinary;
    delete [] imageToFileInterMed;
    delete [] imageToFileFinal;
    
}


