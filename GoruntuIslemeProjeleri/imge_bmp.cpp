
#include <windows.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include "humoments.h"
using namespace std;

#define PI 3.14159265

BYTE* LoadBMP(int% width, int% height, long% size, LPCTSTR bmpfile)
{
	// declare bitmap structures
	BITMAPFILEHEADER bmpheader;
	BITMAPINFOHEADER bmpinfo;
	// value to be used in ReadFile funcs
	DWORD bytesread;
	// open file to read from
	HANDLE file = CreateFile(bmpfile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (NULL == file)
		return NULL; // coudn't open file

					 // read file header
	if (ReadFile(file, &bmpheader, sizeof(BITMAPFILEHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	//read bitmap info
	if (ReadFile(file, &bmpinfo, sizeof(BITMAPINFOHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	// check if file is actually a bmp
	if (bmpheader.bfType != 'MB') {
		CloseHandle(file);
		return NULL;
	}
	// get image measurements
	width = bmpinfo.biWidth;
	height = abs(bmpinfo.biHeight);

	// check if bmp is uncompressed
	if (bmpinfo.biCompression != BI_RGB) {
		CloseHandle(file);
		return NULL;
	}
	// check if we have 24 bit bmp
	if (bmpinfo.biBitCount != 24) {
		CloseHandle(file);
		return NULL;
	}

	// create buffer to hold the data
	size = bmpheader.bfSize - bmpheader.bfOffBits;
	BYTE* Buffer = new BYTE[size];
	// move file pointer to start of bitmap data
	SetFilePointer(file, bmpheader.bfOffBits, NULL, FILE_BEGIN);
	// read bmp data
	if (ReadFile(file, Buffer, size, &bytesread, NULL) == false) {
		delete[] Buffer;
		CloseHandle(file);
		return NULL;
	}
	// everything successful here: close file and return buffer
	CloseHandle(file);

	return Buffer;
}//LOADPMB

bool SaveBMP(BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile)
{
	// declare bmp structures 
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER info;

	// andinitialize them to zero
	memset(&bmfh, 0, sizeof(BITMAPFILEHEADER));
	memset(&info, 0, sizeof(BITMAPINFOHEADER));

	// fill the fileheader with data
	bmfh.bfType = 0x4d42;       // 0x4d42 = 'BM'
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + paddedsize;
	bmfh.bfOffBits = 0x36;		// number of bytes to start of bitmap bits

								// fill the infoheader

	info.biSize = sizeof(BITMAPINFOHEADER);
	info.biWidth = width;
	info.biHeight = height;
	info.biPlanes = 1;			// we only have one bitplane
	info.biBitCount = 24;		// RGB mode is 24 bits
	info.biCompression = BI_RGB;
	info.biSizeImage = 0;		// can be 0 for 24 bit images
	info.biXPelsPerMeter = 0x0ec4;     // paint and PSP use this values
	info.biYPelsPerMeter = 0x0ec4;
	info.biClrUsed = 0;			// we are in RGB mode and have no palette
	info.biClrImportant = 0;    // all colors are important

								// now we open the file to write to
	HANDLE file = CreateFile(bmpfile, GENERIC_WRITE, FILE_SHARE_READ,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == NULL) {
		CloseHandle(file);
		return false;
	}
	// write file header
	unsigned long bwritten;
	if (WriteFile(file, &bmfh, sizeof(BITMAPFILEHEADER), &bwritten, NULL) == false) {
		CloseHandle(file);
		return false;
	}
	// write infoheader
	if (WriteFile(file, &info, sizeof(BITMAPINFOHEADER), &bwritten, NULL) == false) {
		CloseHandle(file);
		return false;
	}
	// write image data
	if (WriteFile(file, Buffer, paddedsize, &bwritten, NULL) == false) {
		CloseHandle(file);
		return false;
	}

	// and close file
	CloseHandle(file);

	return true;
} // SaveBMP

BYTE* ConvertBMPToIntensity(BYTE* Buffer, int width, int height)
{
	// first make sure the parameters are valid
	if ((NULL == Buffer) || (width == 0) || (height == 0))
		return NULL;

	// find the number of padding bytes

	int padding = 0;
	int scanlinebytes = width * 3;
	while ((scanlinebytes + padding) % 4 != 0)     // DWORD = 4 bytes
		padding++;
	// get the padded scanline width
	int psw = scanlinebytes + padding;

	// create new buffer
	BYTE* newbuf = new BYTE[width*height];

	// now we loop trough all bytes of the original buffer, 
	// swap the R and B bytes and the scanlines
	long bufpos = 0;
	long newpos = 0;
	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++) {
			newpos = row * width + column;
			bufpos = (height - row - 1) * psw + column * 3;
			newbuf[newpos] = BYTE(0.11*Buffer[bufpos + 2] + 0.59*Buffer[bufpos + 1] + 0.3*Buffer[bufpos]);
		}

	return newbuf;
}//ConvetBMPToIntensity

BYTE* ConvertIntensityToBMP(BYTE* Buffer, int width, int height, long* newsize)
{
	// first make sure the parameters are valid
	if ((NULL == Buffer) || (width == 0) || (height == 0))
		return NULL;

	// now we have to find with how many bytes
	// we have to pad for the next DWORD boundary	

	int padding = 0;
	int scanlinebytes = width * 3;
	while ((scanlinebytes + padding) % 4 != 0)     // DWORD = 4 bytes
		padding++;
	// get the padded scanline width
	int psw = scanlinebytes + padding;
	// we can already store the size of the new padded buffer
	*newsize = height * psw;

	// and create new buffer
	BYTE* newbuf = new BYTE[*newsize];

	// fill the buffer with zero bytes then we dont have to add
	// extra padding zero bytes later on
	memset(newbuf, 0, *newsize);

	// now we loop trough all bytes of the original buffer, 
	// swap the R and B bytes and the scanlines
	long bufpos = 0;
	long newpos = 0;
	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++) {
			bufpos = row * width + column;     // position in original buffer
			newpos = (height - row - 1) * psw + column * 3;           // position in padded buffer
			newbuf[newpos] = Buffer[bufpos];       //  blue
			newbuf[newpos + 1] = Buffer[bufpos];   //  green
			newbuf[newpos + 2] = Buffer[bufpos];   //  red
		}

	return newbuf;
} //ConvertIntensityToBMP

BYTE *zoom(BYTE * Buffer, unsigned int zoom_width1, unsigned int zoom_width2, unsigned int zoom_height1, unsigned int zoom_height2, unsigned int Width)
{
	int first_index = 0;
	int k = 0;
	int zoom_width;
	int zoom_height;
	BYTE *Zoom_buffer;
	if (zoom_height2 > zoom_height1 && zoom_width2 > zoom_width1) {
		zoom_width = ((zoom_width2 - zoom_width1) + 1);
		zoom_height = ((zoom_height2 - zoom_height1) + 1);
		Zoom_buffer = new BYTE[(2 * zoom_height - 1)*(2 * zoom_width - 1)];

		for (int i = zoom_height1; i < zoom_height2; i++)
		{
			for (int j = zoom_width1; j < zoom_width2+1; j++)
			{
				Zoom_buffer[k] = Buffer[(i*Width) + j];
				k++;
				if (j == zoom_width2)
					break;

				double gecici_bellek = ((Buffer[(i*Width) + j]) + (Buffer[(i*Width) + (j + 1)])) / 2;
				Zoom_buffer[k] = gecici_bellek;
				k++;
			}
			k = k + ((2 * zoom_width) - 1);
		}

		k = ((2 * zoom_width) - 1);

		for (int i = zoom_height1; i < zoom_height2; i++)
		{
			for (int m = 0; m < 2 * zoom_width - 1; m++)
			{
				double gecici_bellek = (Zoom_buffer[first_index + m] + Zoom_buffer[first_index + 2 * (2 * zoom_width - 1) + m]) / 2;
				Zoom_buffer[k] = gecici_bellek;
				k++;
			}
			first_index = first_index + 2 * (2 * zoom_width - 1);
			k = k + ((2 * zoom_width) - 1);
		}
	}
	return Zoom_buffer;

}//zoom

BYTE* Mask(BYTE* Buffer, int uzunluk, int yukseklik, float mask[], int maskElemanSayisi, long% yeniUzunluk, long% yeniYukseklik)
{
	int N = (int)(sqrt(maskElemanSayisi)); // N = matrisin kaça kaçlýk olduðu gösterir N x N
	
	if (N*N != maskElemanSayisi) return NULL; // Mask kare matris deðilse iþlem yapma
	if (N % 2 == 0) return NULL;			// Mask matrisi (2n+1) türünde yani tek matris deðilse (3x3,5x5,7x7 .... gibi deðilse ) iþlem yapma

	BYTE *buf = new BYTE[(uzunluk - N + 1)*(yukseklik - N + 1)]; // iþlem yaptýktan sonra ki görüntü içeriðimizi saklayacaðýmýz alan

	int xKonum = 0, yKonum = 0; // mask gezinme esnasýndaki görüntüdeki konumlarý

	yeniUzunluk = uzunluk - N + 1;
	yeniYukseklik = yukseklik - N + 1;


	for (int i = 0; i < (uzunluk - N + 1)*(yukseklik - N + 1); i++) // Maský görüntü üzerinde gezdirme iþlemi
	{
		float deger = 0.0;
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < N; k++)
			{
				deger = deger + mask[k + j*N] * (int)(Buffer[(xKonum + k) + (yKonum + j)*uzunluk]);
			}
		}
		if (xKonum == uzunluk - N)
		{
			yKonum++;
			xKonum = 0;
		}
		else
		{
			xKonum++;
		}
		buf[i] = BYTE((int)(deger));
	}

	return buf;
}

void cizgiCiz(BYTE* Buffer, int x0, int y0, int x1, int y1, int width, int height)
{
	int egim = ((y1 - y0) / (x1 - x0));
	int konum = 0;

	if (x0 < x1)
	{
		for (int column = y0; column <= y1; column++)
		{
			for (int row = x0; row <= x1; row++)
			{
				if (row == (egim*(column - x0)) + y0)
				{
					konum = (row * width + column);
					Buffer[konum] = BYTE(255);
				}
			}
		}

	}
	if (x0 > x1) {
		for (int row = x1; row <= x0; row++) {
			for (int column = y1; column >= y0; column--)
			{
				if (column == (egim * (row - y0)) + x0) {
					konum = (row * width + column);
					Buffer[konum] = BYTE(255);
				}

			}
		}
	}
	if (x0 == x1) {
		for (int row = x0; row < x0 + 1; row++) {
			for (int column = y0; column <= y1; column++)
			{
				konum = row * width + column;
				Buffer[konum] = BYTE(255);
			}
		}
	}

}//cizgiCiz

void cemberCiz(BYTE* Buffer, int x, int y, int r, int width, int height)
{
	int x0 = 0, y0 = 0, konum = 0;
	for (int i = 0; i < 360; i++)
	{
		x0 = (int)(x + cos(i) * r);
		y0 = (int)(y + sin(i) * r);

		konum = width * y0 + x0;

		if (x0 >= 0 && x0 < width && konum < width*height && konum >= 0)
		{
			Buffer[konum] = BYTE(255);
		}

	}
}//cemberCiz

int *histogram(BYTE* buffer, int width, int height)
{
	int *histogram = new int[256];

	for (unsigned int i = 0; i < 256; i++)
		histogram[i] = 0;

	for (unsigned int pos = 0; pos < width*height; pos++)
	{
		int t = buffer[pos];
		histogram[t]++;
	}
	return histogram;
}//Histogram

BYTE* HistogramEqualization(BYTE* buffer, int width, int height)
{
	int pixel = width * height;
	int level = 255;
	int *stretch = new int[256];
	int etiket = 1;

	BYTE *tBuffer = new BYTE[width * height];

	int *histogram0 = histogram(buffer, width, height);

	for (int i = 0; i < 256; i++)
		stretch[i] = 0;

	float sum = 0.0;
	for (int i = 0; i <= level; i++)
	{
		sum += histogram0[i];
		stretch[i] = (int)round((sum / pixel) *level);
	}



	for (int i = 0; i < width * height; i++)
		tBuffer[i] = BYTE(0);

	for (int k = 0; k < 256; k++)
	{
		if (histogram0[k] > 0)
		{
			for (int pos = 0; pos < width*height; pos++)
			{
				if (buffer[pos] == BYTE(k))
				{
					if (tBuffer[pos] == 0)
					{
						buffer[pos] = BYTE(stretch[k]);
						tBuffer[pos] = BYTE(etiket);
					}
				}
			}
			etiket++;
		}
	}
	delete[]tBuffer;

	return buffer;
}

BYTE *k_means(BYTE *Buffer, unsigned int Width, unsigned int Height)
{
	float t1 = 0, t2 = 255;
	float t11 = -1, t22 = -1;

	double toplam1 = 0, toplam2 = 0;
	double bolme1 = 0, bolme2 = 0;

	int *histogram0 = new int[256];


	histogram0 = histogram(Buffer, Width, Height);

	while (true)
	{
		for (int i = 0; i < 256; i++)
		{
			if (fabs(i - t1) < fabs(i - t2))
			{
				toplam1 += (i*histogram0[i]);
				bolme1 += histogram0[i];
			}
			else
			{
				toplam2 += (i*histogram0[i]);
				bolme2 += histogram0[i];
			}
		}

		t11 = toplam1 / bolme1;
		t22 = toplam2 / bolme2;

		if (t1 == t11 && t2 == t22)
			break;

		t1 = t11;
		t2 = t22;
	}

	BYTE *k_means_buffer = new BYTE[Width*Height];
	k_means_buffer = Buffer;
	for (int i = 0; i < Width * Height; i++)
	{
		if (fabs(k_means_buffer[i] - t11) < fabs(k_means_buffer[i] - t22))
			k_means_buffer[i] = 0;
		else
			k_means_buffer[i] = 255;
	}

	return k_means_buffer;
}

BYTE *dilation(BYTE *Buffer, unsigned int Width, unsigned int Height)
{
	BYTE *dilation = new BYTE[Width*Height];
	int A;
	bool result = 0;

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			A = (i*Width + j);
			result = (Buffer[(A - Width)] || Buffer[(A - 1)] || Buffer[A] || Buffer[(A + 1)] || Buffer[(A + Width)]);


			if (result == true)
				dilation[A] = 255;
			else
				dilation[A] = 0;

		}

	}

	return dilation;
}

BYTE *erosion(BYTE *Buffer, unsigned int Width, unsigned int Height)
{
	BYTE *erosion = new BYTE[Width*Height];
	int A;
	bool result = 0;

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			A = (i*Width + j);
			result = (Buffer[(A - Width)] && Buffer[(A - 1)] && Buffer[A] && Buffer[(A + 1)] && Buffer[(A + Width)]);

			if (result == true)
				erosion[A] = 255;
			else
				erosion[A] = 0;

		}

	}

	return erosion;
}

