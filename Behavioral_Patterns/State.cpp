#include <iostream>
#include <memory>

using namespace std;

class Character;

class State {
public:
    virtual ~State() = default;
    virtual void handle(Character* character) = 0;
};

class Character {
private:
    unique_ptr<State> currState;
public:
    Character(unique_ptr<State> state_ptr) : currState(move(state_ptr)) {}

    void setState(unique_ptr<State> s) {
        currState = move(s);
    }

    void handle() {
        currState->handle(this);
    }
};


class Running : public State {
public:
    void handle(Character* character) override {
        cout << "Running" << endl;
    }

};

class Walking : public State {
public:
    void handle(Character* character) override {
        cout << "Walking" << endl;
        character->setState(make_unique<Running>());
    }
};


int main(int argc, char const *argv[])
{
    unique_ptr<Character> c = make_unique<Character>(make_unique<Walking>());

    for(int i=0; i<2; i++) {
        c->handle();
    }

    system("pause");
    return 0;
}
