#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <numeric>

using namespace std;

// Функция для генерации гаммы
string generateGamma(const string& initialGamma, size_t length) {
    string gamma = initialGamma;
    while (gamma.size() < length) {
        gamma += initialGamma;
    }
    return gamma.substr(0, length);
}

// Функция шифрования
string encrypt(const string& plainText, const string& gamma) {
    if (plainText.size() != gamma.size()) {
        throw invalid_argument("Размер текста и гаммы должны совпадать");
    }
    string cipherText;
    for (size_t i = 0; i < plainText.size(); ++i) {
        cipherText += plainText[i] ^ gamma[i];
    }
    return cipherText;
}

// Функция вычисления контрольной суммы
uint8_t calculateChecksum(const string& text) {
    return accumulate(text.begin(), text.end(), 0) % 256;
}

// Функция шифрования файла
void encryptFile(const string& inputFileName, const string& outputFileName, const string& initialGamma) {
    ifstream inputFile(inputFileName, ios::binary);
    if (!inputFile) {
        throw runtime_error("Не удалось открыть входной файл");
    }

    string plainText((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    // Генерация гаммы и шифрование
    string gamma = generateGamma(initialGamma, plainText.size());
    string cipherText = encrypt(plainText, gamma);

    // Вычисление контрольной суммы
    uint8_t checksum = calculateChecksum(plainText);

    // Запись в выходной файл
    ofstream outputFile(outputFileName, ios::binary);
    if (!outputFile) {
        throw runtime_error("Не удалось открыть выходной файл");
    }
    outputFile.write(cipherText.c_str(), cipherText.size());
    outputFile.put(static_cast<char>(checksum)); // Записываем контрольную сумму в конец файла
    outputFile.close();

    wcout << L"Шифрование завершено. Контрольная сумма исходного текста: " << static_cast<int>(checksum) << endl;
}

// Функция расшифровки и проверки
void decryptAndValidate(const string& inputFileName, const string& initialGamma) {
    ifstream inputFile(inputFileName, ios::binary);
    if (!inputFile) {
        throw runtime_error("Не удалось открыть зашифрованный файл");
    }

    // Чтение зашифрованного текста и контрольной суммы
    string cipherText((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    if (cipherText.empty()) {
        throw runtime_error("Файл пуст");
    }
    uint8_t checksum = static_cast<uint8_t>(cipherText.back());
    cipherText.pop_back(); // Удаляем контрольную сумму из текста
    inputFile.close();

    // Генерация гаммы и расшифровка
    string gamma = generateGamma(initialGamma, cipherText.size());
    string decryptedText = encrypt(cipherText, gamma); // XOR-обратим

    // Вычисление контрольной суммы расшифрованного текста
    uint8_t calculatedChecksum = calculateChecksum(decryptedText);

    // Проверка
    if (calculatedChecksum != checksum) {
        throw runtime_error("Контрольная сумма не совпадает. Файл повреждён!");
    }

    wcout << L"Расшифровка успешна. Контрольная сумма: " << static_cast<int>(calculatedChecksum) << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        // Определяем входной и выходной файлы, а также гамму
        const string inputFileName = "file_in.txt";
        const string outputFileName = "file_out.txt";
        const string initialGamma = "ABCDEFGH"; // Строка гаммы

        // Шифрование файла
        encryptFile(inputFileName, outputFileName, initialGamma);

        // Проверка и расшифровка файла
        decryptAndValidate(outputFileName, initialGamma);

        return 0;
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
}
