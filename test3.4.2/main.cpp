#include <iostream>
#include <string>

using namespace std;

// Функция для генерации ключа
string generateKey(const string& key, size_t length) {
    string generatedKey;
    for (size_t i = 0; i < length; ++i) {
        generatedKey += key[i % key.size()]; //Генерируем ключ нужный длины
    }
    return generatedKey;
}

// Функция для шифрования и дешифрования
string xorCipher(const string& data, const string& key) {
    string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i]; // Используем XoR для шифрования и дешифрования
    }
    return result;
}

// Функция для определения гаммы
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

//Подсчёт контрольной суммы
char kontrolnayaSumma(const string& text)
{
    int checksum = 0;
    for (int i = 0; i < text.length(); i++) {
        checksum += (int)text[i];
    }
    return static_cast<char>(checksum);
}

void KeyTest()
{
    // Тест для ключа
    string text = "Hello world! We the best team";
    string key = "forest";
    string generatedKey = generateKey(key, text.size());
    if(generatedKey == "forestforestforestforestfores")
    {
        cout<<"Генерация ключа успешно прошла проверку"<<endl;
    }
    else
    {
        cout<<"Генерация ключа проверку не прошла"<<endl;
    }
}

void cyphetTest()
{
    string data1 = "Hello, World!";
    string key1 = "key";
    string encrypted1 = xorCipher(data1, key1);
    string decrypted1 = xorCipher(encrypted1, key1);
    if(decrypted1 == data1)
    {
        cout<<"Тест 1 пройден успешно"<<endl;
    }
    else
    {
        cout<<"Тест 1 провален"<<endl;
    }

    string data2 = "";
    string key2 = "key";
    string encrypted2 = xorCipher(data2, key2);
    string decrypted2 = xorCipher(encrypted2, key2);
    if(decrypted2 == data2)
    {
        cout<<"Тест 2 пройден успешно"<<endl;
    }
    else
    {
        cout<<"Тест 2 провален"<<endl;
    }

    string data3 = "Hello!";
    string key3 = "abc";
    string encrypted3 = xorCipher(data3, key3);
    string decrypted3 = xorCipher(encrypted3, key3);
    if(decrypted3 == data3)
    {
        cout<<"Тест 3 пройден успешно"<<endl;
    }
    else
    {
        cout<<"Тест 3 провален"<<endl;
    }

    string data4 = "Hi!";
    string key4 = "123456";
    string encrypted4 = xorCipher(data4, key4);
    string decrypted4 = xorCipher(encrypted4, key4);
    if(decrypted4 == data4)
    {
        cout<<"Тест 4 пройден успешно"<<endl;
    }
    else
    {
        cout<<"Тест 4 провален"<<endl;
    }
}
void gammaTest()
{
        // Тест на определение типа гаммы
    string text = "Привет мир, мы the best команда";
    string gammaType = chooseGammaType(text);
    cout<<text<<"     "<<"Тип гаммы: "<<gammaType<<endl;

    text = "Привет мир, we the best team";
    gammaType = chooseGammaType(text);
    cout<<text<<"     "<<"Тип гаммы: "<<gammaType<<endl;
}

void summaTest()
{
    string text = "Hello world!!!";
    char kontSum = kontrolnayaSumma(text);
    if (kontSum == 'џ') {
        cout << "Контрольная сумма совпадает. Дешифрование успешно!" << endl;
    } else {
        cout << "Контрольная сумма не совпадает." << endl;
    }
}

int main()
{
    setlocale(0, "Russian");
    KeyTest();
    cyphetTest();
    gammaTest();
    summaTest();
    return 0;
}
