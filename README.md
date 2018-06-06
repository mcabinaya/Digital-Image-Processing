# Digital-Image-Processing

All Codes were tested using the below configurations:  

  - OS : Mac OS 10.13.2 64-bit
  - Xcode Version 9.2 
  - Python 2.7

## Documents

1. ***Questions-Part-1.pdf*** and ***Report-Part-1.pdf*** 

	Contains questions and report for 

       *  01-Color-To-Grayscale-Conversion 
        
       *  02-CMY-Color-Space  
       
       *  03-Image-Resizing-via-Bilinear-Interpolation  
       
       *  04-Transfer-Function-Based-Histogram-Equalization 
        
       *  05-Cumulative-Probability-Based-Histogram-Equalization  
       
       *  06-Creating-Oil-Painting-Effect  
      
       *  07-Creating-Film-Special-Effect 
       
       *  08-Mixed-Noise-Removal-In-Color-Image 
        
       *  09-Patch-Based-Local-PCA-Noise-Removal  
       
       *  10-BM3D-Noise-Removal 
 
2. ***Questions-Part-2.pdf*** and ***Report-Part-2.pdf*** 

	Contains questions and report for 

       *  11-Geometrical-Warping 
       
       *  12-Creating-Panorama-Homographic-Transformation-And-Image-Stitching 
       
       *  13-Dithering-For-Digital-Half-toning 
       
       *  14-Error-Diffusion-For-Digital-Half-Toning 

       *  15-Separable-Error-Diffusion-For-Color-Halftoning 
       
       *  16-MBVQ-Based-Error-Diffusion-For-Color-Halftoning 
       
       *  17-Morphological-Processing-Shrinking-Count-Stars 

       *  18-Morphological-Processing-Thinning 
       
       *  19-Morphological-Processing-Skeletonizing 
       
       *  20-Counting-Game 
       
       *  21-Counting-Game-Unique-Items 
        
       
3. ***Questions-Part-3.pdf*** and ***Report-Part-3.pdf*** 

	Contains questions and report for 
	
       *  22-Texture-Classification 
       
       *  23-Texture-Segmentation 
       
       *  24-Improved-Texture-Segmentation 
       
       *  25-Sobel-Edge-Detector 
       
       *  26-Zero-Crossing-Edge-Detector 
       
       *  27-Structured-Edge-Detector 
       
       *  28-SIFT-And-SURF-Salient-Points-Extraction 
       
       *  29-SIFT-And-SURF-Image-Matching 
       
       *  30-Bag-Of-Words 
       

4. ***Questions-Part-4.pdf*** and ***Report-Part-4.pdf*** 
	
	Contains questions and report for 
	
       *  31-CNN-LeNet-5-On-MNIST-Dataset 
       
       *  32-Improved-CNN-On-MNIST-Dataset 
       
       *  33-Saak-Transform-On-MNIST-Dataset 
       
       *  34-Error-Analysis-On-MNIST-Dataset 
       
       
## 01-Color-To-Grayscale-Conversion

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands  

```
   $ g++ -o main main.cpp
   
   $ ./main [row] [col] [bytesPerPixel] [input image path] [raw output image 1 path] [raw output image 2 path] [raw output image 3 path]
```

## 02-CMY-Color-Space

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands  

``` 
   $ g++ -o main main.cpp  
   
   $ ./main [row] [col] [bytesPerPixel]  [input image path] [raw output image 1 path] [raw output image 2 path] [raw output image 3 path] [raw output image 4 path]
```

## 03-Image-Resizing-via-Bilinear-Interpolation

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands  

```
   $ g++ -o main main.cpp  
   
   $ ./main [row] [col] [bytesPerPixel] [input image path] [raw output image 1 path] [resize row] [resize col]
```

## 04-Transfer-Function-Based-Histogram-Equalization

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands  

```
   $ g++ -o main main.cpp  
   
   $ ./main [row] [col] [bytesPerPixel] [input image path] [raw output image 1 path] [text output histogram R] [text output histogram G] [text output histogram B]  [text transfer function R] [text transfer function G] [text transfer function B] [text output Hist Equalized R] [text output Hist Equalized G] [text output Hist Equalized B]
```

Note: Has a Matlab file to read the txt histogram files and display them

## 05-Cumulative-Probability-Based-Histogram-Equalization

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands

```
   $ g++ -o main main.cpp  
   
   $ ./main [row] [col] [bytesPerPixel] [input image path] [raw output image 1 path] [text output Hist Equalized R] [text output Hist Equalized G] [text output Hist Equalized B] [text output CDF Equalized R] [text output CDF Equalized G] [text output CDF Equalized B]
```

Note: Has a Matlab file to read the txt histogram files and display them

## 06-Creating-Oil-Painting-Effect

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands  

