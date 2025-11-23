#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Llama struct - represents a passenger with a name and fancy hat
struct Llama {
    string name;
    string hat;

    // Set the llama's name with validation
    void setName(string n) {
        if (!n.empty()) {
            name = n;
        }
    }

    // Set the llama's hat with validation
    void setHat(string h) {
        if (!h.empty()) {
            hat = h;
        }
    }

    // Get the llama's name
    string getName() {
        return name;
    }

    // Get the llama's hat
    string getHat() {
        return hat;
    }

    // Print passenger information
    void printPassenger() {
        cout << "Passenger " << name << " is wearing a " << hat << "." << endl;
    }
};

// Ship struct - stores multiple passengers and manages the manifest
struct Ship {
    Llama passengers[10];
    int numPassengers;

    // Initialize ship with no passengers
    void init() {
        numPassengers = 0;
    }

    // Check if ship is full
    bool isFull() {
        return numPassengers >= 10;
    }

    // Board a passenger onto the ship
    void boardPassenger(Llama &passenger) {
        if (!isFull()) {
            passengers[numPassengers] = passenger;
            numPassengers++;
            cout << "Passenger " << passenger.getName() << " boarded with a "
                 << passenger.getHat() << "." << endl;
        } else {
            cout << "Ship is full! Cannot board more passengers." << endl;
        }
    }

    // Disembark all passengers in LIFO order
    void disembarkAll() {
        if (numPassengers == 0) {
            cout << "Ship is empty! No passengers to disembark." << endl;
            return;
        }

        cout << "\n===== Disembarking all passengers =====" << endl;
        // Remove passengers in LIFO order (last in, first out)
        for (int i = numPassengers - 1; i >= 0; i--) {
            cout << "Passenger " << passengers[i].getName() << " has disembarked." << endl;
        }
        numPassengers = 0;
    }

    // Clear ship without printing individual messages
    void clearShip() {
        numPassengers = 0;
    }

    // Print the ship manifest
    void printManifest() {
        cout << "\n===== Cruise Passenger Manifest =====" << endl;
        if (numPassengers == 0) {
            cout << "(No passengers)" << endl;
        } else {
            for (int i = 0; i < numPassengers; i++) {
                passengers[i].printPassenger();
            }
        }
    }

    // Load passengers from file (overwrites current passengers)
    void loadFromFile() {
        ifstream inFile("llamas.dat");

        if (!inFile.is_open()) {
            cout << "No passenger data found in file." << endl;
            return;
        }

        // Clear current passengers
        numPassengers = 0;

        string name, hat;
        // Read passengers from file (name on one line, hat on next)
        while (numPassengers < 10 && getline(inFile, name) && getline(inFile, hat)) {
            if (!name.empty() && !hat.empty()) {
                passengers[numPassengers].setName(name);
                passengers[numPassengers].setHat(hat);
                numPassengers++;
            }
        }

        inFile.close();

        if (numPassengers == 0) {
            cout << "No passenger data found in file." << endl;
        } else {
            cout << "Loaded passengers from llamas.dat." << endl;
        }
    }

    // Save passengers to file
    void saveToFile() {
        ofstream outFile("llamas.dat");

        if (!outFile.is_open()) {
            cout << "Error: Could not save to file." << endl;
            return;
        }

        // Write each passenger as two lines: name, then hat
        for (int i = 0; i < numPassengers; i++) {
            outFile << passengers[i].getName() << endl;
            outFile << passengers[i].getHat() << endl;
        }

        outFile.close();
        cout << "Passenger data saved to llamas.dat." << endl;
    }
};

// Display the main menu
void displayMenu() {
    cout << "\n===== Llama Cruise Menu =====" << endl;
    cout << "1. Board a passenger" << endl;
    cout << "2. Disembark all passengers" << endl;
    cout << "3. Print ship manifest" << endl;
    cout << "4. Clear ship" << endl;
    cout << "5. Load passenger data from file" << endl;
    cout << "6. Save passenger data to file" << endl;
    cout << "7. Exit" << endl;
    cout << "Choose an option: ";
}

int main() {
    Ship ship;
    ship.init();

    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear newline from input buffer

        if (choice == 1) {
            // Board a passenger
            if (ship.isFull()) {
                cout << "Ship is full! Cannot board more passengers." << endl;
            } else {
                Llama newPassenger;
                string name, hat;

                cout << "Enter passenger name: ";
                getline(cin, name);

                cout << "Enter hat type: ";
                getline(cin, hat);

                // Validate inputs
                if (name.empty() || hat.empty()) {
                    cout << "Error: Name and hat cannot be empty." << endl;
                } else {
                    newPassenger.setName(name);
                    newPassenger.setHat(hat);
                    ship.boardPassenger(newPassenger);
                }
            }
        }
        else if (choice == 2) {
            // Disembark all passengers
            ship.disembarkAll();
        }
        else if (choice == 3) {
            // Print ship manifest
            ship.printManifest();
        }
        else if (choice == 4) {
            // Clear ship
            ship.clearShip();
            cout << "Ship cleared." << endl;
        }
        else if (choice == 5) {
            // Load from file
            ship.loadFromFile();
        }
        else if (choice == 6) {
            // Save to file
            ship.saveToFile();
        }
        else if (choice == 7) {
            // Exit
            cout << "Exiting program." << endl;
            break;
        }
        else {
            cout << "Invalid option. Please choose 1-7." << endl;
        }
    }

    return 0;
}
