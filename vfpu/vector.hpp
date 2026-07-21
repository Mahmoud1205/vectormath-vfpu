/*
   Copyright (C) 2006, 2007 Sony Computer Entertainment Inc.
   All rights reserved.

   Redistribution and use in source and binary forms,
   with or without modification, are permitted provided that the
   following conditions are met:
	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.
	* Neither the name of the Sony Computer Entertainment Inc nor the names
	  of its contributors may be used to endorse or promote products derived
	  from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef VECTORMATH_VFPU_VECTOR_HPP
#define VECTORMATH_VFPU_VECTOR_HPP

namespace Vectormath
{

namespace VFPU
{

#include "vfpu.h" // implementation of vfpu functions

// Small epsilon value
static const float VECTORMATH_SLERP_TOL = 0.999f;

// ========================================================
// Vector3
// ========================================================

inline Vector3::Vector3(const Vector3 & vec)
{
	vfpuCopy4(&vec.mX, &mX);
}

inline Vector3::Vector3(float _x, float _y, float _z)
{
	mX = _x;
	mY = _y;
	mZ = _z;
}

inline Vector3::Vector3(const Point3 & pnt)
{
	vfpuCopy4(&pnt.mX, &mX);
}

// TODO: for this, and for other similar such as Vec2,4 and Mats,
// please add an overload for zeroing them; VFPU has zeroing
// instructions that are likely more efficient than replication
inline Vector3::Vector3(float scalar)
{
	vfpuReplicate4(scalar, &mX);
}

inline const Vector3 Vector3::xAxis()
{
	return Vector3(1.0f, 0.0f, 0.0f);
}

inline const Vector3 Vector3::yAxis()
{
	return Vector3(0.0f, 1.0f, 0.0f);
}

inline const Vector3 Vector3::zAxis()
{
	return Vector3(0.0f, 0.0f, 1.0f);
}

inline const Vector3 lerp(float t, const Vector3 & vec0, const Vector3 & vec1)
{
	Vector3 res;
	vfpuLerp4(&vec0.mX, &vec1.mX, &res.mX, t);
	return res;
}

inline const Vector3 slerp(float t, const Vector3 & unitVec0, const Vector3 & unitVec1)
{
	// TODO: implement vfpu
	float recipSinAngle, scale0, scale1, cosAngle, angle;
	cosAngle = dot(unitVec0, unitVec1);
	if (cosAngle < VECTORMATH_SLERP_TOL)
	{
		angle = std::acosf(cosAngle);
		recipSinAngle = (1.0f / std::sinf(angle));
		scale0 = (std::sinf(((1.0f - t) * angle)) * recipSinAngle);
		scale1 = (std::sinf((t * angle)) * recipSinAngle);
	}
	else
	{
		scale0 = (1.0f - t);
		scale1 = t;
	}
	return ((unitVec0 * scale0) + (unitVec1 * scale1));
}

inline Vector3 & Vector3::operator = (const Vector3 & vec)
{
	vfpuCopy4(&vec.mX, &mX);
	return *this;
}

inline Vector3 & Vector3::setX(float _x)
{
	mX = _x;
	return *this;
}

inline float Vector3::getX() const
{
	return mX;
}

inline Vector3 & Vector3::setY(float _y)
{
	mY = _y;
	return *this;
}

inline float Vector3::getY() const
{
	return mY;
}

inline Vector3 & Vector3::setZ(float _z)
{
	mZ = _z;
	return *this;
}

inline float Vector3::getZ() const
{
	return mZ;
}

inline Vector3 & Vector3::setW(float _w)
{
	mW = _w;
	return *this;
}

inline float Vector3::getW() const
{
	return mW;
}

inline Vector3 & Vector3::setElem(int idx, float value)
{
	*(&mX + idx) = value;
	return *this;
}

inline float Vector3::getElem(int idx) const
{
	return *(&mX + idx);
}

inline float & Vector3::operator[](int idx)
{
	return *(&mX + idx);
}

inline float Vector3::operator[](int idx) const
{
	return *(&mX + idx);
}

inline const Vector3 Vector3::operator + (const Vector3 & vec) const
{
	Vector3 res;
	vfpuAdd4(&mX, &vec.mX, &res.mX);
	return res;
}

inline const Vector3 Vector3::operator - (const Vector3 & vec) const
{
	Vector3 res;
	vfpuSub4(&mX, &vec.mX, &res.mX);
	return res;
}

inline const Point3 Vector3::operator + (const Point3 & pnt) const
{
	Point3 res;
	vfpuAdd4(&mX, &pnt.mX, &res.mX);
	return res;
}

inline const Vector3 Vector3::operator * (float scalar) const
{
	Vector3 res;
	vfpuScale4(&mX, &res.mX, scalar);
	return res;
}

inline Vector3 & Vector3::operator += (const Vector3 & vec)
{
	vfpuAdd4(&mX, &vec.mX, &mX);
	return *this;
}

inline Vector3 & Vector3::operator -= (const Vector3 & vec)
{
	vfpuSub4(&mX, &vec.mX, &mX);
	return *this;
}

inline Vector3 & Vector3::operator *= (float scalar)
{
	vfpuScale4(&mX, &mX, scalar);
	return *this;
}

inline const Vector3 Vector3::operator / (float scalar) const
{
	Vector3 res;
	vfpuScale4(&mX, &res.mX, 1.0f / scalar);
	return res;
}

inline Vector3 & Vector3::operator /= (float scalar)
{
	vfpuScale4(&mX, &mX, 1.0f / scalar);
	return *this;
}

inline const Vector3 Vector3::operator - () const
{
	Vector3 res;
	vfpuNeg4(&mX, &res.mX);
	return res;
}

inline const Vector3 operator * (float scalar, const Vector3 & vec)
{
	return vec * scalar;
}

inline const Vector3 mulPerElem(const Vector3 & vec0, const Vector3 & vec1)
{
	Vector3 res;
	vfpuMul4(&vec0.mX, &vec1.mX, &res.mX);
	return res;
}

inline const Vector3 divPerElem(const Vector3 & vec0, const Vector3 & vec1)
{
	Vector3 res;
	vfpuDiv4(&vec0.mX, &vec1.mX, &res.mX);
	return res;
}

inline const Vector3 recipPerElem(const Vector3 & vec)
{
	Vector3 res;
	vfpuReciprocal4(&vec.mX, &res.mX);
	return res;
}

inline const Vector3 sqrtPerElem(const Vector3 & vec)
{
	Vector3 res;
	vfpuSqrt4(&vec.mX, &res.mX);
	return res;
}

inline const Vector3 rsqrtPerElem(const Vector3 & vec)
{
	Vector3 res;
	vfpuReciprocalSqrt4(&vec.mX, &res.mX);
	return res;
}

inline const Vector3 absPerElem(const Vector3 & vec)
{
	Vector3 res;
	vfpuAbs4(&vec.mX, &res.mX);
	return res;
}

inline const Vector3 copySignPerElem(const Vector3 & vec0, const Vector3 & vec1)
{
	// TODO: implement in vfpu
	return Vector3((vec1.getX() < 0.0f) ? -std::fabsf(vec0.getX()) : std::fabsf(vec0.getX()),
				   (vec1.getY() < 0.0f) ? -std::fabsf(vec0.getY()) : std::fabsf(vec0.getY()),
				   (vec1.getZ() < 0.0f) ? -std::fabsf(vec0.getZ()) : std::fabsf(vec0.getZ()));
}

inline const Vector3 maxPerElem(const Vector3 & vec0, const Vector3 & vec1)
{
	Vector3 res;
	vfpuMax4v(&vec0.mX, &vec1.mX, &res.mX);
	return res;
}

inline float maxElem(const Vector3 & vec)
{
	return vfpuMax4f(&vec.mX);
}

inline const Vector3 minPerElem(const Vector3 & vec0, const Vector3 & vec1)
{
	Vector3 res;
	vfpuMin4v(&vec0.mX, &vec1.mX, &res.mX);
	return res;
}

inline float minElem(const Vector3 & vec)
{
	return vfpuMin4f(&vec.mX);
}

inline float sum(const Vector3 & vec)
{
	return vfpuSum4(&vec.mX);
}

inline float dot(const Vector3 & vec0, const Vector3 & vec1)
{
	return vfpuDot4(&vec0.mX, &vec1.mX);
}

inline float lengthSqr(const Vector3 & vec)
{
	return vfpuLengthSqr4(&vec.mX);
}

inline float length(const Vector3 & vec)
{
	return vfpuLength4(&vec.mX);
}

inline const Vector3 normalize(const Vector3 & vec)
{
	Vector3 res;
	vfpuNormalize4(&vec.mX, &res.mX);
	return res;
}

inline const Vector3 cross(const Vector3 & vec0, const Vector3 & vec1)
{
	Vector3 res;
	vfpuCross3(&vec0.mX, &vec1.mX, &res.mX);
	return res;
}

// NOTE(Mahmoud): why useless function ???????
inline const Vector3 select(const Vector3 & vec0, const Vector3 & vec1, bool select1)
{
	return select1 ? vec1 : vec0;
}

#ifdef VECTORMATH_DEBUG

inline void print(const Vector3 & vec)
{
	std::printf("( %f %f %f )\n", vec.getX(), vec.getY(), vec.getZ());
}

inline void print(const Vector3 & vec, const char * name)
{
	std::printf("%s: ( %f %f %f )\n", name, vec.getX(), vec.getY(), vec.getZ());
}

#endif // VECTORMATH_DEBUG

// LEFTOFF: continue Vector4

// ========================================================
// Vector4
// ========================================================

inline Vector4::Vector4(const Vector4 & vec)
{
	vfpuCopy4(&vec.mX, &mX);
}

inline Vector4::Vector4(float _x, float _y, float _z, float _w)
{
	mX = _x;
	mY = _y;
	mZ = _z;
	mW = _w;
}

inline Vector4::Vector4(const Vector3 & xyz, float _w)
{
	vfpuCopy4(&xyz.mX, &mX);
	mW = _w;
}

inline Vector4::Vector4(const Vector3 & vec)
{
	vfpuCopy4(&vec.mX, &mX);
	mW = 0.0f;
}

inline Vector4::Vector4(const Point3 & pnt)
{
	vfpuCopy4(&pnt.mX, &mX);
	mW = 1.0f;
}

inline Vector4::Vector4(const Quat & quat)
{
	vfpuCopy4(&quat.mX, &mX);
}

inline Vector4::Vector4(float scalar)
{
	vfpuReplicate4(scalar, &mX);
}

inline const Vector4 Vector4::xAxis()
{
	return Vector4(1.0f, 0.0f, 0.0f, 0.0f);
}

inline const Vector4 Vector4::yAxis()
{
	return Vector4(0.0f, 1.0f, 0.0f, 0.0f);
}

inline const Vector4 Vector4::zAxis()
{
	return Vector4(0.0f, 0.0f, 1.0f, 0.0f);
}

inline const Vector4 Vector4::wAxis()
{
	return Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}

inline const Vector4 lerp(float t, const Vector4 & vec0, const Vector4 & vec1)
{
	Vector4 res;
	vfpuLerp4(&vec0.mX, &vec1.mX, &res.mX, t);
	return res;
}

inline const Vector4 slerp(float t, const Vector4 & unitVec0, const Vector4 & unitVec1)
{
	// TODO: implement vfpu
	float recipSinAngle, scale0, scale1, cosAngle, angle;
	cosAngle = dot(unitVec0, unitVec1);
	if (cosAngle < VECTORMATH_SLERP_TOL)
	{
		angle = std::acosf(cosAngle);
		recipSinAngle = (1.0f / std::sinf(angle));
		scale0 = (std::sinf(((1.0f - t) * angle)) * recipSinAngle);
		scale1 = (std::sinf((t * angle)) * recipSinAngle);
	}
	else
	{
		scale0 = (1.0f - t);
		scale1 = t;
	}
	return ((unitVec0 * scale0) + (unitVec1 * scale1));
}

inline Vector4 & Vector4::operator = (const Vector4 & vec)
{
	vfpuCopy4(&vec.mX, &mX);
	return *this;
}

inline Vector4 & Vector4::setXYZ(const Vector3 & vec)
{
	float savedW = mW;
	vfpuCopy4(&vec.mX, &mX);
	mW = savedW;
	return *this;
}

inline const Vector3 Vector4::getXYZ() const
{
	return Vector3(mX, mY, mZ);
}

inline Vector4 & Vector4::setX(float _x)
{
	mX = _x;
	return *this;
}

inline float Vector4::getX() const
{
	return mX;
}

inline Vector4 & Vector4::setY(float _y)
{
	mY = _y;
	return *this;
}

inline float Vector4::getY() const
{
	return mY;
}

inline Vector4 & Vector4::setZ(float _z)
{
	mZ = _z;
	return *this;
}

inline float Vector4::getZ() const
{
	return mZ;
}

inline Vector4 & Vector4::setW(float _w)
{
	mW = _w;
	return *this;
}

inline float Vector4::getW() const
{
	return mW;
}

inline Vector4 & Vector4::setElem(int idx, float value)
{
	*(&mX + idx) = value;
	return *this;
}

inline float Vector4::getElem(int idx) const
{
	return *(&mX + idx);
}

inline float & Vector4::operator[](int idx)
{
	return *(&mX + idx);
}

inline float Vector4::operator[](int idx) const
{
	return *(&mX + idx);
}

inline const Vector4 Vector4::operator + (const Vector4 & vec) const
{
	Vector4 res;
	vfpuAdd4(&mX, &vec.mX, &res.mX);
	return res;
}

inline const Vector4 Vector4::operator - (const Vector4 & vec) const
{
	Vector4 res;
	vfpuSub4(&mX, &vec.mX, &res.mX);
	return res;
}

inline const Vector4 Vector4::operator * (float scalar) const
{
	Vector4 res;
	vfpuScale4(&mX, &res.mX, scalar);
	return res;
}

inline Vector4 & Vector4::operator += (const Vector4 & vec)
{
	vfpuAdd4(&mX, &vec.mX, &mX);
	return *this;
}

inline Vector4 & Vector4::operator -= (const Vector4 & vec)
{
	vfpuSub4(&mX, &vec.mX, &mX);
	return *this;
}

inline Vector4 & Vector4::operator *= (float scalar)
{
	vfpuScale4(&mX, &mX, scalar);
	return *this;
}

inline const Vector4 Vector4::operator / (float scalar) const
{
	Vector4 res;
	vfpuScale4(&mX, &res.mX, 1.0f / scalar);
	return res;
}

inline Vector4 & Vector4::operator /= (float scalar)
{
	vfpuScale4(&mX, &mX, 1.0f / scalar);
	return *this;
}

inline const Vector4 Vector4::operator - () const
{
	Vector4 res;
	vfpuNeg4(&mX, &res.mX);
	return res;
}

inline const Vector4 operator * (float scalar, const Vector4 & vec)
{
	return vec * scalar;
}

inline const Vector4 mulPerElem(const Vector4 & vec0, const Vector4 & vec1)
{
	Vector4 res;
	vfpuMul4(&vec0.mX, &vec1.mX, &res.mX);
	return res;
}

inline const Vector4 divPerElem(const Vector4 & vec0, const Vector4 & vec1)
{
	Vector4 res;
	vfpuDiv4(&vec0.mX, &vec1.mX, &res.mX);
	return res;
}

inline const Vector4 recipPerElem(const Vector4 & vec)
{
	Vector4 res;
	vfpuReciprocal4(&vec.mX, &res.mX);
	return res;
}

inline const Vector4 sqrtPerElem(const Vector4 & vec)
{
	Vector4 res;
	vfpuSqrt4(&vec.mX, &res.mX);
	return res;
}

inline const Vector4 rsqrtPerElem(const Vector4 & vec)
{
	Vector4 res;
	vfpuReciprocalSqrt4(&vec.mX, &res.mX);
	return res;
}

inline const Vector4 absPerElem(const Vector4 & vec)
{
	Vector4 res;
	vfpuAbs4(&vec.mX, &res.mX);
	return res;
}

inline const Vector4 copySignPerElem(const Vector4 & vec0, const Vector4 & vec1)
{
	// TODO: implement vfpu
	return Vector4((vec1.getX() < 0.0f) ? -std::fabsf(vec0.getX()) : std::fabsf(vec0.getX()),
				   (vec1.getY() < 0.0f) ? -std::fabsf(vec0.getY()) : std::fabsf(vec0.getY()),
				   (vec1.getZ() < 0.0f) ? -std::fabsf(vec0.getZ()) : std::fabsf(vec0.getZ()),
				   (vec1.getW() < 0.0f) ? -std::fabsf(vec0.getW()) : std::fabsf(vec0.getW()));
}

inline const Vector4 maxPerElem(const Vector4 & vec0, const Vector4 & vec1)
{
	Vector4 res;
	vfpuMax4v(&vec0.mX, &vec1.mX, &res.mX);
	return res;
}

inline float maxElem(const Vector4 & vec)
{
	return vfpuMax4f(&vec.mX);
}

inline const Vector4 minPerElem(const Vector4 & vec0, const Vector4 & vec1)
{
	Vector4 res;
	vfpuMin4v(&vec0.mX, &vec1.mX, &res.mX);
	return res;
}

inline float minElem(const Vector4 & vec)
{
	return vfpuMin4f(&vec.mX);
}

inline float sum(const Vector4 & vec)
{
	return vfpuSum4(&vec.mX);
}

inline float dot(const Vector4 & vec0, const Vector4 & vec1)
{
	return vfpuDot4(&vec0.mX, &vec1.mX);
}

inline float lengthSqr(const Vector4 & vec)
{
	return vfpuLengthSqr4(&vec.mX);
}

inline float length(const Vector4 & vec)
{
	return vfpuLength4(&vec.mX);
}

inline const Vector4 normalize(const Vector4 & vec)
{
	Vector4 res;
	vfpuNormalize4(&vec.mX, &res.mX);
	return res;
}

inline const Vector4 select(const Vector4 & vec0, const Vector4 & vec1, bool select1)
{
	return select1 ? vec1 : vec0;
}

#ifdef VECTORMATH_DEBUG

inline void print(const Vector4 & vec)
{
	std::printf("( %f %f %f %f )\n", vec.getX(), vec.getY(), vec.getZ(), vec.getW());
}

inline void print(const Vector4 & vec, const char * name)
{
	std::printf("%s: ( %f %f %f %f )\n", name, vec.getX(), vec.getY(), vec.getZ(), vec.getW());
}

#endif // VECTORMATH_DEBUG

// ========================================================
// Point3
// ========================================================

inline Point3::Point3(const Point3 & pnt)
{
	vfpuCopy4(&pnt.mX, &mX);
}

inline Point3::Point3(float _x, float _y, float _z)
{
	mX = _x;
	mY = _y;
	mZ = _z;
}

inline Point3::Point3(const Vector3 & vec)
{
	vfpuCopy4(&vec.mX, &mX);
}

inline Point3::Point3(float scalar)
{
	vfpuReplicate4(scalar, &mX);
}

inline const Point3 lerp(float t, const Point3 & pnt0, const Point3 & pnt1)
{
	Point3 res;
	vfpuLerp4(&pnt0.mX, &pnt1.mX, &res.mX, t);
	return res;
}

inline Point3 & Point3::operator = (const Point3 & pnt)
{
	vfpuCopy4(&pnt.mX, &mX);
	return *this;
}

inline Point3 & Point3::setX(float _x)
{
	mX = _x;
	return *this;
}

inline float Point3::getX() const
{
	return mX;
}

inline Point3 & Point3::setY(float _y)
{
	mY = _y;
	return *this;
}

inline float Point3::getY() const
{
	return mY;
}

inline Point3 & Point3::setZ(float _z)
{
	mZ = _z;
	return *this;
}

inline float Point3::getZ() const
{
	return mZ;
}

inline Point3 & Point3::setW(float _w)
{
	mW = _w;
	return *this;
}

inline float Point3::getW() const
{
	return mW;
}

inline Point3 & Point3::setElem(int idx, float value)
{
	*(&mX + idx) = value;
	return *this;
}

inline float Point3::getElem(int idx) const
{
	return *(&mX + idx);
}

inline float & Point3::operator[](int idx)
{
	return *(&mX + idx);
}

inline float Point3::operator[](int idx) const
{
	return *(&mX + idx);
}

inline const Vector3 Point3::operator - (const Point3 & pnt) const
{
	Vector3 res;
	vfpuSub4(&mX, &pnt.mX, &res.mX);
	return res;
}

inline const Point3 Point3::operator + (const Vector3 & vec) const
{
	Point3 res;
	vfpuAdd4(&mX, &vec.mX, &res.mX);
	return res;
}

inline const Point3 Point3::operator - (const Vector3 & vec) const
{
	Point3 res;
	vfpuSub4(&mX, &vec.mX, &res.mX);
	return res;
}

inline Point3 & Point3::operator += (const Vector3 & vec)
{
	vfpuAdd4(&mX, &vec.mX, &mX);
	return *this;
}

inline Point3 & Point3::operator -= (const Vector3 & vec)
{
	vfpuSub4(&mX, &vec.mX, &mX);
	return *this;
}

inline const Point3 mulPerElem(const Point3 & pnt0, const Point3 & pnt1)
{
	Point3 res;
	vfpuMul4(&pnt0.mX, &pnt1.mX, &res.mX);
	return res;
}

inline const Point3 divPerElem(const Point3 & pnt0, const Point3 & pnt1)
{
	Point3 res;
	vfpuDiv4(&pnt0.mX, &pnt1.mX, &res.mX);
	return res;
}

inline const Point3 recipPerElem(const Point3 & pnt)
{
	Point3 res;
	vfpuReciprocal4(&pnt.mX, &res.mX);
	return res;
}

inline const Point3 sqrtPerElem(const Point3 & pnt)
{
	Point3 res;
	vfpuSqrt4(&pnt.mX, &res.mX);
	return res;
}

inline const Point3 rsqrtPerElem(const Point3 & pnt)
{
	Point3 res;
	vfpuReciprocalSqrt4(&pnt.mX, &res.mX);
	return res;
}

inline const Point3 absPerElem(const Point3 & pnt)
{
	Point3 res;
	vfpuAbs4(&pnt.mX, &res.mX);
	return res;
}

inline const Point3 copySignPerElem(const Point3 & pnt0, const Point3 & pnt1)
{
	// TODO: implement in vfpu
	return Point3((pnt1.getX() < 0.0f) ? -std::fabsf(pnt0.getX()) : std::fabsf(pnt0.getX()),
				   (pnt1.getY() < 0.0f) ? -std::fabsf(pnt0.getY()) : std::fabsf(pnt0.getY()),
				   (pnt1.getZ() < 0.0f) ? -std::fabsf(pnt0.getZ()) : std::fabsf(pnt0.getZ()));
}

inline const Point3 maxPerElem(const Point3 & pnt0, const Point3 & pnt1)
{
	Point3 res;
	vfpuMax4v(&pnt0.mX, &pnt1.mX, &res.mX);
	return res;
}

inline float maxElem(const Point3 & pnt)
{
	return vfpuMax4f(&pnt.mX);
}

inline const Point3 minPerElem(const Point3 & pnt0, const Point3 & pnt1)
{
	Point3 res;
	vfpuMin4v(&pnt0.mX, &pnt1.mX, &res.mX);
	return res;
}

inline float minElem(const Point3 & pnt)
{
	return vfpuMin4f(&pnt.mX);
}

inline float sum(const Point3 & pnt)
{
	return vfpuSum4(&pnt.mX);
}

inline const Point3 scale(const Point3 & pnt, float scaleVal)
{
	Point3 res;
	vfpuScale4(&pnt.mX, &res.mX, scaleVal);
	return res;
}

inline const Point3 scale(const Point3 & pnt, const Vector3 & scaleVec)
{
	Point3 res;
	vfpuMul4(&pnt.mX, &scaleVec.mX, &res.mX);
	return res;
}

inline float projection(const Point3 & pnt, const Vector3 & unitVec)
{
	return vfpuProjection4(&pnt.mX, &unitVec.mX);
}

inline float distSqrFromOrigin(const Point3 & pnt)
{
	return vfpuLengthSqr4(&pnt.mX);
}

inline float distFromOrigin(const Point3 & pnt)
{
	return vfpuLength4(&pnt.mX);
}

inline float distSqr(const Point3 & pnt0, const Point3 & pnt1)
{
	Vector3 diff = pnt1 - pnt0;
	return vfpuLengthSqr4(&diff.mX);
}

inline float dist(const Point3 & pnt0, const Point3 & pnt1)
{
	Vector3 diff = pnt1 - pnt0;
	return vfpuLength4(&diff.mX);
}

inline const Point3 select(const Point3 & pnt0, const Point3 & pnt1, bool select1)
{
	return select1 ? pnt1 : pnt0;
}

#ifdef VECTORMATH_DEBUG

inline void print(const Point3 & pnt)
{
	std::printf("( %f %f %f )\n", pnt.getX(), pnt.getY(), pnt.getZ());
}

inline void print(const Point3 & pnt, const char * name)
{
	std::printf("%s: ( %f %f %f )\n", name, pnt.getX(), pnt.getY(), pnt.getZ());
}

#endif // VECTORMATH_DEBUG

} // namespace VFPU
} // namespace Vectormath

#endif // VECTORMATH_VFPU_VECTOR_HPP
