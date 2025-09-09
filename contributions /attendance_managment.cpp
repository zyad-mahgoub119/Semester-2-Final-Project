/*
Attendance Management Module
This C++ module provides a system for tracking and managing student attendance within a school management application.
Designed for seamless integration, it efficiently handles the recording, viewing, and reporting of attendance data. 
Key features include: Attendance Marking for students by class, saving records to a local text file (attendance.txt) to ensure Data Persistence, the ability to View Attendance 
History for any specific class, and a function to generate a Monthly Report for any student, showing their attendance status for the last 30 days.
This code was contributed by Seif El-Deen Mohamed Hussein (seifmohamed1412)
*/

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
