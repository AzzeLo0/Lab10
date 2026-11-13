#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <limits>

using namespace std;

// Лабораторна робота 10, варіант 23.
// Автор: Саржевський Даніїл Олександрович, ІПЗ-12(6).
// Завдання: обробити масив структур студентів та виконати три запити.

const int MaxStudents = 60;
const int MaxExams = 5;
const int MaxText = 25;

struct Student
{
    char faculty[MaxText];
    int course;
    char group[MaxText];
    char surname[MaxText];
    int grades[MaxExams];
    int examCount;
    double scholarship;
};

// Уведення цілого числа у заданих межах.
int readInt(const char prompt[], int minValue, int maxValue)
{
    int value = 0;
    bool correct = false;

    while (!correct)
    {
        cout << prompt;

        if (cin >> value && value >= minValue && value <= maxValue)
            correct = true;
        else
            cout << "Incorrect value. Try again.\n";

        if (!cin)
            cin.clear();

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return value;
}

// Уведення невід'ємного числа.
double readMoney(const char prompt[])
{
    double value = -1;
    bool correct = false;

    while (!correct)
    {
        cout << prompt;

        if (cin >> value && value >= 0 && value <= 1000000)
            correct = true;
        else
            cout << "Incorrect value. Try again.\n";

        if (!cin)
            cin.clear();

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return value;
}

// Уведення одного слова без пробілів.
void readWord(const char prompt[], char text[])
{
    cout << prompt;
    cin.getline(text, MaxText);
}

// Копіювання короткого тексту у поле структури.
void copyText(char target[], const char source[])
{
    int i = 0;

    while (source[i] != '\0' && i < MaxText - 1)
    {
        target[i] = source[i];
        i++;
    }

    target[i] = '\0';
}
    
// Уведення масиву структур з клавіатури.
int inputStudents(Student students[])
{
    int count = readInt("Number of students (1-60): ", 1, MaxStudents);

    for (int i = 0; i < count; i++)
    {
        cout << "\nStudent " << i + 1 << "\n";
        readWord("Faculty: ", students[i].faculty);
        students[i].course = readInt("Course (1-6): ", 1, 6);
        readWord("Group: ", students[i].group);
        readWord("Surname: ", students[i].surname);
        students[i].examCount = readInt("Number of exams (1-5): ", 1, MaxExams);

        for (int j = 0; j < students[i].examCount; j++)
            students[i].grades[j] = readInt("Exam grade (2-5): ", 2, 5);

        students[i].scholarship = readMoney("Scholarship: ");
    }

    return count;
}

// Генерація тестового масиву структур.
int generateStudents(Student students[])
{
    const char* faculties[3] = { "FIT", "FKNK", "FMEF" };
    const char* prefixes[3] = { "IPZ", "KN", "EK" };
    const char* surnames[12] = {
        "Bondar", "Melnyk", "Koval", "Shevchenko",
        "Petrenko", "Ivanenko", "Tkachenko", "Sydorenko",
        "Kravchenko", "Marchenko", "Boyko", "Polishchuk"
    };
    int count = readInt("Number of students (1-60): ", 1, MaxStudents);

    for (int i = 0; i < count; i++)
    {
        int facultyId = rand() % 3;
        copyText(students[i].faculty, faculties[facultyId]);
        students[i].course = 1 + rand() % 4;
        int groupId = 1 + rand() % 3;
        snprintf(students[i].group, MaxText, "%s-%d%d", prefixes[facultyId], students[i].course, groupId);
        copyText(students[i].surname, surnames[rand() % 12]);
        students[i].examCount = 3;

        for (int j = 0; j < students[i].examCount; j++)
            students[i].grades[j] = 2 + rand() % 4;

        students[i].scholarship = (rand() % 4) * 800;
    }

    return count;
}

// Створення масиву в один із двох способів.
int createStudents(Student students[])
{
    cout << "\n1 - Keyboard input\n2 - Random generation\n";
    int choice = readInt("Choose: ", 1, 2);
    int count = 0;

    if (choice == 1)
        count = inputStudents(students);
    else
        count = generateStudents(students);

    return count;
}

// Обчислення середнього балу студента.
double averageGrade(const Student & student)
{
    int sum = 0;

    for (int i = 0; i < student.examCount; i++)
        sum = sum + student.grades[i];

    return double(sum) / student.examCount;
}

// Перевірка, чи всі екзаменаційні оцінки дорівнюють 5.
bool isExcellent(const Student & student)
{
    bool excellent = true;

    for (int i = 0; i < student.examCount; i++)
    {
        if (student.grades[i] != 5)
            excellent = false;
    }

    return excellent;
}

// Перевірка наявності оцінки 2.
bool hasBadGrade(const Student& student)
{
    bool hasTwo = false;

    for (int i = 0; i < student.examCount; i++)
    {
        if (student.grades[i] == 2)
            hasTwo = true;
    }

    return hasTwo;
}

// Заголовок таблиці студентів.
void printStudentHeader()
{
    cout << left << setw(17) << "Surname"
        << setw(10) << "Faculty"
        << setw(9) << "Course"
        << setw(12) << "Group"
        << setw(16) << "Grades"
        << setw(12) << "Scholarship"
        << "Average\n";
    cout << "-------------------------------------------------------------------------------\n";
}

// Один рядок таблиці студентів.
void printStudentRow(const Student& student)
{
    cout << left << setw(17) << student.surname
        << setw(10) << student.faculty
        << setw(9) << student.course
        << setw(12) << student.group;

    char gradeText[24] = "";
    int position = 0;
    for (int i = 0; i < student.examCount; i++)
    {
        if (i > 0)
            gradeText[position++] = ',';
        gradeText[position++] = char('0' + student.grades[i]);
    }
    gradeText[position] = '\0';

    cout << setw(16) << gradeText
        << setw(12) << fixed << setprecision(2) << student.scholarship
        << averageGrade(student) << '\n';
}

// Виведення всього масиву структур.
void printStudents(const Student students[], int count)
{
    cout << "\nSTUDENT TABLE\n";
    printStudentHeader();

    for (int i = 0; i < count; i++)
        printStudentRow(students[i]);
}

// Запит А: студенти зі стипендією і їх середній бал.
void showScholarships(const Student students[], int count)
{
    double minimum = readMoney("Minimum scholarship (0 = all scholarship holders): ");
    bool found = false;

    cout << "\nSTUDENTS WITH SCHOLARSHIP\n";
    printStudentHeader();

    for (int i = 0; i < count; i++)
    {
        if (students[i].scholarship > 0 && students[i].scholarship >= minimum)
        {
            printStudentRow(students[i]);
            found = true;
        }
    }

    if (!found)
        cout << "No matching students.\n";
}

// Перевірка, чи група вже була опрацьована.
bool groupWasChecked(const Student students[], int index)
{
    bool checked = false;

    for (int j = 0; j < index; j++)
    {
        if (students[j].course == 1 &&
            strcmp(students[j].faculty, students[index].faculty) == 0 &&
            strcmp(students[j].group, students[index].group) == 0)
            checked = true;
    }

    return checked;
}

// Перевірка, чи у групі першого курсу немає двійок.
bool groupHasNoTwos(const Student students[], int count, int index)
{
    bool good = true;

    for (int j = 0; j < count; j++)
    {
        if (students[j].course == 1 &&
            strcmp(students[j].faculty, students[index].faculty) == 0 &&
            strcmp(students[j].group, students[index].group) == 0 &&
            hasBadGrade(students[j]))
            good = false;
    }

    return good;
}

// Кількість груп без двійок на першому курсі факультету.
int countGoodGroups(const Student students[], int count, const char faculty[])
{
    int result = 0;

    for (int i = 0; i < count; i++)
    {
        if (students[i].course == 1 &&
            strcmp(students[i].faculty, faculty) == 0 &&
            !groupWasChecked(students, i) &&
            groupHasNoTwos(students, count, i))
            result++;
    }

    return result;
}

// Формування списку факультетів з першокурсниками.
int listFirstYearFaculties(const Student students[], int count, char faculties[][MaxText])
{
    int facultyCount = 0;

    for (int i = 0; i < count; i++)
    {
        bool newFaculty = students[i].course == 1;

        for (int j = 0; j < facultyCount; j++)
        {
            if (strcmp(students[i].faculty, faculties[j]) == 0)
                newFaculty = false;
        }

        if (newFaculty)
        {
            copyText(faculties[facultyCount], students[i].faculty);
            facultyCount++;
        }
    }

    return facultyCount;
}

// Друк результатів пошуку кращого факультету.
void printFacultyResults(char faculties[][MaxText], const int results[], int facultyCount)
{
    int maximum = 0;
    cout << "\nFACULTIES: FIRST-YEAR GROUPS WITHOUT GRADE 2\n";
    cout << left << setw(18) << "Faculty" << "Good groups\n";
    cout << "-------------------------------\n";

    for (int i = 0; i < facultyCount; i++)
    {
        cout << left << setw(18) << faculties[i] << results[i] << '\n';
        if (results[i] > maximum)
            maximum = results[i];
    }

    if (maximum == 0)
        cout << "No first-year groups without grade 2.\n";
    else
    {
        cout << "Maximum = " << maximum << "; best faculty: ";
        for (int i = 0; i < facultyCount; i++)
        {
            if (results[i] == maximum)
                cout << faculties[i] << ' ';
        }
        cout << '\n';
    }
}

// Запит Б: факультет з найбільшою кількістю груп без двійок.
void showBestFaculty(const Student students[], int count)
{
    char faculties[MaxStudents][MaxText];
    int results[MaxStudents] = { 0 };
    int facultyCount = listFirstYearFaculties(students, count, faculties);

    for (int i = 0; i < facultyCount; i++)
        results[i] = countGoodGroups(students, count, faculties[i]);

    printFacultyResults(faculties, results, facultyCount);
}

// Запит В: курс з найбільшою кількістю відмінників.
void showBestCourse(const Student students[], int count)
{
    int excellentCount[6] = { 0 };
    int maximum = 0;

    for (int i = 0; i < count; i++)
    {
        if (isExcellent(students[i]))
            excellentCount[students[i].course - 1]++;
    }

    cout << "\nCOURSES WITH EXCELLENT STUDENTS\n";
    cout << left << setw(12) << "Course" << "Excellent students\n";
    cout << "------------------------------\n";
    for (int i = 0; i < 6; i++)
    {
        cout << left << setw(12) << i + 1 << excellentCount[i] << '\n';
        if (excellentCount[i] > maximum)
            maximum = excellentCount[i];
    }

    if (maximum == 0)
        cout << "No excellent students.\n";
    else
    {
        cout << "Maximum = " << maximum << "; best course: ";
        for (int i = 0; i < 6; i++)
        {
            if (excellentCount[i] == maximum)
                cout << i + 1 << ' ';
        }
        cout << '\n';
    }
}

// Додатковий запит за прізвищем як ключем пошуку.
void searchSurname(const Student students[], int count)
{
    char surname[MaxText];
    bool found = false;
    readWord("Enter surname: ", surname);
    cout << "\nSEARCH RESULT\n";
    printStudentHeader();

    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].surname, surname) == 0)
        {
            printStudentRow(students[i]);
            found = true;
        }
    }

    if (!found)
        cout << "No matching students.\n";
}

