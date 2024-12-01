#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;
using namespace std::chrono;

// Определение дня недели
int Day() {
    auto t1 = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(t1);
    tm* local_tm = localtime(&currentTime);
    return local_tm->tm_wday;
}

// Получение названия дня недели
string getDayName(int day) {
    switch (day) {
        case 0: return "Воскресенье";
        case 1: return "Понедельник";
        case 2: return "Вторник";
        case 3: return "Среда";
        case 4: return "Четверг";
        case 5: return "Пятница";
        case 6: return "Суббота";
        default: return "Неизвестный день";
    }
}

// Генерация гаммы в зависимости от дня недели
string generateGamma(int dayW) {
    switch(dayW) {
        case 1:
        case 3:
        case 5:
            return "ABCD EFGH IJKL MNOP";
        case 2:
        case 4:
            return "GHEF OPMN ABCD IJKL";
        case 6:
        case 0: // 0 соответствует воскресенью
            return "GHEF CDAB OPMN KLIJ";
        default:
            return "";
    }
}

// Подсчёт контрольной суммы
unsigned char calculateChecksum(const string& data) {
    unsigned char checksum = 0;
    for (char ch : data) {
        checksum = (checksum + static_cast<unsigned char>(ch)) % 256;
    }
    return checksum;
}

// Шифрование/декодирование текста с использованием гаммы
string encode(const string& data, const string& gamma) {
    string result;
    size_t sizeGamma = gamma.size();

    for (size_t i = 0; i < data.size(); i++) {
        char currentGamma = gamma[i % sizeGamma];
        result.push_back(data[i] ^ currentGamma);
    }

    return result;
}

// Чтение данных из файла
string readFile(const string& fileName) {
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Ошибка открытия файла " << fileName << endl;
        return "";
    }

    string line, text;
    while (getline(inputFile, line)) {
        text += line + '\n';
    }
    inputFile.close();

    return text;
}

// Запись данных в файл
void writeFile(const string& fileName, const string& data) {
    ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        cerr << "Ошибка открытия файла для записи " << fileName << endl;
        return;
    }

    outputFile << data;
    outputFile.close();
}

// Тесты
void testGetDayName() {
    assert(getDayName(0) == "Воскресенье");
    assert(getDayName(1) == "Понедельник");
    assert(getDayName(2) == "Вторник");
    assert(getDayName(3) == "Среда");
    assert(getDayName(4) == "Четверг");
    assert(getDayName(5) == "Пятница");
    assert(getDayName(6) == "Суббота");
    assert(getDayName(7) == "Неизвестный день");
    cout << "testGetDayName пройден" << endl;
}

void testGenerateGamma() {
    assert(generateGamma(1) == "ABCD EFGH IJKL MNOP");
    assert(generateGamma(2) == "GHEF OPMN ABCD IJKL");
    assert(generateGamma(3) == "ABCD EFGH IJKL MNOP");
    assert(generateGamma(4) == "GHEF OPMN ABCD IJKL");
    assert(generateGamma(5) == "ABCD EFGH IJKL MNOP");
    assert(generateGamma(6) == "GHEF CDAB OPMN KLIJ");
    assert(generateGamma(0) == "GHEF CDAB OPMN KLIJ");
    assert(generateGamma(7) == "");
    cout << "testGenerateGamma пройден" << endl;
}

void testCalculateChecksum() {
    assert(calculateChecksum("") == 0);
    assert(calculateChecksum("a") == 'a');
    assert(calculateChecksum("abc") == ('a' + 'b' + 'c') % 256);
    cout << "testCalculateChecksum пройден" << endl;
}

void testEncode() {
    string gamma = "ABCD";
    string data = "abcd";
    string encoded = encode(data, gamma);
    string decoded = encode(encoded, gamma);
    assert(decoded == data);
    cout << "testEncode пройден" << endl;
}

void testReadWriteFile() {
    string fileName = "test_file.txt";
    string data = "Test data";
    writeFile(fileName, data);
    string readData = readFile(fileName);
    assert(readData == data + '\n');
    cout << "testReadWriteFile пройден" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    testGetDayName();
    testGenerateGamma();
    testCalculateChecksum();
    testEncode();
    testReadWriteFile();

    cout << "Все тесты пройдены!" << endl;
    return 0;
}
