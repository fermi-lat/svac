#ifndef NUMERIC_RECIPES
#define NUMERIC_RECIPES
#include <math.h>

namespace NR {

extern void polint(float xa[], float ya[], int n, float x, float *y, 
		   float *dy);

extern float qromb(float (*func)(float), float a, float b);

extern float trapzd(float (*func)(float), float a, float b, int n);

extern void kstwo(float data1[], unsigned long n1, float data2[], 
		  unsigned long n2, float *d, float *prob);

extern float probks(float alam);

extern void sort(unsigned long n, float arr[]);
};

#endif
