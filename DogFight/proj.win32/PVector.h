#ifndef __PVECTOR__
#define __PVECTOR__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class PVector {
protected:

public:
	float x;
	float y;

	PVector();
	PVector(PVector *p);
	PVector(float x_, float y_);

	void add(PVector *v);
	void sub(PVector *v);
	void mult(float n);
	void div(float n);
	float mag();
	void normalize();
	void limit(float max);
	void random2D(); // rand -1 / 1
	float heading(); // get the 2D direction angle, in radians

	static PVector *add(PVector *v1, PVector *v2);
	static PVector *sub(PVector *v1, PVector *v2);
	static PVector *mult(PVector *v1, float n);
	static PVector *div(PVector *v1, float n);
};

#endif