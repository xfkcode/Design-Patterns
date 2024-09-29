#include <iostream>
#include <string>

using namespace std;

class Handle {
public:
    virtual ~Handle() = default;
    virtual void setNext(Handle* next) {
        nextHandle = next;
    }

    virtual void handleRequest(const string& request) {
        if(nextHandle) {
            nextHandle->handleRequest(request);
        }
    }
protected:
    Handle* nextHandle = nullptr;
};

class HandleA : public Handle {
public:
    void handleRequest(const string& request) override {
        if(request == "A") {
            cout << "A handle request" << endl;
        } else {
            Handle::handleRequest(request);
        }
    }
};

class HandleB : public Handle {
public:
    void handleRequest(const string& request) override {
        if(request == "B") {
            cout << "B handle request" << endl;
        } else {
            Handle::handleRequest(request);
        }
    }
};

int main(int argc, char const *argv[])
{
    HandleA handlerA;
    HandleB handlerB;

    handlerA.setNext(&handlerB);

    handlerA.handleRequest("A"); 
    handlerA.handleRequest("B");
    handlerA.handleRequest("C");

    system("pause");
    return 0;
}
