	.set		noreorder

	# TODO: DOCUMENT THIS CODE
	# TODO: utilize branch delay slots



	###########################################
	###########################################
	#	VECTOR & POINT FUNCTIONS
	###########################################
	###########################################


	# void vfpuCopy4(const float inVec[4], float ioVec[4]);
	.ent		vfpuCopy4
	.global		vfpuCopy4
vfpuCopy4:
	lv.q		C000, 0($a0)
	sv.q		C000, 0($a1)
	jr			$ra
	nop
	.end		vfpuCopy4


	# void vfpuReplicate4(float inScalar, float ioVec[4]);
	.ent		vfpuReplicate4
	.global		vfpuReplicate4
vfpuReplicate4:
	# TODO:	maybe vmov.s is faster than mtv. profile this
	#		or vmov.q with swizzle .xxxx prefix
	mfc1		$t0, $f12
	mtv			$t0, S000
	mtv			$t0, S001
	mtv			$t0, S002
	mtv			$t0, S003
	sv.q		C000, 0($a1)
	jr			$ra
	nop
	.end		vfpuReplicate4


	# void vfpuAdd4(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	.ent		vfpuAdd4
	.global		vfpuAdd4
vfpuAdd4:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vadd.q		C000, C000, C010
	sv.q		C000, 0($a2)
	jr			$ra
	nop
	.end		vfpuAdd4


	# void vfpuSub4(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	.ent		vfpuSub4
	.global		vfpuSub4
vfpuSub4:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vsub.q		C000, C000, C010
	sv.q		C000, 0($a2)
	jr			$ra
	nop
	.end		vfpuSub4

	
	# void vfpuMul4(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	.ent		vfpuMul4
	.global		vfpuMul4
vfpuMul4:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vmul.q		C000, C000, C010
	sv.q		C000, 0($a2)
	jr			$ra
	nop
	.end		vfpuMul4

	
	# void vfpuDiv4(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	.ent		vfpuDiv4
	.global		vfpuDiv4
vfpuDiv4:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vdiv.q		C000, C000, C010
	sv.q		C000, 0($a2)
	jr			$ra
	nop
	.end		vfpuDiv4


	# void vfpuScale4(const float inVec[4], float ioVec[4], float inScalar);
	.ent		vfpuScale4
	.global		vfpuScale4
vfpuScale4:
	lv.q		C000, 0($a0)
	mfc1		$t0, $f12
	mtv			$t0, S010
	vscl.q		C000, C000, S010
	sv.q		C000, 0($a1)
	jr			$ra
	nop
	.end		vfpuScale4


	# void vfpuNeg4(const float inVec[4], float ioVec[4]);
	.ent		vfpuNeg4
	.global		vfpuNeg4
vfpuNeg4:
	lv.q		C000, 0($a0)
	vneg.q		C000, C000
	sv.q		C000, 0($a1)
	jr			$ra
	nop
	.end		vfpuNeg4


	# void vfpuReciprocal4(const float inVec[4], float ioVec[4]);
	.ent		vfpuReciprocal4
	.global		vfpuReciprocal4
vfpuReciprocal4:
	lv.q		C000, 0($a0)
	vrcp.q		C000, C000
	sv.q		C000, 0($a1)
	jr			$ra
	nop
	.end		vfpuReciprocal4


	# void vfpuSqrt4(const float inVec[4], float ioVec[4]);
	.ent		vfpuSqrt4
	.global		vfpuSqrt4
vfpuSqrt4:
	lv.q		C000, 0($a0)
	vsqrt.q		C000, C000
	sv.q		C000, 0($a1)
	jr			$ra
	nop
	.end		vfpuSqrt4


	# void vfpuReciprocalSqrt4(const float inVec[4], float ioVec[4]);
	.ent		vfpuReciprocalSqrt4
	.global		vfpuReciprocalSqrt4
vfpuReciprocalSqrt4:
	lv.q		C000, 0($a0)
	vrsq.q		C000, C000
	sv.q		C000, 0($a1)
	jr			$ra
	nop
	.end		vfpuReciprocalSqrt4


	# void vfpuAbs4(const float inVec[4], float ioVec[4]);
	.ent		vfpuAbs4
	.global		vfpuAbs4
