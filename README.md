School Management System
This repository contains the source code for a console-based School Management System developed in C++. The program is designed to assist teachers and school management in performing various administrative tasks efficiently and to save time and effort. It features a simple, user-friendly interface and saves all data to local text files for easy persistence.

Features
The system offers a range of functionalities tailored to different user roles. The program is divided into distinct modules, each handling a specific aspect of school administration.

Authentication and User Roles: The system requires a username and password for access. It supports two primary user roles:

Manager: Has access to all features, including class and financial management.

Teacher: Has access to features relevant to their daily tasks, such as grading, attendance, and lesson management.

Class Management: (Manager-only)

Add Class: Create new classes and assign a teacher to them from a list of available teachers.

Add Student: Add new students to an existing class.

View All: Display a detailed list of all classes, their assigned teachers, and the students enrolled in each.

Grade Management: (Teacher & Manager)

Add Grade: Enter student grades for a specific subject. The program automatically calculates and assigns a letter grade (A, B, C, D, F) and allows for an optional comment.

View Grades: Look up and view all grades for a specific student.

Generate Class Report: Create a detailed report for a chosen class, listing all students and their respective grades.

Financial Management: (Manager-only)

Income Report: Calculate and display the total income from various sources, such as student annual fees and bus fees.

Expenses Report: Calculate and display the total expenses, including teacher and worker salaries, maintenance costs, and other administrative expenses.

Attendance Management: (Teacher & Manager)

Mark Attendance: Mark a student's attendance as "Present" or "Absent" for the current day.

View History: Access and view the complete attendance history for a specific class.

Monthly Report: Generate a report showing a student's attendance for the last 30 days.

Lesson Management: (Teacher & Manager)

Add Lessons: Add new lessons to a specific class.

Assign Assignments: Assign homework for a lesson, including the pages and a deadline. This module also allows for editing or removing existing homework assignments.

Mark Lessons: Update the status of a lesson by providing a "mark" or comment.

How to Compile and Run
This project is a single C++ source file that can be compiled and run using a standard C++ compiler like g++.

Save the Code: Save the provided code into a file named school_management_system.cpp.

Compile: Open your terminal or command prompt and navigate to the directory where you saved the file. Use the following command to compile the program:

g++ school_management_system.cpp -o sms

This command compiles the source code and creates an executable file named sms (or sms.exe on Windows).

Run: Execute the compiled program from the terminal:

./sms

The program will prompt you to log in before providing access to the main menu.

File Structure
The program uses plain text files to store data. These files are created in the same directory as the executable.

classes.txt: Stores the names of all classes and their assigned teachers.

students.txt: Stores the names of students and their associated classes.

grades.txt: Stores student grades, including their name, subject, score, letter grade, and comments.

attendance.txt: Records the attendance history, including student IDs, dates, and attendance status.

lessons_<className>.txt: A separate file is created for each class to store its lessons.

homework_<className>.txt: A separate file is created for each class to store its homework assignments.

Usage
Upon starting the program, you will be prompted to log in.

Login Credentials
The following default accounts are available:

Manager: admin1, admin2

Teacher: teacher1, teacher2, teacher3

All passwords are manger123, manger456, teacher123, teacher456, and teacher789 respectively.

After a successful login, the main menu will appear, with options based on your user role. Simply enter the number corresponding to the function you wish to use.

Future Enhancements
The current system provides a solid foundation for school management. Here are some potential improvements that could be explored:

Database Integration: Replace local text files with a more robust database system (like SQL or Firestore) for better data management, security, and scalability.

Graphical User Interface (GUI): Develop a more user-friendly interface instead of the console-based UI.

Additional User Roles: Add more roles like "Student" to allow students to check their own grades and attendance.

Error Handling: Implement more comprehensive error handling to gracefully handle invalid inputs and unexpected file issues.

Credits
This project was created by the following students:

Abdelrahman Sapry Abd El-Aziz

Zyad Akram Mahgoub

Seif El-Deen Mohamed Hussein

Rodaina Gamal Moustafa

Mohamed Ehab Sayed

Ziad Ahmed Mohamed
