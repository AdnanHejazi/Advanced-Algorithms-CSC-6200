#include <iostream>
using namespace std;

// Node structure for the linked list
struct Node {
    int row, col, value;
    Node* next;
};

// Class to represent the sparse matrix
class SparseMatrix {
private:
    Node* head;

public:
    SparseMatrix() {
        head = nullptr;
    }

    // Function to insert a non-zero element
    void insert(int row, int col, int value) {
        Node* newNode = new Node();
        newNode->row = row;
        newNode->col = col;
        newNode->value = value;
        newNode->next = nullptr;

        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Function to display the sparse matrix
    void display() {
        Node* temp = head;
        cout << "Row\tColumn\tValue\n";
        while (temp) {
            cout << temp->row << "\t" << temp->col << "\t" << temp->value << "\n";
            temp = temp->next;
        }
    }
};

int main() {
    SparseMatrix sparseMatrix;
    int rows, cols, nonZeroElements;

    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;
    cout << "Enter the number of non-zero elements: ";
    cin >> nonZeroElements;

    for (int i = 0; i < nonZeroElements; i++) {
        int row, col, value;
        cout << "Enter row, column, and value for element " << i + 1 << ": ";
        cout << "Row: ";
        cin >> row;
        cout << "Column: ";
        cin >> col;
        cout << "Value: ";
        cin >> value;
        sparseMatrix.insert(row, col, value);
    }

    cout << "\nSparse Matrix Representation:\n";
    sparseMatrix.display();

    return 0;
}
