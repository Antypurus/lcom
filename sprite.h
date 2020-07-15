#pragma once

/** @defgroup Bitmap Bitmap
 * @{
 * Functions for manipulating bitmaps
 */
#pragma pack(push ,1)

typedef struct BITMAPFILEHEADERtag{

	unsigned short type; //File type identifier - tells us if the file is a bmp file
	unsigned int size; //file size in bytes
	unsigned int reserved1; //reserved must be 0
	//unsigned int reserved2; //according to the Microsoft specification
	//there should be 2 reserved slots but in practice there is only 1
	unsigned int offset; // offset to pixel data from the beginning of the file

}BMPFILEHEADER;

typedef struct BITMAPFILEINFOtag{

	unsigned int size; //header size in bytes
	int height;
	int width; //image resolution in pixels
	unsigned short planes; //number of color planes
	unsigned short bitsPerPixel; //bits per pixel
	unsigned int compression; //compression type
	unsigned int imagesize; //image size in bytes
	int xresolution;
	int yresolution; //pixels per meter
	unsigned int NumberColors; //number of colors
	unsigned int importantColors; //number of important colors

}BMPFILEINFO;

typedef struct COLORCODEtag{

	unsigned short red,green,blue; //color components

}COLOR;

typedef struct SPRITE{

	unsigned int width; //image width
	unsigned int height; //iamge height
	unsigned short pixeldata[640*480];
	unsigned short pixelData[480][640];

}SPRITE;

SPRITE loadBitmap(char *filename,unsigned short **pixelarray);

#pragma pack(pop)
