//
//  main.cpp
//  hw_1_prob_2_c
//
//  Created by Abinaya Manimaran on 1/26/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include "DIP_MyHeaderFile.h"

using namespace std;

unsigned char *** mirror3DImage(unsigned char *** image3DMirror, unsigned char *** image3D, int ROW, int COL, int BYTESPERPIXEL) {
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            for(int k = 0; k < BYTESPERPIXEL; k++) {
                image3DMirror[i][j][k] = image3D[i][COL-1-j][k];
            }
        }
    }
    return image3DMirror;
}

unsigned char *** invert3DImage(unsigned char *** image3DColorInvert, unsigned char *** image3D, int ROW, int COL, int BYTESPERPIXEL) {
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            for(int k = 0; k < BYTESPERPIXEL; k++) {
                image3DColorInvert[i][j][k] = 255 - image3D[i][j][k];
            }
        }
    }
    return image3DColorInvert;
}

void histogramSpecification(unsigned int * histMapping, float * histCDF, float * histCDFToMap ) {
    for(int i = 0; i < 256; i++) {
        float tempMinDist = abs(histCDFToMap[0] - histCDF[i]);
        unsigned char tempMinIndex = 0;
        for(int j = 1; j < 256; j++) {
            float tempDist = abs(histCDFToMap[j] - histCDF[i]);
            if( tempDist  <= tempMinDist) {
                tempMinDist = tempDist;
                tempMinIndex = j;
            }
        }
        histMapping[i] = (unsigned char)tempMinIndex;
        //cout << (int) histMapping[i] << endl;
    }
}


