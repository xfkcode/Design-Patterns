#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Mediator;

class Colleague {
protected:
    Mediator* mediator;
public:
    Colleague(Mediator* med) : mediator(med) {}
    void setMediator(Mediator* med) {
        mediator = med;
    }
    virtual void send(const string& message) = 0;
    virtual void receive(const string& message) = 0; 
};

class Mediator {
public:
    virtual void notify(Colleague* sender, const string& message) = 0;
};

class ConcreteColleagueA : public Colleague {
public:
    using Colleague::Colleague;

    void send(const string& message) override {
        cout << "Colleague A sends: " << message << endl;
        mediator->notify(this, message);
    }

    void receive(const string& message) override {
        cout << "Colleague A receives: " << message << endl;
    }
};

class ConcreteColleagueB : public Colleague {
public:
    using Colleague::Colleague;

    void send(const string& message) override {
        cout << "Colleague B sends: " << message << endl;
        mediator->notify(this, message);
    }

    void receive(const string& message) override {
        cout << "Colleague B receives: " << message << endl;
    }
};

class ConcreteMediator : public Mediator {
private:
    ConcreteColleagueA* cA;
    ConcreteColleagueB* cB;
public:
    ConcreteMediator(ConcreteColleagueA* a, ConcreteColleagueB* b) : cA(a), cB(b) {}
    void notify(Colleague* sender, const string& message) override {
        if(sender == cA) {
            cB->receive(message);
        } else if (sender == cB) {
            cA->receive(message);
        }
    }
};

int main(int argc, char const *argv[])
{
    ConcreteColleagueA* a = new ConcreteColleagueA(nullptr);
    ConcreteColleagueB* b = new ConcreteColleagueB(nullptr);
    ConcreteMediator* mediator = new ConcreteMediator(a, b);

    a->setMediator(mediator);
    b->setMediator(mediator);

    a->send("Hello from A");
    b->send("Hello from B");

    delete a;
    delete b;
    delete mediator;

    system("pause");
    return 0;
}

