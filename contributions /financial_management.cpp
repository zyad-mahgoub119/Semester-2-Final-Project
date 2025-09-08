/* 
The code uses two classes, Income and Expenses, to handle financial calculations. 
The Income class calculates total earnings from annual student fees and monthly bus fees. The Expenses class tallies up costs, 
including salaries for teachers and workers, and other expenses like maintenance and management wages. 
The financeManagement function provides a user-friendly menu to access these reports, allowing users to view income, expenses, or both, and input variable costs like maintenance. 
This structure uses object-oriented programming to keep the financial data organized and easy to report.
This contribution was made by Abdelrahman Sapry Abd El-Aziz 
*/
  
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
