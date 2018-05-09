#include <cstdio>
#include <cmath>
#include <cstdlib>
#include "pgmio.h"
// ***************************************************
// ************ open an image from file **************
// ***************************************************
void readPGM(char *filename, PGM & im)

{

	FILE *fptr;
	int r, c, count;
	char buff[100], comments[100];
	int row, col, numColor;

	if ((fptr = fopen(filename, "rb")) == NULL)
		printf("File does not exist!");	//bad source file name

	else
		if (fgetc(fptr) != 'P')			//check if the source file is in correct format
		{
			printf("Not a PGM file!");
			fclose(fptr);
			exit(0);
		}


		else
		{

			fgets(buff, 100, fptr);		//inputs the first line in the image (starting from 'P')
			fgets(comments, 100, fptr);	//comments are stored in char array comments
			count = 0;

			while ((buff[count] = fgetc(fptr)) != ' ') count++;
			buff[count] = '\0';
			col = atoi(buff);			//read number of cols and rows and convrets char to int

			fgets(buff, 100, fptr);
			row = atoi(buff);

			fgets(buff, 100, fptr);		//read max grey level
			numColor = atoi(buff);

			im.row = row;
			im.col = col;

			im.data = new unsigned char *[row];

			for (r = 0; r<row; r++)
			{
				im.data[r] = new unsigned char[col];
			}

			for (r = 0; r<row; r++)		//read image from the file and loads in the array
				for (c = 0; c<col; c++)
					im.data[r][c] = (unsigned char)fgetc(fptr);
			fclose(fptr);				//close the file pointer
		}

}

//******************************************************
//**************** write image in a file ***************
//******************************************************
void writePGM(char *filename, PGM  im)
{

	int r, c;

	FILE *fptr;

	fptr = fopen(filename, "wb");		//create target file

	fputs("P5", fptr);					//format for pgm
	fputc('\n', fptr);

	fputs("#this is demo image in binaray format", fptr);	//comments
	fputc('\n', fptr);

	fprintf(fptr, "%d %d\n255\n", im.col, im.row);

	for (r = 0; r<im.row; r++)				//write the file
		for (c = 0; c<im.col; c++)
			fputc((unsigned char)((int)(im.data[r][c]) % 256), fptr);
	fclose(fptr);						//close the file pointer

}
