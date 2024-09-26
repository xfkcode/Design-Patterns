#include <iostream>
#include <memory>

using namespace std;

class command {
public:
    virtual void execute() = 0;
    virtual ~command() = default;
};

class LightOn : public command {
public:
    void execute() override {
        cout << "Light On" << endl;
    }
};

class LightOff : public command {
public:
    void execute() override {
        cout << "Light Off" << endl;
    }
};

class RemoteControl {
private:
    shared_ptr<command> cmd;
public:
    void setCommand(shared_ptr<command> cmd) {
        this->cmd = cmd;       
    }

    void PressButton() {
        if(cmd) {
            this->cmd->execute();
        }
    }
};

int main(int argc, char const *argv[])
{
    shared_ptr<command> cmdOn = make_shared<LightOn>();
    shared_ptr<command> cmdOff = make_shared<LightOff>();

    RemoteControl rc;
    rc.setCommand(cmdOn);
    rc.PressButton();

    rc.setCommand(cmdOff);
    rc.PressButton();

    system("pause");
    return 0;
}
