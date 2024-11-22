#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;


string generateGamma(int key1) {
    switch (key1) {
        case 1:
            return "ABCD EFGH IJKL MNOP";
        case 2:
            return "GHAB OPIJ MNCD KLEF";
        case 3:
            return "GHEF CDAB OPMN KLIJ";
        default:
            return "";
    }
}

// Функция для определения гаммы на основе языка текста
string chooseGammaType(const string& text) {
    int latinCount = 0;
    int cirillicCount = 0;

    for (char c : text) {
        // Подсчет латинских символов
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            latinCount++;
        }
        // Подсчет кириллических символов
        else if ((c >= 'А' && c <= 'я') || (c >= 'А' && c <= 'Я')) {
            cirillicCount++;
        }
    }

    return (latinCount > cirillicCount) ? "latin" : "cirillic";
}



string encode(const string& data, const string& gamma) {
    string encodedData;
    size_t gammaSize = gamma.size();

    for (size_t i = 0; i < data.size(); i++) {
        char currentGammaChar = gamma[i % gammaSize]; // Повтор гаммы
        encodedData.push_back(data[i] ^ currentGammaChar); // Шифрование с помощью XOR
    }

    return encodedData;
}

string readFile() {
    string inputFileName;
    cout << "Введите имя входного файла: " << endl;
    cin >> inputFileName;
    string line;
    string text;

    ifstream inputFile(inputFileName);
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            text += line + '\n';
        }
        inputFile.close();
    } else {
        cout << "Ошибка открытия файла" << endl;
        return "";
    }
    return text;
}



void writeFile(const string& encodedText) {
    string outputFileName = "file_out.txt";

    ofstream outputFile(outputFileName);
    if (outputFile.is_open()) {
        outputFile << encodedText;
        outputFile.close();
    } else {
        cout << "Ошибка открытия файла для записи" << endl;
        return;
    }
}


bool unit_generateGamma() {
    return (generateGamma(1) == "ABCD EFGH IJKL MNOP") && (generateGamma(2) == "GHAB OPIJ MNCD KLEF") && (generateGamma(3) == "GHEF CDAB OPMN KLIJ");
}


bool chooseGammaType_Test() {
    return (chooseGammaType("test_gamma1") == "latin") && (chooseGammaType("тест гаммы") == "cirillic") && (chooseGammaType("гамма") == "cirillic");
}

bool Test_encode1() {
    return (encode("world", generateGamma(1)) == "6-1(D") && (encode("world", generateGamma(3)) == "0'7*D");
}


// Подсчёт контрольной суммы
char kontrolnayaSumma(const string& text)
{
    int checksum = 0;
    for (int i = 0; i < text.length(); i++) {
        checksum += (int)text[i];
    }
    return static_cast<char>(checksum);
}

void summaTest()
{
    string text = "Hello;";
    char kontSum = kontrolnayaSumma(text);

    if (kontSum == '/') {
        cout << "Контрольная сумма совпадает. Дешифрование успешно!" << endl;
    } else {
        cout << "Контрольная сумма не совпадает." << endl;
    }
}

int main() {


    if (unit_generateGamma()) {
        cout << "Правильный выбор гаммы" << endl;
    } else {
        cout << "Неправильный выбор гаммы" << endl;
    }

    if (chooseGammaType_Test()) {
        cout << "Правильный выбор гаммы на основе языка" << endl;
    } else {
        cout << "Неправильный выбор гаммы на основе языка" << endl;
    }

    if (Test_encode1()) {
        cout << "Тест на encode(): шифрование прошло успешно" << endl;
    } else {
        cout << "Тест на encode(): шифрование НЕ успешно" << endl;
    }

    string textFromFile = readFile();
    if (!textFromFile.empty()) {
        string gammaType = chooseGammaType(textFromFile);
        string gamma = generateGamma(1); // Выбираем гамму (можно изменить)
        string encodedText = encode(textFromFile, gamma);
        writeFile(encodedText);
        cout << "Текст зашифрован и записан в file_out.txt" << endl;
    }

    summaTest();
    return 0;
}
