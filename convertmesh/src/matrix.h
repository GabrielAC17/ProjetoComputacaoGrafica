/*-----------------------------------------------------------------------------
   MATRIX.H - Matrix related classes (Header File)
   
Compiler: Visual C++ 6.0

History:
1) 21-Nov-2001 (Vrubel) - Initial implementation
-----------------------------------------------------------------------------*/
#ifndef _MATRIX_H
#define _MATRIX_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "types.h"
#include "error.h"

#ifdef WIN32
#pragma warning(disable:4514)
#endif

/*-----------------------------------------------------------------------------
                                   Constants
-----------------------------------------------------------------------------*/
// math constants 
#define MIN_FLOAT                      0.00001f
#define MAX_FLOAT                      1.0e37f
#define PI                             3.14159265f
#define TWO_PI                         (2.0f*PI)
#define DEG2RAD(x)                     ((x)*PI/180.0f)
#define RAD2DEG(x)                     ((x)*180.0f/PI)

// interpolation types
#define I_LINEAR                       0
#define I_SIN                          1
#define I_SLOWEST                      2
#define I_SLOW                         3
#define I_FAST                         4
#define I_FASTEST                      5


/*-----------------------------------------------------------------------------
                              Forward References
-----------------------------------------------------------------------------*/
class cPoint3;
class cQuat;
class cBoundBox3;
class cProjection;


/*-----------------------------------------------------------------------------
                                   cMatrix3
-----------------------------------------------------------------------------*/
// class to hold a 3D transform matrix (4x3)
class cMatrix3 {
public:
   float m[4][3];                      // matrix elements

public:
        cMatrix3(void);
        cMatrix3(int type);
   void zero(void);
   void identity(void);
   void getRow(int row, float *v);
   void getRow(int row, cPoint3 &p);
   void setRow(int row, float v1, float v2, float v3);
   void setRow(int row, const cPoint3 &p);
   void setTrans(float tx, float ty, float tz);
   void setTrans(const cPoint3 &p);
   void setRotationX(float angle);
   void setRotationY(float angle);
   void setRotationZ(float angle);
   void setScale(float s);
   void scale(float s);
   void scale(float sx, float sy, float sz);
   void scaleX(float s);
   void scaleY(float s);
   void scaleZ(float s);
   void rotateX(float angle);
   void rotateY(float angle);
   void rotateZ(float angle);
   void rotateQuat(float *q);
   void rotateQuat(cQuat &q);
   void translate(float dx, float dy, float dz);
   void translate(const cPoint3 &p);
   void translateX(float delta);
   void translateY(float delta);
   void translateZ(float delta);
   void preScale(float s);
   void preScale(float sx, float sy, float sz);
   void preScaleX(float s);
   void preScaleY(float s);
   void preScaleZ(float s);
   void preRotateX(float angle);
   void preRotateY(float angle);
   void preRotateZ(float angle);
   void preRotateQuat(float *q);
   void preRotateQuat(cQuat &q);
   void preTranslate(float dx, float dy, float dz);
   void preTranslate(const cPoint3 &p);
   void preTranslateX(float delta);
   void preTranslateY(float delta);
   void preTranslateZ(float delta);
   cMatrix3 operator*(const cMatrix3 &parm);
   cMatrix3 operator+(const cMatrix3 &parm);
   cMatrix3 &operator+=(const cMatrix3 &other);
   cMatrix3 inverse(void);
   void glMatrix(float *data);
   void getEulerZYX(float *rx, float *ry, float *rz);
   };


/*-----------------------------------------------------------------------------
                                  cMatrix3r
-----------------------------------------------------------------------------*/
// class to hold a 3D rotation matrix (3x3)
class cMatrix3r {
public:
   float m[3][3];                      // matrix elements

public:
        cMatrix3r(void);
        cMatrix3r(int type);
   void zero(void);
   void identity(void);
   void getRow(int row, float *v);
   void getRow(int row, cPoint3 &p);
   void setRow(int row, float v1, float v2, float v3);
   void setRow(int row, const cPoint3 &p);
   void setRotationX(float angle);
   void setRotationY(float angle);
   void setRotationZ(float angle);
   void rotateX(float angle);
   void rotateY(float angle);
   void rotateZ(float angle);
   void rotateQuat(cQuat &q);
   void preRotateX(float angle);
   void preRotateY(float angle);
   void preRotateZ(float angle);
   void preRotateQuat(cQuat &q);
   cMatrix3r operator*(const cMatrix3r &parm);
   cMatrix3r inverse(void);
   void removeInaccuracy(void);
   };


