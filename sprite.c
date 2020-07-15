#include"sprite.h"
#include<stdio.h>
#include<stdlib.h>

SPRITE loadBitmap(char *filename,unsigned short *pixelarray[]){

	SPRITE sprite;//sprite that is going to be loaded
	BMPFILEHEADER header;//BMP file header
	BMPFILEINFO info;//BMP file info
	COLOR color;//pixel color components that will be used to
	//generate the color code and put it on the sprite buffer

	unsigned int width;
	unsigned int height;//these are going to be used during
	//pixel data reading

	FILE *ap;
	if((ap=fopen(filename,"rb"))==NULL){
		printf("was unable to open the file\n\n");
		return ;
	}
	printf("File successfully loaded\n");
	//open the file and the opening does not have success is launches as error
	//and returns

	 fread(&header.type,2,1,ap);//reads the file type identifier
	 fread(&header.size,4,1,ap);
	 fread(&header.reserved1,4,1,ap);
	 fread(&header.offset,4,1,ap);

	 if(header.type!=0x4D42){
		 fclose(ap);
		 printf("File is not a BMP FILE\n\n");
		 return ;
	 }
	 printf("file is a BMP file\n");
	 //According to the Microsoft specification the first things that must be written to a BMP file is that it is a BMP file , we do that by wring 4D42 right at the top
	 //so since the type field of the structure has been filled with the first thing at the top, all we need to do is check if the type field has the correct value

	 fread(&info.size,4,1,ap);
	 fread(&info.height,4,1,ap);
	 fread(&info.width,4,1,ap);
	 fread(&info.planes,2,1,ap);
	 fread(&info.bitsPerPixel,2,1,ap);
	 fread(&info.compression,4,1,ap);
	 fread(&info.imagesize,4,1,ap);
	 fread(&info.xresolution,4,1,ap);
	 fread(&info.yresolution,4,1,ap);
	 fread(&info.NumberColors,4,1,ap);
	 fread(&info.importantColors,4,1,ap);

	 width=info.width;
	 height=info.height;//the width and height variables are filled with the values in respective
	 //width and height fields of the BMP file info structure
	 printf("width:%d height:%d\n",width,height);

	 fseek(ap,header.offset,SEEK_SET);//seeks for the place where the pixel data will be
	 //between the file information and the actual pixel data there is a data section about the collor pallete

	 int i=0;
	 short help;
	 for(i=0;i<(info.width*info.height);i++){
		 fread(&help,2,1,ap);
		 if(help<0){
			 //help=~help;
		 }
		 sprite.pixeldata[i]=help;
		 printf("pixel data %d : %d\n",i,help);

	 }
	 sprite.width=width;
	 sprite.height=height;
	 int j=0;
	 int try=0;
	 for(i=0;i<32;i++){
		 for(j=0;j<32;j++){
			 sprite.pixelData[i][j]=sprite.pixeldata[try];
			 try++;
		 }
	 }
	 fclose(ap);
	 return sprite;

}
