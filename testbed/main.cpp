#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <psprtc.h>
#include <pspctrl.h>

#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

PSP_MODULE_INFO("VectorMath VFPU", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU);

int exit_callback(int arg1, int arg2, void *common) {
	sceKernelExitGame();
	return 0;
}

int callback_thread(SceSize args, void *argp) {
	int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();
	return 0;
}

int setup_callbacks(void) {
	int thid = sceKernelCreateThread("update_thread", callback_thread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
		sceKernelStartThread(thid, 0, 0);
	return thid;
}

void pspDebugScreenPutsCorrect(const char* inText)
{
	pspDebugScreenPuts(inText);
	pspDebugScreenPuts("\n");
}

// emulate \r functionality cuz it's not supported
void pspDebugScreenCarriageReturn()
{
	int y = pspDebugScreenGetY() - 1;
	pspDebugScreenSetXY(0, y);
}

void waitForBtn()
{
	// wait for 250ms until the last button was released
	sceKernelDelayThread(250 * 1000);
	for (;;)
	{
		SceCtrlData ctrl;
		sceCtrlReadBufferPositive(&ctrl, 1);
		if (ctrl.Buttons)
			break;
	}
}

#define puts pspDebugScreenPutsCorrect
#define printf pspDebugScreenPrintf
#define DBREAK() asm volatile("break")

class PspTestListener : public testing::EmptyTestEventListener
{
public:
	void OnTestProgramStart(const testing::UnitTest& inUT) override
	{
		puts("====== VectorMath VFPU Test ======");
		puts("Press any button to start testing..\n");
		waitForBtn();
	};

	void OnTestStart(const testing::TestInfo& inTI) override
	{
		pspDebugScreenSetTextColor(0xFFFFFF);
		printf("[ TEST: .... ] %s.%s\n", inTI.test_suite_name(), inTI.name());
	}

	void OnTestPartResult(const testing::TestPartResult& inRes) override
	{
		if (inRes.failed())
		{
			pspDebugScreenSetTextColor(0x0000FF);
			pspDebugScreenCarriageReturn();
			printf("[ TEST: FAIL ]\n");
			printf("[  FAILED   ] %s:%d: %s\n",
				inRes.file_name(),
				inRes.line_number(),
				inRes.summary());
		}
	}

	void OnTestEnd(const testing::TestInfo& inTI) override
	{
		if (inTI.result()->Passed())
		{
			pspDebugScreenSetTextColor(0x00FF00);
			pspDebugScreenCarriageReturn();
			printf("[ TEST: PASS ]\n", inTI.test_suite_name(), inTI.name());
		}
	}

	void OnTestProgramEnd(const testing::UnitTest& inUT) override
	{
		u32 testColor, perfRatioColor;
		if (inUT.failed_test_count() == 0)
			testColor = 0x00FF00;
		else
			testColor = 0x0000FF;

		float scalarVfpuRatio = sScalarTime / sVfpuTime;

		if (scalarVfpuRatio > 1.0f)
			perfRatioColor = 0x00FF00;
		else
			perfRatioColor = 0x0000FF;

		pspDebugScreenSetTextColor(0xFFFFFF);
		printf("\n=== VectorMath VFPU Test [END] ===\n");
		pspDebugScreenSetTextColor(testColor);
		printf("  * %d/%d tests passed.\n", inUT.successful_test_count(), inUT.test_to_run_count());
		pspDebugScreenSetTextColor(perfRatioColor);
		printf("  * Scalar:VFPU Performance Ratio: %.3f (%.3fus/%.3fus)\n\n", scalarVfpuRatio, sScalarTime, sVfpuTime);
		pspDebugScreenSetTextColor(0xFFFFFF);
	}

	inline static float sScalarTime = 0.0f;
	inline static float sVfpuTime = 0.0f;
};

// gtest doesn't link without these stubs
extern "C" int dup(int inFD) { return inFD; }
extern "C" int dup2(int, int inNewFD) { return inNewFD; }

void runTests();

int main(int argc, char** argv)
{
	setup_callbacks();

	pspDebugScreenInit();
	pspDebugScreenSetXY(0, 0);

	testing::InitGoogleTest(&argc, argv);
	testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
	listeners.Append(new PspTestListener());

	int res = RUN_ALL_TESTS();

	printf("Test program exited with code %d. Press any button to exit..\n", res);
	waitForBtn();

	sceKernelExitGame();
	return 0;
}

#include <scalar/vectormath.hpp>
#include <vfpu/vectormath.hpp>
using namespace Vectormath;

#define VMTEST(inTestName) TEST(VectorMath, inTestName)

#define EXPECT_FLOAT_EQ(inA, inB) EXPECT_NEAR(inA, inB, 1e-5)

#define EXPECT_VEC3_EQ(inA, inB)				\
	EXPECT_FLOAT_EQ(inA.getX(), inB.getX());	\
	EXPECT_FLOAT_EQ(inA.getY(), inB.getY());	\
	EXPECT_FLOAT_EQ(inA.getZ(), inB.getZ());

#define EXPECT_VEC4_EQ(inA, inB)				\
	EXPECT_FLOAT_EQ(inA.getX(), inB.getX());	\
	EXPECT_FLOAT_EQ(inA.getY(), inB.getY());	\
	EXPECT_FLOAT_EQ(inA.getZ(), inB.getZ());	\
	EXPECT_FLOAT_EQ(inA.getW(), inB.getW());

/**
 * ======================================================================
 * ======================================================================
 * =====						TESTS								=====
 * ======================================================================
 * ======================================================================
 */

VMTEST(VectorAddition)
{
	Scalar::Vector3 sA(1.0f, 1.0f, 1.0f);
	Scalar::Vector3 sB(1.0f, 1.0f, 1.0f);
	Scalar::Vector3 sC = sA + sB;

	VFPU::Vector3 vA(1.0f, 1.0f, 1.0f);
	VFPU::Vector3 vB(1.0f, 1.0f, 1.0f);
	VFPU::Vector3 vC = vA + vB;

	EXPECT_VEC3_EQ(sC, vC);
}

VMTEST(VectorSubtraction)
{
	Scalar::Vector3 sA(2.0f, 2.0f, 2.0f);
	Scalar::Vector3 sB(1.0f, 1.0f, 1.0f);
	Scalar::Vector3 sC = sA - sB;

	VFPU::Vector3 vA(2.0f, 2.0f, 2.0f);
	VFPU::Vector3 vB(1.0f, 1.0f, 1.0f);
	VFPU::Vector3 vC = vA - vB;

	EXPECT_VEC3_EQ(sC, vC);
}

VMTEST(VectorVectorMultiplication)
{
	Scalar::Vector3 sA(2.0f, 2.0f, 2.0f);
	Scalar::Vector3 sB(2.0f, 2.0f, 2.0f);
	Scalar::Vector3 sC = Scalar::mulPerElem(sA, sB);

	VFPU::Vector3 vA(2.0f, 2.0f, 2.0f);
	VFPU::Vector3 vB(2.0f, 2.0f, 2.0f);
	VFPU::Vector3 vC = VFPU::mulPerElem(vA, vB);

	EXPECT_VEC3_EQ(sC, vC);
}

VMTEST(VectorScalarMultiplication)
{
	Scalar::Vector3 sV(2.0f, 2.0f, 2.0f);
	Scalar::Vector3 sA = sV * 2.0f;
	Scalar::Vector3 sB = sA;
	sB *= 2.0f;

	VFPU::Vector3 vV(2.0f, 2.0f, 2.0f);
	VFPU::Vector3 vA = vV * 2.0f;
	VFPU::Vector3 vB = vA;
	vB *= 2.0f;

	EXPECT_VEC3_EQ(sB, vB);
}

VMTEST(VectorVectorDivision)
{
	Scalar::Vector3 sA(2.0f, 2.0f, 2.0f);
	Scalar::Vector3 sB(2.0f, 2.0f, 2.0f);
	Scalar::Vector3 sC = Scalar::divPerElem(sA, sB);

	VFPU::Vector3 vA(2.0f, 2.0f, 2.0f);
	VFPU::Vector3 vB(2.0f, 2.0f, 2.0f);
	VFPU::Vector3 vC = VFPU::divPerElem(vA, vB);

	EXPECT_VEC3_EQ(sC, vC);
}

VMTEST(VectorScalarDivision)
{
	Scalar::Vector3 sV(2.0f, 2.0f, 2.0f);
	Scalar::Vector3 sA = sV / 2.0f;
	Scalar::Vector3 sB = sA;
	sB /= 2.0f;

	VFPU::Vector3 vV(2.0f, 2.0f, 2.0f);
	VFPU::Vector3 vA = vV / 2.0f;
	VFPU::Vector3 vB = vA;
	vB /= 2.0f;

	EXPECT_VEC3_EQ(sB, vB);
}

VMTEST(VectorNegate)
{
	Scalar::Vector3 sA(2.0f, -2.0f, 9.0f);
	Scalar::Vector3 sB = -sA;

	VFPU::Vector3 vA(2.0f, -2.0f, 9.0f);
	VFPU::Vector3 vB = -vA;

	EXPECT_VEC3_EQ(sB, vB);
}

VMTEST(VectorReciprocal)
{
	Scalar::Vector3 sA(2.0f, -2.0f, 9.0f);
	Scalar::Vector3 sB = Scalar::recipPerElem(sA);

	VFPU::Vector3 vA(2.0f, -2.0f, 9.0f);
	VFPU::Vector3 vB = VFPU::recipPerElem(vA);

	EXPECT_VEC3_EQ(sB, vB);
}

VMTEST(VectorSqrt)
{
	Scalar::Vector3 sA(16.0f, 32.0f, 64.0f);
	Scalar::Vector3 sB = Scalar::sqrtPerElem(sA);

	VFPU::Vector3 vA(16.0f, 32.0f, 64.0f);
	VFPU::Vector3 vB = VFPU::sqrtPerElem(vA);

	EXPECT_VEC3_EQ(sB, vB);
}

VMTEST(VectorReciprocalSqrt)
{
	Scalar::Vector3 sA(16.0f, 32.0f, 64.0f);
	Scalar::Vector3 sB = Scalar::rsqrtPerElem(sA);

	VFPU::Vector3 vA(16.0f, 32.0f, 64.0f);
	VFPU::Vector3 vB = VFPU::rsqrtPerElem(vA);

	EXPECT_VEC3_EQ(sB, vB);
}

VMTEST(VectorAbsolute)
{
	Scalar::Vector3 sA(2.0f, -2.0f, 9.0f);
	Scalar::Vector3 sB = Scalar::absPerElem(sA);

	VFPU::Vector3 vA(2.0f, -2.0f, 9.0f);
	VFPU::Vector3 vB = VFPU::absPerElem(vA);

	EXPECT_VEC3_EQ(sB, vB);
}

VMTEST(VectorMaxPerElem)
{
	Scalar::Vector3 sA(2.0f, -2.0f, 9.0f);
	Scalar::Vector3 sB(5.0f, -5.0f, 12.0f);
	Scalar::Vector3 sC = Scalar::maxPerElem(sA, sB);

	VFPU::Vector3 vA(2.0f, -2.0f, 9.0f);
	VFPU::Vector3 vB(5.0f, -5.0f, 12.0f);
	VFPU::Vector3 vC = VFPU::maxPerElem(vA, vB);

	EXPECT_VEC3_EQ(sC, vC);
}

VMTEST(VectorMinPerElem)
{
	Scalar::Vector3 sA(2.0f, -2.0f, 9.0f);
	Scalar::Vector3 sB(5.0f, -5.0f, 12.0f);
	Scalar::Vector3 sC = Scalar::minPerElem(sA, sB);

	VFPU::Vector3 vA(2.0f, -2.0f, 9.0f);
	VFPU::Vector3 vB(5.0f, -5.0f, 12.0f);
	VFPU::Vector3 vC = VFPU::minPerElem(vA, vB);

	EXPECT_VEC3_EQ(sC, vC);
}

VMTEST(VectorMaxElem)
{
	Scalar::Vector3 sA(2.0f, -2.0f, 9.0f);
	float sB = Scalar::maxElem(sA);

	VFPU::Vector3 vA(2.0f, -2.0f, 9.0f);
	float vB = VFPU::maxElem(vA);

	EXPECT_FLOAT_EQ(sB, vB);
}

VMTEST(VectorMinElem)
{
	Scalar::Vector3 sA(2.0f, -2.0f, 9.0f);
	float sB = Scalar::minElem(sA);

	VFPU::Vector3 vA(2.0f, -2.0f, 9.0f);
	float vB = VFPU::minElem(vA);

	EXPECT_FLOAT_EQ(sB, vB);
}

VMTEST(VectorSum)
{
	Scalar::Vector3 sA(2.0f, -2.0f, 9.0f);
	float sB = Scalar::sum(sA);

	VFPU::Vector3 vA(2.0f, -2.0f, 9.0f);
	float vB = VFPU::sum(vA);

	EXPECT_FLOAT_EQ(sB, vB);
}

VMTEST(VectorDotProduct)
{
	Scalar::Vector3 sA(0.4f, 0.6f, 0.0f);
	Scalar::Vector3 sB(0.2f, 0.2f, 0.6f);
	float sC = Scalar::dot(sA, sB);

	VFPU::Vector3 vA(0.4f, 0.6f, 0.0f);
	VFPU::Vector3 vB(0.2f, 0.2f, 0.6f);
	float vC = VFPU::dot(vA, vB);

	EXPECT_FLOAT_EQ(sC, vC);
}

VMTEST(VectorLengthSqr)
{
	Scalar::Vector3 sA(2.0f, 3.0f, 4.0f);
	Scalar::Vector3 sB(0.5f, 0.2f, 0.3f);
	float sLA = Scalar::lengthSqr(sA);
	float sLB = Scalar::lengthSqr(sB);

	VFPU::Vector3 vA(2.0f, 3.0f, 4.0f);
	VFPU::Vector3 vB(0.5f, 0.2f, 0.3f);
	float vLA = VFPU::lengthSqr(vA);
	float vLB = VFPU::lengthSqr(vB);

	EXPECT_FLOAT_EQ(sLA, vLA);
	EXPECT_FLOAT_EQ(sLB, vLB);
}

VMTEST(VectorLength)
{
	Scalar::Vector3 sA(2.0f, 3.0f, 4.0f);
	Scalar::Vector3 sB(0.5f, 0.2f, 0.3f);
	float sLA = Scalar::length(sA);
	float sLB = Scalar::length(sB);

	VFPU::Vector3 vA(2.0f, 3.0f, 4.0f);
	VFPU::Vector3 vB(0.5f, 0.2f, 0.3f);
	float vLA = VFPU::length(vA);
	float vLB = VFPU::length(vB);

	EXPECT_FLOAT_EQ(sLA, vLA);
	EXPECT_FLOAT_EQ(sLB, vLB);
}

VMTEST(VectorNormalize)
{
	Scalar::Vector3 sA(2.0f, 3.0f, 4.0f);
	Scalar::Vector3 sB = Scalar::normalize(sA);

	VFPU::Vector3 vA(2.0f, 3.0f, 4.0f);
	VFPU::Vector3 vB = VFPU::normalize(vA);

	EXPECT_VEC3_EQ(sB, vB);
}

VMTEST(VectorLerp)
{
	Scalar::Vector3 sA(0.0f, 0.0f, 0.0f);
	Scalar::Vector3 sB(1.0f, 1.0f, 1.0f);
	Scalar::Vector3 sC(2.7f, 67.0f, 1213.0f);
	Scalar::Vector3 sD(-13.7f, 12.0f, -26432.0f);
	Scalar::Vector3 sX, sY;

	VFPU::Vector3 vA(0.0f, 0.0f, 0.0f);
	VFPU::Vector3 vB(1.0f, 1.0f, 1.0f);
	VFPU::Vector3 vC(2.7f, 67.0f, 1213.0f);
	VFPU::Vector3 vD(-13.7f, 12.0f, -26432.0f);
	VFPU::Vector3 vX, vY;

	for (int i = 0; i < 8; i++)
	{
		float t = 0.2f * (float)i;
		sX = Scalar::lerp(t, sA, sB);
		sY = Scalar::lerp(t, sC, sD);

		vX = VFPU::lerp(t, vA, vB);
		vY = VFPU::lerp(t, vC, vD);

		EXPECT_VEC3_EQ(sX, vX);
		EXPECT_VEC3_EQ(sY, vY);
	}
}

VMTEST(VectorSelect)
{
	Scalar::Vector3 sA(0.0f, 0.0f, 0.0f);
	Scalar::Vector3 sB(1.0f, 1.0f, 1.0f);
	Scalar::Vector3 sC = Scalar::select(sA, sB, true);
	Scalar::Vector3 sD = Scalar::select(sA, sB, false);

	VFPU::Vector3 vA(0.0f, 0.0f, 0.0f);
	VFPU::Vector3 vB(1.0f, 1.0f, 1.0f);
	VFPU::Vector3 vC = VFPU::select(vA, vB, true);
	VFPU::Vector3 vD = VFPU::select(vA, vB, false);

	EXPECT_VEC3_EQ(sC, vC);
	EXPECT_VEC3_EQ(sD, vD);
}

VMTEST(VectorCrossProduct)
{
	Scalar::Vector3 sA(1.0f, 0.0f, 0.0f);
	Scalar::Vector3 sB(0.0f, 1.0f, 0.0f);
	Scalar::Vector3 sC( 1.0f,  2.0f,  3.0f);
	Scalar::Vector3 sD(-1.0f, -2.0f, -3.0f);
	Scalar::Vector3 sE( 4.0f,  5.0f,  6.0f);
	Scalar::Vector3 sX = Scalar::cross(sA, sB);
	Scalar::Vector3 sY = Scalar::cross(sC, sD);
	Scalar::Vector3 sZ = Scalar::cross(sC, sE);

	VFPU::Vector3 vA(1.0f, 0.0f, 0.0f);
	VFPU::Vector3 vB(0.0f, 1.0f, 0.0f);
	VFPU::Vector3 vC( 1.0f,  2.0f,  3.0f);
	VFPU::Vector3 vD(-1.0f, -2.0f, -3.0f);
	VFPU::Vector3 vE( 4.0f,  5.0f,  6.0f);
	VFPU::Vector3 vX = VFPU::cross(vA, vB);
	VFPU::Vector3 vY = VFPU::cross(vC, vD);
	VFPU::Vector3 vZ = VFPU::cross(vC, vE);

	EXPECT_VEC3_EQ(sX, vX);
	EXPECT_VEC3_EQ(sY, vY);
	EXPECT_VEC3_EQ(sZ, vZ);
}

VMTEST(Performance)
{
	// in microseconds
	float elapsedScalar, elapsedVFPU;

	{
		using namespace Scalar;
		using V3 = Vector3;

		u64 start, end;
		sceRtcGetCurrentTick(&start);

		V3 add = V3(1.0f, 1.0f, 1.0f) + V3(2.0f, 2.0f, 2.0f);
		V3 sub = V3(1.0f, 1.0f, 1.0f) - V3(2.0f, 2.0f, 2.0f);
		V3 mul = mulPerElem(V3(2.0f, 2.0f, 2.0f), V3(2.0f, 2.0f, 2.0f));
		V3 div = divPerElem(V3(8.0f, 8.0f, 8.0f), V3(2.0f, 2.0f, 2.0f));
		mul *= 5.0f;
		mul /= 2.0f;

		V3 _lerp = lerp(0.5f, sub, add);
		V3 _cross = cross(V3(1.0f, 0.0f, 0.0f), V3(0.0f, 1.0f, 0.0f));

		V3 recip = recipPerElem(V3(5.0f, 5.0f, 5.0f));
		V3 sqrt = sqrtPerElem(V3(16.0f, 16.0f, 16.0f));
		V3 rsqrt = rsqrtPerElem(V3(16.0f, 16.0f, 16.0f));
		V3 abs = absPerElem(V3(-359.0f, -2348.0f, -8573.0f));
		V3 max = maxPerElem(V3(0.0f, 90.0f, 30.0f), V3(1.0f, 89.0f, 31.0f));
		V3 min = minPerElem(V3(0.0f, 90.0f, 30.0f), V3(1.0f, 89.0f, 31.0f));
		V3 normalized = normalize(mul);

		float max2 = maxElem(max);
		float min2 = minElem(min);

		float _sum = sum(add);
		float _dot = dot(add, sub);
		float _lengthSqr = lengthSqr(add);
		float _length = length(add);

		sceRtcGetCurrentTick(&end);
		elapsedScalar = (float)(end - start);
	}

	{
		using namespace VFPU;
		using V3 = Vector3;

		u64 start, end;
		sceRtcGetCurrentTick(&start);

		V3 add = V3(1.0f, 1.0f, 1.0f) + V3(2.0f, 2.0f, 2.0f);
		V3 sub = V3(1.0f, 1.0f, 1.0f) - V3(2.0f, 2.0f, 2.0f);
		V3 mul = mulPerElem(V3(2.0f, 2.0f, 2.0f), V3(2.0f, 2.0f, 2.0f));
		V3 div = divPerElem(V3(8.0f, 8.0f, 8.0f), V3(2.0f, 2.0f, 2.0f));
		mul *= 5.0f;
		mul /= 2.0f;

		V3 _lerp = lerp(0.5f, sub, add);
		V3 _cross = cross(V3(1.0f, 0.0f, 0.0f), V3(0.0f, 1.0f, 0.0f));

		V3 recip = recipPerElem(V3(5.0f, 5.0f, 5.0f));
		V3 sqrt = sqrtPerElem(V3(16.0f, 16.0f, 16.0f));
		V3 rsqrt = rsqrtPerElem(V3(16.0f, 16.0f, 16.0f));
		V3 abs = absPerElem(V3(-359.0f, -2348.0f, -8573.0f));
		V3 max = maxPerElem(V3(0.0f, 90.0f, 30.0f), V3(1.0f, 89.0f, 31.0f));
		V3 min = minPerElem(V3(0.0f, 90.0f, 30.0f), V3(1.0f, 89.0f, 31.0f));
		V3 normalized = normalize(mul);

		float max2 = maxElem(max);
		float min2 = minElem(min);

		float _sum = sum(add);
		float _dot = dot(add, sub);
		float _lengthSqr = lengthSqr(add);
		float _length = length(add);

		sceRtcGetCurrentTick(&end);
		elapsedVFPU = (float)(end - start);
	}

	PspTestListener::sScalarTime = elapsedScalar;
	PspTestListener::sVfpuTime = elapsedVFPU;

	float ratio = elapsedScalar / elapsedVFPU;
	EXPECT_GT(ratio, 1.0f);
}
