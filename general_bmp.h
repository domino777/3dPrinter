/*
 * general_bmp.h
 *
 * Created: 30/10/2012 00:50:34
 *  Author: domyno
 */ 


#ifndef GENERAL_BMP_H_
#define GENERAL_BMP_H_


char const glyph_8x6 [] = 
{	  0, 0, 0, 0, 0, 0				//   //
	, 0, 0, 0, 190, 0, 0			// ! //
	, 0, 0, 6, 0, 6, 0				// " //
	, 0, 80, 248, 80, 248, 80		// # //
	, 0, 8, 84, 214, 84, 32			// $ //
	, 0, 68, 42, 84, 168, 68		// % //
	, 0, 108, 146, 170, 68, 160		// & //
	, 0, 14, 0, 0, 0, 0				// ' //
	, 0, 56, 68, 130, 0, 0			// ( //
	, 0, 0, 130, 68, 56, 0			// ) //
	, 0, 42, 28, 62, 28, 42			// * //
	, 0, 16, 16, 124, 16, 16		// + //
	, 0, 128, 96, 0, 0, 0			// , //
	, 0, 16, 16, 16, 16, 16			// - //
	, 0, 0, 128, 0, 0, 0			// . //
	, 0, 0, 192, 56, 6, 0			// / //
	, 0, 124, 146, 138, 124, 0		// 0 // HX30
	, 0, 0, 128, 132, 254, 128		// 1 //
	, 0, 132, 194, 162, 146, 140	// 2 //
	, 0, 68, 130, 146, 146, 108		// 3 //
	, 0, 48, 40, 36, 254, 32		// 4 //
	, 0, 78, 138, 138, 138, 112		// 5 //
	, 0, 124, 146, 146, 146, 96		// 6 //
	, 0, 2, 2, 226, 26, 6			// 7 //
	, 0, 108, 146, 146, 146, 108	// 8 //
	, 0, 12, 146, 146, 146, 124		// 9 // HX39
	, 0, 0, 136, 0, 0, 0			// : //
	, 0, 128, 104, 0, 0, 0			// ; //
	, 0, 16, 40, 68, 130, 0			// < //
	, 0, 40, 40, 40, 40, 0			// = //
	, 0, 130, 68, 40, 16, 0			// > //
	, 0, 4, 2, 178, 18, 12			// ? //
	, 0, 124, 130, 186, 170, 60		// @ //
	, 0, 252, 34, 34, 34, 252		// A //
	, 0, 254, 138, 138, 148, 96		// B //
	, 0, 124, 130, 130, 130, 68		// C //
	, 0, 254, 130, 130, 132, 120	// D //
	, 0, 254, 146, 146, 146, 128	// E //
	, 0, 254, 18, 18, 18, 2			// F //
	, 0, 124, 130, 130, 162, 100	// G //
	, 0, 254, 16, 16, 16, 254		// H //
	, 0, 130, 130, 254, 130, 130	// I //
	, 0, 98, 130, 130, 126, 2		// J //
	, 0, 254, 16, 40, 68, 130		// K //
	, 0, 254, 128, 128, 128, 128	// L //
	, 0, 254, 4, 8, 4, 254			// M //
	, 0, 254, 4, 8, 16, 254			// N //
	, 0, 124, 130, 130, 130, 124	// O //
	, 0, 254, 18, 18, 18, 12		// P //
	, 0, 124, 130, 162, 66, 188		// Q //
	, 0, 254, 18, 50, 82, 140		// R //
	, 0, 76, 146, 146, 146, 100		// S //
	, 0, 2, 2, 254, 2, 2			// T //
	, 0, 126, 128, 128, 128, 126	// U //
	, 0, 126, 128, 128, 64, 62		// V //
	, 0, 126, 128, 112, 128, 126	// W //
	, 0, 198, 40, 16, 40, 198		// X //
	, 0, 14, 16, 224, 16, 14		// Y //
	, 0, 194, 162, 146, 138, 134	// Z //
	, 0, 0, 254, 130, 130, 0		// [ //
	, 0, 12, 48, 192, 0, 0			// \ //
	, 0, 0, 130, 130, 254, 0		// ] //
	, 0, 8, 4, 2, 4, 8				// ^ //
	, 0, 128, 128, 128, 128, 128	// _ //
	, 0, 0, 0, 2, 4, 8				// boh //
	, 0, 64, 168, 168, 168, 112		// a //
	, 0, 124, 160, 144, 144, 96		// b //
	, 0, 112, 136, 136, 136, 80		// c //
	, 0, 96, 144, 144, 144, 124		// d //
	, 0, 112, 168, 168, 168, 48		// e //
	, 0, 32, 248, 36, 4, 8			// f //
	, 0, 16, 168, 168, 168, 112		// g //
	, 0, 252, 32, 16, 16, 224		// h //
	, 0, 0, 128, 144, 244, 128		// i //
	, 0, 0, 64, 144, 116, 0			// j //
	, 0, 248, 32, 48, 40, 192		// k //
	, 0, 128, 132, 132, 252, 128	// l //
	, 0, 248, 8, 240, 8, 240		// m //
	, 0, 248, 16, 8, 8, 240			// n //
	, 0, 112, 136, 136, 136, 112	// o //
	, 0, 240, 40, 40, 40, 16		// p //
	, 0, 16, 40, 40, 40, 240		// q //.
	, 0, 248, 16, 8, 8, 48			// r //
	, 0, 16, 168, 168, 168, 64		// s //
	, 0, 8, 124, 136, 136, 64		// t //
	, 0, 120, 128, 128, 64, 248		// u //
	, 0, 56, 64, 128, 64, 56		// v //
	, 0, 120, 128, 96, 128, 120		// w //
	, 0, 136, 80, 32, 80, 136		// x //
	, 0, 24, 160, 160, 64, 56		// y //
	, 0, 136, 200, 168, 152, 136	// z //
	, 0, 0, 16, 108, 130, 0			// { //
	, 0, 0, 0, 254, 0, 0			// | //
	, 0, 0, 130, 108, 16, 0			// } //
	, 0, 4, 2, 4, 4, 2				// tilde //	
	}; 
