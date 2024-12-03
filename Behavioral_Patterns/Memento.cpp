#include <iostream>
#include <string>
#include <memory>
#include <vector>

class Memento {
private:
    std::string state;
public:
    explicit Memento(const std::string& s) : state(s) {}
    std::string getState() const {
        return state;
    }
};

class Originator {
private:
    std::string state;
public:
    void setState(const std::string& s) {
        state = s;
    }
    std::string getState() const {
        return state;
    }
    std::shared_ptr<Memento> saveStateToMemento() {
        return std::make_shared<Memento>(state);
    }
    void getStateFromMemento(const std::shared_ptr<Memento>& m) {
        state = m->getState();
        std::cout << "State restored to: " << state << std::endl;
    }
};

class CareTaker {
private:
    std::vector<std::shared_ptr<Memento>> MementoList;
public:
    void add(const std::shared_ptr<Memento>& m) {
        MementoList.push_back(m);
    }
    std::shared_ptr<Memento> getMemento(int index) {
        if (index >= 0 && index < MementoList.size()) {
            return MementoList[index];
        }
        throw std::out_of_range("Invalid index for memento list");
    }
};

int main(int argc, char const *argv[]) {
    Originator originator;
    CareTaker caretaker;

    originator.setState("State1");
    caretaker.add(originator.saveStateToMemento());

    originator.setState("State2");
    caretaker.add(originator.saveStateToMemento());

    originator.setState("State3");

    std::cout << "Current state: " << originator.getState() << std::endl;

    originator.getStateFromMemento(caretaker.getMemento(0));
    originator.getStateFromMemento(caretaker.getMemento(1));

    return 0;
}