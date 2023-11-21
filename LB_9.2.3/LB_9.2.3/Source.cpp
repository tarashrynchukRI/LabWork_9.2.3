#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // ������������ ����������� ��������
using namespace std;

enum Speciality { CS, INF, ME, PI, TN };
string specialityStr[] = { "����'����� �����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };

struct Student {
    string surname;
    unsigned course;
    Speciality speciality;
    int physics;
    int math;
    union {
        int programming;
        int numericalMethods;
        int pedagogy;
    };
};

void Create(Student* s, const int N);
void Print(Student* s, const int N);
int BinSearch(Student* s, const int N, const string surname, const unsigned course, const double avgGrade);

int main() {
    SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
    SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������

    int N;
    cout << "������ ������� �������� N: "; cin >> N;

    Student* s = new Student[N];

    Create(s, N);
    Print(s, N);

    string surname;
    unsigned course;
    double avgGrade;
    cout << "������ ������� ��������: "; cin >> surname;
    cout << "������ ����: "; cin >> course;
    cout << "������ ������� ���: "; cin >> avgGrade;

    int idx = BinSearch(s, N, surname, course, avgGrade);
    if (idx != -1)
        cout << "������� " << surname << " ��������� �� " << course << " ����." << endl;
    else
        cout << "�������� " << surname << " ���� �� " << course << " ����." << endl;

    return 0;
}

void Create(Student* s, const int N) {
    int speciality;
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":" << endl;
        cin.get(); // ������� ����� ��������� � �� ����������� �������
        cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

        cout << " �������: "; getline(cin, s[i].surname);
        cout << " ����: "; cin >> s[i].course;
        cout << " ������������ (0 - ����'����� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
        cin >> speciality;
        s[i].speciality = (Speciality)speciality;
        cout << " ������ � ������: "; cin >> s[i].physics;
        cout << " ������ � ����������: "; cin >> s[i].math;
        switch (s[i].speciality) {
        case CS:
            cout << " ������ � �������������: "; cin >> s[i].programming;
            break;
        case INF:
            cout << " ������ � ��������� ������: "; cin >> s[i].numericalMethods;
            break;
        case ME:
        case PI:
        case TN:
            cout << " ������ � ���������: "; cin >> s[i].pedagogy;
            break;
        }
        cout << endl;
    }
}

void Print(Student* s, const int N) {
    cout << "====================================================================================================" << endl;
    cout << "| " << setw(2) << "�" << " |" << setw(15) << "�������" << " |" << setw(6) << "����" << " |" << setw(25) << "������������" << " |" << setw(8) << "Գ����" << " |" << setw(13) << "����������" << " |" << setw(15) << "�������������" << " |" << setw(15) << "������� ������" << " |" << setw(10) << "���������" << " |" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1 << " ";
        cout << "| " << setw(15) << s[i].surname
            << "| " << setw(5) << s[i].course << " "
            << "| " << setw(25) << specialityStr[s[i].speciality]
            << "| " << setw(8) << s[i].physics
            << "| " << setw(12) << s[i].math << " ";
        switch (s[i].speciality) {
        case CS:
            cout << "| " << setw(15) << s[i].programming
                << "| " << setw(15) << " "
                << "| " << setw(15) << " " << endl;
            break;
        case INF:
            cout << "| " << setw(15) << " "
                << "| " << setw(15) << s[i].numericalMethods
                << "| " << setw(15) << " " << endl;
            break;
        case ME:
        case PI:
        case TN:
            cout << "| " << setw(15) << " "
                << "| " << setw(15) << " "
                << "| " << setw(15) << s[i].pedagogy << " |" << endl;
            break;
        }
    }
    cout << "====================================================================================================" << endl;
    cout << endl;


}


int BinSearch(Student* s, const int N, const string surname, const unsigned course, const double avgGrade) {
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        double avg = (s[m].physics + s[m].math + (s[m].speciality == CS ? s[m].programming : (s[m].speciality == INF ? s[m].numericalMethods : s[m].pedagogy))) / 3.0;
        if (s[m].surname == surname && s[m].course == course && avg == avgGrade)
            return m;
        if ((s[m].surname < surname)
            || (s[m].surname == surname && s[m].course < course)
            || (s[m].surname == surname && s[m].course == course && avg < avgGrade)) {
            L = m + 1;
        }
        else {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}

