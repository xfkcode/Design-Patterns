#include <iostream>
#include <memory>

using namespace std;

class Strategy {
public:
    virtual void execute() = 0;
    virtual ~Strategy() = default;
};

class StrategyA : public Strategy {
public:
    void execute() override {
        cout << "Strategy A OP" << endl; 
    }
};

class StrategyB : public Strategy {
public:
    void execute() override {
        cout << "Strategy B OP" << endl; 
    }
};

class Context {
private:
    unique_ptr<Strategy> strategy;
public:
    void setStrategy(unique_ptr<Strategy> str) {
        strategy = move(str);
    }

    void execStr() {
        if(strategy) {
            strategy->execute();
        }
    }
};

int main(int argc, char const *argv[])
{
    Context context;

    context.setStrategy(make_unique<StrategyA>());
    context.execStr();

    context.setStrategy(make_unique<StrategyB>());
    context.execStr();

    system("pause");
    return 0;
}
