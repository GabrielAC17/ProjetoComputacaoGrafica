/*-----------------------------------------------------------------------------
   MATRIX.CPP - Matrix related functions
   
Compiler: Visual C++ 6.0

History:
1) 21-Nov-2001 (Vrubel) - Initial implementation
-----------------------------------------------------------------------------*/
#include "matrix.h"

/*-----------------------------------------------------------------------------
                           cMatrix3::setRotationX()
-----------------------------------------------------------------------------*/
void cMatrix3::setRotationX(float angle)
{
// build a rotation matrix about the X-axis 
m[0][0] = 1.0f;
m[0][1] = 0.0f;
m[0][2] = 0.0f;
m[1][0] = 0.0f;
m[1][1] = (float)cos(angle);
m[1][2] = (float)sin(angle);
m[2][0] = 0.0f;
m[2][1] = -m[1][2];
m[2][2] = m[1][1];
}
/*-----------------------------------------------------------------------------
                           cMatrix3::setRotationY()
-----------------------------------------------------------------------------*/
void cMatrix3::setRotationY(float angle)
{
// build a rotation matrix about the Y-axis 
m[0][0] = (float)cos(angle);
m[0][1] = 0.0f;
m[0][2] = (float)-sin(angle);
m[1][0] = 0.0f;
m[1][1] = 1.0f;
m[1][2] = 0.0f;
m[2][0] = -m[0][2];
m[2][1] = 0.0f;
m[2][2] = m[0][0];
}
/*-----------------------------------------------------------------------------
                           cMatrix3::setRotationZ()
-----------------------------------------------------------------------------*/
void cMatrix3::setRotationZ(float angle)
{
// build a rotation matrix about the Z-axis 
m[0][0] = (float)cos(angle);
m[0][1] = (float)sin(angle);
m[0][2] = 0.0f;
m[1][0] = -m[0][1];
m[1][1] = m[0][0];
m[1][2] = 0.0f;
m[2][0] = 0.0f;
m[2][1] = 0.0f;
m[2][2] = 1.0f;
}
/*-----------------------------------------------------------------------------
                           cMatrix3::setScale()
-----------------------------------------------------------------------------*/
void cMatrix3::setScale(float s)
{
// build a scale matrix WITHOUT translation
m[0][0] = s;
m[0][1] = 0.0f;
m[0][2] = 0.0f;
m[1][0] = 0.0f;
m[1][1] = s;
m[1][2] = 0.0f;
m[2][0] = 0.0f;
m[2][1] = 0.0f;
m[2][2] = s;
m[3][0] = 0.0f;
m[3][1] = 0.0f;
m[3][2] = 0.0f;
}
/*-----------------------------------------------------------------------------
                               cMatrix3::scale()
-----------------------------------------------------------------------------*/
void cMatrix3::scale(float sx, float sy, float sz)
{
// scale the matrix 
m[0][0] *= sx;
m[0][1] *= sy;
m[0][2] *= sz;
m[1][0] *= sx;
m[1][1] *= sy;
m[1][2] *= sz;
m[2][0] *= sx;
m[2][1] *= sy;
m[2][2] *= sz;
m[3][0] *= sx;
m[3][1] *= sy;
m[3][2] *= sz;
}
/*-----------------------------------------------------------------------------
                               cMatrix3::scaleX()
-----------------------------------------------------------------------------*/
void cMatrix3::scaleX(float s)
{
// scale the matrix on the X axis 
m[0][0] *= s;
m[1][0] *= s;
m[2][0] *= s;
m[3][0] *= s;
}
/*-----------------------------------------------------------------------------
                               cMatrix3::scaleY()
-----------------------------------------------------------------------------*/
void cMatrix3::scaleY(float s)
{
// scale the matrix on the Y axis 
m[0][1] *= s;
m[1][1] *= s;
m[2][1] *= s;
m[3][1] *= s;
}
/*-----------------------------------------------------------------------------
                               cMatrix3::scaleZ()
-----------------------------------------------------------------------------*/
void cMatrix3::scaleZ(float s)
{
// scale the matrix on the Z axis 
m[0][2] *= s;
m[1][2] *= s;
m[2][2] *= s;
m[3][2] *= s;
}
/*-----------------------------------------------------------------------------
                              cMatrix3::rotateX()
-----------------------------------------------------------------------------*/
void cMatrix3::rotateX(float angle)
{
float sinAngle, cosAngle, v1, v2;

// "multiply" with a rotation matrix 
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
v1       = m[0][1]*cosAngle - m[0][2]*sinAngle;
v2       = m[0][1]*sinAngle + m[0][2]*cosAngle;
m[0][1]  = v1;
m[0][2]  = v2;
v1       = m[1][1]*cosAngle - m[1][2]*sinAngle;
v2       = m[1][1]*sinAngle + m[1][2]*cosAngle;
m[1][1]  = v1;
m[1][2]  = v2;
v1       = m[2][1]*cosAngle - m[2][2]*sinAngle;
v2       = m[2][1]*sinAngle + m[2][2]*cosAngle;
m[2][1]  = v1;
m[2][2]  = v2;
v1       = m[3][1]*cosAngle - m[3][2]*sinAngle;
v2       = m[3][1]*sinAngle + m[3][2]*cosAngle;
m[3][1]  = v1;
m[3][2]  = v2;
}
/*-----------------------------------------------------------------------------
                              cMatrix3::rotateY()
-----------------------------------------------------------------------------*/
void cMatrix3::rotateY(float angle)
{
float sinAngle, cosAngle, v1, v2;

// "multiply" with a rotation matrix 
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
v1       =  m[0][0]*cosAngle + m[0][2]*sinAngle;
v2       = -m[0][0]*sinAngle + m[0][2]*cosAngle;
m[0][0]  = v1;
m[0][2]  = v2;
v1       =  m[1][0]*cosAngle + m[1][2]*sinAngle;
v2       = -m[1][0]*sinAngle + m[1][2]*cosAngle;
m[1][0]  = v1;
m[1][2]  = v2;
v1       =  m[2][0]*cosAngle + m[2][2]*sinAngle;
v2       = -m[2][0]*sinAngle + m[2][2]*cosAngle;
m[2][0]  = v1;
m[2][2]  = v2;
v1       =  m[3][0]*cosAngle + m[3][2]*sinAngle;
v2       = -m[3][0]*sinAngle + m[3][2]*cosAngle;
m[3][0]  = v1;
m[3][2]  = v2;
}
/*-----------------------------------------------------------------------------
                              cMatrix3::rotateZ()
-----------------------------------------------------------------------------*/
void cMatrix3::rotateZ(float angle)
{
float sinAngle, cosAngle, v1, v2;

// "multiply" with a rotation matrix 
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
v1       = m[0][0]*cosAngle - m[0][1]*sinAngle;
v2       = m[0][0]*sinAngle + m[0][1]*cosAngle;
m[0][0]  = v1;
m[0][1]  = v2;
v1       = m[1][0]*cosAngle - m[1][1]*sinAngle;
v2       = m[1][0]*sinAngle + m[1][1]*cosAngle;
m[1][0]  = v1;
m[1][1]  = v2;
v1       = m[2][0]*cosAngle - m[2][1]*sinAngle;
v2       = m[2][0]*sinAngle + m[2][1]*cosAngle;
m[2][0]  = v1;
m[2][1]  = v2;
v1       = m[3][0]*cosAngle - m[3][1]*sinAngle;
v2       = m[3][0]*sinAngle + m[3][1]*cosAngle;
m[3][0]  = v1;
m[3][1]  = v2;
}
/*-----------------------------------------------------------------------------
                            cMatrix3::rotateQuat()
-----------------------------------------------------------------------------*/
void cMatrix3::rotateQuat(float *q)
{
cMatrix3 aux(-1);
float wx, wy, wz, xx, xy, xz, yy, yz, zz;

// build a matrix from a quaternion q[0..2] = vector*sin(theta/2), q[3] = cos(theta/2)
wx = q[3] * q[0] * 2.0f;
wy = q[3] * q[1] * 2.0f;
wz = q[3] * q[2] * 2.0f;
xx = q[0] * q[0] * 2.0f;
xy = q[0] * q[1] * 2.0f;
xz = q[0] * q[2] * 2.0f;
yy = q[1] * q[1] * 2.0f;
yz = q[1] * q[2] * 2.0f;
zz = q[2] * q[2] * 2.0f;
aux.m[0][0] = 1.0f - (yy + zz);
aux.m[0][1] = xy + wz;
aux.m[0][2] = xz - wy;
aux.m[1][0] = xy - wz;
aux.m[1][1] = 1.0f - (xx + zz);
aux.m[1][2] = yz + wx;
aux.m[2][0] = xz + wy;
aux.m[2][1] = yz - wx;
aux.m[2][2] = 1.0f - (xx + yy);

// "multiply" with a quaternion rotation matrix 
xx = m[0][0];
yy = m[0][1];
zz = m[0][2];
m[0][0] = xx*aux.m[0][0] + yy*aux.m[1][0] + zz*aux.m[2][0];
m[0][1] = xx*aux.m[0][1] + yy*aux.m[1][1] + zz*aux.m[2][1];
m[0][2] = xx*aux.m[0][2] + yy*aux.m[1][2] + zz*aux.m[2][2];
xx = m[1][0];
yy = m[1][1];
zz = m[1][2];
m[1][0] = xx*aux.m[0][0] + yy*aux.m[1][0] + zz*aux.m[2][0];
m[1][1] = xx*aux.m[0][1] + yy*aux.m[1][1] + zz*aux.m[2][1];
m[1][2] = xx*aux.m[0][2] + yy*aux.m[1][2] + zz*aux.m[2][2];
xx = m[2][0];
yy = m[2][1];
zz = m[2][2];
m[2][0] = xx*aux.m[0][0] + yy*aux.m[1][0] + zz*aux.m[2][0];
m[2][1] = xx*aux.m[0][1] + yy*aux.m[1][1] + zz*aux.m[2][1];
m[2][2] = xx*aux.m[0][2] + yy*aux.m[1][2] + zz*aux.m[2][2];
xx = m[3][0];
yy = m[3][1];
zz = m[3][2];
m[3][0] = xx*aux.m[0][0] + yy*aux.m[1][0] + zz*aux.m[2][0];
m[3][1] = xx*aux.m[0][1] + yy*aux.m[1][1] + zz*aux.m[2][1];
m[3][2] = xx*aux.m[0][2] + yy*aux.m[1][2] + zz*aux.m[2][2];
}
/*-----------------------------------------------------------------------------
                            cMatrix3::rotateQuat()
-----------------------------------------------------------------------------*/
void cMatrix3::rotateQuat(cQuat &q)
{
cMatrix3 aux(-1);
float wx, wy, wz, xx, xy, xz, yy, yz, zz;

// build a matrix from a quaternion 
wx = q.s   * q.v.x * 2.0f;
wy = q.s   * q.v.y * 2.0f;
wz = q.s   * q.v.z * 2.0f;
xx = q.v.x * q.v.x * 2.0f;
xy = q.v.x * q.v.y * 2.0f;
xz = q.v.x * q.v.z * 2.0f;
yy = q.v.y * q.v.y * 2.0f;
yz = q.v.y * q.v.z * 2.0f;
zz = q.v.z * q.v.z * 2.0f;
aux.m[0][0] = 1.0f - (yy + zz);
aux.m[0][1] = xy + wz;
aux.m[0][2] = xz - wy;
aux.m[1][0] = xy - wz;
aux.m[1][1] = 1.0f - (xx + zz);
aux.m[1][2] = yz + wx;
aux.m[2][0] = xz + wy;
aux.m[2][1] = yz - wx;
aux.m[2][2] = 1.0f - (xx + yy);

// "multiply" with a quaternion rotation matrix 
xx = m[0][0];
yy = m[0][1];
zz = m[0][2];
m[0][0] = xx*aux.m[0][0] + yy*aux.m[1][0] + zz*aux.m[2][0];
m[0][1] = xx*aux.m[0][1] + yy*aux.m[1][1] + zz*aux.m[2][1];
m[0][2] = xx*aux.m[0][2] + yy*aux.m[1][2] + zz*aux.m[2][2];
xx = m[1][0];
yy = m[1][1];
zz = m[1][2];
m[1][0] = xx*aux.m[0][0] + yy*aux.m[1][0] + zz*aux.m[2][0];
m[1][1] = xx*aux.m[0][1] + yy*aux.m[1][1] + zz*aux.m[2][1];
m[1][2] = xx*aux.m[0][2] + yy*aux.m[1][2] + zz*aux.m[2][2];
xx = m[2][0];
yy = m[2][1];
zz = m[2][2];
m[2][0] = xx*aux.m[0][0] + yy*aux.m[1][0] + zz*aux.m[2][0];
m[2][1] = xx*aux.m[0][1] + yy*aux.m[1][1] + zz*aux.m[2][1];
m[2][2] = xx*aux.m[0][2] + yy*aux.m[1][2] + zz*aux.m[2][2];
xx = m[3][0];
yy = m[3][1];
zz = m[3][2];
m[3][0] = xx*aux.m[0][0] + yy*aux.m[1][0] + zz*aux.m[2][0];
m[3][1] = xx*aux.m[0][1] + yy*aux.m[1][1] + zz*aux.m[2][1];
m[3][2] = xx*aux.m[0][2] + yy*aux.m[1][2] + zz*aux.m[2][2];
}
/*-----------------------------------------------------------------------------
                             cMatrix3::translate()
-----------------------------------------------------------------------------*/
void cMatrix3::translate(float dx, float dy, float dz)
{
// adjust the translation row 
m[3][0] += dx;
m[3][1] += dy;
m[3][2] += dz;
}
/*-----------------------------------------------------------------------------
                             cMatrix3::translate()
-----------------------------------------------------------------------------*/
void cMatrix3::translate(const cPoint3 &p)
{
// adjust the translation row 
m[3][0] += p.x;
m[3][1] += p.y;
m[3][2] += p.z;
}
/*-----------------------------------------------------------------------------
                              cMatrix3::preScale()
-----------------------------------------------------------------------------*/
void cMatrix3::preScale(float sx, float sy, float sz)
{
// pre-scale the matrix 
m[0][0] *= sx;
m[0][1] *= sx;
m[0][2] *= sx;
m[1][0] *= sy;
m[1][1] *= sy;
m[1][2] *= sy;
m[2][0] *= sz;
m[2][1] *= sz;
m[2][2] *= sz;
}
/*-----------------------------------------------------------------------------
                              cMatrix3::preScaleX()
-----------------------------------------------------------------------------*/
void cMatrix3::preScaleX(float s)
{
// pre-scale the matrix 
m[0][0] *= s;
m[0][1] *= s;
m[0][2] *= s;
}
/*-----------------------------------------------------------------------------
                              cMatrix3::preScaleY()
-----------------------------------------------------------------------------*/
void cMatrix3::preScaleY(float s)
{
// pre-scale the matrix 
m[1][0] *= s;
m[1][1] *= s;
m[1][2] *= s;
}
/*-----------------------------------------------------------------------------
                              cMatrix3::preScaleZ()
-----------------------------------------------------------------------------*/
void cMatrix3::preScaleZ(float s)
{
// pre-scale the matrix 
m[2][0] *= s;
m[2][1] *= s;
m[2][2] *= s;
}
/*-----------------------------------------------------------------------------
                             cMatrix3::preRotateX()
-----------------------------------------------------------------------------*/
void cMatrix3::preRotateX(float angle)
{
float sinAngle, cosAngle, v1, v2;

// "pre-multiply" with a rotation matrix 
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
v1       =  m[1][0]*cosAngle + m[2][0]*sinAngle;
v2       = -m[1][0]*sinAngle + m[2][0]*cosAngle;
m[1][0]  = v1;
m[2][0]  = v2;
v1       =  m[1][1]*cosAngle + m[2][1]*sinAngle;
v2       = -m[1][1]*sinAngle + m[2][1]*cosAngle;
m[1][1]  = v1;
m[2][1]  = v2;
v1       =  m[1][2]*cosAngle + m[2][2]*sinAngle;
v2       = -m[1][2]*sinAngle + m[2][2]*cosAngle;
m[1][2]  = v1;
m[2][2]  = v2;
}
/*-----------------------------------------------------------------------------
                             cMatrix3::preRotateY()
-----------------------------------------------------------------------------*/
void cMatrix3::preRotateY(float angle)
{
float sinAngle, cosAngle, v1, v2;

// "pre-multiply" with a rotation matrix 
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
v1       = m[0][0]*cosAngle - m[2][0]*sinAngle;
v2       = m[0][0]*sinAngle + m[2][0]*cosAngle;
m[0][0]  = v1;
m[2][0]  = v2;
v1       = m[0][1]*cosAngle - m[2][1]*sinAngle;
v2       = m[0][1]*sinAngle + m[2][1]*cosAngle;
m[0][1]  = v1;
m[2][1]  = v2;
v1       = m[0][2]*cosAngle - m[2][2]*sinAngle;
v2       = m[0][2]*sinAngle + m[2][2]*cosAngle;
m[0][2]  = v1;
m[2][2]  = v2;
}
/*-----------------------------------------------------------------------------
                             cMatrix3::preRotateZ()
-----------------------------------------------------------------------------*/
void cMatrix3::preRotateZ(float angle)
{
float sinAngle, cosAngle, v1, v2;

// "pre-multiply" with a rotation matrix 
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
v1       =  m[0][0]*cosAngle + m[1][0]*sinAngle;
v2       = -m[0][0]*sinAngle + m[1][0]*cosAngle;
m[0][0]  = v1;
m[1][0]  = v2;
v1       =  m[0][1]*cosAngle + m[1][1]*sinAngle;
v2       = -m[0][1]*sinAngle + m[1][1]*cosAngle;
m[0][1]  = v1;
m[1][1]  = v2;
v1       =  m[0][2]*cosAngle + m[1][2]*sinAngle;
v2       = -m[0][2]*sinAngle + m[1][2]*cosAngle;
m[0][2]  = v1;
m[1][2]  = v2;
}
/*-----------------------------------------------------------------------------
                           cMatrix3::preRotateQuat()
-----------------------------------------------------------------------------*/
void cMatrix3::preRotateQuat(float *q)
{
cMatrix3 aux(-1);
float wx, wy, wz, xx, xy, xz, yy, yz, zz;

// build a matrix from a quaternion q[0..2] = vector*sin(theta/2), q[3] = cos(theta/2)
wx = q[3] * q[0] * 2.0f;
wy = q[3] * q[1] * 2.0f;
wz = q[3] * q[2] * 2.0f;
xx = q[0] * q[0] * 2.0f;
xy = q[0] * q[1] * 2.0f;
xz = q[0] * q[2] * 2.0f;
yy = q[1] * q[1] * 2.0f;
yz = q[1] * q[2] * 2.0f;
zz = q[2] * q[2] * 2.0f;
aux.m[0][0] = 1.0f - (yy + zz);
aux.m[0][1] = xy + wz;
aux.m[0][2] = xz - wy;
aux.m[1][0] = xy - wz;
aux.m[1][1] = 1.0f - (xx + zz);
aux.m[1][2] = yz + wx;
aux.m[2][0] = xz + wy;
aux.m[2][1] = yz - wx;
aux.m[2][2] = 1.0f - (xx + yy);

// "pre-multiply" with a quaternion rotation matrix 
xx = m[0][0];
yy = m[1][0];
zz = m[2][0];
m[0][0] = aux.m[0][0]*xx + aux.m[0][1]*yy + aux.m[0][2]*zz;
m[1][0] = aux.m[1][0]*xx + aux.m[1][1]*yy + aux.m[1][2]*zz;
m[2][0] = aux.m[2][0]*xx + aux.m[2][1]*yy + aux.m[2][2]*zz;
xx = m[0][1];
yy = m[1][1];
zz = m[2][1];
m[0][1] = aux.m[0][0]*xx + aux.m[0][1]*yy + aux.m[0][2]*zz;
m[1][1] = aux.m[1][0]*xx + aux.m[1][1]*yy + aux.m[1][2]*zz;
m[2][1] = aux.m[2][0]*xx + aux.m[2][1]*yy + aux.m[2][2]*zz;
xx = m[0][2];
yy = m[1][2];
zz = m[2][2];
m[0][2] = aux.m[0][0]*xx + aux.m[0][1]*yy + aux.m[0][2]*zz;
m[1][2] = aux.m[1][0]*xx + aux.m[1][1]*yy + aux.m[1][2]*zz;
m[2][2] = aux.m[2][0]*xx + aux.m[2][1]*yy + aux.m[2][2]*zz;
}
/*-----------------------------------------------------------------------------
                           cMatrix3::preRotateQuat()
-----------------------------------------------------------------------------*/
void cMatrix3::preRotateQuat(cQuat &q)
{
cMatrix3 aux(-1);
float wx, wy, wz, xx, xy, xz, yy, yz, zz;

// build a matrix from a quaternion 
wx = q.s   * q.v.x * 2.0f;
wy = q.s   * q.v.y * 2.0f;
wz = q.s   * q.v.z * 2.0f;
xx = q.v.x * q.v.x * 2.0f;
xy = q.v.x * q.v.y * 2.0f;
xz = q.v.x * q.v.z * 2.0f;
yy = q.v.y * q.v.y * 2.0f;
yz = q.v.y * q.v.z * 2.0f;
zz = q.v.z * q.v.z * 2.0f;
aux.m[0][0] = 1.0f - (yy + zz);
aux.m[0][1] = xy + wz;
aux.m[0][2] = xz - wy;
aux.m[1][0] = xy - wz;
aux.m[1][1] = 1.0f - (xx + zz);
aux.m[1][2] = yz + wx;
aux.m[2][0] = xz + wy;
aux.m[2][1] = yz - wx;
aux.m[2][2] = 1.0f - (xx + yy);

// "pre-multiply" with a quaternion rotation matrix 
xx = m[0][0];
yy = m[1][0];
zz = m[2][0];
m[0][0] = aux.m[0][0]*xx + aux.m[0][1]*yy + aux.m[0][2]*zz;
m[1][0] = aux.m[1][0]*xx + aux.m[1][1]*yy + aux.m[1][2]*zz;
m[2][0] = aux.m[2][0]*xx + aux.m[2][1]*yy + aux.m[2][2]*zz;
xx = m[0][1];
yy = m[1][1];
zz = m[2][1];
m[0][1] = aux.m[0][0]*xx + aux.m[0][1]*yy + aux.m[0][2]*zz;
m[1][1] = aux.m[1][0]*xx + aux.m[1][1]*yy + aux.m[1][2]*zz;
m[2][1] = aux.m[2][0]*xx + aux.m[2][1]*yy + aux.m[2][2]*zz;
xx = m[0][2];
yy = m[1][2];
zz = m[2][2];
m[0][2] = aux.m[0][0]*xx + aux.m[0][1]*yy + aux.m[0][2]*zz;
m[1][2] = aux.m[1][0]*xx + aux.m[1][1]*yy + aux.m[1][2]*zz;
m[2][2] = aux.m[2][0]*xx + aux.m[2][1]*yy + aux.m[2][2]*zz;
}
/*-----------------------------------------------------------------------------
                            cMatrix3::preTranslate()
-----------------------------------------------------------------------------*/
void cMatrix3::preTranslate(float dx, float dy, float dz)
{
// pre-translate the matrix 
m[3][0] += (m[0][0]*dx + m[1][0]*dy + m[2][0]*dz);
m[3][1] += (m[0][1]*dx + m[1][1]*dy + m[2][1]*dz);
m[3][2] += (m[0][2]*dx + m[1][2]*dy + m[2][2]*dz);
}
/*-----------------------------------------------------------------------------
                            cMatrix3::preTranslateX()
-----------------------------------------------------------------------------*/
void cMatrix3::preTranslateX(float delta)
{
// pre-translate the matrix 
m[3][0] += (m[0][0]*delta);
m[3][1] += (m[0][1]*delta);
m[3][2] += (m[0][2]*delta);
}
/*-----------------------------------------------------------------------------
                            cMatrix3::preTranslateY()
-----------------------------------------------------------------------------*/
void cMatrix3::preTranslateY(float delta)
{
// pre-translate the matrix 
m[3][0] += (m[1][0]*delta);
m[3][1] += (m[1][1]*delta);
m[3][2] += (m[1][2]*delta);
}
/*-----------------------------------------------------------------------------
                            cMatrix3::preTranslateZ()
-----------------------------------------------------------------------------*/
void cMatrix3::preTranslateZ(float delta)
{
// pre-translate the matrix 
m[3][0] += (m[2][0]*delta);
m[3][1] += (m[2][1]*delta);
m[3][2] += (m[2][2]*delta);
}
/*-----------------------------------------------------------------------------
                            cMatrix3::preTranslate()
-----------------------------------------------------------------------------*/
void cMatrix3::preTranslate(const cPoint3 &p)
{
// pre-translate the matrix 
m[3][0] += (m[0][0]*p.x + m[1][0]*p.y + m[2][0]*p.z);
m[3][1] += (m[0][1]*p.x + m[1][1]*p.y + m[2][1]*p.z);
m[3][2] += (m[0][2]*p.x + m[1][2]*p.y + m[2][2]*p.z);
}
/*-----------------------------------------------------------------------------
                             cMatrix3::operator*()
-----------------------------------------------------------------------------*/
cMatrix3 cMatrix3::operator*(const cMatrix3 &parm)
{
cMatrix3 aux(-1);

// multiply the parameter matrix on the right of this, returning the result 
aux.m[0][0] = m[0][0]*parm.m[0][0] + m[0][1]*parm.m[1][0] + m[0][2]*parm.m[2][0];
aux.m[0][1] = m[0][0]*parm.m[0][1] + m[0][1]*parm.m[1][1] + m[0][2]*parm.m[2][1];
aux.m[0][2] = m[0][0]*parm.m[0][2] + m[0][1]*parm.m[1][2] + m[0][2]*parm.m[2][2];
aux.m[1][0] = m[1][0]*parm.m[0][0] + m[1][1]*parm.m[1][0] + m[1][2]*parm.m[2][0];
aux.m[1][1] = m[1][0]*parm.m[0][1] + m[1][1]*parm.m[1][1] + m[1][2]*parm.m[2][1];
aux.m[1][2] = m[1][0]*parm.m[0][2] + m[1][1]*parm.m[1][2] + m[1][2]*parm.m[2][2];
aux.m[2][0] = m[2][0]*parm.m[0][0] + m[2][1]*parm.m[1][0] + m[2][2]*parm.m[2][0];
aux.m[2][1] = m[2][0]*parm.m[0][1] + m[2][1]*parm.m[1][1] + m[2][2]*parm.m[2][1];
aux.m[2][2] = m[2][0]*parm.m[0][2] + m[2][1]*parm.m[1][2] + m[2][2]*parm.m[2][2];
aux.m[3][0] = m[3][0]*parm.m[0][0] + m[3][1]*parm.m[1][0] + m[3][2]*parm.m[2][0] + parm.m[3][0];
aux.m[3][1] = m[3][0]*parm.m[0][1] + m[3][1]*parm.m[1][1] + m[3][2]*parm.m[2][1] + parm.m[3][1];
aux.m[3][2] = m[3][0]*parm.m[0][2] + m[3][1]*parm.m[1][2] + m[3][2]*parm.m[2][2] + parm.m[3][2];

return aux;
}
/*-----------------------------------------------------------------------------
                             cMatrix3::operator+()
-----------------------------------------------------------------------------*/
cMatrix3 cMatrix3::operator+(const cMatrix3 &parm)
{
cMatrix3 aux(-1);

// add the parameter matrix on the right of this, returning the result 
aux.m[0][0] = m[0][0] + parm.m[0][0];
aux.m[0][1] = m[0][1] + parm.m[0][1];
aux.m[0][2] = m[0][2] + parm.m[0][2];
aux.m[1][0] = m[1][0] + parm.m[1][0];
aux.m[1][1] = m[1][1] + parm.m[1][1];
aux.m[1][2] = m[1][2] + parm.m[1][2];
aux.m[2][0] = m[2][0] + parm.m[2][0];
aux.m[2][1] = m[2][1] + parm.m[2][1];
aux.m[2][2] = m[2][2] + parm.m[2][2];
aux.m[3][0] = m[3][0] + parm.m[3][0];
aux.m[3][1] = m[3][1] + parm.m[3][1];
aux.m[3][2] = m[3][2] + parm.m[3][2];

return aux;
}
/*-----------------------------------------------------------------------------
                             cMatrix3::operator+=()
-----------------------------------------------------------------------------*/
cMatrix3 &cMatrix3::operator+=(const cMatrix3 &other)
{
// add in the other matrix
m[0][0] += other.m[0][0];
m[0][1] += other.m[0][1];
m[0][2] += other.m[0][2];
m[1][0] += other.m[1][0];
m[1][1] += other.m[1][1];
m[1][2] += other.m[1][2];
m[2][0] += other.m[2][0];
m[2][1] += other.m[2][1];
m[2][2] += other.m[2][2];
m[3][0] += other.m[3][0];
m[3][1] += other.m[3][1];
m[3][2] += other.m[3][2];

return (*this);
}
/*-----------------------------------------------------------------------------
                              cMatrix3::inverse()
-----------------------------------------------------------------------------*/
cMatrix3 cMatrix3::inverse(void)
{
cMatrix3 aux(-1);
float det;

// check if its invertible (determinant must be non-zero) 
det = m[0][0]*(m[1][1]*m[2][2]-m[1][2]*m[2][1]) +
      m[0][1]*(m[1][2]*m[2][0]-m[1][0]*m[2][2]) +
      m[0][2]*(m[1][0]*m[2][1]-m[1][1]*m[2][0]);
if( (det < 1.0e-10f) && (-det < 1.0e-10f) )
   {
   // return a null matrix if it is not invertible 
   warningSet("Matrix is non-invertible",0);
   aux.zero();
   return aux;
   }
det = 1.0f / det;

// built the inverse of the matrix, and returns it 
// obs: the inverse of a cMatrix3 is ALWAYS a cMatrix3 (mathematically provable)
aux.m[0][0] = (m[1][1]*m[2][2] - m[1][2]*m[2][1]) * det;
aux.m[0][1] = (m[0][2]*m[2][1] - m[0][1]*m[2][2]) * det;
aux.m[0][2] = (m[0][1]*m[1][2] - m[0][2]*m[1][1]) * det;
aux.m[1][0] = (m[1][2]*m[2][0] - m[1][0]*m[2][2]) * det;
aux.m[1][1] = (m[0][0]*m[2][2] - m[0][2]*m[2][0]) * det;
aux.m[1][2] = (m[0][2]*m[1][0] - m[0][0]*m[1][2]) * det;
aux.m[2][0] = (m[1][0]*m[2][1] - m[1][1]*m[2][0]) * det;
aux.m[2][1] = (m[0][1]*m[2][0] - m[0][0]*m[2][1]) * det;
aux.m[2][2] = (m[0][0]*m[1][1] - m[0][1]*m[1][0]) * det;
aux.m[3][0] = -(m[3][0]*aux.m[0][0] + m[3][1]*aux.m[1][0] + m[3][2]*aux.m[2][0]);
aux.m[3][1] = -(m[3][0]*aux.m[0][1] + m[3][1]*aux.m[1][1] + m[3][2]*aux.m[2][1]);
aux.m[3][2] = -(m[3][0]*aux.m[0][2] + m[3][1]*aux.m[1][2] + m[3][2]*aux.m[2][2]);

return aux;
}
/*-----------------------------------------------------------------------------
                             cMatrix3::glMatrix()
-----------------------------------------------------------------------------*/
void cMatrix3::glMatrix(float *data)
{
// fill an OpenGL-compatible matrix of floats
data[0]  = m[0][0];
data[1]  = m[0][1];
data[2]  = m[0][2];
data[3]  = 0.0f;
data[4]  = m[1][0];
data[5]  = m[1][1];
data[6]  = m[1][2];
data[7]  = 0.0f;
data[8]  = m[2][0];
data[9]  = m[2][1];
data[10] = m[2][2];
data[11] = 0.0f;
data[12] = m[3][0];
data[13] = m[3][1];
data[14] = m[3][2];
data[15] = 1.0f;
}
/*-----------------------------------------------------------------------------
                           cMatrix3r::getEulerZYX()
-----------------------------------------------------------------------------*/
void cMatrix3::getEulerZYX(float *rx, float *ry, float *rz)
{
float aux;

// decompose the matrix as rotations on Z, Y and X axis. Matrix cannot have scale components
aux = (m[2][0] <= -1.0f) ? -1.0f : ((m[2][0] >= 1.0f) ? 1.0f : m[2][0]);
*ry = (float)asin(aux);
if( aux < 1.0f )
   {
   if( aux > -1.0f )
      {
      *rx = (float)atan2(-m[2][1], m[2][2]);
      *rz = (float)atan2(-m[1][0], m[0][0]);
      }
   else // not a unique solution
      {
      *rx = (float)-atan2(m[0][1], m[1][1]);
      *rz = 0.0f;
      }
   }
else // not a unique solution, too
   {
   *rx = (float)atan2(m[0][1], m[1][1]);
   *rz = 0.0f;
   }
}
/*-----------------------------------------------------------------------------
                           cMatrix3r::setRotationX()
-----------------------------------------------------------------------------*/
void cMatrix3r::setRotationX(float angle)
{
// build a rotation matrix about the X-axis 
m[0][0] = 1.0f;
m[0][1] = 0.0f;
m[0][2] = 0.0f;
m[1][0] = 0.0f;
m[1][1] = (float)cos(angle);
m[1][2] = (float)sin(angle);
m[2][0] = 0.0f;
m[2][1] = -m[1][2];
m[2][2] = m[1][1];
}
/*-----------------------------------------------------------------------------
                           cMatrix3r::setRotationY()
-----------------------------------------------------------------------------*/
void cMatrix3r::setRotationY(float angle)
{
// build a rotation matrix about the Y-axis 
m[0][0] = (float)cos(angle);
m[0][1] = 0.0f;
m[0][2] = (float)-sin(angle);
m[1][0] = 0.0f;
m[1][1] = 1.0f;
m[1][2] = 0.0f;
m[2][0] = -m[0][2];
m[2][1] = 0.0f;
m[2][2] = m[0][0];
}
/*-----------------------------------------------------------------------------
                           cMatrix3r::setRotationZ()
-----------------------------------------------------------------------------*/
void cMatrix3r::setRotationZ(float angle)
{
// build a rotation matrix about the Z-axis 
m[0][0] = (float)cos(angle);
m[0][1] = (float)sin(angle);
m[0][2] = 0.0f;
m[1][0] = -m[0][1];
m[1][1] = m[0][0];
m[1][2] = 0.0f;
m[2][0] = 0.0f;
m[2][1] = 0.0f;
m[2][2] = 1.0f;
}
/*-----------------------------------------------------------------------------
                              cMatrix3r::rotateX()
-----------------------------------------------------------------------------*/
void cMatrix3r::rotateX(float angle)
{
float sinAngle, cosAngle, v1, v2;

// "multiply" with a rotation matrix 
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
v1       = m[0][1]*cosAngle - m[0][2]*sinAngle;
v2       = m[0][1]*sinAngle + m[0][2]*cosAngle;
m[0][1]  = v1;
m[0][2]  = v2;
v1       = m[1][1]*cosAngle - m[1][2]*sinAngle;
v2       = m[1][1]*sinAngle + m[1][2]*cosAngle;
m[1][1]  = v1;
m[1][2]  = v2;
v1       = m[2][1]*cosAngle - m[2][2]*sinAngle;
v2       = m[2][1]*sinAngle + m[2][2]*cosAngle;
m[2][1]  = v1;
m[2][2]  = v2;
}
/*-----------------------------------------------------------------------------
                              cMatrix3r::rotateY()
-----------------------------------------------------------------------------*/
void cMatrix3r::rotateY(float angle)
{
float sinAngle, cosAngle, v1, v2;

// "multiply" with a rotation matrix 
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
v1       =  m[0][0]*cosAngle + m[0][2]*sinAngle;
v2       = -m[0][0]*sinAngle + m[0][2]*cosAngle;
m[0][0]  = v1;
m[0][2]  = v2;
v1       =  m[1][0]*cosAngle + m[1][2]*sinAngle;
v2       = -m[1][0]*sinAngle + m[1][2]*cosAngle;
m[1][0]  = v1;
m[1][2]  = v2;
v1       =  m[2][0]*cosAngle + m[2][2]*sinAngle;
v2       = -m[2][0]*sinAngle + m[2][2]*cosAngle;
m[2][0]  = v1;
m[2][2]  = v2;
}
/*-----------------------------------------------------------------------------
                              cMatrix3r::rotateZ()
-----------------------------------------------------------------------------*/
void cMatrix3r::rotateZ(float angle)
{
float sinAngle, cosAngle, v1, v2;

// "multiply" with a rotation matrix 
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
v1       = m[0][0]*cosAngle - m[0][1]*sinAngle;
v2       = m[0][0]*sinAngle + m[0][1]*cosAngle;
m[0][0]  = v1;
m[0][1]  = v2;
v1       = m[1][0]*cosAngle - m[1][1]*sinAngle;
v2       = m[1][0]*sinAngle + m[1][1]*cosAngle;
m[1][0]  = v1;
m[1][1]  = v2;
v1       = m[2][0]*cosAngle - m[2][1]*sinAngle;
v2       = m[2][0]*sinAngle + m[2][1]*cosAngle;
m[2][0]  = v1;
m[2][1]  = v2;
}
/*-----------------------------------------------------------------------------
                            cMatrix3r::rotateQuat()
-----------------------------------------------------------------------------*/
void cMatrix3r::rotateQuat(cQuat &q)
{
cMatrix3r aux(-1);
float x, y, z;

// build a matrix from a quaternion 
aux = q.matrix3r();

// "multiply" with a quaternion rotation matrix 
x = m[0][0];
y = m[0][1];
z = m[0][2];
m[0][0] = x*aux.m[0][0] + y*aux.m[1][0] + z*aux.m[2][0];
m[0][1] = x*aux.m[0][1] + y*aux.m[1][1] + z*aux.m[2][1];
m[0][2] = x*aux.m[0][2] + y*aux.m[1][2] + z*aux.m[2][2];
x = m[1][0];
y = m[1][1];
z = m[1][2];
m[1][0] = x*aux.m[0][0] + y*aux.m[1][0] + z*aux.m[2][0];
m[1][1] = x*aux.m[0][1] + y*aux.m[1][1] + z*aux.m[2][1];
m[1][2] = x*aux.m[0][2] + y*aux.m[1][2] + z*aux.m[2][2];
x = m[2][0];
y = m[2][1];
z = m[2][2];
m[2][0] = x*aux.m[0][0] + y*aux.m[1][0] + z*aux.m[2][0];
m[2][1] = x*aux.m[0][1] + y*aux.m[1][1] + z*aux.m[2][1];
m[2][2] = x*aux.m[0][2] + y*aux.m[1][2] + z*aux.m[2][2];
}
/*-----------------------------------------------------------------------------
                             cMatrix3r::preRotateX()
-----------------------------------------------------------------------------*/
void cMatrix3r::preRotateX(float angle)
{
float sinAngle, cosAngle, v1, v2;

// "pre-multiply" with a rotation matrix 
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
v1       =  m[1][0]*cosAngle + m[2][0]*sinAngle;
v2       = -m[1][0]*sinAngle + m[2][0]*cosAngle;
m[1][0]  = v1;
m[2][0]  = v2;
v1       =  m[1][1]*cosAngle + m[2][1]*sinAngle;
v2       = -m[1][1]*sinAngle + m[2][1]*cosAngle;
m[1][1]  = v1;
m[2][1]  = v2;
v1       =  m[1][2]*cosAngle + m[2][2]*sinAngle;
v2       = -m[1][2]*sinAngle + m[2][2]*cosAngle;
m[1][2]  = v1;
m[2][2]  = v2;
}
/*-----------------------------------------------------------------------------
                             cMatrix3r::preRotateY()
-----------------------------------------------------------------------------*/
void cMatrix3r::preRotateY(float angle)
{
float sinAngle, cosAngle, v1, v2;

// "pre-multiply" with a rotation matrix 
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
v1       = m[0][0]*cosAngle - m[2][0]*sinAngle;
v2       = m[0][0]*sinAngle + m[2][0]*cosAngle;
m[0][0]  = v1;
m[2][0]  = v2;
v1       = m[0][1]*cosAngle - m[2][1]*sinAngle;
v2       = m[0][1]*sinAngle + m[2][1]*cosAngle;
m[0][1]  = v1;
m[2][1]  = v2;
v1       = m[0][2]*cosAngle - m[2][2]*sinAngle;
v2       = m[0][2]*sinAngle + m[2][2]*cosAngle;
m[0][2]  = v1;
m[2][2]  = v2;
}
/*-----------------------------------------------------------------------------
                             cMatrix3r::preRotateZ()
-----------------------------------------------------------------------------*/
void cMatrix3r::preRotateZ(float angle)
{
float sinAngle, cosAngle, v1, v2;

// "pre-multiply" with a rotation matrix 
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
v1       =  m[0][0]*cosAngle + m[1][0]*sinAngle;
v2       = -m[0][0]*sinAngle + m[1][0]*cosAngle;
m[0][0]  = v1;
m[1][0]  = v2;
v1       =  m[0][1]*cosAngle + m[1][1]*sinAngle;
v2       = -m[0][1]*sinAngle + m[1][1]*cosAngle;
m[0][1]  = v1;
m[1][1]  = v2;
v1       =  m[0][2]*cosAngle + m[1][2]*sinAngle;
v2       = -m[0][2]*sinAngle + m[1][2]*cosAngle;
m[0][2]  = v1;
m[1][2]  = v2;
}
/*-----------------------------------------------------------------------------
                           cMatrix3r::preRotateQuat()
-----------------------------------------------------------------------------*/
void cMatrix3r::preRotateQuat(cQuat &q)
{
cMatrix3r aux(-1);
float x, y, z;

// build a matrix from a quaternion 
aux = q.matrix3r();

// "pre-multiply" with a quaternion rotation matrix 
x = m[0][0];
y = m[1][0];
z = m[2][0];
m[0][0] = aux.m[0][0]*x + aux.m[0][1]*y + aux.m[0][2]*z;
m[1][0] = aux.m[1][0]*x + aux.m[1][1]*y + aux.m[1][2]*z;
m[2][0] = aux.m[2][0]*x + aux.m[2][1]*y + aux.m[2][2]*z;
x = m[0][1];
y = m[1][1];
z = m[2][1];
m[0][1] = aux.m[0][0]*x + aux.m[0][1]*y + aux.m[0][2]*z;
m[1][1] = aux.m[1][0]*x + aux.m[1][1]*y + aux.m[1][2]*z;
m[2][1] = aux.m[2][0]*x + aux.m[2][1]*y + aux.m[2][2]*z;
x = m[0][2];
y = m[1][2];
z = m[2][2];
m[0][2] = aux.m[0][0]*x + aux.m[0][1]*y + aux.m[0][2]*z;
m[1][2] = aux.m[1][0]*x + aux.m[1][1]*y + aux.m[1][2]*z;
m[2][2] = aux.m[2][0]*x + aux.m[2][1]*y + aux.m[2][2]*z;
}
/*-----------------------------------------------------------------------------
                             cMatrix3r::operator*()
-----------------------------------------------------------------------------*/
cMatrix3r cMatrix3r::operator*(const cMatrix3r &parm)
{
cMatrix3r aux(-1);

// multiply the parameter matrix on the right of this, returning the result 
aux.m[0][0] = m[0][0]*parm.m[0][0] + m[0][1]*parm.m[1][0] + m[0][2]*parm.m[2][0];
aux.m[0][1] = m[0][0]*parm.m[0][1] + m[0][1]*parm.m[1][1] + m[0][2]*parm.m[2][1];
aux.m[0][2] = m[0][0]*parm.m[0][2] + m[0][1]*parm.m[1][2] + m[0][2]*parm.m[2][2];
aux.m[1][0] = m[1][0]*parm.m[0][0] + m[1][1]*parm.m[1][0] + m[1][2]*parm.m[2][0];
aux.m[1][1] = m[1][0]*parm.m[0][1] + m[1][1]*parm.m[1][1] + m[1][2]*parm.m[2][1];
aux.m[1][2] = m[1][0]*parm.m[0][2] + m[1][1]*parm.m[1][2] + m[1][2]*parm.m[2][2];
aux.m[2][0] = m[2][0]*parm.m[0][0] + m[2][1]*parm.m[1][0] + m[2][2]*parm.m[2][0];
aux.m[2][1] = m[2][0]*parm.m[0][1] + m[2][1]*parm.m[1][1] + m[2][2]*parm.m[2][1];
aux.m[2][2] = m[2][0]*parm.m[0][2] + m[2][1]*parm.m[1][2] + m[2][2]*parm.m[2][2];

return aux;
}
/*-----------------------------------------------------------------------------
                              cMatrix3r::inverse()
-----------------------------------------------------------------------------*/
cMatrix3r cMatrix3r::inverse(void)
{
cMatrix3r aux(-1);
float det;

// check if its invertible (determinant must be non-zero) 
det = m[0][0]*(m[1][1]*m[2][2]-m[1][2]*m[2][1]) +
      m[0][1]*(m[1][2]*m[2][0]-m[1][0]*m[2][2]) +
      m[0][2]*(m[1][0]*m[2][1]-m[1][1]*m[2][0]);
if( (det < 1.0e-10f) && (-det < 1.0e-10f) )
   {
   // return a null matrix if it is not invertible 
   warningSet("Matrix is non-invertible",0);
   aux.zero();
   return aux;
   }
det = 1.0f / det;

// built the inverse of the matrix, and returns it 
aux.m[0][0] = (m[1][1]*m[2][2] - m[1][2]*m[2][1]) * det;
aux.m[0][1] = (m[0][2]*m[2][1] - m[0][1]*m[2][2]) * det;
aux.m[0][2] = (m[0][1]*m[1][2] - m[0][2]*m[1][1]) * det;
aux.m[1][0] = (m[1][2]*m[2][0] - m[1][0]*m[2][2]) * det;
aux.m[1][1] = (m[0][0]*m[2][2] - m[0][2]*m[2][0]) * det;
aux.m[1][2] = (m[0][2]*m[1][0] - m[0][0]*m[1][2]) * det;
aux.m[2][0] = (m[1][0]*m[2][1] - m[1][1]*m[2][0]) * det;
aux.m[2][1] = (m[0][1]*m[2][0] - m[0][0]*m[2][1]) * det;
aux.m[2][2] = (m[0][0]*m[1][1] - m[0][1]*m[1][0]) * det;

return aux;
}
/*-----------------------------------------------------------------------------
                         cMatrix3r::removeInaccuracy()
-----------------------------------------------------------------------------*/
void cMatrix3r::removeInaccuracy(void)
{
int i, j;

// adjust near-zero and near-one elements
for(i=0; i<3; i++)
   for(j=0; j<3; j++)
      {
      if( (m[i][j] < MIN_FLOAT) && (-m[i][j] < MIN_FLOAT) )
         m[i][j] = 0.0f;
      else if( (1.0f-m[i][j]) < MIN_FLOAT )
         m[i][j] = 1.0f;
      else if( (1.0f+m[i][j]) < MIN_FLOAT )
         m[i][j] = -1.0f;
      }
}
/*-----------------------------------------------------------------------------
                              cPoint3::normalize()
-----------------------------------------------------------------------------*/
cPoint3 cPoint3::normalize(void)
{
float len;

// divide by the length 
len = this->length();
if( len < 1.0e-10f || (isNan(x) || isNan(y) || isNan(z)) )
   {
//   warningSet("Normalizing a zero-length cPoint3",0);
   this->zero();
   }
else
   {
   len = 1.0f / len;
   x  *= len;
   y  *= len;
   z  *= len;
   }

return (*this);
}
/*-----------------------------------------------------------------------------
                              cPoint3::operator*()
-----------------------------------------------------------------------------*/
cPoint3 cPoint3::operator*(const cMatrix3 &tm)
{
cPoint3 aux(-1);

// multiplies the point by the transformation matrix 
aux.x = x*tm.m[0][0] + y*tm.m[1][0] + z*tm.m[2][0] + tm.m[3][0];
aux.y = x*tm.m[0][1] + y*tm.m[1][1] + z*tm.m[2][1] + tm.m[3][1];
aux.z = x*tm.m[0][2] + y*tm.m[1][2] + z*tm.m[2][2] + tm.m[3][2];

return aux;
}
/*-----------------------------------------------------------------------------
                              cPoint3::operator*()
-----------------------------------------------------------------------------*/
cPoint3 cPoint3::operator*(const cMatrix3r &tm)
{
cPoint3 aux(-1);

// multiplies the point by the rotation matrix 
aux.x = x*tm.m[0][0] + y*tm.m[1][0] + z*tm.m[2][0];
aux.y = x*tm.m[0][1] + y*tm.m[1][1] + z*tm.m[2][1];
aux.z = x*tm.m[0][2] + y*tm.m[1][2] + z*tm.m[2][2];

return aux;
}
/*-----------------------------------------------------------------------------
                             cPoint3::operator*()
-----------------------------------------------------------------------------*/
cQuat cPoint3::operator*(const cQuat &q)
{
cQuat aux(-1);

// multiply a quaternion [0,vector] by another quaternion 
aux.s   = -(x*q.v.x + y*q.v.y + z*q.v.z);
aux.v.x = x*q.s + y*q.v.z - z*q.v.y;
aux.v.y = y*q.s + z*q.v.x - x*q.v.z;
aux.v.z = z*q.s + x*q.v.y - y*q.v.x;

return aux;
}
/*-----------------------------------------------------------------------------
                                cQuat::cQuat()
-----------------------------------------------------------------------------*/
cQuat::cQuat(const cMatrix3 &parm)
{
float trace, aux;
int   i;

// build a quaternion from a matrix
trace = parm.m[0][0] + parm.m[1][1] + parm.m[2][2];
if( trace > 0.0f )
   {
   // trace+1 = 4s^2
   aux = (float)sqrt(trace + 1.0f);
   s   = aux * 0.5f;
   aux = 0.5f / aux;
   v.x = (parm.m[1][2] - parm.m[2][1]) * aux;
   v.y = (parm.m[2][0] - parm.m[0][2]) * aux;
   v.z = (parm.m[0][1] - parm.m[1][0]) * aux;
   }
else // abs(s) < 1/2
   {
   // get largest diagonal element
   i = 0;
   if( parm.m[1][1] > parm.m[0][0] )
      i = 1;
   if( parm.m[2][2] > parm.m[i][i] )
      i = 2;

   // process according to largest diagonal element
   switch( i ) {
   case 0:
      // x is the largest
      aux = (float)sqrt(parm.m[0][0] - parm.m[1][1] - parm.m[2][2] + 1.0f);
      v.x = aux * 0.5f;
      aux = 0.5f / aux;
      s   = (parm.m[1][2] - parm.m[2][1]) * aux;
      v.y = (parm.m[1][0] + parm.m[0][1]) * aux;
      v.z = (parm.m[2][0] + parm.m[0][2]) * aux;
      break;
   case 1:
      // y is the largest
      aux = (float)sqrt(parm.m[1][1] - parm.m[0][0] - parm.m[2][2] + 1.0f);
      v.y = aux * 0.5f;
      aux = 0.5f / aux;
      s   = (parm.m[2][0] - parm.m[0][2]) * aux;
      v.x = (parm.m[1][0] + parm.m[0][1]) * aux;
      v.z = (parm.m[2][1] + parm.m[1][2]) * aux;
      break;
   case 2:
      // z is the largest
      aux = (float)sqrt(parm.m[2][2] - parm.m[0][0] - parm.m[1][1] + 1.0f);
      v.z = aux * 0.5f;
      aux = 0.5f / aux;
      s   = (parm.m[0][1] - parm.m[1][0]) * aux;
      v.x = (parm.m[2][0] + parm.m[0][2]) * aux;
      v.y = (parm.m[2][1] + parm.m[1][2]) * aux;
      break;
      }
   }
}
/*-----------------------------------------------------------------------------
                                cQuat::cQuat()
-----------------------------------------------------------------------------*/
cQuat::cQuat(const cMatrix3r &parm)
{
float trace, aux;
int   i;

// build a quaternion from a matrix
trace = parm.m[0][0] + parm.m[1][1] + parm.m[2][2];
if( trace > 0.0f )
   {
   // trace+1 = 4s^2
   aux = (float)sqrt(trace + 1.0f);
   s   = aux * 0.5f;
   aux = 0.5f / aux;
   v.x = (parm.m[1][2] - parm.m[2][1]) * aux;
   v.y = (parm.m[2][0] - parm.m[0][2]) * aux;
   v.z = (parm.m[0][1] - parm.m[1][0]) * aux;
   }
else // abs(s) < 1/2
   {
   // get largest diagonal element
   i = 0;
   if( parm.m[1][1] > parm.m[0][0] )
      i = 1;
   if( parm.m[2][2] > parm.m[i][i] )
      i = 2;

   // process according to largest diagonal element
   switch( i ) {
   case 0:
      // x is the largest
      aux = (float)sqrt(parm.m[0][0] - parm.m[1][1] - parm.m[2][2] + 1.0f);
      v.x = aux * 0.5f;
      aux = 0.5f / aux;
      s   = (parm.m[1][2] - parm.m[2][1]) * aux;
      v.y = (parm.m[1][0] + parm.m[0][1]) * aux;
      v.z = (parm.m[2][0] + parm.m[0][2]) * aux;
      break;
   case 1:
      // y is the largest
      aux = (float)sqrt(parm.m[1][1] - parm.m[0][0] - parm.m[2][2] + 1.0f);
      v.y = aux * 0.5f;
      aux = 0.5f / aux;
      s   = (parm.m[2][0] - parm.m[0][2]) * aux;
      v.x = (parm.m[1][0] + parm.m[0][1]) * aux;
      v.z = (parm.m[2][1] + parm.m[1][2]) * aux;
      break;
   case 2:
      // z is the largest
      aux = (float)sqrt(parm.m[2][2] - parm.m[0][0] - parm.m[1][1] + 1.0f);
      v.z = aux * 0.5f;
      aux = 0.5f / aux;
      s   = (parm.m[0][1] - parm.m[1][0]) * aux;
      v.x = (parm.m[2][0] + parm.m[0][2]) * aux;
      v.y = (parm.m[2][1] + parm.m[1][2]) * aux;
      break;
      }
   }
}
/*-----------------------------------------------------------------------------
                              cQuat::normalize()
-----------------------------------------------------------------------------*/
cQuat cQuat::normalize(void)
{
float len;

// divide by the length 
len = this->length();
if( len < 1.0e-10f )
   this->zero();
else
   {
   len  = 1.0f / len;
   s   *= len;
   v.x *= len;
   v.y *= len;
   v.z *= len;
   }

return (*this);
}
/*-----------------------------------------------------------------------------
                              cQuat::operator*()
-----------------------------------------------------------------------------*/
cQuat cQuat::operator*(const cQuat &other)
{
cQuat aux(-1);

// multiply two quaternions (combine rotations)
aux.s   = s*other.s   - v.x*other.v.x - v.y*other.v.y - v.z*other.v.z;
aux.v.x = s*other.v.x + v.x*other.s   + v.y*other.v.z - v.z*other.v.y;
aux.v.y = s*other.v.y - v.x*other.v.z + v.y*other.s   + v.z*other.v.x;
aux.v.z = s*other.v.z + v.x*other.v.y - v.y*other.v.x + v.z*other.s;

return aux;
}
/*-----------------------------------------------------------------------------
                              cQuat::operator*()
-----------------------------------------------------------------------------*/
cQuat cQuat::operator*(const cPoint3 &other)
{
cQuat aux(-1);

// multiply a quaternion by a quaternion [0,vector]
aux.s   = -(v.x*other.x + v.y*other.y + v.z*other.z);
aux.v.x = s*other.x + v.y*other.z - v.z*other.y;
aux.v.y = s*other.y + v.z*other.x - v.x*other.z;
aux.v.z = s*other.z + v.x*other.y - v.y*other.x;

return aux;
}
/*-----------------------------------------------------------------------------
                            cQuat::setRotationX()
-----------------------------------------------------------------------------*/
void cQuat::setRotationX(float angle)
{
// build a quaternion rotated about the X-axis
angle *= 0.5f;
s   = (float)cos(angle);
v.x = (float)sin(angle);
v.y = 0.0f;
v.z = 0.0f;
}
/*-----------------------------------------------------------------------------
                            cQuat::setRotationY()
-----------------------------------------------------------------------------*/
void cQuat::setRotationY(float angle)
{
// build a quaternion rotated about the Y-axis
angle *= 0.5f;
s   = (float)cos(angle);
v.x = 0.0f;
v.y = (float)sin(angle);
v.z = 0.0f;
}
/*-----------------------------------------------------------------------------
                            cQuat::setRotationZ()
-----------------------------------------------------------------------------*/
void cQuat::setRotationZ(float angle)
{
// build a quaternion rotated about the Z-axis
angle *= 0.5f;
s   = (float)cos(angle);
v.x = 0.0f;
v.y = 0.0f;
v.z = (float)sin(angle);
}
/*-----------------------------------------------------------------------------
                              cQuat::rotateX()
-----------------------------------------------------------------------------*/
void cQuat::rotateX(float angle)
{
float sinAngle, cosAngle, x, y, z, w;

// "multiply" with another quaternion [cos(angle/2), sin(angle/2)(1,0,0)]
angle   *= 0.5f;
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
w   = s*cosAngle   - v.x*sinAngle;
x   = s*sinAngle   + v.x*cosAngle;
y   = v.y*cosAngle + v.z*sinAngle;
z   = v.z*cosAngle - v.y*sinAngle;
s   = w;
v.x = x;
v.y = y;
v.z = z;
}
/*-----------------------------------------------------------------------------
                              cQuat::rotateY()
-----------------------------------------------------------------------------*/
void cQuat::rotateY(float angle)
{
float sinAngle, cosAngle, x, y, z, w;

// "multiply" with another quaternion [cos(angle/2), sin(angle/2)(0,1,0)]
angle   *= 0.5f;
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
w   = s*cosAngle   - v.y*sinAngle;
x   = v.x*cosAngle - v.z*sinAngle;
y   = s*sinAngle   + v.y*cosAngle;
z   = v.z*cosAngle + v.x*sinAngle;
s   = w;
v.x = x;
v.y = y;
v.z = z;
}
/*-----------------------------------------------------------------------------
                              cQuat::rotateZ()
-----------------------------------------------------------------------------*/
void cQuat::rotateZ(float angle)
{
float sinAngle, cosAngle, x, y, z, w;

// "multiply" with another quaternion [cos(angle/2), sin(angle/2)(0,0,1)]
angle   *= 0.5f;
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
w   = s*cosAngle   - v.z*sinAngle;
x   = v.x*cosAngle + v.y*sinAngle;
y   = v.y*cosAngle - v.x*sinAngle;
z   = s*sinAngle   + v.z*cosAngle;
s   = w;
v.x = x;
v.y = y;
v.z = z;
}
/*-----------------------------------------------------------------------------
                            cQuat::preRotateX()
-----------------------------------------------------------------------------*/
void cQuat::preRotateX(float angle)
{
float sinAngle, cosAngle, x, y, z, w;

// "pre-multiply" with another quaternion [cos(angle/2), sin(angle/2)(1,0,0)]
angle   *= 0.5f;
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
w   = cosAngle*s   - sinAngle*v.x;
x   = cosAngle*v.x + sinAngle*s;
y   = cosAngle*v.y - sinAngle*v.z;
z   = cosAngle*v.z + sinAngle*v.y;
s   = w;
v.x = x;
v.y = y;
v.z = z;
}
/*-----------------------------------------------------------------------------
                            cQuat::preRotateY()
-----------------------------------------------------------------------------*/
void cQuat::preRotateY(float angle)
{
float sinAngle, cosAngle, x, y, z, w;

// "pre-multiply" with another quaternion [cos(angle/2), sin(angle/2)(0,1,0)]
angle   *= 0.5f;
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
w   = cosAngle*s   - sinAngle*v.y;
x   = cosAngle*v.x + sinAngle*v.z;
y   = cosAngle*v.y + sinAngle*s;
z   = cosAngle*v.z - sinAngle*v.x;
s   = w;
v.x = x;
v.y = y;
v.z = z;
}
/*-----------------------------------------------------------------------------
                            cQuat::preRotateZ()
-----------------------------------------------------------------------------*/
void cQuat::preRotateZ(float angle)
{
float sinAngle, cosAngle, x, y, z, w;

// "pre-multiply" with another quaternion [cos(angle/2), sin(angle/2)(0,0,1)]
angle   *= 0.5f;
cosAngle = (float)cos(angle);
sinAngle = (float)sin(angle);
w   = cosAngle*s   - sinAngle*v.z;
x   = cosAngle*v.x - sinAngle*v.y;
y   = cosAngle*v.y + sinAngle*v.x;
z   = cosAngle*v.z + sinAngle*s;
s   = w;
v.x = x;
v.y = y;
v.z = z;
}
/*-----------------------------------------------------------------------------
                               cQuat::matrix3()
-----------------------------------------------------------------------------*/
cMatrix3 cQuat::matrix3(void)
{
cMatrix3 aux(-1);
float wx, wy, wz, xx, xy, xz, yy, yz, zz;

// build a matrix from a normalized quaternion 
wx = s   * v.x * 2.0f;
wy = s   * v.y * 2.0f;
wz = s   * v.z * 2.0f;
xx = v.x * v.x * 2.0f;
xy = v.x * v.y * 2.0f;
xz = v.x * v.z * 2.0f;
yy = v.y * v.y * 2.0f;
yz = v.y * v.z * 2.0f;
zz = v.z * v.z * 2.0f;
aux.m[0][0] = 1.0f - (yy + zz);
aux.m[0][1] = xy + wz;
aux.m[0][2] = xz - wy;
aux.m[1][0] = xy - wz;
aux.m[1][1] = 1.0f - (xx + zz);
aux.m[1][2] = yz + wx;
aux.m[2][0] = xz + wy;
aux.m[2][1] = yz - wx;
aux.m[2][2] = 1.0f - (xx + yy);
aux.m[3][0] = 0.0f;
aux.m[3][1] = 0.0f;
aux.m[3][2] = 0.0f;

return aux;
}
/*-----------------------------------------------------------------------------
                               cQuat::matrix3r()
-----------------------------------------------------------------------------*/
cMatrix3r cQuat::matrix3r(void)
{
cMatrix3r aux(-1);
float wx, wy, wz, xx, xy, xz, yy, yz, zz;

// build a matrix from a normalized quaternion 
wx = s   * v.x * 2.0f;
wy = s   * v.y * 2.0f;
wz = s   * v.z * 2.0f;
xx = v.x * v.x * 2.0f;
xy = v.x * v.y * 2.0f;
xz = v.x * v.z * 2.0f;
yy = v.y * v.y * 2.0f;
yz = v.y * v.z * 2.0f;
zz = v.z * v.z * 2.0f;
aux.m[0][0] = 1.0f - (yy + zz);
aux.m[0][1] = xy + wz;
aux.m[0][2] = xz - wy;
aux.m[1][0] = xy - wz;
aux.m[1][1] = 1.0f - (xx + zz);
aux.m[1][2] = yz + wx;
aux.m[2][0] = xz + wy;
aux.m[2][1] = yz - wx;
aux.m[2][2] = 1.0f - (xx + yy);

return aux;
}
/*-----------------------------------------------------------------------------
                               cQuat::glMatrix()
-----------------------------------------------------------------------------*/
void cQuat::glMatrix(float *data)
{
float wx, wy, wz, xx, xy, xz, yy, yz, zz;

// build a matrix from a normalized quaternion 
wx = s   * v.x * 2.0f;
wy = s   * v.y * 2.0f;
wz = s   * v.z * 2.0f;
xx = v.x * v.x * 2.0f;
xy = v.x * v.y * 2.0f;
xz = v.x * v.z * 2.0f;
yy = v.y * v.y * 2.0f;
yz = v.y * v.z * 2.0f;
zz = v.z * v.z * 2.0f;
data[0]  = 1.0f - (yy + zz);
data[1]  = xy + wz;
data[2]  = xz - wy;
data[3]  = 0.0f;
data[4]  = xy - wz;
data[5]  = 1.0f - (xx + zz);
data[6]  = yz + wx;
data[7]  = 0.0f;
data[8]  = xz + wy;
data[9]  = yz - wx;
data[10] = 1.0f - (xx + yy);
data[11] = 0.0f;
data[12] = 0.0f;
data[13] = 0.0f;
data[14] = 0.0f;
data[15] = 1.0f;
}
/*-----------------------------------------------------------------------------
                              cProjection::set()
-----------------------------------------------------------------------------*/
void cProjection::set(float viewW, float viewH, float pixelAspect, float fovParm, float zNearParm, float zFarParm)
{
float wS, hS;

// calculate parameters to build projection matrix
zNear = zNearParm;
zFar  = zFarParm;
hS    = viewH;
wS    = viewW * pixelAspect;
Q     = zFar / (zFar - zNear);
if( wS > hS )
   {
   // frustrum has spatial width > spatial height, so fovW > fovH
   fovW    = DEG2RAD(fovParm*0.5f);
   tanFovW = (float)tan(fovW);
   wP      = 1.0f / tanFovW;
   hP      = wP * wS / hS;
   tanFovH = 1.0f / hP;
   fovH    = (float)atan(tanFovH);
   }
else // frustrum has spatial height > spatial width, so fovH > fovW
   {
   fovH    = DEG2RAD(fovParm*0.5f);
   tanFovH = (float)tan(fovH);
   hP      = 1.0f / tanFovH;
   wP      = hP * hS / wS;
   tanFovW = 1.0f / wP;
   fovW    = (float)atan(tanFovW);
   }

// generate the projection matrix
memset(proj, 0, sizeof(proj));
proj[0][0] = wP;
proj[1][1] = hP;
proj[2][2] = Q;
proj[2][3] = 1.0f;
proj[3][2] = -Q * zNear;
}
/*-----------------------------------------------------------------------------
                        cProjection::generateMatrix()
-----------------------------------------------------------------------------*/
void cProjection::generateMatrix(const cMatrix3 &tm)
{
// generate a transposed composite 4x4 matrix of tm*projection 
viewProj[0][0] = tm.m[0][0]*wP;
viewProj[0][1] = tm.m[1][0]*wP;
viewProj[0][2] = tm.m[2][0]*wP;
viewProj[0][3] = tm.m[3][0]*wP;
viewProj[1][0] = tm.m[0][1]*hP;
viewProj[1][1] = tm.m[1][1]*hP;
viewProj[1][2] = tm.m[2][1]*hP;
viewProj[1][3] = tm.m[3][1]*hP;
viewProj[2][0] = tm.m[0][2]*Q;
viewProj[2][1] = tm.m[1][2]*Q;
viewProj[2][2] = tm.m[2][2]*Q;
viewProj[2][3] = tm.m[3][2]*Q - Q*zNear;
viewProj[3][0] = tm.m[0][2];
viewProj[3][1] = tm.m[1][2];
viewProj[3][2] = tm.m[2][2];
viewProj[3][3] = tm.m[3][2];
}
/*-----------------------------------------------------------------------------
                         cProjection::projectPoint()
-----------------------------------------------------------------------------*/
cPoint3 cProjection::projectPoint(const cPoint3 &p)
{
cPoint3 aux(-1);
float rhw;

// convert a point in world space to clip space
rhw   = 1.0f / (p.x*viewProj[3][0] + p.y*viewProj[3][1] + p.z*viewProj[3][2] + viewProj[3][3]);
aux.x = (p.x*viewProj[0][0] + p.y*viewProj[0][1] + p.z*viewProj[0][2] + viewProj[0][3]) * rhw;
aux.y = (p.x*viewProj[1][0] + p.y*viewProj[1][1] + p.z*viewProj[1][2] + viewProj[1][3]) * rhw;
aux.z = (p.x*viewProj[2][0] + p.y*viewProj[2][1] + p.z*viewProj[2][2] + viewProj[2][3]) * rhw;

return aux;
}
/*-----------------------------------------------------------------------------
                                normalRotate()
-----------------------------------------------------------------------------*/
cPoint3 normalRotate(const cPoint3 &n, const cMatrix3 &tm)
{
cPoint3 aux(-1);

// multiplies the point by the transformation matrix 
aux.x = n.x*tm.m[0][0] + n.y*tm.m[1][0] + n.z*tm.m[2][0];
aux.y = n.x*tm.m[0][1] + n.y*tm.m[1][1] + n.z*tm.m[2][1];
aux.z = n.x*tm.m[0][2] + n.y*tm.m[1][2] + n.z*tm.m[2][2];

return aux;
}
/*-----------------------------------------------------------------------------
                                crossProduct()
-----------------------------------------------------------------------------*/
cPoint3 crossProduct(const cPoint3 &p1, const cPoint3 &p2)
{
cPoint3 aux(-1);

// return the cross product of two vectors: |cross| = |p1|.|p2|.sin(angle) 
aux.x = p1.y*p2.z - p1.z*p2.y;
aux.y = p1.z*p2.x - p1.x*p2.z;
aux.z = p1.x*p2.y - p1.y*p2.x;

return aux;
}
/*-----------------------------------------------------------------------------
                                 mFromQuat()
-----------------------------------------------------------------------------*/
cMatrix3 mFromQuat(float *q)
{
cMatrix3 aux(-1);
float wx, wy, wz, xx, xy, xz, yy, yz, zz;

// build a matrix from a quaternion 
// obs: this code seems wrong (column-vectors)!!!!
wx = q[3] * q[0] * 2.0f;
wy = q[3] * q[1] * 2.0f;
wz = q[3] * q[2] * 2.0f;
xx = q[0] * q[0] * 2.0f;
xy = q[0] * q[1] * 2.0f;
xz = q[0] * q[2] * 2.0f;
yy = q[1] * q[1] * 2.0f;
yz = q[1] * q[2] * 2.0f;
zz = q[2] * q[2] * 2.0f;
aux.m[0][0] = 1.0f - (yy + zz);
aux.m[0][1] = xy + wz;
aux.m[0][2] = xz - wy;
aux.m[1][0] = xy - wz;
aux.m[1][1] = 1.0f - (xx + zz);
aux.m[1][2] = yz + wx;
aux.m[2][0] = xz + wy;
aux.m[2][1] = yz - wx;
aux.m[2][2] = 1.0f - (xx + yy);
aux.m[3][0] = 0.0f;
aux.m[3][1] = 0.0f;
aux.m[3][2] = 0.0f;

return aux;
}
/*-----------------------------------------------------------------------------
                                transpose()
-----------------------------------------------------------------------------*/
cMatrix3r transpose(const cMatrix3r &tm)
{
cMatrix3r aux(-1);

// transpose the source matrix 
aux.m[0][0] = tm.m[0][0];
aux.m[1][0] = tm.m[0][1];
aux.m[2][0] = tm.m[0][2];
aux.m[0][1] = tm.m[1][0];
aux.m[1][1] = tm.m[1][1];
aux.m[2][1] = tm.m[1][2];
aux.m[0][2] = tm.m[2][0];
aux.m[1][2] = tm.m[2][1];
aux.m[2][2] = tm.m[2][2];

return aux;
}
/*-----------------------------------------------------------------------------
                                normalize()
-----------------------------------------------------------------------------*/
cQuat normalize(cQuat &q)
{
cQuat aux(-1);
float len;

// divide by the length 
len = q.length();
if( len < 1.0e-10f )
   aux.zero();
else
   {
   len     = 1.0f / len;
   aux.s   = q.s * len;
   aux.v.x = q.v.x * len;
   aux.v.y = q.v.y * len;
   aux.v.z = q.v.z * len;
   }

return aux;
}
/*-----------------------------------------------------------------------------
                                   arctan2()
-----------------------------------------------------------------------------*/
float arctan2(float dx, float dy)
{
float absdx, absdy;

// check parameter validity
assert( (dx != 0.0f) || (dy != 0.0f) );

// calculates the arc-tangent, according to the signs of the deltas [-PI,PI)
absdx = (dx < 0.0f) ? -dx : dx;
absdy = (dy < 0.0f) ? -dy : dy;
if( absdx > absdy )
   {
   if( dx > 0.0f )
      {
      if( dy > 0.0f )
         {
         return (float)atan(absdy/absdx);
         }
      else // dy <= 0.0f
         {
         return (float)-atan(absdy/absdx);
         }
      }
   else // dx <= 0.0f
      {
      if( dy > 0.0f )
         {
         return (float)(PI - atan(absdy/absdx));
         }
      else // dy <= 0.0f
         {
         return (float)(-PI + atan(absdy/absdx));
         }
      }
   }
else // absdy >= absdx
   {
   if( dx > 0.0f )
      {
      if( dy > 0.0f )
         {
         return (float)(PI*0.5f - atan(absdx/absdy));
         }
      else // dy <= 0.0f
         {
         return (float)(-PI*0.5f + atan(absdx/absdy));
         }
      }
   else // dx <= 0.0f
      {
      if( dy > 0.0f )
         {
         return (float)(PI*0.5f + atan(absdx/absdy));
         }
      else // dy <= 0.0f
         {
         return (float)(-PI*0.5f - atan(absdx/absdy));
         }
      }
   }
}
/*-----------------------------------------------------------------------------
                                 interpolate()
-----------------------------------------------------------------------------*/
float interpolate(int type, float iniVal, float endVal, dword startTime, dword duration, dword msTime)
{
float t, b0, b1, b2, b3;

// check parameter validity
assert( duration > 0 );
assert( (type >= I_LINEAR) && (type <= I_FASTEST) );

// check if past the end time
if( msTime <= startTime )
   return iniVal;
if( msTime >= (startTime+duration) )
   return endVal;

// check if will use linear or bezier interpolation
if( type == I_LINEAR )
   {
   // perform a linear interpolation
   return iniVal + ((float)(msTime - startTime))*(endVal - iniVal) / (float)duration;
   }
else // bezier interpolation
   {
   // calculate parametric offset
   t = (float)(msTime - startTime) / (float)duration;

   // calculate bezier basis
   b0 = (1.0f - t) * (1.0f - t) * (1.0f - t);
   b1 = 3.0f * t * (1.0f - t) * (1.0f - t);
   b2 = 3.0f * t * t * (1.0f - t);
   b3 = t * t * t;

   // process according to interpolation type
   switch( type ) {
   case I_SIN:
      // sinuidal interpolation
      return (b0+b1)*iniVal + (b2+b3)*endVal;

   case I_SLOWEST:
      // start slowest, finish fast
      return (b0+b1+b2)*iniVal + b3*endVal;

   case I_SLOW:
      // start slow, finish fast
      return (b0+b1)*iniVal + b2*0.5f*(iniVal+endVal) + b3*endVal;

   case I_FAST:
      // start fast, finish slow
      return b0*iniVal + b1*0.5f*(iniVal+endVal) + (b2+b3)*endVal;

   case I_FASTEST:
      // start fastest, finish slow
      return b0*iniVal + (b1+b2+b3)*endVal;
      }

   return endVal;
   }
}
/*-----------------------------------------------------------------------------
                                 interpolate()
-----------------------------------------------------------------------------*/
float interpolate(int type, float iniVal, float endVal, float t)
{
float b0, b1, b2, b3;

// check parameter validity
assert( (type >= I_LINEAR) && (type <= I_FASTEST) );

// check if past the end time
if( t <= 0.0f )
   return iniVal;
if( t >= 1.0f )
   return endVal;

// check if will use linear or bezier interpolation
if( type == I_LINEAR )
   {
   // perform a linear interpolation
   return iniVal + t*(endVal - iniVal);
   }
else // bezier interpolation
   {
   // calculate bezier basis
   b0 = (1.0f - t) * (1.0f - t) * (1.0f - t);
   b1 = 3.0f * t * (1.0f - t) * (1.0f - t);
   b2 = 3.0f * t * t * (1.0f - t);
   b3 = t * t * t;

   // process according to interpolation type
   switch( type ) {
   case I_SIN:
      // sinuidal interpolation
      return (b0+b1)*iniVal + (b2+b3)*endVal;

   case I_SLOWEST:
      // start slowest, finish fast
      return (b0+b1+b2)*iniVal + b3*endVal;

   case I_SLOW:
      // start slow, finish fast
      return (b0+b1)*iniVal + b2*0.5f*(iniVal+endVal) + b3*endVal;

   case I_FAST:
      // start fast, finish slow
      return b0*iniVal + b1*0.5f*(iniVal+endVal) + (b2+b3)*endVal;

   case I_FASTEST:
      // start fastest, finish slow
      return b0*iniVal + (b1+b2+b3)*endVal;
      }

   return endVal;
   }
}
/*-----------------------------------------------------------------------------
                               solveJacobi()
-----------------------------------------------------------------------------*/
int solveJacobi(tJacobiParm *parm)
{
int   j, iq, ip, i;
float tresh, theta, tau, t, sm, s, h, g, c;
float b[6], z[6];


// Computes all eigenvalues and eigenvectors of a real symmetric matrix a[0..n][0..n]. On
// output, elements of a above the diagonal are destroyed. d[0..n] returns the eigenvalues of a.
// v[0..n][0..n] is a matrix whose columns contain, on output, the normalized eigenvectors of a.
// nRot returns the number of Jacobi rotations that were required. The matrix dimension is parm->dim

// initialize v to the identity matrix, b and d to the diagonal of a
memset(parm->v, 0, sizeof(parm->v));
for(i=0; i < parm->dim; i++)
   {
   parm->v[i][i] = 1.0f;
   b[i] = parm->d[i] = parm->a[i][i];
   z[i] = 0.0f;
   }
parm->nRot = 0;

// loop on a maximum of 50 iterations
for(i=1; i <= 50; i++)
   {
   // sum off-diagonal elements
   sm = 0.0f;
   for(ip=0; ip < parm->dim-1; ip++)
      {
      for(iq=ip+1; iq < parm->dim; iq++)
         sm += fAbs(parm->a[ip][iq]);
      }

   // the normal return. We cannot rely on 0.0f as automatic underflow
   if( sm < MIN_FLOAT )
      return 1;

   // calculate treshold. Different for the first three sweeps
   tresh = (i < 4) ? 0.2f*sm / (float)(parm->dim*parm->dim) : 0.0f;
   for(ip=0; ip < parm->dim-1; ip++)
      {
      for(iq=ip+1; iq < parm->dim; iq++)
         {
         // after 4 sweeps, skip the rotation if the off-diagonal element is small
         // note that we sum g, that if too small will not affect the diagonal elements in floating point math
         g = 100.0f*fAbs(parm->a[ip][iq]);
         if( (i > 4) && ((fAbs(parm->d[ip])+g) == fAbs(parm->d[ip])) && ((fAbs(parm->d[iq])+g) == fAbs(parm->d[iq])) )
            {
            parm->a[ip][iq] = 0.0f;
            }
         else if( fAbs(parm->a[ip][iq]) > tresh )
            {
            h = parm->d[iq] - parm->d[ip];
            if( (fAbs(h)+g) == fAbs(h) )
               t = parm->a[ip][iq] / h;
            else
               {
               theta = 0.5f*h / parm->a[ip][iq];
               t     = 1.0f / (fAbs(theta) + (float)sqrt(1.0f + theta*theta));
               if( theta < 0.0f )
                  t = -t;
               }
            c      = 1.0f / (float)sqrt(1.0f + t*t);
            s      = t * c;
            tau    = s / (1.0f + c);
            h      = t * parm->a[ip][iq];
            z[ip] -= h;
            z[iq] += h;
            parm->d[ip] -= h;
            parm->d[iq] += h;
            parm->a[ip][iq] = 0.0f;
            for(j=0; j <= ip-1; j++)
               {
               // case of rotations 1 <= j < p  ROTATE(a,j,ip,j,iq)
               g = parm->a[j][ip];
               h = parm->a[j][iq];
               parm->a[j][ip] = g - s*(h + g*tau);
               parm->a[j][iq] = h + s*(g - h*tau);
               }
            for(j=ip+1; j <= iq-1; j++)
               {
               // case of rotations p < j < q  ROTATE(a,ip,j,j,iq)
               g = parm->a[ip][j];
               h = parm->a[j][iq];
               parm->a[ip][j] = g - s*(h + g*tau);
               parm->a[j][iq] = h + s*(g - h*tau);
               }
            for(j=iq+1; j<parm->dim; j++)
               {
               // case of rotations q < j <= dim  ROTATE(a,ip,j,iq,j)
               g = parm->a[ip][j];
               h = parm->a[iq][j];
               parm->a[ip][j] = g - s*(h + g*tau);
               parm->a[iq][j] = h + s*(g - h*tau);
               }
            for(j=0; j<parm->dim; j++)
               {
               // ROTATE(v,j,ip,j,iq)
               g = parm->v[j][ip];
               h = parm->v[j][iq];
               parm->v[j][ip] = g - s*(h + g*tau);
               parm->v[j][iq] = h + s*(g - h*tau);
               }
            parm->nRot++;
            }
         }
      }

   // update d with the sum of tapq, and reinitialize z
   for(j=0; j<parm->dim; j++)
      {
      b[j] += z[j];
      parm->d[j] = b[j];
      z[j] = 0.0f;
      }
   }

// too many iterations 
return errorSet("Too many iterations in solveJacobi()",i);
}

