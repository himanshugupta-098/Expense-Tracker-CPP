#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;
class User
{
private:
    double income;

public:
    void setincome()
    {
        cout << "Enter Income : ";

        while (!(cin >> income) || income <= 0)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Income must be Positive. Enter Again : ";
        }
        ofstream fout("Income.txt");
        fout << income;
        fout.close();
    }
    double getincome()
    {
        ifstream fin("Income.txt");

        if (fin >> income)
        {
            return income;
        }
        return 0;
    }
};
class Expense
{
private:
    double expense = 0;
    int id;
    string category, date;

public:
    void adddata()
    {
        cout << "Enter Expense Amount : ";

        while (!(cin >> expense) || expense <= 0)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Expense Must be Positive. Enter Again : ";
        }

        cout << "Enter category : ";
        cin >> category;
        while (true)
        {
            cout << "Enter Date (DD-MM-YYYY) : ";
            cin >> date;

            bool valid = true;

            if (date.length() != 10 || date[2] != '-' || date[5] != '-')
                valid = false;

            for (int i = 0; i < date.length(); i++)
            {
                if (i == 2 || i == 5)
                    continue;

                if (!isdigit(date[i]))
                {
                    valid = false;
                    break;
                }
            }

            if (valid)
            {
                int day = stoi(date.substr(0, 2));
                int month = stoi(date.substr(3, 2));

                if (day < 1 || day > 31)
                    valid = false;

                if (month < 1 || month > 12)
                    valid = false;
            }

            if (valid)
                break;

            cout << "Invalid Date! Try Again.\n";
        }
    }

    void setid(int id)
    {
        this->id = id;
    }

    int getid() const { return id; }
    string getdate() const { return date; }
    string getcategory() const { return category; }
    double getexpenses() const { return expense; }
    void showdata() const
    {
        cout << "Expense Amount : " << expense << endl;
        cout << "category : " << category << endl;
        cout << "Date : " << date << endl;
        cout << "Expense ID : " << id << endl;
        cout << "-----------------------------\n\n";
    }

    void savefile() const
    {
        ofstream fout("Expense.txt", ios::app);
        fout << id << " " << category << " " << date << " " << expense << endl;
        fout.close();
    }
    void loaddata(int id, string category, string date, double expense)
    {
        this->id = id;
        this->category = category;
        this->date = date;
        this->expense = expense;
    }
};
void updatefile(const vector<Expense> &Exp)
{
    ofstream fout("Expense.txt");
    for (const Expense &e : Exp)
    {
        fout << e.getid() << " " << e.getcategory() << " " << e.getdate() << " " << e.getexpenses() << endl;
    }
    fout.close();
}

