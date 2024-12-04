#include <iostream>
#include <memory>
#include <string>

class Prototype {
public:
    virtual ~Prototype() = default;
    virtual std::unique_ptr<Prototype> clone() const = 0;
    virtual void show() const = 0;
};

class ConcretePrototype : public Prototype {
private:
    std::string str;
public:
    ConcretePrototype(const std::string &str) : str(str) {}
    ConcretePrototype(const ConcretePrototype &other) : str(other.str) {}

    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototype>(*this);
    }

    void show() const override {
        std::cout << "ConcretePrototype: " << str << std::endl;
    }
};

int main(int argc, char *argv[]) {
    std::unique_ptr<Prototype> p1 = std::make_unique<ConcretePrototype>("Hello");
    p1->show();

    std::unique_ptr<Prototype> p2 = p1->clone();
    p2->show();
    
    return 0;
}