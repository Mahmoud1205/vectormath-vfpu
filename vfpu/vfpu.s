	.set noreorder

	# TODO: DOCUMENT THIS CODE


	# void vfpuCopy4v(const float inVec[4], float ioVec[4]);
	.global vfpuCopy4v
vfpuCopy4v:
	lv.q		C000, 0($a0)
	sv.q		C000, 0($a1)
	jr			$ra
	nop


	# void vfpuReplicate4(float inScalar, float ioVec[4]);
	.global vfpuReplicate4
vfpuReplicate4:
	mfc1		$t0, $f12
	mtv			$t0, S000
	mtv			$t0, S001
	mtv			$t0, S002
	mtv			$t0, S003
	sv.q		C000, 0($a1)
	jr			$ra
	nop


	# void vfpuAdd4(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	.global vfpuAdd4
vfpuAdd4:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vadd.q		C000, C000, C010
	sv.q		C000, 0($a2)
	jr			$ra
	nop


	# void vfpuSub4(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	.global vfpuSub4
vfpuSub4:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vsub.q		C000, C000, C010
	sv.q		C000, 0($a2)
	jr			$ra
	nop

	
	# void vfpuMul4(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	.global vfpuMul4
vfpuMul4:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vmul.q		C000, C000, C010
	sv.q		C000, 0($a2)
	jr			$ra
	nop

	
	# void vfpuDiv4(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	.global vfpuDiv4
vfpuDiv4:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vdiv.q		C000, C000, C010
	sv.q		C000, 0($a2)
	jr			$ra
	nop


	# void vfpuScale4(const float inVec[4], float ioVec[4], float inScalar);
	.global vfpuScale4
vfpuScale4:
	lv.q		C000, 0($a0)
	mfc1		$t0, $f12
	mtv			$t0, S010
	vscl.q		C000, C000, S010
	sv.q		C000, 0($a1)
	jr			$ra
	nop


	# void vfpuNeg4(const float inVec[4], float ioVec[4]);
	.global vfpuNeg4
vfpuNeg4:
	lv.q		C000, 0($a0)
	vneg.q		C000, C000
	sv.q		C000, 0($a1)
	jr			$ra
	nop


	# void vfpuReciprocal4(const float inVec[4], float ioVec[4]);
	.global vfpuReciprocal4
vfpuReciprocal4:
	lv.q		C000, 0($a0)
	vrcp.q		C000, C000
	sv.q		C000, 0($a1)
	jr			$ra
	nop


	# void vfpuSqrt4(const float inVec[4], float ioVec[4]);
	.global vfpuSqrt4
vfpuSqrt4:
	lv.q		C000, 0($a0)
	vsqrt.q		C000, C000
	sv.q		C000, 0($a1)
	jr			$ra
	nop


	# void vfpuReciprocalSqrt4(const float inVec[4], float ioVec[4]);
	.global vfpuReciprocalSqrt4
vfpuReciprocalSqrt4:
	lv.q		C000, 0($a0)
	vrsq.q		C000, C000
	sv.q		C000, 0($a1)
	jr			$ra
	nop


	# void vfpuAbs4(const float inVec[4], float ioVec[4]);
	.global vfpuAbs4
vfpuAbs4:
	lv.q		C000, 0($a0)
	vabs.q		C000, C000
	sv.q		C000, 0($a1)
	jr			$ra
	nop


	# void vfpuMax4v(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	.global vfpuMax4v
vfpuMax4v:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vmax.q		C000, C000, C010
	sv.q		C000, 0($a2)
	jr			$ra
	nop


	# float vfpuMax4f(const float inVec[4]);
	.global vfpuMax4f
vfpuMax4f:
	lv.q		C000, 0($a0)
	vmax.s		S010, S000, S001
	vmax.s		S011, S002, S003
	vmax.s		S000, S010, S011
	mfv			$t0, S000
	mtc1		$t0, $f0
	jr			$ra
	nop


	# void vfpuMin4v(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	.global vfpuMin4v
vfpuMin4v:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vmin.q		C000, C000, C010
	sv.q		C000, 0($a2)
	jr			$ra
	nop


	# float vfpuMin4f(const float inVec[4]);
	.global vfpuMin4f
vfpuMin4f:
	lv.q		C000, 0($a0)
	vmin.s		S010, S000, S001
	vmin.s		S011, S002, S003
	vmin.s		S000, S010, S011
	mfv			$t0, S000
	mtc1		$t0, $f0
	jr			$ra
	nop


	# float vfpuSum4(const float inVec[4]);
	.global vfpuSum4
vfpuSum4:
	lv.q		C000, 0($a0)
	vfad.q		S010, C000
	mfv			$t0, S000
	mtc1		$t0, $f0
	jr			$ra
	nop


	# float vfpuDot4(const float inVecA[4], const float inVecB[4]);
	.global vfpuDot4
vfpuDot4:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vdot.q		S020, C000, C010
	mfv			$t0, S020
	mtc1		$t0, $f0
	jr			$ra
	nop


	# float vfpuLengthSqr4(const float inVec[4])
	.global vfpuLengthSqr4
vfpuLengthSqr4:
	lv.q		C000, 0($a0)
	vmul.q		C000, C000, C000
	vfad.q		S000, C000
	mfv			$t0, S000
	mtc1		$t0, $f0
	jr			$ra
	nop


	# float vfpuLength4(const float inVec[4])
	.global vfpuLength4
vfpuLength4:
	lv.q		C000, 0($a0)
	vmul.q		C000, C000, C000
	vfad.q		S000, C000
	vsqrt.s		S000, S000
	mfv			$t0, S000
	mtc1		$t0, $f0
	jr			$ra
	nop


	# void vfpuNormalize4(const float inVec[4], float ioVec[4]);
	.global vfpuNormalize4
vfpuNormalize4:
	lv.q		C000, 0($a0)
	vmov.q		C010, C000
	vmul.q		C000, C000, C000
	vfad.q		S000, C000
	vrsq.s		S000, S000
	vscl.q		C010, C010, S000
	sv.q		C010, 0($a1)
	jr			$ra
	nop


	# void vfpuLerp4(const float inVecA[4], const float inVecB[4], float ioVec[4], float inT);
	.global vfpuLerp4
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


	# void vfpuCross3(const float inVecA[4], const float inVecB[4], float ioVec[4]);
	.global vfpuCross3
vfpuCross3:
	lv.q		C000, 0($a0)
	lv.q		C010, 0($a1)
	vcrsp.t		C020, C000, C010
	sv.q		C020, 0($a2)
	jr			$ra
	nop
