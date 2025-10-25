#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

class AnimalUtil {
public:
    enum Animal { DOG = 1, CAT, BIRD, FISH };
    
    static const char* toStr(Animal a) {
        switch (a) {
            case DOG:  return "Dog";
            case CAT:  return "Cat";
            case BIRD: return "Bird";
            case FISH: return "Fish";
            default:   return "Unknown";
        }
    }
};

const std::string staticWelcomeMessage = "Welcome to the Animal Guesser!";

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // For Question #5: Print staticWelcomeMessage address (MOVED INSIDE MAIN)
    std::cout << "staticWelcomeMessage address: " << &staticWelcomeMessage << "\n\n";

    std::cout << staticWelcomeMessage << "\n";
    std::cout << "Guess the Animal! (1: Dog, 2: Cat, 3: Bird, 4: Fish)\n";
    std::cout << "Enter 0 to quit.\n";

    AnimalUtil::Animal* mysteryAnimal = nullptr;

    // ERROR #1 - COMMENTED OUT
    // Trying to use pointer before it points to anything valid
    // std::cout << "The animal is initialized to: " << AnimalUtil::toStr(*mysteryAnimal) << "\n";
    
    // ERROR #2 - COMMENTED OUT
    // Trying to use a nullptr pointer crashes the program
    // mysteryAnimal = nullptr;
    // std::cout << "The animal should initally be nothing: " << AnimalUtil::toStr(*mysteryAnimal) << "\n";
    
    while (true) {
        // ERROR #3 FIX - Delete old memory before creating new
        // Without this, memory leaks after every round
        if (mysteryAnimal != nullptr) {
            delete mysteryAnimal;
        }
        
        mysteryAnimal = new AnimalUtil::Animal(
            static_cast<AnimalUtil::Animal>(1 + std::rand() % 4));
        
        // For Question #4: Print memory addresses
        std::cout << "\n=== Memory Diagnostic ===" << "\n";
        std::cout << "Address of pointer variable: " << &mysteryAnimal << "\n";
        std::cout << "Address pointer is pointing to: " << mysteryAnimal << "\n";
        std::cout << "Value at that address: " << *mysteryAnimal 
                  << " (" << AnimalUtil::toStr(*mysteryAnimal) << ")" << "\n";
        std::cout << "========================\n";
        
        std::cout << "\nYour guess: ";
        int guess = -1;
        if (!(std::cin >> guess)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input; try again.\n";
            continue;
        }
        if (guess == 0) {
            std::cout << "Bye!\n";
            break;
        }
        
        // incorporating validation 
        if (guess < 1 || guess > 4) {
            std::cout << "Invalid choice! Please enter 1-4 (or 0 to quit).\n";
            continue;
        }
        
        if (*mysteryAnimal == static_cast<AnimalUtil::Animal>(guess)) {
            std::cout << "Correct! It was " << AnimalUtil::toStr(*mysteryAnimal) << "\n";
        } else {
            std::cout << "Wrong! It was " << AnimalUtil::toStr(*mysteryAnimal) << "\n";
        }
    }
    
    delete mysteryAnimal;
    return 0;
}