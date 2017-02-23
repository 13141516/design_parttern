#include <iostream>

/*This is a simple implemention of smart pointer, it's function just like a shared_ptr*/

template<class typeData>
class SmartPointer{
public:
	class Ref {
	public:
		Ref(typeData *ptr) :ptr(ptr), account(1){
			std::cout << "construct exe from Ref ..." << std::endl;
		};
		~Ref(){
			std::cout << "deconstruct exe from Ref ..." << std::endl;
			delete ptr;
		};
		friend class SmartPointer;
	private:
		typeData *ptr;
		int account;
	};
	explicit SmartPointer(typeData *ptr) :ref(new Ref(ptr)){
		std::cout << "construct exe from SmartPointer ..." << std::endl;
	};
	SmartPointer(const SmartPointer &sp){
		std::cout << "copy construct exe from SmartPointer ..." << std::endl;
		ref = sp.ref;
		++ref->account;
	};
	~SmartPointer(){
		std::cout << "deconstruct exe from SmartPointer ..." << std::endl;
		--ref->account;;
		if (ref->account == 0) {
			delete ref;
		}
	};
private:
	Ref *ref;
};

void test() {
	SmartPointer<int> sp(new int(10));
	SmartPointer<int> ps(sp);
	SmartPointer<int> ssp = ps;
}

int main(int argc, char * args []) {
	/*
	std::shared_ptr<int> sp = std::make_shared<int>(8);
	std::cout << *sp.get() << std::endl;
	*/
	test();
	return 0;
}