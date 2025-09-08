/*
This shit provides a comprehensive system for managing student grades. 
Designed for seamless integration into a larger school management application, it simplifies the process of recording, calculating, and reporting academic performance. 
The system automatically converts numerical scores into letter grades and saves all data to a local text file (grades.txt) for easy access and persistence. 
Its key features include the ability to add new grades for students, view a student's grades for all subjects, and generate a class report to provide a full overview of academic standing.
This contribution has been made by Rodaina Gamal Moustafa
*/

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
