//
//  main.cpp
//  hw_3_prob_3_c
//
//  Created by Abinaya Manimaran on 3/25/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//
#include <stdio.h>
#include <string>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

class bagOfWords{
public:
    Mat img1,img2,img3,img4;
    int minHessian;
    Mat descriptors1, descriptors2, descriptors3, descriptors4;
    Mat vocabularyCentroids;
    int * img1HistVocab;
    int * img2HistVocab;
    int * img3HistVocab;
    int * img4HistVocab;
    
    bagOfWords(Mat inpImg1, Mat inpImg2, Mat inpImg3, Mat inpImg4, int inpMinHessian){
        img1 = inpImg1;
        img2 = inpImg2;
        img3 = inpImg3;
        img4 = inpImg4;
        minHessian = inpMinHessian;
    }
    
    //Detect SIFT Descriptors for an image
    Mat detectSIFTDescriptors(Mat img) {
        Ptr<SIFT> detector = SIFT::create(minHessian);
        std::vector<KeyPoint> keypoints;
        Mat descriptors;
        detector->detectAndCompute( img, Mat(), keypoints, descriptors);
        return descriptors;
    }
    
    // Compute descriptors for all images
    void detectAllImageSIFTDescriptors(){
        descriptors1 = detectSIFTDescriptors(img1);
        descriptors2 = detectSIFTDescriptors(img2);
        descriptors3 = detectSIFTDescriptors(img3);
        descriptors4 = detectSIFTDescriptors(img4);
        cout << "-----------------" << endl;
        cout << "Descriptor 1 No Of Rows: " << descriptors1.rows << endl;
        cout << "Descriptor 1 No Of Cols: " << descriptors1.cols << endl;
        cout << "-----------------" << endl;
        cout << "Descriptor 2 No Of Rows: " << descriptors2.rows << endl;
        cout << "Descriptor 2 No Of Cols: " << descriptors2.cols << endl;
        cout << "-----------------" << endl;
        cout << "Descriptor 3 No Of Rows: " << descriptors3.rows << endl;
        cout << "Descriptor 3 No Of Cols: " << descriptors3.cols << endl;
        cout << "-----------------" << endl;
        cout << "Descriptor 4 No Of Rows: " << descriptors4.rows << endl;
        cout << "Descriptor 4 No Of Cols: " << descriptors4.cols << endl;
    }
    
    // Training to find cluster centroids based on img1, img2 and img3
    void trainBagOfWords(Mat trainDescriptor1, Mat trainDescriptor2, Mat trainDescriptor3, int nClusters){
        BOWKMeansTrainer BGOWORDS(nClusters);
        BGOWORDS.add(trainDescriptor1);
        BGOWORDS.add(trainDescriptor2);
        BGOWORDS.add(trainDescriptor3);
        vocabularyCentroids = BGOWORDS.cluster();
        cout << "-----------------" << endl;
        cout << "Vocabulary No Of Rows: " << vocabularyCentroids.rows << endl;
        cout << "Vocabulary No Of Cols: " << vocabularyCentroids.cols << endl;
    }
    
    //Find Histogram of Vocabulary for an image
    int * findVocabHistogram(Mat descriptors){
        int * histVocab = new int [vocabularyCentroids.rows]();
        
        //Using L2 Distance to find the closest Centroid to every feature
        for(int featureNo=0; featureNo<descriptors.rows; featureNo++){
            
            //Find distance from all centroids
            long double * tempArray = new long double [vocabularyCentroids.rows]();
            for(int centroidNo=0; centroidNo<vocabularyCentroids.rows; centroidNo++){
                long double tempSum=0;
                for(int dimNo=0; dimNo<vocabularyCentroids.cols; dimNo++){
                    long double tempDiff = descriptors.at<float>(featureNo,dimNo) - vocabularyCentroids.at<float>(centroidNo,dimNo);
                    tempSum = tempSum + pow(tempDiff,2);
                }
                tempSum = sqrt(tempSum);
                tempArray[centroidNo] = tempSum;
            }
            
            //Find centroid with minimum distance
            long double minDist = tempArray[0];
            int minDistIndex = 0;
            for(int i=1; i<vocabularyCentroids.rows; i++) {
                if(tempArray[i] < minDist){
                    minDist = tempArray[i];
                    minDistIndex = i;
                }
            }
            
            //Add Count to the Histogram of minimum centroid
            histVocab[minDistIndex] ++;
        }
        return histVocab;
    }
    
