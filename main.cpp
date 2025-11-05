#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    int linesPerPage, pages;

    // welcome message - gotta look professional and all that
    cout << "Welcome to the Babbage Log Engine" << endl << endl;

    // grab the specs from user - easier than mission briefs back in the corps lol
    cout << "Lines Per Page: ";
    cin >> linesPerPage;
    cout << "Pages: ";
    cin >> pages;

    // time to generate these log tables - this is actually kinda sick
    for (int page = 0; page < pages; page++) {
        // figure out where this page starts and ends, math is simple when you break it down
        double firstX = 0.1 + (page * linesPerPage * 4) * 0.1;
        double lastX = 0.1 + (page * linesPerPage * 4 + linesPerPage * 4 - 1) * 0.1;

        // throw the header up top showing the range
        cout << fixed << setprecision(1);
        cout << setw(5) << firstX;
        cout << setw(60) << " ";
        cout << setw(5) << lastX << endl;

        // separator line - setfill is clutch for this, no loops needed
        cout << setfill('-') << setw(70) << "" << setfill(' ') << endl;

        // now we print each line of the table
        for (int line = 0; line < linesPerPage; line++) {
            // 4 columns per line - keeping it organized like a good formation
            for (int col = 0; col < 4; col++) {
                // calculate what x value we're at
                double x = 0.1 + (page * linesPerPage * 4 + line + col * linesPerPage) * 0.1;

                // get the natural log - cmath library does the heavy lifting
                double logX = log(x);

                // format it nice and clean with iomanip
                cout << fixed << setprecision(1);
                cout << setw(5) << x;

                cout << fixed << setprecision(4);
                cout << setw(8) << logX;

                // spacing between columns but not after the last one
                if (col < 3) {
                    cout << setw(6) << " ";
                }
            }
            cout << endl;
        }

        // blank line after the table
        cout << endl;

        // one more blank line (2 total between pages)
        cout << endl;
    }

    return 0;
}
