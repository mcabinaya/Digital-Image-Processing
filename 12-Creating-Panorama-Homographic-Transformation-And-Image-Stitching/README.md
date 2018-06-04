## 12-Creating-Panorama-Homographic-Transformation-And-Image-Stitching

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands 

```
   $ g++ -o main main.cpp 
   
   $ ./main [row] [col] [bytesPerPixel] [input left image path] [input middle image path] [input right image path] [output Middle Bounded image path] [output Left Warped image path] [output Right Warped image path] [output Panorama image path]
```