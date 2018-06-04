//
//  main.cpp
//  hw_2_prob_2_c2
//
//  Created by Abinaya Manimaran on 2/25/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <string>
#include <map>
#include "DIP_MyHeaderFile.h"


using namespace std;

string getMBVQString(long double r, long double g, long double b) {
    string mbvq;
    if ((r+g) > 255.0) {
        if((g+b) > 255.0) {
            if((r+g+b) > 510.0) { mbvq = "CMYW";}
            else {mbvq = "MYGC";}}
        else{ mbvq = "RGMY"; }
    }
    else{ if (!((g+b) > 255.0)) {
        if (!((r+g+b) > 255.0)) {
            mbvq = "KRGB";}
        else{
            mbvq = "RGBM";
        }
    }
    else { mbvq = "CMGB";
    }
    }
    return mbvq;
}

char getMinDistVertex(long double rPixel, long double gPixel, long double bPixel, map <string, long double **> mbvqVertices, int noVertices, string mbvq) {
    long double * vertexDist = new long double [noVertices]();
    for (int i = 0; i < noVertices; i++) {
        long double tempSum = 0;
        long double tempDiff1 = ((gPixel)/255.0) - mbvqVertices[mbvq][i][0];
        long double tempDiff2 = ((rPixel)/255.0) - mbvqVertices[mbvq][i][1];
        long double tempDiff3 = ((bPixel)/255.0) - mbvqVertices[mbvq][i][2];
        tempSum = pow(tempDiff1,2) + pow(tempDiff2,2) + pow(tempDiff3,2);
        vertexDist[i] = sqrt(tempSum);
        //cout << vertexDist[i] << endl;
    }
    long double minDist = vertexDist[0];
    int minIndex = 0;
    for (int i=1; i < noVertices; i++) {
        if(vertexDist[i] < minDist) {
            minDist = vertexDist[i];
            minIndex = i;
        }
    }
    return mbvq[minIndex];
}

