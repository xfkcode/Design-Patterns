#include <iostream>
#include <string>

using namespace std;

class Coffee {
public:
    virtual string getDescription() const {
        return "Coffer";
    }

    virtual double cost() const {
        return 1.0;
    }
};

class CoffeeDecorator : public Coffee {
protected:
    Coffee* coffee;
public:
    CoffeeDecorator(Coffee* coffee) : coffee(coffee) {}
    virtual ~CoffeeDecorator() { delete coffee; }
};

class Milk : public CoffeeDecorator {
public:
    Milk(Coffee* c) : CoffeeDecorator(c) {}
    
    string getDescription() const override {
        return coffee->getDescription() + ", Milk";
    }

    double cost() const override {
        return coffee->cost() + 0.5;
    }
};

int main(int argc, char const *argv[])
{
    Coffee* myCoffee = new Coffee();
    Coffee* myMilk = new Milk(myCoffee);

    std::cout << "Description: " << myCoffee->getDescription() << std::endl;
    std::cout << "Cost: $" << myCoffee->cost() << std::endl;

    std::cout << "Description: " << myMilk->getDescription() << std::endl;
    std::cout << "Cost: $" << myMilk->cost() << std::endl;

    delete myCoffee;

    system("pause");
    return 0;
}
