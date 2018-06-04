## 4-Transfer-Function-Based-Histogram-Equalization

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands  

```
   $ g++ -o main main.cpp  
   
   $ ./main [row] [col] [bytesPerPixel] [input image path] [raw output image 1 path] [text output histogram R] [text output histogram G] [text output histogram B]  [text transfer function R] [text transfer function G] [text transfer function B] [text output Hist Equalized R] [text output Hist Equalized G] [text output Hist Equalized B]
```
Note: Has a Matlab file to read the txt histogram files and display them