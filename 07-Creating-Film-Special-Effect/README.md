## 07-Creating-Film-Special-Effect

1. Open command Prompt
2. Change directory using cd to the folder that has main.cpp and DIP_MyHeaderFile.h file
3. Execute the following commands

```
   $ g++ -o main main.cpp  
   
   $ ./main [row] [col] [bytesPerPixel] [input Original image path] [input Film image path] [input Girl image path] [row of Girl Image] [col of Girl Image] [bytesPerPixel of Girl image] [raw output image path - original mirror] [raw output image path - original invert] [raw output image path - original film effect] [raw output image path - Girl mirror] [raw output image path - Girl invert] [raw output image path - Girl film effect] [text output histogram R] [text output histogram G] [text output histogram B]  [text output Hist Film R] [text output Hist Film G] [text output Hist Film B] [text transfer function R] [text transfer function G] [text transfer function B]
```

Note: Has a Matlab file to read the txt histogram files and display them