    //Find Histogram of Vocabulary for all images
    void findAllImagesVocabHistogram(){
        img1HistVocab = findVocabHistogram(descriptors1);
        img2HistVocab = findVocabHistogram(descriptors2);
        img3HistVocab = findVocabHistogram(descriptors3);
        img4HistVocab = findVocabHistogram(descriptors4);
    }
    
    //Histogram Matching Value
    long double returnHistogramMatchingValue(int *outHist, int * inpHist, int histLen) {
        long double matchValue = 0;
        for(int i=0; i< histLen; i++){
            matchValue = matchValue + (abs(outHist[i] - inpHist[i]));
        }
        matchValue = matchValue/((long double) histLen);
        return matchValue;
    }
    
    //Match All Training images histogram with test image and find best matched one
    void matchTestImageHistogram(){
        long double * tempMatchArray = new long double [3]();
        cout << "-----------------" << endl;
        tempMatchArray[0] = returnHistogramMatchingValue(img4HistVocab, img1HistVocab, vocabularyCentroids.rows);
        cout << "Error Matching with Image 1 (Ferrari 1): " << tempMatchArray[0] << endl;
        tempMatchArray[1] = returnHistogramMatchingValue(img4HistVocab, img2HistVocab, vocabularyCentroids.rows);
        cout << "Error Matching with Image 2 (Optimus Prime):" << tempMatchArray[1] << endl;
        tempMatchArray[2] = returnHistogramMatchingValue(img4HistVocab, img3HistVocab, vocabularyCentroids.rows);
        cout << "Error Matching with Image 3 (Bumblebee):" << tempMatchArray[2] << endl;
        
        //Find good match
        long double minValue = tempMatchArray[0];
        int minIndex = 0;
        for(int i=1; i< 3; i++) {
            if(tempMatchArray[i] < minValue){
                minValue = tempMatchArray[i];
                minIndex = i;
            }
        }
        
        // print good match
        cout << "-----------------" << endl;
        cout << "-----------------" << endl;
        cout << "Good Match of Image 4 is with Image " << minIndex+1 << endl;
        cout << "-----------------" << endl;
    }
};

void fileWriteHist(char* fileName, int *histData, int DATALEN) {
    FILE *file;
    file = fopen(fileName, "w");
    if (file != NULL)
    {
        for (int i = 0; i < DATALEN;  i++)
        {
            fprintf(file, "%d\t%d\n", i, histData[i]);
        }
        fclose(file);
        //cout << "File " << fileName << " written successfully !!!" << endl;
    }
    else
    {
        cout << "Cannot open file " << fileName << endl;
    }
}

int main( int argc, char** argv )
{
    if( argc != 9){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [input 1 image path] [input 2 image path] [input 3 image path] [input 4 image path] [output hist text path 1] [output hist text path 2] [output hist text path 3] [output hist text path 4]" << endl;
        return 0;}
    
    Mat img1 = imread( argv[1], CV_LOAD_IMAGE_COLOR ); //Ferrari 1
    Mat img2 = imread( argv[2], CV_LOAD_IMAGE_COLOR ); //Optimus Prime
    Mat img3 = imread( argv[3], CV_LOAD_IMAGE_COLOR ); //Bumblebee
    Mat img4 = imread( argv[4], CV_LOAD_IMAGE_COLOR ); //Ferrari 2
    
    if( !img1.data || !img2.data || !img3.data || !img4.data)
    { std::cout<< " --(!) Error reading images " << std::endl; return 0; }
    
    // Bag of Words - Class
    int minHessian = 400;
    cout << "Chosen minHessian Value = " << minHessian << endl;
    int nClusters = 8;
    bagOfWords bagOfWordsObject = bagOfWords(img1, img2, img3, img4, minHessian);
    bagOfWordsObject.detectAllImageSIFTDescriptors();
    bagOfWordsObject.trainBagOfWords(bagOfWordsObject.descriptors1, bagOfWordsObject.descriptors2, bagOfWordsObject.descriptors3, nClusters);
    bagOfWordsObject.findAllImagesVocabHistogram();
    bagOfWordsObject.matchTestImageHistogram();
    
    //Save Histograms to text file
    fileWriteHist(argv[5], bagOfWordsObject.img1HistVocab, nClusters);
    fileWriteHist(argv[6], bagOfWordsObject.img2HistVocab, nClusters);
    fileWriteHist(argv[7], bagOfWordsObject.img3HistVocab, nClusters);
    fileWriteHist(argv[8], bagOfWordsObject.img4HistVocab, nClusters);
}