// Меню команд.
void printMenu()
{
    cout << "\n1 - Create student array\n"
         << "2 - Print student array\n"
         << "3 - Students with scholarship and average grade\n"
         << "4 - Faculty with most good first-year groups\n"
         << "5 - Course with most excellent students\n"
         << "6 - Find student by surname\n"
         << "0 - Exit\n";
}

// Керування програмою через виклики окремих функцій.
void runProgram()
{
    Student students[MaxStudents];
    int count = 0;
    int choice = -1;
    srand((unsigned)time(NULL));

    while (choice != 0)
    {
        printMenu();
        choice = readInt("Choose: ", 0, 6);

        if (choice == 1)
        {
            count = createStudents(students);
            printStudents(students, count);
        }
        else if (count == 0 && choice != 0)
            cout << "Create the student array first (command 1).\n";
        else if (choice == 2)
            printStudents(students, count);
        else if (choice == 3)
            showScholarships(students, count);
        else if (choice == 4)
            showBestFaculty(students, count);
        else if (choice == 5)
            showBestCourse(students, count);
        else if (choice == 6)
            searchSurname(students, count);
    }
}

// Дані автора і запуск програми.
void showHeader()
{
    cout << "Laboratory work 10, variant 23\n"
         << "Student: Sarzhevskyi Daniil Oleksandrovych\n"
         << "Group: IPZ-12(6)\n";
}

// Коротка умова задачі для користувача.
void showTask()
{
    cout << "Task: faculty, course, group, surname, grades, scholarship.\n"
         << "Queries: scholarship students and averages; best first-year faculty;\n"
         << "course with the highest number of excellent students.\n";
}

int main()
{
    showHeader();
    showTask();
    runProgram();
    return 0;
}