int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 25){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [row] [col] [bytesPerPixel] [input Original image path] [input Film image path] [input Girl image path] [row of Girl Image] [col of Girl Image] [bytesPerPixel of Girl image] [raw output image path - original mirror] [raw output image path - original invert] [raw output image path - original film effect] [raw output image path - Girl mirror] [raw output image path - Girl invert] [raw output image path - Girl film effect] [text output histogram R] [text output histogram G] [text output histogram B]  [text output Hist Film R] [text output Hist Film G] [text output Hist Film B] [text transfer function R] [text transfer function G] [text transfer function B] " << endl;
        return 0;
    }
    
    // Store the required arguments --------
    int ROW = atoi(argv[1]);
    int COL = atoi(argv[2]);
    int BYTESPERPIXEL = atoi(argv[3]);
    long int IMAGELEN = ROW*COL*BYTESPERPIXEL;
    
    int ROWGIRL = atoi(argv[7]);
    int COLGIRL = atoi(argv[8]);
    int BYTESPERPIXELGIRL = atoi(argv[9]);
    long int IMAGELENGIRL = ROWGIRL*COLGIRL*BYTESPERPIXELGIRL;

    cout << "Number of arguments passed: " << argc << endl;
    cout << "BYTESPERPIXEL: " << BYTESPERPIXEL << endl;
    cout << "ROW: " << ROW << endl;
    cout << "COL: " << COL << endl;
    cout << "File length: " << IMAGELEN << endl;
    cout << "Processing File: " << argv[4] << endl;
    cout << "-----------------------" << endl;
    
    // Declare required input and output datastructures ---------
    unsigned char *imageFromFile = new unsigned char [IMAGELEN]();
    unsigned char *imageMirrorToFile = new unsigned char [IMAGELEN]();
    unsigned char *imageInvertToFile = new unsigned char [IMAGELEN]();
    unsigned char *imageFilmEffectToFile = new unsigned char [IMAGELEN]();
    
    unsigned char *imageFromFileFilm = new unsigned char [IMAGELEN]();

    unsigned char *imageFromFileGirl = new unsigned char [IMAGELENGIRL]();
    unsigned char *imageMirrorToFileGirl = new unsigned char [IMAGELENGIRL]();
    unsigned char *imageInvertToFileGirl = new unsigned char [IMAGELENGIRL]();
    unsigned char *imageFilmEffectToFileGirl = new unsigned char [IMAGELENGIRL]();

    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFile, IMAGELEN);
    fileRead(argv[5], imageFromFileFilm, IMAGELEN);
    fileRead(argv[6], imageFromFileGirl, IMAGELENGIRL);
    
    // Declare and allocate memoory for the images --------
    unsigned char *** image3D = NULL;
    image3D = image1Dto3D(image3D, imageFromFile, ROW, COL, BYTESPERPIXEL);
    
    unsigned char *** image3DFilm = NULL;
    image3DFilm = image1Dto3D(image3DFilm, imageFromFileFilm, ROW, COL, BYTESPERPIXEL);
    
    unsigned char *** image3DGirl = NULL;
    image3DGirl = image1Dto3D(image3DGirl, imageFromFileGirl, ROWGIRL, COLGIRL, BYTESPERPIXELGIRL);
    
    // Declare and allocate memoory for the required data types --------
    
    unsigned char *** image3DMirror = NULL;
    image3DMirror = allocMemory3D(image3DMirror, ROW, COL, BYTESPERPIXEL);
    
    unsigned char *** image3DColorInvert = NULL;
    image3DColorInvert = allocMemory3D(image3DColorInvert, ROW, COL, BYTESPERPIXEL);
    
    unsigned char *** image3DFilmEffect = NULL;
    image3DFilmEffect = allocMemory3D(image3DFilmEffect, ROW, COL, BYTESPERPIXEL);
    
    unsigned char *** image3DMirrorGirl = NULL;
    image3DMirrorGirl = allocMemory3D(image3DMirrorGirl, ROWGIRL, COLGIRL, BYTESPERPIXELGIRL);
    
    unsigned char *** image3DColorInvertGirl = NULL;
    image3DColorInvertGirl = allocMemory3D(image3DColorInvertGirl, ROWGIRL, COLGIRL, BYTESPERPIXELGIRL);
    
    unsigned char *** image3DFilmEffectGirl = NULL;
    image3DFilmEffectGirl = allocMemory3D(image3DFilmEffectGirl, ROWGIRL, COLGIRL, BYTESPERPIXELGIRL);
    
    unsigned char ** image2DRChannelFilmEffect = NULL;
    image2DRChannelFilmEffect = allocMemory2D(image2DRChannelFilmEffect, ROW, COL);
    
    unsigned char ** image2DGChannelFilmEffect = NULL;
    image2DGChannelFilmEffect = allocMemory2D(image2DRChannelFilmEffect, ROW, COL);

    unsigned char ** image2DBChannelFilmEffect = NULL;
    image2DBChannelFilmEffect = allocMemory2D(image2DBChannelFilmEffect, ROW, COL);

    unsigned char ** image2DRChannelFilm = NULL;
    image2DRChannelFilm = seperateChannels(image3DFilm, image2DRChannelFilm, ROW, COL, 0);
    
    unsigned char ** image2DGChannelFilm = NULL;
    image2DGChannelFilm = seperateChannels(image3DFilm, image2DGChannelFilm, ROW, COL, 1);
    
    unsigned char ** image2DBChannelFilm = NULL;
    image2DBChannelFilm = seperateChannels(image3DFilm, image2DBChannelFilm, ROW, COL, 2);
    
    unsigned int *histRChannel = new unsigned int [256]();
    unsigned int *histGChannel = new unsigned int [256]();
    unsigned int *histBChannel = new unsigned int [256]();
    float *histRChannelCDF = new float [256]();
    float *histGChannelCDF = new float [256]();
    float *histBChannelCDF = new float [256]();
    unsigned int *histRChannelFilm = new unsigned int [256]();
    unsigned int *histGChannelFilm = new unsigned int [256]();
    unsigned int *histBChannelFilm = new unsigned int [256]();
    float *histRChannelCDFFilm = new float [256]();
    float *histGChannelCDFFilm = new float [256]();
    float *histBChannelCDFFilm = new float [256]();
    unsigned int *histRChannelMapping = new unsigned int [256]();
    unsigned int *histGChannelMapping = new unsigned int [256]();
    unsigned int *histBChannelMapping = new unsigned int [256]();
    
    // Mirroring the image --------
    image3DMirror = mirror3DImage(image3DMirror, image3D, ROW, COL, BYTESPERPIXEL);
     
    // Inverting the color -------
    image3DColorInvert = invert3DImage(image3DColorInvert, image3DMirror, ROW, COL, BYTESPERPIXEL);
    
    unsigned char ** image2DRChannel = NULL;
    image2DRChannel = seperateChannels(image3DColorInvert, image2DRChannel, ROW, COL, 0);
    
    unsigned char ** image2DGChannel = NULL;
    image2DGChannel = seperateChannels(image3DColorInvert, image2DGChannel, ROW, COL, 1);
    
    unsigned char ** image2DBChannel = NULL;
    image2DBChannel = seperateChannels(image3DColorInvert, image2DBChannel, ROW, COL, 2);

    // Histogram Matching to get Special film effect --------
    // Get the Histogram --------
    histogram2DImage(image2DRChannel, histRChannel, ROW, COL);
    histogram2DImage(image2DGChannel, histGChannel, ROW, COL);
    histogram2DImage(image2DBChannel, histBChannel, ROW, COL);
    
    histogram2DImage(image2DRChannelFilm, histRChannelFilm, ROW, COL);
    histogram2DImage(image2DGChannelFilm, histGChannelFilm, ROW, COL);
    histogram2DImage(image2DBChannelFilm, histBChannelFilm, ROW, COL);
    
    // Calculate normalized histogram --------
    for(int i=0; i < 256;i++){
        histRChannelCDF[i] = histRChannel[i] / (((float)(ROW))*((float)(COL)));
        histGChannelCDF[i] = histGChannel[i] / (((float)(ROW))*((float)(COL)));
        histBChannelCDF[i] = histBChannel[i] / (((float)(ROW))*((float)(COL)));
        histRChannelCDFFilm[i] = histRChannelFilm[i] / (((float)(ROW))*((float)(COL)));
        histGChannelCDFFilm[i] = histGChannelFilm[i] / (((float)(ROW))*((float)(COL)));
        histBChannelCDFFilm[i] = histBChannelFilm[i] / (((float)(ROW))*((float)(COL)));
        //cout << (float) histRChannelCDF[i] << ' ' << (float) histGChannelCDF[i] << ' ' << (float) histBChannelCDF[i] << endl;
    }
    
    // Calculate cdf
    for(int i=0; i< 256; i++) {
        if(i == 0) {
            histRChannelCDF[i] = histRChannelCDF[i];
            histGChannelCDF[i] = histGChannelCDF[i];
            histBChannelCDF[i] = histBChannelCDF[i];
            histRChannelCDFFilm[i] = histRChannelCDFFilm[i];
            histGChannelCDFFilm[i] = histGChannelCDFFilm[i];
            histBChannelCDFFilm[i] = histBChannelCDFFilm[i];
            
        }
        else{
            histRChannelCDF[i] = histRChannelCDF[i] + histRChannelCDF[i-1];
            histGChannelCDF[i] = histGChannelCDF[i] + histGChannelCDF[i-1];
            histBChannelCDF[i] = histBChannelCDF[i] + histBChannelCDF[i-1];
            histRChannelCDFFilm[i] = histRChannelCDFFilm[i] + histRChannelCDFFilm[i-1];
            histGChannelCDFFilm[i] = histGChannelCDFFilm[i] + histGChannelCDFFilm[i-1];
            histBChannelCDFFilm[i] = histBChannelCDFFilm[i] + histBChannelCDFFilm[i-1];
        }
        //cout << (float) histRChannelCDF[i] << ' ' << (float) histGChannelCDF[i] << ' ' << (float) histBChannelCDF[i] << endl;
    }

    // Histogram mapping and getting a one-on-one transfer function for every channel
    histogramSpecification(histRChannelMapping,histRChannelCDF,histRChannelCDFFilm);
    histogramSpecification(histGChannelMapping,histGChannelCDF,histGChannelCDFFilm);
    histogramSpecification(histBChannelMapping,histBChannelCDF,histBChannelCDFFilm);
    
    // Change the R, G and B channel pixels based on Transfer Function
    unsigned char tempR, tempG, tempB;
    for(int i=0; i < ROW; i++) {
        for(int j=0; j < COL; j++) {
            tempR = image3DColorInvert[i][j][0];
            tempG = image3DColorInvert[i][j][1];
            tempB = image3DColorInvert[i][j][2];
            image3DFilmEffect[i][j][0] = histRChannelMapping[tempR];
            image3DFilmEffect[i][j][1] = histGChannelMapping[tempG];
            image3DFilmEffect[i][j][2] = histBChannelMapping[tempB];
        }
    }
    
    // Girl Image - Mirror, Invert and map the pixels according to the transfer function
    image3DMirrorGirl = mirror3DImage(image3DMirrorGirl, image3DGirl, ROWGIRL, COLGIRL, BYTESPERPIXELGIRL);
    
    image3DColorInvertGirl = invert3DImage(image3DColorInvertGirl, image3DMirrorGirl, ROWGIRL, COLGIRL, BYTESPERPIXELGIRL);
    
    for(int i=0; i < ROWGIRL; i++) {
        for(int j=0; j < COLGIRL; j++) {
            tempR = image3DColorInvertGirl[i][j][0];
            tempG = image3DColorInvertGirl[i][j][1];
            tempB = image3DColorInvertGirl[i][j][2];
            image3DFilmEffectGirl[i][j][0] = histRChannelMapping[tempR];
            image3DFilmEffectGirl[i][j][1] = histGChannelMapping[tempG];
            image3DFilmEffectGirl[i][j][2] = histBChannelMapping[tempB];
        }
    }
    
    // Write outputs to the Raw files --------
    image3Dto1D(image3DMirror, imageMirrorToFile, ROW, COL, BYTESPERPIXEL);
    fileWrite(argv[10], imageMirrorToFile, IMAGELEN);
    
    image3Dto1D(image3DColorInvert, imageInvertToFile, ROW, COL, BYTESPERPIXEL);
    fileWrite(argv[11], imageInvertToFile, IMAGELEN);
    
    image3Dto1D(image3DFilmEffect, imageFilmEffectToFile, ROW, COL, BYTESPERPIXEL);
    fileWrite(argv[12], imageFilmEffectToFile, IMAGELEN);

    image3Dto1D(image3DMirrorGirl, imageMirrorToFileGirl, ROWGIRL, COLGIRL, BYTESPERPIXELGIRL);
    fileWrite(argv[13], imageMirrorToFileGirl, IMAGELENGIRL);
    
    image3Dto1D(image3DColorInvertGirl, imageInvertToFileGirl, ROWGIRL, COLGIRL, BYTESPERPIXELGIRL);
    fileWrite(argv[14], imageInvertToFileGirl, IMAGELENGIRL);
    
    image3Dto1D(image3DFilmEffectGirl, imageFilmEffectToFileGirl, ROWGIRL, COLGIRL, BYTESPERPIXELGIRL);
    fileWrite(argv[15], imageFilmEffectToFileGirl, IMAGELENGIRL);
    
    fileWriteHist(argv[16], histRChannel);
    fileWriteHist(argv[17], histGChannel);
    fileWriteHist(argv[18], histBChannel);
    fileWriteHist(argv[19], histRChannelFilm);
    fileWriteHist(argv[20], histGChannelFilm);
    fileWriteHist(argv[21], histBChannelFilm);
    fileWriteHist(argv[22], histRChannelMapping);
    fileWriteHist(argv[23], histGChannelMapping);
    fileWriteHist(argv[24], histBChannelMapping);

    
    // Deallocate memory --------
    freeMemory3D(image3D, ROW, COL, BYTESPERPIXEL);
    freeMemory3D(image3DMirror,  ROW, COL, BYTESPERPIXEL);
    freeMemory3D(image3DColorInvert,  ROW, COL, BYTESPERPIXEL);
    freeMemory3D(image3DFilmEffect,  ROW, COL, BYTESPERPIXEL);
    freeMemory3D(image3DMirrorGirl, ROWGIRL, COLGIRL, BYTESPERPIXELGIRL);
    freeMemory3D(image3DColorInvertGirl, ROWGIRL, COLGIRL, BYTESPERPIXELGIRL);
    freeMemory3D(image3DFilmEffectGirl, ROWGIRL, COLGIRL, BYTESPERPIXELGIRL);

    freeMemory2D(image2DRChannel, ROW, COL);
    freeMemory2D(image2DGChannel, ROW, COL);
    freeMemory2D(image2DBChannel, ROW, COL);
    freeMemory2D(image2DRChannelFilm, ROW, COL);
    freeMemory2D(image2DGChannelFilm, ROW, COL);
    freeMemory2D(image2DBChannelFilm, ROW, COL);
    freeMemory2D(image2DRChannelFilmEffect, ROW, COL);
    freeMemory2D(image2DGChannelFilmEffect, ROW, COL);
    freeMemory2D(image2DBChannelFilmEffect, ROW, COL);
    
    delete[] imageFromFile;
    delete[] imageMirrorToFile;
    delete[] imageInvertToFile;
    delete[] imageFilmEffectToFile;
    delete[] imageFromFileFilm;
    delete[] imageFromFileGirl;
    delete[] imageMirrorToFileGirl;
    delete[] imageInvertToFileGirl;
    delete[] imageFilmEffectToFileGirl;
    
    delete[] histRChannel;
    delete[] histGChannel;
    delete[] histBChannel;
    delete[] histRChannelCDF;
    delete[] histGChannelCDF;
    delete[] histBChannelCDF;
    delete[] histRChannelFilm;
    delete[] histGChannelFilm;
    delete[] histBChannelFilm;
    delete[] histRChannelCDFFilm;
    delete[] histGChannelCDFFilm;
    delete[] histBChannelCDFFilm;
    delete[] histRChannelMapping;
    delete[] histGChannelMapping;
    delete[] histBChannelMapping;

}

    
