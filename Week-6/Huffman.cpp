#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// Huffman Tree Node
struct Node {
    char data;
    int freq;
    Node *left, *right;

    Node(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }
};

// Comparison function for priority queue (min-heap)
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Function to generate Huffman codes
void generateHuffmanCodes(Node* root, string code, unordered_map<char, string> &huffmanCodes) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Function to build Huffman Tree and return the root node
Node* buildHuffmanTree(string chars, vector<int> freq) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (size_t i = 0; i < chars.size(); i++) {
        minHeap.push(new Node(chars[i], freq[i]));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        Node* newNode = new Node('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

    return minHeap.top();
}

// Function to extract unique characters and their frequencies
void getFrequencies(const string &input, string &chars, vector<int> &freq) {
    unordered_map<char, int> freqMap;

    for (char ch : input) {
        freqMap[ch]++;
    }

    for (auto &entry : freqMap) {
        chars += entry.first;
        freq.push_back(entry.second);
    }

    cout << "\nCharacter Frequencies:\n";
    for (size_t i = 0; i < chars.size(); i++) {
        cout << chars[i] << " : " << freq[i] << endl;
    }
}

// Function to encode the input string using Huffman codes
string encodeString(const string &input, unordered_map<char, string> &huffmanCodes) {
    string encodedString = "";
    for (char ch : input) {
        encodedString += huffmanCodes[ch];
    }
    return encodedString;
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;

    string chars;
    vector<int> freq;

    getFrequencies(input, chars, freq);

    Node* root = buildHuffmanTree(chars, freq);

    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    cout << "\nHuffman Codes:\n";
    for (auto &entry : huffmanCodes) {
        cout << entry.first << " : " << entry.second << endl;
    }

    // Encode the input string
    string encodedString = encodeString(input, huffmanCodes);
    cout << "\nEncoded String: " << encodedString << endl;

    return 0;
}