unsigned char *** errorDiffusionSerpentine(unsigned char *** image2DErrorDiffusion, long double *** image3DTemp, long double *** image3DTempCMY, long double *matrix, int MASKSIZE, int ROW, int COL, int BYTESPERPIXEL,map <string, long double **> mbvqVertices, int noVertices, map <char , long double * > verticesIntensity) {
    signed int startN = - floor(MASKSIZE/2.0);
    signed int endN =  floor(MASKSIZE/2.0);
    
    for(int i=0; i < ROW; i++){
        //int i = 2;
        if (i%2 == 0) {
            for(int j = 0; j < COL; j++){
                //int j = 6;
                long double rPixel = image3DTemp[i][j][0];
                long double gPixel = image3DTemp[i][j][1];
                long double bPixel = image3DTemp[i][j][2];
                
                string mbvq =  getMBVQString(rPixel, gPixel, bPixel);
                char minDistVertex = getMinDistVertex(image3DTempCMY[i][j][0], image3DTempCMY[i][j][1], image3DTempCMY[i][j][2], mbvqVertices, noVertices, mbvq);
                
                for(int k=0; k < BYTESPERPIXEL; k++) {
                    long double middlePixel = image3DTempCMY[i][j][k];
                    long double tobemiddlePixel;
                    if (k==0) {tobemiddlePixel = verticesIntensity[minDistVertex][1]*255.0; }
                    else if (k==1) {tobemiddlePixel = verticesIntensity[minDistVertex][0]*255.0; }
                    else {tobemiddlePixel = verticesIntensity[minDistVertex][k]*255.0; }
                    
                    long double errorToBeDiffused = middlePixel - tobemiddlePixel;
                    image2DErrorDiffusion[i][j][k] = 255 - tobemiddlePixel;
                    //cout << i << ' ' << j << ' ' << middlePixel << ' ' << tobemiddlePixel << ' ' << errorToBeDiffused << endl;
                
                    unsigned char * tempPixelArray = new unsigned char [MASKSIZE*MASKSIZE]();
                    unsigned int count = 0;
                    for(signed int p = startN ; p <= endN ; p ++) {
                        for(signed int q = startN ; q <= endN ; q ++) {
                            signed int ROWIndex = i + p;
                            signed int COLIndex = j + q;
                            if((ROWIndex >= 0) and (COLIndex >= 0) and (ROWIndex <= ROW-1) and (COLIndex <= COL-1)){
                                tempPixelArray[count] = image3DTempCMY[ROWIndex][COLIndex][k];
                                image3DTempCMY[ROWIndex][COLIndex][k] = tempPixelArray[count] + (errorToBeDiffused * matrix[count]);
                                //cout << i << ' ' << j << ' ' << p << ' ' << q << ' ' << count << endl;
                                //cout << (int)tempPixelArray[count] << ' ' <<  image3DTemp[ROWIndex][COLIndex][k] << endl;
                            }
                        count ++ ;
                        }
                    }
                }
            }
        }
        
        else {
            for(int j = COL-1; j >= 0; j--){
                //int j = 8;
                long double rPixel = image3DTemp[i][j][0];
                long double gPixel = image3DTemp[i][j][1];
                long double bPixel = image3DTemp[i][j][2];
                
                string mbvq =  getMBVQString(rPixel, gPixel, bPixel);
                char minDistVertex = getMinDistVertex(image3DTempCMY[i][j][0], image3DTempCMY[i][j][1], image3DTempCMY[i][j][2], mbvqVertices, noVertices, mbvq);
                
                for(int k=0; k < BYTESPERPIXEL; k++) {
                    long double middlePixel = image3DTempCMY[i][j][k];
                    long double tobemiddlePixel;
                    if (k==0) {tobemiddlePixel = verticesIntensity[minDistVertex][1]*255.0; }
                    else if (k==1) {tobemiddlePixel = verticesIntensity[minDistVertex][0]*255.0; }
                    else {tobemiddlePixel = verticesIntensity[minDistVertex][k]*255.0; }
                    
                    long double errorToBeDiffused = middlePixel - tobemiddlePixel;
                    image2DErrorDiffusion[i][j][k] = 255 - tobemiddlePixel;
                    //cout << i << ' ' << j << ' ' << middlePixel << ' ' << tobemiddlePixel << ' ' <<  errorToBeDiffused << endl;
                    
                    unsigned char * tempPixelArray = new unsigned char [MASKSIZE*MASKSIZE]();
                    unsigned int count = 0;
                    for(signed int p = startN ; p <= endN ; p++) {
                        for(signed int q = endN ; q >= startN ; q--) {
                            signed int ROWIndex = i + p;
                            signed int COLIndex = j + q;
                            if((ROWIndex >= 0) and (COLIndex >= 0) and (ROWIndex <= ROW-1) and (COLIndex <= COL-1)){
                                tempPixelArray[count] = image3DTempCMY[ROWIndex][COLIndex][k];
                                image3DTempCMY[ROWIndex][COLIndex][k] = tempPixelArray[count] + (errorToBeDiffused * matrix[count]);
                                //cout << i << ' ' << j << ' ' << p << ' ' << q << ' ' << ROWIndex << ' ' << COLIndex << ' ' << count << endl;
                                //cout << (int)tempPixelArray[count] << ' ' <<  image3DTemp[ROWIndex][COLIndex][k] << endl;
                                
                            }
                            count ++ ;
                        }
                    }
                }
            }
        }
    }
    return image2DErrorDiffusion;
}


