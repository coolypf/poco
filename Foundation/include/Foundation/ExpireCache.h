//
// ExpireCache.h
//
// $Id: //poco/1.1.0/Foundation/include/Foundation/ExpireCache.h#2 $
//
// Library: Foundation
// Package: Cache
// Module:  ExpireCache
//
// Definition of the ExpireCache class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
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


#ifndef  Foundation_ExpireCache_INCLUDED
#define  Foundation_ExpireCache_INCLUDED


#include "Foundation/AbstractCache.h"
#include "Foundation/ExpireStrategy.h"


Foundation_BEGIN


template <class TKey, class TValue> 
class ExpireCache: public AbstractCache<TKey, TValue, ExpireStrategy<TKey, TValue > >
	/// An ExpireCache caches entries for a fixed time period (per default 10 minutes)
	/// Be careful when using an ExpireCache. A cache is often used
	/// like cache.has(x) followed by cache.get x). Note that it could happen
	/// that the "has" call works, then the current execution thread gets descheduled, time passes,
	/// the entry gets invalid, thus leading to an empty SharedPtr being returned 
	/// when "get" is invoked.
{
public:
	ExpireCache(Timestamp::TimeDiff expire = 600000): 
		AbstractCache<TKey, TValue, ExpireStrategy<TKey, TValue> >(ExpireStrategy<TKey, TValue>(expire))
	{
	}

	~ExpireCache()
	{
	}

private:
	ExpireCache(const ExpireCache& aCache);
	ExpireCache& operator = (const ExpireCache& aCache);
};


Foundation_END


#endif
