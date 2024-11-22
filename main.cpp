#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// Функция для генерации ключа
string generateKey(const string& key, size_t length) {
    string generatedKey;
    for (size_t i = 0; i < length; ++i) {
        generatedKey += key[i % key.size()]; // Генерируем ключ нужной длины
    }
    return generatedKey;
}

// Функция для шифрования и дешифрования
string xorCipher(const string& data, const string& key) {
    string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i]; // Используем XOR для шифрования и дешифрования
    }
    return result;
}

int Day()
{
    auto t1 = chrono::system_clock::now();

    // time_point в time_t
    time_t currentTime = chrono::system_clock::to_time_t(t1);
    tm* local_tm = localtime(&currentTime);
    int l = local_tm->tm_wday;
    return local_tm->tm_wday;

}

string generateGamma(int dayW)
{
    switch(dayW)
    {
        case 1:
        case 3:
        case 5:
            return "ABCD EFGH IJKL MNOP";
        case 2:
        case 4:
            return "GHEF OPMN ABCD IJKL";
        case 6:
        case 7:
            return "GHEF CDAB OPMN KLIJ";
        default:
            return "";
    }
}

// Подсчёт контрольной суммы
char kontrolnayaSumma(const string& text, int key2)
{
    int checksum = 0;
    for (int i = 0; i < text.length(); i++) {
        checksum += (int)text[i];
    }
    checksum += key2;
    return static_cast<char>(checksum);
}


int main() {

    string file_in = "file_in.txt";
    string file_out = "file_out.txt";

    // Чтение текста из файла
    string text;
    ifstream fileIn(file_in);

    if (fileIn.is_open()) {
        getline(fileIn, text);
        fileIn.close();
    } else {
        cout << "Ошибка: Не удалось открыть файл " << file_in << endl;
        return 1;
    }

    string chooseDay;
    cout<<"Взять день недели из системы?(Yes or No)"<<endl;
    cin>>chooseDay;
    int gammaType = 0;

    if(chooseDay == "Yes" || chooseDay == "yes")
    {
    gammaType = Day();
    }
    else
    {
        if(chooseDay == "No" || chooseDay == "no")
        {
            while (!(gammaType >= 1 && gammaType <= 7))
            {
                cout<<"Введите число от 1 до 7: ";
                cin>>gammaType;
                if(!(gammaType >= 0 || gammaType <= 7))
                {
                    cout<<"Некорректный ввод"<<endl;
                }
            }
        }
        else
        {
            cout<<"Некорректный ввод"<<endl;
            return 0;
        }
    }

    int key1 = 1;
    int key2;

    while(true)
    {
    switch(key1){
        case 1:
            key2 = 20;
        case 2:
            key2 = 40;
        case 3:
            key2 = 60;
        default:
            key2 = 0;
    }


    // Выбор гаммы
    string gamma = generateGamma(gammaType);

    // Генерация ключа нужной длины
    string generatedKey = generateKey(gamma, text.size()); // Используем введенный ключ
    cout << "Генерация ключа: " << generatedKey << endl;

    //Добавление контрольной суммы
    char kontSum = kontrolnayaSumma(text, key2);
    text += kontSum;

    // Шифрование
    string ciphertext = xorCipher(text, generatedKey);
    cout << "Зашифрованный текст: " << ciphertext << endl;

    // Запись зашифрованного текста в файл
    ofstream outputFile(file_out);
    if (!outputFile.is_open()) {
        cout << "Ошибка при открытии файла " << file_out << endl;
        return 1;
    }

    outputFile << ciphertext;
    outputFile.close();

    // Дешифрование текста
    string decryptedtext = xorCipher(ciphertext, generatedKey);
    cout << "Расшифрованный текст: " << decryptedtext << endl;

    key1 = (key1 % 3) + 1;

    // Извлечение контрольной суммы
        char kontAfterSum = decryptedtext.back();
        decryptedtext.pop_back();

        // Проверка контрольной суммы
        kontSum = kontrolnayaSumma(decryptedtext, key2);
        if (kontSum == kontAfterSum) {
            cout << "Контрольная сумма совпадает. Дешифрование успешно!" << endl;
        } else {
            cout << "Контрольная сумма не совпадает." << endl;
        }

        // Ожидание следующего цикла
        this_thread::sleep_for(chrono::seconds(20)); // остановка до следующей гаммы
    }
    return 0;
}



