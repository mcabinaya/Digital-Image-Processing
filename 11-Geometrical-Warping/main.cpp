//
//  main.cpp
//  hw_2_prob_1_a
//
//  Created by Abinaya Manimaran on 2/15/18.
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
    if (argc != 7){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [ROW] [COL] [BYTESPERPIXEL] [input image path] [output Warped image path] [output reverse image path]" << endl;
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
    unsigned char *imageToFileWarped = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileReversed = new unsigned char [IMAGELEN]();
    
    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFile, IMAGELEN);
    
    // Declare and allocate memoory for the images --------
    unsigned char *** image3D = NULL;
    image3D = image1Dto3D(image3D, imageFromFile, ROW, COL, BYTESPERPIXEL);
    
    unsigned char *** image3DWarped = NULL;
    image3DWarped = allocMemory3D(image3DWarped, ROW, COL, BYTESPERPIXEL);
    
    unsigned char *** image3DReversed = NULL;
    image3DReversed = allocMemory3D(image3DReversed, ROW, COL, BYTESPERPIXEL);
    
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            long double x = (i - ((ROW/2)-1))/(long double)((ROW/2)-1);
            long double y = (j - ((COL/2)-1))/(long double)((COL/2)-1);
            long double u = x * sqrt(1 - ((pow(y,2)))/2);
            long double v = y * sqrt(1 - ((pow(x,2)))/2);
            unsigned int p = (u*((ROW/2)-1))+((ROW/2)-1);
            unsigned int q = (v*((COL/2)-1))+((COL/2)-1);
            image3DWarped[p][q][0] = image3D[i][j][0];
            image3DWarped[p][q][1] = image3D[i][j][1];
            image3DWarped[p][q][2] = image3D[i][j][2];
            long double xnew = 1.00/2.00 * ((sqrt((2 + (pow(u,2)) - (pow(v,2)) + (2*(sqrt(2)*u))))) - (sqrt((2 + (pow(u,2)) - (pow(v,2)) - (2*(sqrt(2)*u))))));
            long double ynew = 1.00/2.00 * ((sqrt((2 - (pow(u,2)) + (pow(v,2)) + (2*(sqrt(2)*v))))) - (sqrt((2 - (pow(u,2)) + (pow(v,2)) - (2*(sqrt(2)*v))))));
            unsigned int l = round((xnew*(((ROW/2)-1)))+((ROW/2)-1));
            unsigned int m = round((ynew*(((COL/2)-1)))+((COL/2)-1));
            image3DReversed[l][m][0] = image3DWarped[p][q][0];
            image3DReversed[l][m][1] = image3DWarped[p][q][1];
            image3DReversed[l][m][2] = image3DWarped[p][q][2];
            /*
             cout << i << ' ' << j  << ' '  << x << ' '  << y  << endl;
             cout << u << ' '  << v << ' '  << p << ' '  << q << endl;
             cout << xnew << ' '  << ynew << ' '  << l << ' '  << m << endl;
             cout << (int) image3DWarped[p][q][0] << ' ' << (int) image3DWarped[p][q][0] << ' ' << (int) image3DWarped[p][q][0] << endl;
             cout << "----" << endl;
             */
            
        }
    }
    
    // Write outputs to the Raw files --------
    image3Dto1D(image3DWarped, imageToFileWarped, ROW, COL, BYTESPERPIXEL);
    fileWrite(argv[5], imageToFileWarped, IMAGELEN);
    image3Dto1D(image3DReversed, imageToFileReversed, ROW, COL, BYTESPERPIXEL);
    fileWrite(argv[6], imageToFileReversed, IMAGELEN);
    
    //Deallocate all memories
    freeMemory3D(image3D, ROW, COL, BYTESPERPIXEL);
    freeMemory3D(image3DWarped, ROW, COL, BYTESPERPIXEL);
    freeMemory3D(image3DReversed, ROW, COL, BYTESPERPIXEL);
    
    delete [] imageFromFile;
    delete [] imageToFileWarped;
    delete [] imageToFileReversed;
    

    
}


