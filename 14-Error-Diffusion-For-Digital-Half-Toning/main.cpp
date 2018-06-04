//
//  main.cpp
//  hw_2_prob_2_b
//
//  Created by Abinaya Manimaran on 2/22/18.
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
                        signed int rowIndex = i + p;
                        signed int colIndex = j + q;
                        if((rowIndex >= 0) and (colIndex >= 0) and (rowIndex <= ROW-1) and (colIndex <= COL-1)){
                            tempPixelArray[count] = image2DTemp[rowIndex][colIndex];
                            image2DTemp[rowIndex][colIndex] = tempPixelArray[count] + (errorToBeDiffused * matrix[count]);
                            //cout << i << ' ' << j << ' ' << p << ' ' << q << ' ' << count << endl;
                            //cout << (int)tempPixelArray[count] << ' ' <<  image2DTemp[rowIndex][colIndex] << endl;
                            
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
                        signed int rowIndex = i + p;
                        signed int colIndex = j + q;
                        if((rowIndex >= 0) and (colIndex >= 0) and (rowIndex <= ROW-1) and (colIndex <= COL-1)){
                            tempPixelArray[count] = image2DTemp[rowIndex][colIndex];
                            image2DTemp[rowIndex][colIndex] = tempPixelArray[count] + (errorToBeDiffused * matrix[count]);
                            //cout << i << ' ' << j << ' ' << p << ' ' << q << ' ' << rowIndex << ' ' << colIndex << ' ' << count << endl;
                            //cout << (int)tempPixelArray[count] << ' ' <<  image2DTemp[rowIndex][colIndex] << endl;
                            
                        }
                        count ++ ;
                    }
                }
            }
        }
    }
    return image2DErrorDiffusion;
}


unsigned char ** errorDiffusion(unsigned char ** image2DErrorDiffusion, long double ** image2DTemp, long double *matrix,int MASKSIZE, int ROW, int COL ) {
    signed int startN = - floor(MASKSIZE/2.0);
    signed int endN =  floor(MASKSIZE/2.0);
    
    for(int i=0; i < ROW; i++){
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
                    signed int rowIndex = i + p;
                    signed int colIndex = j + q;
                    if((rowIndex >= 0) and (colIndex >= 0) and (rowIndex <= ROW-1) and (colIndex <= COL-1)){
                        tempPixelArray[count] = image2DTemp[rowIndex][colIndex];
                        image2DTemp[rowIndex][colIndex] = tempPixelArray[count] + (errorToBeDiffused * matrix[count]);
                        //cout << i << ' ' << j << ' ' << p << ' ' << q << ' ' << count << endl;
                        //cout << (int)tempPixelArray[count] << ' ' <<  image2DTemp[rowIndex][colIndex] << endl;
                        
                    }
                    count ++ ;
                }
            }
        }
    }
    return image2DErrorDiffusion;
}

