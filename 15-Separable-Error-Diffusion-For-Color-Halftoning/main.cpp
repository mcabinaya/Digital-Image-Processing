 //
//  main.cpp
//  hw_2_prob_2_c1
//
//  Created by Abinaya Manimaran on 2/25/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include "DIP_MyHeaderFile.h"
using namespace std;

unsigned char ** errorDiffusionSerpentine(unsigned char ** image2DErrorDiffusion, long double ** image2DTemp, long double *matrix, int MASKSIZE, int ROW, int COL ) {
    signed int startN = - floor(MASKSIZE/2.0);
    signed int endN =  floor(MASKSIZE/2.0);
    
    for(int i=0; i < ROW; i++){
        //int i = 2;
        if (i%2 == 0) {
            for(int j = 0; j < COL; j++){
                //int j = 6;
                long double middlePixel = image2DTemp[i][j];
                long double tobemiddlePixel;
                if(middlePixel <= 127) {
                    tobemiddlePixel = 0;
                }
                else {
                    tobemiddlePixel = 255;
                }
                
                long double errorToBeDiffused = middlePixel - tobemiddlePixel;
                image2DErrorDiffusion[i][j] = tobemiddlePixel;
                //cout << i << ' ' << j << ' ' << middlePixel << ' ' << tobemiddlePixel << ' ' << errorToBeDiffused << endl;
                
                unsigned char * tempPixelArray = new unsigned char [MASKSIZE*MASKSIZE]();
                unsigned int count = 0;
                for(signed int p = startN ; p <= endN ; p ++) {
                    for(signed int q = startN ; q <= endN ; q ++) {
                        signed int ROWIndex = i + p;
                        signed int COLIndex = j + q;
                        if((ROWIndex >= 0) and (COLIndex >= 0) and (ROWIndex <= ROW-1) and (COLIndex <= COL-1)){
                            tempPixelArray[count] = image2DTemp[ROWIndex][COLIndex];
                            image2DTemp[ROWIndex][COLIndex] = tempPixelArray[count] + (errorToBeDiffused * matrix[count]);
                            //cout << i << ' ' << j << ' ' << p << ' ' << q << ' ' << count << endl;
                            //cout << (int)tempPixelArray[count] << ' ' <<  image2DTemp[ROWIndex][COLIndex] << endl;
                            
                        }
                        count ++ ;
                    }
                }
            }
        }
        
        else {
            for(int j = COL-1; j >= 0; j--){
                //int j = 8;
                long double middlePixel = image2DTemp[i][j];
                long double tobemiddlePixel;
                if(middlePixel <= 127) {
                    tobemiddlePixel = 0;
                }
                else {
                    tobemiddlePixel = 255;
                }
                
                long double errorToBeDiffused = middlePixel - tobemiddlePixel;
                image2DErrorDiffusion[i][j] = tobemiddlePixel;
                //cout << i << ' ' << j << ' ' << middlePixel << ' ' << tobemiddlePixel << ' ' <<  errorToBeDiffused << endl;
                
                unsigned char * tempPixelArray = new unsigned char [MASKSIZE*MASKSIZE]();
                unsigned int count = 0;
                for(signed int p = startN ; p <= endN ; p++) {
                    for(signed int q = endN ; q >= startN ; q--) {
                        signed int ROWIndex = i + p;
                        signed int COLIndex = j + q;
                        if((ROWIndex >= 0) and (COLIndex >= 0) and (ROWIndex <= ROW-1) and (COLIndex <= COL-1)){
                            tempPixelArray[count] = image2DTemp[ROWIndex][COLIndex];
                            image2DTemp[ROWIndex][COLIndex] = tempPixelArray[count] + (errorToBeDiffused * matrix[count]);
                            //cout << i << ' ' << j << ' ' << p << ' ' << q << ' ' << ROWIndex << ' ' << COLIndex << ' ' << count << endl;
                            //cout << (int)tempPixelArray[count] << ' ' <<  image2DTemp[ROWIndex][COLIndex] << endl;
                            
                        }
                        count ++ ;
                    }
                }
            }
        }
    }
    return image2DErrorDiffusion;
}


