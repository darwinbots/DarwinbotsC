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
    return VECTOR(X / k, Y / k, Z / k);
}

inline void VECTOR::operator/= (const SCALAR k)
{
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
    return VECTOR((*this) / Length());
}

inline VECTOR VECTOR::Normalize()
{
    (*this) /= Length();    
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
