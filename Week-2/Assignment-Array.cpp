#include <iostream>
using namespace std;

int main() {
    int rows, cols, nonZero;

    // Input number of rows, columns, and non-zero elements
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;
    cout << "Enter the number of non-zero elements: ";
    cin >> nonZero;

    // Declare arrays to store the sparse matrix representation
    int row[nonZero], col[nonZero], value[nonZero];

    // Input non-zero elements
    cout << "Enter the non-zero elements (row, column, value):" << endl;
    for (int i = 0; i < nonZero; i++) {
        bool valid = false;
        while(!valid){

            cout << "Element " << i + 1 << ":" << endl;
            cout << "Row: ";
            cin >> row[i];
            cout << "Column: ";
            cin >> col[i];
            cout << "Value: ";
            cin >> value[i];
            if(value[i] == 0) {
                cout << "Error: The entered value cannot be zero. Please enter a non-zero value." << endl;
            }
            else if (row[i] < 0 || row[i] >= rows || col[i] < 0 || col[i] >= cols) {
                cout << "Error: Array indices are out of bounds. Please re-enter the element." << endl;
            } else {
                valid = true;
            }
        }
    }

    // Display the sparse matrix representation
    cout << "\nSparse Matrix Representation:" << endl;
    cout << "Row\tColumn\tValue" << endl;
    for (int i = 0; i < nonZero; i++) {
        cout << row[i] << "\t" << col[i] << "\t" << value[i] << endl;
    }

    return 0;
}
