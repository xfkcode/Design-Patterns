#include <iostream>
#include <unordered_map>
#include <memory>

using namespace std;

class Flyweight {
public:
    virtual void operation(int intrinsicState) = 0;
};

class ConcreteFlyweight : public Flyweight {
public:
    void operation(int intrinsicState) override {
        cout << "ConcreteFlyweight" << intrinsicState << endl;
    }
};

class FlyweightFactory {
private:
    unordered_map<int, shared_ptr<Flyweight>> flyweights;

public:
    shared_ptr<Flyweight> getFlyweight(int key) {
        if(flyweights.find(key) == flyweights.end()) {
            flyweights[key] = make_shared<ConcreteFlyweight>();
        }
        return flyweights[key];
    }
};

int main(int argc, char const *argv[])
{
    FlyweightFactory ff;
    for(int i=0; i<5; ++i) {
        auto flyweight = ff.getFlyweight(i % 2);
        flyweight->operation(i);
    }
    
    system("pause");
    return 0;
}
