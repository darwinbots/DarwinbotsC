/**********************************************************************
This is a "raw" include.  Vectors.h contains the pre-processor
directives necessary to allow this to compile.  The idea is that
the vector implementation has been abstracted away from what SCALAR
you're using and what you're calling the vector class.

This is probably similar to a template, but MSVC templates and inlining
together cause all sorts of headache.  I'm saving myself the effort and
using old school C pre processor directives to take care of it.
************************************************************************/

#include <assert.h>

#define VECTORNAME #VECTOR \

class VECTOR
{
    friend inline VECTOR floor(const VECTOR &v);
    friend inline VECTOR ceil(const VECTOR &v);
    friend inline VECTOR CrossProduct (const VECTOR &v1, const VECTOR &v2);
    
    private:
    
    //provide 2 different ways to access the same element 
    static union
    {   
	    struct
	    {
		    SCALAR X;
		    SCALAR Y;
		    SCALAR Z;
	    };	
	    SCALAR e[3];
    };

    public:

VECTOR (void)
{

};
	
// [] is to read, () is to write (const correctness)
//bounds are not checked
inline const SCALAR &operator[] (int i) const
{
    return e[i];
}

inline SCALAR &operator() (int i)
{
    return e[i];
}

inline const SCALAR &x(void) const
{
    return X;
}

inline const SCALAR &y(void) const
{
    return Y;
}

inline const SCALAR &z(void) const
{
    return Z;
}	

// Provides access to the underlying array; useful for passing this class off to C APIs
inline const SCALAR *readArray(void)
{
    return e;
}

inline SCALAR *getArray(void)
{
    return e;
}

inline VECTOR::VECTOR(const VECTOR &v)
{
    X = v.X;
    Y = v.Y;
    Z = v.Z;
}

inline VECTOR::VECTOR(const SCALAR a, const SCALAR b, const SCALAR c = 0)
{
    X = a;
    Y = b;
    Z = c;
}

inline VECTOR &VECTOR::set(const SCALAR &x, const SCALAR &y, const SCALAR &z = 0)
{
    X = x;
    Y = y;
    Z = z;
    return *this;
}

inline VECTOR &VECTOR::setX(const SCALAR &x)
{
    X = x;
    return (*this);
}

inline VECTOR &VECTOR::setY(const SCALAR &y)
{
    Y = y;
    return (*this);
}

inline VECTOR &VECTOR::setZ(const SCALAR &z)
{
    Z = z;
    return (*this);
}

inline bool VECTOR::operator== (const VECTOR &v)
{
    return (X == v.X && Y == v.Y && Z == v.Z);
}

inline bool VECTOR::operator!= (const VECTOR &v)
{
    return !((*this) == v);
}

inline VECTOR VECTOR::operator-() 
{
    return VECTOR(-X, -Y, -Z);
}

inline VECTOR VECTOR::operator* (const SCALAR k) const
{
    return VECTOR(k*X, k*Y, k*Z);
}



inline void VECTOR::operator*= (const SCALAR k)
{
    X *= k;
    Y *= k;
    Z *= k;
}

inline VECTOR VECTOR::operator/ (const SCALAR k) const
{
    assert(k != 0 && "Attempting to divide by 0 in VECTOR::operator /");
    return VECTOR(X / k, Y / k, Z / k);
}

inline void VECTOR::operator/= (const SCALAR k)
{
    assert(k != 0 && "Attempting to divide by 0 in VECTOR::operator /=");
    X /= k;
    Y /= k;
    Z /= k;
}

inline VECTOR VECTOR::operator+ (const VECTOR &v) const
{
    return VECTOR(X + v.X, Y + v.Y, Z + v.Z);
}

inline void VECTOR::operator+= (const VECTOR &v)
{
    X += v.X;
    Y += v.Y;
    Z += v.Z;
}

inline VECTOR VECTOR::operator- (const VECTOR &v) const
{
    return VECTOR(X - v.X, Y - v.Y, Z - v.Z);
}

inline void VECTOR::operator-= (const VECTOR &v)
{
    X -= v.X;
    Y -= v.Y;
    Z -= v.Z;
}

inline VECTOR VECTOR::VectorSub2D(const VECTOR &v)
{
    return VECTOR(X - v.X, Y - v.Y);
}

inline SCALAR VECTOR::LengthSquared() const
{
    return ((*this) * (*this));
}

inline SCALAR VECTOR::Length() const
{
    return SQRT(LengthSquared());
}

//returns a normal vector without modifying existing vector
inline VECTOR VECTOR::Normal() const
{
    SCALAR length = Length();
    assert(length != 0 && "Attempting to Normalize a 0 length vector in VECTOR::Normal()" );
    return VECTOR((*this) / length);
}

inline VECTOR VECTOR::Normalize()
{
    SCALAR length = Length();
    assert(length != 0 && "Attempting to Normalize a 0 length vector in VECTOR::Normalize()" );
    (*this) /= length;    
    return (*this);
}

inline SCALAR VECTOR::operator* (const VECTOR &v) const
{
    return X * v.X + Y * v.Y + Z * v.Z;
}

//3D cross product
inline VECTOR VECTOR::operator^ (const VECTOR v) const
{
    return CrossProduct((*this), v);
}

//2D cross product
inline SCALAR VECTOR::operator% (const VECTOR &v) const
{
	return X*v.Y - Y*v.X;
}

};

inline VECTOR operator* (const SCALAR k, const VECTOR &v)
{
    return v * k;
}

inline VECTOR operator/ (const SCALAR k, const VECTOR &v)
{
    assert(k != 0 && "Attempting to divide by 0 in VECTOR, non-internal operator/");
    return v / k;
}

inline VECTOR CrossProduct (const VECTOR &v1, const VECTOR &v2)
{
    return VECTOR(v1.Y * v2.Z - v1.Z * v2.Y,
					v2.X * v1.Z - v2.Z * v1.X,
					v1.X * v2.Y - v1.Y * v2.X);
}

inline VECTOR floor(const VECTOR &v)
{
    return VECTOR(FLOOR(v.X), FLOOR(v.Y), FLOOR(v.Z));
}

inline VECTOR ceil(const VECTOR &v)
{
    return VECTOR(CEIL(v.X), CEIL(v.Y), CEIL(v.Z));
}