BYTE* Sinirlar(BYTE*Buffer, int uzunluk, int yukseklik, int option) {

	if (option == 0) 
	{
		BYTE* dilation_buf = dilation(Buffer, uzunluk, yukseklik);
		BYTE* buf = new BYTE[uzunluk*yukseklik];
		for (int i = 0; i < uzunluk*yukseklik; i++)
		{
			if (Buffer[i] != dilation_buf[i])
			{
				buf[i] = BYTE(255);
			}
			else
			{
				buf[i] = BYTE(0);
			}
		}
		return buf;
	}
	else if (option == 1)
	{
		BYTE* dilation_buf = dilation(Buffer, uzunluk, yukseklik);
		BYTE* buf = new BYTE[uzunluk*yukseklik];
		for (int i = 0; i < uzunluk*yukseklik; i++)
		{
			if (Buffer[i] != dilation_buf[i])
			{
				buf[i] = BYTE(0);
			}
			else
			{
				buf[i] = BYTE(255);
			}
		}
		return buf;
	}
	else if (option == 2)
	{
		BYTE* erosion_buf = erosion(Buffer, uzunluk, yukseklik);
		BYTE* buf = new BYTE[uzunluk*yukseklik];
		for (int i = 0; i < uzunluk*yukseklik; i++)
		{
			if (Buffer[i] != erosion_buf[i])
			{
				buf[i] = BYTE(255);
			}
			else
			{
				buf[i] = BYTE(0);
			}
		}
		return buf;
	}
	else if (option == 3)
	{
		BYTE* erosion_buf = erosion(Buffer, uzunluk, yukseklik);
		BYTE* buf = new BYTE[uzunluk*yukseklik];
		for (int i = 0; i < uzunluk*yukseklik; i++)
		{
			if (Buffer[i] != erosion_buf[i])
			{
				buf[i] = BYTE(0);
			}
			else
			{
				buf[i] = BYTE(255);
			}
		}
		return buf;
	}

	
}

