#include <iostream>
#include <memory>

/*
* this is a demo of singleton
*/

////////////////////////////
// this is class of Singleton
class Singleton {
private :
	Singleton(){}
	~Singleton(){ std::cout << "execute deconstruct..."; }
	Singleton(const Singleton&);//copy construct function
	Singleton & operator=(const Singleton&);//overide operator =
	static Singleton * instance;
public :
	void testFunc();
	static Singleton * getInstance();
	static void release();                                 
};

Singleton * Singleton::instance = new Singleton();

Singleton * Singleton::getInstance() {
	return instance;
}

void Singleton::testFunc() {
	std::cout << "execute func..." << std::endl;
}

void Singleton::release() {
	if (instance != nullptr) {
		delete instance;
	}
}

//////////////////////
//test
int main(int args, char ** argv) {
	Singleton * singleton = Singleton::getInstance();
	singleton->testFunc();
	Singleton::release();
	getchar();
	return 0;
}