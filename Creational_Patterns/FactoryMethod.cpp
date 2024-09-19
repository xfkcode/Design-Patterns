#include <memory>
#include <iostream>

using namespace std;

class Product {
public:
    virtual void use() const = 0;
    virtual ~Product() = default;
};

class ProductA : public Product {
public:
    void use() const override {
        cout << "use A" << endl;
    }
};

class ProductB : public Product {
public:
    void use() const override {
        cout << "use B" << endl;
    }
};

class Factory {
public:
    virtual unique_ptr<Product> createProduct() const = 0;
    virtual ~Factory() = default;
};

class FactoryProductA : public Factory {
public:
    unique_ptr<Product> createProduct() const override {
        return make_unique<ProductA>();
    } 
};

class FactoryProductB : public Factory {
public:
    unique_ptr<Product> createProduct() const override {
        return make_unique<ProductB>();
    } 
};

int main() {
    std::unique_ptr<Factory> FactoryA = std::make_unique<FactoryProductA>();
    std::unique_ptr<Product> PA = FactoryA->createProduct();
    PA->use();

    std::unique_ptr<Factory> FactoryB = std::make_unique<FactoryProductB>();
    std::unique_ptr<Product> PB = FactoryB->createProduct();
    PB->use();
    system("pause");
    return 0;
}