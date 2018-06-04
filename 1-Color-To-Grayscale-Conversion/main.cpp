//
//  main.cpp
//  hw_1_prob_1_a1
//
//  Created by Abinaya Manimaran on 1/18/18.
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
    if (argc != 8){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [row] [col] [bytesPerPixel] [input image path] [raw output image 1 path] [raw output image 2 path] [raw output image 3 path]  " << endl;
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
    unsigned char *imageLightnessToFile = new unsigned char [imageLen]();
    unsigned char *imageAverageToFile = new unsigned char [imageLen]();
    unsigned char *imageLuminosityToFile = new unsigned char [imageLen]();

    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFile, imageLen);
    
    // Declare and allocate memoory for the images --------
    unsigned char *** image3D = NULL;
    image3D = image1Dto3D(image3D, imageFromFile, row, col, bytesPerPixel);
    
    unsigned char ** image2DByLightness = NULL;
    image2DByLightness = allocMemory2D(image2DByLightness, row, col);
    
    unsigned char ** image2DByAverage = NULL;
    image2DByAverage = allocMemory2D(image2DByAverage, row, col);
    
    unsigned char ** image2DByLuminosity = NULL;
    image2DByLuminosity = allocMemory2D(image2DByLuminosity, row, col);
    
    // Grayscale conversion --------
    for(int i=0; i<row; i++){
        for(int j=0; j< col; j++) {
            unsigned char rValue = image3D[i][j][0];
            unsigned char gValue = image3D[i][j][1];
            unsigned char bValue = image3D[i][j][2];
        
            unsigned char maxValue;
            unsigned char minValue;
            
            maxValue = max(rValue,gValue);
            maxValue = max(bValue,maxValue);
            
            minValue = min(rValue,gValue);
            minValue = min(bValue,minValue);
            
            image2DByLightness[i][j] = (unsigned char) ((maxValue + minValue ) / 2.0);
            image2DByAverage[i][j] = (unsigned char) ((rValue + gValue + bValue) / 3.0);
            image2DByLuminosity[i][j] = (unsigned char) (0.21 * rValue + 0.72 * gValue+ 0.07 * bValue);
        }
    }
    
    // Write outputs to the Raw files --------
    image2Dto1D(image2DByLightness, imageLightnessToFile, row, col);
    fileWrite(argv[5], imageLightnessToFile, imageLen);
    
    image2Dto1D(image2DByAverage, imageAverageToFile, row, col);
    fileWrite(argv[6], imageAverageToFile, imageLen);
    
    image2Dto1D(image2DByLuminosity, imageLuminosityToFile, row, col);
    fileWrite(argv[7], imageLuminosityToFile, imageLen);
    
    // Deallocate all the other memories used --------
    freeMemory3D(image3D, row, col, bytesPerPixel);
    freeMemory2D(image2DByLightness,row,col);
    freeMemory2D(image2DByAverage,row,col);
    freeMemory2D(image2DByLuminosity,row,col);
    delete[] imageFromFile;
    delete[] imageLightnessToFile;
    delete[] imageAverageToFile;
    delete[] imageLuminosityToFile;
    
}