BYTE* Tumleme(BYTE*Buffer, int uzunluk, int yukseklik, int option) {
	if(option == 0)
	{
		BYTE* buf = new BYTE[uzunluk*yukseklik];
		for (int i = 0; i < uzunluk*yukseklik; i++)
		{
			buf[i] = BYTE(option + int(Buffer[i]));
		}
		return buf;
	}
	else if (option == 255) {
		BYTE* buf = new BYTE[uzunluk*yukseklik];
		for (int i = 0; i < uzunluk*yukseklik; i++)
		{
			buf[i] = BYTE(option - int(Buffer[i]));
		}
		return buf;
	}
	
	
}

float oklid_Distance(float *arr1, float *arr2, int size)
{
	float temp = 0;
	for (int i = 0; i < size; i++)
	{
		temp += pow((arr1[i] - arr2[i]), 2);
	}
	return sqrt(temp);
}



BYTE* ObjectDetect(BYTE* buffer, int width, int height, int %label)
{
	int etiket = 2;

	int *object = new int[width*height];
	for (int i = 0; i < height*width; i++)
	{
		if ((int)buffer[i] == 0)// fotonun kendi degerlerini etiketliyoruz
			object[i] = 1;
		else
			object[i] = 0;
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (etiket == 99)
				etiket++;
			if ((int)buffer[i * width + j] == 0)
			{
				// (0,0)
				if (i == 0 && j == 0)
					object[i * width + j] = etiket++;
				// (0,j)
				else if (i == 0)
				{
					if (object[i * width + j - 1] != 0)
						object[i * width + j] = object[i * width + j - 1];
					else
						object[i * width + j] = etiket++;
				}

				// (i,0)
				else if (j == 0)
				{
					if (object[(i - 1) * width + j] != 0)
						object[i * width + j] = object[(i - 1) * width + j];
					else
						object[i * width + j] = etiket++;
				}
				// -----
				else
				{
					if (object[(i - 1) * width + j] == 0 && object[i* width + j - 1] == 0)
						object[i * width + j] = etiket++;
					else if (object[(i - 1) * width + j] == object[i* width + j - 1])
						object[i * width + j] = object[(i - 1) * width + j];
					else if (object[(i - 1) * width + j] != 0 && object[(i - 1) * width + j] != 'c' && object[i* width + j - 1] != 0 && object[i* width + j - 1] != 'c')
						object[i * width + j] = 'c';
					else if (object[(i - 1) * width + j] != 0 && object[i* width + j - 1] == 0)
						object[i * width + j] = object[(i - 1) * width + j];
					else if (object[i* width + j - 1] != 0 && object[(i - 1) * width + j] == 0)
						object[i * width + j] = object[i* width + j - 1];
					else if (object[i* width + j - 1] != 0 && object[(i - 1) * width + j] == 'c')
						object[i * width + j] = object[i* width + j - 1];
					else if (object[(i - 1)* width + j] != 0 && object[i * width + j - 1] == 'c')
						object[i * width + j] = object[(i - 1)* width + j];
				}

			}
		}

	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (object[i * width + j] == 'c')
			{

				if (object[(i - 1) * width + j] != 0 && object[(i - 1) * width + j] < object[i * width + j - 1])
				{
					object[i * width + j] = object[(i - 1) * width + j];
					int a = object[(i - 1) * width + j];
					int b = object[i * width + j - 1];

					for (int i = 0; i < height*width; i++)
					{
						if (object[i] == b)
							object[i] = a;
					}
				}
				else if (object[i * width + j - 1] != 0 && object[i * width + j - 1] < object[(i - 1) * width + j])
				{
					object[i * width + j] = object[i * width + j - 1];
					int a = object[(i - 1) * width + j];
					int b = object[i * width + j - 1];
					for (int i = 0; i < height*width; i++)
					{
						if (object[i] == a)
							object[i] = b;
					}
				}
				else
				{
					if (object[i * width + j - 1] != 0)
						object[i * width + j] = object[i * width + j - 1];
					else
						object[i * width + j] = object[(i - 1) * width + j];
				}
			}
		}
	}

	int *hist = new int[etiket];
	for (int i = 0; i < etiket; i++)
		hist[i] = 0;

	for (int i = 0; i < width*height; i++)
		hist[object[i]]++;

	label = 0;
	for (int i = 2; i < etiket; i++)
		if (hist[i] != 0)
			label++;

	int cmin = 99999, cmax = -99999;
	int rmin = 99999, rmax = -99999;
	for (int k = 2; k < etiket; k++)
	{
		int cmin = 99999, cmax = -99999;
		int rmin = 99999, rmax = -99999;
		if (hist[k] != 0)
		{
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					if (object[i*width + j] == k)
					{
						if (cmin > j)
							cmin = j;
						else if (cmax < j)
							cmax = j;

						if (rmin > i)
							rmin = i;
						else if (rmax < i)
							rmax = i;
					}

				}
			}
			for (int m = rmin; m <= rmax; m++)
			{
				for (int n = cmin; n <= cmax; n++)
				{
					if (m == rmin || m == rmax)
						buffer[m*width + n] = BYTE(150);
					else
					{
						if (n == cmin || n == cmax)
							buffer[m*width + n] = BYTE(150);
					}
				}
			}
		}

	}
	return buffer;
}