int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 11){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [row] [col] [bytesPerPixel]  [input color checker image path] [output image path - Method1] [output image path - Method1 Serpentine] [output image path - Method2] [output image path - Method2 - Serpentine] [output image path - Method3] [output image path - Method3 - Serpentine]" << endl;
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
    unsigned char *imageToFileMethod1 = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileMethod2 = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileMethod3 = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileMethod1Serpentine = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileMethod2Serpentine = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileMethod3Serpentine = new unsigned char [IMAGELEN]();

    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFile, IMAGELEN);
    
    // Declare and allocate memoory for the images --------
    unsigned char ** image2D = NULL;
    image2D = image1Dto2D(image2D, imageFromFile, ROW, COL);
    
    unsigned char ** image2DErrorDiffusionMethod1 = NULL;
    image2DErrorDiffusionMethod1 = allocMemory2D(image2DErrorDiffusionMethod1, ROW, COL);

    unsigned char ** image2DErrorDiffusionMethod2 = NULL;
    image2DErrorDiffusionMethod2 = allocMemory2D(image2DErrorDiffusionMethod2, ROW, COL);

    unsigned char ** image2DErrorDiffusionMethod3 = NULL;
    image2DErrorDiffusionMethod3 = allocMemory2D(image2DErrorDiffusionMethod3, ROW, COL);
    
    unsigned char ** image2DErrorDiffusionMethod1Serpentine = NULL;
    image2DErrorDiffusionMethod1Serpentine = allocMemory2D(image2DErrorDiffusionMethod1Serpentine, ROW, COL);

    unsigned char ** image2DErrorDiffusionMethod2Serpentine = NULL;
    image2DErrorDiffusionMethod2Serpentine = allocMemory2D(image2DErrorDiffusionMethod2Serpentine, ROW, COL);
    
    unsigned char ** image2DErrorDiffusionMethod3Serpentine = NULL;
    image2DErrorDiffusionMethod3Serpentine = allocMemory2D(image2DErrorDiffusionMethod3Serpentine, ROW, COL);
    
    // Error Diffusion Matrix initialization
    long double * method1Matrix = new long double [9] {0,0,0,0,0,7.0/16.0,3.0/16.0,5.0/16.0,1.0/16.0};
    long double * method2Matrix = new long double [25] {0,0,0,0,0, 0,0,0,0,0, 0,0,0,7.0/48.0,5.0/48.0, 3.0/48.0,5.0/48.0,7.0/48.0,5.0/48.0,3.0/48.0, 1.0/48.0,3.0/48.0,5.0/48.0,3.0/48.0,1.0/48.0};
    long double * method3Matrix = new long double [25] {0,0,0,0,0, 0,0,0,0,0, 0,0,0,8.0/42.0,4.0/42.0, 2.0/42.0,4.0/42.0,8.0/42.0,4.0/42.0,2.0/42.0, 1.0/42.0,2.0/42.0,4.0/42.0,2.0/42.0,1.0/48.0};

    
    long double ** image2DTemp = NULL;
    image2DTemp = new long double *[ROW]();
    for(int i=0; i < ROW; i++) {
        image2DTemp[i] = new long double [COL]();
        for(int j=0; j < COL; j++) {
            image2DTemp[i][j] = image2D[i][j];
        }
    }
    image2DErrorDiffusionMethod1 = errorDiffusion(image2DErrorDiffusionMethod1, image2DTemp, method1Matrix, 3, ROW, COL);
    

    for(int i=0; i < ROW; i++) {
        for(int j=0; j < COL; j++) {
            image2DTemp[i][j] = image2D[i][j];
        }
    }
    image2DErrorDiffusionMethod1Serpentine = errorDiffusion(image2DErrorDiffusionMethod1Serpentine, image2DTemp, method1Matrix, 3, ROW, COL);
    
    
    for(int i=0; i < ROW; i++) {
        for(int j=0; j < COL; j++) {
            image2DTemp[i][j] = image2D[i][j];
        }
    }
    image2DErrorDiffusionMethod2 = errorDiffusion(image2DErrorDiffusionMethod2, image2DTemp, method2Matrix, 5, ROW, COL);
    
    for(int i=0; i < ROW; i++) {
        for(int j=0; j < COL; j++) {
            image2DTemp[i][j] = image2D[i][j];
        }
    }
    image2DErrorDiffusionMethod2Serpentine = errorDiffusionSerpentine(image2DErrorDiffusionMethod2Serpentine, image2DTemp, method2Matrix, 5, ROW, COL);
    
    for(int i=0; i < ROW; i++) {
        for(int j=0; j < COL; j++) {
            image2DTemp[i][j] = image2D[i][j];
        }
    }
    image2DErrorDiffusionMethod3 = errorDiffusion(image2DErrorDiffusionMethod3, image2DTemp, method3Matrix, 5, ROW, COL);
    
    for(int i=0; i < ROW; i++) {
        for(int j=0; j < COL; j++) {
            image2DTemp[i][j] = image2D[i][j];
        }
    }
    image2DErrorDiffusionMethod3Serpentine = errorDiffusionSerpentine(image2DErrorDiffusionMethod3Serpentine, image2DTemp, method3Matrix, 5, ROW, COL);
    
    /*
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            if( image2DErrorDiffusionMethod1[i][j] == 1) {
                image2DErrorDiffusionMethod1[i][j] = 255; }
        }
    }*/

    
    // Writing the Final iteration First stage and Second Stage output
    image2Dto1D(image2DErrorDiffusionMethod1, imageToFileMethod1, ROW, COL);
    fileWrite(argv[5], imageToFileMethod1, IMAGELEN);
    image2Dto1D(image2DErrorDiffusionMethod1Serpentine, imageToFileMethod1Serpentine, ROW, COL);
    fileWrite(argv[6], imageToFileMethod1Serpentine, IMAGELEN);
    image2Dto1D(image2DErrorDiffusionMethod2, imageToFileMethod2, ROW, COL);
    fileWrite(argv[7], imageToFileMethod2, IMAGELEN);
    image2Dto1D(image2DErrorDiffusionMethod2Serpentine, imageToFileMethod2Serpentine, ROW, COL);
    fileWrite(argv[8], imageToFileMethod2Serpentine, IMAGELEN);
    image2Dto1D(image2DErrorDiffusionMethod3, imageToFileMethod3, ROW, COL);
    fileWrite(argv[9], imageToFileMethod3, IMAGELEN);
    image2Dto1D(image2DErrorDiffusionMethod3Serpentine, imageToFileMethod3Serpentine, ROW, COL);
    fileWrite(argv[10], imageToFileMethod3Serpentine, IMAGELEN);
    
    // Deallocate all the memories
    freeMemory2D(image2D, ROW, COL);
    freeMemory2D(image2DErrorDiffusionMethod1, ROW, COL);
    freeMemory2D(image2DErrorDiffusionMethod1Serpentine, ROW, COL);
    freeMemory2D(image2DErrorDiffusionMethod2, ROW, COL);
    freeMemory2D(image2DErrorDiffusionMethod2Serpentine, ROW, COL);
    freeMemory2D(image2DErrorDiffusionMethod3, ROW, COL);
    freeMemory2D(image2DErrorDiffusionMethod3Serpentine, ROW, COL);
    
    delete [] imageFromFile;
    delete [] imageToFileMethod1;
    delete [] imageToFileMethod2;
    delete [] imageToFileMethod3;
    delete [] imageToFileMethod1Serpentine;
    delete [] imageToFileMethod2Serpentine;
    delete [] imageToFileMethod3Serpentine;

}