int main()
{
    int choice, maxid = 0, id = 1, deleteid, searchid, fileid;
    string permission, filecategory, filedate;
    vector<Expense> Exp;
    User u;
    ifstream fin("Expense.txt");
    double fileexpense;
    if (!fin)
    {
        cout << "No previous expense data found. Starting fresh...\n";
        
    }
    else
    {
        while (fin >> fileid >> filecategory >> filedate >> fileexpense)
        {
            Expense E;
            E.loaddata(fileid, filecategory, filedate, fileexpense);
            Exp.push_back(E);
            if (fileid > maxid)
            {
                maxid = fileid;
            }
        }
        fin.close();
    }
    id = maxid + 1;

    do
    {
        cout << "----Expense Tracker----\n";
        cout << "1. Add Expense\n2. View Expenses\n3. Delete Expense\n4. Search Expense\n5. Set income\n6. Budget Status\n7. Monthly Report\n8. Exit\n";
        cout << "Enter choice : ";

        while (!(cin >> choice) || (choice < 1 || choice > 8))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "please enter valid choice : ";
        }

        switch (choice)
        {
        case 1:
        {
            Expense E;
            cout << "\n----Add Expense----\n";
            E.adddata();
            E.setid(id++);
            Exp.push_back(E);
            E.savefile();

            cout << "Stored! Size = " << Exp.size() << endl;
            break;
        }
        case 2:
        {
            double totalexpense = 0;
            cout << "\n-----------View Expense-----------\n";
            cout << "\n-----------------------------\n";
            if (Exp.empty())
            {
                cout << "No Expenses Found!\n";
                break;
            }

            for (const Expense &e : Exp)
            {
                e.showdata();
                totalexpense += e.getexpenses();
            }
            cout << "Total Expense = " << totalexpense << endl;
            break;
        }
        case 3:
        {
            if (Exp.empty())
            {

                cout << "\nNo Expenses Available...\n";
                break;
            }
            bool found = false;
            cout << "Enter Expense ID to delete : ";

            while (!(cin >> deleteid) || deleteid <= 0)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Enter Correct Delete Id : ";
            }
            for (auto i = Exp.begin(); i != Exp.end(); i++)
            {
                if (i->getid() == deleteid)
                {
                    found = true;
                    Exp.erase(i);
                    updatefile(Exp);
                    cout << "\nExpense Deleted Successfuly!\n";
                    break;
                }
            }
            if (!found)
            {

                cout << "\nExpense Not found!\n";
            }
        }
        break;
        case 4:
        {
            if (Exp.empty())
            {

                cout << "\nNo Expenses Available...\n";
                break;
            }
            bool found = false;
            cout << "Enter Expense ID to Search : ";
            while (!(cin >> searchid) || searchid <= 0)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Enter Correct Search Id : ";
            }

            for (auto i = Exp.begin(); i != Exp.end(); i++)
            {
                if (i->getid() == searchid)
                {
                    found = true;
                    cout << "\n-----------------------------\n";
                    i->showdata();
                    break;
                }
            }
            if (!found)
            {
                cout << "\nNo Expense Found...\n";
            }

            break;
        }
        case 5:
        {
            u.setincome();
            break;
        }
        case 6:
        {

            double totalexpense = 0, income = u.getincome();
            for (const Expense &e : Exp)
            {
                totalexpense += e.getexpenses();
            }
            double remaining = income - totalexpense;
            cout << "Income : " << income << endl;
            cout << "Total Expenses : " << totalexpense << endl;
            cout << "Remaining : " << remaining << endl;
            if (remaining < 0)
            {
                cout << "Warning: You have exceeded your income by " << -remaining << endl;
            }
            break;
        }
        case 7:
        {
            string month, year, monthnumber;
            double monthlytotal = 0;
            cout << "Enter Month : ";
            cin >> month;
            cout << "Enter Year : ";
            cin >> year;
            for (char &ch : month)
            {
                ch = tolower(ch);
            }
            vector<string> months = {"january", "february", "march", "april", "may", "june",
                                     "july", "august", "september", "october", "november", "december"};
            for (int i = 0; i < months.size(); i++)
            {

                if (months[i] == month)
                {
                    if (i + 1 < 10)
                    {
                        monthnumber = "0" + to_string(i + 1);
                    }
                    else
                    {
                        monthnumber = to_string(i + 1);
                    }
                    break;
                }
            }

            if (monthnumber.empty())
            {
                cout << "\nInvalid month!\n";
                break;
            }
            for (const Expense &e : Exp)
            {
                if ((e.getdate().substr(3, 2) == monthnumber) && (e.getdate().substr(6, 4) == year))
                {
                    monthlytotal += e.getexpenses();
                }
            }
            month[0] = toupper(month[0]);
            cout << "\n--------Monthly Report--------\n";
            cout << month << " " << year << endl;
            cout << "Total Expense : " << monthlytotal;
            cout << "\n------------------------------\n";

            break;
        }
        case 8:
            cout << "Exitting......\n";
            return 0;
        }
        cout << "Do you want to continue(Y/N) : ";
        cin >> permission;

    } while (permission != "n" && permission != "N");
    cout << "Exitting......\n";
}
