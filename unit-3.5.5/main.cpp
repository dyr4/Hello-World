#include <iostream>
#include <string>
#include <ctime>

// ������� �� ��������� ����

// ������� ��� ��������� �����
std::string generateKey(const std::string& key, size_t length) {
    std::string generatedKey;
    for (size_t i = 0; i < length; ++i) {
        generatedKey += key[i % key.size()]; // ���������� ���� ������ �����
    }
    return generatedKey;
}

// ������� ��� ���������� � ������������
std::string xorCipher(const std::string& data, const std::string& key) {
    std::string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i]; // ���������� XOR ��� ���������� � ������������
    }
    return result;
}

// ������� ��� ���������� ��� ������
int Day() {
    time_t tm = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%d", localtime(&tm));
    return std::stoi(buf);
}

// ������� ��� ����������� ���� �����
std::string chooseGammaType(const std::string& text) {
    int latinCount = 0;
    int cirillicCount = 0;

    for (char c : text) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) { // ������� ��������� ��������
            latinCount++;
        } else if ((c >= '�' && c <= '�') || (c >= '�' && c <= '�')) { // ������� ���������
            cirillicCount++;
        }
    }
    if(latinCount > cirillicCount) {
        return "latin";
    } else {
        return "cirillic";
    }
}

// ���� ��� ��������� �����
void KeyTest() {
    std::string text = "Hello world! We the best team";
    std::string key = "forest";
    std::string generatedKey = generateKey(key, text.size());
    if(generatedKey == "forestforestforestforestfores") {
        std::cout << "��������� ����� ������� ������ ��������" << std::endl;
    } else {
        std::cout << "��������� ����� �������� �� ������" << std::endl;
    }
}

// ���� ��� XOR ���������� � ������������
void CipherTest() {
    std::string data1 = "Hello, World!";
    std::string key1 = "key";
    std::string encrypted1 = xorCipher(data1, key1);
    std::string decrypted1 = xorCipher(encrypted1, key1);
    if(decrypted1 == data1) {
        std::cout << "���� 1 ������� �������" << std::endl;
    } else {
        std::cout << "���� 1 ��������" << std::endl;
    }

    std::string data2 = "";
    std::string key2 = "key";
    std::string encrypted2 = xorCipher(data2, key2);
    std::string decrypted2 = xorCipher(encrypted2, key2);
    if(decrypted2 == data2) {
        std::cout << "���� 2 ������� �������" << std::endl;
    } else {
        std::cout << "���� 2 ��������" << std::endl;
    }

    std::string data3 = "Hello!";
    std::string key3 = "abc";
    std::string encrypted3 = xorCipher(data3, key3);
    std::string decrypted3 = xorCipher(encrypted3, key3);
    if(decrypted3 == data3) {
        std::cout << "���� 3 ������� �������" << std::endl;
    } else {
        std::cout << "���� 3 ��������" << std::endl;
    }

    std::string data4 = "Hi!";
    std::string key4 = "123456";
    std::string encrypted4 = xorCipher(data4, key4);
    std::string decrypted4 = xorCipher(encrypted4, key4);
    if(decrypted4 == data4) {
        std::cout << "���� 4 ������� �������" << std::endl;
    } else {
        std::cout << "���� 4 ��������" << std::endl;
    }
}

// ���� ��� ���������� �������� ���
void DayTest() {
    int day = Day();
    int nowDay;
    std::cout << "������� ����� ������ �����: ";
    std::cin >> nowDay;
    if(day == nowDay) {
        std::cout << "�������� ���� ������ �������" << std::endl;
    } else {
        std::cout << "�������� ���� ���������" << std::endl;
    }
}

// ���� ��� ����������� ���� �����
void GammaTest() {
    std::string text1 = "������ ���, �� ������ �������";
    std::string gammaType1 = chooseGammaType(text1);
    std::cout << text1 << "     " << "��� �����: " << gammaType1 << std::endl;

    std::string text2 = "������ ���, we are the best team";
    std::string gammaType2 = chooseGammaType(text2);
    std::cout << text2 << "     " << "��� �����: " << gammaType2 << std::endl;
}

int main() {
    setlocale(0, "Russian");
    KeyTest();
    CipherTest();
    DayTest();
    GammaTest();
    return 0;
}
