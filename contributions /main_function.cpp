/*
This code snippet represents the core **main function** of the School Management System.
It serves as the program's central control hub, managing the entire user experience from start to finish.
Its primary responsibilities include: handling the initial **user login** and **authentication**, presenting the user with the main menu, and directing them to the various management modules based on their input.
The main loop also enforces **role-based access control**, ensuring that features like Class Management and Financial Management are only accessible to users with the 'manager' role.
Finally, it provides a clean exit point for the application.

This contribution has been made by Zyad Akram Mahgoub (zyad-mahgoub119)
*/




// ==================== MAIN INTEGRATION ===================
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
