#include <memory>
#include <iostream>

using namespace std;

class AbstractProductA {
public:
    virtual void use() const = 0;
    virtual ~AbstractProductA() = default;
};
class ProductA1 : public AbstractProductA {
public:
    void use() const override {
        cout << "use A1" << endl;
    }
};
class ProductA2 : public AbstractProductA {
public:
    void use() const override {
        cout << "use A2" << endl;
    }
};

class AbstractProductB {
public:
    virtual void show() const = 0;
    virtual ~AbstractProductB() = default;
};
class ProductB1 : public AbstractProductB {
public:
    void show() const override {
        cout << "show B1" << endl;
    }
};
class ProductB2 : public AbstractProductB {
public:
    void show() const override {
        cout << "show B2" << endl;
    }
};

class AbstractFactory {
public:
    virtual unique_ptr<AbstractProductA> createProductA() const = 0;
    virtual unique_ptr<AbstractProductB> createProductB() const = 0;
    virtual ~AbstractFactory() = default;
};
class ConcreteFactory1 : public AbstractFactory {
public:
    unique_ptr<AbstractProductA> createProductA() const {
        return make_unique<ProductA1>();        
    }
    unique_ptr<AbstractProductB> createProductB() const {
        return make_unique<ProductB1>();        
    }
};
class ConcreteFactory2 : public AbstractFactory {
public:
    unique_ptr<AbstractProductA> createProductA() const {
        return make_unique<ProductA2>();        
    }
    unique_ptr<AbstractProductB> createProductB() const {
        return make_unique<ProductB2>();        
    }
};

int main() {
    std::unique_ptr<AbstractFactory> fc1 = std::make_unique<ConcreteFactory1>();
    std::unique_ptr<AbstractProductA> a1 = fc1->createProductA();
    std::unique_ptr<AbstractProductB> b1 = fc1->createProductB();
    a1->use();
    b1->show();

    std::unique_ptr<AbstractFactory> fc2 = std::make_unique<ConcreteFactory2>();
    std::unique_ptr<AbstractProductA> a2 = fc2->createProductA();
    std::unique_ptr<AbstractProductB> b2 = fc2->createProductB();
    a2->use();
    b2->show();

    system("pause");
    return 0;
}