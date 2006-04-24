#ifndef VECTORS_H
#define VECTORS_H

/***********************************************************
Vector class I swiped from some article and totally rewrote.

vector2 * vector2 = 2D dot product = SCALAR
vector3 * Vector3 = 3D dot product = SCALAR
vector2 % vector2 = 2D cross product = SCALAR
vector3 % vector3 = 2D cross product (ignores z) = SCALAR
vector3 ^ vector3 = 3D cross product = Vector4

************************************************************/

#include <math.h>

typedef float SCALAR_F;

inline SCALAR_F SQRT_FUNCTION   (SCALAR_F x) 		{ return sqrtf(x); }
inline SCALAR_F FLOOR_FUNCTION  (SCALAR_F x) 		{ return floorf(x); }
inline SCALAR_F CEIL_FUNCTION   (SCALAR_F x) 		{ return ceilf(x); }

class Vector3f
{
    friend inline Vector3f floor(const Vector3f &v);
    friend inline Vector3f ceil(const Vector3f &v);
    friend inline Vector3f CrossProduct (const Vector3f &v1, const Vector3f &v2);
    
    private:
    
    //provide 2 different ways to access the same element 
    static union
    {   
	    struct
	    {
		    SCALAR_F X;
		    SCALAR_F Y;
		    SCALAR_F Z;
	    };	
	    SCALAR_F e[3];
    };

    public:
	Vector3f (void) {};
    /*{
        X = Y = Z = 0;    
    }
	/*Vector3f (SCALAR_F a, SCALAR_F b, SCALAR_F c=0);
    Vector3f (int a, int b, int c=0);
    Vector3f (const Vector3f &v);

	inline Vector3f &set(const SCALAR_F &x, const SCALAR_F &y, const SCALAR_F &z=0.0f);
    inline Vector3f &Vector3f::setX(const SCALAR_F &x);
    inline Vector3f &Vector3f::setY(const SCALAR_F &y);
    inline Vector3f &Vector3f::setZ(const SCALAR_F &z);*/
	
	// [] is to read, () is to write (const correctness)
    //bounds are not checked
	inline const SCALAR_F &operator[] (int i) const
    {
        return e[i];
    }

	inline SCALAR_F &operator() (int i)
    {
        return e[i];
    }

	inline const SCALAR_F &x(void) const { return X; }
	inline const SCALAR_F &y(void) const { return Y; }
	inline const SCALAR_F &z(void) const { return Z; }
	
	// Provides access to the underlying array; useful for passing this class off to C APIs
	inline const SCALAR_F *readArray(void) { return e; }
	inline SCALAR_F *getArray(void) { return e; }

