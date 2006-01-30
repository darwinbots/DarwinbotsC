/*******************************************************************************
****     This is a vector class for 2D geometry adapted from Vector4        ****
*******************************************************************************/
#ifndef MATH2D_H
#define MATH2D_H

#include <math.h>
#include "Math3D.h"

class Math3D::Vector4;

namespace Math2D {

// definition of the scalar type
typedef float SCALAR;

// inline pass-throughs to various basic math functions
// written in this style to allow for easy substitution with more efficient versions
  inline SCALAR SINE_FUNCTION (SCALAR x) 		{ return sinf(x); }
  inline SCALAR COSINE_FUNCTION (SCALAR x) 	    { return cosf(x); }
  inline SCALAR SQRT_FUNCTION (SCALAR x) 		{ return sqrtf(x); }

// 2 element vector
class Vector2 {
    friend bool operator== (const Vector2&, const Vector2&);
    friend bool operator< (const Vector2&, const Vector2&);

    friend Vector2 operator- (const Vector2&);
    friend Vector2 operator* (const Vector2&, SCALAR);
    friend Vector2 operator* (SCALAR, const Vector2&);
    friend Vector2& operator*= (Vector2&, SCALAR);
    friend Vector2 operator/ (const Vector2&, SCALAR);
    friend Vector2& operator/= (Vector2&, SCALAR);

    friend Vector2 operator+ (const Vector2&, const Vector2&);
    friend Vector2& operator+= (Vector2&, const Vector2&);
    friend Vector2 operator- (const Vector2&, const Vector2&);
    friend Vector2& operator-= (Vector2&, const Vector2&);

    friend SCALAR DotProduct (const Vector2&, const Vector2&);
    friend SCALAR operator* (const Vector2 &, const Vector2 &);

    friend SCALAR CrossProduct (const Vector2&, const Vector2&);
    friend SCALAR operator^ (const Vector2 &, const Vector2 &);
    friend SCALAR operator% (const Vector2&, const Vector2&);

public:
	Vector2 () {};
	Vector2 (SCALAR a, SCALAR b): X(a),Y(b) {};
    explicit Vector2(SCALAR* initArray): X(initArray[0]),Y(initArray[1]) {};
    Vector2 (const Math3D::Vector4& v4):X(v4.x()),Y(v4.y()){};
    
	void set(const SCALAR &x, const SCALAR &y){ X = x; Y = y; }

	// [] is to read, () is to write (const correctness)
	/*inline const SCALAR& operator[] (int i) const
    {
        return e[i];
    }

	inline SCALAR& operator() (int i)
    {
        return e[i];
    }*/

	const SCALAR &x() const { return X; }
	const SCALAR &y() const { return Y; }
	
	SCALAR LengthSquared() const
        {return X*X+Y*Y;};
    SCALAR Length() const
        {return SQRT_FUNCTION(LengthSquared());};
    Vector2 Normalize()
        {return (*this)/=this->Length();};
	
private:
    float X;
	float Y;
	
};

inline bool operator== (const Vector2& v1, const Vector2& v2)
{
    return ( v1.X == v2.X && v1.Y == v2.Y );
}

inline bool operator< (const Vector2& v1, const Vector2& v2)
{
	if (v1.X < v2.X) return true;
		else if (v1.X > v2.X) return false;
    if (v1.Y < v2.Y) return true;
		else if (v1.Y < v2.Y) return false;
	return false;
}

inline Vector2 operator- (const Vector2& v)
{
    return Vector2(-v.X, -v.Y);
}

inline Vector2 operator* (SCALAR k, const Vector2& v)
{
    return Vector2(k*v.X, k*v.Y);
}

inline Vector2 operator* (const Vector2& v, SCALAR k)
{
    return k*v;
}

inline Vector2& operator*= (Vector2& v, SCALAR k)
{
    v.X*=k;
    v.Y*=k;
    return v;
}

inline Vector2 operator/ (const Vector2& v, SCALAR k)
{
    return Vector2(v.X/k, v.Y/k);
}

inline Vector2& operator/= (Vector2& v, SCALAR k)
{
    v.X/=k;
    v.Y/=k;
    return v;
}

inline Vector2 operator+ (const Vector2& v1, const Vector2& v2)
{
    return Vector2( v1.X + v2.X, v1.Y + v2.Y );
}

inline Vector2& operator+= (Vector2& v1, const Vector2& v2)
{
    v1.X+=v2.X;
    v1.Y+=v2.Y;
    return v1;
}


inline Vector2 operator- (const Vector2 &v1, const Vector2 &v2)
{
    return Vector2( v1.X - v2.X, v1.Y-v2.Y);
}

inline Vector2& operator-= (Vector2& v1, const Vector2& v2)
{
    v1.X-=v2.X;
    v1.Y-=v2.Y;
    return v1;
}

inline SCALAR DotProduct (const Vector2& v1, const Vector2& v2)
{
    return v1.X*v2.X + v1.Y*v2.Y;
}
inline SCALAR operator * (const Vector2 &v1, const Vector2 &v2)
{ return DotProduct(v1, v2); }

//Strictly speaking, the result should be a pseudo-scalar, but it's almost certainly irrelevant
inline SCALAR CrossProduct (const Vector2& v1, const Vector2& v2)
{
    return v1.X*v2.Y - v1.Y*v2.X;
}
inline SCALAR operator^ (const Vector2 &v1, const Vector2 &v2)
{ return CrossProduct(v1, v2); }

//for compatibility with Vector4 class
inline SCALAR operator% (const Vector2 &v1, const Vector2 &v2)
{	return CrossProduct(v1, v2); }


} //close namespace Math2D

#endif //MATH2D_H