/*-----------------------------------------------------------------------------
                                   cPoint3
-----------------------------------------------------------------------------*/
// class to hold a 3D homogeneus point
class cPoint3 {
public:
   float x;                            // coordinate x of the point or vector
   float y;                            // coordinate y of the point or vector
   float z;                            // coordinate z of the point or vector

public:
         cPoint3(void);
         cPoint3(int type);
         cPoint3(float xP, float yP, float zP);
   void  zero(void);
   void  set(float xP, float yP, float zP);
   float length(void);
   float squaredLength(void);
   cPoint3 normalize(void);
   cPoint3 operator-(void);
   cPoint3 operator-(const cPoint3 &other);
   cPoint3 operator+(const cPoint3 &other);
   cPoint3 operator^(const cPoint3 &other);
   cPoint3 operator*(const cPoint3 &other);
   cPoint3 operator*(float value);
   cPoint3 &operator-=(const cPoint3 &other);
   cPoint3 &operator+=(const cPoint3 &other);
   cPoint3 operator*(const cMatrix3 &tm);
   cPoint3 operator*(const cMatrix3r &tm);
   cQuat   operator*(const cQuat &q);
   };


/*-----------------------------------------------------------------------------
                                     cQuat
-----------------------------------------------------------------------------*/
// class to hold a quaternion 
class cQuat {
public:
   float   s;                          // scalar part = cos(theta/2)
   cPoint3 v;                          // imaginary vector = sin(theta/2)*v

public:
         cQuat(void);
         cQuat(int type);
         cQuat(float sP, float xP, float yP, float zP);
         cQuat(const cMatrix3 &parm);
         cQuat(const cMatrix3r &parm);
   void  zero(void);
   void  identity(void);
   float length(void);
   float squaredLength(void);
   cQuat normalize(void);
   cQuat operator+(const cQuat &other);
   cQuat operator-(const cQuat &other);
   cQuat operator*(float value);
   cQuat operator*(const cQuat &other);
   cQuat operator*(const cPoint3 &other);
   void  setRotationX(float angle);
   void  setRotationY(float angle);
   void  setRotationZ(float angle);
   void  rotateX(float angle);
   void  rotateY(float angle);
   void  rotateZ(float angle);
   void  preRotateX(float angle);
   void  preRotateY(float angle);
   void  preRotateZ(float angle);
   cMatrix3  matrix3(void);
   cMatrix3r matrix3r(void);
   void  glMatrix(float *data);
   };


/*-----------------------------------------------------------------------------
                                   cBoundBox3
-----------------------------------------------------------------------------*/
// class to hold a world aligned bounding box
class cBoundBox3 {
public:
   cPoint3 pMin;                       // point with minimum coordinates
   cPoint3 pMax;                       // point with maximum coordinates

public:
        cBoundBox3(void);
   void reset(void);
   int  contains(const cPoint3 &p);
   void add(const cPoint3 &p);
   };


/*-----------------------------------------------------------------------------
                                  cProjection
-----------------------------------------------------------------------------*/
// class to manage projection matrices 
class cProjection {
public:
   float proj[4][4];                   // projection matrix
   float viewProj[4][4];               // transpose composite view-projection matrix
   float wP;                           // w parameter of projection matrix
   float hP;                           // h parameter of projection matrix
   float Q;                            // Q parameter of projection matrix
   float zNear;                        // Z of the near plane of the frustrum
   float zFar;                         // Z of the far plane of the frustrum
   float fovW;                         // half of the horizontal Field Of View (radians)
   float fovH;                         // half of the vertical Field Of View (radians)
   float tanFovW;                      // tangent of fovW
   float tanFovH;                      // tangent of fovH

public:
        cProjection(void);
   void set(float viewW, float viewH, float pixelAspect, float fovParm, float zNearParm, float zFarParm);
   void generateMatrix(const cMatrix3 &tm);
   cPoint3 projectPoint(const cPoint3 &p);
   };


/*-----------------------------------------------------------------------------
                         Auxiliary Function Prototypes
-----------------------------------------------------------------------------*/
// auxiliary structures
// parameters for a 6x6 (or less) Jacobi eigenvector finder
typedef struct {
   float a[6][6];                      // matrix to solve eigensystems
   float d[6];                         // eigenvalues
   float v[6][6];                      // eigenvectors (in each column)
   int   nRot;                         // number of rotations required
   int   dim;                          // dimension of the matrices (maximum of 6)
   } tJacobiParm;

