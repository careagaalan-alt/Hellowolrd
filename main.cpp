#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// function declarations up front so everything knows what's available
bool isDna(string s);
bool isRna(string s);
string dnaOpposite(string s);
string rnaOpposite(string s);
bool getNextLine(ifstream &fin, string &line);

int main() {
    string filename;
    char sequenceType;

    // grab the filename from user - pretty straightforward
    cout << "Enter input filename: ";
    cin >> filename;

    // find out if we're dealing with DNA or RNA
    cout << "Is this file DNA or RNA sequences? (D/R): ";
    cin >> sequenceType;

    // open up the input file, bail if it doesn't exist
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    // set up the output file for results
    ofstream fout("results.txt");
    if (!fout.is_open()) {
        cerr << "Error: Could not create results.txt" << endl;
        return 1;
    }

    // run through each sequence in the file
    string line;
    while (getNextLine(fin, line)) {
        bool valid = false;
        string complement = "";

        // check the sequence based on what type the user said it was
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

        // write everything to the results file
        if (valid) {
            fout << line << " is valid." << endl;
            fout << "Complement: " << complement << endl;
        } else {
            fout << line << " is not valid." << endl;
        }
    }

    // clean up and close the files
    fin.close();
    fout.close();

    // let the user know we're done
    cout << "Processing complete. Results written to results.txt" << endl;

    return 0;
}

// validates DNA sequences - only accepts uppercase A, T, C, G
bool isDna(string s) {
    for (int i = 0; i < s.length(); i++) {
        char base = s[i];
        if (base != 'A' && base != 'T' && base != 'C' && base != 'G') {
            return false;
        }
    }
    return true;
}

// validates RNA sequences - only accepts uppercase A, U, C, G
bool isRna(string s) {
    for (int i = 0; i < s.length(); i++) {
        char base = s[i];
        if (base != 'A' && base != 'U' && base != 'C' && base != 'G') {
            return false;
        }
    }
    return true;
}

// builds the complement strand for DNA - A pairs with T, C pairs with G
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

// builds the complement strand for RNA - A pairs with U, C pairs with G
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

// pulls the next line from the file, returns true if we got one
bool getNextLine(ifstream &fin, string &line) {
    if (getline(fin, line)) {
        return true;
    }
    return false;
}
