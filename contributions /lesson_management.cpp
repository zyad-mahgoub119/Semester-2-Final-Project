/*
the code provides functionality to add lessons, assign homework assignments, and mark lesson completion status. 
The system stores data in text files (lessons and homework) specific to each class, allowing teachers to track curriculum progress, assign tasks with deadlines, and record student performance marks. 
The menu-driven interface supports operations like adding/removing assignments, modifying deadlines, and updating lesson status while maintaining persistent storage through file handling operations.
This contribution was been made by Mohamed Ehab Sayed
*/




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
