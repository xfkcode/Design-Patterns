#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

class Observer {
public:
    virtual void update(int state) = 0;
};

class Subject {
private:
    vector<Observer*> observers;
    int state;
public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void detach(Observer* observer) {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void setState(int state) {
        this->state = state;
        notify();
    }

    int getState() const {
        return this->state;
    }

    void notify() {
        for(auto observer : observers) {
            observer->update(this->state);
        }
    }
};

class ConcreteObserver : public Observer {
public:
    ConcreteObserver(const string& n) : name(n) {}
    void update(int state) override {
        cout << "Observer" << name << "notified. New state: " << state << endl;
    }
private:
    string name;
};

int main(int argc, char const *argv[])
{
    Subject subject;
    ConcreteObserver ob1("Ob 1");
    ConcreteObserver ob2("Ob 2");

    subject.attach(&ob1);
    subject.attach(&ob2);

    subject.setState(1);
    subject.setState(2);

    subject.detach(&ob1);
    subject.setState(3);

    system("pause");
    return 0;
}
