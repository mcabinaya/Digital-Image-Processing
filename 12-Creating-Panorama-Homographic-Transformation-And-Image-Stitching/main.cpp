//
//  main.cpp
//  hw_2_prob_1_b
//
//  Created by Abinaya Manimaran on 2/10/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include "DIP_MyHeaderFile.h"

using namespace std;

long double ** convert1DtoMatrix(long double ** matrix, long double *array, int ROW, int COL) {
    unsigned int tempCount = 0;
    matrix = new long double *[ROW]();
    for(int i=0; i < 3; i++){
        matrix[i] = new long double [COL]();
        for(int j=0; j < 3; j++){
            matrix[i][j] = array[tempCount];
            //cout << Hinv[i][j] << endl;
            tempCount ++;
        }
    }
    return matrix;
}

long double * multiplyMatrixVector(long double *outVector, long double **matrix, long double *inpVector, int MatrixSize){
    for(int i = 0; i < MatrixSize; i++){
        long double tempSum = 0.0;
        for(int j = 0; j < MatrixSize; j++) {
            tempSum = tempSum + (matrix[i][j]*inpVector[j]);
            //cout << "check " << matrix[i][j] << ' ' << inpVector[j] << ' ' << tempSum << endl;
        }
        //tempSum = (ceil(tempSum*100.0))/100.0;
        outVector[i] = tempSum;
        //cout << outVector[i] << endl;
    }
    return outVector;
}

long double * getCoordinatesMinMax(long double * coordinatesMinMax,long double ** H, int ROW, int COL) {
    long double * xCoordinates = new long double [4]();
    long double * yCoordinates = new long double [4]();

    int tempCount = 0;
    long double * inpVector = new long double [3] ();
    long double * outVector = new long double [3]();

    for(int i = 1; i <= ROW; i=i+ROW-1) {
        for(int j = 1; j <= COL; j=j+COL-1 ) {
            inpVector[0] = i;
            inpVector[1] = j;
            inpVector[2] = 1;
            outVector = multiplyMatrixVector(outVector, H, inpVector, 3);
            xCoordinates[tempCount] = outVector[0] / outVector[2];
            yCoordinates[tempCount] = outVector[1] / outVector[2];
            cout << i << ' ' << j << ' ' << xCoordinates[tempCount] << ' ' << yCoordinates[tempCount] << endl;
            tempCount++;
        }
    }
            
    coordinatesMinMax[0] = xCoordinates[0];
    coordinatesMinMax[1] = xCoordinates[0];
    coordinatesMinMax[2] = yCoordinates[0];
    coordinatesMinMax[3] = yCoordinates[0];
    
    for(int i = 1; i < 4; i++) {
        if (xCoordinates[i] < coordinatesMinMax[0]){ coordinatesMinMax[0]  = xCoordinates[i]; }
        if (xCoordinates[i] > coordinatesMinMax[1]){ coordinatesMinMax[1]  = xCoordinates[i]; }
        if (yCoordinates[i] < coordinatesMinMax[2]){ coordinatesMinMax[2]  = yCoordinates[i]; }
        if (yCoordinates[i] > coordinatesMinMax[3]){ coordinatesMinMax[3]  = yCoordinates[i]; }
    }
    for(int i = 0; i < 4; i++) {
        cout << coordinatesMinMax[i] << endl;
    }

    return coordinatesMinMax;
}

        
unsigned char *** inverseWarping(unsigned char *** image3DWarped, unsigned char *** image3D, long double ** Hinv,int ROW,int COL,int BYTESPERPIXEL, int MIDROW, int MIDCOL) {
    unsigned int ycount = 0;
    for (long double x =  1; x < MIDROW; x++) {
        unsigned int xcount = 0;
        for (long double y = 1; y < MIDCOL; y++) {
            
            long double *xyArray = new long double [3]{x, y, 1};
            long double *uvArray = new long double [3]();
            uvArray = multiplyMatrixVector(uvArray, Hinv, xyArray, 3);
            long double mappedRowIndex = (uvArray[0]) / (uvArray[2]);
            long double mappedColIndex = (uvArray[1]) / (uvArray[2]);
            //cout << mappedRowIndex << ' ' << mappedColIndex << endl;
            int referenceRowIndex = (int)floor(mappedRowIndex);
            int referenceColIndex = (int)floor(mappedColIndex);
            //cout << referenceRowIndex << ' ' << referenceColIndex << endl;
            
            double deltaRow = mappedRowIndex - referenceRowIndex;
            double deltaCol = mappedColIndex - referenceColIndex;
            
            if ((referenceRowIndex > 0) & (referenceColIndex > 0) & (referenceRowIndex < ROW-1) & (referenceColIndex < COL-1)) {
                
                for(int k=0; k < BYTESPERPIXEL; k++) {
                    int intX = round(x)-1;
                    int intY = round(y)-1;
                    
                    image3DWarped[intX][intY][k] = (unsigned char)((image3D[referenceRowIndex][referenceColIndex][k] * (1 - deltaRow) * (1 - deltaCol))+
                                                             (image3D[referenceRowIndex+1][referenceColIndex][k] * (deltaRow) * (1 - deltaCol)) +
                                                             (image3D[referenceRowIndex][referenceColIndex+1][k] * (1 - deltaRow) *  (deltaCol)) +
                                                             (image3D[referenceRowIndex+1][referenceColIndex+1][k] * (deltaRow) * (deltaCol)));
                    //cout << "check " << (int) image3DWarped[intX][intY][k] << endl;
                }
                //cout << (int) image3DWarped[intX][intY][0] << ' ' <<(int)  image3DWarped[intX][intY][1] << ' ' << (int)image3DWarped[intX][intY][2] << endl;
                //break;
            }
            xcount ++;
        }
        ycount ++;
        //break;
    }
    return image3DWarped;
}





