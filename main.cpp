#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function prototypes
bool isDna(string s);
bool isRna(string s);
string dnaOpposite(string s);
string rnaOpposite(string s);
bool getNextLine(ifstream &fin, string &line);

int main() {
    string filename;
    char sequenceType;

    // Get input filename from user
    cout << "Enter input filename: ";
    cin >> filename;

    // Get sequence type (DNA or RNA)
    cout << "Is this file DNA or RNA sequences? (D/R): ";
    cin >> sequenceType;

    // Open input file
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    // Open output file
    ofstream fout("results.txt");
    if (!fout.is_open()) {
        cerr << "Error: Could not create results.txt" << endl;
        return 1;
    }

    // Process each line from the input file
    string line;
    while (getNextLine(fin, line)) {
        bool valid = false;
        string complement = "";

        // Check if sequence is DNA or RNA based on user input
        if (sequenceType == 'D' || sequenceType == 'd') {
            valid = isDna(line);
            if (valid) {
                complement = dnaOpposite(line);
            }
        } else if (sequenceType == 'R' || sequenceType == 'r') {
            valid = isRna(line);
            if (valid) {
                complement = rnaOpposite(line);
            }
        }

        // Write results to output file
        if (valid) {
            fout << line << " is valid." << endl;
            fout << "Complement: " << complement << endl;
        } else {
            fout << line << " is not valid." << endl;
        }
    }

    // Close files
    fin.close();
    fout.close();

    // Print completion message
    cout << "Processing complete. Results written to results.txt" << endl;

    return 0;
}

// Check if a string is a valid DNA sequence
// Valid DNA contains only A, T, C, G (uppercase)
bool isDna(string s) {
    for (int i = 0; i < s.length(); i++) {
        char base = s[i];
        if (base != 'A' && base != 'T' && base != 'C' && base != 'G') {
            return false;
        }
    }
    return true;
}

// Check if a string is a valid RNA sequence
// Valid RNA contains only A, U, C, G (uppercase)
bool isRna(string s) {
    for (int i = 0; i < s.length(); i++) {
        char base = s[i];
        if (base != 'A' && base != 'U' && base != 'C' && base != 'G') {
            return false;
        }
    }
    return true;
}

// Generate the complement of a DNA sequence
// A ↔ T, C ↔ G
string dnaOpposite(string s) {
    string complement = "";
    for (int i = 0; i < s.length(); i++) {
        char base = s[i];
        if (base == 'A') {
            complement += 'T';
        } else if (base == 'T') {
            complement += 'A';
        } else if (base == 'C') {
            complement += 'G';
        } else if (base == 'G') {
            complement += 'C';
        }
    }
    return complement;
}

// Generate the complement of an RNA sequence
// A ↔ U, C ↔ G
string rnaOpposite(string s) {
    string complement = "";
    for (int i = 0; i < s.length(); i++) {
        char base = s[i];
        if (base == 'A') {
            complement += 'U';
        } else if (base == 'U') {
            complement += 'A';
        } else if (base == 'C') {
            complement += 'G';
        } else if (base == 'G') {
            complement += 'C';
        }
    }
    return complement;
}

// Read the next line from the input file
// Returns true if a line was read, false at EOF
bool getNextLine(ifstream &fin, string &line) {
    if (getline(fin, line)) {
        return true;
    }
    return false;
}
