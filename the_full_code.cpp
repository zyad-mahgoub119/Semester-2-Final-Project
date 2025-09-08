#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include <sstream>
using namespace std;

// ==================== AUTHENTICATION MODULE ====================

class User {
    public:
        string username;
        string password;
        string role;
        string displayName;

        User(string u, string p, string r, string d)  {
            username = u;
            password = p;
            role = r;
            displayName = d;
        }
    };

class Manager : public User {
public:
    Manager(string u, string p, string d) : User("", "", "", "") {
    username = u;
    password = p;
    role = "manager";
    displayName = d;
    }
};

class Teacher : public User {
public:
    Teacher(string u, string p, string d) : User("", "", "", "") {
        username = u;
        password = p;
        role = "teacher";
        displayName = d;
    }
};

class AuthSystem {
private:
    vector<User> users;
public:
    AuthSystem() {
        users.push_back(Manager("admin1", "manger123", "Principal Akram"));
        users.push_back(Manager("admin2", "manger456", "Vice Principal Marwan"));
        users.push_back(Teacher("teacher1", "teacher123", "Mr. Ahmed"));
        users.push_back(Teacher("teacher2", "teacher456", "Mr. Mohamed"));
        users.push_back(Teacher("teacher3", "teacher789", "Mrs. Kenzy"));
    }

    bool login(string username, string password) {
        for (const User& user : users) {
            if (user.username == username && user.password == password) {
                return true;
            }
        }
        return false;
    }

    string getRole(string username) {
        for (const User& user : users) {
            if (user.username == username) {
                return user.role;
            }
        }
        return "";
    }

    string getDisplayName(string username) {
        for (const User& user : users) {
            if (user.username == username) {
                return user.displayName;
            }
        }
        return username;
    }

    vector<string> getTeacherNames() {
        vector<string> teachers;
        for (const User& user : users) {
            if (user.role == "teacher") {
                teachers.push_back(user.displayName);
            }
        }
        return teachers;
    }
};

// ==================== CLASS MANAGEMENT ====================
struct Class {
    string name;
    string teacher;
    vector<string> students;
};

vector<Class> allClasses;

void saveData() {
    ofstream classFile("classes.txt");
    for (int i = 0; i < allClasses.size(); i++) {
        classFile << allClasses[i].name << "," << allClasses[i].teacher << endl;
    }

    ofstream studentFile("students.txt");
    for (int i = 0; i < allClasses.size(); i++) {
        for (int j = 0; j < allClasses[i].students.size(); j++) {
            studentFile << allClasses[i].name << "," << allClasses[i].students[j] << endl;
        }
    }
}

void loadData(AuthSystem& auth) {
    ifstream classFile("classes.txt");
    string line;
    while (getline(classFile, line)) {
        if (line.find(',') != string::npos) {
            size_t comma = line.find(',');
            Class newClass;
            newClass.name = line.substr(0, comma);
            newClass.teacher = line.substr(comma + 1);
            allClasses.push_back(newClass);
        }
    }

    ifstream studentFile("students.txt");
    while (getline(studentFile, line)) {
        if (line.find(',') != string::npos) {
            size_t comma = line.find(',');
            string className = line.substr(0, comma);
            string studentName = line.substr(comma + 1);

            for (int i = 0; i < allClasses.size(); i++) {
                if (allClasses[i].name == className) {
                    allClasses[i].students.push_back(studentName);
                    break;
                }
            }
        }
    }

    vector<string> validTeachers = auth.getTeacherNames();
    for (Class& cls : allClasses) {
        bool teacherValid = false;
        for (const string& teacher : validTeachers) {
            if (cls.teacher == teacher) {
                teacherValid = true;
                break;
            }
        }
        if (!teacherValid && !cls.teacher.empty()) {
            cout << "Warning: Teacher '" << cls.teacher << "' not found in auth system for class " << cls.name << endl;
        }
    }
}

