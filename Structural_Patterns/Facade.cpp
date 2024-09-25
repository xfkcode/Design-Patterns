#include <iostream>
#include <memory>

using namespace std;

class subsystemA {
public:
    void op() {
        cout << "subsystemA op" << endl;
    }
};

class subsystemB {
public:
    void op() {
        cout << "subsystemA op" << endl;
    }
};

class facade {
private:
    subsystemA* A;
    subsystemB* B;
public:
    facade() {
        A = new subsystemA();
        B = new subsystemB();
    }
    ~facade() {
        delete A;
        delete B;
    }

    void OP() {
        A->op();
        B->op();
    }
};


int main(int argc, char const *argv[])
{
    unique_ptr<facade> fa = make_unique<facade>(); 
    fa->OP();
    system("pause");
    return 0;
}
