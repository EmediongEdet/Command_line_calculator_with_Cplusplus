#include <iostream>
#include <list> // Include the STL list header
#include <stdexcept>
#include <limits> // For numeric_limits
#include <cmath>  // For pow function
#include <string> // For converting int to str


using namespace std;

// Base class: Calculator
class Calculator {
    std::list<string> history; // To store the history of operations

public:
    // Function to display the menu of available operations
    virtual void displayMenu() {
        cout << "Select an operation: \n";
        cout << "1. Addition \n";
        cout << "2. Subtraction \n";
        cout << "3. Multiplication \n";
        cout << "4. Division \n";
        cout << "5. Modulo \n"; // New operation
        cout << "6. Power \n";   // New operation
        cout << "7. View History \n";
        cout << "8. Exit \n";
    }

    // Function to get and validate user input (number)
    int getInput() {
        int num;
        while (true) {
            cout << "Please enter a number: ";
            cin >> num;

            // If user enters a non-numeric input, clear the error state
            if (cin.fail()) {
                cin.clear(); // Clear the fail state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "Invalid input. Please enter an integer.\n";
            }
            else {
                return num; // Return the valid integer input
            }
        }
    }

    // Virtual function to perform the selected operation
    virtual int performOperation(int operation, int num1, int num2) {
        int result = 0;
        string operationStr;

        switch (operation) {
        case 1: // Addition
            result = num1 + num2;
            operationStr = to_string(num1) + " + " + to_string(num2) + " = " + to_string(result);
            break;

        case 2: // Subtraction
            result = num1 - num2;
            operationStr = to_string(num1) + " - " + to_string(num2) + " = " + to_string(result);
            break;

        case 3: // Multiplication
            result = num1 * num2;
            operationStr = to_string(num1) + " * " + to_string(num2) + " = " + to_string(result);
            break;

        case 4: // Division
            if (num2 == 0) {
                cout << "Error: Division by zero is not allowed.\n";
                return 0;
            }
            result = num1 / num2;
            operationStr = to_string(num1) + " / " + to_string(num2) + " = " + to_string(result);
            break;

        case 5: // Modulo
            if (num2 == 0) {
                cout << "Error: Modulo by zero is not allowed. \n";
                return 0;
            }
            return num1 % num2;

        case 6: // Power
            return static_cast<int>(pow(num1, num2));

        default: // If an invalid operation is selected
            cout << "Invalid operation selected.\n";
            return 0;
        }

        history.push_back(operationStr); // Store the operation in history
        return result;
    }

    // Function to display the history of operations
    void displayHistory() {
        if (history.empty()) {
            cout << "No history available.\n";
        }
        else {
            cout << "Operation History:\n";
            for (const auto& entry : history) {
                cout << entry << endl;
            }
        }
    }

    // Function to run the main calculator program
    void run() {
        while (true) { // Start an infinite loop for the program
            displayMenu(); // Display the menu of operations

            int userChoice;
            cout << "Enter your choice: ";
            cin >> userChoice;

            // Handle menu options
            if (userChoice == 8) {
                cout << "Exiting...\n";
                break;
            }

            if (userChoice == 7) {
                displayHistory();
                continue;
            }

            if (userChoice < 1 || userChoice > 8 || cin.fail()) {
                cin.clear(); // Clear the fail state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "Invalid choice. Please select a valid operation.\n";
                continue;
            }

            // If the user's choice is valid, proceed with the operation
            int num1 = getInput();
            int num2 = getInput();
            int result = performOperation(userChoice, num1, num2);
            cout << "Result: " << result << endl;
        }
    }
};

// Derived class: AdvancedCalculator
class AdvancedCalculator : public Calculator {
public:
    // Override displayMenu to include more options for advanced operations
    void displayMenu() override {
        cout << "Select an operation: \n";
        cout << "1. Addition \n";
        cout << "2. Subtraction \n";
        cout << "3. Multiplication \n";
        cout << "4. Division \n";
        cout << "5. Modulo \n"; // New operation
        cout << "6. Power \n";   // New operation
        cout << "7. View History \n";
        cout << "8. Exit \n";
    }

    // Override performOperation to handle new operations like Modulo and Power
    int performOperation(int operation, int num1, int num2) override {
        switch (operation) {
        case 1: // Addition
            return num1 + num2;

        case 2: // Subtraction
            return num1 - num2;

        case 3: // Multiplication
            return num1 * num2;

        case 4: // Division
            if (num2 == 0) { // Check for division by zero
                cout << "Error: Division by zero is not allowed. \n";
                return 0; // Return 0 if division by zero occurs
            }
            return num1 / num2; // Perform the division

        case 5: // Modulo
            if (num2 == 0) {
                cout << "Error: Modulo by zero is not allowed. \n";
                return 0;
            }
            return num1 % num2;

        case 6: // Power
            return static_cast<int>(pow(num1, num2));

        default: // If an invalid operation is selected
            cout << "Invalid operation selected. \n";
            return 0;
        }
    }
};

// Main function, entry point of the program
int main() {
    // Create a pointer to the base class and point it to the derived class object
    Calculator* calculator = new AdvancedCalculator(); // Create an object of the derived class

    calculator->run(); // Call the `run` method to start the calculator program

    delete calculator; // Clean up memory
    return 0; // Return 0 to indicate successful execution
}
