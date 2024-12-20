#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

// Function to generate a repeating key string
string generateKey(const string& key, size_t length) {
    string generatedKey;
    for (size_t i = 0; i < length; ++i) {
        generatedKey += key[i % key.size()];
    }
    return generatedKey;
}

// XOR cipher function
string xorCipher(const string& data, const string& key) {
    string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i];
    }
    return result;
}

// Function to get the day of the week
int getDayOfWeek() {
    time_t tm = time(nullptr);
    tm = mktime(localtime(&tm));
    return localtime(&tm)->tm_wday; // Sunday = 0, Monday = 1, ...
}

// Function to select gamma based on the day of the week
string chooseGammaForDay() {
    int dayOfWeek = getDayOfWeek();

    switch (dayOfWeek) {
        case 1: // Monday
        case 3: // Wednesday
        case 5: // Friday
            return "ABCDEFGH IJKL MNOP";
        case 2: // Tuesday
        case 4: // Thursday
            return "GHEF OPMN ABCD IJKL";
        case 0: // Sunday
        case 6: // Saturday
            return "GHEF CDAB OPMN KLIJ";
        default:
            return "";
    }
}

// Function to append the length of plaintext as a byte
string addLengthByte(const string& data) {
    char lengthByte = static_cast<char>(data.size());
    return data + lengthByte;
}

// Function to extract the length from ciphertext
size_t extractLengthFromCiphertext(const string& data) {
    return static_cast<size_t>(static_cast<unsigned char>(data.back()));
}

int main() {
    setlocale(0, "Russian");

    string file_in = "file_in.txt";
    string file_out = "file_out.txt";
    string text;

    // Read plaintext from file
    ifstream fileIn(file_in);
    if (fileIn.is_open()) {
        getline(fileIn, text);
        fileIn.close();
    } else {
        cout << "Ошибка: Не удалось открыть файл " << file_in << endl;
        return 1;
    }

    // Select gamma based on the day of the week
    string gamma = chooseGammaForDay();
    if (gamma.empty()) {
        cout << "Ошибка: Невозможно определить гамму." << endl;
        return 1;
    }

    // Generate key
    string generatedKey = generateKey(gamma, text.size());
    cout << "Сгенерированный ключ: " << generatedKey << endl;

    // Encrypt text
    string ciphertext = xorCipher(text, generatedKey);

    // Append the length byte
    ciphertext = addLengthByte(ciphertext);

    // Write ciphertext to file
    ofstream outputFile(file_out);
    if (!outputFile.is_open()) {
        cout << "Ошибка при открытии файла " << file_out << endl;
        return 1;
    }

    outputFile << ciphertext;
    outputFile.close();

    // Decrypt text using the same key
    string decryptedTextWithLength = xorCipher(ciphertext, generatedKey);

    // Extract the original length
    size_t originalLength = extractLengthFromCiphertext(decryptedTextWithLength);

    // Remove the length byte and decrypt the text
    string decryptedText = xorCipher(decryptedTextWithLength.substr(0, originalLength), generatedKey);
    cout << "Расшифрованный текст: " << decryptedText << endl;

    return 0;
}
