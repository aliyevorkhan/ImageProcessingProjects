#pragma once
#include <windows.h>
BYTE* LoadBMP(int% width, int% height, long% size, LPCTSTR bmpfile);
bool  SaveBMP(BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile);
BYTE* ConvertBMPToIntensity(BYTE* Buffer, int width, int height);
BYTE* ConvertIntensityToBMP(BYTE* Buffer, int width, int height, long* newsize);
BYTE* Mask(BYTE* Buffer, int uzunluk, int yukseklik, float mask[], int maskElemanSayisi, long% yeniUzunluk, long% yeniYukseklik);
BYTE* zoom(BYTE* Buffer, unsigned int zoom_width1, unsigned int zoom_width2, unsigned int zoom_height1, unsigned int zoom_height2, unsigned int Width);
void cemberCiz(BYTE* Buffer, int x, int y, int r, int width, int height);
void cizgiCiz(BYTE* Buffer, int x0, int y0, int x1, int y1, int width, int height);
int* histogram(BYTE* buffer, int width, int height);
BYTE* HistogramEqualization(BYTE* buffer, int width, int height);
BYTE* k_means(BYTE *Buffer, unsigned int Width, unsigned int Height);
BYTE* dilation(BYTE *Buffer, unsigned int Width, unsigned int Height);
BYTE* erosion(BYTE *Buffer, unsigned int Width, unsigned int Height);
BYTE* Sinirlar(BYTE*Buffer, int uzunluk, int yukseklik, int option);
float oklid_Distance(float *arr1, float *arr2, int size);
BYTE* Tumleme(BYTE*Buffer, int uzunluk, int yukseklik, int option);
BYTE *canny_Andhough(BYTE *Buffer, unsigned int Width, unsigned int Height);
void draw(BYTE *Buffer, unsigned int Width, unsigned int Height, int padding, int x1, int x2, int y1, int y2, int renk);
BYTE* ObjectDetect(BYTE* buffer, int width, int height, int %label);
BYTE *object_recognition(BYTE *Buffer, unsigned int Width, unsigned int Height);
BYTE* MoveImage(BYTE* buffer, int width, int height);
BYTE* RotateImage(BYTE* buffer, int width, int height,int angle);
BYTE* RotateImageAlias(BYTE* buffer, int width, int height, int angle);
BYTE* MirrorImage(BYTE* buffer, int width, int height, int angle);
BYTE* Shearing(BYTE* buffer, int width, int height, double coefficients, int direction);


