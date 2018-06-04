//
//  STKMasks.h
//  hw_2_prob_3_a
//
//  Created by Abinaya Manimaran on 2/17/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//

#ifndef STKMasks_h
#define STKMasks_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <map>
using namespace std;

unsigned char ** returnShrinkConditionalMasks(int bondValue){
    
    const int MASKSIZE = 9;
    
    // TYPE : S; BOND: 1
    unsigned char ** B1 = NULL;
    B1 = new unsigned char *[4]();
    B1[0] = new unsigned char [MASKSIZE] {0,0,1,0,1,0,0,0,0};
    B1[1] = new unsigned char [MASKSIZE] {1,0,0,0,1,0,0,0,0};
    B1[2] = new unsigned char [MASKSIZE] {0,0,0,0,1,0,1,0,0};
    B1[3] = new unsigned char [MASKSIZE] {0,0,0,0,1,0,0,0,1};
    
    // TYPE : S; BOND: 2
    unsigned char ** B2 = NULL;
    B2 = new unsigned char *[4]();
    B2[0] = new unsigned char [MASKSIZE] {0,0,0,0,1,1,0,0,0};
    B2[1] = new unsigned char [MASKSIZE] {0,1,0,0,1,0,0,0,0};
    B2[2] = new unsigned char [MASKSIZE] {0,0,0,1,1,0,0,0,0};
    B2[3] = new unsigned char [MASKSIZE] {0,0,0,0,1,0,0,1,0};
    
    // TYPE : S; BOND: 3
    unsigned char ** B3 = NULL;
    B3 = new unsigned char *[8]();
    B3[0] = new unsigned char [MASKSIZE] {0,0,1,0,1,1,0,0,0};
    B3[1] = new unsigned char [MASKSIZE] {0,1,1,0,1,0,0,0,0};
    B3[2] = new unsigned char [MASKSIZE] {1,1,0,0,1,0,0,0,0};
    B3[3] = new unsigned char [MASKSIZE] {1,0,0,1,1,0,0,0,0};
    B3[4] = new unsigned char [MASKSIZE] {0,0,0,1,1,0,1,0,0};
    B3[5] = new unsigned char [MASKSIZE] {0,0,0,0,1,0,1,1,0};
    B3[6] = new unsigned char [MASKSIZE] {0,0,0,0,1,0,0,1,1};
    B3[7] = new unsigned char [MASKSIZE] {0,0,0,0,1,1,0,0,1};
    
    // TYPE : TK, STK; BOND: 4
    unsigned char ** B4 = NULL;
    B4 = new unsigned char *[4]();
    B4[0] = new unsigned char [MASKSIZE] {0,0,1,0,1,1,0,0,1};
    B4[1] = new unsigned char [MASKSIZE] {1,1,1,0,1,0,0,0,0};
    B4[2] = new unsigned char [MASKSIZE] {1,0,0,1,1,0,1,0,0};
    B4[3] = new unsigned char [MASKSIZE] {0,0,0,0,1,0,1,1,1};
    
    // TYPE : ST, ST; BOND: 5
    unsigned char ** B5 = NULL;
    B5 = new unsigned char *[8]();
    B5[0] = new unsigned char [MASKSIZE] {1,1,0,0,1,1,0,0,0};
    B5[1] = new unsigned char [MASKSIZE] {0,1,0,0,1,1,0,0,1};
    B5[2] = new unsigned char [MASKSIZE] {0,1,1,1,1,0,0,0,0};
    B5[3] = new unsigned char [MASKSIZE] {0,0,1,0,1,1,0,1,0};
    B5[4] = new unsigned char [MASKSIZE] {0,1,1,0,1,1,0,0,0};
    B5[5] = new unsigned char [MASKSIZE] {1,1,0,1,1,0,0,0,0};
    B5[6] = new unsigned char [MASKSIZE] {0,0,0,1,1,0,1,1,0};
    B5[7] = new unsigned char [MASKSIZE] {0,0,0,0,1,1,0,1,1};
    
    // TYPE : ST, STK; BOND: 6
    unsigned char ** B6 = NULL;
    B6 = new unsigned char *[10]();
    B6[0] = new unsigned char [MASKSIZE] {1,1,0,0,1,1,0,0,1};
    B6[1] = new unsigned char [MASKSIZE] {0,1,1,1,1,0,1,0,0};
    B6[2] = new unsigned char [MASKSIZE] {1,1,1,0,1,1,0,0,0};
    B6[3] = new unsigned char [MASKSIZE] {0,1,1,0,1,1,0,0,1};
    B6[4] = new unsigned char [MASKSIZE] {1,1,1,1,1,0,0,0,0};
    B6[5] = new unsigned char [MASKSIZE] {1,1,0,1,1,0,1,0,0};
    B6[6] = new unsigned char [MASKSIZE] {1,0,0,1,1,0,1,1,0};
    B6[7] = new unsigned char [MASKSIZE] {0,0,0,1,1,0,1,1,1};
    B6[8] = new unsigned char [MASKSIZE] {0,0,0,0,1,1,1,1,1};
    B6[9] = new unsigned char [MASKSIZE] {0,0,1,0,1,1,0,1,1};
    
    // TYPE : STK; BOND: 7
    unsigned char ** B7 = NULL;
    B7 = new unsigned char *[4]();
    B7[0] = new unsigned char [MASKSIZE] {1,1,1,0,1,1,0,0,1};
    B7[1] = new unsigned char [MASKSIZE] {1,1,1,1,1,0,1,0,0};
    B7[2] = new unsigned char [MASKSIZE] {1,0,0,1,1,0,1,1,1};
    B7[3] = new unsigned char [MASKSIZE] {0,0,1,0,1,1,1,1,1};
    
    // TYPE : STK; BOND: 8
    unsigned char ** B8 = NULL;
    B8 = new unsigned char *[4]();
    B8[0] = new unsigned char [MASKSIZE] {0,1,1,0,1,1,0,1,1};
    B8[1] = new unsigned char [MASKSIZE] {1,1,1,1,1,1,0,0,0};
    B8[2] = new unsigned char [MASKSIZE] {1,1,0,1,1,0,1,1,0};
    B8[3] = new unsigned char [MASKSIZE] {0,0,0,1,1,1,1,1,1};
    
    // TYPE : STK; BOND: 9
    unsigned char ** B9 = NULL;
    B9 = new unsigned char *[8]();
    B9[0] = new unsigned char [MASKSIZE] {1,1,1,0,1,1,0,1,1};
    B9[1] = new unsigned char [MASKSIZE] {0,1,1,0,1,1,1,1,1};
    B9[2] = new unsigned char [MASKSIZE] {1,1,1,1,1,1,1,0,0};
    B9[3] = new unsigned char [MASKSIZE] {1,1,1,1,1,1,0,0,1};
    B9[4] = new unsigned char [MASKSIZE] {1,1,1,1,1,0,1,1,0};
    B9[5] = new unsigned char [MASKSIZE] {1,1,0,1,1,0,1,1,1};
    B9[6] = new unsigned char [MASKSIZE] {1,0,0,1,1,1,1,1,1};
    B9[7] = new unsigned char [MASKSIZE] {0,0,1,1,1,1,1,1,1};
    
    // TYPE : STK; BOND: 10
    unsigned char ** B10 = NULL;
    B10 = new unsigned char *[4]();
    B10[0] = new unsigned char [MASKSIZE] {1,1,1,0,1,1,1,1,1};
    B10[1] = new unsigned char [MASKSIZE] {1,1,1,1,1,1,1,0,1};
    B10[2] = new unsigned char [MASKSIZE] {1,1,1,1,1,0,1,1,1};
    B10[3] = new unsigned char [MASKSIZE] {1,0,1,1,1,1,1,1,1};
    
    // TYPE : K; BOND: 11
    unsigned char ** B11 = NULL;
    B11 = new unsigned char *[4]();
    B11[0] = new unsigned char [MASKSIZE] {1,1,1,1,1,1,0,1,1};
    B11[1] = new unsigned char [MASKSIZE] {1,1,1,1,1,1,1,1,0};
    B11[2] = new unsigned char [MASKSIZE] {1,1,0,1,1,1,1,1,1};
    B11[3] = new unsigned char [MASKSIZE] {0,1,1,1,1,1,1,1,1};
   
    std::map <int, unsigned char ** > conditionalMasks;
    conditionalMasks[1]= B1;
    conditionalMasks[2]= B2;
    conditionalMasks[3]= B3;
    conditionalMasks[4]= B4;
    conditionalMasks[5]= B5;
    conditionalMasks[6]= B6;
    conditionalMasks[7]= B7;
    conditionalMasks[8]= B8;
    conditionalMasks[9]= B9;
    conditionalMasks[10]= B10;
    //conditionalMasks[11]= B11;

    return conditionalMasks[bondValue];
}


