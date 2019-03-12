
#include <windows.h>
#include <math.h>
#include <iostream>

using namespace std;

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

//\\
//ZOOM YAPMA FONKSIYONU\\
//\\

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
	unsigned int k = 0;
	unsigned int zoom_width;
	unsigned int zoom_height;
	BYTE *Zoom_buffer;
	if (zoom_height2 > zoom_height1 && zoom_width2 > zoom_width1) {
		zoom_width = ((zoom_width2 - zoom_width1) + 1);
		zoom_height = ((zoom_height2 - zoom_height1) + 1);
		Zoom_buffer = new BYTE[(2 * zoom_height - 1)*(2 * zoom_width - 1)];

		for (unsigned int i = zoom_height1; i < zoom_height2; i++)
		{
			for (unsigned int j = zoom_width1; j < zoom_width2+1; j++)
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
	int N = (int)(sqrt(maskElemanSayisi)); 
	
	if (N*N != maskElemanSayisi) return NULL; 
	if (N % 2 == 0) return NULL;	

	BYTE *buf = new BYTE[(uzunluk - N + 1)*(yukseklik - N + 1)]; 

	int xKonum = 0, yKonum = 0; 
	yeniUzunluk = uzunluk - N + 1;
	yeniYukseklik = yukseklik - N + 1;


	for (int i = 0; i < (uzunluk - N + 1)*(yukseklik - N + 1); i++) 
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

int *Histogram(BYTE* buffer, int width, int height)
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

	int *histogram = Histogram(buffer, width, height);

	for (int i = 0; i < 256; i++)
		stretch[i] = 0;

	float sum = 0.0;
	for (int i = 0; i <= level; i++)
	{
		sum += histogram[i];
		stretch[i] = (int)round((sum / pixel) *level);
	}



	for (int i = 0; i < width * height; i++)
		tBuffer[i] = BYTE(0);

	for (int k = 0; k < 256; k++)
	{
		if (histogram[k] > 0)
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
