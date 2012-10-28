/***
	AutoPtr - A smart pointer for using native objects in managed code.

	Author	:	Nishant Sivakumar
	Email	:	voidnish@gmail.com	
	Blog	:	http://blog.voidnish.com
	Web		:	http://www.voidnish.com 	

	You may freely use this class as long as you include
	this copyright. 
	
	You may freely modify and use this class as long
	as you include this copyright in your modified version. 

	This code is provided "as is" without express or implied warranty. 
	
	Copyright © Nishant Sivakumar, 2006.
	All Rights Reserved.
***/

#pragma once
#pragma managed
namespace PacParser
{
template<typename T> ref class AutoPtr
{
private:
	T* _ptr;

public:
	AutoPtr() : _ptr(nullptr)
	{
	}

	AutoPtr(T* t) : _ptr(t)
	{
	}

	AutoPtr(AutoPtr<T>% an) : _ptr(an.Detach())
	{
	}

	template<typename TDERIVED> 
		AutoPtr(AutoPtr<TDERIVED>% an) : _ptr(an.Detach())
	{
	}

	!AutoPtr()
	{	
		delete _ptr;
	}

	~AutoPtr()
	{
		this->!AutoPtr();
	}

	AutoPtr<T>% operator=(T* t)
	{
		Attach(t);
		return *this;
	}

	AutoPtr<T>% operator=(AutoPtr<T>% an)
	{
		if(this != %an)
			Attach(an.Detach());
		return *this;
	}

	template<typename TDERIVED> 
		AutoPtr<T>% operator=(AutoPtr<TDERIVED>% an)
	{
		Attach(an.Detach());
		return *this;
	}

	static T* operator->(AutoPtr<T>% an)
	{
		return an._ptr;
	}

	static operator T*(AutoPtr<T>% an)
	{
		return an._ptr;
	}

	T* Detach()
	{
		T* t = _ptr;
		_ptr = nullptr;
		return t;
	}

	void Attach(T* t)
	{
		if(t)
		{	
			if(_ptr != t)
			{
				delete _ptr;
				_ptr = t;
			}
		}
		else
		{
#ifdef _DEBUG
			throw gcnew Exception(
				"Attempting to Attach(...) a nullptr!");
#endif
		}		
	}

	void Destroy()
	{
		delete _ptr;
		_ptr = nullptr;
	}
};
};