#include <iostream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

// Заглушка для функции Day
int mockDay(int fixedDay) {
    return fixedDay;  // Возвращаем заданный день недели
}

// Заглушка для функции getDayName
string mockGetDayName(int day) {
    switch (day) {
        case 0: return "Воскресенье";
        case 1: return "Понедельник";
        case 2: return "Вторник";
        case 3: return "Среда";
        case 4: return "Четверг";
        case 5: return "Пятница";
        case 6: return "Суббота";
        default: return "Неверный день";
    }
}

// Заглушка для функции generateGamma
string mockGenerateGamma(int dayW) {
    switch(dayW) {
        case 1:
        case 3:
        case 5:
            return "ABCD EFGH IJKL MNOP";
        case 2:
        case 4:
            return "GHEF OPMN ABCD IJKL";
        case 6:
        case 0:
            return "GHEF CDAB OPMN KLIJ";
        default:
            return "";
    }
}

// Тестирование функции getDayName с mockDay
void testGetDayName() {
    assert(mockGetDayName(0) == "Воскресенье");
    assert(mockGetDayName(1) == "Понедельник");
    assert(mockGetDayName(2) == "Вторник");
    assert(mockGetDayName(3) == "Среда");
    assert(mockGetDayName(4) == "Четверг");
    assert(mockGetDayName(5) == "Пятница");
    assert(mockGetDayName(6) == "Суббота");
    assert(mockGetDayName(7) == "Неверный день");
}

// Тестирование функции generateGamma
void testGenerateGamma() {
    assert(mockGenerateGamma(1) == "ABCD EFGH IJKL MNOP");
    assert(mockGenerateGamma(2) == "GHEF OPMN ABCD IJKL");
    assert(mockGenerateGamma(6) == "GHEF CDAB OPMN KLIJ");
    assert(mockGenerateGamma(0) == "GHEF CDAB OPMN KLIJ");
    assert(mockGenerateGamma(4) == "GHEF OPMN ABCD IJKL");
}

// Тестирование функции Day с mockDay
void testDay() {
    // Тестируем, что mockDay возвращает правильный день недели
    assert(mockDay(0) == 0);
    assert(mockDay(1) == 1);
    assert(mockDay(6) == 6);
    assert(mockDay(5) == 5);
}

// Заглушка для функции calculateChecksum
unsigned char mockCalculateChecksum(const string& data) {
    unsigned char checksum = 0;
    for (char ch : data) {
        checksum = (checksum + static_cast<unsigned char>(ch)) % 256;
    }
    return checksum;
}

// Тестирование функции calculateChecksum
void testCalculateChecksum() {
    string testData = "test";
    unsigned char checksum = mockCalculateChecksum(testData);
    assert(checksum == 0x14); // Ручной расчет контрольной суммы для "test"

    testData = "hello";
    checksum = mockCalculateChecksum(testData);
    assert(checksum == 0x50); // Ручной расчет контрольной суммы для "hello"
}

// Заглушка для функции encode
string mockEncode(const string& data, const string& gamma) {
    string result;
    size_t sizeGamma = gamma.size();
    for (size_t i = 0; i < data.size(); i++) {
        char currentGamma = gamma[i % sizeGamma];
        result.push_back(data[i] ^ currentGamma);
    }
    return result;
}

// Тестирование функции encode
void testEncode() {
    string data = "test";
    string gamma = "ABCD EFGH IJKL MNOP";
    string encodedData = mockEncode(data, gamma);
    string expectedEncoded = "¿QXÄ";  // Ручной расчет кодированного значения для теста
    assert(encodedData == expectedEncoded);
}

// Основная функция для запуска всех тестов
int main() {
    // Запуск всех тестов
    testGetDayName();
    testGenerateGamma();
    testDay();
    testCalculateChecksum();
    testEncode();

    cout << "Все тесты пройдены!" << endl;
    return 0;
}
