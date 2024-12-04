#include <iostream>
#include <memory>
#include <vector>
#include <string>

class FileSysEntity {
public:
    virtual ~FileSysEntity() = default;
    virtual void show(int depth = 0) const = 0;
};

class File : public FileSysEntity {
private:
    std::string name;
public:
    File(const std::string& name) : name(name) {}

    void show(int depth = 0) const override {
        std::cout << std::string(depth, '-') << "File: " << name << std::endl;
    }
};

class Directory : public FileSysEntity {
private:
    std::string name;
    std::vector<std::shared_ptr<FileSysEntity>> children;
public:
    explicit Directory(const std::string& name) : name(name) {}
    void add(const std::shared_ptr<FileSysEntity>& entity) {
        children.push_back(entity);
    }
    void show(int depth = 0) const override {
        std::cout << std::string(depth, '-') << "Directory: " << name << std::endl;
        for (const auto& child : children) {
            child->show(depth + 2);
        }
    }
};

int main(int argc, char const *argv[]) {
    auto file1 = std::make_shared<File>("file1.txt");
    auto file2 = std::make_shared<File>("file2.txt");
    auto file3 = std::make_shared<File>("file3.txt");

    auto dir1 = std::make_shared<Directory>("dir1");
    auto dir2 = std::make_shared<Directory>("dir2");
    auto root = std::make_shared<Directory>("root");

    dir1->add(file1);
    dir1->add(file2);
    dir2->add(file3);
    root->add(dir1);
    root->add(dir2);

    root->show();

    return 0;
}