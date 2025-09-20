/// @file extern stubs for vfpu.s

// TODO: if it positively effects performance: write 3 element functions for Vector3

extern "C"
{
	extern void		vfpuCopy4v(const float inVec[4], float ioVec[4]);
	extern void		vfpuReplicate4(float inScalar, float ioVec[4]);

	extern void		vfpuAdd4(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	extern void		vfpuSub4(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	extern void		vfpuMul4(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	extern void		vfpuDiv4(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	extern void		vfpuScale4(const float inVec[4], float ioVec[4], float inScalar);

	extern void		vfpuNeg4(const float inVec[4], float ioVec[4]);
	extern void		vfpuReciprocal4(const float inVec[4], float ioVec[4]);
	extern void		vfpuSqrt4(const float inVec[4], float ioVec[4]);
	extern void		vfpuReciprocalSqrt4(const float inVec[4], float ioVec[4]);
	extern void		vfpuAbs4(const float inVec[4], float ioVec[4]);
	extern void		vfpuMax4v(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	extern float	vfpuMax4f(const float inVec[4]);
	extern void		vfpuMin4v(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	extern float	vfpuMin4f(const float inVec[4]);
	extern float	vfpuSum4(const float inVec[4]);

	extern float	vfpuDot4(const float inVecA[4], const float inVecB[4]);
	extern void		vfpuCross3(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	extern float	vfpuLengthSqr4(const float inVec[4]);
	extern float	vfpuLength4(const float inVec[4]);
	extern float	vfpuNormalize4(const float inVec[4], float ioVec[4]);

	extern void		vfpuLerp4(const float inVecA[4], const float inVecB[4], float ioVec[4], float inT);
	extern float	vfpuProjection4(const float inPnt[4], const float inUnitVec[4]);
}