vfpuAbs4:
	lv.q		C000, 0($a0)
	vabs.q		C000, C000
	sv.q		C000, 0($a1)
	jr			$ra
	nop
	.end		vfpuAbs4


	# void vfpuMax4v(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	.ent		vfpuMax4v
	.global		vfpuMax4v
vfpuMax4v:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vmax.q		C000, C000, C010
	sv.q		C000, 0($a2)
	jr			$ra
	nop
	.end		vfpuMax4v


	# float vfpuMax4f(const float inVec[4]);
	.ent		vfpuMax4f
	.global		vfpuMax4f
vfpuMax4f:
	lv.q		C000, 0($a0)
	vmax.s		S010, S000, S001
	vmax.s		S011, S002, S003
	vmax.s		S000, S010, S011
	mfv			$t0, S000
	mtc1		$t0, $f0
	jr			$ra
	nop
	.end		vfpuMax4f


	# void vfpuMin4v(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	.ent		vfpuMin4v
	.global		vfpuMin4v
vfpuMin4v:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vmin.q		C000, C000, C010
	sv.q		C000, 0($a2)
	jr			$ra
	nop
	.end		vfpuMin4v


	# float vfpuMin4f(const float inVec[4]);
	.ent		vfpuMin4f
	.global		vfpuMin4f
vfpuMin4f:
	lv.q		C000, 0($a0)
	vmin.s		S010, S000, S001
	vmin.s		S011, S002, S003
	vmin.s		S000, S010, S011
	mfv			$t0, S000
	mtc1		$t0, $f0
	jr			$ra
	nop
	.end		vfpuMin4f


	# float vfpuSum4(const float inVec[4]);
	.ent		vfpuSum4
	.global		vfpuSum4
vfpuSum4:
	lv.q		C000, 0($a0)
	vfad.q		S010, C000
	mfv			$t0, S010
	mtc1		$t0, $f0
	jr			$ra
	nop
	.end		vfpuSum4


	# float vfpuDot4(const float inVecA[4], const float inVecB[4]);
	.ent		vfpuDot4
	.global		vfpuDot4
vfpuDot4:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vdot.q		S020, C000, C010
	mfv			$t0, S020
	mtc1		$t0, $f0
	jr			$ra
	nop
	.end		vfpuDot4


	# float vfpuLengthSqr4(const float inVec[4])
	.ent		vfpuLengthSqr4
	.global		vfpuLengthSqr4
vfpuLengthSqr4:
	lv.q		C000, 0($a0)
	vdot.q		S000, C000, C000
	mfv			$t0, S000
	mtc1		$t0, $f0
	jr			$ra
	nop
	.end		vfpuLengthSqr4


	# float vfpuLength4(const float inVec[4])
	.ent		vfpuLength4
	.global		vfpuLength4
vfpuLength4:
	lv.q		C000, 0($a0)
	vdot.q		S000, C000, C000
	vsqrt.s		S000, S000
	mfv			$t0, S000
	mtc1		$t0, $f0
	jr			$ra
	nop
	.end		vfpuLength4


	# void vfpuNormalize4(const float inVec[4], float ioVec[4]);
	.ent		vfpuNormalize4
	.global		vfpuNormalize4
vfpuNormalize4:
	lv.q		C000, 0($a0)
	vmov.q		C010, C000
	vdot.q		S000, C000, C000
	vrsq.s		S000, S000
	vscl.q		C010, C010, S000
	sv.q		C010, 0($a1)
	jr			$ra
	nop
	.end		vfpuNormalize4


	# void vfpuLerp4(const float inVecA[4], const float inVecB[4], float ioVec[4], float inT);
	.ent		vfpuLerp4
	.global		vfpuLerp4
vfpuLerp4:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	mfc1		$t0, $f12
	mtv			$t0, S100
	vocp.s		S101, S100			# S100 = t, S101 = 1-t
	vscl.q		C000, C000, S101
	vscl.q		C010, C010, S100
	vadd.q		C000, C000, C010
	sv.q		C000, 0($a2)
	jr			$ra
	nop
	.end		vfpuLerp4


	# void vfpuCross3(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	.ent		vfpuCross3
	.global		vfpuCross3