int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 7){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [ROW] [COL] [BYTESPERPIXEL]  [input Flower image path] [output image path - CMY] [output image path - Error Diffused]" << endl;
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
    unsigned char *imageCMYToFile = new unsigned char [IMAGELEN]();
    unsigned char *imageCMYEDToFile = new unsigned char [IMAGELEN]();
    
    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFile, IMAGELEN);
    
    // Declare and allocate memoory for the images --------
    unsigned char *** image3D = NULL;
    image3D = image1Dto3D(image3D, imageFromFile, ROW, COL, BYTESPERPIXEL);
    
    unsigned char *** image3DCMY = NULL;
    image3DCMY = allocMemory3D(image3DCMY, ROW, COL, BYTESPERPIXEL);
    
    unsigned char ** image2DCyan = NULL;
    image2DCyan = allocMemory2D(image2DCyan, ROW, COL);
    
    unsigned char ** image2DMagenta = NULL;
    image2DMagenta = allocMemory2D(image2DMagenta, ROW, COL);
    
    unsigned char ** image2DYellow = NULL;
    image2DYellow = allocMemory2D(image2DYellow, ROW, COL);
    
    unsigned char ** image2DErrorDiffusionCyan = NULL;
    image2DErrorDiffusionCyan = allocMemory2D(image2DErrorDiffusionCyan, ROW, COL);
    
    unsigned char ** image2DErrorDiffusionMagenta = NULL;
    image2DErrorDiffusionMagenta = allocMemory2D(image2DErrorDiffusionMagenta, ROW, COL);
    
    unsigned char ** image2DErrorDiffusionYellow = NULL;
    image2DErrorDiffusionYellow = allocMemory2D(image2DErrorDiffusionYellow, ROW, COL);
    
    unsigned char *** image3DCMYED = NULL;
    image3DCMYED = allocMemory3D(image3DCMYED, ROW, COL, BYTESPERPIXEL);
    
    
    // Cyan - Magenta - Yellow conversion and seperation --------
    for(int i=0; i<ROW; i++){
        for(int j=0; j< COL; j++) {
            unsigned char cValue = 255 - image3D[i][j][0];
            unsigned char mValue = 255 - image3D[i][j][1];
            unsigned char yValue = 255 - image3D[i][j][2];
            
            image2DCyan[i][j] = cValue;
            image2DMagenta[i][j] = mValue;
            image2DYellow[i][j] = yValue;
        }
    }
    
    // Error Diffusion Matrix initialization
    long double * method1Matrix = new long double [9] {0,0,0,0,0,7.0/16.0,3.0/16.0,5.0/16.0,1.0/16.0};
    
    long double ** image2DTemp1 = NULL;
    image2DTemp1 = new long double *[ROW]();
    long double ** image2DTemp2 = NULL;
    image2DTemp2 = new long double *[ROW]();
    long double ** image2DTemp3 = NULL;
    image2DTemp3 = new long double *[ROW]();
    for(int i=0; i < ROW; i++) {
        image2DTemp1[i] = new long double [COL]();
        image2DTemp2[i] = new long double [COL]();
        image2DTemp3[i] = new long double [COL]();
        for(int j=0; j < COL; j++) {
            image2DTemp1[i][j] = image2DCyan[i][j];
            image2DTemp2[i][j] = image2DMagenta[i][j];
            image2DTemp3[i][j] = image2DYellow[i][j];
            
        }
    }
    
    image2DErrorDiffusionCyan = errorDiffusionSerpentine(image2DErrorDiffusionCyan, image2DTemp1, method1Matrix, 3, ROW, COL);
    image2DErrorDiffusionMagenta = errorDiffusionSerpentine(image2DErrorDiffusionMagenta, image2DTemp2, method1Matrix, 3, ROW, COL);
    image2DErrorDiffusionYellow = errorDiffusionSerpentine(image2DErrorDiffusionYellow, image2DTemp3, method1Matrix, 3, ROW, COL);
    
    //Combine C, M and Y channels
    image3DCMY = combineChannels(image3DCMY, image2DCyan, image2DMagenta, image2DYellow, ROW, COL, BYTESPERPIXEL);
    image3DCMYED = combineChannels(image3DCMYED, image2DErrorDiffusionCyan, image2DErrorDiffusionMagenta, image2DErrorDiffusionYellow, ROW, COL, BYTESPERPIXEL);
    
    // Inverting the CMY to RGB
    for(int i=0; i<ROW; i++){
        for(int j=0; j< COL; j++) {
            unsigned char cValue = 255 - image3DCMYED[i][j][0];
            unsigned char mValue = 255 - image3DCMYED[i][j][1];
            unsigned char yValue = 255 - image3DCMYED[i][j][2];
            
            image3DCMYED[i][j][0] = cValue;
            image3DCMYED[i][j][1] = mValue;
            image3DCMYED[i][j][2] = yValue;
        }
    }
    
    // Write outputs to the Raw files --------
    image3Dto1D(image3DCMY, imageCMYToFile, ROW, COL, BYTESPERPIXEL);
    fileWrite(argv[5], imageCMYToFile, IMAGELEN);
    
    image3Dto1D(image3DCMYED, imageCMYEDToFile, ROW, COL, BYTESPERPIXEL);
    fileWrite(argv[6], imageCMYEDToFile, IMAGELEN);
    
    //Deallocate all memories
    freeMemory2D(image2DCyan, ROW, COL);
    freeMemory2D(image2DYellow, ROW, COL);
    freeMemory2D(image2DMagenta, ROW, COL);
    freeMemory2D(image2DErrorDiffusionCyan, ROW, COL);
    freeMemory2D(image2DErrorDiffusionMagenta, ROW, COL);
    freeMemory2D(image2DErrorDiffusionYellow, ROW, COL);
    freeMemory3D(image3D, ROW, COL, BYTESPERPIXEL);
    freeMemory3D(image3DCMY, ROW, COL, BYTESPERPIXEL);
    freeMemory3D(image3DCMYED, ROW, COL, BYTESPERPIXEL);
    
    delete [] imageFromFile;
    delete [] imageCMYToFile;
    delete [] imageCMYEDToFile;
    
}
