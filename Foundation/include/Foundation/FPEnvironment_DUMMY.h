//
// FPEnvironment_DUMMY.h
//
// $Id: //poco/1.1.0/Foundation/include/Foundation/FPEnvironment_DUMMY.h#2 $
//
// Library: Foundation
// Package: Core
// Module:  FPEnvironment
//
// Definition of class FPEnvironmentImpl for platforms that do not
// support IEEE 754 extensions.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_FPEnvironment_DUMMY_INCLUDED
#define Foundation_FPEnvironment_DUMMY_INCLUDED


#ifndef Foundation_Foundation_INCLUDED
#include "Foundation/Foundation.h"
#endif
#ifndef STD_MATH_INCLUDED
#include <math.h>
#define STD_MATH_INCLUDED
#endif


Foundation_BEGIN


class FPEnvironmentImpl
{
protected:
	enum RoundingModeImpl
	{
		FP_ROUND_DOWNWARD_IMPL,
		FP_ROUND_UPWARD_IMPL,
		FP_ROUND_TONEAREST_IMPL,
		FP_ROUND_TOWARDZERO_IMPL
	};
	enum FlagImpl
	{
		FP_DIVIDE_BY_ZERO_IMPL,
		FP_INEXACT_IMPL,
		FP_OVERFLOW_IMPL,
		FP_UNDERFLOW_IMPL,
		FP_INVALID_IMPL
	};
	FPEnvironmentImpl();
	FPEnvironmentImpl(const FPEnvironmentImpl& env);
	~FPEnvironmentImpl();
	FPEnvironmentImpl& operator = (const FPEnvironmentImpl& env);
	void keepCurrentImpl();		
	static void clearFlagsImpl();
	static bool isFlagImpl(FlagImpl flag);	
	static void setRoundingModeImpl(RoundingModeImpl mode);
	static RoundingModeImpl getRoundingModeImpl();
	static bool isInfiniteImpl(float value);		
	static bool isInfiniteImpl(double value);
	static bool isInfiniteImpl(long double value);
	static bool isNaNImpl(float value);		
	static bool isNaNImpl(double value);
	static bool isNaNImpl(long double value);
	static float copySignImpl(float target, float source);		
	static double copySignImpl(double target, double source);
	static long double copySignImpl(long double target, long double source);

private:
	static RoundingModeImpl _roundingMode;
};


//
// inlines
//
inline bool FPEnvironmentImpl::isInfiniteImpl(float value)
{
	return isinf(value) != 0;
}


inline bool FPEnvironmentImpl::isInfiniteImpl(double value)
{
	return isinf(value) != 0;
}


inline bool FPEnvironmentImpl::isInfiniteImpl(long double value)
{
	return isinf((double) value) != 0;
}


inline bool FPEnvironmentImpl::isNaNImpl(float value)
{
	return isnan(value) != 0;
}


inline bool FPEnvironmentImpl::isNaNImpl(double value)
{
	return isnan(value) != 0;
}


inline bool FPEnvironmentImpl::isNaNImpl(long double value)
{
	return isnan((double) value) != 0;
}


inline float FPEnvironmentImpl::copySignImpl(float target, float source)
{
	return copysignf(target, source);
}


inline double FPEnvironmentImpl::copySignImpl(double target, double source)
{
	return copysign(target, source);
}


Foundation_END


#endif // Foundation_FPEnvironment_DUMMY_INCLUDED
