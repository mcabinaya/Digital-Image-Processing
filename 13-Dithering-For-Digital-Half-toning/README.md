## 13-Dithering-For-Digital-Half-toning

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [row] [col] [bytesPerPixel] [input color checker image path] [output image path - fixed thresholding] [output image path - random thresholding] [output image path - dithering (N=2)] [output image path - dithering (N=4)] [output image path - dithering (N=8)] [output image path - 4 Intensity dithering (N=2)] [output image path - 4 Intensity dithering (N=4)] [output image path - 4 Intensity dithering (N=8)]
```