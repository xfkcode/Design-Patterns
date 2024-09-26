#include <iostream>
#include <memory>

using namespace std;

class subject {
public:
    virtual void request() = 0;
    virtual ~subject() = default;
};

class realsubject : public subject {
public:
    void request() override {
        cout << "real subject OP" << endl;
    }
};

class proxy : public subject {
private:
    realsubject* rs;
public:
    proxy() {
        rs = new realsubject();
    }
    ~proxy() {
        delete rs;
    }

    void request() override {
        rs->request();
    }
};

int main(int argc, char const *argv[])
{
    proxy p;
    p.request();
    system("pause");
    return 0;
}