// function prototypes
float     dotProduct(const cPoint3 &p1, const cPoint3 &p2);
cPoint3   crossProduct(const cPoint3 &p1, const cPoint3 &p2);
cMatrix3  mFromQuat(float *q);
cPoint3   normalRotate(const cPoint3 &n, const cMatrix3 &tm);
cMatrix3r transpose(const cMatrix3r &tm);
cQuat     normalize(cQuat &q);
float     arctan2(float dx, float dy);
float     fAbs(float value);
float     interpolate(int type, float iniVal, float endVal, dword startTime, dword duration, dword msTime);
float     interpolate(int type, float iniVal, float endVal, float t);
int       solveJacobi(tJacobiParm *parm);


/*-----------------------------------------------------------------------------
                          Inline: cMatrix3::cMatrix3()
-----------------------------------------------------------------------------*/
inline cMatrix3::cMatrix3(void)
{
// initializes as a null matrix
memset(m, 0, sizeof(m));
}
/*-----------------------------------------------------------------------------
                          Inline: cMatrix3::cMatrix3()
-----------------------------------------------------------------------------*/
inline cMatrix3::cMatrix3(int type)
{
switch( type ) {
case 0:
   // initializes as a null matrix
   memset(m, 0, sizeof(m));
   break;
case 1:
   // initializes as a identity matrix 
   this->identity();
   break;
default:
   // do not initialize - used when the matrix will be set to other values 
   break;
   }
}
/*-----------------------------------------------------------------------------
                           Inline: cMatrix3::zero()
-----------------------------------------------------------------------------*/
inline void cMatrix3::zero(void)
{
// initializes as a null matrix 
memset(m, 0, sizeof(m));
}
/*-----------------------------------------------------------------------------
                         Inline: cMatrix3::identity()
-----------------------------------------------------------------------------*/
inline void cMatrix3::identity(void)
{
// initializes as a identity matrix 
memset(m, 0, sizeof(m));
m[0][0] = 1.0f;
m[1][1] = 1.0f;
m[2][2] = 1.0f;
}
/*-----------------------------------------------------------------------------
                          Inline: cMatrix3::getRow()
-----------------------------------------------------------------------------*/
inline void cMatrix3::getRow(int row, float *v)
{
// get the specified row 
v[0] = m[row][0];
v[1] = m[row][1];
v[2] = m[row][2];
}
/*-----------------------------------------------------------------------------
                          Inline: cMatrix3::getRow()
-----------------------------------------------------------------------------*/
inline void cMatrix3::getRow(int row, cPoint3 &p)
{
// get the specified row 
p.x = m[row][0];
p.y = m[row][1];
p.z = m[row][2];
}
/*-----------------------------------------------------------------------------
                          Inline: cMatrix3::setRow()
-----------------------------------------------------------------------------*/
inline void cMatrix3::setRow(int row, float v1, float v2, float v3)
{
// fill the specified row 
m[row][0] = v1;
m[row][1] = v2;
m[row][2] = v3;
}
/*-----------------------------------------------------------------------------
                          Inline: cMatrix3::setRow()
-----------------------------------------------------------------------------*/
inline void cMatrix3::setRow(int row, const cPoint3 &p)
{
// fill the specified row 
m[row][0] = p.x;
m[row][1] = p.y;
m[row][2] = p.z;
}
/*-----------------------------------------------------------------------------
                         Inline: cMatrix3::setTrans()
-----------------------------------------------------------------------------*/
inline void cMatrix3::setTrans(float tx, float ty, float tz)
{
// fill the translation row of the matrix 
this->setRow(3,tx,ty,tz);
}
/*-----------------------------------------------------------------------------
                         Inline: cMatrix3::setTrans()
-----------------------------------------------------------------------------*/
inline void cMatrix3::setTrans(const cPoint3 &p)
{
// fill the translation row of the matrix 
this->setRow(3,p);
}
/*-----------------------------------------------------------------------------
                          Inline: cMatrix3::scale()
-----------------------------------------------------------------------------*/
inline void cMatrix3::scale(float s)
{
// uniform scale the matrix 
this->scale(s,s,s);
}
/*-----------------------------------------------------------------------------
                         Inline: cMatrix3::preScale()
-----------------------------------------------------------------------------*/
inline void cMatrix3::preScale(float s)
{
// uniform pre-scale the matrix 
this->preScale(s,s,s);
}
/*-----------------------------------------------------------------------------
                             cMatrix3::translateX()
-----------------------------------------------------------------------------*/
inline void cMatrix3::translateX(float delta)
{
// adjust the translation row 
m[3][0] += delta;
}
/*-----------------------------------------------------------------------------
                             cMatrix3::translateY()
-----------------------------------------------------------------------------*/
inline void cMatrix3::translateY(float delta)
{
// adjust the translation row 
m[3][1] += delta;
}
/*-----------------------------------------------------------------------------
                             cMatrix3::translateZ()
-----------------------------------------------------------------------------*/
inline void cMatrix3::translateZ(float delta)
{
// adjust the translation row 
m[3][2] += delta;
}
/*-----------------------------------------------------------------------------
                          Inline: cMatrix3r::cMatrix3r()
-----------------------------------------------------------------------------*/
inline cMatrix3r::cMatrix3r(void)
{
// initializes as a null matrix
memset(m, 0, sizeof(m));
}
/*-----------------------------------------------------------------------------
                          Inline: cMatrix3r::cMatrix3r()
-----------------------------------------------------------------------------*/
inline cMatrix3r::cMatrix3r(int type)
{
switch( type ) {
case 0:
   // initializes as a null matrix
   memset(m, 0, sizeof(m));
   break;
case 1:
   // initializes as a identity matrix 
   this->identity();
   break;
default:
   // do not initialize - used when the matrix will be set to other values 
   break;
   }
}
/*-----------------------------------------------------------------------------
                           Inline: cMatrix3r::zero()
-----------------------------------------------------------------------------*/
inline void cMatrix3r::zero(void)
{
// initializes as a null matrix 
memset(m, 0, sizeof(m));
}
/*-----------------------------------------------------------------------------
                         Inline: cMatrix3r::identity()
-----------------------------------------------------------------------------*/
inline void cMatrix3r::identity(void)
{
// initializes as a identity matrix 
memset(m, 0, sizeof(m));
m[0][0] = 1.0f;
m[1][1] = 1.0f;
m[2][2] = 1.0f;
}
/*-----------------------------------------------------------------------------
                          Inline: cMatrix3r::getRow()
-----------------------------------------------------------------------------*/
inline void cMatrix3r::getRow(int row, float *v)
{
// get the specified row 
v[0] = m[row][0];
v[1] = m[row][1];
v[2] = m[row][2];
}
/*-----------------------------------------------------------------------------
                          Inline: cMatrix3r::getRow()
-----------------------------------------------------------------------------*/
inline void cMatrix3r::getRow(int row, cPoint3 &p)
{
// get the specified row 
p.x = m[row][0];
p.y = m[row][1];
p.z = m[row][2];
}
/*-----------------------------------------------------------------------------
                          Inline: cMatrix3r::setRow()
-----------------------------------------------------------------------------*/
inline void cMatrix3r::setRow(int row, float v1, float v2, float v3)
{
// fill the specified row 
m[row][0] = v1;
m[row][1] = v2;
m[row][2] = v3;
}
/*-----------------------------------------------------------------------------
                          Inline: cMatrix3r::setRow()
-----------------------------------------------------------------------------*/
inline void cMatrix3r::setRow(int row, const cPoint3 &p)
{
// fill the specified row 
m[row][0] = p.x;
m[row][1] = p.y;
m[row][2] = p.z;
}
/*-----------------------------------------------------------------------------
                          Inline: cPoint3::cPoint3()
-----------------------------------------------------------------------------*/
inline cPoint3::cPoint3(void)
{
// initializes at the origin 
x = 0.0f;
y = 0.0f;
z = 0.0f;
}
/*-----------------------------------------------------------------------------
                          Inline: cPoint3::cPoint3()
-----------------------------------------------------------------------------*/
inline cPoint3::cPoint3(int type)
{
switch( type ) {
case 0:
   // initializes at the origin 
   x = 0.0f;
   y = 0.0f;
   z = 0.0f;
   break;
default:
   // do not initialize - used when the point will be set to other values 
   break;
   }
}
/*-----------------------------------------------------------------------------
                          Inline: cPoint3::cPoint3()
-----------------------------------------------------------------------------*/
inline cPoint3::cPoint3(float xP, float yP, float zP)
{
// initializes with the specified coordinates 
x = xP;
y = yP;
z = zP;
}
/*-----------------------------------------------------------------------------
                            Inline: cPoint3::zero()
-----------------------------------------------------------------------------*/
inline void cPoint3::zero(void)
{
// put it at the origin 
x = 0.0f;
y = 0.0f;
z = 0.0f;
}
/*-----------------------------------------------------------------------------
                            Inline: cPoint3::set()
-----------------------------------------------------------------------------*/
inline void cPoint3::set(float xP, float yP, float zP)
{
// initializes with the specified coordinates 
x = xP;
y = yP;
z = zP;
}
/*-----------------------------------------------------------------------------
                           Inline: cPoint3::length()
-----------------------------------------------------------------------------*/
inline float cPoint3::length(void)
{
// return the length of the vetor 
return (float)sqrt(x*x + y*y + z*z);
}
/*-----------------------------------------------------------------------------
                        Inline: cPoint3::squaredLength()
-----------------------------------------------------------------------------*/
inline float cPoint3::squaredLength(void)
{
// return the squared length of the vetor 
return (x*x + y*y + z*z);
}
/*-----------------------------------------------------------------------------
                          Inline: cPoint3::operator-()
-----------------------------------------------------------------------------*/
inline cPoint3 cPoint3::operator-(void)
{
return cPoint3(-x,-y,-z);
}
/*-----------------------------------------------------------------------------
                          Inline: cPoint3::operator-()
-----------------------------------------------------------------------------*/
inline cPoint3 cPoint3::operator-(const cPoint3 &other)
{
return cPoint3(x-other.x, y-other.y, z-other.z);
}
/*-----------------------------------------------------------------------------
                          Inline: cPoint3::operator+()
-----------------------------------------------------------------------------*/
inline cPoint3 cPoint3::operator+(const cPoint3 &other)
{
	//if (other.x != other.x || other.y != other.y || other.z != other.z)
	//	printf("erro\n");
return cPoint3(x+other.x, y+other.y, z+other.z);
}
/*-----------------------------------------------------------------------------
                          Inline: cPoint3::operator^()
-----------------------------------------------------------------------------*/
inline cPoint3 cPoint3::operator^(const cPoint3 &other)
{
// calculate the cross product of the two vectors 
return crossProduct(*this, other);
}
/*-----------------------------------------------------------------------------
                          Inline: cPoint3::operator*()
-----------------------------------------------------------------------------*/
inline cPoint3 cPoint3::operator*(float value)
{
return cPoint3(x*value, y*value, z*value);
}
/*-----------------------------------------------------------------------------
                          Inline: cPoint3::operator*()
-----------------------------------------------------------------------------*/
inline cPoint3 cPoint3::operator*(const cPoint3 &other)
{
return cPoint3(x*other.x, y*other.y, z*other.z);
}
/*-----------------------------------------------------------------------------
                         Inline: cPoint3::operator-=()
-----------------------------------------------------------------------------*/
inline cPoint3 &cPoint3::operator-=(const cPoint3 &other)
{
x -= other.x;
y -= other.y;
z -= other.z;

return (*this);
}
/*-----------------------------------------------------------------------------
                         Inline: cPoint3::operator+=()
-----------------------------------------------------------------------------*/
inline cPoint3 &cPoint3::operator+=(const cPoint3 &other)
{
x += other.x;
y += other.y;
z += other.z;

return (*this);
}
/*-----------------------------------------------------------------------------
                             Inline: cQuat::cQuat()
-----------------------------------------------------------------------------*/
inline cQuat::cQuat(void)
{
// initialize members
s = 1.0f;
v.zero();
}
/*-----------------------------------------------------------------------------
                             Inline: cQuat::cQuat()
-----------------------------------------------------------------------------*/
inline cQuat::cQuat(int type)
{
switch( type ) {
case 0:
   // null quaternion
   s = 0.0f;
   v.zero();
   break;
case 1:
   // identity quaternion
   s = 1.0f;
   v.zero();
   break;
default:
   // do not initialize - used when the quaternion will be set to other values 
   break;
   }
}
/*-----------------------------------------------------------------------------
                             Inline: cQuat::cQuat()
-----------------------------------------------------------------------------*/
inline cQuat::cQuat(float sP, float xP, float yP, float zP)
{
// initialize members
s   = sP;
v.x = xP;
v.y = yP;
v.z = zP;
}
/*-----------------------------------------------------------------------------
                             Inline: cQuat::zero()
-----------------------------------------------------------------------------*/
inline void cQuat::zero(void)
{
// null quaternion 
s = 0.0f;
v.zero();
}
/*-----------------------------------------------------------------------------
                           Inline: cQuat::identity()
-----------------------------------------------------------------------------*/
inline void cQuat::identity(void)
{
// identity quaternion 
s = 1.0f;
v.zero();
}
/*-----------------------------------------------------------------------------
                            Inline: cQuat::length()
-----------------------------------------------------------------------------*/
inline float cQuat::length(void)
{
// quaternion length
return (float)sqrt(s*s + v.x*v.x + v.y*v.y + v.z*v.z);
}
/*-----------------------------------------------------------------------------
                         Inline: cQuat::squaredLength()
-----------------------------------------------------------------------------*/
inline float cQuat::squaredLength(void)
{
// quaternion squared length
return (float)(s*s + v.x*v.x + v.y*v.y + v.z*v.z);
}
/*-----------------------------------------------------------------------------
                           Inline: cQuat::operator+()
-----------------------------------------------------------------------------*/
inline cQuat cQuat::operator+(const cQuat &other)
{
return cQuat(s+other.s, v.x+other.v.x, v.y+other.v.y, v.z+other.v.z);
}
/*-----------------------------------------------------------------------------
                           Inline: cQuat::operator-()
-----------------------------------------------------------------------------*/
inline cQuat cQuat::operator-(const cQuat &other)
{
return cQuat(s-other.s, v.x-other.v.x, v.y-other.v.y, v.z-other.v.z);
}
/*-----------------------------------------------------------------------------
                           Inline: cQuat::operator*()
-----------------------------------------------------------------------------*/
inline cQuat cQuat::operator*(float value)
{
return cQuat(s*value, v.x*value, v.y*value, v.z*value);
}
/*-----------------------------------------------------------------------------
                         Inline: cBoundBox3::cBoundBox3()
-----------------------------------------------------------------------------*/
inline cBoundBox3::cBoundBox3(void)
{
// initializes with a null box 
this->reset();
}
/*-----------------------------------------------------------------------------
                           Inline: cBoundBox3::reset()
-----------------------------------------------------------------------------*/
inline void cBoundBox3::reset(void)
{
// initializes with a null box 
pMin.set(MAX_FLOAT, MAX_FLOAT, MAX_FLOAT);
pMax.set(-MAX_FLOAT, -MAX_FLOAT, -MAX_FLOAT);
}
/*-----------------------------------------------------------------------------
                          Inline: cBoundBox3::contains()
-----------------------------------------------------------------------------*/
inline int cBoundBox3::contains(const cPoint3 &p)
{
// check if a point is inside a bounding box 
return ( (p.x >= pMin.x) && (p.x <= pMax.x) &&
         (p.y >= pMin.y) && (p.y <= pMax.y) &&
         (p.z >= pMin.z) && (p.z <= pMax.z) );
}
/*-----------------------------------------------------------------------------
                            Inline: cBoundBox3::add()
-----------------------------------------------------------------------------*/
inline void cBoundBox3::add(const cPoint3 &p)
{
// add a point to a bounding box 
if( pMin.x > p.x )
   pMin.x = p.x;
if( pMin.y > p.y )
   pMin.y = p.y;
if( pMin.z > p.z )
   pMin.z = p.z;
if( pMax.x < p.x )
   pMax.x = p.x;
if( pMax.y < p.y )
   pMax.y = p.y;
if( pMax.z < p.z )
   pMax.z = p.z;
}
/*-----------------------------------------------------------------------------
                      Inline: cProjection::cProjection()
-----------------------------------------------------------------------------*/
inline cProjection::cProjection(void)
{
// initialize projection matrix parameters (ZNear=1.0, ZFar=500.0) 
fovW    = DEG2RAD(45.0f);
fovH    = DEG2RAD(36.87f);
tanFovW = 1.0f;
tanFovH = 0.75f;
wP      = 1.0f;
hP      = 4.0f / 3.0f;
Q       = 500.0f / 499.0f;
zNear   = 1.0f;
zFar    = 500.0f;
this->generateMatrix(cMatrix3(1));
}
/*-----------------------------------------------------------------------------
                              Inline: dotProduct()
-----------------------------------------------------------------------------*/
inline float dotProduct(const cPoint3 &p1, const cPoint3 &p2)
{
// return the dot product of two vectors: |p1|.|p2|.cos(angle) 
return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}
/*-----------------------------------------------------------------------------
                                 Inline: fAbs()
-----------------------------------------------------------------------------*/
inline float fAbs(float value)
{
// return the absolute of the float value
return (value < 0.0f) ? -value : value;
}

inline bool isNan( float value ) { return ((*(dword*)&value) & 0x7fffffff) > 0x7f800000; } 


#endif
