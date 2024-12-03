#include <iostream>
#include <string>
#include <memory>

// 抽象表达式类
class AbstractExpression {
public:
    virtual ~AbstractExpression() = default;
    virtual int interpret() const = 0;
};

class Number : public AbstractExpression {
private:
    int number;  
public:
    Number(int num) : number(num) {}
    int interpret() const override {
        return number;
    }
};

class Add : public AbstractExpression {
private:
    std::shared_ptr<AbstractExpression> left;
    std::shared_ptr<AbstractExpression> right;
public:
    Add(std::shared_ptr<AbstractExpression> l, std::shared_ptr<AbstractExpression> r) : left(l), right(r) {}
    int interpret() const override {
        return left->interpret() + right->interpret();
    }
};

class Subtract : public AbstractExpression {
private:
    std::shared_ptr<AbstractExpression> left;
    std::shared_ptr<AbstractExpression> right;  
public:
    Subtract(std::shared_ptr<AbstractExpression> l, std::shared_ptr<AbstractExpression> r) : left(l), right(r) {}
    int interpret() const override {
        return left->interpret() - right->interpret();
    }
};

int main(int argc, char const *argv[]) {
    std::shared_ptr<AbstractExpression> expression = std::make_shared<Add>(
        std::make_shared<Number>(1),
        std::make_shared<Subtract>(
            std::make_shared<Number>(20),
            std::make_shared<Number>(3)
        )
    );

    std::cout << expression->interpret() << std::endl;
    return 0;
}