BYTE *canny_Andhough(BYTE *Buffer, unsigned int Width, unsigned int Height)
{
	BYTE *Raw_Intensity = Buffer;

	int C, index = 0;	//Center
	int result;
	int *horizontal_derivative = new int[(Width - 2)*(Height - 2)];
	for (int i = 1; i < Height - 1; i++)
	{
		for (int j = 1; j < Width - 1; j++)
		{
			C = (i*Width + j);
			// 1 2 1 - 0 0 0 - -1 -2 -1  maskesini gezidiriyoruz	yatay maske gezdiriyoruz

			result = (1 * Raw_Intensity[(C - Width - 1)] + 2 * Raw_Intensity[(C - Width)] + 1 * Raw_Intensity[(C - Width + 1)] + 0 * Raw_Intensity[(C - 1)] + 0 * Raw_Intensity[C] + 0 * Raw_Intensity[(C + 1)] + (-1)*Raw_Intensity[(C + Width - 1)] + (-2)*Raw_Intensity[(C + Width)] + (-1)*Raw_Intensity[(C + Width + 1)]);
			horizontal_derivative[index] = abs(result);
			index++;
		}
	}

	index = 0;
	int *vertical_derivative = new int[(Width - 2)*(Height - 2)];
	for (int i = 1; i < Height - 1; i++)
	{
		for (int j = 1; j < Width - 1; j++)
		{
			C = (i*Width + j);
			// 1 0 -1 -  2 0 -2 -  1 0 -1  maskesini gezidiriyoruz		//kenar yönü dikeyde
			result = (1 * Raw_Intensity[(C - Width - 1)] + 0 * Raw_Intensity[(C - Width)] + (-1) *Raw_Intensity[(C - Width + 1)] + 2 * Raw_Intensity[(C - 1)] + 0 * Raw_Intensity[C] + (-2) * Raw_Intensity[(C + 1)] + 1 * Raw_Intensity[(C + Width - 1)] + 0 * Raw_Intensity[(C + Width)] + (-1)*Raw_Intensity[(C + Width + 1)]);
			vertical_derivative[index] = abs(result);
			index++;
		}
	}

	BYTE *deneme6 = new BYTE[(Width - 2) * (Height - 2)];
	for (int i = 0; i < Height - 2; i++)
	{
		for (int j = 0; j < Width - 2; j++)
		{
			C = i * (Width - 2) + j;
			deneme6[C] = round(horizontal_derivative[C]/54);
		}
	}
	long new_size6;
	BYTE *temp_buffer6 = ConvertIntensityToBMP(deneme6, Width - 2, Height - 2, &new_size6);
	LPCTSTR output6;
	output6 = L"C://Users//Orkhan ALIYEV//Desktop//Projeler//fotograflar//FindLine//ytürev.bmp";				//BMP goruntumuzu kaydederiz
	SaveBMP(temp_buffer6, Width - 2, Height - 2, new_size6, output6);


	BYTE *deneme5 = new BYTE[(Width - 2) * (Height - 2)];
	for (int i = 0; i < Height - 2; i++)
	{
		for (int j = 0; j < Width - 2; j++)
		{
			C = i * (Width - 2) + j;
			deneme5[C] = round(vertical_derivative[C] / 4);
		}
	}
	long new_size5;
	BYTE *temp_buffer5 = ConvertIntensityToBMP(deneme5, Width - 2, Height - 2, &new_size5);
	LPCTSTR output5;
	output5 = L"C://Users//Orkhan ALIYEV//Desktop//Projeler//fotograflar//FindLine//dtürev.bmp";				//BMP goruntumuzu kaydederiz
	SaveBMP(temp_buffer5, Width - 2, Height - 2, new_size5, output5);





	int *edge_image = new int[(Width - 2)*(Height * 2)];
	int *edge_image1 = new int[(Width - 2)*(Height * 2)];
	int sonuc2;
	for (int i = 0; i < Height - 2; i++)
	{
		for (int j = 0; j < Width - 2; j++)
		{
			C = (i*(Width - 2) + j);
			// 2 maske sonucunu topluyoruz  not: 255den daha buyuk degeler olabýlýr max 1020 olabýlýr
			result = abs(vertical_derivative[C]) + abs(horizontal_derivative[C]) %255;
			sonuc2 = (vertical_derivative[C] + horizontal_derivative[C]) ;
			edge_image[C] = abs(result);
			edge_image1[C] = abs(sonuc2);
		}
	}

	BYTE *deneme4 = new BYTE[(Width - 2) * (Height - 2)];
	for (int i = 0; i < Height - 2; i++)
	{
		for (int j = 0; j < Width - 2; j++)
		{
			C = i * (Width - 2) + j;
			deneme4[C] = round(edge_image1[C] / 4);
		}
	}
	long new_size4;
	BYTE *temp_buffer4 = ConvertIntensityToBMP(deneme4, Width - 2, Height - 2, &new_size4);
	LPCTSTR output4;
	output4 = L"C://Users//Orkhan ALIYEV//Desktop//Projeler//fotograflar//FindLine//edge.bmp";				//BMP goruntumuzu kaydederiz
	SaveBMP(temp_buffer4, Width - 2, Height - 2, new_size4, output4);


	float Q; //Angle

	for (int i = 0; i < Height - 2; i++)
	{
		for (int j = 0; j < Width - 2; j++)
		{
			C = (i*(Width - 2) + j);

			Q = atan2(vertical_derivative[C], horizontal_derivative[C]) * 180 / PI;		//q=tan^-1((dI/dy)/(dI/dx))		gradient drection

			// buldugumuz aciya gore buyukluk kýyaslamasý yapacagýz ve eger buyukse aynen kalacak degilse 0 atanacak boylece non-maximum suppresion matrisimizi elde edecegiz.
			if ((0 <= Q && Q < 22.5) || (337.5 <= Q && Q <= 360) || (157.5 <= Q && Q < 202.5) || (0 > Q && Q > -22.5) || (-157.5 >= Q && Q > -202.5) || (-337.5 >= Q && Q >= -360))	// acý bu araliktaysa yatayda
			{
				if (j == 0)
				{
					if (edge_image[C] > edge_image[C + 1])
						edge_image[C] = edge_image[C];
					else
						edge_image[C] = 0;
				}
				else if (j == (Width - 2) - 1)
				{
					if (edge_image[C] > edge_image[C - 1])
						edge_image[C] = edge_image[C];
					else
						edge_image[C] = 0;
				}
				else
				{
					if (edge_image[C] > edge_image[C - 1] && edge_image[C] > edge_image[C + 1])
						edge_image[C] = edge_image[C];
					else
						edge_image[C] = 0;
				}

			}

			else if ((22.5 <= Q && Q < 67.5) || (202.5 <= Q && Q < 247.5) || (-112.5 >= Q && Q > -157.5) || (-292.5 >= Q && Q > -337.5))		// acý bu araliktaysa caprazda(45 derece)
			{

				if ((j == 0 && i == 0) || (i == (Height - 2 - 1) && j == (Width - 2) - 1))
				{
					edge_image[C] = edge_image[C];
				}

				else if ((i == 0) || (j == (Width - 2) - 1))
				{
					if (edge_image[C] > edge_image[C + (Width - 2) - 1])
						edge_image[C] = edge_image[C];
					else
						edge_image[C] = 0;
				}

				else if ((j == 0) || (i == (Height - 2) - 1))
				{
					if (edge_image[C] > edge_image[(C - (Width - 2) + 1)])
						edge_image[C] = edge_image[C];
					else
						edge_image[C] = 0;
				}
				else
				{
					if (edge_image[C] > edge_image[(C - (Width - 2) + 1)] && edge_image[C] > edge_image[C + (Width - 2) - 1])
						edge_image[C] = edge_image[C];
					else
						edge_image[C] = 0;
				}

			}

			else if ((67.5 <= Q && Q < 112.5) || (247.5 <= Q && Q < 292.5) || (-67.5 >= Q && Q > -112.5) || (-247.5 >= Q && Q > -292.5))	// acý bu aralikta ise dikeyde (90 derece)
			{
				if (i == 0)
				{
					if (edge_image[C] > edge_image[C + (Width - 2)])
						edge_image[C] = edge_image[C];
					else
						edge_image[C] = 0;
				}
				else if (i == (Height - 2 - 1))
				{
					if (edge_image[C] > edge_image[(C - (Width - 2))])
						edge_image[C] = edge_image[C];
					else
						edge_image[C] = 0;
				}
				else
				{
					if (edge_image[C] > edge_image[C - (Width - 2)] && edge_image[C] > edge_image[C + (Width - 2)])
						edge_image[C] = edge_image[C];
					else
						edge_image[C] = 0;
				}
			}

			else if ((112.5 <= Q && Q < 157.5) || (292.5 <= Q && Q < 337.5) || (-22.5 >= Q && Q > -67.5) || (-202.5 >= Q && Q > -247.5))	// acý bu aralikta ise caprazda (135 derece)
			{
				if ((j == 0 && i == (Height - 2) - 1) || (i == 0 && j == (Width - 2) - 1))
				{
					edge_image[C] = edge_image[C];
				}

				else if (j == 0 || i == 0)
				{
					if (edge_image[C] > edge_image[C + (Width - 2) + 1])
						edge_image[C] = edge_image[C];
					else
						edge_image[C] = 0;
				}

				else if (i == (Height - 2 - 1) || j == (Width - 2 - 1))
				{
					if (edge_image[C] > edge_image[(C - (Width - 2) - 1)])
						edge_image[C] = edge_image[C];
					else
						edge_image[C] = 0;
				}

				else
				{
					if (edge_image[C] > edge_image[(C - (Width - 2) - 1)] && edge_image[C] > edge_image[C + (Width - 2) + 1])
						edge_image[C] = edge_image[C];
					else
						edge_image[C] = 0;
				}

			}

		}
	}

	BYTE *deneme3 = new BYTE[(Width - 2) * (Height - 2)];
	for (int i = 0; i < Height - 2; i++)
	{
		for (int j = 0; j < Width - 2; j++)
		{
			C = i * (Width - 2) + j;
			deneme3[C] = round(edge_image[C] / 4);

		}
	}
	long new_size3;
	BYTE *temp_buffer3 = ConvertIntensityToBMP(deneme3, Width - 2, Height - 2, &new_size3);
	LPCTSTR output3;
	output3 = L"C://Users//Orkhan ALIYEV//Desktop//Projeler//fotograflar//FindLine//non-maximum-suppresion.bmp";				//BMP goruntumuzu kaydederiz
	SaveBMP(temp_buffer3, Width - 2, Height - 2, new_size3, output3);


	// NONMAXÝMUM SUPPRESÝON MATRÝSÝMÝZÝDE BULDUKDAON SONRA HERHANGÝ BÝR TLOW VE THÝGH DEGERÝ SECÝP BINARY GORUNTU ELDE EDICEZ
	// BAZI SAYILAR BINARY OLMAZSA BU SEFER KENAR YONUNDE KOMSULUKLARA BAKICAZ

	//Tlow degerini 20 Thigh degerini 2000 olarak belirledik ve bu sinira gore binary goruntumuzu olusturduk
	int *nonmaximum_suppression = new int[(Width - 2)*(Height - 2)];
	nonmaximum_suppression = edge_image;

	//goruntudeki en buyuk degeri bulduk
	int max_pixel = 0;
	for (int i = 0; i < Height - 2; i++)
		for (int j = 0; j < Width - 2; j++)
		{
			C = i * (Width - 2) + j;
			if (nonmaximum_suppression[C] > max_pixel)
				max_pixel = nonmaximum_suppression[C];

		}

	//Tlow ve Thýgh degerlerýmý belirledik
	for (int i = 0; i < Height - 2; i++)
	{
		for (int j = 0; j < Width - 2; j++)
		{
			C = i * (Width - 2) + j;
			if (nonmaximum_suppression[C] <= 40)
			{
				nonmaximum_suppression[C] = 0;
			}
			else if (nonmaximum_suppression[C] >= max_pixel - 5)
			{
				nonmaximum_suppression[C] = 1;
			}

		}
	}


	BYTE *deneme1 = new BYTE[(Width - 2) * (Height - 2)];
	for (int i = 0; i < Height - 2; i++)
	{
		for (int j = 0; j < Width - 2; j++)
		{
			C = i * (Width - 2) + j;
			deneme1[C] = round(nonmaximum_suppression[C] / 4);

		}
	}
	long new_size1;
	BYTE *temp_buffer1 = ConvertIntensityToBMP(deneme1, Width - 2, Height - 2, &new_size1);
	LPCTSTR output1;
	output1 = L"C://Users//Orkhan ALIYEV//Desktop//Projeler//fotograflar//FindLine//hysteric_threshold.bmp";				//BMP goruntumuzu kaydederiz
	SaveBMP(temp_buffer1, Width - 2, Height - 2, new_size1, output1);

	//Tlow ve Thigh arasýndaki degeler icin kenar dogrultusu yonunde komsuluklara bakarak asýl binary goruntumuzu elde edicez


	for (int i = 0; i < Height - 2; i++)
	{
		for (int j = 0; j < Width - 2; j++)
		{
			C = i * (Width - 2) + j;
			if (nonmaximum_suppression[C] != 0 && nonmaximum_suppression[C] != 1)
			{

				Q = atan2(vertical_derivative[C], horizontal_derivative[C]) * 180 / PI;		//q=tan^-1((dI/dy)/(dI/dx))		gradient drection


			   //buldugumuz acýnýn bu sefer tersine gore yani kenar dogrultusu boyunca komsularýna bakicaz eger 1 ise 1, 0 ise 0 vericez ikisi varsa 0'ý tercih edecegiz.
				if ((0 <= Q && Q < 22.5) || (337.5 <= Q && Q <= 360) || (157.5 <= Q && Q < 202.5) || (0 > Q && Q > -22.5) || (-157.5 >= Q && Q > -202.5) || (-337.5 >= Q && Q >= -360))	// acý bu araliktaysa dikeyde kenar dogrultusunda komsuluklarýna bakýlýr
				{
					if (i == 0)
					{
						if (nonmaximum_suppression[C + (Width - 2)] == 1)
							nonmaximum_suppression[C] = 1;
						else if (nonmaximum_suppression[C + (Width - 2)] == 0)
							nonmaximum_suppression[C] = 0;


					}
					else if (i == (Height - 2) - 1)
					{
						if (nonmaximum_suppression[(C - (Width - 2))] == 1)
							nonmaximum_suppression[C] = 1;
						else if (nonmaximum_suppression[(C - (Width - 2))] == 0)
							nonmaximum_suppression[C] = 0;
					}
					else
					{
						if ((nonmaximum_suppression[(C - (Width - 2))] == 1 && nonmaximum_suppression[C + (Width - 2)] == 1))
							nonmaximum_suppression[C] = 1;

						else if ((nonmaximum_suppression[(C - (Width - 2))] == 0 && nonmaximum_suppression[C + (Width - 2)] == 0) || (nonmaximum_suppression[(C - (Width - 2))] == 0 && nonmaximum_suppression[C + (Width - 2)] == 1) || (nonmaximum_suppression[(C - (Width - 2))] == 1 && nonmaximum_suppression[C + (Width - 2)] == 0))
							nonmaximum_suppression[C] = 0;
					}

				}

				else if ((22.5 <= Q && Q < 67.5) || (202.5 <= Q && Q < 247.5) || (-112.5 >= Q && Q > -157.5) || (-292.5 >= Q && Q > -337.5))		// acý bu araliktaysa caprazda(135 derece) kenar dogrultusunda komsuluklara bakýlýr
				{

					if ((j == 0 && i == (Height - 2) - 1) || (i == 0 && j == (Width - 2) - 1))
					{
						nonmaximum_suppression[C] = 0;
					}

					else if (j == 0 || i == 0)
					{
						if (nonmaximum_suppression[C + (Width - 2) + 1] == 1)
							nonmaximum_suppression[C] = 1;
						else if (nonmaximum_suppression[C + (Width - 2) + 1] == 0)
							nonmaximum_suppression[C] = 0;
					}

					else if (i == (Height - 2 - 1) || j == (Width - 2 - 1))
					{
						if (nonmaximum_suppression[C - (Width - 2) - 1] == 1)
							nonmaximum_suppression[C] = 1;
						else if (nonmaximum_suppression[C - (Width - 2) - 1] == 0)
							nonmaximum_suppression[C] = 0;
					}

					else
					{
						if ((nonmaximum_suppression[(C - (Width - 2) - 1)] == 1 && nonmaximum_suppression[C + (Width - 2) + 1] == 1))
							nonmaximum_suppression[C] = 1;

						else if ((nonmaximum_suppression[(C - (Width - 2) - 1)] == 0 && nonmaximum_suppression[C + (Width - 2) + 1] == 0) || (nonmaximum_suppression[(C - (Width - 2) - 1)] == 0 && nonmaximum_suppression[C + (Width - 2) + 1] == 1) || (nonmaximum_suppression[(C - (Width - 2) - 1)] == 1 && nonmaximum_suppression[C + (Width - 2) + 1] == 0))
							nonmaximum_suppression[C] = 0;
					}

				}

				else if ((67.5 <= Q && Q < 112.5) || (247.5 <= Q && Q < 292.5) || (-67.5 >= Q && Q > -112.5) || (-247.5 >= Q && Q > -292.5))	// acý bu aralikta ise yatayda kenar dogrultusunda komsulklara bakýlýr (0 derece)
				{

					if (j == 0)
					{
						if (nonmaximum_suppression[C + 1] == 1)
							nonmaximum_suppression[C] = 1;
						else if (nonmaximum_suppression[C + 1] == 0)
							nonmaximum_suppression[C] = 0;
					}
					else if (j == (Width - 2) - 1)
					{
						if (nonmaximum_suppression[C - 1] == 1)
							nonmaximum_suppression[C] = nonmaximum_suppression[C - 1];
						else if (nonmaximum_suppression[C - 1] == 0)
							nonmaximum_suppression[C] = 0;
					}
					else
					{
						if ((nonmaximum_suppression[C - 1] == 1 && nonmaximum_suppression[C + 1] == 1))
							nonmaximum_suppression[C] = 1;

						else if ((nonmaximum_suppression[C - 1] == 0 && nonmaximum_suppression[C + 1] == 0) || (nonmaximum_suppression[C - 1] == 0 && nonmaximum_suppression[C + 1] == 1) || (nonmaximum_suppression[C - 1] == 1 && nonmaximum_suppression[C + 1] == 0))
							nonmaximum_suppression[C] = 0;
					}

				}

				else if ((112.5 <= Q && Q < 157.5) || (292.5 <= Q && Q < 337.5) || (-22.5 >= Q && Q > -67.5) || (-202.5 >= Q && Q > -247.5))	// acý bu aralikta ise caprazda (45 derece) kenar dogrultusunda komsuluklara bakýlýr
				{

					if ((j == 0 && i == 0) || (i == (Height - 2 - 1) && j == (Width - 2 - 1)))
					{
						nonmaximum_suppression[C] = 0;
					}

					else if ((i == 0) || (j == (Width - 2) - 1))
					{
						if (nonmaximum_suppression[C + (Width - 2) - 1] == 1)
							nonmaximum_suppression[C] = 1;
						else if (nonmaximum_suppression[C + (Width - 2) - 1] == 0)
							nonmaximum_suppression[C] == 0;

					}

					else if ((j == 0) || (i == (Height - 2) - 1))
					{
						if (nonmaximum_suppression[C + (Width - 2) + 1] == 1)
							nonmaximum_suppression[C] = 1;
						else if (nonmaximum_suppression[C + (Width - 2) + 1] == 0)
							nonmaximum_suppression[C] == 0;
					}
					else
					{
						if ((nonmaximum_suppression[(C - (Width - 2) + 1)] == 1 && nonmaximum_suppression[C + (Width - 2) - 1] == 1))
							nonmaximum_suppression[C] = 1;

						else if ((nonmaximum_suppression[(C - (Width - 2) + 1)] == 0 && nonmaximum_suppression[C + (Width - 2) - 1] == 0) || (nonmaximum_suppression[(C - (Width - 2) + 1)] == 0 && nonmaximum_suppression[C + (Width - 2) - 1] == 1) || (nonmaximum_suppression[(C - (Width - 2) + 1)] == 1 && nonmaximum_suppression[C + (Width - 2) - 1] == 0))
							nonmaximum_suppression[C] = 0;
					}
				}
			}

			/*else
				binary_image[M] = nonmaximum_suppression[M];*/
		}
	}


	int *binary_edge_image = new int[(Width - 2)*(Height - 2)];
	for (int i = 0; i < Height - 2; i++)
	{
		for (int j = 0; j < Width - 2; j++)
		{
			C = i * (Width - 2) + j;
			if (nonmaximum_suppression[C] == 0)
			{
				binary_edge_image[C] = 0;
			}
			/*else if (nonmaximum_suppression[M] == 1)
			{
				binary_edge_image[M] = 1;
			}*/
			else
			{
				binary_edge_image[C] = 1;
			}
		}
	}

	BYTE *deneme = new BYTE[(Width - 2) * (Height - 2)];
	for (int i = 0; i < Height - 2; i++)
	{
		for (int j = 0; j < Width - 2; j++)
		{
			C = i * (Width - 2) + j;
			if (binary_edge_image[C] == 0)
			{
				deneme[C] = 0;
			}
			else
			{
				deneme[C] = 255;
			}

		}
	}
	long new_size;
	BYTE *temp_buffer = ConvertIntensityToBMP(deneme, Width - 2, Height - 2, &new_size);
	LPCTSTR output;
	output = L"C://Users//Orkhan ALIYEV//Desktop//Projeler//fotograflar//FindLine//binary.bmp";				//BMP goruntumuzu kaydederiz
	SaveBMP(temp_buffer, Width - 2, Height - 2, new_size, output);

	int d_limit = (Height * 4);
	int *hough_transform = new int[d_limit * 360];

	for (int i = 0; i < d_limit; i++)
		for (int j = 0; j < 360; j++)
		{
			C = i * 360 + j;
			hough_transform[C] = 0;
		}

	int d;
	int M2;
	int r, c;

	for (int i = 0; i < Height - 2; i++)
	{
		for (int j = 0; j < Width - 2; j++)
		{
			C = i * (Width - 2) + j;
			if (binary_edge_image[C] == 1)
			{
				Q = round(atan2(vertical_derivative[C], horizontal_derivative[C]) * 180 / PI);	//kenar yonunu bulduk

				//negatif yonle gelen acýlarda aslýnda ayni yonu verdigi icin pozitife tamamladik
				if (Q < 0)
					Q = 360 + Q;

				if (Q == 270)
					Q = 90;
				if (Q == 180 || Q == 360)
					Q = 0;

				r = i + 1;
				c = j + 1;
				d = abs(r * round(sin(Q)) + c * round(cos(Q)));

				M2 = d * 360 + Q;
				hough_transform[M2] = hough_transform[M2] + 1;
			}


		}
	}

	BYTE *deneme7 = new BYTE[4 * Height * 360];
	for (int i = 0; i < Height * 4; i++)
	{
		for (int j = 0; j < 360; j++)
		{
			C = i * 360 + j;

			if (hough_transform[C] > 10)
				deneme7[C] = 255;
			else
			{
				deneme7[C] = 0;
			}

		}
	}
	long new_size7;
	BYTE *temp_buffer7 = ConvertIntensityToBMP(deneme7, 360, Height * 4, &new_size7);
	LPCTSTR output7;
	output7 = L"C://Users//Orkhan ALIYEV//Desktop//Projeler//fotograflar//FindLine//hough_transform.bmp";				//BMP goruntumuzu kaydederiz
	SaveBMP(temp_buffer7, 360, Height * 4, new_size7, output7);


	//kenar ve yonlerýnýn tutuldugu diziler
	int kenar_indisleri[500];
	int acý_indisleri[500];
	int k = 0;
	for (int r = 0; r < d_limit; r++)
	{
		for (int c = 0; c < 360; c++)
		{
			C = r * 360 + c;
			if (hough_transform[C] > 20)
			{
				kenar_indisleri[k] = r;
				acý_indisleri[k] = c;
				k++;
			}
		}
	}
	kenar_indisleri[k] = -1;

	for (int i = 0; kenar_indisleri[i] != -1; i++)
	for (int j = 0; kenar_indisleri[j] != -1;j++)
	{
		if (kenar_indisleri[j] < kenar_indisleri[j + 1])
		{
			int gecici = kenar_indisleri[j + 1];
			kenar_indisleri[j + 1] = kenar_indisleri[j];
			kenar_indisleri[j] =gecici;
			int gecici2 = acý_indisleri[j + 1];
			acý_indisleri[j + 1] = acý_indisleri[j];
			acý_indisleri[j] = gecici2;
		}

	}



	int padding = 0;
	int scanlinebytes = Width * 3;
	while ((scanlinebytes + padding) % 4 != 0)     // DWORD = 4 bytes
		padding++;
	// get the padded scanline width
	int psw = scanlinebytes + padding;
	int new_height;
	long newpos;
	int red = 0, green = 0, blue = 255;
	int red1 = 255, green1 = 0, blue1 = 0;

	//dongunun sinirlarý max kenar sayýsýný asmamalý
	for (int i = 0; kenar_indisleri[i] != -1; i++)
	{
		if (acý_indisleri[i] == 0)
		{
			for (int j = 0; j < Height; j++)
			{
				newpos = j * psw + kenar_indisleri[i] * 3;
				Buffer[newpos] = red;
				Buffer[newpos + 1] = green;
				Buffer[newpos + 2] = blue;
			}

		}
		else if (acý_indisleri[i] == 90)
		{
			new_height = (Height - kenar_indisleri[i] - 1);

			for (int column = 0; column < Width; column++)
			{
				newpos = new_height * psw + column * 3;
				Buffer[newpos] = red1;
				Buffer[newpos + 1] = green1;
				Buffer[newpos + 2] = blue1;
			}
		}
	}


	return Buffer;
}

