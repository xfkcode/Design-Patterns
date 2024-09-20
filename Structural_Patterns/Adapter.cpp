#include <iostream>
#include <string>

class TargetPrint {
public:
    virtual void printstring(const std::string& str) = 0;
    virtual ~TargetPrint() = default;
};

class Oldprint {
public:
    void Print(const char* str) {
        std::cout << "Old Printer: " << str << std::endl;
    }
};

class PrinterAdapter_Ins : public TargetPrint {
public:
    PrinterAdapter_Ins(Oldprint& printer) : oldprinter(printer) {}

    void printstring(const std::string& str) override {
        oldprinter.Print(str.c_str());
    }
private:
    Oldprint& oldprinter;
};

class PrinterAdapter_class : public TargetPrint, private Oldprint {
public:
    void printstring(const std::string& str) override {
        Print(str.c_str());
    }
};

void printDocument(TargetPrint& printer, const std::string& document) {
    printer.printstring(document);
}

int main(int argc, char const *argv[])
{
    Oldprint oldprinter;
    PrinterAdapter_Ins adapter_ins(oldprinter);
    printDocument(adapter_ins, "Hello, world");

    PrinterAdapter_class adapter_class;
    printDocument(adapter_class, "Hello, world");

    system("pause");
    return 0;
}
