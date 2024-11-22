#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cassert>

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

// ������� ��� ����������� �����
string chooseGammaType(const string& text) {
    int latinCount = 0;
    int cirillicCount = 0;

    for (char c : text) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) { // ������� ��������� ��������
            latinCount++;
        } else if ((c >= '�' && c <= '�') || (c >= '�' && c <= '�')) { // ������� ���������
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

// ������� ��� ���������� ����� ������
int Day()
{

    auto t1 = chrono::system_clock::now();

    // time_point � time_t
    time_t currentTime = chrono::system_clock::to_time_t(t1);
    tm* local_tm = localtime(&currentTime);
    int l = local_tm->tm_wday;
    return local_tm->tm_wday;
}

//������� ��� ������ ����� � ����������� �� ��� ������
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

// ������� ��� ������ �����
string readFile()
{
    string inputFileName;
    cout << "������� ��� �������� �����: " << endl;
    cin >> inputFileName;
    string line;
    string text;

    ifstream inputFile(inputFileName);
    if (inputFile.is_open())
    {
        while (getline(inputFile, line)) {
            text += line + '\n';
        }
        cout<<"���� ������ �������"<<endl;
        inputFile.close();
    } else {
        cout << "������ �������� �����" << endl;
        return "";
    }
//    cout << text << endl;

    return text;
}

void writeFile()
{

    string outputFileName;
    cout << "������� ��� ����� ��� ������" << endl;
    cin >> outputFileName;
    string encode_Text = "���� �������";
    ofstream outputFile(outputFileName);
    if (outputFile.is_open())
    {
        outputFile << encode_Text;
        outputFile.close();
        cout<<"� ���� ������� �� ��������"<<endl;
    } else {
        cout << "������ �������� ����� ��� ������" << endl;
        return;
    }

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

//������� ��� �������� �����
void gammaTest()
{
        // ���� �� ����������� ���� �����
    string text = "������ ���, �� the best �������";
    string gammaType = chooseGammaType(text);
    cout<<text<<"     "<<"��� �����: "<<gammaType<<endl;

    text = "������ ���, we the best team";
    gammaType = chooseGammaType(text);
    cout<<text<<"     "<<"��� �����: "<<gammaType<<endl;
}

void testDay() {
    // ����� ��� Day()
    assert(Day() >= 0 && Day() <= 6); // ���� ������ ������ ���� � ��������� �� 0 �� 6
}

void testGenerateGamma() {
    // ����� ��� generateGamma()
    assert(generateGamma(1) == "ABCD EFGH IJKL MNOP");
    assert(generateGamma(2) == "GHEF OPMN ABCD IJKL");
    assert(generateGamma(3) == "ABCD EFGH IJKL MNOP");
    assert(generateGamma(4) == "GHEF OPMN ABCD IJKL");
    assert(generateGamma(5) == "ABCD EFGH IJKL MNOP");
    assert(generateGamma(6) == "GHEF CDAB OPMN KLIJ");
    assert(generateGamma(7) == "GHEF CDAB OPMN KLIJ");
    assert(generateGamma(8) == ""); // ������������ ���� ������
}

// ������� ����������� �����
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
        cout << "����������� ����� ���������. ������������ �������!" << endl;
    } else {
        cout << "����������� ����� �� ���������." << endl;
    }
}

int main()
{
    KeyTest();
    cyphetTest();
    gammaTest();
    testDay();
    testGenerateGamma();
    readFile();
    writeFile();
    summaTest();

    return 0;
}
