#include <iostream>
#include <fstream>
#include <string>
#include <numeric> // Для std::accumulate

using namespace std;

// Генерация гаммы
string generateKey(const string& key, size_t length) 
{
    string generatedKey;
    for (size_t i = 0; i < length; ++i) 
    {
        generatedKey += key[i % key.size()];
    }
    return generatedKey;
}

// XOR шифрование
string xorCipher(const string& data, const string& key) 
{
    string result = data;
    for (size_t i = 0; i < data.size(); ++i) 
    {
        result[i] = data[i] ^ key[i];
    }
    return result;
}

// Вычисление контрольной суммы
unsigned int calculateChecksum(const string& text) 
{
    return accumulate(text.begin(), text.end(), 0u);
}

int main() 
{
    setlocale(0, "Russian");

    string file_in = "file_in.txt";
    string file_out = "file_out.txt";
    string file_decrypted = "file_decrypted.txt";

    // Чтение входного файла
    string text;
    ifstream fileIn(file_in);
    if (fileIn.is_open()) 
    {
        getline(fileIn, text);
        fileIn.close();
    } 
    else 
    {
        cout << "Ошибка: Не удалось открыть файл " << file_in << endl;
        return 1;
    }

    // Поле длины и контрольная сумма
    size_t textLength = text.size();
    unsigned int checksum = calculateChecksum(text);

    // Создание данных для шифрования
    string dataToEncrypt = to_string(textLength) + "|" + text + "|" + to_string(checksum);

    // Генерация гаммы
    string gamma = "2";
    string generatedKey = generateKey(gamma, dataToEncrypt.size());

    // Шифрование
    string ciphertext = xorCipher(dataToEncrypt, generatedKey);
    ofstream outputFile(file_out);
    if (!outputFile.is_open()) 
    {
        cout << "Ошибка при открытии файла для записи " << file_out << endl;
        return 1;
    }
    outputFile << ciphertext;
    outputFile.close();
    cout << "Шифрование завершено. Данные записаны в файл " << file_out << "." << endl;

    // Дешифрование
    string decryptedData = xorCipher(ciphertext, generatedKey);

    // Разбор расшифрованных данных
    size_t delimiter1 = decryptedData.find('|');
    size_t delimiter2 = decryptedData.find('|', delimiter1 + 1);
    if (delimiter1 == string::npos || delimiter2 == string::npos) 
    {
        cout << "Ошибка: некорректный формат данных." << endl;
        return 1;
    }

    // Восстановление исходных данных
    size_t decryptedLength = stoi(decryptedData.substr(0, delimiter1));
    string decryptedText = decryptedData.substr(delimiter1 + 1, delimiter2 - delimiter1 - 1);
    unsigned int decryptedChecksum = stoi(decryptedData.substr(delimiter2 + 1));

    // Проверка контрольной суммы
    if (decryptedText.size() == decryptedLength && calculateChecksum(decryptedText) == decryptedChecksum) 
    {
        // Запись расшифрованного текста в файл
        ofstream decryptedFile(file_decrypted);
        if (!decryptedFile.is_open()) 
        {
            cout << "Ошибка при открытии файла для записи " << file_decrypted << endl;
            return 1;
        }
        decryptedFile << decryptedText;
        decryptedFile.close();
        cout << "Дешифрование успешно. Данные записаны в файл " << file_decrypted << "." << endl;
    } 
    else 
    {
        cout << "Ошибка: контрольная сумма или длина не совпадают!" << endl;
        return 1;
    }

    return 0;
}

