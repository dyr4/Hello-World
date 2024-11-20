#include <iostream>
#include <chrono>
#include <fstream>
#include <string>

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

int main() {
    setlocale(LC_ALL, "Russian");

    string inputFileName = "file_in.txt";
    string outputFileName = "file_out.txt";

    // Определение текущего дня недели
    int currentDay = Day();
    string dayName = getDayName(currentDay);

    // Генерация гаммы
    string gamma = generateGamma(currentDay);

    cout << "Сегодня: " << dayName << endl;
    cout << "Используемая гамма: " << gamma << endl;

    // Чтение данных из входного файла
    string data = readFile(inputFileName);

    // Вывод контрольной суммы
    unsigned char checksum = calculateChecksum(data);
    cout << "Контрольная сумма данных: " << static_cast<int>(checksum) << endl;

    // Шифрование текста
    string encodedData = encode(data, gamma);

    // Запись зашифрованного текста в файл
    writeFile(outputFileName, encodedData);

    // Декодирование текста для проверки
    string decodedData = encode(encodedData, gamma); // Декодирование идентично шифрованию

    // Вывод результатов
    cout << "\nИсходный текст:\n" << data << endl;
    cout << "\nЗашифрованный текст:\n" << encodedData << endl;
    cout << "\nРасшифрованный текст (проверка):\n" << decodedData << endl;

    cout << "\nШифрование завершено. Результат записан в " << outputFileName << endl;

    return 0;
}
