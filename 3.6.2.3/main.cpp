#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <thread>
#include <chrono>

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

int Day()
{
    auto t1 = chrono::system_clock::now();

    // time_point � time_t
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

// ������� ����������� �����
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

    // ������ ������ �� �����
    string text;
    ifstream fileIn(file_in);

    if (fileIn.is_open()) {
        getline(fileIn, text);
        fileIn.close();
    } else {
        cout << "������: �� ������� ������� ���� " << file_in << endl;
        return 1;
    }

    string chooseDay;
    cout<<"����� ���� ������ �� �������?(Yes or No)"<<endl;
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
                cout<<"������� ����� �� 1 �� 7: ";
                cin>>gammaType;
                if(!(gammaType >= 0 || gammaType <= 7))
                {
                    cout<<"������������ ����"<<endl;
                }
            }
        }
        else
        {
            cout<<"������������ ����"<<endl;
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


    // ����� �����
    string gamma = generateGamma(gammaType);

    // ��������� ����� ������ �����
    string generatedKey = generateKey(gamma, text.size()); // ���������� ��������� ����
    cout << "��������� �����: " << generatedKey << endl;

    //���������� ����������� �����
    char kontSum = kontrolnayaSumma(text, key2);
    text += kontSum;

    // ����������
    string ciphertext = xorCipher(text, generatedKey);
    cout << "������������� �����: " << ciphertext << endl;

    // ������ �������������� ������ � ����
    ofstream outputFile(file_out);
    if (!outputFile.is_open()) {
        cout << "������ ��� �������� ����� " << file_out << endl;
        return 1;
    }

    outputFile << ciphertext;
    outputFile.close();

    // ������������ ������
    string decryptedtext = xorCipher(ciphertext, generatedKey);
    cout << "�������������� �����: " << decryptedtext << endl;

    key1 = (key1 % 3) + 1;

    // ���������� ����������� �����
        char kontAfterSum = decryptedtext.back();
        decryptedtext.pop_back();

        // �������� ����������� �����
        kontSum = kontrolnayaSumma(decryptedtext, key2);
        if (kontSum == kontAfterSum) {
            cout << "����������� ����� ���������. ������������ �������!" << endl;
        } else {
            cout << "����������� ����� �� ���������." << endl;
        }

        // �������� ���������� �����
        this_thread::sleep_for(chrono::seconds(20)); // ��������� �� ��������� �����
    }
    return 0;
}



