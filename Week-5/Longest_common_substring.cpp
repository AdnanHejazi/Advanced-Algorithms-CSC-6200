#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Function to find the longest common substring and display an enhanced lookup table
void longestCommonSubstring(const string& str1, const string& str2) {
    int len1 = str1.length();
    int len2 = str2.length();
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0)); // DP table
    int maxLength = 0, endIndex = 0;

    // Build the DP table
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i;
                }
            }
        }
    }

    // Extract the longest common substring
    string lcs = str1.substr(endIndex - maxLength, maxLength);

    // Print the lookup table with characters along the axes
    cout << "\nLookup Table:\n";
    cout << "    "; // Spacing for the top-left corner
    for (int j = 0; j < len2; j++) {
        cout << setw(3) << str2[j]; // Print characters of str2 on the top axis
    }
    cout << "\n  ";
    
    for (int j = 0; j <= len2; j++) {
        cout << setw(3) << "-"; // Separator row
    }
    cout << endl;

    for (int i = 0; i <= len1; i++) {
        if (i > 0) cout << str1[i - 1] << " |"; // Print characters of str1 on the left axis
        else cout << "  |"; // First row does not have a character

        for (int j = 0; j <= len2; j++) {
            cout << setw(3) << dp[i][j]; // Print the DP table values
        }
        cout << endl;
    }

    // Display results
    cout << "\nLongest Common Substring: " << lcs << endl;
    cout << "Length of Longest Common Substring: " << maxLength << "\n";
}

int main() {
    string str1, str2, choice;

    while (true) {
        cout << "\nEnter first string (or 'X' to exit): ";
        cin >> str1;
        if (str1 == "X" || str1 == "x") break;

        cout << "Enter second string: ";
        cin >> str2;

        longestCommonSubstring(str1, str2);

        cout << "\nEnter 'X' to exit or any other key to continue: ";
        cin >> choice;
        if (choice == "X" || choice == "x") break;
    }

    cout << "\nProgram Terminated. Thank you!\n";
    return 0;
}
