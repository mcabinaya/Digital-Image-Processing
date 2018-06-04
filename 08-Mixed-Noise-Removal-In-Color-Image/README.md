## 08-Mixed-Noise-Removal-In-Color-Image 
1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands  

```
   $ g++ -o main main.cpp  
   
   $ ./main [row] [col] [bytesPerPixel] [input Noise free image path]  [input Noisy image path] [output image path] [N - mask size] [Filter Name 1] [Filter Name 2] [Filter Name 3] (filter names: medianFilter, lowPassFilter, gaussianFilter, give 0 if no need of filters)
```