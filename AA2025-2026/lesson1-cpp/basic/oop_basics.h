#ifndef OOP_BASICS_H
#define OOP_BASICS_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Shape {
protected:
    std::string name;
    
public:
    explicit Shape(const std::string& n) : name(n) {
        std::cout << "Shape constructor: " << name << "\n";
    }
    
    virtual ~Shape() {
        std::cout << "Shape destructor: " << name << "\n";
    }
    
    virtual double area() const = 0;
    
    virtual void display() const {
        std::cout << "Shape: " << name << "\n";
    }
    
    std::string get_name() const { return name; }
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : Shape("Circle"), radius(r) {
        std::cout << "Circle constructor, radius=" << radius << "\n";
    }
    
    ~Circle() override {
        std::cout << "Circle destructor\n";
    }
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    void display() const override {
        std::cout << "Circle with radius " << radius 
                  << ", area = " << area() << "\n";
    }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : Shape("Rectangle"), width(w), height(h) {
        std::cout << "Rectangle constructor, " << width << "x" << height << "\n";
    }
    
    ~Rectangle() override {
        std::cout << "Rectangle destructor\n";
    }
    
    double area() const override {
        return width * height;
    }
    
    void display() const override {
        std::cout << "Rectangle " << width << "x" << height 
                  << ", area = " << area() << "\n";
    }
};

class Drawable {
public:
    virtual void draw() const = 0;
    virtual ~Drawable() = default;
};

class Colorable {
public:
    virtual void set_color(const std::string& color) = 0;
    virtual ~Colorable() = default;
};

class ColoredCircle : public Circle, public Drawable, public Colorable {
private:
    std::string color;
    
public:
    ColoredCircle(double r, const std::string& c) 
        : Circle(r), color(c) {}
    
    void draw() const override {
        std::cout << "Drawing " << color << " circle\n";
    }
    
    void set_color(const std::string& c) override {
        color = c;
    }
};

class Complex {
private:
    double real, imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                      real * other.imag + imag * other.real);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real;
        if (c.imag >= 0) os << " + " << c.imag << "i";
        else os << " - " << -c.imag << "i";
        return os;
    }
};

void demonstrate_oop() {
    std::cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ OOP: inheritance, polymorphism, abstract classes, operators    │\n";
    std::cout << "└─────────────────────────────────────────────────────────────────┘\n";
    
    std::cout << "\n--- Polymorphism ---\n";
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    
    for (const auto& shape : shapes) {
        shape->display();
        std::cout << "Area: " << shape->area() << "\n";
    }
    
    std::cout << "\n--- Multiple Inheritance ---\n";
    ColoredCircle colored_circle(3.0, "Red");
    colored_circle.display();
    colored_circle.draw();
    colored_circle.set_color("Blue");
    colored_circle.draw();
    
    std::cout << "\n--- Operator Overloading ---\n";
    Complex c1(3, 4);
    Complex c2(1, -2);
    std::cout << "c1 = " << c1 << "\n";
    std::cout << "c2 = " << c2 << "\n";
    std::cout << "c1 + c2 = " << c1 + c2 << "\n";
    std::cout << "c1 * c2 = " << c1 * c2 << "\n";
}

#endif