unsigned char ** returnThinConditionalMasks(int bondValue){
    
    const int MASKSIZE = 9;
    
    // TYPE : TK, STK; BOND: 4
    unsigned char ** B4 = NULL;
    B4 = new unsigned char *[8]();
    B4[0] = new unsigned char [MASKSIZE] {0,1,0,0,1,1,0,0,0};
    B4[1] = new unsigned char [MASKSIZE] {0,1,0,1,1,0,0,0,0};
    B4[2] = new unsigned char [MASKSIZE] {0,0,0,1,1,0,0,1,0};
    B4[3] = new unsigned char [MASKSIZE] {0,0,0,0,1,1,0,1,0};
    B4[4] = new unsigned char [MASKSIZE] {0,0,1,0,1,1,0,0,1};
    B4[5] = new unsigned char [MASKSIZE] {1,1,1,0,1,0,0,0,0};
    B4[6] = new unsigned char [MASKSIZE] {1,0,0,1,1,0,1,0,0};
    B4[7] = new unsigned char [MASKSIZE] {0,0,0,0,1,0,1,1,1};
    
    // TYPE : ST, ST; BOND: 5
    unsigned char ** B5 = NULL;
    B5 = new unsigned char *[8]();
    B5[0] = new unsigned char [MASKSIZE] {1,1,0,0,1,1,0,0,0};
    B5[1] = new unsigned char [MASKSIZE] {0,1,0,0,1,1,0,0,1};
    B5[2] = new unsigned char [MASKSIZE] {0,1,1,1,1,0,0,0,0};
    B5[3] = new unsigned char [MASKSIZE] {0,0,1,0,1,1,0,1,0};
    B5[4] = new unsigned char [MASKSIZE] {0,1,1,0,1,1,0,0,0};
    B5[5] = new unsigned char [MASKSIZE] {1,1,0,1,1,0,0,0,0};
    B5[6] = new unsigned char [MASKSIZE] {0,0,0,1,1,0,1,1,0};
    B5[7] = new unsigned char [MASKSIZE] {0,0,0,0,1,1,0,1,1};
    
    // TYPE : ST, STK; BOND: 6
    unsigned char ** B6 = NULL;
    B6 = new unsigned char *[10]();
    B6[0] = new unsigned char [MASKSIZE] {1,1,0,0,1,1,0,0,1};
    B6[1] = new unsigned char [MASKSIZE] {0,1,1,1,1,0,1,0,0};
    B6[2] = new unsigned char [MASKSIZE] {1,1,1,0,1,1,0,0,0};
    B6[3] = new unsigned char [MASKSIZE] {0,1,1,0,1,1,0,0,1};
    B6[4] = new unsigned char [MASKSIZE] {1,1,1,1,1,0,0,0,0};
    B6[5] = new unsigned char [MASKSIZE] {1,1,0,1,1,0,1,0,0};
    B6[6] = new unsigned char [MASKSIZE] {1,0,0,1,1,0,1,1,0};
    B6[7] = new unsigned char [MASKSIZE] {0,0,0,1,1,0,1,1,1};
    B6[8] = new unsigned char [MASKSIZE] {0,0,0,0,1,1,1,1,1};
    B6[9] = new unsigned char [MASKSIZE] {0,0,1,0,1,1,0,1,1};
    
    // TYPE : STK; BOND: 7
    unsigned char ** B7 = NULL;
    B7 = new unsigned char *[4]();
    B7[0] = new unsigned char [MASKSIZE] {1,1,1,0,1,1,0,0,1};
    B7[1] = new unsigned char [MASKSIZE] {1,1,1,1,1,0,1,0,0};
    B7[2] = new unsigned char [MASKSIZE] {1,0,0,1,1,0,1,1,1};
    B7[3] = new unsigned char [MASKSIZE] {0,0,1,0,1,1,1,1,1};
    
    // TYPE : STK; BOND: 8
    unsigned char ** B8 = NULL;
    B8 = new unsigned char *[4]();
    B8[0] = new unsigned char [MASKSIZE] {0,1,1,0,1,1,0,1,1};
    B8[1] = new unsigned char [MASKSIZE] {1,1,1,1,1,1,0,0,0};
    B8[2] = new unsigned char [MASKSIZE] {1,1,0,1,1,0,1,1,0};
    B8[3] = new unsigned char [MASKSIZE] {0,0,0,1,1,1,1,1,1};
    
    // TYPE : STK; BOND: 9
    unsigned char ** B9 = NULL;
    B9 = new unsigned char *[8]();
    B9[0] = new unsigned char [MASKSIZE] {1,1,1,0,1,1,0,1,1};
    B9[1] = new unsigned char [MASKSIZE] {0,1,1,0,1,1,1,1,1};
    B9[2] = new unsigned char [MASKSIZE] {1,1,1,1,1,1,1,0,0};
    B9[3] = new unsigned char [MASKSIZE] {1,1,1,1,1,1,0,0,1};
    B9[4] = new unsigned char [MASKSIZE] {1,1,1,1,1,0,1,1,0};
    B9[5] = new unsigned char [MASKSIZE] {1,1,0,1,1,0,1,1,1};
    B9[6] = new unsigned char [MASKSIZE] {1,0,0,1,1,1,1,1,1};
    B9[7] = new unsigned char [MASKSIZE] {0,0,1,1,1,1,1,1,1};
    
    // TYPE : STK; BOND: 10
    unsigned char ** B10 = NULL;
    B10 = new unsigned char *[4]();
    B10[0] = new unsigned char [MASKSIZE] {1,1,1,0,1,1,1,1,1};
    B10[1] = new unsigned char [MASKSIZE] {1,1,1,1,1,1,1,0,1};
    B10[2] = new unsigned char [MASKSIZE] {1,1,1,1,1,0,1,1,1};
    B10[3] = new unsigned char [MASKSIZE] {1,0,1,1,1,1,1,1,1};
    
    std::map <int, unsigned char ** > conditionalMasks;
    conditionalMasks[4]= B4;
    conditionalMasks[5]= B5;
    conditionalMasks[6]= B6;
    conditionalMasks[7]= B7;
    conditionalMasks[8]= B8;
    conditionalMasks[9]= B9;
    conditionalMasks[10]= B10;
    
    return conditionalMasks[bondValue];
}

