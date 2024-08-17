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

int main() {
    // Create a unique_ptr to manage the Car object
    std::unique_ptr<Car> carPtr = std::make_unique<Car>();
    
    // Use the car object through the smart pointer
    carPtr->drive();
    
    // The car object will be automatically deleted when the unique_ptr goes out of scope
    carPtr->setSpeed(10);
    carPtr->getSpeed();

    return 0;
}