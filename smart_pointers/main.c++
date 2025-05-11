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

void useRawPointer() {
    while (1) {
        // Create a raw pointer to manage the Car object
        Car* carPtr = new Car();
        
        try {
            carPtr->drive();
            carPtr->setSpeed(10);
            carPtr->getSpeed();
            
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void useSmartPointer() {
    while (1) {
        try {
            // Create a unique_ptr to manage the Car object
            std::unique_ptr<Car> carPtr = std::make_unique<Car>();
            
            carPtr->drive();
            carPtr->setSpeed(10);
            carPtr->getSpeed();
            
            // Simulate an exception
            // throw std::runtime_error("An error occurred while using smart pointer");
            
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            // No need to manually delete the smart pointer, it will be automatically deleted
        }
    }
}

int main() {
    cout << "Using raw pointer:" << endl;
    // Uncomment the following line to test raw pointers
    useRawPointer();
    
    // cout << "Using smart pointer:" << endl;
    // useSmartPointer();

    return 0;
}