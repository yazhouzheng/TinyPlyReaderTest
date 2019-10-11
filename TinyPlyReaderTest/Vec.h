#ifndef _VEC_H_
#define _VEC_H_

template <class T>
union Vec3
{
    struct { T x; T y; T z;};
    struct { T r; T g; T b;};
    T xyz[3];
    T rgb[3];

    Vec3() : x(0), y(0), z(0) {}
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
    Vec3(const Vec3 &u) : x(u.x), y(u.y), z(u.z) {}

    Vec3 operator + (Vec3 &v) { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator - (Vec3 &v) { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator * (float num) { return Vec3(x * num, y * num, z * num); }
    Vec3 operator / (float num) { return Vec3(x / num, y / num, z / num); }

    Vec3 cross(const Vec3 &u, const Vec3 &v) { return Vec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.y, u.x * v.y - u.y * v.x);}

    T dot(const Vec3 &u, const Vec3 &v) { return u.x * v.x + u.y * v.y + u.z * v.z; }

    float dist2(const Vec3 &v) { return (x - v.x) * (x - v.x) + (y - v.y) * (y - v.y) + (z - v.z) * (z - v.z);}

    float dist(const Vec3 &v) { return sqrt(dist2(v)); }
};

template <class T>
union Vec2
{
    struct { T x; T y;};

    Vec2() : x(0), y(0){}
    Vec2(T x, T y, T z) : x(x), y(y){}
    Vec2(const Vec2 &u) : x(u.x), y(u.y){}
};

typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;
typedef Vec2<float> Vec2f;

#endif /*_VEC_H_*/