#include <memory>
#include <iostream>

using namespace std;

// 颜色
class Color {
public:
    virtual ~Color() = default;
    virtual std::string fill() = 0;
};
class REDcolor : public Color {
public:
    std::string fill() override {
        return "Red";
    }
};
class BLUEcolor : public Color {
public:
    std::string fill() override {
        return "Blue";
    }
};

// 形状
class shape {
public:
    shape(std::shared_ptr<Color> color_ptr) : color(std::move(color_ptr)) {}
    virtual ~shape() = default;
    virtual void draw() const = 0;

protected:
    std::shared_ptr<Color> color;
};
class Circle : public shape {
public:
    Circle(int radius, std::shared_ptr<Color> color_ptr) : shape(std::move(color_ptr)), radius(radius) {}
    void draw() const override {
        std::cout << "Drawing a Circle with radius " << radius << " and color " << color->fill() << "." << std::endl;
    }
private:
    int radius;
};
class Square : public shape {
public:
    Square(int side, std::shared_ptr<Color> color_ptr) : shape(std::move(color_ptr)), side(side) {}

    void draw() const override {
        std::cout << "Drawing a Square with side " << side << " and color " << color->fill() << "." << std::endl;
    }
private:
    int side;
};

int main(int argc, char const *argv[])
{
    std::shared_ptr<Color> red = std::make_shared<REDcolor>();
    std::shared_ptr<Color> blue = std::make_shared<BLUEcolor>();

    std::shared_ptr<shape> c = std::make_shared<Circle>(5, red);
    std::shared_ptr<shape> s = std::make_shared<Square>(5, blue);

    c->draw();
    s->draw();

    system("pause");
    return 0;
}