unsigned char ** returnSkeletonizeConditionalMasks(int bondValue){
    
    const int MASKSIZE = 9;
    
    // TYPE : TK, STK; BOND: 4
    unsigned char ** B4 = NULL;
    B4 = new unsigned char *[8]();
    B4[0] = new unsigned char [MASKSIZE] {0,1,0,0,1,1,0,0,0};
    B4[1] = new unsigned char [MASKSIZE] {0,1,0,1,1,0,0,0,0};
    B4[2] = new unsigned char [MASKSIZE] {0,0,0,1,1,0,0,1,0};
    B4[3] = new unsigned char [MASKSIZE] {0,0,0,0,1,1,0,1,0};
    B4[4] = new unsigned char [MASKSIZE] {0,0,1,0,1,1,0,0,1};
    B4[5] = new unsigned char [MASKSIZE] {1,1,1,0,1,0,0,0,0};
    B4[6] = new unsigned char [MASKSIZE] {1,0,0,1,1,0,1,0,0};
    B4[7] = new unsigned char [MASKSIZE] {0,0,0,0,1,0,1,1,1};
    
    
    // TYPE : ST, STK; BOND: 6
    unsigned char ** B6 = NULL;
    B6 = new unsigned char *[8]();
    B6[0] = new unsigned char [MASKSIZE] {1,1,1,0,1,1,0,0,0};
    B6[1] = new unsigned char [MASKSIZE] {0,1,1,0,1,1,0,0,1};
    B6[2] = new unsigned char [MASKSIZE] {1,1,1,1,1,0,0,0,0};
    B6[3] = new unsigned char [MASKSIZE] {1,1,0,1,1,0,1,0,0};
    B6[4] = new unsigned char [MASKSIZE] {1,0,0,1,1,0,1,1,0};
    B6[5] = new unsigned char [MASKSIZE] {0,0,0,1,1,0,1,1,1};
    B6[6] = new unsigned char [MASKSIZE] {0,0,0,0,1,1,1,1,1};
    B6[7] = new unsigned char [MASKSIZE] {0,0,1,0,1,1,0,1,1};
    
    // TYPE : STK; BOND: 7
    unsigned char ** B7 = NULL;
    B7 = new unsigned char *[4]();
    B7[0] = new unsigned char [MASKSIZE] {1,1,1,0,1,1,0,0,1};
    B7[1] = new unsigned char [MASKSIZE] {1,1,1,1,1,0,1,0,0};
    B7[2] = new unsigned char [MASKSIZE] {1,0,0,1,1,0,1,1,1};
    B7[3] = new unsigned char [MASKSIZE] {0,0,1,0,1,1,1,1,1};
    
    // TYPE : STK; BOND: 8
    unsigned char ** B8 = NULL;
    B8 = new unsigned char *[4]();
    B8[0] = new unsigned char [MASKSIZE] {0,1,1,0,1,1,0,1,1};
    B8[1] = new unsigned char [MASKSIZE] {1,1,1,1,1,1,0,0,0};
    B8[2] = new unsigned char [MASKSIZE] {1,1,0,1,1,0,1,1,0};
    B8[3] = new unsigned char [MASKSIZE] {0,0,0,1,1,1,1,1,1};
    
    // TYPE : STK; BOND: 9
    unsigned char ** B9 = NULL;
    B9 = new unsigned char *[8]();
    B9[0] = new unsigned char [MASKSIZE] {1,1,1,0,1,1,0,1,1};
    B9[1] = new unsigned char [MASKSIZE] {0,1,1,0,1,1,1,1,1};
    B9[2] = new unsigned char [MASKSIZE] {1,1,1,1,1,1,1,0,0};
    B9[3] = new unsigned char [MASKSIZE] {1,1,1,1,1,1,0,0,1};
    B9[4] = new unsigned char [MASKSIZE] {1,1,1,1,1,0,1,1,0};
    B9[5] = new unsigned char [MASKSIZE] {1,1,0,1,1,0,1,1,1};
    B9[6] = new unsigned char [MASKSIZE] {1,0,0,1,1,1,1,1,1};
    B9[7] = new unsigned char [MASKSIZE] {0,0,1,1,1,1,1,1,1};
    
    // TYPE : STK; BOND: 10
    unsigned char ** B10 = NULL;
    B10 = new unsigned char *[4]();
    B10[0] = new unsigned char [MASKSIZE] {1,1,1,0,1,1,1,1,1};
    B10[1] = new unsigned char [MASKSIZE] {1,1,1,1,1,1,1,0,1};
    B10[2] = new unsigned char [MASKSIZE] {1,1,1,1,1,0,1,1,1};
    B10[3] = new unsigned char [MASKSIZE] {1,0,1,1,1,1,1,1,1};
    
    // TYPE : K; BOND: 11
    unsigned char ** B11 = NULL;
    B11 = new unsigned char *[4]();
    B11[0] = new unsigned char [MASKSIZE] {1,1,1,1,1,1,0,1,1};
    B11[1] = new unsigned char [MASKSIZE] {1,1,1,1,1,1,1,1,0};
    B11[2] = new unsigned char [MASKSIZE] {1,1,0,1,1,1,1,1,1};
    B11[3] = new unsigned char [MASKSIZE] {0,1,1,1,1,1,1,1,1};
    
    std::map <int, unsigned char ** > conditionalMasks;
    conditionalMasks[4]= B4;
    conditionalMasks[6]= B6;
    conditionalMasks[7]= B7;
    conditionalMasks[8]= B8;
    conditionalMasks[9]= B9;
    conditionalMasks[10]= B10;
    conditionalMasks[11]= B11;
    
    return conditionalMasks[bondValue];
}


