#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

// ������� ��� ��������� �����
string generateKey(const string& key, size_t length) {
    string generatedKey;
    for (size_t i = 0; i < length; ++i) {
        generatedKey += key[i % key.size()]; // ���������� ���� ������ �����
    }
    return generatedKey;
}

// ������� ��� ���������� � ������������
string xorCipher(const string& data, const string& key) {
    string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i]; // ���������� XOR ��� ���������� � ������������
    }
    return result;
}

// ������� ��� ���������� ����� ������
int Day()
{
    time_t tm = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%d", localtime(&tm));

    cout << "������� ����: " << buf << endl;

    return stoi(buf);
}

void KeyTest()
{
    // ���� ��� �����
    string text = "Hello world! We the best team";
    string key = "forest";
    string generatedKey = generateKey(key, text.size());
    if(generatedKey == "forestforestforestforestfores")
    {
        cout<<"��������� ����� ������� ������ ��������"<<endl;
    }
    else
    {
        cout<<"��������� ����� �������� �� ������"<<endl;
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
        cout<<"���� 1 ������� �������"<<endl;
    }
    else
    {
        cout<<"���� 1 ��������"<<endl;
    }

    string data2 = "";
    string key2 = "key";
    string encrypted2 = xorCipher(data2, key2);
    string decrypted2 = xorCipher(encrypted2, key2);
    if(decrypted2 == data2)
    {
        cout<<"���� 2 ������� �������"<<endl;
    }
    else
    {
        cout<<"���� 2 ��������"<<endl;
    }

    string data3 = "Hello!";
    string key3 = "abc";
    string encrypted3 = xorCipher(data3, key3);
    string decrypted3 = xorCipher(encrypted3, key3);
    if(decrypted3 == data3)
    {
        cout<<"���� 3 ������� �������"<<endl;
    }
    else
    {
        cout<<"���� 3 ��������"<<endl;
    }

    string data4 = "Hi!";
    string key4 = "123456";
    string encrypted4 = xorCipher(data4, key4);
    string decrypted4 = xorCipher(encrypted4, key4);
    if(decrypted4 == data4)
    {
        cout<<"���� 4 ������� �������"<<endl;
    }
    else
    {
        cout<<"���� 4 ��������"<<endl;
    }
}

void testDay()
{
    int day = Day();
    cout<<"������� ����� ������ �����: ";
    int nowDay;
    cin>>nowDay;
    if(day == nowDay)
    {
        cout<<"�������� ���� ������ �������"<<endl;
    }
}

int main()
{
    setlocale(0, "Russian");
    KeyTest();
    cyphetTest();
    testDay();
    return 0;
}