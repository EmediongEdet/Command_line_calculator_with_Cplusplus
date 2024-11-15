#include <iostream>
#include <stdexcept>
#include <limits> // For numeric_limits

using namespace std;

// Base class: Calculator
class Calculator {
public:
    // Virtual function to display the menu of available operations
    virtual void displayMenu() {
        cout << "Select an operation: \n";
        cout << "1. Addition \n";
        cout << "2. Subtraction \n";
        cout << "3. Multiplication \n";
        cout << "4. Division \n";
        cout << "5. Exit \n";
    }

    // Function to get and validate user input (number)
    int getInput() {
        int num;
        while (true) {
            cout << "Please enter a number \n";
            cin >> num;

            // If user enters a non-numeric input, clear the error state
            if (cin.fail()) {
                cin.clear(); // Clear the fail state
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                throw invalid_argument("Invalid input. Please enter an integer.");
            }
            else {
                return num; // Return the valid integer input
            }
        }
    }

    // Virtual function to perform the selected operation (addition, subtraction, multiplication, division)
    virtual int performOperation(int operation, int num1, int num2) {
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
            else {
                return num1 / num2; // Perform the division
            }

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

    // Function to run the main calculator program
    void run() {
        while (true) { // Start an infinite loop for the program
            displayMenu(); // Display the menu of operations

            int userChoice; // Variable to store user's menu choice
            cout << "Enter your choice: ";
            cin >> userChoice; // Get the user's choice for operation

            // Check if user wants to exit the program (option 5)
            if (userChoice == 7) {
                cout << "Exiting... \n";
                break; // Exit the program
            }

            // If user enters a non-numeric input for operation, clear the error state
            if (cin.fail()) {
                cin.clear();  // Clear the fail state
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                cout << "Invalid input. Please select a valid operation \n";
                continue; // Skip to the next iteration of the loop
            }

            // If the user enters a value that is not within the list of valid choices (1-4)
            if (userChoice < 1 || userChoice > 7) {
                cout << "Invalid choice. Please select a valid operation \n";
                continue; // Ask for the choice again
            }

            // If the user's choice is valid (between 1 and 4), proceed with the operation
            try {
                cout << "Enter the first number: \n";
                int num1 = getInput(); // Get the first number

                cout << "Enter the second number: \n";
                int num2 = getInput(); // Get the second number

                // Perform the operation and display the result
                int result = performOperation(userChoice, num1, num2);
                if (result != INT_MIN) { // Check for invalid result (e.g., division by zero)
                    cout << "Result: " << result << endl;
                }
            }
            catch (const invalid_argument& e) {
                // Handle invalid input (non-integer input)
                cout << e.what() << endl;
            }
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
        cout << "7. Exit \n";
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
