//
//  main.cpp
//  hw_2_prob_3_d2
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
#include "STKMasks.h"

using namespace std;


unsigned int insertLookUpTable(unsigned char x, unsigned char y, unsigned char ** lookUpTable, unsigned int lookUpTableIndex) {
    
    int flag = 0;
    for (int i = 0; i <= lookUpTableIndex; i++) {
        if ((x == lookUpTable[i][0]) and (y == lookUpTable[i][1])) {
            flag = 1;
        }
        else if ((y == lookUpTable[i][0]) and (x == lookUpTable[i][1])) {
            flag = 1;
        }
    }
    if (flag == 0) {
        if (x < y ) {
            lookUpTable[lookUpTableIndex][0] = x;
            lookUpTable[lookUpTableIndex][1] = y; }
        else {
            lookUpTable[lookUpTableIndex][0] = y;
            lookUpTable[lookUpTableIndex][1] = x;
        }
        //cout << (int)lookUpTable[lookUpTableIndex][0] << ' ' << (int)lookUpTable[lookUpTableIndex][1] << endl;
        return (lookUpTableIndex + 1);
    }
    else { return lookUpTableIndex; }
    
}



unsigned char ** connectedComponentLabels( unsigned char ** image2DConnectedComponent, unsigned char ** lookUpTable, int newLabel, int ROW, int COL) {
    
    // Connected Component Analysis - stage 1
    const int NOCONNECTEDCOMPS = 4;
    unsigned int loopUpTableIndex = 0;

    for(int i=0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            if (image2DConnectedComponent[i][j] != 0) {
                
                // Get the 4 connected pixels for analysis
                unsigned char * tempPixelArray = new unsigned char [NOCONNECTEDCOMPS]();
                if((i-1 >= 0) and (j-1 >= 0) and (i-1 <= ROW-1) and (j-1 <= COL-1)) {
                    tempPixelArray[0] = image2DConnectedComponent[i-1][j-1];}
                if((i-1 >= 0) and (j >= 0) and (i-1 <= ROW-1) and (j <= COL-1)) {
                    tempPixelArray[1] = image2DConnectedComponent[i-1][j];}
                if((i-1 >= 0) and (j+1 >= 0) and (i-1 <= ROW-1) and (j+1 <= COL-1)) {
                    tempPixelArray[2] = image2DConnectedComponent[i-1][j+1];}
                if((i >= 0) and (j-1 >= 0) and (i <= ROW-1) and (j-1 <= COL-1)) {
                    tempPixelArray[3] = image2DConnectedComponent[i][j-1];}
                
                // Get connected component for i,j pixel location
                int toAssign = 500;
                int toAssignFlag = 0;
                for(int p = 0; p < NOCONNECTEDCOMPS; p++) {
                    if (tempPixelArray[p] != 0){
                        if (tempPixelArray[p] < toAssign) {
                            toAssign = tempPixelArray[p];
                            toAssignFlag = 1;
                        }
                    }
                }
                if(toAssignFlag == 0) {
                    image2DConnectedComponent[i][j] = newLabel;
                    newLabel++; }
                else{ image2DConnectedComponent[i][j] = toAssign;}
                
                // Frame the look up table for next stage
                int xFlag = 0;
                for(int p = 0; p < NOCONNECTEDCOMPS; p++) {
                    if (tempPixelArray[p] != 0) {
                        if (xFlag == 0) { xFlag = tempPixelArray[p]; }
                        else{
                            if (xFlag != tempPixelArray[p]) {
                                loopUpTableIndex = insertLookUpTable(xFlag, tempPixelArray[p], lookUpTable, loopUpTableIndex);
                                //cout << xFlag << ' ' << (int) tempPixelArray[p] << ' ' << loopUpTableIndex << endl;
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int i = 0; i < loopUpTableIndex; i++) {
            //cout << (int) lookUpTable[i][0] << ' ' << (int) lookUpTable[i][1] << endl;
        }

        cout << "new label count " << newLabel << endl;

        // Connected Component Analysis - Stage 2
        for (int label = newLabel; label >= 2; label--) {
            //int label = 133;
            //cout << "Checking label ---" << label << endl;
            unsigned char * tempLabelMatchedArray = new unsigned char [100] ();
            int tempCount = 0;
            for (int p = 0; p < loopUpTableIndex; p++) {
                if (lookUpTable[p][1] == label) {
                    tempLabelMatchedArray[tempCount] = lookUpTable[p][0];
                    //cout << (int)tempLabelMatchedArray[tempCount] << endl;
                    tempCount ++;
                    lookUpTable[p][0] = 0;
                    lookUpTable[p][1] = 0;
                }
            }
            
            unsigned char destinMinLabel = tempLabelMatchedArray[0];
            int noMatched = 0;
            for (int q = 0; q <100 ; q++) {
                if(tempLabelMatchedArray[q] == 0) {
                    //cout << q << " Breakingg--" << endl;
                    noMatched = q;
                    break; }
                if(tempLabelMatchedArray[q] > tempLabelMatchedArray[q+1] ) {
                    if (tempLabelMatchedArray[q+1] != 0) {
                        destinMinLabel = tempLabelMatchedArray[q+1];
                        //cout << q << ' ' << (int)tempLabelMatchedArray[q] <<' ' <<  (int) tempLabelMatchedArray[q+1] << ' ' << (int) destinMinLabel << endl;
                    }
                }
            }
            
            
            
            if (destinMinLabel != 0 and noMatched != 0) {
                //cout << "Min Label " << (int) destinMinLabel << ' ' << noMatched << endl;
                for(int i=0; i < ROW; i++) {
                    for(int j=0; j< COL; j++) {
                        if (image2DConnectedComponent[i][j] == label) {
                            image2DConnectedComponent[i][j] = destinMinLabel;
                        }
                    }
                }
                
                for(int i=0; i < ROW; i++) {
                    for(int j=0; j< COL; j++) {
                        for(int k = 0; k < noMatched; k++) {
                            if (image2DConnectedComponent[i][j] == tempLabelMatchedArray[k]) {
                                //cout << "True" << ' ' << (int) image2DConnectedComponent[i][j] << endl;
                                image2DConnectedComponent[i][j] = destinMinLabel;
                                //cout << ' ' << (int) image2DConnectedComponent[i][j] << endl;
                                
                            }
                        }
                    }
                }
            }
        }
    return image2DConnectedComponent;
}
    

int * getUniqueLabels( int * uniqueLabels, unsigned char ** image2DConnectedComponent, int ROW, int COL) {
    unsigned int * histLabels = new unsigned int [500]();
    for(int i=0; i < ROW; i++) {
      for(int j=0; j<COL; j++) {
          for(int k=0; k < 500; k++) {
              if(image2DConnectedComponent[i][j] == k ){
                  histLabels[k] ++;
              }
          }
      }
    }
    int tempCount = 0;
    for (int k = 1; k < 500; k++) {
      if (histLabels[k] > 0) {
          uniqueLabels[tempCount] = k;
          //cout << uniqueLabels[tempCount] << endl;
          tempCount ++;
      }
    }
    return uniqueLabels;
}




int main(int argc, char * argv[]) {
    
    // Check for proper syntax --------
    if (argc != 9){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [row] [col] [bytesPerPixel]  [input board image path] [output Binary image path] [output Connected Components image path] [output Squares image path] [output XORed image path]" << endl;
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
    unsigned char *imageToFileConnectedComp = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileSquare1s = new unsigned char [IMAGELEN]();
    unsigned char *imageToFileXor = new unsigned char [IMAGELEN]();
    
    // Read raw file and store in 1D array --------
    fileRead(argv[4], imageFromFile, IMAGELEN);
    
    // Declare and allocate memoory for the images --------
    unsigned char ** image2D = NULL;
    image2D = image1Dto2D(image2D, imageFromFile, ROW, COL);
    
    unsigned char ** image2DBinary = NULL;
    image2DBinary = allocMemory2D(image2DBinary, ROW, COL);
    
    unsigned char ** image2DConnectedComponent = NULL;
    image2DConnectedComponent = allocMemory2D(image2DConnectedComponent, ROW, COL);
    
    unsigned char ** image2DSquare1s = NULL;
    image2DSquare1s = allocMemory2D(image2DSquare1s, ROW, COL);
    
    unsigned char ** image2DXor = NULL;
    image2DXor = allocMemory2D(image2DXor, ROW, COL);
    
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
    // Also initialize Dilated image to the Binary image
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            if( image2DBinary[i][j] == 255) {
                image2DBinary[i][j] = 0;
                image2DConnectedComponent[i][j] = 0;
                image2DXor[i][j] = 0;
            }
            else {
                image2DBinary[i][j] = 1;
                image2DConnectedComponent[i][j] = 1;
                image2DXor[i][j] = 1;
            }
        }
    }
    
    // Stage 1 and 2 of Connected Component Analysis
    unsigned char ** lookUpTable = NULL;
    lookUpTable = allocMemory2D(lookUpTable, 10000, 2);
    image2DConnectedComponent = connectedComponentLabels(image2DConnectedComponent, lookUpTable, 2, ROW, COL);
    
    // Get Unique labels from Connected Components
    int * uniqueLabels = new int [16]();
    uniqueLabels = getUniqueLabels(uniqueLabels, image2DConnectedComponent, ROW, COL);
    
    // Get startX, startY for every unique component
    unsigned int *startXArray = new unsigned int [16]();
    unsigned int *startYArray = new unsigned int [16]();
    
    
    for(int k = 0; k < 16; k++) {
        // Getting x and y values for every label
        unsigned int * tempXArray = new unsigned int [3000]();
        unsigned int * tempYArray = new unsigned int [3000]();
        int tempCount = 0;
        for (int i =0; i < ROW; i++) {
            for (int j=0; j < COL; j++) {
                if (image2DConnectedComponent[i][j] == uniqueLabels[k]) {
                    tempXArray[tempCount] = i;
                    tempYArray[tempCount] = j;
                    tempCount++;
                }
            }
        }
        // Get minimum x and y value
        unsigned int minY =  tempYArray[0];
        unsigned int minYIndex = 0;
        for(int i = 1; i < 3000; i++) {
            if( tempYArray[i] != 0) {
                if (tempYArray[i] < minY) {
                    minY = tempYArray[i];
                    minYIndex = i;
                }
            }
        }
        int minX = tempXArray[minYIndex];
        startXArray[k] = minX;
        startYArray[k] = minY;
        cout << uniqueLabels[k]  << " - Label's Start x and y: " << startXArray[k] << ' ' << startYArray[k] << endl;
    }
    
    // Get square size from the 1st jigsaw
    int firstLabel = uniqueLabels[0];
    int minY = startYArray[0];
    int squareSize = 0;
    for(int i=0; i<ROW; i++){
        if(image2DConnectedComponent[i][minY] == firstLabel) {
            squareSize++;
        }
    }
    cout << "\nSqaure Size Found to be :" << squareSize << endl;
    
    // Framing squares of 1's with acquired start x and y of Connected components
    for (int k=0; k < 16; k++) {
        for(int i= startXArray[k]; i <= (startXArray[k]+squareSize-1); i++) {
            for(int j= startYArray[k] ; j <= (startYArray[k]+squareSize-1); j++) {
                image2DSquare1s[i][j] = uniqueLabels[k];
            }
        }
    }
    
    // xor operation and store in another matrix
    for(int i=0; i < ROW; i++) {
        for(int j=0; j<COL; j++) {
            if ((image2DConnectedComponent[i][j] ^ image2DSquare1s[i][j]) == 0) {
                image2DXor[i][j] = 0;
            }
            else{ image2DXor[i][j] = 1; } //image2DSquare1s[i][j]; }
        }
    }
    
    // Initialize maps for protrusion and holes and find them
    map <int, unsigned char * > protrusionsInfo;
    map <int, unsigned char * > holesInfo;
    map <int, unsigned char * > protrusionsInfoVertRefl;
    map <int, unsigned char * > holesInfoVertRefl;
    map <int, unsigned char * > protrusionsInfoHorizRefl;
    map <int, unsigned char * > holesInfoHorizRefl;
    
    
    int checkOffset = 5;
    int halfLength = squareSize / 2.0;
    
    for(int k = 0; k < 16; k++) {
        unsigned char * tempProtrusionsInfo = new unsigned char [4]();
        unsigned char * tempHolesInfo = new unsigned char [4]();
        
        cout << "\n------ Analysis of component with label " << uniqueLabels[k] << endl;
        int midX = startXArray[k] + (squareSize / 2.0);
        int midY = startYArray[k] + (squareSize / 2.0);
        cout << "Mid Points " << midX << ' ' << midY << endl;
        
        int topTrackCount = 0;
        for(int i = midX; i > (midX-halfLength-checkOffset); i--) {
            if (image2DXor[i][midY] == 1) {
                if( topTrackCount < halfLength) {
                    cout << "Top - Hole Found" << endl;
                    tempHolesInfo[0] = 1;
                    break;
                }
                else {
                    cout << "Top - Protrusion Found" << endl;
                    tempProtrusionsInfo[0] = 1;
                    break;
                }
            }
            topTrackCount ++;
        }
        
        int rightTrackCount = 0;
        for(int j = midY; j <= (midY+halfLength+checkOffset); j++ ) {
            if (image2DXor[midX][j] == 1) {
                if( rightTrackCount < halfLength) {
                    cout << "Right - Hole Found" << endl;
                    tempHolesInfo[1] = 1;
                    break;
                }
                else {
                    cout << "Right - Protrusion Found" << endl;
                    tempProtrusionsInfo[1] = 1;
                    break;
                }
            }
            rightTrackCount ++;
        }
        
        int bottomTrackCount = 0;
        for(int i = midX; i < (midX+halfLength+checkOffset); i++) {
            if (image2DXor[i][midY] == 1) {
                if( bottomTrackCount < halfLength) {
                    cout << "Bottom - Hole Found" << endl;
                    tempHolesInfo[2] = 1;
                    break;
                }
                else {
                    cout << "Bottom - Protrusion Found" << endl;
                    tempProtrusionsInfo[2] = 1;
                    break;
                }
            }
            bottomTrackCount ++;
        }
        
        int leftTrackCount = 0;
        for(int j = midY; j > (midY-halfLength-checkOffset); j--) {
            if (image2DXor[midX][j] == 1) {
                if( leftTrackCount < halfLength) {
                    cout << "Left - Hole Found" << endl;
                    tempHolesInfo[3] = 1;
                    break;
                }
                else {
                    cout << "Left - Protrusion Found" << endl;
                    tempProtrusionsInfo[3] = 1;
                    break;
                }
            }
            leftTrackCount ++;
        }
        
        holesInfo[uniqueLabels[k]] = tempHolesInfo;
        protrusionsInfo[uniqueLabels[k]] = tempProtrusionsInfo;
    }
    
    
    // Reflecting Vertically
    for (int k=0; k < 16; k++) {
        int label = uniqueLabels[k];
        unsigned char * tempProtrusionsInfo = new unsigned char [4]();
        unsigned char * tempHolesInfo = new unsigned char [4]();
        for(int i=0; i < 4; i++) {
            if (i == 0){
                tempProtrusionsInfo[i] = protrusionsInfo[label][2];
                tempHolesInfo[i] = holesInfo[label][2];
            }
            else if(i == 2) {
                tempProtrusionsInfo[i] = protrusionsInfo[label][0];
                tempHolesInfo[i] = holesInfo[label][0];
            }
            else{
                tempProtrusionsInfo[i] = protrusionsInfo[label][i];
                tempHolesInfo[i] = holesInfo[label][i];
            }
        }
        protrusionsInfoVertRefl[label] = tempProtrusionsInfo;
        holesInfoVertRefl[label] = tempHolesInfo;
    }
    
    // Reflecting Horizontally
    for (int k=0; k < 16; k++) {
        int label = uniqueLabels[k];
        unsigned char * tempProtrusionsInfo = new unsigned char [4]();
        unsigned char * tempHolesInfo = new unsigned char [4]();
        for(int i=0; i < 4; i++) {
            if (i == 1){
                tempProtrusionsInfo[i] = protrusionsInfo[label][3];
                tempHolesInfo[i] = holesInfo[label][3];
            }
            else if(i == 3) {
                tempProtrusionsInfo[i] = protrusionsInfo[label][1];
                tempHolesInfo[i] = holesInfo[label][1];
            }
            else{
                tempProtrusionsInfo[i] = protrusionsInfo[label][i];
                tempHolesInfo[i] = holesInfo[label][i];
            }
        }
        protrusionsInfoHorizRefl[label] = tempProtrusionsInfo;
        holesInfoHorizRefl[label] = tempHolesInfo;
       // cout << (int) protrusionsInfoHorizRefl[label][0] << ' ' << (int) protrusionsInfoHorizRefl[label][1] << ' ' << (int) protrusionsInfoHorizRefl[label][2] << ' ' << (int) protrusionsInfoHorizRefl[label][3] << endl;
    }
    
    
    // Find unique jigsaw pieces and store it in a map with label and its count
    cout << "\nMatching jigsaws using protrusions and holes position with rotation also" << endl;
    map < int, int > jigsawLabel;
    map < int, int > jigsawLabelCount;
    jigsawLabel[0] = uniqueLabels[0];
    jigsawLabelCount[0] = 1;
    int tempCount = 1;
    
   for(int newLabelIndex = 1; newLabelIndex < 16; newLabelIndex++) {
        int newLabel = uniqueLabels[newLabelIndex];
    //int newLabel = 41;
        int newLabelMatchFlag = 0;
        
        for( int oldLabelIndex = 0; oldLabelIndex < tempCount; oldLabelIndex++ ){
            int oldLabel = jigsawLabel[oldLabelIndex];
            
            // Rotation and checking
            for(int k = 0; k < 4; k++) {
                int checkFlag = 0;
                for(int i = 0; i < 4; i++) {
                    int j = i+k;
                    if ( j >= 4) { j = j-4; }
                    //cout << i << ' ' << j << endl;
                    if((holesInfo[oldLabel][i] == holesInfo[newLabel][j]) and (protrusionsInfo[oldLabel][i] == protrusionsInfo[newLabel][j])) {
                        checkFlag ++;
                    }
                }
                //cout << checkFlag << endl;
                if(checkFlag == 4) {
                    cout << newLabel << " Labelled Jigsaw matched after " << k << " rotation with " << oldLabel << endl;
                    jigsawLabelCount[oldLabelIndex] ++;
                    newLabelMatchFlag = 1;
                    break;
                }
            }
            if ( newLabelMatchFlag == 1) { break;}
            
            // Rotation and checking with vertically reflected ones
            for(int k = 0; k < 4; k++) {
                int checkFlag = 0;
                for(int i = 0; i < 4; i++) {
                    int j = i+k;
                    if ( j >= 4) { j = j-4; }
                    //cout << i << ' ' << j << endl;
                    if((holesInfo[oldLabel][i] == holesInfoVertRefl[newLabel][j]) and (protrusionsInfo[oldLabel][i] == protrusionsInfoVertRefl[newLabel][j])) {
                        checkFlag ++;
                    }
                }
                //cout << checkFlag << endl;
                if(checkFlag == 4) {
                    cout << newLabel << " Labelled Jigsaw matched after " << k << " rotation and vertical reflection with " << oldLabel << endl;
                    jigsawLabelCount[oldLabelIndex] ++;
                    newLabelMatchFlag = 1;
                    break;
                }
            }
            if ( newLabelMatchFlag == 1) { break;}
            
            
            // Rotation and checking with Horizontally reflected ones
            for(int k = 0; k < 4; k++) {
                int checkFlag = 0;
                for(int i = 0; i < 4; i++) {
                    int j = i+k;
                    if ( j >= 4) { j = j-4; }
                    //cout << i << ' ' << j << endl;
                    if((holesInfo[oldLabel][i] == holesInfoHorizRefl[newLabel][j]) and (protrusionsInfo[oldLabel][i] == protrusionsInfoHorizRefl[newLabel][j])) {
                        checkFlag ++;
                    }
                }
                //cout << checkFlag << endl;
                if(checkFlag == 4) {
                    cout << newLabel << " Labelled Jigsaw matched after " << k << " rotation and horizontal reflection with " << oldLabel << endl;
                    jigsawLabelCount[oldLabelIndex] ++;
                    newLabelMatchFlag = 1;
                    break;
                }
            }
            if ( newLabelMatchFlag == 1) { break;}
            
            
        }
        if (newLabelMatchFlag == 0) {
            jigsawLabel[tempCount] = newLabel;
            jigsawLabelCount[tempCount] = 1;
            tempCount++;
        }
    }
    
    //Print the outputs
    for(int i = 0; i < tempCount; i++) {
        cout << "\nJigsaw with label: " << jigsawLabel[i] << " Count: " << jigsawLabelCount[i] << endl;
    }
    cout << "\nUnique number of jigsaws: " << tempCount << endl;
   
    
    // Changeing 1's to 255 for viewing purpose
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            if(image2DConnectedComponent[i][j] > 1) {
                image2DConnectedComponent[i][j] = 255;
            }
            if(image2DSquare1s[i][j] > 1) {
                image2DSquare1s[i][j] = 255;
            }
            if(image2DXor[i][j] == 1) {
                image2DXor[i][j] = 255;
            }
        }
    }
    
    
    // Writing the Final iteration First stage and Second Stage output
    image2Dto1D(image2DConnectedComponent, imageToFileConnectedComp, ROW, COL);
    fileWrite(argv[6], imageToFileConnectedComp, IMAGELEN);
    
    image2Dto1D(image2DSquare1s, imageToFileSquare1s, ROW, COL);
    fileWrite(argv[7], imageToFileSquare1s, IMAGELEN);
    
    image2Dto1D(image2DXor, imageToFileXor, ROW, COL);
    fileWrite(argv[8], imageToFileXor, IMAGELEN);
    
    // Deallocate all memories
    freeMemory2D(image2D, ROW, COL);
    freeMemory2D(image2DConnectedComponent, ROW, COL);
    freeMemory2D(image2DBinary, ROW, COL);
    freeMemory2D(image2DSquare1s, ROW, COL);
    freeMemory2D(image2DXor, ROW, COL);
    
    delete  [] imageFromFile;
    delete  [] imageToFileBinary;
    delete  [] imageToFileConnectedComp;
    delete  [] imageToFileSquare1s;
    delete  [] imageToFileXor;
    
}

