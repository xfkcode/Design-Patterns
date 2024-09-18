#include <iostream>
#include <memory>
#include <string>

class Product {
public:
    virtual void use() const = 0;
    virtual ~Product() {}
};

class ProductA : public Product {
    void use() const override {
        std::cout << "use A" << std::endl;
    }
};

class ProductB : public Product {
    void use() const override {
        std::cout << "use B" << std::endl;
    }
};

class SimpleFactory {
public:
    static std::unique_ptr<Product> createProduct(const std::string& type) {
        if (type == "A") {
            return std::make_unique<ProductA>();
        } else if (type == "B") {
            return std::make_unique<ProductB>();
        } else {
            return nullptr;
        }
    }
};

int main() {
    // 创建工厂对象并生成产品A
    std::unique_ptr<Product> productA = SimpleFactory::createProduct("A");
    if (productA) {
        productA->use();  // 输出：ues A
    }

    // 创建工厂对象并生成产品B
    std::unique_ptr<Product> productB = SimpleFactory::createProduct("B");
    if (productB) {
        productB->use();  // 输出：use B
    }
    system("pause");
    return 0;
}