#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
class Iterator {
public:
    virtual ~Iterator() {}
    virtual bool hasNext() = 0;
    virtual T next() = 0;
};

template<typename T>
class Aggregate {
public:
    virtual ~Aggregate() {}
    virtual Iterator<T>* createIterator() = 0;
};

template<typename T>
class ConcreteIterator : public Iterator<T> {
private:
    std::vector<T> items;
    int position = 0;
public:
    ConcreteIterator(const std::vector<T>& items) : items(items) {}
    bool hasNext() override {
        return position < items.size();
    }
    T next() override {
        if(hasNext()) {
            return items[position++];
        } else {
            throw std::out_of_range("No more elements");
        }
    }
};

template<typename T>
class ConcreteAggregate : public Aggregate<T> {
private:
    std::vector<T> items;
public:
    ConcreteAggregate(std::initializer_list<T> list) : items(list) {}
    Iterator<T>* createIterator() override {
        return new ConcreteIterator<T>(items);
    }
    void addItem(const T& item) {
        items.push_back(item);
    }
};

int main(int argc, char const *argv[])
{
    // 创建聚合对象并添加元素
    ConcreteAggregate<int> aggregate = {1, 2, 3, 4, 5};
    
    // 创建迭代器
    Iterator<int>* iterator = aggregate.createIterator();

    // 遍历元素
    while (iterator->hasNext()) {
        std::cout << iterator->next() << " ";
    }

    delete iterator;  // 不要忘记删除迭代器对象
    system("pause");
    return 0;
}
