//
//  main.cpp
//  hw_1_prob_1_b
//
//  Created by Abinaya Manimaran on 1/19/18.
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
    if (argc != 8){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [row] [col] [bytesPerPixel] [input image path] [raw output image 1 path] [resize row] [resize col]  " << endl;
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
    
    int resizeRow = atoi(argv[6]);
    int resizeCol = atoi(argv[7]);
    
    // Declare required input and output datastructures ---------
    unsigned char *imageFromFile = new unsigned char [imageLen]();
    unsigned char *imageResizedToFile = new unsigned char [resizeRow*resizeCol*bytesPerPixel]();
    
    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFile, imageLen);
    
    // Declare and allocate memoory for the images --------
    unsigned char *** image3D = NULL;
    image3D = image1Dto3D(image3D, imageFromFile, row, col, bytesPerPixel);
    
    unsigned char *** image3DResized = NULL;
    image3DResized = allocMemory3D(image3DResized, resizeRow, resizeCol, bytesPerPixel);
    
    // Resizing by Linear Interpolation --------
    
    float rowRatio = (float) (row)/(float) resizeRow;
    float colRatio = (float) (col)/(float) resizeCol;
    
    for(int i=0; i < resizeRow; i++) {
        for(int j=0; j < resizeCol; j++) {
            double mappedRowIndex = i * rowRatio;
            double mappedColIndex = j * colRatio;
            
            int referenceRowIndex = (int)floor(mappedRowIndex);
            int referenceColIndex = (int)floor(mappedColIndex);
            //cout << referenceRowIndex << ' ' << referenceColIndex << endl;
            
            double deltaRow = mappedRowIndex - referenceRowIndex;
            double deltaCol = mappedColIndex - referenceColIndex;
            
            
            if(referenceRowIndex >= (row - 1)){
                referenceRowIndex = referenceRowIndex - 1;
            }
            if(referenceColIndex >= (col - 1)){
                referenceColIndex = referenceColIndex - 1;
            }
    
            for(int k=0; k < bytesPerPixel; k++) {
                
                image3DResized[i][j][k] = (unsigned char)((image3D[referenceRowIndex][referenceColIndex][k] * (1 - deltaRow) * (1 - deltaCol)) +
                                        (image3D[referenceRowIndex+1][referenceColIndex][k] * (deltaRow) * (1 - deltaCol)) +
                                      (image3D[referenceRowIndex][referenceColIndex+1][k] * (1 - deltaRow) *  (deltaCol)) +
                                      (image3D[referenceRowIndex+1][referenceColIndex+1][k] * (deltaRow) * (deltaCol)));
            }
            //cout << (int) image3DResized[i][j][0] << ' ' <<(int) image3DResized[i][j][1] << ' ' << (int)image3DResized[i][j][2] << endl;
        }
    }
    
    // Write outputs to the Raw files --------
    image3Dto1D(image3DResized, imageResizedToFile, resizeRow, resizeCol, bytesPerPixel);
    fileWrite(argv[5], imageResizedToFile, resizeRow*resizeCol*bytesPerPixel);
    
    // Deallocate all the other memories used --------
    freeMemory3D(image3D, row, col, bytesPerPixel);
    freeMemory3D(image3DResized,resizeRow,resizeCol, bytesPerPixel);
    delete[] imageFromFile;
    delete[] imageResizedToFile;
}


