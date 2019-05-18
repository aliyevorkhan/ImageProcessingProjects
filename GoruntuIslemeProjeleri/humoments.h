/*
 * Example
 * arr is an array of object and arr must be binary image
 * width and height is integer
 * HuMoments obj1(arr,width,height);
 * obj1.calcOrgins();
 * obj1.calcInvariantMoments();
 * float moments[7];
 * float *moments = obj1.getInvariantMoments();
 */

#ifndef HUMOMENTS_H
#define HUMOMENTS_H

#include <math.h>

class HuMoments
{
public:
	HuMoments(int *array, int width, int height);
	~HuMoments();
	float calcMoment(int p, int q);
	void calcOrgins();
	float calcOrginMoment(int p, int q);
	float calcNormalizedMoment(int p, int q);
	void calcInvariantMoments();
	float *getInvariantMoments();
	void normalizeObject(int *arr);

private:
	int width, height;
	float orginOfX, orginOfY;
	int *object;
	float invariantMoments[7];
};

#endif // HUMOMENTS_H
