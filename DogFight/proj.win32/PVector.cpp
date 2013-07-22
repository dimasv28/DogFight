#include "PVector.h"

PVector::PVector() {
	x = 0;
	y = 0;
}

PVector::PVector(PVector *p) {
	x = p->x;
	y = p->y;
}

PVector::PVector(float x_, float y_) {
	x = x_;
	y = y_;
}

void PVector::add(PVector *v) {
	y = y + v->y;
	x = x + v->x;
}

void PVector::sub(PVector *v) {
	x = x - v->x;
	y = y - v->y;
}

void PVector::mult(float n) {
	x = x * n;
	y = y * n;
}

void PVector::div(float n) {
	x = x / n;
	y = y / n;
}

float PVector::mag() {
	return sqrt(x*x + y*y);
}

void PVector::normalize() {
	float m = mag();
	if (m != 0) {
		div(m);
	}
}

void PVector::limit(float max) {
	if ( mag() > max ) {
		normalize();
		mult(max);
	}
}

void PVector::random2D() {
	int r1 = rand() % 2;
	int r2 = rand() % 2;
	if(!r1)	{ r1 = -1; }
	if(!r2)	{ r2 = -1; }
	x = r1;
	y = r2;
}

float PVector::heading() {
	return atan2(y,x);
}

PVector *PVector::add(PVector *v1, PVector *v2) {
	PVector *v3 = new PVector(v1->x + v2->x, v1->y + v2->y);
	return v3;
}

PVector *PVector::sub(PVector *v1, PVector *v2) {
	PVector *v3 = new PVector(v1->x - v2->x, v1->y - v2->y);
	return v3;
}

PVector *PVector::mult(PVector *v1, float n) {
	PVector *v2 = new PVector(v1->x * n, v1->y * n);
	return v2;
}

PVector *PVector::div(PVector *v1, float n) {
	PVector *v2 = new PVector(v1->x / n, v1->y / n);
	return v2;
}