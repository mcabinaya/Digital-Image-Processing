//
//  main.cpp
//  hw_3_prob_3_a
//
//  Created by Abinaya Manimaran on 3/18/18.
//  Copyright © 2018 Abinaya Manimaran. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

Mat detectSIFTKeyPoints(Mat img, int minHessian) {
    // Declare required detector, vector and Matrix
    std::vector<KeyPoint> keypoints;
    Mat imgWithKeyPoints;
    Ptr<SIFT> detector = SIFT::create(minHessian);

    // Detect and Draw Key points
    detector->detect(img, keypoints);
    drawKeypoints(img, keypoints, imgWithKeyPoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
    
    return imgWithKeyPoints;
}

Mat detectSURFKeyPoints(Mat img, int minHessian) {
    // Declare required detector, vector and Matrix
    std::vector<KeyPoint> keypoints;
    Mat imgWithKeyPoints;
    Ptr<SURF> detector = SURF::create(minHessian);
    
    // Detect and Draw Key points
    detector->detect(img, keypoints);
    drawKeypoints(img, keypoints, imgWithKeyPoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
    
    return imgWithKeyPoints;
}

int main( int argc, char** argv )
{
    if( argc != 13){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [input 1 image path] [input 2 image path] [input 3 image path] [input 4 image path] [output 1 image 1 path] [output 1 image 2 path] [output 1 image 3 path] [output 1 image 4 path] [output 2 image 1 path] [output 2 image 2 path] [output 2 image 3 path] [output 2 image 4 path]" << endl;
        return 0;}
    
    Mat img1 = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );
    Mat img2 = imread( argv[2], CV_LOAD_IMAGE_GRAYSCALE );
    Mat img3 = imread( argv[3], CV_LOAD_IMAGE_GRAYSCALE );
    Mat img4 = imread( argv[4], CV_LOAD_IMAGE_GRAYSCALE );

    if( !img1.data || !img2.data || !img3.data || !img4.data)
    { std::cout<< " --(!) Error reading images " << std::endl; return 0; }
    
    // Declare output Matrices
    Mat img1Sift, img2Sift, img3Sift, img4Sift, img1Surf, img2Surf, img3Surf, img4Surf;
    
    //Detect Sift and Surf features
    int minHessian = 20;
    img1Sift = detectSIFTKeyPoints(img1, minHessian);
    img2Sift = detectSIFTKeyPoints(img2, minHessian);
    img3Sift = detectSIFTKeyPoints(img3, minHessian);
    img4Sift = detectSIFTKeyPoints(img4, minHessian);
    
    img1Surf = detectSURFKeyPoints(img1, minHessian);
    img2Surf = detectSURFKeyPoints(img2, minHessian);
    img3Surf = detectSURFKeyPoints(img3, minHessian);
    img4Surf = detectSURFKeyPoints(img4, minHessian);

    // Write outputs
    imwrite(argv[5],img1Sift);
    imwrite(argv[6],img2Sift);
    imwrite(argv[7],img3Sift);
    imwrite(argv[8],img4Sift);
    
    imwrite(argv[9],img1Surf);
    imwrite(argv[10],img2Surf);
    imwrite(argv[11],img3Surf);
    imwrite(argv[12],img4Surf);
  
}