int returnShrinkBondSize(int bondValue){
    std::map <int, int> conditionalMasks;
    conditionalMasks[1]= 4;
    conditionalMasks[2]= 4;
    conditionalMasks[3]= 8;
    conditionalMasks[4]= 4;
    conditionalMasks[5]= 8;
    conditionalMasks[6]= 10;
    conditionalMasks[7]= 4;
    conditionalMasks[8]= 4;
    conditionalMasks[9]= 8;
    conditionalMasks[10]= 4;
    return conditionalMasks[bondValue]; 
}

int returnThinBondSize(int bondValue){
    std::map <int, int> conditionalMasks;
    conditionalMasks[4]= 8;
    conditionalMasks[5]= 8;
    conditionalMasks[6]= 10;
    conditionalMasks[7]= 4;
    conditionalMasks[8]= 4;
    conditionalMasks[9]= 8;
    conditionalMasks[10]= 4;
    return conditionalMasks[bondValue];
}

int returnSkeletonizeBondSize(int bondValue){
    std::map <int, int> conditionalMasks;
    conditionalMasks[4]= 8;
    conditionalMasks[6]= 8;
    conditionalMasks[7]= 4;
    conditionalMasks[8]= 4;
    conditionalMasks[9]= 8;
    conditionalMasks[10]= 4;
    conditionalMasks[11]= 4;
    return conditionalMasks[bondValue];
}


