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
    {   cout << "\n-----------------------------\n\n";
        cout << "Expense Amount : Rs. " << expense << endl;
        cout << "category : " << category << endl;
        cout << "Date : " << date << endl;
        cout << "Expense ID : " << id << endl;
        cout << "\n-----------------------------\n\n";
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

    while(true)
    {   system("cls");
cout << "\n==================================================\n";
cout << "                 EXPENSE TRACKER                  \n";
cout << "==================================================\n";
cout << " 1. Add Expense\n";
cout << " 2. View Expenses\n";
cout << " 3. Delete Expense\n";
cout << " 4. Search Expense\n";
cout << " 5. Set Income\n";
cout << " 6. Budget Status\n";
cout << " 7. Monthly Report\n";
cout << " 8. Exit\n";
cout << "==================================================\n";
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
            cout<<"\n========================================\n";
            cout << "           ADD EXPENSE                \n";
            cout<<"========================================\n";
            E.adddata();
            E.setid(id++);
            Exp.push_back(E);
            E.savefile();

            cout << "\nStored! Size = " << Exp.size() << endl;
            cout << "\n==================================================\n";
            cout << "        EXPENSE ADDED SUCCESSFULLY              \n";
            cout << "==================================================\n";
            
            break;
        }
        case 2:
        {
            double totalexpense = 0;
            cout<<"\n========================================\n";
            cout << "          View Expense          \n";
            cout<<"========================================\n";
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
            cout<<"========================================\n\n";
            cout << "Total Expense = " << totalexpense << endl<<endl;
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
            cout<<"========================================\n\n";
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
                    cout << "\n==================================================\n";
                    cout << "       EXPENSE DELETED SUCCESSFULLY             \n";
                    cout << "==================================================\n";
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
            cout << "\n==================================================\n";
            cout << "                  SEARCH RESULT                   \n";
            cout << "==================================================\n";

            for (auto i = Exp.begin(); i != Exp.end(); i++)
            {
                if (i->getid() == searchid)
                {
                    found = true;
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
            cout << "\n==================================================\n";
            cout << "                  BUDGET STATUS                   \n";
            cout << "==================================================\n";

            double totalexpense = 0, income = u.getincome();
            for (const Expense &e : Exp)
            {
                totalexpense += e.getexpenses();
            }
            double remaining = income - totalexpense;
            cout << " Monthly Income   : Rs. " << income << endl;
            cout << " Total Expenses   : Rs. " << totalexpense << endl;
            cout << " Remaining Amount : Rs. " << remaining << endl;
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
           cout << "\n==================================================\n";
           cout << "                 MONTHLY REPORT                  \n";
           cout << "==================================================\n";
            cout << month << " " << year << endl;
            cout << "Total Expense : Rs. " << monthlytotal << endl;
            cout << "\n------------------------------\n";

            break;
        }
        case 8:
            cout << "Exitting......\n";
            return 0;
        }
        cout << "\nPress Enter to continue...";
        cin.ignore(10000, '\n');
        cin.get();

    } 
    cout << "Exitting......\n";
}
