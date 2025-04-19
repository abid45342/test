#include <iostream>
#include <string>
#include <gtest/gtest.h>
using namespace std;

// Base interface
class Beverage {
public:
    virtual string getDescription() = 0;
    virtual double cost() = 0;
    virtual ~Beverage() {}
};

// Concrete base class
class Espresso : public Beverage {
public:
    string getDescription() override {
        return "Espresso";
    }
    double cost() override {
        return 1.99;
    }
};

// Another concrete base class
class HouseBlend : public Beverage {
public:
    string getDescription() override {
        return "House Blend Coffee";
    }
    double cost() override {
        return 1.50;
    }
};

// Decorator base class
class CondimentDecorator : public Beverage {
public:
    virtual string getDescription() = 0;
};

// Milk decorator
class Milk : public CondimentDecorator {
private:
    Beverage* beverage;
public:
    Milk(Beverage* b) {
        beverage = b;
    }
    string getDescription() override {
        return beverage->getDescription() + ", Milk";
    }
    double cost() override {
        return beverage->cost() + 0.20;
    }
};

// Sugar decorator
class Sugar : public CondimentDecorator {
private:
    Beverage* beverage;
public:
    Sugar(Beverage* b) {
        beverage = b;
    }
    string getDescription() override {
        return beverage->getDescription() + ", Sugar";
    }
    double cost() override {
        return beverage->cost() + 0.15;
    }
};

// ---------- Test Cases ----------

TEST(DecoratorTest, EspressoOnly) {
    Beverage* drink = new Espresso();
    EXPECT_EQ(drink->getDescription(), "Espresso");
    EXPECT_DOUBLE_EQ(drink->cost(), 1.99);
    delete drink;
}

TEST(DecoratorTest, EspressoWithMilk) {
    Beverage* drink = new Milk(new Espresso());
    EXPECT_EQ(drink->getDescription(), "Espresso, Milk");
    EXPECT_DOUBLE_EQ(drink->cost(), 2.19);
    delete drink;
}

TEST(DecoratorTest, HouseBlendWithMilkAndSugar) {
    Beverage* drink = new HouseBlend();
    drink = new Milk(drink);
    drink = new Sugar(drink);
    EXPECT_EQ(drink->getDescription(), "House Blend Coffee, Milk, Sugar");
    EXPECT_DOUBLE_EQ(drink->cost(), 1.85);
    delete drink;
}

// ---------- Main ----------
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