int returnBondValue(unsigned char * inpArray){
    int * bondWeights = new int [9] {1,2,1,2,0,2,1,2,1};
    int bondValue = 0;
    for(int i=0; i<9; i++){
        bondValue= bondValue + (inpArray[i] * bondWeights[i]);
    }
    return bondValue;
}

unsigned char ** returnShrinkThinUnconditionalMasks(){
    
    const int MASKSIZE = 9;
    
    // All masks are returned as a 2D array
    unsigned char ** masks = NULL;
    masks = new unsigned char *[37]();
    masks[0] = new unsigned char [MASKSIZE] {0,0,1,0,1,0,0,0,0};
    masks[1] = new unsigned char [MASKSIZE] {1,0,0,0,1,0,0,0,0};
    masks[2] = new unsigned char [MASKSIZE] {0,0,0,0,1,0,0,1,0};
    masks[3] = new unsigned char [MASKSIZE] {0,0,0,0,1,1,0,0,0};
    masks[4] = new unsigned char [MASKSIZE] {0,0,1,0,1,1,0,0,0};
    masks[5] = new unsigned char [MASKSIZE] {0,1,1,0,1,0,0,0,0};
    masks[6] = new unsigned char [MASKSIZE] {1,1,0,0,1,0,0,0,0};
    masks[7] = new unsigned char [MASKSIZE] {1,0,0,1,1,0,0,0,0};
    masks[8] = new unsigned char [MASKSIZE] {0,0,0,1,1,0,1,0,0};
    masks[9] = new unsigned char [MASKSIZE] {0,0,0,0,1,0,1,1,0};
    masks[10] = new unsigned char [MASKSIZE] {0,0,0,0,1,0,0,1,1};
    masks[11] = new unsigned char [MASKSIZE] {0,0,0,0,1,1,0,0,1};
    masks[12] = new unsigned char [MASKSIZE] {0,1,1,1,1,0,0,0,0};
    masks[13] = new unsigned char [MASKSIZE] {1,1,0,0,1,1,0,0,0};
    masks[14] = new unsigned char [MASKSIZE] {0,1,0,0,1,1,0,0,1};
    masks[15] = new unsigned char [MASKSIZE] {0,0,1,0,1,1,0,1,0};
    masks[16] = new unsigned char [MASKSIZE] {0,'a',1,0,1,'b',1,0,0};
    masks[17] = new unsigned char [MASKSIZE] {1,'b',0,'a',1,0,0,0,1};
    masks[18] = new unsigned char [MASKSIZE] {0,0,1,'a',1,0,1,'b',0};
    masks[19] = new unsigned char [MASKSIZE] {1,0,0,0,1,'b',0,'a',1};
    masks[20] = new unsigned char [MASKSIZE] {1,1,'d',1,1,'d','d','d','d'};
    masks[21] = new unsigned char [MASKSIZE] {'d',1,0,1,1,1,'d',0,0};
    masks[22] = new unsigned char [MASKSIZE] {0,1,'d',1,1,1,0,0,'d'};
    masks[23] = new unsigned char [MASKSIZE] {0,0,'d',1,1,1,0,1,'d'};
    masks[24] = new unsigned char [MASKSIZE] {'d',0,0,1,1,1,'d',1,0};
    masks[25] = new unsigned char [MASKSIZE] {'d',1,'d',1,1,0,0,1,0};
    masks[26] = new unsigned char [MASKSIZE] {0,1,0,1,1,0,'d',1,'d'};
    masks[27] = new unsigned char [MASKSIZE] {0,1,0,0,1,1,'d',1,'d'};
    masks[28] = new unsigned char [MASKSIZE] {'d',1,'d',0,1,1,0,1,0};
    masks[29] = new unsigned char [MASKSIZE] {1,'d',1,'d',1,'d','a','b','c'};
    masks[30] = new unsigned char [MASKSIZE] {1,'d','c','d',1,'b',1,'d','a'};
    masks[31] = new unsigned char [MASKSIZE] {'c','b','a','d',1,'d',1,'d',1};
    masks[32] = new unsigned char [MASKSIZE] {'a','d',1,'b',1,'d','c','d',1};
    masks[33] = new unsigned char [MASKSIZE] {'d',1,0,0,1,1,1,0,'d'};
    masks[34] = new unsigned char [MASKSIZE] {0,1,'d',1,1,0,'d',0,1};
    masks[35] = new unsigned char [MASKSIZE] {'d',0,1,1,1,0,0,1,'d'};
    masks[36] = new unsigned char [MASKSIZE] {1,0,'d',0,1,1,'d',1,0};
    
    return masks;
}

