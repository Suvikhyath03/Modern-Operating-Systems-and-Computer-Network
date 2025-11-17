#include <iostream>
#include <string>
using namespace std;

// Function to perform XOR between two bit strings
string xorBits(const string &a, const string &b) {
    string result = "";
    for (size_t i = 0; i < b.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

// Function to compute CRC
string computeCRC(string data, const string &generator) {
    int genLen = generator.length();
    string appendedData = data;

    // Append zeros to the data equal to degree of generator
    appendedData.append(genLen - 1, '0');

    string temp = appendedData.substr(0, genLen);

    for (size_t i = genLen; i <= appendedData.length(); i++) {
        if (temp[0] == '1') {
            temp = xorBits(temp, generator);
        } else {
            temp = xorBits(temp, string(genLen, '0'));
        }

        if (i < appendedData.length())
            temp = temp.substr(1) + appendedData[i];
        else
            temp = temp.substr(1); // last step, no more bits to bring down
    }

    return temp; // This is the remainder
}

int main() {
    string data = "1101011011";
    string generator = "10011";

    string crc = computeCRC(data, generator);
    string transmitted = data + crc;

    cout << "Original data: " << data << endl;
    cout << "Generator: " << generator << endl;
    cout << "CRC Remainder: " << crc << endl;
    cout << "Transmitted Frame: " << transmitted << endl;

    return 0;
}

