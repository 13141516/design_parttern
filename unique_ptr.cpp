#include "unique_ptr.h"

namespace SmartPointer {
	//construct 
	template<typename T, typename Deleter>
	unique_ptr<T, Deleter>::unique_ptr(T *pT) :m_pT(pT)
	{
	}

	//destroy
	template<typename T, typename Deleter>
	unique_ptr<T, Deleter>::~unique_ptr()
	{
		del();
	}

	//call deleter
	template<typename T, typename Deleter>
	void unique_ptr<T, Deleter>::del()
	{
		if (*this)
		{
			m_deleter(m_pT);
			m_pT = nullptr;
		}
	}

	//get the pointer
	template<typename T, typename Deleter>
	T *unique_ptr<T, Deleter>::get()
	{
		return m_pT;
	}

	//reset 
	template<typename T, typename Deleter>
	void unique_ptr<T, Deleter>::reset(T *p)
	{
		del();
		m_pT = p;
	}

	//release the own of the pointer
	template<typename T, typename Deleter>
	T *unique_ptr<T, Deleter>::release()
	{
		T *p = m_pT;
		m_pT = nullptr;
		return p;
	}

	//convert unique_ptr to bool
	template<typename T, typename Deleter>
	unique_ptr<T, Deleter>::operator bool() const
	{
		return nullptr != m_pT;
	}

	//overload for operator *
	template<typename T, typename Deleter>
	T &unique_ptr<T, Deleter>::operator*()
	{
		assert(*this);
		return *m_pT;
	}

	//overload for operator ->
	template<typename T, typename Deleter>
	T *unique_ptr<T, Deleter>::operator->()
	{
		assert(*this);
		return m_pT;
	}
}


class TestClass {
private:
	int x;
	int y;
public:
	TestClass(int x, int y) : x(x), y(y) {};
	~TestClass() {
		printf("deconstructor is executing ...\n");
	};
	int getX() {
		return x;
	};
	int getY() {
		return y;
	};
};

void test() {
	// test unique_ptr
	std::unique_ptr<TestClass> testCpp(new TestClass(7, 8));
	printf("%d\n", (*testCpp).getX());
	// test smart pointer self define unique_ptr
	SmartPointer::unique_ptr<TestClass> testCqq(new TestClass(9, 10));
	printf("%d\n", (*testCqq).getX());
}

int main(int argc, char * args[]) {
	test();
	getchar();
	return 0;
}