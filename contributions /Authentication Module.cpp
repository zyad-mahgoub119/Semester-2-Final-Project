/*

This code provides a simple, console-based authentication system for a school management application. It handles user login, role-based access control, and user information retrieval.
Role-Based Access: Defines distinct Manager and Teacher roles with different permissions.
User Management: Includes predefined accounts for multiple managers and teachers.
Secure Login: Authenticates users by verifying their username and password.
User Information Retrieval: Functions to retrieve a user's role and display name after a successful login.
Teacher List: Provides a utility function to get a list of all teachers in the system.
This contributions was made by Zyad Akram Mahgoub

*/




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
