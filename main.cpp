#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    int linesPerPage, pages;

    // Print welcome message
    cout << "Welcome to the Babbage Log Engine" << endl << endl;

    // Get user input
    cout << "Lines Per Page: ";
    cin >> linesPerPage;
    cout << "Pages: ";
    cin >> pages;

    // Generate the logarithm tables
    for (int page = 0; page < pages; page++) {
        // Calculate first and last x values for this page
        double firstX = 0.1 + (page * linesPerPage * 4) * 0.1;
        double lastX = 0.1 + (page * linesPerPage * 4 + linesPerPage * 4 - 1) * 0.1;

        // Print page header with first and last x values
        cout << fixed << setprecision(1);
        cout << setw(5) << firstX;
        cout << setw(60) << " ";
        cout << setw(5) << lastX << endl;

        // Print separator line (70 dashes)
        cout << setfill('-') << setw(70) << "" << setfill(' ') << endl;

        // Print each line of the table
        for (int line = 0; line < linesPerPage; line++) {
            // Print 4 columns per line
            for (int col = 0; col < 4; col++) {
                // Calculate x value for this entry
                double x = 0.1 + (page * linesPerPage * 4 + line + col * linesPerPage) * 0.1;

                // Calculate log(x)
                double logX = log(x);

                // Print the entry with proper formatting
                cout << fixed << setprecision(1);
                cout << setw(5) << x;

                cout << fixed << setprecision(4);
                cout << setw(8) << logX;

                // Add spacing between columns (except after the last column)
                if (col < 3) {
                    cout << setw(6) << " ";
                }
            }
            cout << endl;
        }

        // Print blank line after the table
        cout << endl;

        // Print additional blank line (2 blank lines total after each page)
        cout << endl;
    }

    return 0;
}