BYTE* MoveImage(BYTE* buffer, int width, int height) 
{
	BYTE* CikisResmi = new BYTE[width*height];
	int x2 = 0, y2 = 0;
	//Taşıma mesafelerini atıyor.
	int Tx = 100;
	int Ty = 50;

	//Tx ve Ty araligini beyazlat!
	for (int x1 = 0; x1 < width; x1++)
	{
		for (int y1 = 0; y1 < height; y1++)
		{
			x2 = x1 + Tx;
			y2 = y1 + Ty;

			if (x2 > 0 && x2 < width && y2 > 0 && y2 < height)
			{	
				CikisResmi[y2*width + x2] = buffer[y1*width+x1];
			}
		}
	}
	return CikisResmi;
}

BYTE* RotateImage(BYTE* buffer, int width, int height, int angle) 
{
	BYTE* CikisResmi = new BYTE[width*height];
	int x2 = 0, y2 = 0;
	
	double RadyanAci = angle * 2 * PI / 360;
	int x0 = width  / 2;
	int y0 = height / 2;

	for (int x1 = 0; x1 < (width); x1++)
	{
		for (int y1 = 0; y1 < (height); y1++)
		{
			//Döndürme Formülleri
			x2 =cos(RadyanAci) * (x1 - x0) - sin(RadyanAci) * (y1 - y0) + x0;
			y2 = sin(RadyanAci) * (x1 - x0) + cos(RadyanAci) * (y1 - y0) + y0;
			if (x2 > 0 && x2 < width && y2>0 && y2 < height)
				CikisResmi[y2*width + x2] = buffer[y1*width + x1];

		}
	}
	return CikisResmi;

}

