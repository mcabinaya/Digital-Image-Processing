//
//  main.cpp
//  hw_1_prob_1_a2
//
//  Created by Abinaya Manimaran on 1/19/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "DIP_MyHeaderFile.h"

using namespace std;

int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 9){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [row] [col] [bytesPerPixel]  [input image path] [raw output image 1 path] [raw output image 2 path] [raw output image 3 path] [raw output image 4 path] " << endl;
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
    unsigned char *imageCyanToFile = new unsigned char [imageLen]();
    unsigned char *imageMagentaToFile = new unsigned char [imageLen]();
    unsigned char *imageYellowToFile = new unsigned char [imageLen]();
    unsigned char *imageCMYToFile = new unsigned char [imageLen]();
    
    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFile, imageLen);
    
    // Declare and allocate memoory for the images --------
    unsigned char *** image3D = NULL;
    image3D = image1Dto3D(image3D, imageFromFile, row, col, bytesPerPixel);
    
    unsigned char *** image3DCMY = NULL;
    image3DCMY = allocMemory3D(image3DCMY, row, col, bytesPerPixel);
    
    unsigned char ** image2DCyan = NULL;
    image2DCyan = allocMemory2D(image2DCyan, row, col);
    
    unsigned char ** image2DMagenta = NULL;
    image2DMagenta = allocMemory2D(image2DMagenta, row, col);
    
    unsigned char ** image2DYellow = NULL;
    image2DYellow = allocMemory2D(image2DYellow, row, col);
    
    // Cyan - Magenta - Yellow conversion and seperation --------
    for(int i=0; i<row; i++){
        for(int j=0; j< col; j++) {
            unsigned char cValue = 255 - image3D[i][j][0];
            unsigned char mValue = 255 - image3D[i][j][1];
            unsigned char yValue = 255 - image3D[i][j][2];
            
            image2DCyan[i][j] = cValue;
            image2DMagenta[i][j] = mValue;
            image2DYellow[i][j] = yValue;
        }
    }
    
    //Combine C, M and Y channels
    image3DCMY = combineChannels(image3DCMY, image2DCyan, image2DMagenta, image2DYellow, row, col, bytesPerPixel);
    
    // Write outputs to the Raw files --------
    image2Dto1D(image2DCyan, imageCyanToFile, row, col);
    fileWrite(argv[5], imageCyanToFile, imageLen);
    
    image2Dto1D(image2DMagenta, imageMagentaToFile, row, col);
    fileWrite(argv[6], imageMagentaToFile, imageLen);
    
    image2Dto1D(image2DYellow, imageYellowToFile, row, col);
    fileWrite(argv[7], imageYellowToFile, imageLen);
    
    image3Dto1D(image3DCMY, imageCMYToFile, row, col, bytesPerPixel);
    fileWrite(argv[8], imageCMYToFile, imageLen);
    
    // Deallocate all the other memories used --------
    freeMemory3D(image3D, row, col, bytesPerPixel);
    freeMemory2D(image2DCyan,row,col);
    freeMemory2D(image2DMagenta,row,col);
    freeMemory2D(image2DYellow,row,col);
    delete[] imageFromFile;
    delete[] imageCyanToFile;
    delete[] imageMagentaToFile;
    delete[] imageYellowToFile;
    
}

