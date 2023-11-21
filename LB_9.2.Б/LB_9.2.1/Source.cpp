#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
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
void Sort(Student* s, const int N);
int* IndexSort(Student* s, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);
int GetSubjectGrade(Student& s);
int BinSearch(Student* s, const int N, const string surname, const unsigned course, const double avgGrade);

int main() {
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251); 

    int N;
    cout << "������ ������� �������� N: "; cin >> N;
    int menuItem;
    int idx;
    string surname;
    unsigned course;
    double avgGrade;
    
    Student* s = new Student[N];

    Create(s, N);
    Print(s, N);

    do {
        cout << endl << endl << endl;
        cout << "������� ��:" << endl << endl;
        cout << " [1] - ���� ����� �� �����" << endl;
        cout << " [2] - Գ����� ������������� ������" << endl;
        cout << " [3] - �������� ������������� ������" << endl;
        cout << " [4] - �������� �����" << endl;
        cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
        cout << "������ ��������: "; cin >> menuItem;
        cout << endl << endl << endl;
        switch (menuItem)
        {
        case 1:
            Print(s, N);
            break;
        case 2:
            Sort(s, N);
            Print(s, N);
            break;
        case 3:
            IndexSort(s, N);
            PrintIndexSorted(s, IndexSort(s, N), N);
            break;
        case 4:
            
            cout << "������ ������� ��������: "; cin >> surname;
            cout << "������ ����: "; cin >> course;
            cout << "������ ������� ���: "; cin >> avgGrade;

            idx = BinSearch(s, N, surname, course, avgGrade);
            if (idx != -1)
                cout << "������� " << surname << " ��������� �� " << course << " ����." << endl;
            else
                cout << "�������� " << surname << " ���� �� " << course << " ����." << endl;
            break;
        case 0:
            break;
        default:
            cout << "�� ����� ��������� ��������! "
                "��� ������ ����� - ����� ��������� ������ ����" << endl;
        }
    } while (menuItem != 0);

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

void Sort(Student* s, const int N) {
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((s[i1].course > s[i1 + 1].course)
                || (s[i1].course == s[i1 + 1].course && s[i1].physics + s[i1].math + GetSubjectGrade(s[i1]) > s[i1 + 1].physics + s[i1 + 1].math + GetSubjectGrade(s[i1 + 1]))
                || (s[i1].course == s[i1 + 1].course && s[i1].physics + s[i1].math + GetSubjectGrade(s[i1]) == s[i1 + 1].physics + s[i1 + 1].math + GetSubjectGrade(s[i1 + 1]) && s[i1].surname < s[i1 + 1].surname)) {
                tmp = s[i1];
                s[i1] = s[i1 + 1];
                s[i1 + 1] = tmp;
            }
}

int* IndexSort(Student* s, const int N) {
    int* I = new int[N]; // �������� ��������� �����
    for (int i = 0; i < N; i++)
        I[i] = i; // ��������� ���� ����������� ������

    // �������� ��������� ����� �������
    for (int i = 1; i < N; i++) {
        int value = I[i];
        int j = i - 1;

        // ��������� �� ������� �����, ������� ����� �� ��������
        while (j >= 0 && (
            s[I[j]].course > s[value].course ||
            (s[I[j]].course == s[value].course &&
                s[I[j]].physics + s[I[j]].math + GetSubjectGrade(s[I[j]]) > s[value].physics + s[value].math + GetSubjectGrade(s[value]) ||
                (s[I[j]].course == s[value].course &&
                    s[I[j]].physics + s[I[j]].math + GetSubjectGrade(s[I[j]]) == s[value].physics + s[value].math + GetSubjectGrade(s[value]) &&
                    s[I[j]].surname > s[value].surname)
                ))) {
            I[j + 1] = I[j];
            j--;
        }

        I[j + 1] = value;
    }

    return I;
}

int GetSubjectGrade(Student& s) {
    switch (s.speciality) {
    case CS:
        return s.programming;
    case INF:
        return s.numericalMethods;
    case ME:
    case PI:
    case TN:
        return s.pedagogy;
    default:
        return 0;
    }
}

void PrintIndexSorted(Student* s, int* I, const int N) {
    cout << "====================================================================================================" << endl;
    cout << "| " << setw(2) << "�" << " |" << setw(15) << "�������" << " |" << setw(6) << "����" << " |" << setw(25) << "������������" << " |" << setw(8) << "Գ����" << " |" << setw(13) << "����������" << " |" << setw(15) << "�������������" << " |" << setw(15) << "������� ������" << " |" << setw(10) << "���������" << " |" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1 << " ";
        cout << "| " << setw(15) << s[I[i]].surname
            << "| " << setw(5) << s[I[i]].course << " "
            << "| " << setw(25) << specialityStr[s[I[i]].speciality]
            << "| " << setw(8) << s[I[i]].physics
            << "| " << setw(12) << s[I[i]].math << " ";
        switch (s[i].speciality) {
        case CS:
            cout << "| " << setw(15) << s[I[i]].programming
                << "| " << setw(15) << " "
                << "| " << setw(15) << " " << endl;
            break;
        case INF:
            cout << "| " << setw(15) << " "
                << "| " << setw(15) << s[I[i]].numericalMethods
                << "| " << setw(15) << " " << endl;
            break;
        case ME:
        case PI:
        case TN:
            cout << "| " << setw(15) << " "
                << "| " << setw(15) << " "
                << "| " << setw(15) << s[I[i]].pedagogy << " |" << endl;
            break;
        }
    }
    cout << "====================================================================================================" << endl;
    cout << endl;
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