unsigned char ** returnSkeletonizeUnconditionalMasks(){
    
    const int MASKSIZE = 9;
    
    // All masks are returned as a 2D array
    unsigned char ** masks = NULL;
    masks = new unsigned char *[26]();
    masks[0] = new unsigned char [MASKSIZE] {0,0,0,0,1,0,0,0,1};
    masks[1] = new unsigned char [MASKSIZE] {0,0,0,0,1,0,1,0,0};
    masks[2] = new unsigned char [MASKSIZE] {0,0,1,0,1,0,0,0,0};
    masks[3] = new unsigned char [MASKSIZE] {1,0,0,0,1,0,0,0,0};
    masks[4] = new unsigned char [MASKSIZE] {0,0,0,0,1,0,0,1,0};
    masks[5] = new unsigned char [MASKSIZE] {0,0,0,0,1,1,0,0,0};
    masks[6] = new unsigned char [MASKSIZE] {0,0,0,1,1,0,0,0,0};
    masks[7] = new unsigned char [MASKSIZE] {0,1,0,0,1,0,0,0,0};
    masks[8] = new unsigned char [MASKSIZE] {0,1,0,0,1,1,0,0,0};
    masks[9] = new unsigned char [MASKSIZE] {0,1,0,1,1,0,0,0,0};
    masks[10] = new unsigned char [MASKSIZE] {0,0,0,0,1,1,0,1,0};
    masks[11] = new unsigned char [MASKSIZE] {0,0,0,1,1,0,0,1,0};
    masks[12] = new unsigned char [MASKSIZE] {1,1,'d',1,1,'d','d','d','d'};
    masks[13] = new unsigned char [MASKSIZE] {'d','d','d','d',1,1,'d',1,1};
    masks[14] = new unsigned char [MASKSIZE] {'d',1,'d',1,1,1,'d','d','d'};
    masks[15] = new unsigned char [MASKSIZE] {'d',1,'d',1,1,'d','d',1,'d'};
    masks[16] = new unsigned char [MASKSIZE] {'d','d','d',1,1,1,'d',1,'d'};
    masks[17] = new unsigned char [MASKSIZE] {'d',1,'d','d',1,1,'d',1,'d'};
    masks[18] = new unsigned char [MASKSIZE] {1,'d',1,'d',1,'d','a','b','c'};
    masks[19] = new unsigned char [MASKSIZE] {1,'d','c','d',1,'b',1,'d','a'};
    masks[20] = new unsigned char [MASKSIZE] {'c','b','a','d',1,'d',1,'d',1};
    masks[21] = new unsigned char [MASKSIZE] {'a','d','1','b',1,'d','c','d',1};
    masks[22] = new unsigned char [MASKSIZE] {'d',1,0,0,1,1,1,0,'d'};
    masks[23] = new unsigned char [MASKSIZE] {0,1,'d',1,1,0,'d',0,1};
    masks[24] = new unsigned char [MASKSIZE] {'d',0,1,1,1,0,0,1,'d'};
    masks[25] = new unsigned char [MASKSIZE] {1,0,'d',0,1,1,'d',1,0};
    
    return masks;
}
    
#endif /* STKMasks_h */
