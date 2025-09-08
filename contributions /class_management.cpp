/*

This C++ code module implements a **class management system** that allows users to create academic classes, assign teachers to them, enroll students, and persistently store this information in text files.

It provides a console-based menu interface for performing these operations and integrates with an external authentication system to validate that only registered teachers can be assigned to classes. 

The system loads existing data on startup and saves any changes upon exit, maintaining a record of classes, their assigned teachers, and student rosters between sessions.

This contribution was been made by Ziad Ahmed Mohamed El-Bahy (elbahy999)

*/


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
