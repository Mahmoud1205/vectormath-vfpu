
# Vectormath

## VFPU Modification
VFPU version of [glampert's modification of Sony's open-sourced header-only vector and matrix math library](https://github.com/glampert/vectormath).
* **THIS PORT IS NOT COMPLETE YET !!**
* This modification replaces the SSE implementation with a VFPU implementation for the PlayStation Portable.
* The Scalar implementation is kept for reference and debugging.
* This modification is no longer header-only; it contains an assembly file which must be compiled using `psp-gcc` from the open-source `pspsdk`.
* The user can switch between VFPU and Scalar mode by defining `VECTORMATH_MODE_VFPU` or `VECTORMATH_MODE_SCALAR` respectively before including `vectormath.hpp` or in the compiler option. If none are defined: the library defaults to `VECTORMATH_MODE_VFPU`.
* This modification includes a testbed application to run unit testing (GoogleTest) to verify the output of the VFPU implementation against the Scalar implementation on Emulator PSP or real PSP.

## Building Steps (Linux)
The releases tab contains a precompiled version of the library. But if you wish to compile it yourself,
1. Ensure you have the open-source `pspsdk` installed and in the system `PATH`.
2. Run `build.sh` script in this directory.
3. `libVectorMathVFPU.a` is now in `./bin/` directory.

<hr>

### Original copyright notice:

<pre>
 Vector Math library for 3-D linear algebra (vector, matrix, quaternion)
   SIMD support for SSE. Also includes generic multi-platform scalar version.

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
</pre>

<hr>

### glampert's original notes:
#### NOTE(Mahmoud): this information is outdated but I keep it to respect the original author.
The main differences from the original library released by Sony:
- Removed deprecated SPU/PPU implementations that only targeted PS3/PowerPC.
- Removed the C interfaces - the C++ interface is much nicer to use with operator overloads, return by val, etc.
- Massive namespace cleanup. Removed or replaced most macros with functions and constants.
- Better compliance with strict-aliasing rules.
- Added portable macros for alignment annotations to remove some `#ifdefs`.
- Internal SSE helper code moved to a separate header - other files also renamed.
- Removed the Aos/Soa sub-namespaces, since the Soa implementations were only available for SPU.
- The library now includes only the generic scalar version and the x86/64 SSE intrinsics version.
- Added an unpadded `Vector2` and `Point2` to also support basic 2D vector maths. These are always scalar mode (size = 2 floats).
- All you need to do is include the public header file `vectormath.hpp`. It will expose the relevant parts of the library for you and try to select the SSE implementation if supported.
