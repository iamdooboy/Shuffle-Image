#include "pgmio.h"
#include <iostream>
#include <ctime>

void shuffle_image_3(PGM src, PGM & target);

int main(int argc, char ** argv) {
	srand(time(NULL));

	// both src and target contain a 2D array 
	// of the same size
	PGM src, target;
	readPGM("michael_jordan.pgm", src);
	readPGM("michael_jordan.pgm", target);
	shuffle_image_3(src, target);
	writePGM("michael_jordan_shuffled.pgm", target);
	system("michael_jordan_shuffled.pgm");
	return 0;
}

void shuffle_image_3(PGM src, PGM & target) {

	if (src.row != target.row || src.col != target.col) {
		return;
	}

	bool used[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			used[i][j] = false;
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int r; // randomly select a tile in the source,
			int c; // copy the pixel values from that tile to target
			do {
				r = rand() % 3; // randomly select a tile in the source
				c = rand() % 3;
			} while (used[r][c] == true);

			used[r][c] = true; // we must have used[r][c] == false
			int randRow = r * (src.row / 3);
			int randCol = c * (src.col / 3);
			int randRow2 = i * (src.row / 3);
			int randCol2 = j * (src.col / 3);
			for (int y = 0; y < src.row / 3; y++) {
				for (int x = 0; x < src.col / 3; x++) {
					// move the tile at row r and col c from the source to target at row i and col j
					target.data[randRow + y][randCol + x] = src.data[randRow2 + y][randCol2 + x];
				}
			}
		}
	}
}