int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 11){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [row] [col] [bytesPerPixel]  [input left image path] [input middle image path] [input right image path] [output Middle Bounded image path] [output Left Warped image path] [output Right Warped image path] [output Panorama image path]" << endl;
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
    unsigned char *imageFromFileLeft = new unsigned char [IMAGELEN]();
    unsigned char *imageFromFileMiddle = new unsigned char [IMAGELEN]();
    unsigned char *imageFromFileRight = new unsigned char [IMAGELEN]();
    
    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFileLeft, IMAGELEN);
    fileRead(argv[5], imageFromFileMiddle, IMAGELEN);
    fileRead(argv[6], imageFromFileRight, IMAGELEN);
    
    // Declare and allocate memoory for the images --------
    unsigned char *** image3DLeft = NULL;
    image3DLeft = image1Dto3D(image3DLeft, imageFromFileLeft, ROW, COL, BYTESPERPIXEL);
    
    unsigned char *** image3DMiddle = NULL;
    image3DMiddle = image1Dto3D(image3DMiddle, imageFromFileMiddle, ROW, COL, BYTESPERPIXEL);
    
    unsigned char *** image3DRight = NULL;
    image3DRight = image1Dto3D(image3DRight, imageFromFileRight, ROW, COL, BYTESPERPIXEL);
    
    // Embed middle image into a bigger image with bounding box
    const int ROWOFFSET = 300;
    const int COLOFFSET = 795;
    const int MIDROW = 1240;
    const int MIDCOL = 2000;
    
    unsigned char *** image3DMiddleBounded = NULL;
    image3DMiddleBounded = allocMemory3D(image3DMiddleBounded, MIDROW, MIDCOL, BYTESPERPIXEL);
    
    unsigned char *** image3DPanorama = NULL;
    image3DPanorama = allocMemory3D(image3DPanorama, MIDROW, MIDCOL, BYTESPERPIXEL);
    
    //Declaring H inverse 2D pointer array - float values
    
    long double * H1DLeft = new long double [9]{1.4335676762071,   0.5642266083990,   186.1898407153198, 0.0742788231530,   2.3018711509579 ,  391.4644721765437, 0.0000688400972, 0.0009791055256,  1.0000000000000};

    long double * Hinv1DLeft= new long double [9]{ 0.7085522931281,  -0.1410493508118,  -76.7094289296011, -0.0174795607964,   0.5246967576371 , -202.1456226406839, -0.0000316624742,  -0.0005040236436,   1.2032025806476};

    long double *H1DRight = new long double [9]{0.913205175363, -0.494233792743,  340.736887988386, 0.037493068763, 0.021757365662, 1010.405932392893, 0.037829223,  -0.0772001369,   1.000000000000};

    long double * Hinv1DRight = new long double [9]{1.110981575213, 0.320334477785, -702.220261254909, 0.001011231121, 1.247497630304, -1260.823570050726, -0.000041246898, 0.000950951874, 0.053206924333};

        
    long double **HLeft = NULL;
    long double **HinvLeft = NULL;
    long double **HRight = NULL;
    long double **HinvRight = NULL;
    
    HLeft = convert1DtoMatrix(HLeft, H1DLeft, 3, 3);
    HinvLeft = convert1DtoMatrix(HinvLeft, Hinv1DLeft, 3, 3);
    HRight = convert1DtoMatrix(HRight, H1DRight, 3, 3);
    HinvRight = convert1DtoMatrix(HinvRight, Hinv1DRight, 3, 3);
    
    
    // Embed middle image for Warping just for report purpose. Not used anywhere
    for(int i = ROWOFFSET; i < ROWOFFSET+ROW; i++) {
        for(int j = COLOFFSET; j < COLOFFSET+COL; j++) {
            for(int k=0; k < BYTESPERPIXEL; k++) {
                image3DMiddleBounded[i-1][j-1][k] = image3DMiddle[i-ROWOFFSET][j-COLOFFSET][k];
            }
        }
    }
    
    unsigned char *imageToFileMiddleBounded = new unsigned char [MIDROW*MIDCOL*BYTESPERPIXEL]();
    image3Dto1D(image3DMiddleBounded, imageToFileMiddleBounded, MIDROW, MIDCOL, BYTESPERPIXEL);
    fileWrite(argv[7], imageToFileMiddleBounded, MIDROW*MIDCOL*BYTESPERPIXEL);
    
    
    /*
    // Get MinX, MaxX, MinY and MaxY Coordinates - Forward warping
    long double * coordinatesMinMaxLeft = new long double [4]();
    long double * coordinatesMinMaxRight = new long double [4]();

    coordinatesMinMaxLeft = getCoordinatesMinMax(coordinatesMinMaxLeft, HLeft, ROW, COL);
    coordinatesMinMaxRight = getCoordinatesMinMax(coordinatesMinMaxRight, HRight, ROW, COL);
     */
    
    
    // Inverse warping for left and right images with respect to the middle one
    
    image3DPanorama = inverseWarping(image3DPanorama, image3DLeft, HinvLeft, ROW, COL, BYTESPERPIXEL, MIDROW, MIDCOL);
    
    unsigned char *imageToFileLeftWarped = new unsigned char [MIDROW*MIDCOL*BYTESPERPIXEL]();
    image3Dto1D(image3DPanorama, imageToFileLeftWarped, MIDROW, MIDCOL, BYTESPERPIXEL);
    fileWrite(argv[8], imageToFileLeftWarped, MIDROW*MIDCOL*BYTESPERPIXEL);
    
    image3DPanorama = inverseWarping(image3DPanorama, image3DRight, HinvRight, ROW, COL, BYTESPERPIXEL, MIDROW, MIDCOL);
    
    unsigned char *imageToFileRightWarped = new unsigned char [MIDROW*MIDCOL*BYTESPERPIXEL]();
    image3Dto1D(image3DPanorama, imageToFileRightWarped, MIDROW, MIDCOL, BYTESPERPIXEL);
    fileWrite(argv[9], imageToFileRightWarped, MIDROW*MIDCOL*BYTESPERPIXEL);
    
    for(int i = ROWOFFSET; i < ROWOFFSET+ROW; i++) {
        for(int j = COLOFFSET; j < COLOFFSET+COL; j++) {
            //if ((image3DPanorama[i-1][j-1][0]) > 0 and (image3DPanorama[i-1][j-1][0] > 0) and (image3DPanorama[i-1][j-1][0] > 0)) {
                for(int k=0; k < BYTESPERPIXEL; k++) {
                    //image3DPanorama[i-1][j-1][k] = (image3DMiddle[i-ROWOFFSET][j-COLOFFSET][k] + image3DPanorama[i-1][j-1][k])/ 2.0;
                    image3DPanorama[i-1][j-1][k] = image3DMiddle[i-ROWOFFSET][j-COLOFFSET][k];
                }
            //}
        }
    }
    
    unsigned char *imageToFilePanorama = new unsigned char [MIDROW*MIDCOL*BYTESPERPIXEL]();
    image3Dto1D(image3DPanorama, imageToFilePanorama, MIDROW, MIDCOL, BYTESPERPIXEL);
    fileWrite(argv[10], imageToFilePanorama, MIDROW*MIDCOL*BYTESPERPIXEL);
    
    //Deallocate all memories
    freeMemory3D(image3DMiddle, ROW, COL, BYTESPERPIXEL);
    freeMemory3D(image3DLeft, ROW, COL, BYTESPERPIXEL);
    freeMemory3D(image3DRight, ROW, COL, BYTESPERPIXEL);
    freeMemory3D(image3DMiddleBounded, MIDROW, MIDCOL, BYTESPERPIXEL);
    freeMemory3D(image3DPanorama, MIDROW, MIDCOL, BYTESPERPIXEL);
    
    delete [] imageToFileMiddleBounded;
    delete [] imageToFilePanorama;
    delete [] imageToFileLeftWarped;
    delete [] imageToFileRightWarped;
    delete [] imageFromFileMiddle;
    delete [] imageFromFileLeft;
    delete [] imageFromFileRight;




}

