#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/sge.h>
#include "config.h"
#include "primitives.h"
#include "tools.h"



namespace ephidrena
{

typedef struct Vertex
{
	Uint32 x;
	Uint32 y;
} _V;
        

class Matrix;
class ostream;

class Vector3D
{

public:
	float x,y,z;

	Vector3D() {}
	Vector3D(float X, float Y, float Z) { x=X; y=Y; z=Z; }
	Vector3D(float X) {x = y = z = X;}
	Vector3D(const Vector3D &v) { x=v.x; y=v.y; z=v.z; }

	friend float Magnitude(const Vector3D &v);
	friend Vector3D Normalize(const Vector3D &A);

	Vector3D operator+ () const;
	Vector3D operator- () const;

	Vector3D &operator+= (const Vector3D &A);
	Vector3D &operator-= (const Vector3D &A);
	Vector3D &operator*= (const Vector3D &A);
	Vector3D &operator*= (float A);
	Vector3D &operator/= (float A);

	friend Vector3D operator+ (const Vector3D &A, const Vector3D &B);
	friend Vector3D operator- (const Vector3D &A, const Vector3D &B);
	friend Vector3D operator* (const Vector3D &A, const Vector3D &B);
	friend Vector3D operator* (float A, const Vector3D &B);
	friend Vector3D operator* (const Matrix&, const Vector3D&);
	friend Vector3D operator/ (const Vector3D &A, const Vector3D &B);

	friend int operator< (const Vector3D &A, const Vector3D &B);

	friend Vector3D operator/ (const Vector3D &A, float B);
	friend int operator== (const Vector3D &A, const Vector3D &B);
	friend float DotProd(const Vector3D &A, const Vector3D &B);
	friend Vector3D CrossProd(const Vector3D &A, const Vector3D &B);

	friend ostream& operator<< (const ostream &s, const Vector3D& A);
	
	friend void Minimize(Vector3D &min, const Vector3D &Candidate);
	friend void Maximize(Vector3D &max, const Vector3D &Candidate);
	
};

inline float Magnitude(const Vector3D &v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

inline Vector3D Normalize(const Vector3D &A, const Vector3D &B)
{
	return A / Magnitude(A);
}

inline float DotProd (const Vector3D &A, const Vector3D &B)
{
	return A.x * B.x + A.y * B.y + A.z * B.z;
}

inline Vector3D Vector3D::operator+ () const
{
	return *this;
}

inline Vector3D Vector3D::operator- () const
{
	return Vector3D(-x, -y, -z);
}

inline Vector3D &Vector3D::operator+= (const Vector3D &A)
{
	x+= A.x;
	y+= A.y;
	z+= A.z;
	return *this;
}

inline Vector3D &Vector3D::operator-= (const Vector3D &A)
{
	x-= A.x;
	y-= A.y;
	z-= A.z;
	return *this;
}

inline Vector3D &Vector3D::operator*= (float A)
{
	x*= A;
	y*= A;
	z*= A;
	return *this;
}

inline Vector3D &Vector3D::operator/= (float A)
{
	x/= A;
	y/= A;
	z/= A;
	return *this;
}

inline Vector3D &Vector3D::operator*= (const Vector3D &A)
{
	x*= A.x;
	y*= A.y;
	z*= A.z;
	return *this;
}
		
inline Vector3D operator+ (const Vector3D &A, const Vector3D &B)
{
	return Vector3D(A.x + B.x, A.y + B.y, A.z + B.z);
}

inline Vector3D operator- (const Vector3D &A, const Vector3D &B)
{
	return Vector3D(A.x - B.x, A.y - B.y, A.z - B.z);
}

inline Vector3D operator* (const Vector3D &A, const Vector3D &B)
{
	return Vector3D(A.x * B.x, A.y * B.y, A.z * B.z);
}

inline Vector3D operator* (const Vector3D &A, float B)
{
	return Vector3D(A.x * B, A.y * B, A.z * B);
}

inline Vector3D operator* (float A, const Vector3D &B)
{
	return B * A;
}

inline Vector3D operator/ (const Vector3D &A, const Vector3D &B)
{
	return (A.x/B.x, A.y/B.y, A.z/B.z);
}

inline Vector3D operator/ (const Vector3D &A, float B)
{
	return (A.x/B, A.y/B, A.z/B);
}

inline int operator< (const Vector3D &A, const Vector3D &B)
{
	return A.x < B.x && A.y < B.y && A.z < B.z;
}

inline int operator== (const Vector3D &A, const Vector3D &B)
{
	return (A.x == B.x) && (A.y == B.y) && (A.z == B.z);
}
 
inline Vector3D CrossProd (const Vector3D &A, const Vector3D &B)
{
	return Vector3D(A.y * B.z - A.z * B.y,
			A.z * B.x - A.x * B.z,
			A.x * B.y - A.y * B.x);
}

	
class Engine
{
private:      
        
	void  fastTriangle(const _V &Vertex, const _V &Vertex, const _V &Vertex, SDL_Surface*);
	void  triangle(const Vertex, const Vertex, const Vertex);
	int*  min(int*, int*, int*);
	float min(float, float, float);
	int*  max(int*, int*, int*);
	float max(float, float, float);
	float y1,y2,y3;
	float x1,x2,x3;
	// Bounding rectangle
	int minx, maxx, miny,maxy;

public:
	Engine();
	~Engine();
};

}
