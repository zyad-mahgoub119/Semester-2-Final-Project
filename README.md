# School Management System

A comprehensive C++ application designed to help teachers and school administrators manage various academic tasks efficiently.

## Overview

This School Management System provides a centralized platform for handling class organization, grading, financial management, attendance tracking, and lesson planning. The system features role-based access control with separate interfaces for teachers and management staff.

## Features

### 1. Authentication System
- Secure login with username and password
- Role-based access (Manager vs. Teacher)
- Pre-configured accounts for administrators and teachers

### 2. Class Management
- Create and manage classes
- Assign teachers to classes
- Add and view students in each class
- Persistent data storage

### 3. Grade Management
- Record student grades with automatic letter grade calculation (A-F)
- Add comments for each grade
- View individual student grades
- Generate comprehensive class reports

### 4. Financial Management
- Income tracking (student fees, bus fees)
- Expense management (salaries, maintenance costs)
- Financial reporting capabilities

### 5. Attendance System
- Mark student attendance (Present/Absent)
- View class attendance history
- Generate monthly attendance reports
- Uses actual date tracking

### 6. Lesson Management
- Create and manage lessons
- Assign homework with deadlines
- Mark lesson completion status
- Organize content by difficulty levels

## Technical Implementation

Built with C++ using object-oriented programming principles. Data is persisted across sessions using text files for:
- Class information (`classes.txt`)
- Student records (`students.txt`)
- Grade data (`grades.txt`)
- Attendance records (`attendance.txt`)
- Lesson plans (class-specific files)

## Usage

1. Login with provided credentials (managers: admin1/admin2, teachers: teacher1/teacher2/teacher3)
2. Access features based on your role:
   - Managers: Full access to all modules
   - Teachers: Restricted access (no class or financial management)
3. Navigate through the menu system to perform academic tasks

## Development

This project was created by a dedicated student who recognized the need for efficient school management tools. The system prioritizes user-friendly interfaces while maintaining comprehensive functionality for educational institutions.

## Future Enhancements

Potential improvements could include:
- Database integration for better data management
- Graphical user interface
- Additional reporting features
- Parent portal access
- Mobile application support
