//
// PriorityDelegate.h
//
// $Id: //poco/1.1.0/Foundation/include/Foundation/PriorityDelegate.h#2 $
//
// Library: Foundation
// Package: Events
// Module:  PriorityDelegate
//
// Implementation of the PriorityDelegate template.
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


#ifndef  Foundation_PriorityDelegate_INCLUDED
#define  Foundation_PriorityDelegate_INCLUDED


#include "Foundation/Foundation.h"
#include "Foundation/AbstractPriorityDelegate.h"
#include "Foundation/PriorityExpire.h"


Foundation_BEGIN


template <class TObj, class TArgs> 
class PriorityDelegate: public AbstractPriorityDelegate<TArgs>
{
public:
	typedef void (TObj::*NotifyMethod)(const void*, TArgs&);

	PriorityDelegate(TObj* obj, NotifyMethod method, int prio): 
		_receiverObject(obj), 
		_receiverMethod(method),
		_priority(prio)
	{
	}
	
	PriorityDelegate(const PriorityDelegate& delegate):
		_receiverObject(delegate._receiverObject),
		_receiverMethod(delegate._receiverMethod),
		_priority(delegate._priority)
	{
	}
	
	PriorityDelegate& operator = (const PriorityDelegate& delegate)
	{
		if (&delegate != this)
		{
			_receiverObject = delegate._receiverObject;
			_receiverMethod = delegate._receiverMethod;
			_priority       = delegate._priority;
		}
		return *this;
	}

	~PriorityDelegate()
	{
	}

	bool notify(const void* sender, TArgs& arguments)
	{
		(_receiverObject->*_receiverMethod)(sender, arguments);
		return true; // per default the delegate never expires
	}

	AbstractPriorityDelegate<TArgs>* clone() const
	{
		return new PriorityDelegate(*this);
	}

	bool operator < (const AbstractPriorityDelegate<TArgs>& other) const
	{
		const PriorityDelegate* pOther = dynamic_cast<const PriorityDelegate*>(&other);

		if (pOther == 0)
		{
			const PriorityExpire<TArgs>* pExpire = dynamic_cast<const PriorityExpire<TArgs>*>(&other);
			poco_check_ptr(pExpire);

			return this->operator < (pExpire->getDelegate());
		}

		if (_priority < pOther->_priority)
		{
			return true;
		}

		if (_priority > pOther->_priority)
		{
			return false;
		}

		return _receiverObject < pOther->_receiverObject;
	}

protected:
	TObj*        _receiverObject;
	NotifyMethod _receiverMethod;
	int	         _priority;

private:
	PriorityDelegate();
};


Foundation_END


#endif
