#include <iostream>

using namespace std;

class Singleton_1 {
public:
    static Singleton_1& getInstance() {
        // 使用静态局部变量，确保只创建一次实例
        static Singleton_1 instance;
        return instance;
    }

    Singleton_1(const Singleton_1&) = delete;
    Singleton_1& operator=(const Singleton_1&) = delete;

    void op() {
        cout << "Singleton instance is working" << endl;
    }

private:
    Singleton_1() {
        cout << "Singleton instance created.\n";
    }

    ~Singleton_1() {
        cout << "Singleton instance destroyed.\n";
    }
};

void RunSingleton_1() {
    Singleton_1& instance1 = Singleton_1::getInstance();
    instance1.op();

    Singleton_1& instance2 = Singleton_1::getInstance();
    instance2.op();
}

int main() {
    RunSingleton_1();

    system("pause");
    return 0;
}