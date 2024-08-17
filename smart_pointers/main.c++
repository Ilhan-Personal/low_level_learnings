#include <iostream>
#include <memory>

using namespace std;

class Car {
private:
    int speed;
    int gear;
    std::string color;
public:
    void setSpeed(int speed) {
        this->speed = speed;
    }
    void getSpeed() {
        std::cout << "Speed: " << this->speed << std::endl;
    }

    void drive() {
        std::cout << "Driving the car" << std::endl;
    }
};

void useSmartPointer() {
    try {
        // Create a unique_ptr to manage the Car object
        std::unique_ptr<Car> carPtr = std::make_unique<Car>();
        
        carPtr->drive();
        
        carPtr->setSpeed(10);
        carPtr->getSpeed();
        
        // Simulate an exception
        throw std::runtime_error("An error occurred while using smart pointer");
        
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

int main() {
    cout << "Using smart pointer:" << endl;
    useSmartPointer();

    return 0;
}