void classManagement(AuthSystem& auth) {
    loadData(auth);
    vector<string> teachers = auth.getTeacherNames();

    while (true) {
        cout << "\n1. Add Class\n2. Add Student\n3. View All\n4. Save & Exit\nChoose: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Class newClass;
            cout << "Class name: ";
            getline(cin, newClass.name);

            cout << "Available Teachers:\n";
            for (int i = 0; i < teachers.size(); i++) {
                cout << i+1 << ". " << teachers[i] << endl;
            }
            cout << "Select teacher (1-" << teachers.size() << "): ";
            int teacherChoice;
            cin >> teacherChoice;
            cin.ignore();

            if (teacherChoice > 0 && teacherChoice <= teachers.size()) {
                newClass.teacher = teachers[teacherChoice-1];
                allClasses.push_back(newClass);
            } else {
                cout << "Invalid teacher selection!\n";
            }
        }
        else if (choice == 2) {
            string className, student;
            cout << "Class name: ";
            getline(cin, className);

            bool found = false;
            for (int i = 0; i < allClasses.size(); i++) {
                if (allClasses[i].name == className) {
                    cout << "Student name: ";
                    getline(cin, student);
                    allClasses[i].students.push_back(student);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Class not found!\n";
        }
        else if (choice == 3) {
            cout << "\n--- All Classes ---\n";
            for (int i = 0; i < allClasses.size(); i++) {
                cout << "\nClass: " << allClasses[i].name
                    << "\nTeacher: " << allClasses[i].teacher
                    << "\nStudents: ";

                for (int j = 0; j < allClasses[i].students.size(); j++) {
                    cout << allClasses[i].students[j];
                    if (j != allClasses[i].students.size() - 1) {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
        }
        else if (choice == 4) {
            saveData();
            cout << "Saved! Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
}

// ==================== GRADE MANAGEMENT ====================
struct Grade {
    string studentName;
    string subject;
    float score;
    string letterGrade;
    string comment;

    Grade(string name, string sub, float scr, string com) {
        studentName = name;
        subject = sub;
        score = scr;
        comment = com;
        letterGrade = calculateLetter(scr);
    }

    string calculateLetter(float score) {
        if (score >= 90) return "A";
        else if (score >= 80) return "B";
        else if (score >= 70) return "C";
        else if (score >= 60) return "D";
        else return "F";
    }
};

class GradeManager {
public:
    vector<Grade> grades;

    bool studentExistsInClasses(string name) {
        for (int i = 0; i < allClasses.size(); i++) {
            for (int j = 0; j < allClasses[i].students.size(); j++) {
                if (allClasses[i].students[j] == name) return true;
            }
        }
        return false;
    }

    void addGradeToStudent() {
        string name;
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);

        if (!studentExistsInClasses(name)) {
            cout << "Student not found in any class!\n";
            return;
        }

        string subject, comment;
        float score;

        cout << "Enter subject: ";
        getline(cin, subject);
        cout << "Enter score: ";
        cin >> score;
        cin.ignore();
        cout << "Enter comment: ";
        getline(cin, comment);

        Grade g(name, subject, score, comment);
        grades.push_back(g);
        saveGrades();

        cout << "Grade added successfully.\n";
    }

    void viewGrades() {
        string name;
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);

        bool found = false;
        for (int i = 0; i < grades.size(); i++) {
            if (grades[i].studentName == name) {
                if (!found) {
                    cout << "\nGrades for " << name << ":\n";
                    found = true;
                }
                cout << "Subject: " << grades[i].subject << ", Score: " << grades[i].score
                     << ", Grade: " << grades[i].letterGrade << ", Comment: " << grades[i].comment << "\n";
            }
        }

        if (!found) {
            cout << "No grades found for this student.\n";
        }
    }

    void generateClassReport() {
        string className;
        cout << "Enter class name: ";
        cin.ignore();
        getline(cin, className);

        bool classFound = false;
        for (int i = 0; i < allClasses.size(); i++) {
            if (allClasses[i].name == className) {
                classFound = true;
                cout << "\n=== CLASS REPORT: " << className << " ===\n";
                cout << "Teacher: " << allClasses[i].teacher << "\n";
                cout << "Students and Grades:\n";

                for (int j = 0; j < allClasses[i].students.size(); j++) {
                    cout << "\nStudent: " << allClasses[i].students[j] << "\n";
                    bool hasGrades = false;

                    for (int k = 0; k < grades.size(); k++) {
                        if (grades[k].studentName == allClasses[i].students[j]) {
                            if (!hasGrades) {
                                hasGrades = true;
                                cout << "Grades:\n";
                            }
                            cout << "  Subject: " << grades[k].subject << " - " << grades[k].score
                                 << " (" << grades[k].letterGrade << ")\n";
                            cout << "  Comment: " << grades[k].comment << "\n";
                        }
                    }

                    if (!hasGrades) {
                        cout << "  No grades recorded yet\n";
                    }
                }
                break;
            }
        }

        if (!classFound) {
            cout << "Class not found!\n";
        }
        cout << "=== END OF REPORT ===\n";
    }

    void saveGrades() {
        ofstream gradeFile("grades.txt");
        for (int i = 0; i < grades.size(); i++) {
            gradeFile << grades[i].studentName << "," << grades[i].subject << ","
                      << grades[i].score << "," << grades[i].letterGrade << ","
                      << grades[i].comment << endl;
        }
    }

    void loadGrades() {
        ifstream gradeFile("grades.txt");
        string line;
        while (getline(gradeFile, line)) {
            stringstream ss(line);
            string studentName, subject, letterGrade, comment;
            float score;

            getline(ss, studentName, ',');
            getline(ss, subject, ',');
            ss >> score;
            ss.ignore(1);
            getline(ss, letterGrade, ',');
            getline(ss, comment);

            Grade g(studentName, subject, score, comment);
            grades.push_back(g);
        }
    }
};

void gradeManagement() {
    GradeManager gm;
    gm.loadGrades();

    int choice;
    do {
        cout << "\nGrade Management Menu:\n";
        cout << "1. Add Grade\n";
        cout << "2. View Grades\n";
        cout << "3. Generate Class Report\n";
        cout << "4. Exit and save\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                gm.addGradeToStudent();
                break;
            case 2:
                gm.viewGrades();
                break;
            case 3:
                gm.generateClassReport();
                break;
        }
    } while (choice != 4);
}

// ==================== FINANCIAL MANAGEMENT ====================
class Income {
public:
    int students_annual_fees = 1024, bus_fees_monthly = 500, Number_of_students = 600, Balance = 308200;

    void Income_Calculutor() {
        cout << " The total income from the annual fees of students is :" << students_annual_fees * Number_of_students << "\n";
        cout << " The total income from the monthly fees of students buses is :" << bus_fees_monthly * Number_of_students << "\n";
        cout << "The total income is" << (students_annual_fees * Number_of_students) + (bus_fees_monthly * Number_of_students) << "\n";
    }

    void Income_Calculutor(bool display) {
        if (display) {
            Income_Calculutor();
        }
    }
};

class Expenses {
public:
    int Teachers_salary = 6500, Workers_salary = 2000, Maintainence_Expenses, Others = 10000, Num_of_teachers = 9, Num_of_workers = 12;

    void Expenses_Calculutor() {
        cout << "The total wage of teachers is: " << Teachers_salary * Num_of_teachers << "\n";
        cout << "The partial wage of workers is: " << Num_of_workers * Workers_salary << "\n";
        cout << "Enter the maintenance cost: ";
        cin >> Maintainence_Expenses;
        cout << " The maintenance cost is: " << Maintainence_Expenses << "\n";
        cout << "Other expenses including the wage of management is: " << Others << "\n";
        cout << "The total is: " << (Teachers_salary * Num_of_teachers) + (Num_of_workers * Workers_salary) + Maintainence_Expenses + Others << "\n";
    }

    void Expenses_Calculutor(int maintenance) {
        Maintainence_Expenses = maintenance;
        cout << "The total wage of teachers is: " << Teachers_salary * Num_of_teachers << "\n";
        cout << "The partial wage of workers is: " << Num_of_workers * Workers_salary << "\n";
        cout << " The maintenance cost is: " << Maintainence_Expenses << "\n";
        cout << "Other expenses including the wage of management is: " << Others << "\n";
        cout << "The total is: " << (Teachers_salary * Num_of_teachers) + (Num_of_workers * Workers_salary) + Maintainence_Expenses + Others << "\n";
    }
};

void financeManagement() {
    Income A;
    Expenses B;
    int choice;
    do {
        cout << "\nFinancial Management:\n";
        cout << "1. Income Report\n";
        cout << "2. Expenses Report\n";
        cout << "3. Both Reports\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                A.Income_Calculutor(true);
                break;
            case 2: {
                int maintenance;
                cout << "Enter the maintenance cost: ";
                cin >> maintenance;
                B.Expenses_Calculutor(maintenance);
                break;
            }
            case 3:
                A.Income_Calculutor(true);
                B.Expenses_Calculutor();
                break;
        }
    } while(choice != 4);
}

// ==================== ATTENDANCE MANAGEMENT ====================
class Person {
public:
    string id;
    string name;
    Person() {
        id = "";
        name = "";
    }
    Person(string i, string n) {
        id = i;
        name = n;
    }
    void display() {
        cout << "ID: " << id << " | Name: " << name << "\n";
    }
    string getID() const {
        return id;
    }
    string getName() const {
        return name;
    }
};

class Student : public Person {
public:
    string className;
    Student(string id, string name, string cls) : Person(id, name), className(cls) {}
    string getClassName() const {
        return className;
    }
};

class AttendanceRecord {
public:
    string id, date, status, type, className;
    AttendanceRecord(string i, string d, string s, string t, string c) {
        id = i;
        date = d;
        status = s;
        type = t;
        className = c;
    }
    string toString() {
        return type + " | " + id + " | " + date + " | " + status + " | " + className;
    }
};

class Attendance {
public:
    vector<AttendanceRecord> records;

    void markAttendance(const Student& student, const string& status) {
        time_t now = time(0);
        tm* t = localtime(&now);
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%d/%m/%Y", t);
        string date(buffer);

        AttendanceRecord record(student.getID(), date, status, "student", student.getClassName());
        records.push_back(record);

        ofstream file("attendance.txt", ios::app);
        if (file.is_open()) {
            file << record.toString() << "\n";
            file.close();
            cout << "Attendance record saved to file.\n";
        }
        else {
            cout << "Error opening file.\n";
        }
    }

    void viewAttendanceHistory(const string& className) {
        cout << "Attendance History for class " << className << ":\n";
        ifstream file("attendance.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string type, id, date, status, cls;
            getline(ss, type, '|');
            getline(ss, id, '|');
            getline(ss, date, '|');
            getline(ss, status, '|');
            getline(ss, cls);

            id = trim(id);
            date = trim(date);
            status = trim(status);
            cls = trim(cls);
            type = trim(type);

            if (type == "student" && cls == className) {
                cout << id << " | " << date << " | " << status << "\n";
            }
        }
    }

    void monthlyReport(const string& id) {
        cout << "Monthly report for ID: " << id << "\n";
        ifstream file("attendance.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string type, sid, date, status, cls;
            getline(ss, type, '|');
            getline(ss, sid, '|');
            getline(ss, date, '|');
            getline(ss, status, '|');
            getline(ss, cls);

            sid = trim(sid);
            date = trim(date);
            status = trim(status);
            type = trim(type);

            if (type == "student" && sid == id) {
                cout << date << " | " << status << "\n";
            }
        }
    }

private:
    string trim(const string& str) {
        size_t first = str.find_first_not_of(" \t");
        if (string::npos == first)
            return "";
        size_t last = str.find_last_not_of(" \t");
        return str.substr(first, (last - first + 1));
    }
};

void attendanceManagement() {
    Attendance att;

    int attendChoice = 0;
    while (attendChoice != 4) {
        cout << "\nAttendance Management Menu:\n";
        cout << "1. Mark Student Attendance\n";
        cout << "2. View Class Attendance History\n";
        cout << "3. Generate Monthly Report\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> attendChoice;

        switch (attendChoice) {
        case 1: {
            if (allClasses.empty()) {
                cout << "No classes available.\n";
                break;
            }
            cout << "\nAvailable Classes:\n";
            for (size_t i = 0; i < allClasses.size(); i++) {
                cout << i + 1 << ". " << allClasses[i].name << "\n";
            }
            cout << "Choose class number: ";
            size_t classChoice;
            cin >> classChoice;
            if (classChoice < 1 || classChoice > allClasses.size()) {
                cout << "Invalid class choice.\n";
                break;
            }

            Class& selectedClass = allClasses[classChoice - 1];
            if (selectedClass.students.empty()) {
                cout << "No students in this class.\n";
                break;
            }
            cout << "\nMark attendance for students in " << selectedClass.name << ":\n";
            vector<Student> students;
            for (size_t i = 0; i < selectedClass.students.size(); i++) {
                string id = "ID" + to_string(i + 1) + selectedClass.students[i].substr(0, 3);
                students.emplace_back(id, selectedClass.students[i], selectedClass.name);
                cout << i + 1 << ". " << selectedClass.students[i] << " (ID: " << id << ")\n";
            }
            cout << "Choose student number: ";
            size_t studentChoice;
            cin >> studentChoice;
            if (studentChoice < 1 || studentChoice > students.size()) {
                cout << "Invalid student choice.\n";
                break;
            }

            cout << "Enter status (Present/Absent): ";
            string status;
            cin >> status;
            att.markAttendance(students[studentChoice - 1], status);
            break;
        }
        case 2: {
            string cls;
            cout << "\nEnter class name: ";
            cin >> cls;
            att.viewAttendanceHistory(cls);
            break;
        }
        case 3: {
            string id;
            cout << "\nEnter person ID: ";
            cin >> id;
            att.monthlyReport(id);
            break;
        }
        }
    }
}

// ==================== LESSON MANAGEMENT ====================
struct Lesson {
    string level;
    string lesson;
    string mark;
};

struct Homework {
    string level;
    string pages;
    string deadline;
};

void saveLessons(const vector<Lesson>& lessons, const string& className) {
    ofstream lessonFile("lessons_" + className + ".txt");
    for (const Lesson& lesson : lessons) {
        lessonFile << lesson.level << "," << lesson.lesson << "," << lesson.mark << endl;
    }
}

void loadLessons(vector<Lesson>& lessons, const string& className) {
    ifstream lessonFile("lessons_" + className + ".txt");
    string line;
    while (getline(lessonFile, line)) {
        stringstream ss(line);
        Lesson lesson;
        getline(ss, lesson.level, ',');
        getline(ss, lesson.lesson, ',');
        getline(ss, lesson.mark);
        lessons.push_back(lesson);
    }
}

void saveHomework(const vector<Homework>& homework, const string& className) {
    ofstream homeworkFile("homework_" + className + ".txt");
    for (const Homework& hw : homework) {
        homeworkFile << hw.level << "," << hw.pages << "," << hw.deadline << endl;
    }
}

void loadHomework(vector<Homework>& homework, const string& className) {
    ifstream homeworkFile("homework_" + className + ".txt");
    string line;
    while (getline(homeworkFile, line)) {
        stringstream ss(line);
        Homework hw;
        getline(ss, hw.level, ',');
        getline(ss, hw.pages, ',');
        getline(ss, hw.deadline);
        homework.push_back(hw);
    }
}

void lessons() {
    int choice;
    string arr[] = {"Add Lessons", "Assign Assignment", "Mark Lessons", "Exit"};

    do {
        cout << "\nLesson Management Menu:\n";
        for (int i = 0; i < 4; i++) {
            cout << i + 1 << ". " << arr[i] << endl;
        }
        cout << "Choose an option (1-4): ";
        cin >> choice;
        cin.ignore(); 

        if (choice < 1 || choice > 4) {
            cout << "Invalid choice! Please try again.\n";
            continue;
        }

        if (choice == 4) {
            cout << "Returning to main menu...\n";
            break; // Exit to main menu
        }

        if (allClasses.empty()) {
            cout << "No classes available.\n";
            continue;
        }

 
        cout << "\nAvailable Classes:\n";
        for (size_t i = 0; i < allClasses.size(); i++) {
            cout << i + 1 << ". " << allClasses[i].name << "\n";
        }
        cout << "Choose class number: ";
        size_t classChoice;
        cin >> classChoice;
        cin.ignore(); 

        if (classChoice < 1 || classChoice > allClasses.size()) {
            cout << "Invalid class choice.\n";
            continue;
        }
        string selectedClassName = allClasses[classChoice - 1].name;

        vector<Lesson> lessons;
        vector<Homework> homework;
        loadLessons(lessons, selectedClassName);
        loadHomework(homework, selectedClassName);

        if (choice == 1) {
            cout << "Existing lessons for class " << selectedClassName << ":\n";
            if (lessons.empty()) {
                cout << "No lessons available.\n";
            } else {
                cout << "Level\t\t\tLessons\t\tMark\n";
                for (const auto& lesson : lessons) {
                    cout << lesson.level << "\t\t\t" << lesson.lesson << "\t\t" << lesson.mark << endl;
                }
            }
            cout << "Do you want to add a new lesson (yes/no)?\n==>";
            string answer;
            cin >> answer;
            cin.ignore();

            if (answer == "yes" || answer == "YES") {
                Lesson newLesson;
                cout << "Enter the level:\n==>";
                getline(cin, newLesson.level);
                cout << "Enter new lesson:\n==>";
                getline(cin, newLesson.lesson);
                newLesson.mark = "not yet";
                lessons.push_back(newLesson);
                saveLessons(lessons, selectedClassName);
                cout << "Lessons now are:\n";
                cout << "Level\t\t\tLessons\t\tMark\n";
                for (const auto& lesson : lessons) {
                    cout << lesson.level << "\t\t\t" << lesson.lesson << "\t\t" << lesson.mark << endl;
                }
            } else {
                cout << "No new lesson added.\n";
            }
        }
        else if (choice == 2) {
            cout << "The homework for class " << selectedClassName << ":\n";
            if (homework.empty()) {
                cout << "No homework available.\n";
            } else {
                cout << "Level\t\t\tHomework\t\tDeadline\n";
                for (const auto& hw : homework) {
                    cout << hw.level << "\t\t\t" << hw.pages << "\t\t" << hw.deadline << endl;
                }
            }
            cout << "Do you want to edit the homework (yes/no)?\n==>";
            string ch1;
            cin >> ch1;
            cin.ignore();

            if (ch1 == "yes" || ch1 == "YES") {
                cout << "Choose between add, remove, or change:\n==>";
                string ch2;
                cin >> ch2;
                cin.ignore();

                if (ch2 == "add" || ch2 == "Add" || ch2 == "ADD") {
                    Homework newHw;
                    cout << "Enter the level of the homework:\n==>";
                    getline(cin, newHw.level);
                    cout << "Enter the pages of the homework (from/to):\n==>";
                    getline(cin, newHw.pages);
                    cout << "Enter the deadline (day/month) :\n==>";
                    getline(cin, newHw.deadline);
                    homework.push_back(newHw);
                    saveHomework(homework, selectedClassName);
                    cout << "The homework now is:\n";
                    cout << "Level\t\t\tHomework\t\tDeadline\n";
                    for (const auto& hw : homework) {
                        cout << hw.level << "\t\t\t" << hw.pages << "\t\t" << hw.deadline << endl;
                    }
                }
                else if (ch2 == "remove" || ch2 == "Remove" || ch2 == "REMOVE") {
                    if (homework.empty()) {
                        cout << "No homework to remove.\n";
                        continue;
                    }
                    cout << "Choose the number of the homework to remove (1 to " << homework.size() << "):\n==>";
                    int index;
                    cin >> index;
                    cin.ignore();
                    if (index >= 1 && index <= (int)homework.size()) {
                        homework.erase(homework.begin() + index - 1);
                        saveHomework(homework, selectedClassName);
                        cout << "Homework removed successfully!\n";
                    } else {
                        cout << "Invalid number, please try again.\n";
                    }
                    cout << "The homework now is:\n";
                    if (homework.empty()) {
                        cout << "No homework available.\n";
                    } else {
                        cout << "Level\t\t\tHomework\t\tDeadline\n";
                        for (const auto& hw : homework) {
                            cout << hw.level << "\t\t\t" << hw.pages << "\t\t" << hw.deadline << endl;
                        }
                    }
                }
                else if (ch2 == "change" || ch2 == "Change" || ch2 == "CHANGE") {
                    if (homework.empty()) {
                        cout << "No homework to change.\n";
                        continue;
                    }
                    cout << "Choose what to change (deadline, hw, or level):\n==>";
                    string ch4;
                    cin >> ch4;
                    cin.ignore();

                    cout << "Enter the index of the homework to change (1 to " << homework.size() << "):\n==>";
                    int index;
                    cin >> index;
                    cin.ignore();
                    if (index < 1 || index > (int)homework.size()) {
                        cout << "Invalid index.\n";
                        continue;
                    }

                    if (ch4 == "deadline" || ch4 == "Deadline" || ch4 == "DEADLINE") {
                        cout << "Current deadline: " << homework[index - 1].deadline << endl;
                        cout << "Enter new deadline:\n==>";
                        string newDeadline;
                        getline(cin, newDeadline);
                        homework[index - 1].deadline = newDeadline;
                        saveHomework(homework, selectedClassName);
                        cout << "Deadline updated successfully.\n";
                    }
                    else if (ch4 == "hw" || ch4 == "Hw" || ch4 == "HW") {
                        cout << "Current homework: " << homework[index - 1].pages << endl;
                        cout << "Enter new homework pages (from\\to):\n==>";
                        string newPages;
                        getline(cin, newPages);
                        homework[index - 1].pages = newPages;
                        saveHomework(homework, selectedClassName);
                        cout << "Homework updated successfully.\n";
                    }
                    else if (ch4 == "level" || ch4 == "LEVEL" || ch4 == "Level") {
                        cout << "Current level: " << homework[index - 1].level << endl;
                        cout << "Enter the new level:\n==>";
                        string newLevel;
                        getline(cin, newLevel);
                        homework[index - 1].level = newLevel;
                        saveHomework(homework, selectedClassName);
                        cout << "Level updated successfully.\n";
                    }
                    else {
                        cout << "Invalid choice. Please select 'deadline', 'hw', or 'level'.\n";
                    }
                    cout << "The homework now is:\n";
                    if (homework.empty()) {
                        cout << "No homework available.\n";
                    } else {
                        cout << "Level\t\t\tHomework\t\tDeadline\n";
                        for (const auto& hw : homework) {
                            cout << hw.level << "\t\t\t" << hw.pages << "\t\t" << hw.deadline << endl;
                        }
                    }
                }
            }
        }
        else if (choice == 3) {
            cout << "The lessons for class " << selectedClassName << ":\n";
            if (lessons.empty()) {
                cout << "No lessons available.\n";
            } else {
                cout << "Level\t\t\tLesson\t\tMark\n";
                for (const auto& lesson : lessons) {
                    cout << lesson.level << "\t\t\t" << lesson.lesson << "\t\t" << lesson.mark << endl;
                }
            }
            cout << "Do you want to mark a lesson (yes/no)?\n==>";
            string answer;
            cin >> answer;
            cin.ignore();

            if (answer == "yes" || answer == "Yes" || answer == "YES") {
                if (lessons.empty()) {
                    cout << "No lessons to mark.\n";
                    continue;
                }
                cout << "Enter the index of the lesson to mark (1 to " << lessons.size() << "):\n==>";
                int index;
                cin >> index;
                cin.ignore();
                if (index >= 1 && index <= (int)lessons.size()) {
                    cout << "What is the mark?\n==>";
                    string mark;
                    getline(cin, mark);
                    lessons[index - 1].mark = mark;
                    saveLessons(lessons, selectedClassName);
                    cout << "The new mark list is:\n";
                    cout << "Level\t\t\tLesson\t\tMark\n";
                    for (const auto& lesson : lessons) {
                        cout << lesson.level << "\t\t\t" << lesson.lesson << "\t\t" << lesson.mark << endl;
                    }
                } else {
                    cout << "Invalid index. Please try again.\n";
                }
            }
        }
    } while (true);
}

// ==================== MAIN INTEGRATION ====================
int main() {
    AuthSystem auth;
    string username, password;

    cout << "School Management System Login\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (!auth.login(username, password)) {
        cout << "Invalid login!\n";
        return 0;
    }

    string role = auth.getRole(username);
    string displayName = auth.getDisplayName(username);
    cout << "Welcome, " << displayName << " (" << role << ")\n";

    loadData(auth);  

    int choice;
    do {
        cout << "\nMain Menu:\n";
        cout << "1. Class Management\n";
        cout << "2. Grade Management\n";
        cout << "3. Financial Management\n";
        cout << "4. Attendance Management\n";
        cout << "5. Lesson Management\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if ((choice == 1 || choice == 3) && role != "manager") {
            cout << "Access denied - manager role required\n";
            continue;
        }

        switch(choice) {
            case 1:
                classManagement(auth);
                break;
            case 2:
                gradeManagement();
                break;
            case 3:
                financeManagement();
                break;
            case 4:
                attendanceManagement();
                break;
            case 5:
                lessons();
                break;
        }
    } while(choice != 6);

    cout << "Goodbye!\n";
    return 0;
}