BYTE* RotateImageAlias(BYTE* buffer, int width, int height, int angle)
{
	BYTE* CikisResmi = new BYTE[width*height];
	int x2 = 0, y2 = 0;

	double RadyanAci = angle * 2 * PI / 360;
	int x0 = width / 2;
	int y0 = height / 2;

	for (int x1 = 0; x1 < (width); x1++)
	{
		for (int y1 = 0; y1 < (height); y1++)
		{
			x2 = (x1 - x0) -tan(RadyanAci / 2) * (y1 - y0) + x0;
			y2 = (y1 - y0) + y0;

			x2 = (x2 - x0) + x0;
			y2 = sin(RadyanAci) * (x2 - x0) + (y2 - y0) + y0;

			x2 = (x2 - x0) - tan(RadyanAci / 2) * (y2 - y0) + x0;
			y2 = (y2 - y0) + y0;

			if (x2 > 0 && x2 < width && y2>0 && y2 < height)
				CikisResmi[y2*width + x2] = buffer[y1*width + x1];

		}
	}
	return CikisResmi;

}

BYTE* MirrorImage(BYTE* buffer, int width, int height, int angle)
{
	BYTE* CikisResmi = new BYTE[width*height];
	int x2 = 0, y2 = 0;

	double RadyanAci = angle * 2 * PI / 360;
	int x0 = width / 2;
	int y0 = height / 2;

	for (int x1 = 0; x1 < (width); x1++)
	{
		for (int y1 = 0; y1 < (height); y1++)
		{
			//Döndürme Formülleri
			double Delta = (x1 - x0) * sin(RadyanAci) - (y1 - y0) * cos(RadyanAci);

			x2 = (x1 + 2 * Delta * (-sin(RadyanAci)));
			y2 = (y1 + 2 * Delta * (cos(RadyanAci)));


			if (x2 > 0 && x2 < width && y2>0 && y2 < height)
				CikisResmi[y2*width + x2] = buffer[y1*width + x1];

		}
	}
	return CikisResmi;
}

BYTE* Shearing(BYTE* buffer, int width, int height, double coefficients, int direction)
{
	BYTE* CikisResmi = new BYTE[width*height];
	int x2 = 0, y2 = 0;
	coefficients = 0.2;



	for (int x1 = 0; x1 < (width); x1++)
	{
		for (int y1 = 0; y1 < (height); y1++)
		{
			if (direction == 0)//+x yonunde
			{
				x2 = x1 + coefficients * y1;
				y2 = y1;
			}else if (direction == 1)//-x yonunde
			{
				x2 = x1 - coefficients * y1;
				y2 = y1;
			}else if (direction == 2) //+y yonunde
			{
				x2 = x1; 
				y2 = coefficients *x1 +y1;
			}else if (direction == 3) //-y yonunde
			{
				x2 = x1;
				y2 = -coefficients * x1 + y1;
			}



			if (x2 > 0 && x2 < width && y2 > 0 && y2 < height)
			{
				CikisResmi[y2*width + x2] = buffer[y1*width + x1];
			}
		}
	}
	return CikisResmi;
}