char const glyph_32x25[] ={
	  0, 0, 0, 0, 0, 128, 192, 224, 240, 120, 56, 56, 56, 56, 56, 120, 240, 240, 224, 128, 0, 0, 0, 0, 0	// 0 //
	, 0, 0, 0, 0, 248, 255, 255, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 255, 255, 248, 0, 0, 0, 0
	, 0, 0, 0, 0, 63, 255, 255, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 255, 255, 63, 0, 0, 0, 0
	, 0, 0, 0, 0, 0, 3, 15, 31, 30, 60, 56, 56, 56, 56, 56, 60, 30, 15, 7, 3, 0, 0, 0, 0, 0

	, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 192, 224, 240, 248, 248, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0					// 1 //
	, 0, 0, 0, 0, 0, 28, 14, 15, 7, 7, 3, 1, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 63, 63, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	
	, 0, 0, 0, 0, 192, 224, 240, 112, 112, 56, 56, 56, 56, 56, 56, 120, 112, 240, 224, 192, 0, 0, 0, 0, 0	// 2 //
	, 0, 0, 0, 6, 7, 7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 225, 255, 127, 31, 0, 0, 0, 0
	, 0, 0, 0, 0, 0, 0, 0, 128, 192, 224, 224, 112, 56, 60, 30, 15, 7, 3, 1, 0, 0, 0, 0, 0, 0
	, 0, 0, 0, 48, 60, 62, 63, 59, 59, 57, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 0, 0, 0, 0
	
	, 0, 0, 0, 0, 0, 192, 224, 240, 112, 120, 56, 56, 56, 56, 56, 112, 240, 224, 192, 128, 0, 0, 0, 0, 0	// 3 //
	, 0, 0, 0, 0, 3, 3, 3, 1, 0, 0, 128, 192, 192, 192, 224, 224, 240, 191, 63, 15, 0, 0, 0, 0, 0
	, 0, 0, 0, 0, 192, 192, 192, 0, 0, 0, 1, 1, 1, 1, 1, 1, 3, 7, 255, 254, 248, 0, 0, 0, 0
	, 0, 0, 0, 0, 0, 3, 15, 31, 28, 60, 56, 56, 56, 56, 56, 28, 28, 15, 15, 3, 1, 0, 0, 0, 0
	
	, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 224, 240, 248, 248, 248, 0, 0, 0, 0, 0, 0, 0					// 4 //
	, 0, 0, 0, 0, 0, 0, 128, 192, 240, 248, 62, 31, 7, 3, 1, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0
	, 0, 0, 0, 120, 124, 127, 127, 119, 113, 112, 112, 112, 112, 112, 112, 255, 255, 255, 112, 112, 112, 0, 0, 0, 0
	, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 63, 63, 63, 0, 0, 0, 0, 0, 0, 0
	
	, 0, 0, 0, 0, 0, 0, 224, 248, 248, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 0, 0, 0, 0, 0			// 5 //
	, 0, 0, 0, 0, 128, 252, 255, 255, 227, 96, 112, 112, 112, 112, 112, 240, 224, 224, 192, 128, 0, 0, 0, 0, 0
	, 0, 0, 0, 0, 193, 193, 193, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 255, 255, 254, 0, 0, 0, 0
	, 0, 0, 0, 0, 1, 7, 15, 31, 28, 60, 56, 56, 56, 56, 56, 28, 28, 15, 7, 3, 0, 0, 0, 0, 0
	
	, 0, 0, 0, 0, 0, 0, 128, 224, 224, 240, 112, 56, 56, 56, 56, 56, 120, 112, 240, 224, 192, 0, 0, 0, 0	// 6 //
	, 0, 0, 0, 0, 240, 255, 255, 135, 193, 224, 96, 112, 112, 112, 112, 112, 240, 224, 225, 195, 3, 3, 0, 0, 0
	, 0, 0, 0, 0, 63, 255, 255, 131, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 255, 255, 252, 0, 0, 0
	, 0, 0, 0, 0, 0, 1, 7, 15, 30, 28, 56, 56, 56, 56, 56, 56, 28, 30, 15, 7, 3, 0, 0, 0, 0
	
	, 0, 0, 0, 0, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 184, 248, 120, 56, 0, 0, 0, 0			// 7 //
	, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 240, 248, 62, 15, 3, 1, 0, 0, 0, 0, 0, 0
	, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 248, 255, 31, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	, 0, 0, 0, 0, 0, 0, 0, 0, 60, 63, 63, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	
	, 0, 0, 0, 0, 0, 128, 192, 224, 240, 120, 56, 56, 56, 56, 56, 112, 240, 224, 192, 128, 0, 0, 0, 0, 0	// 8 //
	, 0, 0, 0, 0, 0, 31, 63, 127, 240, 224, 192, 192, 192, 192, 192, 224, 240, 127, 63, 31, 0, 0, 0, 0, 0
	, 0, 0, 0, 0, 248, 254, 255, 15, 3, 3, 1, 1, 1, 1, 1, 3, 3, 15, 254, 254, 248, 0, 0, 0, 0
	, 0, 0, 0, 0, 1, 7, 15, 30, 28, 60, 56, 56, 56, 56, 56, 60, 28, 31, 15, 7, 1, 0, 0, 0, 0
	
	, 0, 0, 0, 0, 0, 128, 224, 240, 240, 120, 56, 56, 56, 56, 56, 112, 112, 224, 192, 128, 0, 0, 0, 0, 0	// 9 //
	, 0, 0, 0, 0, 254, 255, 255, 129, 0, 0, 0, 0, 0, 0, 0, 0, 0, 129, 255, 255, 252, 0, 0, 0, 0
	, 0, 0, 0, 0, 128, 131, 135, 15, 14, 30, 28, 28, 28, 28, 12, 14, 7, 195, 255, 255, 63, 0, 0, 0, 0
	, 0, 0, 0, 0, 1, 7, 15, 30, 28, 56, 56, 56, 56, 56, 60, 28, 14, 15, 7, 1, 0, 0, 0, 0, 0

	, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0						// : //
	, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

char const SYMS3_BMP[512] = {
	0,   0,   0, 192,   0,   0,   0,   0, 192,   0,   0, 128,
	64,  64,  64,  64,   0,   0, 128,  64,  64, 128, 128,   0,
	0,   0,   0,  64, 248,  68,  68,   4,  64,  64,  64, 128,
	0,   0,   0, 192,  64,  64,  64,  64, 128,  64,  64,  64,
	64, 128,   0, 196,   0,   0, 252,   0,   0, 196,   0,   0,
	0,   0,  64,  64,  64, 128,   0,   0, 128, 128,  64,   0,
	0,   0,   0,   0, 128,  64,  64,  64,  64, 192,   0,   0,
	0,   0,   0,  15,  16,  16,  16,  16,  31,   0,   0,   9,
	18,  18,  12,   0,   0,  15,  18,  18,  18,  18,  11,   2,
	0,   0,   0,   0,  31,   0,   0,  12,  18,  17,  17,  31,
	0,   0,   0,  31,   0,   0,   0,   0,
	0,   0,   0,  15,  16,  16,  16,  16,  31,   0,   0,   9,
	18,  18,  12,   0,   0,  15,  18,  18,  18,  18,  11,   2,
	0,   0,   0,   0,  31,   0,   0,  12,  18,  17,  17,  31,
	0,   0,   0,  31,   0,   0,   0,   0,  31,   0,   0,   0,
	0,  31,   0,  31,   0,   0,  31,   0,   0,  31,   0,   0,
	0,  12,  18,  17,  17,  31,   0,   0,  31,   0,   0,   0,
	0,   0,   0,   0,   9,  18,  18,  12,   0, 129, 198,  56,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,  64, 224, 240, 240,  96,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,  64, 224, 240, 240,  96,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0, 240, 248, 248, 240,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0, 192, 224, 112,  48,  56, 248, 252,
	252, 254, 254, 252, 249, 128,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0, 192, 224, 112,  48,  56, 248, 252,
	252, 254, 254, 252, 249, 128,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0, 255, 255, 255, 255,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,  48, 248, 252, 252, 252, 248,  56,
	0,   0,   0,   0,   0,  31,  31,   0,   0, 252, 255, 255,
	255, 255, 199,   1,   3,   7,   6,  14,  12,  28,  24,  24,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 128,
	192, 192, 224, 240, 240, 248, 248, 252
};




#endif /* GENERAL_BMP_H_ */