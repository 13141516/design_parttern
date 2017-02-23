/** this is a demo of unique_ptr just like unique_ptr in C++11*/
#pragma once

#include <iostream>
#include <memory>

namespace SmartPointer {
	template<typename T>
	struct DefaultDeleter
	{
		void operator()(T *p)
		{
			if (p)
			{
				delete p;
				p = nullptr;
			}
		}
	};

	template<typename T, typename Deleter = DefaultDeleter<T>>
	class unique_ptr
	{
	public:
		//construct 
		unique_ptr(T *pT = nullptr);
		//destroy
		~unique_ptr();
	private:
		//not allow copyable
		unique_ptr(const unique_ptr &) {};
		unique_ptr& operator=(const unique_ptr &) {};

	public:
		//reset 
		void reset(T *p);
		//release the own of the pointer
		T *release();
		//get the pointer
		T *get();
		//convert unique_ptr to bool
		operator bool() const;

	public:
		//overload for operator *
		T &operator*();
		//overload for operator ->
		T *operator->();

	private:
		//pointer
		T *m_pT;
		//deleter
		Deleter m_deleter;
		//call deleter
		void del();
	};
}