vfpuCross3:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vcrsp.t		C020, C000, C010
	sv.q		C020, 0($a2)
	jr			$ra
	nop
	.end		vfpuCross3


	# float vfpuProjection4(const float inPnt[4], const float inUnitVec[4]);
	.ent		vfpuProjection4
	.global		vfpuProjection4
vfpuProjection4:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vdot.q		S000, C000, C010
	mfv			$t0, S000
	mtc1		$t0, $f0
	jr			$ra
	nop
	.end		vfpuProjection4



	###########################################
	###########################################
	#	MATRIX FUNCTIONS
	###########################################
	###########################################


	# void vfpuCopy9(const float inMat[9], float ioMat[9]);
	.ent		vfpuCopy9
	.global		vfpuCopy9
vfpuCopy9:
	lv.q		C000, 0($a0)
	lv.q		C010, 16($a0)
	lv.q		C020, 32($a0)
	sv.q		C000, 0($a1)
	sv.q		C010, 16($a1)
	sv.q		C020, 32($a1)
	jr			$ra
	nop
	.end		vfpuCopy9


	# void vfpuCopy16(const float inMat[16], float ioMat[16]);
	.ent		vfpuCopy16
	.global		vfpuCopy16
vfpuCopy16:
	lv.q		C000, 0($a0)
	lv.q		C010, 16($a0)
	lv.q		C020, 32($a0)
	lv.q		C030, 48($a0)
	sv.q		C000, 0($a1)
	sv.q		C010, 16($a1)
	sv.q		C020, 32($a1)
	sv.q		C030, 48($a1)
	jr			$ra
	nop
	.end		vfpuCopy16


	# TODO:	optimize this for matrices or change the code that uses
	#		it to use multiple vfpuReplicate4
	# void vfpuReplicate9(float inScalar, float ioMat[9]);
	.ent		vfpuReplicate9
	.global		vfpuReplicate9
vfpuReplicate9:
	# TODO: maybe vmov.s is faster than mtv. profile this
	# or vmov.q with swizzle .xxxx prefix
	mfc1		$t0, $f12
	mtv			$t0, S000
	mtv			$t0, S001
	mtv			$t0, S002
	vmov.t		C010, C000
	vmov.t		C020, C000
	sv.q		C000, 0($a1)
	sv.q		C010, 16($a1)
	sv.q		C020, 32($a1)
	jr			$ra
	nop
	.end		vfpuReplicate9


	# TODO:	optimize this for matrices or change the code that uses
	#		it to use multiple vfpuReplicate4
	# void vfpuReplicate16(float inScalar, float ioVec[4]);
	.ent		vfpuReplicate16
	.global		vfpuReplicate16
vfpuReplicate16:
	# TODO: maybe vmov.s is faster than mtv. profile this
	# or vmov.q with swizzle .xxxx prefix
	mfc1		$t0, $f12
	mtv			$t0, S000
	mtv			$t0, S001
	mtv			$t0, S002
	vmov.t		C010, C000
	vmov.t		C020, C000
	vmov.t		C020, C000
	sv.q		C000, 0($a1)
	sv.q		C010, 16($a1)
	sv.q		C020, 32($a1)
	sv.q		C030, 48($a1)
	jr			$ra
	nop
	.end		vfpuReplicate16


	# NOTE: see vfpuCopy16
	# void vfpuTranspose9(const float inMat[9], const float ioMat[9]);
	.ent		vfpuTranspose9
	.global		vfpuTranspose9
vfpuTranspose9:
	lv.q		C000, 0($a0)
	lv.q		C010, 16($a0)
	lv.q		C020, 32($a0)
	sv.q		R000, 0($a1)
	sv.q		R001, 16($a1)
	sv.q		R002, 32($a1)
	jr			$ra
	nop
	.end		vfpuTranspose9


	# NOTE: see vfpuCopy16
	# void vfpuTranspose16(const float inMat[16], const float ioMat[16]);
	.ent		vfpuTranspose16
	.global		vfpuTranspose16
vfpuTranspose16:
	lv.q		C000, 0($a0)
	lv.q		C010, 16($a0)
	lv.q		C020, 32($a0)
	lv.q		C030, 48($a0)
	sv.q		R000, 0($a1)
	sv.q		R001, 16($a1)
	sv.q		R002, 32($a1)
	sv.q		R003, 48($a1)
	jr			$ra
	nop
	.end		vfpuTranspose16


	# void vfpuIdentity9(float ioMat[9]);
	.ent		vfpuIdentity9
	.global		vfpuIdentity9