```
   $ g++ -o main main.cpp  
   
   $ ./main [row] [col] [bytesPerPixel] [input image path] [raw output image 1 path] [raw output image 2 path] [Number of Quantization levels] [N - for N*N neighborhood]
```

## 07-Creating-Film-Special-Effect

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands

```
   $ g++ -o main main.cpp  
   
   $ ./main [row] [col] [bytesPerPixel] [input Original image path] [input Film image path] [input Girl image path] [row of Girl Image] [col of Girl Image] [bytesPerPixel of Girl image] [raw output image path - original mirror] [raw output image path - original invert] [raw output image path - original film effect] [raw output image path - Girl mirror] [raw output image path - Girl invert] [raw output image path - Girl film effect] [text output histogram R] [text output histogram G] [text output histogram B]  [text output Hist Film R] [text output Hist Film G] [text output Hist Film B] [text transfer function R] [text transfer function G] [text transfer function B]
```

Note: Has a Matlab file to read the txt histogram files and display them

## 08-Mixed-Noise-Removal-In-Color-Image 
1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands  

```
   $ g++ -o main main.cpp  
   
   $ ./main [row] [col] [bytesPerPixel] [input Noise free image path]  [input Noisy image path] [output image path] [N - mask size] [Filter Name 1] [Filter Name 2] [Filter Name 3] (filter names: medianFilter, lowPassFilter, gaussianFilter, give 0 if no need of filters)
```

## 09-Patch-Based-Local-PCA-Noise-Removal

1. Change directory to the folder in Matlab
2. Open main.m file in Matlab and run

## 10-BM3D-Noise-Removal

1. Change directory to the folder in Matlab
2. Open BM3D.m file in Matlab and run

## 11-Geometrical-Warping

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [ROW] [COL] [BYTESPERPIXEL] [input image path] [output Warped image path] [output reverse image path]
```

## 12-Creating-Panorama-Homographic-Transformation-And-Image-Stitching

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [row] [col] [bytesPerPixel] [input left image path] [input middle image path] [input right image path] [output Middle Bounded image path] [output Left Warped image path] [output Right Warped image path] [output Panorama image path]
```

## 13-Dithering-For-Digital-Half-toning

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [row] [col] [bytesPerPixel] [input color checker image path] [output image path - fixed thresholding] [output image path - random thresholding] [output image path - dithering (N=2)] [output image path - dithering (N=4)] [output image path - dithering (N=8)] [output image path - 4 Intensity dithering (N=2)] [output image path - 4 Intensity dithering (N=4)] [output image path - 4 Intensity dithering (N=8)]
```

## 14-Error-Diffusion-For-Digital-Half-Toning

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [row] [col] [bytesPerPixel]  [input color checker image path] [output image path - Method1] [output image path - Method1 Serpentine] [output image path - Method2] [output image path - Method2 - Serpentine] [output image path - Method3] [output image path - Method3 - Serpentine]
```
## 15-Separable-Error-Diffusion-For-Color-Halftoning

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [ROW] [COL] [BYTESPERPIXEL] [input Flower image path] [output image path - CMY] [output image path - Error Diffused]
```

## 16-MBVQ-Based-Error-Diffusion-For-Color-Halftoning

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [ROW] [COL] [BYTESPERPIXEL] [input flower image path] [output image path - MBVQ image]
```

## 17-Morphological-Processing-Shrinking-Count-Stars

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp, DIP_MyHeaderFile.h and STKMasks.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [row] [col] [bytesPerPixel]  [input stars image path] [output Binary image path] [output First Stage image path] [output Second Stage image path]
```

## 18-Morphological-Processing-Thinning

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp, DIP_MyHeaderFile.h and STKMasks.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [row] [col] [bytesPerPixel]  [input Jigsaw image path] [output Binary image path] [output First Stage image path] [output Second Stage image path]
```

## 19-Morphological-Processing-Skeletonizing

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp, DIP_MyHeaderFile.h and STKMasks.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [row] [col] [bytesPerPixel]  [input Jigsaw image path] [output Binary image path] [output First Stage image path] [output Second Stage image path]
```

## 20-Counting-Game

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp, DIP_MyHeaderFile.h and STKMasks.h file
3. Execute the following commands

```
   $ g++ -o main main.cpp 
   
   $ ./main [row] [col] [bytesPerPixel]  [input board image path] [output Binary image path] [output First Stage image path] [output Second Stage image path]
```

## 21-Counting-Game-Unique-Items

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp, DIP_MyHeaderFile.h and STKMasks.h file
3. Execute the following commands 

``` 
   $ g++ -o main main.cpp 
   
   $ ./main [row] [col] [bytesPerPixel]  [input board image path] [output Binary image path] [output Connected Components image path] [output Squares image path] [output XORed image path]
