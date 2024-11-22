#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

// calculateChecksum
char calculateChecksum(const string& data) {
    char checksum = 0;
    for (char c : data) {
        checksum ^= c;
    }
    return checksum;
}

// chooseGammaType
string chooseGammaType(const string& text) {
    int latinCount = 0;
    int cirillicCount = 0;

    for (char c : text) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) { // Подсчёт латинских символов
            latinCount++;
        } else if ((c >= 'А' && c <= 'Я') || (c >= 'а' && c <= 'я')) { // Подсчёт кириллицы
            cirillicCount++;
        }
    }
    if(latinCount > cirillicCount)
    {
        return "latin";
    }
    else
    {
        return "cirillic";
    }
}

string encode(const string& data, const string& gamma) {
    string encodedData;
    size_t sizeGamma = gamma.size();

    for (size_t i = 0; i < data.size(); i++) {
        char currentGamma = gamma[i % sizeGamma];
        encodedData.push_back(data[i] ^ currentGamma);
    }

    return encodedData;
}

bool Test_calculateChecksum() {
    return (calculateChecksum("ABC") == ('A' ^ 'B' ^ 'C')) &&
           (calculateChecksum("") == 0) && // Пустая строка
           (calculateChecksum("123456789") == ('1' ^ '2' ^ '3' ^ '4' ^ '5' ^ '6' ^ '7' ^ '8' ^ '9')) &&
           (calculateChecksum("TestChecksum") == ('T' ^ 'e' ^ 's' ^ 't' ^ 'C' ^ 'h' ^ 'e' ^ 'c' ^ 'k' ^ 's' ^ 'u' ^ 'm'));
}

bool Test_chooseGammaType() {
    return (chooseGammaType("Hello123") == "latin") &&
           (chooseGammaType("Привет123") == "cirillic") &&
           (chooseGammaType("123456") == "latin") &&
           (chooseGammaType("") == "cirillic");
}


bool Test_encode1()
{
    return ((encode("world", "ABCDEFGHIJKLMNOP") == "6-1(!") &&
            (encode("worl", "GHEFABCDOPMNIJKL") == "0'7*") &&
            (encode("la-123-ga", "ABCDEFGHIJKLMNOP") == "-#nuwuj/(")
            && (encode("la-12----dd", "GHEFABCDOPMNIJKL") == "+)hwsonib4)")
              ) ;

}

int Day()
{
    time_t tm = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%d", localtime(&tm));

    cout << "Текущая дата: " << buf << endl;

    return stoi(buf);
}

bool Test_Day()
{
    int today;
    cin >> today;
    return (Test_Day() == today ); // Проверка диапазона дней
}

int main() {
    setlocale(LC_ALL, "Russian");


    if (Test_calculateChecksum()) {
        cout << "Тест на calculateChecksum() пройден успешно." << endl;
    } else {
        cout << "Тест на calculateChecksum() НЕ пройден." << endl;
    }


    if (Test_chooseGammaType()) {
        cout << "Тест на chooseGammaType() пройден успешно." << endl;
    } else {
        cout << "Тест на chooseGammaType() НЕ пройден." << endl;
    }

    if (Test_encode1()) {
        cout << "Тест на encode() пройден успешно." << endl;
    } else {
        cout << "Тест на encode() НЕ пройден." << endl;
    }

    if (Test_Day())
    {
       cout << "Тест на Day() пройден успешно." << endl;
    } else
    {
        cout << "Тест на Day() НЕ пройден." << endl;
    }


}

