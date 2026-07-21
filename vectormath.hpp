
// ================================================================================================
// -*- C++ -*-
// File: vectormath/vectormath.hpp
// Author: Guilherme R. Lampert
// Created on: 30/12/16
// Brief: This header exposes the Sony Vectormath library types and functions into the global scope.
//
// Modified by: Mahmoud Nouh (Mahmoud1205)
// ================================================================================================

#ifndef VECTORMATH_HPP
#define VECTORMATH_HPP

#if (!defined(VECTORMATH_DEBUG) && (defined(DEBUG) || defined(_DEBUG)))
	#define VECTORMATH_DEBUG 1
#endif // DEBUG || _DEBUG

#if !defined(VECTORMATH_MODE_VFPU) && !defined(VECTORMATH_MODE_SCALAR)
	#define VECTORMATH_MODE_VFPU // default to vfpu mode
#endif

#ifdef VECTORMATH_MODE_VFPU
	#include "vfpu/vectormath.hpp"
	using namespace Vectormath::VFPU;
#else
	#include "scalar/vectormath.hpp"
	using namespace Vectormath::Scalar;
#endif

#include "vec2d.hpp"  // - Extended 2D vector and point classes; not aligned and always in scalar floats mode.
#include "common.hpp" // - Miscellaneous helper functions.
using namespace Vectormath;

#endif // VECTORMATH_HPP
