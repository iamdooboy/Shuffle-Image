#pragma once
#ifndef _PGMIO
#define _PGMIO

#include <cstdio>
#include <cmath>
#include <cstdlib>

typedef struct _PGM {
	unsigned char ** data;
	int row;
	int col;
} PGM;

void readPGM(char *filename, PGM & im);

void writePGM(char *filename, PGM im);

#endif 