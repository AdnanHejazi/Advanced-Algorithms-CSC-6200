#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdint>

// Initialze round constants
const uint32_t k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Bitwise Rotation
uint32_t rotr(uint32_t x, uint32_t n) { return (x >> n) | (x << (32 - n)); }

// SHA-256 Pre-processing (Padding)
std::vector<uint8_t> padMessage(const std::string &msg) {
    std::vector<uint8_t> padded(msg.begin(), msg.end());
    padded.push_back(0x80);
    while ((padded.size() + 8) % 64 != 0) padded.push_back(0x00);
    
    uint64_t bitLength = msg.size() * 8;
    for (int i = 7; i >= 0; --i)
        padded.push_back((bitLength >> (i * 8)) & 0xFF);
    
    return padded;
}

// SHA-256 Processing
std::string sha256(const std::string &input) {

    // Initialize hash values: 
    uint32_t h[8] = { 
        0x6a09e667,
        0xbb67ae85,
        0x3c6ef372, 
        0xa54ff53a, 
        0x510e527f, 
        0x9b05688c, 
        0x1f83d9ab, 
        0x5be0cd19 
    };

    std::vector<uint8_t> padded = padMessage(input);
    
    for (size_t i = 0; i < padded.size(); i += 64) {
        uint32_t w[64], a, b, c, d, e, f, g, hTemp;
        
        for (int j = 0; j < 16; ++j)
            w[j] = (padded[i + j * 4] << 24) | (padded[i + j * 4 + 1] << 16) | (padded[i + j * 4 + 2] << 8) | (padded[i + j * 4 + 3]);

        for (int j = 16; j < 64; ++j)
            w[j] = w[j-16] + (rotr(w[j-15], 7) ^ rotr(w[j-15], 18) ^ (w[j-15] >> 3)) + w[j-7] + (rotr(w[j-2], 17) ^ rotr(w[j-2], 19) ^ (w[j-2] >> 10));

        a = h[0]; b = h[1]; c = h[2]; d = h[3];
        e = h[4]; f = h[5]; g = h[6]; hTemp = h[7];

        for (int j = 0; j < 64; ++j) {
            uint32_t temp1 = hTemp + (rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25)) + ((e & f) ^ (~e & g)) + k[j] + w[j];
            uint32_t temp2 = (rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22)) + ((a & b) ^ (a & c) ^ (b & c));
            hTemp = g; 
            g = f; 
            f = e; 
            e = d + temp1;
            d = c; 
            c = b; 
            b = a; 
            a = temp1 + temp2;

        }

        h[0] += a; h[1] += b; h[2] += c; h[3] += d;
        h[4] += e; h[5] += f; h[6] += g; h[7] += hTemp;
    }
    
    std::ostringstream result;
    for (uint32_t val : h)
        result << std::hex << std::setw(8) << std::setfill('0') << val;

    return result.str();
}

// Read Local HTML File
std::string readFile(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        exit(1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    // Read the Book of Mark from a local file
    std::string filePath = "mark.html";  // Make sure this file exists in the same directory
    std::string bookOfMarkText = readFile(filePath);
    
    // Compute SHA-256 Hash
    std::string hash = sha256(bookOfMarkText);
    
    // Print Result
    std::cout << "SHA-256 Hash of the Book of Mark: \n"<< hash << std::endl;

    return 0;
}
