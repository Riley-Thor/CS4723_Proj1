#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <iomanip>

using namespace std;

// Expansion table (DES-based)
const int EXPANSION_TABLE[48] = {
    32, 1, 2, 3, 4, 5, 
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13, 
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29, 
    28, 29, 30, 31, 32, 1
};

// S-Box (DES S1 used)
const int SBOX[4][16] = {
    {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
    {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
};

// Expand 32-bit input to 48-bit using the expansion table
bitset<48> expand(bitset<32> input) {
    bitset<48> expanded;
    for (int i = 0; i < 48; i++) {
        expanded[i] = input[EXPANSION_TABLE[i] - 1];
    }
    return expanded;
}

// S-Box substitution
bitset<32> sbox_substitution(bitset<48> input) {
    string combo = "";
    for (int i = 8; i > 0; i--) {
        int row = (input[i * 6 - 1] << 1) | input[i * 6 - 6];
        int col = (input[i * 6 - 2] << 3) | (input[i * 6 - 3] << 2) | (input[i * 6 - 4] << 1) | input[i * 6 - 5];
        bitset<4> sbox_output(SBOX[row][col]);
        combo += sbox_output.to_string();
    }
    return bitset<32>(combo);
}

// MTUHash function
bitset<32> MTUHash(bitset<32> input) {
    for (int round = 0; round < 16; round++) {
        bitset<48> expanded = expand(input);
        input = sbox_substitution(expanded);
    }
    return input;
}

// Function to count differing bits between two bitsets
int countDifferingBits(const bitset<32>& hash1, const bitset<32>& hash2) {
    return (hash1 ^ hash2).count();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./AECalculator <input_file>" << endl;
        return 1;
    }
    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Error: Cannot open input file!" << endl;
        return 1;
    }
    string inputString;
    inputFile >> inputString;
    inputFile.close();

    if (inputString.length() != 32) {
        cerr << "Length Error" << endl;
        return 1;
    }

    bitset<32> input(inputString);
    bitset<32> originalHash = MTUHash(input);

    double totalFlipRate = 0.0;
    int bitLength = 32;

    for (int i = 0; i < bitLength; i++) {
        bitset<32> modifiedInput = input;
        modifiedInput.flip(i);
        bitset<32> modifiedHash = MTUHash(modifiedInput);
        int differingBits = countDifferingBits(originalHash, modifiedHash);
        double flipRate = (differingBits / 32.0) * 100.0;
        totalFlipRate += flipRate;
    }

    double AFR = totalFlipRate / bitLength;

    ofstream outputFile("AFR.txt");
    outputFile << fixed << setprecision(1) << AFR << "%" << endl;
    outputFile.close();

    return 0;
}
