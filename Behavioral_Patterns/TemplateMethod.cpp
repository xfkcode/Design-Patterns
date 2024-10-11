#include <iostream>
#include <memory>  // 包含智能指针库
using namespace std;

// 抽象基类，定义了算法的模板方法
class AbstractClass {
public:
    // 模板方法，定义算法的骨架
    void TemplateMethod() {
        Step1();
        Step2();
        Step3();
    }

    // 具体步骤
    void Step1() {
        cout << "Step 1: Common for all." << endl;
    }

    // 可变步骤，需要子类实现
    virtual void Step2() = 0;

    // 具体步骤
    void Step3() {
        cout << "Step 3: Common for all." << endl;
    }

    // 虚析构函数，确保子类析构时正确调用
    virtual ~AbstractClass() {}
};

// 具体子类 1，实现可变步骤
class ConcreteClassA : public AbstractClass {
public:
    void Step2() override {
        cout << "Step 2: ConcreteClassA implementation." << endl;
    }
};

// 具体子类 2，实现可变步骤
class ConcreteClassB : public AbstractClass {
public:
    void Step2() override {
        cout << "Step 2: ConcreteClassB implementation." << endl;
    }
};

int main() {
    // 使用 std::shared_ptr 管理内存
    shared_ptr<AbstractClass> classA = make_shared<ConcreteClassA>();
    shared_ptr<AbstractClass> classB = make_shared<ConcreteClassB>();

    cout << "ConcreteClassA:" << endl;
    classA->TemplateMethod();  // 使用 ConcreteClassA 的实现

    cout << "\nConcreteClassB:" << endl;
    classB->TemplateMethod();  // 使用 ConcreteClassB 的实现

    // 不需要手动释放内存，shared_ptr 会自动处理
    return 0;
}