int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 6){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [ROW] [COL] [BYTESPERPIXEL] [input flower image path] [output image path - MBVQ image]" << endl;
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
    unsigned char *imageToFile = new unsigned char [IMAGELEN]();
    
    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFile, IMAGELEN);
    
    // Declare and allocate memoory for the images --------
    unsigned char *** image3D = NULL;
    image3D = image1Dto3D(image3D, imageFromFile, ROW, COL, BYTESPERPIXEL);
    
    unsigned char *** image3DMBVQ = NULL;
    image3DMBVQ = image1Dto3D(image3DMBVQ, imageFromFile, ROW, COL, BYTESPERPIXEL);
    
    // Declare all MBVQ Quadruples Vertices
    const int noVertices = 4;
    const int noDimensions = 3;
    
    long double * CMYW1D = new long double [12]{0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0};
    long double * MYGC1D = new long double [12]{1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0};
    long double * RGMY1D = new long double [12]{1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1};
    long double * KRGB1D = new long double [12]{1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0};
    long double * RGBM1D = new long double [12]{1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0};
    long double * CMGB1D = new long double [12]{0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0};
        
    map < string , long double ** > mbvqVertices;
    mbvqVertices["CMYW"] = convert1DtoMatrixLongDouble(mbvqVertices["CMYW"], CMYW1D, noVertices, noDimensions);
    mbvqVertices["MYGC"] = convert1DtoMatrixLongDouble(mbvqVertices["MYGC"], MYGC1D, noVertices, noDimensions);
    mbvqVertices["RGMY"] = convert1DtoMatrixLongDouble(mbvqVertices["RGMY"], RGMY1D, noVertices, noDimensions);
    mbvqVertices["KRGB"] = convert1DtoMatrixLongDouble(mbvqVertices["KRGB"], KRGB1D, noVertices, noDimensions);
    mbvqVertices["RGBM"] = convert1DtoMatrixLongDouble(mbvqVertices["RGBM"], RGBM1D, noVertices, noDimensions);
    mbvqVertices["CMGB"] = convert1DtoMatrixLongDouble(mbvqVertices["CMGB"], CMGB1D, noVertices, noDimensions);
    
    map <char , long double * > verticesIntensity;
    verticesIntensity['C'] = mbvqVertices["CMYW"][0];
    verticesIntensity['M'] = mbvqVertices["CMYW"][1];
    verticesIntensity['Y'] = mbvqVertices["CMYW"][2];
    verticesIntensity['W'] = mbvqVertices["CMYW"][3];
    verticesIntensity['K'] = mbvqVertices["KRGB"][0];
    verticesIntensity['R'] = mbvqVertices["KRGB"][1];
    verticesIntensity['G'] = mbvqVertices["KRGB"][2];
    verticesIntensity['B'] = mbvqVertices["KRGB"][3];

    // Error Diffusion Matrix initialization
    long double * method1Matrix = new long double [9] {0,0,0,0,0,7.0/16.0,3.0/16.0,5.0/16.0,1.0/16.0};
    
    long double *** image3DTemp = NULL;
    long double *** image3DTempCMY = NULL;
    image3DTemp = new long double **[ROW]();
    image3DTempCMY = new long double **[ROW]();
    for(int i=0; i < ROW; i++) {
        image3DTemp[i] = new long double *[COL]();
        image3DTempCMY[i] = new long double *[COL]();
        for(int j=0; j < COL; j++) {
            image3DTemp[i][j] = new long double [BYTESPERPIXEL];
            image3DTempCMY[i][j] = new long double [BYTESPERPIXEL];
            for(int k=0; k < BYTESPERPIXEL; k++) {
                image3DTemp[i][j][k] = (long double) image3D[i][j][k];
                image3DTempCMY[i][j][k] = 255.0 - ((long double) image3D[i][j][k]);
            }
        }
    }
    
    image3DMBVQ = errorDiffusionSerpentine(image3DMBVQ, image3DTemp, image3DTempCMY, method1Matrix, 3, ROW, COL, BYTESPERPIXEL, mbvqVertices, noVertices, verticesIntensity);
    
    // Write outputs to the Raw files --------
    image3Dto1D(image3DMBVQ, imageToFile, ROW, COL, BYTESPERPIXEL);
    fileWrite(argv[5], imageToFile, IMAGELEN);
    
    freeMemory3D(image3D, ROW, COL, BYTESPERPIXEL);
    freeMemory3D(image3DMBVQ, ROW, COL, BYTESPERPIXEL);
    
    delete[] CMYW1D;
    delete[] MYGC1D;
    delete[] RGMY1D;
    delete[] KRGB1D;
    delete[] RGBM1D;
    delete[] CMGB1D;
    delete [] imageFromFile;
    delete [] imageToFile;
    
}

