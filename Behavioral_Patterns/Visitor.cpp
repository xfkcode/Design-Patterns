#include <iostream>
#include <vector>
#include <string>
#include <memory>

// 前向声明 Visitor 类
class File;
class Folder;
class Visitor;

// 元素接口
class FileSystemElement {
public:
    virtual ~FileSystemElement() = default;
    virtual void accept(Visitor& visitor) = 0; // 接受访问者
};

// 具体元素：文件
class File : public FileSystemElement {
public:
    File(const std::string& name, size_t size) : name_(name), size_(size) {}

    const std::string& getName() const { return name_; }
    size_t getSize() const { return size_; }

    void accept(Visitor& visitor) override;

private:
    std::string name_;
    size_t size_;
};

// 具体元素：文件夹
class Folder : public FileSystemElement {
public:
    Folder(const std::string& name) : name_(name) {}

    void addElement(std::unique_ptr<FileSystemElement> element) {
        elements_.push_back(std::move(element));
    }

    const std::string& getName() const { return name_; }
    const std::vector<std::unique_ptr<FileSystemElement>>& getElements() const {
        return elements_;
    }

    void accept(Visitor& visitor) override;

private:
    std::string name_;
    std::vector<std::unique_ptr<FileSystemElement>> elements_;
};

// 访问者接口
class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(File& file) = 0;
    virtual void visit(Folder& folder) = 0;
};

// 具体访问者：统计文件系统大小
class SizeCalculator : public Visitor {
public:
    void visit(File& file) override {
        totalSize_ += file.getSize();
    }

    void visit(Folder& folder) override {
        for (const auto& element : folder.getElements()) {
            element->accept(*this); // 递归访问文件夹内的元素
        }
    }

    size_t getTotalSize() const { return totalSize_; }

private:
    size_t totalSize_ = 0;
};

// 具体访问者：压缩文件
class Compressor : public Visitor {
public:
    void visit(File& file) override {
        std::cout << "Compressing file: " << file.getName() << "\n";
    }

    void visit(Folder& folder) override {
        for (const auto& element : folder.getElements()) {
            element->accept(*this); // 递归压缩文件夹内的元素
        }
    }
};

// 具体访问者：列出文件夹内容
class FolderLister : public Visitor {
public:
    void visit(File& file) override {
        std::cout << "File: " << file.getName() << "\n";
    }

    void visit(Folder& folder) override {
        std::cout << "Folder: " << folder.getName() << "\n";
        for (const auto& element : folder.getElements()) {
            element->accept(*this); // 递归列出文件夹内的元素
        }
    }
};

// accept 方法实现
void File::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void Folder::accept(Visitor& visitor) {
    visitor.visit(*this);
}

int main(int argc, char const *argv[]) {
    // 构建文件系统
    auto root = std::make_unique<Folder>("root");
    root->addElement(std::make_unique<File>("file1.txt", 500));
    root->addElement(std::make_unique<File>("file2.txt", 300));

    auto subFolder = std::make_unique<Folder>("subfolder");
    subFolder->addElement(std::make_unique<File>("file3.txt", 200));
    subFolder->addElement(std::make_unique<File>("file4.txt", 100));

    root->addElement(std::move(subFolder));

    // 1. 统计文件系统总大小
    SizeCalculator sizeCalculator;
    root->accept(sizeCalculator);
    std::cout << "Total size: " << sizeCalculator.getTotalSize() << " bytes\n";

    // 2. 压缩文件系统
    Compressor compressor;
    root->accept(compressor);

    // 3. 列出文件系统内容
    FolderLister folderLister;
    root->accept(folderLister);

    return 0;
}

