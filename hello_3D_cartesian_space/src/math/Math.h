#pragma once
#include <cmath>

// Minimal vector/matrix types and builders (column-major, OpenGL style)

struct Vec3 { float x=0, y=0, z=0; };
struct Vec4 { float x=0, y=0, z=0, w=0; };

struct Mat4 {
    float m[16]{}; // column-major: m[col*4 + row]

    float& operator()(int i, int j)       { return m[j*4 + i]; }
    float  operator()(int i, int j) const { return m[j*4 + i]; }

    static Mat4 identity() {
        Mat4 r{};
        r(0,0)=1; r(1,1)=1; r(2,2)=1; r(3,3)=1;
        return r;
    }
};

inline Mat4 operator*(const Mat4& A, const Mat4& B) {
    Mat4 C{};
    for (int i=0;i<4;++i)
        for (int j=0;j<4;++j) {
            float s=0.0f;
            for (int k=0;k<4;++k) s += A(i,k)*B(k,j);
            C(i,j)=s;
        }
    return C;
}

inline Vec4 mul(const Mat4& A, const Vec4& v) {
    Vec4 r{};
    r.x = A(0,0)*v.x + A(0,1)*v.y + A(0,2)*v.z + A(0,3)*v.w;
    r.y = A(1,0)*v.x + A(1,1)*v.y + A(1,2)*v.z + A(1,3)*v.w;
    r.z = A(2,0)*v.x + A(2,1)*v.y + A(2,2)*v.z + A(2,3)*v.w;
    r.w = A(3,0)*v.x + A(3,1)*v.y + A(3,2)*v.z + A(3,3)*v.w;
    return r;
}

inline Mat4 translate(float x, float y, float z) {
    Mat4 T = Mat4::identity();
    T(0,3)=x; T(1,3)=y; T(2,3)=z;
    return T;
}

inline Mat4 scale(float x, float y, float z) {
    Mat4 S{};
    S(0,0)=x; S(1,1)=y; S(2,2)=z; S(3,3)=1;
    return S;
}

inline Mat4 rotateAxis(float angleRad, float ax, float ay, float az) {
    float len = std::sqrt(ax*ax + ay*ay + az*az);
    if (len == 0) return Mat4::identity();
    ax/=len; ay/=len; az/=len;
    float c = std::cos(angleRad), s = std::sin(angleRad), t = 1.0f - c;
    Mat4 R = Mat4::identity();
    R(0,0)=t*ax*ax+c;     R(0,1)=t*ax*ay - s*az; R(0,2)=t*ax*az + s*ay;
    R(1,0)=t*ay*ax + s*az; R(1,1)=t*ay*ay + c;   R(1,2)=t*ay*az - s*ax;
    R(2,0)=t*az*ax - s*ay; R(2,1)=t*az*ay + s*ax; R(2,2)=t*az*az + c;
    return R;
}

inline Mat4 perspective(float fovRadians, float aspect, float znear, float zfar) {
    Mat4 P{};
    float f = 1.0f / std::tan(fovRadians * 0.5f);
    P(0,0) = f / aspect;
    P(1,1) = f;
    P(2,2) = (zfar + znear) / (znear - zfar);
    P(2,3) = (2.0f * zfar * znear) / (znear - zfar);
    P(3,2) = -1.0f;
    return P;
}

inline Mat4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up) {
    auto normalize = [](Vec3 v){
        float l = std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
        if (l > 1e-8f) { v.x/=l; v.y/=l; v.z/=l; }
        return v;
    };
    auto cross = [](const Vec3& a, const Vec3& b){
        return Vec3{ a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x };
    };
    auto sub = [](const Vec3& a, const Vec3& b){
        return Vec3{ a.x-b.x, a.y-b.y, a.z-b.z };
    };

    Vec3 fwd = normalize(sub(center, eye));
    Vec3 s = normalize(cross(fwd, up));
    Vec3 u = cross(s, fwd);

    Mat4 V = Mat4::identity();
    V(0,0)= s.x; V(1,0)= s.y; V(2,0)= s.z;
    V(0,1)= u.x; V(1,1)= u.y; V(2,1)= u.z;
    V(0,2)=-fwd.x; V(1,2)=-fwd.y; V(2,2)=-fwd.z;
    V(0,3)= -(s.x*eye.x + s.y*eye.y + s.z*eye.z);
    V(1,3)= -(u.x*eye.x + u.y*eye.y + u.z*eye.z);
    V(2,3)= -(-fwd.x*eye.x + -fwd.y*eye.y + -fwd.z*eye.z);
    return V;
}