    /*inline SCALAR_F LengthSquared() const;
    inline SCALAR_F Length() const;
    inline Vector3f Normal() const;
    inline Vector3f Normalize();

    inline bool     operator==  (const Vector3f &v);
    inline bool     operator!=  (const Vector3f &v);
    
    inline Vector3f operator-   ();
    inline Vector3f operator*   (const SCALAR_F k)  const;
    inline void     operator*=  (const SCALAR_F k);
    inline Vector3f operator/   (const SCALAR_F k);
    inline void     operator/=  (const SCALAR_F k);
    inline Vector3f operator+   (const Vector3f &v) const;
    inline Vector3f operator+   (const SCALAR_F k)  const;
    inline void     operator+=  (const Vector3f &v);
    inline void     operator+=  (const SCALAR_F k);
    inline Vector3f operator-   (const Vector3f &v) const;
    inline Vector3f operator-   (const SCALAR_F k)  const;
    inline void     operator-=  (const Vector3f &v);
    inline void     operator-=  (const SCALAR_F k);

    //special function that only subtracts X and Y
    //primarily for use in situations where extra
    //high speed is needed
    inline Vector3f VectorSub2  D (const Vector3f &v);

    //Dot product
    inline SCALAR_F operator* (const Vector3f &v) const;
    inline Vector3f operator^ (const Vector3f v)  const;
    inline SCALAR_F operator% (const Vector3f &v) const;*/

inline Vector3f::Vector3f(const Vector3f &v)
{
    X = v.X;
    Y = v.Y;
    Z = v.Z;
}

inline Vector3f::Vector3f(const SCALAR_F a, const SCALAR_F b, const SCALAR_F c = 0)
{
    X = a;
    Y = b;
    Z = c;
}

inline Vector3f &Vector3f::set(const SCALAR_F &x, const SCALAR_F &y, const SCALAR_F &z = 0)
{
    X = x;
    Y = y;
    Z = z;
    return *this;
}

inline Vector3f &Vector3f::setX(const SCALAR_F &x)
{
    X = x;
}

inline Vector3f &Vector3f::setY(const SCALAR_F &y)
{
    Y = y;
}

inline Vector3f &Vector3f::setZ(const SCALAR_F &z)
{
    Z = z;
}

inline bool Vector3f::operator== (const Vector3f &v)
{
    return (X == v.X && Y == v.Y && Z == v.Z);
}

inline bool Vector3f::operator!= (const Vector3f &v)
{
    return !((*this) == v);
}

inline Vector3f Vector3f::operator-() 
{
    return Vector3f(-X, -Y, -Z);
}

inline Vector3f Vector3f::operator* (const SCALAR_F k) const
{
    return Vector3f(k*X, k*Y, k*Z);
}



inline void Vector3f::operator*= (const SCALAR_F k)
{
    X *= k;
    Y *= k;
    Z *= k;
}

inline Vector3f Vector3f::operator/ (const SCALAR_F k) const
{
    return Vector3f(X / k, Y / k, Z / k);
}

inline void Vector3f::operator/= (const SCALAR_F k)
{
    X /= k;
    Y /= k;
    Z /= k;
}

/*inline Vector3f Vector3f::operator+ (const SCALAR_F k) const
{
    return Vector3f(X + k, Y + k, Z + k);
}*/

inline Vector3f Vector3f::operator+ (const Vector3f &v) const
{
    return Vector3f(X + v.X, Y + v.Y, Z + v.Z);
}

inline void Vector3f::operator+= (const Vector3f &v)
{
    X += v.X;
    Y += v.Y;
    Z += v.Z;
}

/*inline void Vector3f::operator+= (const SCALAR_F k)
{
    X += k;
    Y += k;
    Z += k;
}*/

/*inline Vector3f Vector3f::operator- (const SCALAR_F k) const
{
    return Vector3f(X - k, Y - k, Z - k);
}*/

inline Vector3f Vector3f::operator- (const Vector3f &v) const
{
    return Vector3f(X - v.X, Y - v.Y, Z - v.Z);
}

inline void Vector3f::operator-= (const Vector3f &v)
{
    X -= v.X;
    Y -= v.Y;
    Z -= v.Z;
}

/*inline void Vector3f::operator-= (const SCALAR_F k)
{
    X -= k;
    Y -= k;
    Z -= k;
}*/

inline Vector3f Vector3f::VectorSub2D(const Vector3f &v)
{
    return Vector3f(X - v.X, Y - v.Y);
}

inline SCALAR_F Vector3f::LengthSquared() const
{
    return ((*this) * (*this));
}

inline SCALAR_F Vector3f::Length() const
{
    return SQRT_FUNCTION(LengthSquared());
}

//returns a normal vector without modifying existing vector
inline Vector3f Vector3f::Normal() const
{
    return Vector3f((*this) / Length());
}

inline Vector3f Vector3f::Normalize()
{
    (*this) /= Length();    
    return (*this);
}

inline SCALAR_F Vector3f::operator* (const Vector3f &v) const
{
    return X * v.X + Y * v.Y + Z * v.Z;
}

//3D cross product
inline Vector3f Vector3f::operator^ (const Vector3f v) const
{
    return CrossProduct((*this), v);
}

//2D cross product
inline SCALAR_F Vector3f::operator% (const Vector3f &v) const
{
	return X*v.Y - Y*v.X;
}

};

inline Vector3f operator* (const SCALAR_F k, const Vector3f &v)
{
    return v * k;
}

inline Vector3f operator/ (const SCALAR_F k, const Vector3f &v)
{
    return v / k;
}

inline Vector3f CrossProduct (const Vector3f &v1, const Vector3f &v2)
{
    return Vector3f(v1.Y * v2.Z - v1.Z * v2.Y,
					v2.X * v1.Z - v2.Z * v1.X,
					v1.X * v2.Y - v1.Y * v2.X);
}

inline Vector3f floor(const Vector3f &v)
{
    return Vector3f(FLOOR_FUNCTION(v.X), FLOOR_FUNCTION(v.Y), FLOOR_FUNCTION(v.Z));
}

inline Vector3f ceil(const Vector3f &v)
{
    return Vector3f(CEIL_FUNCTION(v.X), CEIL_FUNCTION(v.Y), CEIL_FUNCTION(v.Z));
}

#endif