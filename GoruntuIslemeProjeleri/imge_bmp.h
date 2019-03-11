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

int *Histogram(BYTE* buffer, int width, int height);
BYTE* HistogramEqualization(BYTE* buffer, int width, int height);