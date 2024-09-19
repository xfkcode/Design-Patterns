#include <memory>
#include <iostream>

using namespace std;

class Product {
public:
    Product() {}
    ~Product() {}

    void setOS(const string &OS) {
        this->os = OS;
    }
    void setSTORAGE(const string &STORAGE) {
        this->storage = STORAGE;
    }

    void show() const {
        cout << "OS:" << os << endl;
        cout << "STORAGE:" << storage << endl;
    }

private:
    string os;
    string storage;
};

class builder {
public:
    virtual void buildOS() = 0;
    virtual void buildSTORAGE() =0;
    virtual unique_ptr<Product> getProduct() = 0;
    virtual ~builder() = default;
};
class builderProductA : public builder {
public:
    builderProductA() {
        this->P = make_unique<Product>(); 
    }

    void buildOS() override {
        this->P->setOS("ios 18");
    }
    void buildSTORAGE() override {
        this->P->setSTORAGE("256G");
    }
    unique_ptr<Product> getProduct() override {
        return move(P);
    }

private:
    unique_ptr<Product> P;
};
class builderProductB : public builder {
public:
    builderProductB() {
        this->P = make_unique<Product>(); 
    }

    void buildOS() override {
        this->P->setOS("ios 16");
    }
    void buildSTORAGE() override {
        this->P->setSTORAGE("128G");
    }
    unique_ptr<Product> getProduct() override {
        return move(P);
    }

private:
    unique_ptr<Product> P;
};

class Director {
public:
    Director(builder* Builder) : Builder(Builder) {}

    void construct() {
        Builder->buildOS();
        Builder->buildSTORAGE();
    }

private:
    builder* Builder;
};

int main(int argc, const char** argv) {
    builderProductA BP_a;
    Director Pa_Dir(&BP_a);
    Pa_Dir.construct();
    unique_ptr<Product> PA = BP_a.getProduct();
    PA->show();

    builderProductB BP_b;
    Director Pb_Dir(&BP_b);
    Pb_Dir.construct();
    unique_ptr<Product> PB = BP_b.getProduct();
    PB->show();
    system("pause");
    return 0;
}