#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#pragma warning(disable: 4996)
using namespace std;

// ������� ���� ����� �����
const int l_name = 35, l_year = 5, l_pay = 5;
// ������� ������ - ���� ������ ���� struct
const int l_buf = l_name + l_year + l_pay;
// ��������� ��� ��������� ��������� ��� ����������

const int l_dbase = 100;

struct Sotr {
    char name[l_name + 1]; /* ������� ���� ������ �
    ����������� ����-������� */
    int birth_year;
    float pay;
};

int DataSort(const int l_dbase, Sotr *dbase) { // ���������� �� �����
    ofstream fout("LR5/db_otd-kadr.txt");
    if (!fout) { // �������� �� ��������
        cout << " ������� �������� ����� !" << endl;
        return 1;
    }
	  //���� � ����� ��������� ����������
    for (int i = 0; i < l_dbase - 1; i++) {
        int min_i = i;
        for (int j = i + 1; j < l_dbase; j++)
            if (dbase[j].birth_year < dbase[min_i].birth_year && dbase[j].pay == dbase[min_i].pay) min_i = j;
        // ���� ���������� ��������
        Sotr tmp = dbase[i];
        dbase[i] = dbase[min_i];
        dbase[min_i] = tmp;
    }
    for (int i = 0; i < l_dbase; i++) {
        fout << dbase[i].name << dbase[i].birth_year <<
            "\t" << dbase[i].pay << endl; // ��������� �����
    }
    fout.close(); // �������� �����
}
int OkladSort(const int l_dbase, Sotr* dbase) { // ���������� �� �������
    ofstream fout("LR5/db_otd-kadr.txt"); // �������� �����
    if (!fout) { // ��������
        cout << " ������� �������� ����� !" << endl;
        return 1;
    }
	  // ���� � ����� ��������� ����������
    for (int i = 0; i < l_dbase - 1; i++) {
        int min_i = i;
        for (int j = i + 1; j < l_dbase; j++)
            if (dbase[j].pay < dbase[min_i].pay) min_i = j;
        // ���� ���������� ��������
        Sotr tmp = dbase[i];
        dbase[i] = dbase[min_i];
        dbase[min_i] = tmp;
    }
    // ��������� �����
    for (int i = 0; i < l_dbase; i++) {
        fout << dbase[i].name << dbase[i].birth_year <<
            "\t" << dbase[i].pay << endl;
    }
    fout.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // ����� �������� ��� ��������� �񳺿 ���� �����
    Sotr dbase[l_dbase];
    Sotr currBase[l_dbase];
    // ����� ��� ��������� ����� � �����
    char buf[l_buf + 1];
    // ����� ��� ϲ� ������������ ����������
    char name[l_name + 1];
    /////// ���� 1. ³������� ����� � ������� ����� ///////
    ifstream fin("LR5/db_otd-kadr.txt");
    if (!fin.is_open()) {
        cout << "������� �������� �����!" << endl;
        return 1;
    }
    int i = 0;
    //���������� ���� �����
    while (!fin.eof()) { // ���� �� ����� �����
        fin.getline(buf, l_buf); // ���������� ������ � �����
        strncpy(dbase[i].name, buf, l_name); // ������� ��'� � �����
        dbase[i].name[l_name] = '\0'; // ������ ������� ������
        dbase[i].birth_year = atoi(&buf[l_name]);
        dbase[i].pay = atof(&buf[l_name + l_year]);
        i++;
        if (i > l_dbase) {
            puts("���� ������� ������!\n");
            return 1;
        }
    }
    fin.close(); // ������� ����
    //////////// ���� 2. ����� ����������� ////////////
    int n_record = i, n_sotr = 0; /* n_record -
    ������� ������ ��� �����������, n_sotr - �������
    �����������, ��� �� ���������� ��� */
    float sum_pay = 0; // ���� ������
    wchar_t* ansi_name = new wchar_t[100];
    int current = 0;
    setlocale(LC_ALL, "");
    while (true) {
        cout << "������ ������� ��� ������ (end - ��� ���������� ������):";
        cin >> name;
        for (size_t i = 0; i < l_name + 1; i++)
        {
            name[i] = tolower(name[i]);
        }
        name[0] = toupper(name[0]);
        OemToChar(name, ansi_name); // ���������� ����� � ANSI
        if (strcmp(name, "end") == 0) break;
        bool not_found = true;
        for (int i = 0; i < n_record; i++) {
            if (strstr(dbase[i].name, name))
                if (dbase[i].name[strlen(name)] == ' ') {
                    cout << dbase[i].name << dbase[i].birth_year << "\t" << dbase[i].pay << endl;
                    n_sotr++;
                    currBase[current] = dbase[i];
                    if (current != 0 && currBase[current].pay > currBase[--current].pay * 0.5 && currBase[current].pay < currBase[--current].pay * 1.5)
                    {
                        sum_pay += dbase[i].pay;
                    }
                    else if (current == 0) {
                        sum_pay += dbase[i].pay;
                    }
                    not_found = false;
                    current++;
                }
        }
        if (not_found) cout << "������ ����������� ����!" << endl;
        if (_getch() == 27) break;
    }
    if (n_sotr > 0) cout << "������� �����: " << sum_pay / n_sotr << endl;

    //////////// ���� 2. ���������� ////////////
    OkladSort(l_dbase, dbase);
    DataSort(l_dbase, dbase);