vfpuIdentity9:
	vmidt.t		E000
	sv.q		C000, 0($a0)
	sv.q		C010, 16($a0)
	sv.q		C020, 32($a0)
	jr			$ra
	nop
	.end		vfpuIdentity9


	# void vfpuIdentity16(float ioMat[16]);
	.ent		vfpuIdentity16
	.global		vfpuIdentity16
vfpuIdentity16:
	vmidt.q		E000
	sv.q		C000, 0($a0)
	sv.q		C010, 16($a0)
	sv.q		C020, 32($a0)
	sv.q		C030, 48($a0)
	jr			$ra
	nop
	.end		vfpuIdentity16


	# void vfpuInverse9(const float inMat[9], float ioMat[9]);
	.ent		vfpuInverse9
	.global		vfpuInverse9
vfpuInverse9:
	lv.q		C000, 0($a0)
	lv.q		C010, 16($a0)
	lv.q		C020, 32($a0)
	vcrsp.t		C100, C010, C020
	vcrsp.t		C110, C020, C000
	vcrsp.t		C120, C000, C010
	vdot.t		S300, C020, C120
	vrcp.s		S300, S300
	vscl.t		C000, C100, S300
	vscl.t		C010, C110, S300
	vscl.t		C020, C120, S300
	sv.q		R000, 0($a1)
	sv.q		R001, 16($a1)
	sv.q		R002, 32($a1)
	jr			$ra
	nop
	.end		vfpuInverse9


	# void vfpuScale9(const float inMat[9], float ioMat[9], float inScalar);
	.ent		vfpuScale9
	.global		vfpuScale9
vfpuScale9:
	mfc1		$t0, $f12
	mtv			$t0, S100
	lv.q		C000, 0($a0)
	lv.q		C010, 16($a0)
	lv.q		C020, 32($a0)
	vmscl.t		E000, E000, S100
	sv.q		C000, 0($a1)
	sv.q		C010, 16($a1)
	sv.q		C020, 32($a1)
	jr			$ra
	nop
	.end		vfpuScale9


	# float vfpuDeterminant3(const float inMat[9]);
	.ent		vfpuDeterminant3
	.global		vfpuDeterminant3
vfpuDeterminant3:
	lv.q		C000, 0($a0)
	lv.q		C010, 16($a0)
	lv.q		C020, 32($a0)
	vcrsp.t		C100, C000, C010
	vdot.t		S200, C020, C100
	mfv			$t0, S200
	mtc1		$t0, $f0
	jr			$ra
	nop
	.end		vfpuDeterminant3


	# void vfpuMulMat3Vec3(const float inMat[9], const float inVec[4], float ioVec[4]);
	.ent		vfpuMulMat3Vec3
	.global		vfpuMulMat3Vec3
vfpuMulMat3Vec3:
	lv.q		C000, 0($a0)
	lv.q		C010, 16($a0)
	lv.q		C020, 32($a0)
	lv.q		C030, 0($a1)
	vtfm4.q		C100, E000, C030
	sv.q		C100, 0($a2)
	jr			$ra
	nop
	.end		vfpuMulMat3Vec3


	# void vfpuMulMat3Mat3(const float inMatA[9], const float inMatB[9], float ioMat[9]);
	.ent		vfpuMulMat3Mat3
	.global		vfpuMulMat3Mat3
vfpuMulMat3Mat3:
	lv.q		C000, 0($a0)
	lv.q		C010, 16($a0)
	lv.q		C020, 32($a0)
	lv.q		C030, 48($a0)
	lv.q		C100, 0($a1)
	lv.q		C110, 16($a1)
	lv.q		C120, 32($a1)
	lv.q		C130, 48($a1)
	vmmul.t		E200, E000, E100
	sv.q		C200, 0($a2)
	sv.q		C200, 16($a2)
	sv.q		C200, 32($a2)
	sv.q		C200, 48($a2)
	jr			$ra
	nop
	.end		vfpuMulMat3Mat3

	###########################################
	###########################################
	#	QUATERNION FUNCTIONS
	###########################################
	###########################################

	# coming soon ...
