#include <iostream>
#include <vector>

namespace chenli {
	// 定义Iterator接口
	template<typename Item>
	class Iterator {
	public:
		virtual void first() = 0;
		virtual void next() = 0;
		virtual Item & operator * () = 0;
		virtual void operator ++ () = 0;
		virtual bool isNotDone() = 0;
		virtual void setPosition(int c) = 0;
		virtual ~Iterator() {}
	};

	// 申明Aggregate接口
	template<typename Item>
	class Aggregate;

	// 实现Iterator接口 
	template<typename Item>
	class ConcreateIterator : public Iterator<Item> {
	private:
		Aggregate<Item> * aggr;
		int cur;
	public:
		ConcreateIterator(Aggregate<Item>*a) :aggr(a) {}
		virtual ~ConcreateIterator() {}
		void setPosition(int c) override {
			cur = c;
		}
		virtual void first() override
		{
			cur = 0;
		}
		virtual void next() override
		{
			if (cur < aggr->getLen()) {
				cur++;
			}
		}
		virtual Item & operator * () override
		{
			return (*aggr)[cur];
		}
		virtual void operator ++ () override {
			cur++;
		}
		virtual bool isNotDone() override
		{
			return (cur < aggr->getLen());
		}
	};

	// 定义Aggregate接口
	template<typename Item>
	class Aggregate
	{
	public:
		virtual Iterator<Item> & begin() = 0;
		virtual Iterator<Item> & end() = 0;
		virtual int getLen() = 0;
		virtual Item & operator[](int index) = 0;
		virtual ~Aggregate() {}
	};

	// 利用std::vector实现Aggregate接口
	template<typename Item>
	class VectorAggregate : public Aggregate<Item> {
	private: std::vector<Item> iVector;
			 Iterator<Item> *iter;
	public:
		VectorAggregate(int size, int value) {
			for (int i = 0; i < size; ++i) {
				iVector.push_back(value);
			}
			iter = new ConcreateIterator<Item>(this);
		}
		virtual ~VectorAggregate() {
			delete iter;
		}
		virtual Iterator<Item> & begin() override {
			iter->setPosition(0);
			return *iter;
		}
		virtual Iterator<Item> & end() override {
			iter->setPosition(iVector.size() - 1);
			return *iter;
		}
		virtual int getLen() override {
			return iVector.size();
		}
		virtual Item & operator[](int index) override {
			return iVector[index];
		}
	};
}

void testTwo() {
	// test stl iterator
	std::cout << "start to test stl iterator" << std::endl;
	std::vector<int>  iVector(10, 1);
	for (std::vector<int>::iterator iter = iVector.begin(); iter != iVector.end(); ++iter) {
		std::cout << *iter << std::endl;
	}
	// test chenli iterator, just like java, not like c++
	std::cout << "start to test chenli iterator" << std::endl;
	chenli::VectorAggregate<int> ca(10, 2);
	for (chenli::Iterator<int> & ite = ca.begin(); ite.isNotDone(); ++ite) {
		std::cout << *ite << std::endl;
	}
 }

int main(int argc, char * args[]) {
	testTwo();
	system("pause");
	return 0;
}