```

## 22-Texture-Classification

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [ROW] [COL] [BYTESPERPIXEL] [input 12 image paths] [output energy feature file path]
```

## 23-Texture-Segmentation

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [[ROW] [COL] [BYTESPERPIXEL] [input image paths] [output image path]
```

## 24-Improved-Texture-Segmentation


1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [ROW] [COL] [BYTESPERPIXEL] [input image paths] [output image path]
```

## 25-Sobel-Edge-Detector

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [ROW] [COL] [BYTESPERPIXEL] [input 1 image path] [output 1 image path 1] [output 1 image path 2] [output 1 image path 3] [output 1 image path 4] [input 2 image path] [output 2 image path 1] [output 2 image path 2] [output 2 image path 3] [output 2 image path 4]
```

## 26-Zero-Crossing-Edge-Detector

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands

```
   $ g++ -o main main.cpp 
   
   $ ./main [ROW] [COL] [BYTESPERPIXEL] [input 1 image path] [input 2 image path] [output 1 image path 1] [output 1 image path 2] [output 1 image path 3] [output 2 image path 1] [output 2 image path 2] [output 2 image path 3]
```

## 27-Structured-Edge-Detector

1. Source: https://github.com/pdollar/edges
2. Changed edgesDemo.m and edgesEvalImg.m file

## 28-SIFT-And-SURF-Salient-Points-Extraction

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [input 1 image path] [input 2 image path] [input 3 image path] [input 4 image path] [output 1 image 1 path] [output 1 image 2 path] [output 1 image 3 path] [output 1 image 4 path] [output 2 image 1 path] [output 2 image 2 path] [output 2 image 3 path] [output 2 image 4 path]
```
## 29-SIFT-And-SURF-Image-Matching

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [input 1 image path] [input 2 image path] [input 3 image path] [input 4 image path] [output match 1] [output match 2] [output match 3] [output match 4] [output match 5] [output match 6]
```

## 30-Bag-Of-Words

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [[input 1 image path] [input 2 image path] [input 3 image path] [input 4 image path] [output hist text path 1] [output hist text path 2] [output hist text path 3] [output hist text path 4]
```

## 31-CNN-LeNet-5-On-MNIST-Dataset

1. Python files can be directly run from the computer's python or can be run from Google Colaboratory. All the experiments were run in Google Colaboratory since it takes less time. 

2. The Runtime settings were made as below:
   - Runtime Type: Python 2
   - Hardware Accelerator: GPU

3. For initial setup of Google Colaboratory with Keras, the steps given in this link was followed (https://medium.com/deep-learning-turkey/google-colab-free-gpu-tutorial-e113627b9f5d)

4. From system's command prompt or Google Colab command prompt type the below commands

```
	$ cnn.py
	$ cnn_leakyrelu.py
	$ python plot_curves.py
```

## 32-Improved-CNN-On-MNIST-Dataset

1. Python files can be directly run from the computer's python or can be run from Google Colaboratory. All the experiments were run in Google Colaboratory since it takes less time. 

2. The Runtime settings were made as below:
   - Runtime Type: Python 2
   - Hardware Accelerator: GPU

3. For initial setup of Google Colaboratory with Keras, the steps given in this link was followed (https://medium.com/deep-learning-turkey/google-colab-free-gpu-tutorial-e113627b9f5d)

4.  From system's command prompt or Google Colab command prompt type the below commands

```
	$ python architecture_1.py
	$ python architecture_2.py
	$ python architecture_3.py
	$ python architecture_4.py
	$ python architecture_5.py
	$ python plot_curves.py
```

## 33-Saak-Transform-On-MNIST-Dataset

1. Python files can be directly run from the computer's python or can be run from Google Colaboratory. All the experiments were run in Google Colaboratory since it takes less time. 

2. The Runtime settings were made as below:
   - Runtime Type: Python 2
   - Hardware Accelerator: GPU

3. For initial setup of Google Colaboratory with Keras, the steps given in this link was followed (https://medium.com/deep-learning-turkey/google-colab-free-gpu-tutorial-e113627b9f5d)

4. From system's command prompt or Google Colab command prompt type the below commands

```
	$ python /Saak-tensorflow-master/mnist.py
```

## 34-Error-Analysis-On-MNIST-Dataset

1. Python files can be directly run from the computer's python or can be run from Google Colaboratory. All the experiments were run in Google Colaboratory since it takes less time. 

2. The Runtime settings were made as below:
   - Runtime Type: Python 2
   - Hardware Accelerator: GPU

3. For initial setup of Google Colaboratory with Keras, the steps given in this link was followed (https://medium.com/deep-learning-turkey/google-colab-free-gpu-tutorial-e113627b9f5d)

4. From system's command prompt or Google Colab command prompt type the below commands

```
	$ python compare_results.py
	$ python view_image.py
```
