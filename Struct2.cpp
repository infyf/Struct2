#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#pragma warning(disable: 4996)
using namespace std;

// довжини полів рядка файлу
const int l_name = 35, l_year = 5, l_pay = 5;
// довжина буфера - сума довжин полів struct
const int l_buf = l_name + l_year + l_pay;
// структура для зберігання відомостей про працівника

const int l_dbase = 100;

struct Sotr {
    char name[l_name + 1]; /* довжина поля задана з
    урахуванням нуль-символу */
    int birth_year;
    float pay;
};

int DataSort(const int l_dbase, Sotr *dbase) { // Сортування за датою
    ofstream fout("LR5/db_otd-kadr.txt");
    if (!fout) { // перевірка на відкриття
        cout << " Помилка відкриття файлу !" << endl;
        return 1;
    }
	  //цикл в якому проходить сортування
    for (int i = 0; i < l_dbase - 1; i++) {
        int min_i = i;
        for (int j = i + 1; j < l_dbase; j++)
            if (dbase[j].birth_year < dbase[min_i].birth_year && dbase[j].pay == dbase[min_i].pay) min_i = j;
        // обмін елементами структур
        Sotr tmp = dbase[i];
        dbase[i] = dbase[min_i];
        dbase[min_i] = tmp;
    }
    for (int i = 0; i < l_dbase; i++) {
        fout << dbase[i].name << dbase[i].birth_year <<
            "\t" << dbase[i].pay << endl; // заповення файлу
    }
    fout.close(); // закриття файлу
}
int OkladSort(const int l_dbase, Sotr* dbase) { // сортування за окладом
    ofstream fout("LR5/db_otd-kadr.txt"); // відкриття файлу
    if (!fout) { // перевірка
        cout << " Помилка відкриття файлу !" << endl;
        return 1;
    }
	  // цикл у якому проходить сортування
    for (int i = 0; i < l_dbase - 1; i++) {
        int min_i = i;
        for (int j = i + 1; j < l_dbase; j++)
            if (dbase[j].pay < dbase[min_i].pay) min_i = j;
        // обмін елементами структур
        Sotr tmp = dbase[i];
        dbase[i] = dbase[min_i];
        dbase[min_i] = tmp;
    }
    // заповення файлу
    for (int i = 0; i < l_dbase; i++) {
        fout << dbase[i].name << dbase[i].birth_year <<
            "\t" << dbase[i].pay << endl;
    }
    fout.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // масив структур для зберігання всієї бази даних
    Sotr dbase[l_dbase];
    Sotr currBase[l_dbase];
    // буфер для зберігання рядка з файлу
    char buf[l_buf + 1];
    // рядок для ПІБ запитуваного працівника
    char name[l_name + 1];
    /////// Крок 1. Відкриття файлу і читання даних ///////
    ifstream fin("LR5/db_otd-kadr.txt");
    if (!fin.is_open()) {
        cout << "Помилка відкриття файлу!" << endl;
        return 1;
    }
    int i = 0;
    //заповнення бази даних
    while (!fin.eof()) { // поки не кінець файлу
        fin.getline(buf, l_buf); // зчитування строки у буфер
        strncpy(dbase[i].name, buf, l_name); // копіюємо ім'я в масив
        dbase[i].name[l_name] = '\0'; // додаємо останній символ
        dbase[i].birth_year = atoi(&buf[l_name]);
        dbase[i].pay = atof(&buf[l_name + l_year]);
        i++;
        if (i > l_dbase) {
            puts("Файл занадто довгий!\n");
            return 1;
        }
    }
    fin.close(); // закрити файл
    //////////// Крок 2. Пошук співробітників ////////////
    int n_record = i, n_sotr = 0; /* n_record -
    кількість записів про співробітників, n_sotr - кількість
    співробітників, про які виводяться дані */
    float sum_pay = 0; // сума окладів
    wchar_t* ansi_name = new wchar_t[100];
    int current = 0;
    setlocale(LC_ALL, "");
    while (true) {
        cout << "Введіть прізвище для пошуку (end - для завершення пошуку):";
        cin >> name;
        for (size_t i = 0; i < l_name + 1; i++)
        {
            name[i] = tolower(name[i]);
        }
        name[0] = toupper(name[0]);
        OemToChar(name, ansi_name); // перетворює рядок в ANSI
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
        if (not_found) cout << "Такого співробітника немає!" << endl;
        if (_getch() == 27) break;
    }
    if (n_sotr > 0) cout << "Середній оклад: " << sum_pay / n_sotr << endl;

    //////////// Крок 2. Сортування ////////////
    OkladSort(l_dbase, dbase);
    DataSort(l_dbase, dbase);
