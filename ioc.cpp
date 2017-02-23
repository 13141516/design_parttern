#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <memory>

/*
* this is demo of ioc of c++
*/

/////////////////////
//define the interface
class FuncInterface {
public:
	virtual void func() = 0;
};

/////////////////////
//subclass of FuncInterface
class ClassA : public FuncInterface {
public:
	void func();
};

void ClassA::func() {
	std::cout << "I am A" << std::endl;
}
////////////////////
//subclass of FuncInterface
class ClassB : public FuncInterface {
public:
	void func();
};

void ClassB::func() {
	std::cout << "I am B" << std::endl;
}

////////////////////
//ico class
template<class T>
class ICOContainer {
private:
	std::map <std::string, std::function<T*()>> iContainer;
public:
	ICOContainer();
	virtual ~ICOContainer();
	template<class Drived>
	void registerType(std::string key);
	std::shared_ptr<T> getType(std::string key);
};

template<class T>
ICOContainer<T>::ICOContainer() {
}

template<class T>
ICOContainer<T>::~ICOContainer() {
}

template<class T>
template<class Drived>
void ICOContainer<T>::registerType(std::string key) {
	std::function<T*()> initFunc = [=](){return new Drived(); };
	iContainer.emplace(key, initFunc);
}

template<class T>
std::shared_ptr<T> ICOContainer<T>::getType(std::string key){
	if (iContainer.find(key) == iContainer.end()) {
		throw std::invalid_argument("This key has already exist!");
	}
	std::function<T*()> specialType = iContainer[key];
	std::shared_ptr<T> returnValue(specialType());
	return returnValue;
}

int main(int argc, char ** argv) {
	ICOContainer<FuncInterface> icoContainer;
	icoContainer.registerType<ClassA>("A");
	icoContainer.registerType<ClassB>("B");
	icoContainer.getType("A")->func();
	icoContainer.getType("B")->func();
	getchar();
	return 0;
}
