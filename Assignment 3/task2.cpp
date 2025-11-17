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

// Function to compute CRC remainder
string computeCRC(string data, const string &generator) {
    int genLen = generator.length();
    string appendedData = data + string(genLen - 1, '0');

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
            temp = temp.substr(1);
    }

    return temp; // remainder
}

// Function to check if a received message has error
bool checkError(string received, const string &generator) {
    int genLen = generator.length();
    string temp = received.substr(0, genLen);

    for (size_t i = genLen; i <= received.length(); i++) {
        if (temp[0] == '1') {
            temp = xorBits(temp, generator);
        } else {
            temp = xorBits(temp, string(genLen, '0'));
        }

        if (i < received.length())
            temp = temp.substr(1) + received[i];
        else
            temp = temp.substr(1);
    }

    return temp != string(generator.length() - 1, '0'); // error if remainder != 0
}

int main() {
    string message = "10011101";
    string generator = "1001";

      // Step 1: Compute CRC
    string crc = computeCRC(message, generator);
    string transmitted = message + crc;

    cout << "Original message: " << message << endl;
    cout << "Generator: " << generator << endl;
    cout << "CRC Remainder: " << crc << endl;
    cout << "Transmitted frame: " << transmitted << endl;

    // Step 2: Simulate error (invert 3rd bit)
    string received = transmitted;
    received[2] = (received[2] == '0') ? '1' : '0'; // invert 3rd bit
    cout << "Received frame (3rd bit inverted): " << received << endl;

    if (checkError(received, generator))
        cout << "Error detected!" << endl;
    else
        cout << "No error detected." << endl;

    return 0;
}

