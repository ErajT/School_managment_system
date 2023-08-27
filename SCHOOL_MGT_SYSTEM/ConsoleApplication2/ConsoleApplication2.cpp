#include<iostream>
#include<string>
#include <vector>
#include <conio.h>
#include <map>
#include<thread>
#include"sqlite\sqlite3.h"

//using namespace std;

using namespace std;

//using namespace std;



// #include<D:\OOP PPROJECT SMS\Admin - Copy.h>
using namespace std;

namespace management {
    string upper(string text) {
        int count = 0;
        for (char c : text) {
            text[count] = toupper(c);
            ++count;
        }
        return text;
    }
    string lower(string text) {
        int count = 0;
        for (char c : text) {
            text[count] = tolower(c);
            ++count;
        }
        return text;
    }

    class Database {
    private:
        sqlite3* db;
    public:
        Database() {
            sqlite3_initialize();
        }
        Database(const string& filename) {
            sqlite3_initialize();
            int result = sqlite3_open(filename.c_str(), &db);
            if (result != SQLITE_OK) {
                //cout << "ERROR OPENING DATABASE! " << endl;
            }
            //else {
                //cout << "\t\t\t\t************ SCHOOL \t MANAGEMENT \t SYSTEM ************" << endl;
            //}
        }
        ~Database() {
            sqlite3_close(db);
        }
        bool executeQuery(const string& query) {
            char* errMsg = nullptr;
            int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
            if (result != SQLITE_OK) {
                cerr << "Error executing Query: " << errMsg << endl;
                sqlite3_free(errMsg);
                //cout << result<<endl;
                return false;


            }
            else {
                cout << "Query executed successfully! " << endl;
            }
            return true;
        }
    };


    class NoticeBoard {
    private:
        string title;
        string content;

    public:
        NoticeBoard(const string& title, const string& content) : title(title), content(content) {
        }


        // void setContent(const string& newContent);

        // void add(vector<NoticeBoard>& noticeList);
        // void update(vector<NoticeBoard>& noticeList);
        // void deleteNotice(vector<NoticeBoard>& noticeList);
        // void view(const vector<NoticeBoard>& noticeList) const;

        string getTitle() {
            return title;
        }

        string getContent() const {
            return content;
        }

        void setTitle(const string& newTitle) {
            title = newTitle;
        }

        void setContent(const string& newContent) {
            content = newContent;
        }


        void update(vector<NoticeBoard>& noticeList) {
            cout << "Enter the title of the notice you want to update: ";
            string oldTitle;
            cin.ignore();
            getline(cin, oldTitle);

            for (NoticeBoard& notice : noticeList) {
                if (notice.title == oldTitle) {
                    cout << "Enter the new title of the notice: ";
                    getline(cin, notice.title);
                    cout << "Enter the new content of the notice: ";
                    getline(cin, notice.content);
                    cout << "Successfully updated" << endl;
                    return;
                }
            }

            cout << "Notice with the given title not found" << endl;
        }

        void deleteNotice(vector<NoticeBoard>& noticeList) {
            cout << "Enter the title of the notice you want to delete: ";
            string title;
            cin.ignore();
            getline(cin, title);

            for (int i = 0; i < noticeList.size(); i++) {
                if (noticeList[i].title == title) {
                    noticeList.erase(noticeList.begin() + i);
                    cout << "Successfully deleted" << endl;
                    return;
                }
            }

            cout << "Notice with the given title not found" << endl;
        }

        void view(const vector<NoticeBoard>& noticeList) const {
            for (const NoticeBoard& notice : noticeList) {
                cout << "Title: " << notice.title << endl;
                cout << "Content: " << notice.content << endl;
                cout << endl;
            }
        }
    };

    class Student {
    private:
        string rollNumber;
        string name;
        string phoneNumber;
        string grade;
        char section;
        int fees;
        bool feesPaid;
        int attendance;
        string address;
        map <string, int> marksMap;
        bool resultStatus = false;

    public:
        Student(){}
        Student(string rollNumber, const string& name, const string& phoneNumber, const string& grade,
            int fees, bool feesPaid, int attendance, const string& address, char section)
            : rollNumber(rollNumber), name(name), phoneNumber(phoneNumber), grade(grade),
            fees(fees), feesPaid(feesPaid), attendance(attendance), address(address) {
            this->section = toupper(section);
        }
        bool isResult() {
            return resultStatus;
        }
        string getRollNumber() const {
            return rollNumber;
        }

        string getName() const {
            return name;
        }

        string getPhoneNumber() const {
            return phoneNumber;
        }

        string getGrade() const {
            return grade;
        }

        int getFees() const {
            return fees;
        }

        bool getFeesPaid() const {
            return feesPaid;
        }

        int getAttendance() const {
            return attendance;
        }

        string getAddress() const {
            return address;
        }
        char getSec() {
            return section;
        }

        void setRollNumber(string rollNumber) {
            this->rollNumber = rollNumber;
        }

        void setName(const string& name) {
            this->name = name;
        }

        void setPhoneNumber(const string& phoneNumber) {
            this->phoneNumber = phoneNumber;
        }

        void setGrade(const string& grade) {
            this->grade = grade;
        }

        void setFees(int fees) {
            this->fees = fees;
        }

        void setFeesPaid(bool feesPaid) {
            this->feesPaid = feesPaid;
        }

        void setAttendance(int attendance) {
            this->attendance = attendance;
        }

        void setAddress(const string& address) {
            this->address = address;
        }
        void attIncrement() {
            this->attendance++;
        }
        void printReport() const {
            cout << "Roll Number: " << rollNumber << endl;
            cout << "Name: " << name << endl;
            cout << "Phone Number: " << phoneNumber << endl;
            cout << "Grade: " << grade << endl;
            cout << "Fees: " << fees << endl;
            cout << "Fee Status: " << (feesPaid ? "Paid" : "Pending") << endl;
            cout << "Attendance: " << attendance << endl;
            cout << "Address: " << address << endl;
            cout << "---------------------------" << endl;
        }

        void appendResult() {
            int cont = 1;
            string sub;
            int marks;
            while (cont) {
                cout << "Enter Subject Name " << endl;
                cin >> sub;
                cout << "Enter Marks " << endl;
                cin >> marks;
                marksMap[sub] = marks;
                cout << "Enter 0 to exit or any other number to continue " << endl;
                cin >> cont;
            }
            this->resultStatus = true;

        }
        map<string, int> getMarks() {
            return marksMap;
        }
        void dispResult() {
                      
            if (!resultStatus) {
                cout << "Result hasn't been uploaded yet" << endl;
            }
            else {
                auto it = marksMap.begin();

                // Iterate through the map and print the elements
                while (it != marksMap.end())
                {
                    std::cout << "Subject: " << it->first << ", Marks: " << it->second << std::endl;
                    ++it;
                }

            }
        }
    };

    /*class venue {
    private:
        int size;
        int capacity;
    public:
        venue(int sz, int cap) {
            size = sz;
            capacity = cap;
        }
        int getsize() {
            return size;
        }
        int getcapacity() {
            return capacity;
        }

    };*/

    class employee {
    protected:
        string empid;
        string empname;
        double salary;
        int attendance;
    public:
        employee() {}
        employee(string empid, string empname, double salary, int att)
        {
            this->empid = empid;
            this->empname = empname;
            this->salary = salary;
            attendance = att;
        }
        virtual void getdetails()
        {
            cout << "PERSONAL INFORMATION" << endl;
            cout << "****************************" << endl;
            cout << "Your Name: " << empname << endl;
            cout << "Your ID: " << empid << endl;
            cout << "Your salary: " << salary << endl;
            cout << "Attendance to date: " << attendance << endl;
        }
        void increment() {
            attendance++;
        };
        int getsalary()
        {
            return salary;
        }
        string getempid()
        {
            return empid;
        }
        string getempname()
        {
            return empname;
        }
        int getattendance()
        {
            return attendance;
        }
    };

    class SupportStaff : public employee
    {
    public:
        SupportStaff() {}
        SupportStaff(string eid, string en, int s, int att) :employee(eid, en, s, att)
        {

        }
        void getdetails()
        {
            cout << "PERSONAL INFORMATION" << endl;
            cout << "****************************" << endl;
            cout << "Your Name: " << empname << endl;
            cout << "Your ID: " << empid << endl;
            cout << "Your salary: " << salary << endl;
            cout << "Attendance to date: " << attendance << endl;
        }
        void getAttendance() {
            cout << " Attendance count = " << attendance << endl;
        }
    };

    class Teacher : public employee
    {
    private:
        string sub;
        int noc;
    public:
        Teacher() {}
        Teacher(string eid, string en, double s, string sub, int noc, int att) :employee(eid, en, s, att)
        {
            this->sub = sub;
            this->noc = noc;
        }
        void getdetails()
        {
            cout << "PERSONAL INFORMATION" << endl;
            cout << "****************************" << endl;
            cout << "Your Name: " << empname << endl;
            cout << "Your ID: " << empid << endl;
            cout << "Your salary: " << salary << endl;
            cout << "Attendance to date: " << attendance << endl;
            cout << "Your Subject: " << sub << endl;
            cout << "Number of classes you are teaching: " << noc << endl;
        }
        int getNoc() {

            return noc;
        }
        string getSub() {
            return sub;
        }

    };

    class equipment {
        string name;
        string type;
        int quantity;
    public:


        equipment(string name, string type, int quantity) {
            this->name = name;
            this->type = type;
            this->quantity = quantity;
        }
        string getName() {
            return name;
        }
        string getType() {
            return type;
        }
        int getQty() {
            return quantity;
        }
    };


    class student_credentials
    {
        string user;
        string pass;
        string _id;
    public:
        student_credentials(string u, string p, string id)
        {
            user = u;
            pass = p;
            _id = id;
        }
        void setuser(string u)
        {
            user = u;
        }
        string getuser()
        {
            return user;
        }
        void setpass(string p)
        {
            pass = p;
        }
        string getpass()
        {
            return pass;
        }
        string getId() {
            return _id;
        }

    };

    class teachers_credentials
    {
        string user;
        string pass, _id;
    public:
        teachers_credentials(string u, string p, string id)
        {
            user = u;
            pass = p;
            _id = id;
        }
        string getId() {
            return _id;
        }
        void setuser(string u)
        {
            user = u;
        }
        string getuser()
        {
            return user;
        }
        void setpass(string p)
        {
            pass = p;
        }
        string getpass()
        {
            return pass;
        }
    };

    class admin_credentials
    {
        string user;
        string pass, _id;
    public:
        admin_credentials(string u, string p, string id) {

            user = u;
            pass = p;
            _id = id;
        }
        string getId() {
            return _id;
        }
        void setuser(string u)
        {
            user = u;
        }
        string getuser()
        {
            return user;
        }
        void setpass(string p)
        {
            pass = p;
        }
        string getpass()
        {
            return pass;
        }
    };



    class school_management {
    protected:
        
        vector<equipment> eqpVe;
        vector<Student> stdVe;
        vector<NoticeBoard> ntVe;
        vector <Teacher> teachersVe;
        vector <SupportStaff> supportstaffVe;
        vector <student_credentials> stdLogin;
        vector <teachers_credentials> empLogin;
        vector <admin_credentials> adminLogin;




    public:
        school_management() {
        
            //stdLogin.push_back(student_credentials("a", "abcd", "SE-22054"));
            //stdLogin.push_back(student_credentials("d", "abcd", "SE-22055"));
            /*empLogin.push_back(teachers_credentials("b", "abc", "TE-0015"));
            empLogin.push_back(teachers_credentials("x", "abz", "SS-0015"));
            adminLogin.push_back(admin_credentials("c", "abcde", "AD-110"));
            
            teachersVe.push_back(Teacher("TE-0015", "Eraj", 45000.0, "English", 3,0));
            supportstaffVe = { SupportStaff("TE-0001","Mr XYZ",1000.50,0), SupportStaff("TE-0002","Mr ABC",1000.50,0),SupportStaff("TE-0003","Mr DFG",1000.50,0) };
            supportstaffVe.push_back(SupportStaff("SS-0015", "Ali", 20000,0));

            eqpVe = { equipment("PC", "Electronic", 47),management::equipment("Projector", "Electronic", 7),management::equipment("Desks", "Furniture", 80),management::equipment("White Board", "Furniture", 20) };
            stdVe = { Student("SE-22054", "Mr Dave", "9255415320", "V",
                  42000, NULL, 0, "North Nazimabad, Karachi" , 'a'),Student("SE-22055", "Mr Dab", "9255415324", "VI",
                  42000, NULL, 0, "North Nazimabad, Karachi" , 'b') };
            ntVe = { NoticeBoard("PTM","PTM WILL BE HELD ON 32 DECEMBER "),NoticeBoard("RESULT","RESULT WILL BE ANNOUNCED ON 32 DECEMBER ") };*/
        }
        vector <Teacher> getTeVe() {
            return teachersVe;
        }
    };

    class basicOperations :public school_management {
    protected:
        Database db;
        string dbfilename;
    public:
        basicOperations() {}
        // Constructor for creating table
        basicOperations(const string& dbfile) :db(dbfile) {
            dbfilename = dbfile;

        }
        //Callback function for checking if user already exist or not(LINKED TO newuser AND setuser FUNCTION)
        static int checkUserExistsCallback(void* data, int argc, char** argv, char** azColName) {
            bool* userExists = static_cast<bool*>(data);
            *userExists = (argc > 0);
            return 0;
        }
        //Callback function for viewing user's credentials(LINKED TO viewCredentials AND setuser FUNCTION)
        static int callback(void* data, int argc, char** argv, char** azColName) {
            for (int i = 0; i < argc; i++) {
                cout << azColName[i] << ";" << argv[i] << endl;
            }
            cout << endl;
            return 0;
        }
        //Viewing user credentials
        void viewID(char key) {
            sqlite3* ddb;
            sqlite3_open(dbfilename.c_str(), &ddb);
            char* errMsg;
            string selectQ;
            int result;
            switch (key) {
            case 'e':
                selectQ = "SELECT userid FROM EmployeeC ORDER BY userid ASC;";
                break;
            case 'E':
                selectQ = "SELECT userid FROM Employee ORDER BY userid ASC;";
                break;
            case 't':
                selectQ = "SELECT userid FROM Teacher ORDER BY userid ASC;";
                break;
            case 's':
                selectQ = "SELECT empid FROM Student ORDER BY userid ASC;";
                break;
            case 'q':
                selectQ = "SELECT name FROM Equipment ORDER BY name ASC;";
                break;
            }
            result = sqlite3_exec(ddb, selectQ.c_str(), callback, nullptr, &errMsg);
            if (result != SQLITE_OK) {
                cerr << "Error executing query! " << errMsg << endl;
                sqlite3_free(errMsg);
            }
        }

        void viewCredentials(char key) {
            sqlite3* ddb;
            sqlite3_open(dbfilename.c_str(), &ddb);
            char* errMsg;
            const char* selectQ;
            sqlite3_stmt* stmt;
            int result;
            int rc;            
            switch (key) {
            case 'a':
                selectQ = "SELECT * FROM AdminC;";
                rc = sqlite3_prepare_v2(ddb, selectQ, -1, &stmt, nullptr);
                if (rc != SQLITE_OK) {
                    cerr << "Error executing Query! " << sqlite3_errmsg(ddb) << endl;
                    //sqlite3_free(errMsg);
                }
                else {
                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                        string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                        string pass = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                        string id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                        adminLogin.push_back(admin_credentials(username, pass, id));
                        //cout << adminLogin[adminLogin.size() - 1].getuser() << endl;
                        
                        // Process or print retrieved values
                    }

                }
                sqlite3_finalize(stmt);

                break;
            case 'e':{
                selectQ = "SELECT * FROM EmployeeC ;";
                rc = sqlite3_prepare_v2(ddb, selectQ, -1, &stmt,nullptr);
                if (rc != SQLITE_OK) {
                    cerr << "Error executing Query! " <<sqlite3_errmsg(ddb)<< endl;
                    //sqlite3_free(errMsg);
                }
                else {
                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                        string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                        string pass = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                        string id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                        empLogin.push_back(teachers_credentials(username, pass,id));

                        // Process or print retrieved values
                    }

                }
                sqlite3_finalize(stmt);

                break;
            }
            case 'E':
                selectQ = "SELECT * FROM Employee ORDER BY userid ASC;";
                rc = sqlite3_prepare_v2(ddb, selectQ, -1, &stmt, nullptr);
                if (rc != SQLITE_OK) {
                    cerr << "Error executing query! " << endl;
                    //sqlite3_free(errMsg);
                }
                else {
                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                        string _id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                        supportstaffVe.push_back(SupportStaff(_id, name, 20.05, 0));

                        // Process or print retrieved values
                    }
                }
                    sqlite3_finalize(stmt);

                    break;
            case 'T':
                selectQ = "SELECT * FROM Teachers ;";
                rc = sqlite3_prepare_v2(ddb, selectQ, -1, &stmt, nullptr);
                if (rc != SQLITE_OK) {
                    cerr << "Error executing Query! " << sqlite3_errmsg(ddb) << endl;
                    //sqlite3_free(errMsg);
                }
                else {
                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                        string _id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                        float salary = static_cast<float>(sqlite3_column_double(stmt, 2));
                        string sub = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
                        int noc = sqlite3_column_int(stmt, 4);
                        int att = sqlite3_column_int(stmt, 5);
                        //cout <<"View credentials " << name << endl;
                        teachersVe.push_back(Teacher(_id, name, salary,sub,noc, att));
                        //cout << teachersVe[teachersVe.size() - 1].getempname() << " pushed in vector" << endl;
                        // Process or print retrieved values
                    }
                }
                sqlite3_finalize(stmt);

                break;
            case 's':
                selectQ = "SELECT * FROM StudentC ORDER BY iD ASC;";
                rc = sqlite3_prepare_v2(ddb, selectQ, -1, &stmt, nullptr);
                if (rc != SQLITE_OK) {
                    cerr << "Error executing Query! " << sqlite3_errmsg(ddb) << endl;
                    //sqlite3_free(errMsg);
                }
                else {
                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                        string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                        string pass = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                        string id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                        stdLogin.push_back(student_credentials(username, pass, id));

                        // Process or print retrieved values
                    }

                }
                sqlite3_finalize(stmt);
                break;

            case 'S':
                selectQ = "SELECT * FROM Students ;";
                rc = sqlite3_prepare_v2(ddb, selectQ, -1, &stmt, nullptr);
                if (rc != SQLITE_OK) {
                    cerr << "Error executing Query! " << sqlite3_errmsg(ddb) << endl;
                    //sqlite3_free(errMsg);
                }
                else {
                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                        string _roll = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                        string no = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                        string grade = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
                        int fees = sqlite3_column_int(stmt, 4);
                        int temp = sqlite3_column_int(stmt, 5);
                        bool status = bool(temp == 1);
                        int att = sqlite3_column_int(stmt, 6);
                        string add = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
                        char sec = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8))[0];
                        //cout << "View credentials " << name << endl;
                        stdVe.push_back(Student(_roll, name, no, grade, fees,status ,att,add,sec));
                        //cout << stdVe[stdVe.size() - 1].getName() << " pushed in vector" << endl;
                        // Process or print retrieved values
                    }
                }
                sqlite3_finalize(stmt);

                break;
            case 'q':
                selectQ = "SELECT * FROM Equipment ORDER BY name ASC;";
                rc = sqlite3_prepare_v2(ddb, selectQ, -1, &stmt, nullptr);
                if (rc != SQLITE_OK) {
                    cerr << "Error executing Query! " << sqlite3_errmsg(ddb) << endl;
                }
                else {
                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                        string _roll = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                        int qty = (sqlite3_column_int(stmt, 2));
                        eqpVe.push_back(equipment(_roll, name, qty));
                        
                    }
                }
                sqlite3_finalize(stmt);

                
                break;

            case 'n':
                selectQ = "SELECT * FROM Notices;";
                rc = sqlite3_prepare_v2(ddb, selectQ, -1, &stmt, nullptr);
                if (rc != SQLITE_OK) {
                    cerr << "Error executing Query! " << sqlite3_errmsg(ddb) << endl;
                }
                else {
                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                        string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                        string content = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                        
                        ntVe.push_back(NoticeBoard(title, content));

                    }
                }
                sqlite3_finalize(stmt);
            }
            /*result = sqlite3_exec(ddb, selectQ.c_str(), callback, nullptr, &errMsg);
            if (result != SQLITE_OK) {
                cerr << "Error executing query! " << errMsg << endl;
                sqlite3_free(errMsg);
            }*/
            sqlite3_close(ddb);
        }
        //Adding new user
        void newuser(char key) {
            sqlite3* ddb;
            sqlite3_open(dbfilename.c_str(), &ddb);
            string checkQ;
            char* errMsg;
            int result;
            bool userExists = false;
            switch (key) {
            case 'e':
                checkQ = "SELECT id FROM EmployeeC WHERE id = '" + empLogin[empLogin.size() - 1].getId() + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errMsg << endl;
                    sqlite3_free(errMsg);
                    return;
                }
                break;
            case 'E':
                checkQ = "SELECT userid FROM Employee WHERE userid = '" + supportstaffVe[supportstaffVe.size() - 1].getempid() + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errMsg << endl;
                    sqlite3_free(errMsg);
                    return;
                }
                if (userExists) {
                    cout << "User already Registered! " << endl;
                    return;
                }
                break;
            case 'T':
                checkQ = "SELECT ID FROM Teachers WHERE ID = '" + teachersVe[teachersVe.size() - 1].getempid() + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errMsg << endl;
                    sqlite3_free(errMsg);
                    return;
                }
                break;
            case 's':
                checkQ = "SELECT Username FROM StudentC WHERE Username = '" + stdLogin[stdLogin.size() - 1].getuser() + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errMsg << endl;
                    sqlite3_free(errMsg);
                    return;
                }
                break;
            case 'S':
                checkQ = "SELECT ROLL_NO FROM Students WHERE ROLL_NO = '" + stdVe[stdVe.size() - 1].getRollNumber() + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errMsg << endl;
                    sqlite3_free(errMsg);
                    return;
                }
                break;
            case 'q':
                checkQ = "SELECT name FROM Equipment WHERE name = '" + eqpVe[eqpVe.size() - 1].getName() + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errMsg << endl;
                    sqlite3_free(errMsg);
                    return;
                }
                break;
            }
            if (userExists) {
                cout << "User already Registered! " << endl;
                return;
            }
            string insertQ;
            switch (key) {
            case 'e':
                insertQ = "INSERT INTO EmployeeC(username, password,id) VALUES('" + empLogin[empLogin.size() - 1].getuser() + "', '" + empLogin[empLogin.size() - 1].getpass() + "','" + empLogin[empLogin.size() - 1].getId() + "');";
                break;
            case 'E':
                insertQ = "INSERT INTO Employee(userid, Name, Salary,Attendance) VALUES('" + supportstaffVe[supportstaffVe.size() - 1].getempid()
                    + "','" + supportstaffVe[supportstaffVe.size() - 1].getempname() + "','" + to_string(supportstaffVe[supportstaffVe.size() - 1].getsalary()) + "','"
                    + to_string(supportstaffVe[supportstaffVe.size() - 1].getattendance()) + "');";
                break;
            case 'T':
                insertQ = "INSERT INTO Teachers(ID, NAME,SALARY,SUBJECT,NOC, ATT) VALUES('" + teachersVe[teachersVe.size() - 1].getempid() +
                    "', '" + teachersVe[teachersVe.size() - 1].getempname() + "', '" + to_string(teachersVe[teachersVe.size() - 1].getsalary()) +
                    "','" + teachersVe[teachersVe.size() - 1].getSub() + "','" + to_string(teachersVe[teachersVe.size() - 1].getNoc()) +
                    "','" + to_string(teachersVe[teachersVe.size() - 1].getattendance()) + "');" ;
                break;
            case 's':
                insertQ = "INSERT INTO StudentC VALUES('" + stdLogin[stdLogin.size() - 1].getuser()
                    + "', '" + stdLogin[stdLogin.size() - 1].getpass() + "','" +
                    stdLogin[stdLogin.size() - 1].getId() + "');";
                break;
            case 'S':
                insertQ = "INSERT INTO Students VALUES('" +
                    stdVe[stdVe.size() - 1].getRollNumber()
                    + "','" + stdVe[stdVe.size() - 1].getName() + "','" +
                    (stdVe[stdVe.size() - 1].getPhoneNumber()) + "','"
                    + (stdVe[stdVe.size() - 1].getGrade()) + "','" +
                    to_string(stdVe[stdVe.size() - 1].getFees()) + "','" +
                    to_string(stdVe[stdVe.size() - 1].getFeesPaid()) + "','" +
                    to_string(stdVe[stdVe.size() - 1].getAttendance()) + "','" +
                    (stdVe[stdVe.size() - 1].getAddress()) + "','" +
                    (stdVe[stdVe.size() - 1].getSec()) + "');";
                break;
            case 'q':
                insertQ = "INSERT INTO Equipment(name, type, quantity) VALUES('" + eqpVe[eqpVe.size() - 1].getName() + "','"
                    + eqpVe[eqpVe.size() - 1].getType() + "','" + to_string(eqpVe[eqpVe.size() - 1].getQty()) + "');";
                break;
            case 'n':
                insertQ = "INSERT INTO Notices VALUES('" + ntVe[ntVe.size() - 1].getTitle() + "','" +
                    ntVe[ntVe.size() - 1].getContent() + "');";
                break;
            }
            db.executeQuery(insertQ);
        }
        //Updating userid
        void setuser( char key)
        {
            string uName, uType, checkQ, query;
            float uSalary;
            int uattendance, uqty, result, result1;
            sqlite3* ddb;
            bool userExists;
            char* errMsg;
            char* errorMsg;
            sqlite3_open(dbfilename.c_str(), &ddb);
            switch (key) {
            case 'E':
                checkQ = "SELECT id FROM EmployeeC WHERE id = '" + empLogin[empLogin.size() - 1].getId() + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errorMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errorMsg << endl;
                    sqlite3_free(errorMsg);
                    return;
                }
                if (userExists == false) {
                    cout << "User does not exist! " << endl;
                    return;
                }

                query = "UPDATE EmployeeC SET username = '" + empLogin[empLogin.size() - 1].getuser() + "', password ='" + empLogin[empLogin.size() - 1].getpass() + "' WHERE id = '" + empLogin[empLogin.size() - 1].getId() + "';";
                result1 = sqlite3_exec(ddb, query.c_str(), callback, nullptr, &errMsg);
                if (result1 != SQLITE_OK) {
                    cerr << "Error executing query! " << errMsg << endl;
                    sqlite3_free(errMsg);
                }
                else {
                    cout << "Executed" << endl;
                }
                break;

                

            case 'S':
                checkQ = "SELECT iD FROM StudentC WHERE iD = '" + stdLogin[stdLogin.size() - 1].getId() + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errorMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errorMsg << endl;
                    sqlite3_free(errorMsg);
                    return;
                }
                if (userExists == false) {
                    cout << "User does not exist! " << endl;
                    return;
                }

                query = "UPDATE StudentC SET Username = '" + stdLogin[stdLogin.size() - 1].getuser() + "', Pass ='" + stdLogin[stdLogin.size() - 1].getpass()  + "' WHERE iD = '" + stdLogin[stdLogin.size() - 1].getId() + "';";
                result1 = sqlite3_exec(ddb, query.c_str(), callback, nullptr, &errMsg);
                if (result1 != SQLITE_OK) {
                    cerr << "Error executing query! " << errMsg << endl;
                    sqlite3_free(errMsg);
                }
                else {
                    cout << "Executed" << endl;
                }
                break;


            case 'e':
                checkQ = "SELECT userid FROM Employee WHERE userid = '" + supportstaffVe[supportstaffVe.size() - 1].getempid() + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errorMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errorMsg << endl;
                    sqlite3_free(errorMsg);
                    return;
                }
                if (userExists == false) {
                    cout << "User does not exist! " << endl;
                    return;
                }
               
                query = "UPDATE Employee SET Name = '" + supportstaffVe[supportstaffVe.size()-1].getempname() + "', Salary =" + to_string(supportstaffVe[supportstaffVe.size() - 1].getsalary()) +
                    ", Attendance = " + to_string(supportstaffVe[supportstaffVe.size() - 1].getattendance()) + " WHERE userid = '" + supportstaffVe[supportstaffVe.size() - 1].getempid() + "';";
                result1 = sqlite3_exec(ddb, query.c_str(), callback, nullptr, &errMsg);
                if (result1 != SQLITE_OK) {
                    cerr << "Error executing query! " << errMsg << endl;
                    sqlite3_free(errMsg);
                }
                else {
                    cout << "Executed" << endl;
                }
                break;
            
            case 't':
                checkQ = "SELECT ID FROM Teachers WHERE ID = '" + teachersVe[teachersVe.size() - 1].getempid() + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errorMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errorMsg << endl;
                    sqlite3_free(errorMsg);
                    return;
                }
                if (userExists == false) {
                    cout << "User does not exist! " << endl;
                    return;
                }

                query = "UPDATE Teachers SET NAME = '" + teachersVe[teachersVe.size() - 1].getempname() + "', SALARY =" + to_string(teachersVe[teachersVe.size() - 1].getsalary()) +
                    ", ATT = " + to_string(teachersVe[teachersVe.size() - 1].getattendance()) + ", NOC = "+ to_string(teachersVe[teachersVe.size() - 1].getNoc()) + ", SUBJECT = '"+ teachersVe[teachersVe.size() - 1].getSub() + "' WHERE ID = '" + teachersVe[teachersVe.size() - 1].getempid() + "';";
                result1 = sqlite3_exec(ddb, query.c_str(), callback, nullptr, &errMsg);
                if (result1 != SQLITE_OK) {
                    cerr << "Error executing query! " << errMsg << endl;
                    sqlite3_free(errMsg);
                }
                else {
                    cout << "Executed" << endl;
                }
                break;

            
            case 's':
                checkQ = "SELECT ROLL_NO FROM Students WHERE ROLL_NO = '" + stdVe[stdVe.size() - 1].getRollNumber() + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errorMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errorMsg << endl;
                    sqlite3_free(errorMsg);
                    return;
                }
                if (userExists == false) {
                    cout << "User does not exist! " << endl;
                    return;
                }
                query = "UPDATE Students SET NAME = '" + stdVe[stdVe.size() - 1].getName() +  "', CONTACT_NO ='" +
                    stdVe[stdVe.size() - 1].getPhoneNumber() + "', CLASS ='" + stdVe[stdVe.size() - 1].getGrade() + "',FEES_STATUS = "+
                    to_string(stdVe[stdVe.size() - 1].getFeesPaid()) + ", FEES = " + to_string(stdVe[stdVe.size() - 1].getFees()) +
                    ", ATT = " + to_string(stdVe[stdVe.size() - 1].getAttendance()) + ", ADDRESS = '"+ stdVe[stdVe.size() - 1].getAddress() +
                    "', SECTION = '" + stdVe[stdVe.size() - 1].getSec() +
                    "' WHERE ROLL_NO = '" + stdVe[stdVe.size() - 1].getRollNumber() + "';";  
                result1 = sqlite3_exec(ddb, query.c_str(), callback, nullptr, &errMsg);
                if (result1 != SQLITE_OK) {
                    cerr << "Error executing query! " << errMsg << endl;
                    sqlite3_free(errMsg);
                }
                else {
                    cout << "Executed" << endl;
                }
                break;

            case 'q':
                checkQ = "SELECT name FROM Equipment WHERE name = '" + eqpVe[eqpVe.size() - 1].getName() + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errorMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errorMsg << endl;
                    sqlite3_free(errorMsg);
                    return;
                }
                if (userExists == false) {
                    cout << "User does not exist! " << endl;
                    return;
                }
                query = "UPDATE Equipment SET TYPE = '" + eqpVe[eqpVe.size() - 1].getType() + "', QUANTITY =" +
                    to_string(eqpVe[eqpVe.size() - 1].getQty()) +
                    " WHERE name = '" + eqpVe[eqpVe.size() - 1].getName() + "';";
                result1 = sqlite3_exec(ddb, query.c_str(), callback, nullptr, &errMsg);
                if (result1 != SQLITE_OK) {
                    cerr << "Error executing query! " << errMsg << endl;
                    sqlite3_free(errMsg);
                }
                else {
                    cout << "Executed!!!!!!!" << endl;
                }
                break;

            case 'n':
                checkQ = "SELECT title FROM Notices WHERE title = '" + ntVe[ntVe.size() - 1].getTitle() + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errorMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errorMsg << endl;
                    sqlite3_free(errorMsg);
                    return;
                }
                if (userExists == false) {
                    cout << "User does not exist! " << endl;
                    return;
                }
                query = "UPDATE Notices SET content = '" + ntVe[ntVe.size() - 1].getContent() + 
                    "' WHERE title = '" + ntVe[ntVe.size() - 1].getTitle() + "';";
                result1 = sqlite3_exec(ddb, query.c_str(), callback, nullptr, &errMsg);
                if (result1 != SQLITE_OK) {
                    cerr << "Error executing query! " << errMsg << endl;
                    sqlite3_free(errMsg);
                }
                else {
                    cout << "Executed!!!!!!!" << endl;
                }
                break;
            }

        }

        void updateAtt(int index, char key) {
            string checkQ,query;
            int result,result1;
            sqlite3* ddb;
            bool userExists;
            char* errMsg;
            char* errorMsg;
            sqlite3_open(dbfilename.c_str(), &ddb);
            switch (key) {
            case 'e':
                checkQ = "SELECT userid FROM Employee WHERE userid = '" + supportstaffVe[index].getempid() + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errorMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errorMsg << endl;
                    sqlite3_free(errorMsg);
                    return;
                }
                if (userExists == false) {
                    cout << "User does not exist! " << endl;
                    //return;
                }

                query = "UPDATE Employee SET Attendance = " + to_string(supportstaffVe[index].getattendance()) + " WHERE userid = '" + supportstaffVe[index].getempid() + "';";
                result1 = sqlite3_exec(ddb, query.c_str(), callback, nullptr, &errMsg);
                if (result1 != SQLITE_OK) {
                    cerr << "Error executing query! " << errMsg << endl;
                    sqlite3_free(errMsg);
                }
                else {
                    cout << "Executed" << endl;
                }
                break;

            case 't':
                checkQ = "SELECT ID FROM Teachers WHERE ID = '" + teachersVe[index].getempid() + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errorMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errorMsg << endl;
                    sqlite3_free(errorMsg);
                    return;
                }
                if (userExists == false) {
                    cout << "User does not exist! " << endl;
                    return;
                }

                query = "UPDATE Teachers SET ATT = " + to_string(teachersVe[index].getattendance()) + " WHERE ID = '" + teachersVe[index].getempid() + "';";
                result1 = sqlite3_exec(ddb, query.c_str(), callback, nullptr, &errMsg);
                if (result1 != SQLITE_OK) {
                    cerr << "Error executing query! " << errMsg << endl;
                    sqlite3_free(errMsg);
                }
                else {
                    cout << "Executed" << endl;
                }
                break;


            case 's':
                checkQ = "SELECT ROLL_NO FROM Students WHERE ROLL_NO = '" + stdVe[index].getRollNumber() + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errorMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errorMsg << endl;
                    sqlite3_free(errorMsg);
                    return;
                }
                if (userExists == false) {
                    cout << "User does not exist! " << endl;
                    //return;
                }
                query = "UPDATE Students SET ATT = " + to_string(stdVe[index].getAttendance()) +
                    " WHERE ROLL_NO = '" + stdVe[index].getRollNumber() + "';";
                result1 = sqlite3_exec(ddb, query.c_str(), callback, nullptr, &errMsg);
                if (result1 != SQLITE_OK) {
                    cerr << "Error executing query! " << errMsg << endl;
                    sqlite3_free(errMsg);
                }
                else {
                    cout << "Executed" << endl;
                }
                break;
            }

        }
        void del(string delID, char key) {
            string delQ;
            sqlite3* ddb;
            string checkQ;
            bool userExists;
            char* errorMsg;
            int result;
            sqlite3_open(dbfilename.c_str(), &ddb);
            switch (key) {
            case 'E':
                checkQ = "SELECT userid FROM Employee WHERE userid = '" + delID + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errorMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errorMsg << endl;
                    sqlite3_free(errorMsg);
                    return;
                }
                if (userExists == false) {
                    cout << "User does not exist! " << endl;
                    return;
                }
                delQ = "DELETE FROM Employee WHERE userid = '" + delID + "';";
                break;
            case 'q':
                checkQ = "SELECT name FROM Equipment WHERE name = '" + delID + "';";
                userExists = false;
                result = sqlite3_exec(ddb, checkQ.c_str(), checkUserExistsCallback, &userExists, &errorMsg);
                if (result != SQLITE_OK) {
                    cerr << "error" << errorMsg << endl;
                    sqlite3_free(errorMsg);
                    return;
                }
                if (userExists == false) {
                    cout << "User does not exist! " << endl;
                    return;
                }
                delQ = "DELETE FROM Equipment WHERE name = '" + delID + "';";
                break;
            }
            db.executeQuery(delQ);
        }
    };



    class adminOperations : public basicOperations {
        bool flag;
    public:
        adminOperations(string file):basicOperations(file){}
        void  create(char key) {
            switch (key)
            {
            case 't': {
                string _id, _name,subject,pass,username;
                int att, noc;
                float salary;
                cout << "ENTER EMPLOYEE CREDENTIALS " << endl;
                cout << "Enter Teacher Id" << endl;
                cin>> _id;    
                cout << "Enter Teacher Name" << endl;
                cin>>_name;  
                cout << "Enter Teacher's salary" << endl;
                cin >> salary; 
                cout << "Enter Teacher's attendance count " << endl;
                cin >> att;
                cout << "Enter Teacher's Subject " << endl;
                cin>>subject;
                cout << "Enter Teavher's number of classes " << endl;
                cin >> noc;
                cout << "Enter Username for login: ";
                cin>>username;
                cout << "Enter Password: ";
                cin>>pass;
                teachersVe.push_back(Teacher(_id, _name, salary, subject, noc, att));
                empLogin.push_back(teachers_credentials(username, pass, _id));
                break;

            }
            case 'e': {
                string _id,pass,username;
                string _name;
                int att;
                float salary = 0.00;
                cout << "ENTER EMPLOYEE CREDENTIALS " << endl;
                cout << "Enter EMPLOYEE Id" << endl;
                cin>>_id;
                cout << "Enter Employee Name" << endl;
                cin>> _name;
                cout << "Enter Employee's salary" << endl;
                cin >> salary;
                cout << "Enter Employee's attendance count " << endl;
                cin >> att;
                cout << "Enter Username for login: ";
                cin>>username;
                cout << "Enter Password: ";
                cin>>pass;
                // for(int){
                  // if(e.getId()==_id){
                  //   cout<<"Employee with Id "+_id+" already exists. Please enter a unique ID for a new employee"<<endl;
                  //   break;
                  // }
                // }
                supportstaffVe.push_back(SupportStaff(_id, _name, salary,att));
                empLogin.push_back(teachers_credentials(username, pass, _id));
                
                cout << "Data Updated succesfully!!" << endl;
                break;
            }

            case 's': {
                string rollNumber;
                string name;
                string phoneNumber;
                string grade,pass,username;
                int fees;
                bool feesPaid;
                int attendance;
                string address;
                char sec;
                cout << "Enter roll number: ";
                cin >> rollNumber;

                cin.ignore();
                cout << "Enter student name: ";
                cin>>name;

                cout << "Enter phone number: ";
                cin>>phoneNumber;

                cout << "Enter grade: ";
                cin>>grade;

                cout << "Enter fees amount: ";
                cin >> fees;

                cout << "Is fees paid? (1 for Yes, 0 for No): ";
                cin >> feesPaid;

                cout << "Enter attendance percentage: ";
                cin >> attendance;
                cout << "Enter section percentage: ";
                cin >> sec;

                cin.ignore();
                cout << "Enter address: ";
                cin>>address;

                cout << "Enter Username for login: ";
                cin>>username;
                cout << "Enter Password: ";
                cin>>pass;

                stdVe.push_back(Student(rollNumber, name, phoneNumber, grade, fees, feesPaid, attendance, address, sec));
                stdLogin.push_back(student_credentials(username, pass, rollNumber));
                cout << "Student added successfully!" << endl;
                cout << "---------------------------" << endl;
            }

                    //student code here


                    break;
            case 'q':
            {
                string _type;
                string _name;
                int _qty;
                cout << "ENTER EQUIPMENT CREDENTIALS " << endl;
                cout << "Enter Equipment Name" << endl;
                cin>>_name;
                cout << "Enter Equipment Type" << endl;
                cin>>_type;
                cout << "Enter Equipment Quantity" << endl;
                cin >> _qty;
                for (equipment& e : eqpVe) {
                    if (e.getName() == _name) {
                        cout << "Equipment with name " + _name + " already exists. Please enter a new equipment " << endl;
                    }
                }
                eqpVe.push_back(equipment(_name, _type, _qty));
                cout << "Data updated succesfully!!" << endl;

                break;
            }

            case 'n': {
                string title, content;
                cout << "Enter the title of the notice: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter the content of the notice: ";
                getline(cin, content);
                ntVe.push_back(NoticeBoard(title, content));
                cout << "Successfully added" << endl;}

            }
            
        }

        void  read(char key) {
            system("cls");
              
            switch (key) {
            case 't':
                cout << "TEACHER DATA." << endl;
                if (teachersVe.size() == 0) {
                    cout << "No data found..";
                }
                for (int i = 0;i < teachersVe.size();i++) {
                    cout << "ID : " << teachersVe[i].getempid() << " NAME : " << teachersVe[i].getempname() << " SALARY : " << 
                        teachersVe[i].getsalary() << " Attendance : " << teachersVe[i].getattendance()<< " Subject : " 
                        << teachersVe[i].getSub() << "No. of classes : " << teachersVe[i].getNoc() << endl;
                }
                break;
            case 'e':
                cout << "EMPLOYEE DATA." << endl;
                if (supportstaffVe.size() == 0) {
                    cout << "No data found..";
                }
                for (int i = 0;i < supportstaffVe.size();i++) {
                    cout << "ID : " << supportstaffVe[i].getempid() << " NAME : " << supportstaffVe[i].getempname() << " SALARY : " << supportstaffVe[i].getsalary() << " Attendance : "<<supportstaffVe[i].getattendance() <<endl;
                }
                break;
            case 's':
                //student code here
                if (stdVe.empty()) {
                    cout << "No students found!" << endl;
                }
                else {
                    cout << "STUDENT LIST" << endl;
                    cout << "---------------------------" << endl;
                    for (const auto& student : stdVe) {
                        student.printReport();
                    }
                }

                cout << "---------------------------" << endl;
                break;
            case 'q':
                if (supportstaffVe.size() == 0) {
                    cout << "No data found..";
                }
                for (int i = 0; i < eqpVe.size(); i++) {
                    cout << "Name: " << eqpVe[i].getName() << endl;
                    cout << "Type: " << eqpVe[i].getType() << endl;
                    cout << "Quantity: " << eqpVe[i].getQty() << endl;
                    cout << endl;
                }
                break;

            case 'n':
                for (NoticeBoard notice : ntVe) {
                    cout << "Title: " << notice.getTitle() << endl;
                    cout << "Content: " << notice.getContent() << endl;
                    cout << endl;
                }
                break;
            }
        }
        void del(char key) {

            //to be decided
            switch (key) {
            case 'n':
                cout << "Enter the title of the notice you want to delete: ";
                string title;
                cin.ignore();
                getline(cin, title);

                for (int i = 0; i < ntVe.size(); i++) {
                    if (ntVe[i].getTitle() == title) {
                        ntVe.erase(ntVe.begin() + i);
                        cout << "Successfully deleted" << endl;
                        return;
                    }
                }

                cout << "Notice with the given title not found" << endl;
            }
        }
        int _find(char key) {
            string req;
        options:
            switch (key) {
            case 't':
                cout << "Enter the ID of the teacher you want to find. " << endl;
                cin>>req;
                cout << "TEACHER DATA." << endl;
                if (teachersVe.size() == 0) {
                    cout << "No data found..";
                    return -1;
                }
                for (int i = 0;i < teachersVe.size();i++) {
                    if (teachersVe[i].getempid() == req) {
                        string found = "ID :" + teachersVe[i].getempid() + "\nNAME : " + teachersVe[i].getempname() + "\nSALARY : " + to_string(teachersVe[i].getsalary()) + "\n" + 
                            "Attendance : " + to_string(teachersVe[i].getattendance()) + "\nNo. of classes: "+ to_string(teachersVe[i].getNoc()) + "\nSubject : "+ 
                            teachersVe[i].getSub() + "\n";
                        cout << found;
                        return i;
                    }
                }
                cout << "No match found for " + req << endl;
                return -1;

            case 'e':
                cout << "Enter the ID of the employee you want to find. " << endl;
                cin>>req;
                cout << "EMPLOYEE DATA." << endl;
                if (supportstaffVe.size() == 0) {
                    cout << "No data found..";
                    return -1;
                }
                for (int i = 0;i < supportstaffVe.size();i++) {
                    if (supportstaffVe[i].getempid() == req) {
                        string found = "ID :" + supportstaffVe[i].getempid() + "\nNAME : " + supportstaffVe[i].getempname() + "\nSALARY : " + to_string(supportstaffVe[i].getsalary()) + "\n";
                        cout << found;
                        return i;
                    }
                }
                cout << "No match found for " + req << endl;
                return -1;

            case 's':
                //student code here
                cout << "Enter the Roll Number of the student you want to find. " << endl;
                cin>>req;
                cout << "STUDENT DATA." << endl;
                if (stdVe.size() == 0) {
                    cout << "No data found..";
                    return -1;
                }
                for (int i = 0;i < stdVe.size();i++) {
                    if (stdVe[i].getRollNumber() == req) {
                        // string found = "ROLl NO. :" + stdVe[i].getRollNumber()+ "\nNAME : " + stdVe[i].getName() + "\nGRADE : " + stdVe[i].getGrade() +"\nPhone Number :"+ stdVe[i].getPhoneNumber()+ "\nAddress :" + stdVe[i].g +"\n" ;
                        stdVe[i].printReport();
                        return i;
                    }
                }
                cout << "No match found for " + req << endl;
                return -1;

                break;
            case 'q':
                cout << "Enter the Name of the equipment you want to find. " << endl;
                cin>>req;
                cout << "EMPLOYEE DATA." << endl;
                if (supportstaffVe.size() == 0) {
                    cout << "No data found..";
                    return -1;
                }
                for (int i = 0;i < eqpVe.size();i++) {
                    if (eqpVe[i].getName() == req) {
                        string found = "Name: " + eqpVe[i].getName() + "\nType: " + eqpVe[i].getType() + "\nQuantity: " + to_string(eqpVe[i].getQty());
                        cout << endl;
                        cout << found;
                        return i;
                    }
                }
                cout << "No match found for " + req << endl;
                return -1;

            case 'n':
                cout << "Please enter the Title of the notice, you are looking for" << endl;
                getline(cin, req);
                getline(cin,req);
                flag = true;
                for (int i = 0; i < ntVe.size() && flag;i++) {
                    if (ntVe[i].getTitle() == req) {
                        cout << "TITLE : " << ntVe[i].getTitle() << endl;
                        cout << "CONTENT : " << ntVe[i].getContent() << endl;
                        flag = false;
                        return i;
                    }
                }
                if (flag) {
                    cout << "No Notice found with " << req << endl;
                    return -1;
                }


            default:
                return -1;
                break;
            }
            return -1;
        }
        void update(char key) {

            // string updatee=find(key);
            int begin, end;
            int count;
        options:
            switch (key)
            {
            case 't': {

                count = _find('t');

                if (count >= 0) {
                    supportstaffVe.erase(supportstaffVe.begin() + count);
                    
                    create('t');
                    setuser('t');
                    setuser('E');
                    

                }
                break;
            }
              

            case 'e': {
          
                count = _find('e');

                if (count >= 0) {
                    supportstaffVe.erase(supportstaffVe.begin() + count);
                    cout << "Here" << endl;
                    create('e');
                    setuser('e');
                    setuser('E');
                }
                break;
            }

            case 's':
                //student code here
                count = _find('s');

                if (count >= 0) {
                    stdVe.erase(stdVe.begin() + count);
                    cout << "Here" << endl;
                    create('s');
                    setuser('s');
                    setuser('S');

                }
                break;

            case 'q':
            {

                count = _find('q');
                if (count >= 0) {
                    eqpVe.erase(eqpVe.begin() + count);
                    cout << "Here" << endl;
                    create('q');
                    setuser('q');
                }
                break;
            }
            case 'n': {
                count = _find('n');
                cout << "COUNT =" << count << endl;
                if (count >= 0) {
                    ntVe.erase(ntVe.begin() + count);
                    create('n');
                    setuser('n');
                }
                break;
            }

            }

        }

        void empAtt(char key) {
            int choice;
            switch (key)
            {
            case 'e':           
            for (int i = 0; i < supportstaffVe.size();i++) {
                cout << "Name : " << supportstaffVe[i].getempname() << endl;
                cout << "Id : " << supportstaffVe[i].getempid() << endl;
                cout << "Press 1 for present and 0 for absent" << endl;
                cin >> choice;
                if (choice == 0) {
                    continue;
                }
                else if (choice == 1) {
                    supportstaffVe[i].increment();
                    updateAtt(i,'e');
                }
                else {
                    cout << "Invalid entry" << endl;
                    i--;
            }
                }
            break;

            case 't':
                for (int i = 0; i < teachersVe.size();i++) {
                    cout << "Name : " << teachersVe[i].getempname() << endl;
                    cout << "Id : " << teachersVe[i].getempid() << endl;
                    cout << "Press 1 for present and 0 for absent" << endl;
                    cin >> choice;
                    if (choice == 0) {
                        continue;
                    }
                    else if (choice == 1) {
                        teachersVe[i].increment();
                        updateAtt(i, 't');
                    }
                    else {
                        cout << "Invalid entry" << endl;
                        i--;
                    }
                }
                break;
            }
        }

        void AddResult() {
            string grade; char sec;
            this->flag = false;
            cout << "Enter Class Name whose result has to be added " << endl;
            cin.ignore();
            getline(cin,grade);
            cout << " Enter Section name " << endl;
            cin >> sec;
            for (int i = 0; i < stdVe.size();i++) {
                if (stdVe[i].getGrade() == grade && stdVe[i].getSec()) {
                    cout << "STUDENT NAME : " << stdVe[i].getName() << endl;
                    stdVe[i].appendResult();
                    flag = true;
                }
            }
            if (!flag) {
                cout << " Couldn't find students for " << grade << " and " << sec << endl;
            }
            return;
        }

        void ViewResult() {
            string grade; char sec;
            flag = false;
            cout << "Enter Class Name whose result has to be displayed " << endl;
            cin.clear();
            cin.ignore();
            getline(cin, grade);
            cout << " Enter Section name " << endl;
            cin >> sec;
            for (int i = 0; i < stdVe.size();i++) {
                if (stdVe[i].getGrade() == grade && stdVe[i].getSec()) {
                    stdVe[i].dispResult();
                    flag = true;
                }
            }
            if (!flag) {
                cout << " Couldn't find students for " << grade << " and " << sec << endl;
            }
        }
        Student* stdLoginAuth() {
            string username, password;
            
            cout << "Enter your username: ";
            cin >> username;
            cout << endl;
            cout << "Enter your password: ";
            cin>>password;
            cout << endl;
            for (int i = 0; i < stdLogin.size();i++) {
                if (username == stdLogin[i].getuser() && password == stdLogin[i].getpass())
                {
                    cout << "Logged In Successfully !!" << endl;
                    for (int j = 0; j < stdVe.size();j++) {
                        cout << "ROLL NUMBER: " << stdVe[j].getRollNumber() << endl;
                        if (stdLogin[i].getId() == stdVe[j].getRollNumber()) {
                            cout << " STUDENT FOUND"<<endl;
                            return &stdVe[j];
                        }
                    }

                }

            }
            cout << "Incorrect Password. try again" << endl;
            return nullptr;
        }
        string empLoginAuth() {
            string username, password;
            cout << "Enter your username: ";
            cin>>username;
            cout << endl;
            cout << "Enter your password: ";
            cin>>password;
            cout << endl;
            for (int i = 0; i < empLogin.size();i++) {
                if (username == empLogin[i].getuser() && password == empLogin[i].getpass())
                {
                    cout << "Logged In Successfully !!" << endl;
                    return empLogin[i].getId();

                }
            }
            
            return "";
        }

        int AdminLoginAuth() {
            string username, password;

            cout << "\t\t\t\t SCHOOL \t MANAGEMENT \t SYSTEM" << endl;
                    cout << "Enter your username: ";
                    cin>>username;
                    cout << endl;
                    cout << "Enter your password: ";
                    cin>>password;
                    cout << endl;
                    for (int i = 0; i < adminLogin.size();i++) {
                        if (username == adminLogin[i].getuser() && password == adminLogin[i].getpass())
                        {
                            cout << "Logged In Successfully !!" << endl;
                            return 1;

                        }
                    }
                    cout << "Incorrect Password. try again" << endl;

        }

        void checkFeeStatus(string id) {
            for (int i = 0;i < stdVe.size();i++) {
                if (lower(stdVe[i].getRollNumber()) == lower(id)) {
                    cout << "Fee Status " << bool(stdVe[i].getFeesPaid()) << endl;
                return;
                }
             }
            cout << "Could not find data for " << id << endl;
            }

    };

    class TeacherOperations : public adminOperations
    {
    public:
        
        TeacherOperations() :adminOperations("C:\\Users\\Shaheryar\\source\\repos\\New folder\\New folder\\ConsoleApplication2\\Debug\\data.db") {

        }
        TeacherOperations(string file) :adminOperations(file) {
            //cout << "hello";
        }
        void getdetails() {
            teachersVe[0].getdetails();

        }
        void markattendance()
        {
            cout << "Enter 1 for Present and 0 for Absent" << endl;
            for (int i = 0; i < stdVe.size();i++)
            {
                cout << "Is " << stdVe[i].getName() << " present?" << endl;

                int choice;
                cin >> choice;
                
                if (choice == 1) {
                    stdVe[i].attIncrement();
                    updateAtt( i,'s');

                }
                else if (choice != 0 && choice != 1) {
                    cout << "Please Press relevant number" << endl;
                    i--;
                }
                
            }
        }
        void viewattendace()
        {
            for (int i = 0;i < stdVe.size();i++) {
                cout << "NAME :" << stdVe[i].getName() << "  Roll Number : " << stdVe[i].getRollNumber() << "  Attendance Count = " << stdVe[i].getAttendance() << endl;
            }
        }
       

    };

    class StaffOperations : public SupportStaff, public school_management
    {
    };


    class StudentOperations 
    {
    protected:
        vector <Student> students;
        //Student currentStd;
    public:
        StudentOperations(){}
        void personalDetails() {


        }
        void viewAttendance() {

        }
        void printReport() {

        }
        void feeVoucher() {

        }

    };


    class adminNavigation {
    protected:
        TeacherOperations ad;
    private:
        bool state;

    public:
        adminNavigation(TeacherOperations& sample) {
            //cout << "constructor of nav called" << endl;
            ad = sample;
            //  cout<<ad<<endl;
        }

        void noticeSection() {
            state = true;
            while (state) {
                cout << "1. Add notice" << endl;
                cout << "2. Update notice" << endl;
                cout << "3. Delete notice" << endl;
                cout << "4. View notices" << endl;
                cout << "5. Find notice" << endl;
                cout << "6. Exit" << endl;

                int choice;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                case 1: {
                    NoticeBoard newNotice("", "");
                    ad.create('n');
                    ad.newuser('n');
                    break;
                }
                case 2: {
                    ad.update('n');
                    break;
                }
                case 3: {

                    ad.del('n');
                    break;
                }
                case 4: {
                    cout << "Viewing all notices:" << endl;
                    ad.read('n');
                    break;
                }
                case 5:
                    ad._find('n');
                    break;
                case 6:
                    state = false;
                    break;
                }
            }
        }

        void  studentSection() {
            int choice;

            do {
                cout << "STUDENT SECTION" << endl;
                cout << "---------------------------" << endl;
                cout << "1. Add Student" << endl;
                cout << "2. View All Students" << endl;
                cout << "3. Check Fee Status" << endl;
                cout << "4. VIew Student Attendance" << endl;
                cout << "5. Update Student" << endl;
                cout << "6. Search Student" << endl;
                cout << "7. Mark Student Attendance" << endl;
                cout << "0. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    ad.create('s');
                    ad.newuser('s');
                    ad.newuser('S');
                    break;

                case 2:
                    ad.read('s');
                    break;
                case 3: {
                    string rollNumber;
                    cout << "Enter roll number of student to check fee status: ";
                    cin >> rollNumber;
                    cout << "1 refers to fee paid and 0 refers to fee not paid" << endl;
                    ad.checkFeeStatus(rollNumber);
                    break;
                }
               
                case 4:
                    ad.viewattendace();
                    break;
                case 5: {

                    ad.update('s');
                    break;
                }
               case 6:
                    ad._find('s');
                    break;
               case 7:
                   ad.markattendance();
                   break;
                case 0:
                    cout << "Exit" << endl;
                    break;
                    

                }

                cout << endl;
            } while (choice != 0);
        }

        void equipmentSection() {
            state = true;
            while (state)
            {


                cout << "1. Add equipment" << endl;
                cout << "2. Update equipment" << endl;
                cout << "3. Delete equipment" << endl;
                cout << "4. View equipment" << endl;
                cout << "5. Find equipment" << endl;
                cout << "0. Go back" << endl;
                // break;
                int choice;
                cin >> choice;
                // adminOperations eqp;
                switch (choice) {
                case 0:
                    state = false;
                    break;
                case(1):
                    // equipmentList[0].add();
                    // (*ad).create('q');
                    (ad).create('q');
                    ad.newuser('q');
                    // equipmentSection();
                    break;
                case(2):
                    // equipmentList[0].update(equipmentList);
                    // (*ad). update('q');
                    (ad).update('q');
                    break;
                case(3):
                    // equipmentList[0].remove(equipmentList);
                    // (*ad). del('q');
                    (ad).del('q');
                    break;
                case(4):
                    // (*ad). read('q');
                    (ad).read('q');
                    // equipmentList[0].view(equipmentList);
                    break;
                case(5):
                    //  cout<< (*ad)._find('q') <<endl;
                    cout << (ad)._find('q') << endl;
                    break;

                }
            }
        }

        /*void venueSection() {
            venue playground(36000, 100);
            venue library(70000, 250);
            venue audotorium(66777, 90);
            venue gymnassium(30000, 60);
        }*/

        void employeeSection() {
            system("cls");
            int choice;
            bool status = true;
            while (status) {
            cout << "Please enter 1 for Support staff and 2 for Teachers " << endl;
            cin >> choice;
                switch (choice) {
                case 1:{
                    cout << " Support Staff SECTION " << endl;
                    cout << " *************************** " << endl;
                    cout << "1. View all employees " << endl;
                    cout << "2. Search employee " << endl;
                    cout << "3. Update employee details" << endl;
                    cout << "4. Add Employee" << endl;
                    //cout << "5. Delete employee " << endl;
                    cout << "5. Mark employee attendance" << endl;
                    cout << "0. Go back " << endl;
                    cout << "Enter the serial number to perform the corresponding operation " << endl;

                    int nav;
                    int i;

                    cin >> nav;
                    bool repeat = false;
                    // adminOperations em;

                    switch (nav) {
                    case 0:
                        return;

                        break;
                    case 1:
                        // viewEmp()
                        (ad).read('e');
                        // cout<< "Employees detail will be updated soon "<<endl;
                        break;

                    case 2:
                        //searchEmp
                        i = ad._find('e');
                        break;

                    case 3:
                        //updateEmp
                        ad.update('e');
                        break;

                    case 4:
                        cout << "NOTE : EMPLOYEE ID should start from S." << endl;
                        ad.create('e');
                        ad.newuser('e');
                        ad.newuser('E');
                        break;

                    /*case 5:
                        //delEmp

                        cout << " coming soon... " << endl;
                        break;*/
                    case 5:
                        //empAtt
                        ad.empAtt('e');

                        break;



                    default:
                        cout << "Please enter the correct number " << endl;
                        repeat = true;
                        break;
                    }
                    break;
                }
            case 2: {
                cout << " Teacher SECTION " << endl;
                cout << " *************************** " << endl;
                cout << "1. View all Teachers" << endl;
                cout << "2. Search Teacher " << endl;
                cout << "3. Update Teacher details" << endl;
                cout << "4. Add Teacher" << endl;
               // cout << "5. Delete Teavher " << endl;
                cout << "5. Mark Teacher attendance" << endl;
                cout << "0. Go back " << endl;
                cout << "Enter the serial number to perform the corresponding operation " << endl;

                int nav;
                int i;

                cin >> nav;
                bool repeat = false;
                // adminOperations em;

                switch (nav) {
                case 0:
                    return;

                    break;
                case 1:
                    // viewEmp()
                    (ad).read('t');
                    // cout<< "Employees detail will be updated soon "<<endl;
                    break;

                case 2:
                    //searchEmp
                    i = ad._find('t');
                    break;

                case 3:
                    //updateEmp
                    ad.update('t');
                    break;

                case 4:
                    cout << "NOTE : EMPLOYEE ID should start from T." << endl;
                    ad.create('t');
                    ad.newuser('e');
                    ad.newuser('T');
                    break;

                /*case 5:
                    //delEmp

                    cout << " coming soon... " << endl;
                    break;*/
                case 5:
                    //empAtt
                    ad.empAtt('t');

                    break;



                default:
                    cout << "Please enter the correct number " << endl;
                    repeat = true;
                    break;
                }
                break;
                }
            default:
                cout << " Please enter correct number " << endl;
                break;
            }
                
            }

        }

        void mainMenu() {
            // system("cls");
            
            while (true) {
                cout << "*** ADMIN SECTION *** " << endl;
                cout << "1 . EMPLOYEE DETAILS " << endl;
                cout << "2 . STUDENT DETAILS " << endl;
                cout << "3 . EQUIPMENT DETAILS  " << endl;
                //cout << "4 . VENUE DETAILS " << endl;
                //cout << "5 . TRANSPORT DETAILS" << endl;
                cout << "4 . NOTICES" << endl;
                cout << "0 . Go Back" << endl;

                cout << "Enter the serial number of the section you want to go to... " << endl;
                int nav;
                bool repeat = false;
                cin >> nav;
            options:
                switch (nav) {
                case 0:
                    
                    return;
                    break;
                case 1:
                    employeeSection();
                    break;

                case 2:
                    //studentSection
                    studentSection();
                    break;

                case 3:
                    equipmentSection();
                    break;

                /*case 4:
                    venueSection();
                    break;

                case 5:
                    //transportSection
                    break;*/

                case 4:
                    //noticeSection
                    noticeSection();
                    break;

                default:
                    repeat = true;
                    break;


                }
                if (repeat) {
                    cout << "Please enter the correct number " << endl;
                }
            }
        }
    };

    class teachernavigation {
    private:
        Teacher teach;
        TeacherOperations t;
    public:

        teachernavigation(TeacherOperations& sample, string id) {
            t = sample;
            for (int i = 0; i < t.getTeVe().size();i++) {
                if (t.getTeVe()[i].getempid() == id) {
                    // assign teach the vector of t;
                    teach = t.getTeVe()[i];
                    cout << " assigned"<<endl;
                }

                // perform this task in teacher operations

            }
        }
        void teacher()
        {
            bool flag = true;
            while (flag) {



                cout << "\t\t\t\t SCHOOL \t MANAGEMENT \t SYSTEM" << endl;
                cout << "Teacher Section" << endl;
                cout << "****************************" << endl;
                cout << "1. View personal details" << endl;
                cout << "2. Mark Student Attendance" << endl;
                cout << "3. Check Student Attendance" << endl;
                cout << "4. Upload subject Marks" << endl;
                cout << "5. Check subject Marks" << endl;
                //cout << "6. Book Auditorium" << endl;
                cout << "6. Check my own Attendance" << endl;
                cout << "7. Check salary" << endl;
                cout << "8. Go back" << endl;

                int choice;
                cin >> choice;

                switch (choice)
                {
                case(1):
                    /*teacher object.getdetails();*/
                    teach.getdetails();
                    break;
                case(2):
                    /*teacher object.markattendance();*/
                    t.markattendance();
                    break;
                case(3):
                    /*teacher object.viewattendance();*/
                    t.viewattendace();
                    break;
                case(4):
                    t.AddResult();

                    break;
                case(5):
                    /*teacher object.checkmarks();*/
                    t.ViewResult();

                    break;
                //case(6):
                    /*teacher object.bookauditorium();*/
                    // t.bookauditorium("Eraj");
                  break;
                case(6):
                    /*teacher object.getattendance();*/
                     cout<<"Your attendance : "<<teach.getattendance()<< endl;

                    break;
                case(7):
                    /*teacher object.getsalary();*/
                    // t.getsalary();
                    cout << "Your salary : " << teach.getsalary() << endl;

                    break;
                case(8):
                    flag = false;
                    return;
                    //			exit code and go to login page
                    break;
                }
            }
        }
    };

    class staffnavigation : school_management{
    private:
        string id;
        SupportStaff s;
    public:
        staffnavigation(string id) {
            //cout << "constructor of staff member nav called" << endl;
            for (int i = 0; i < supportstaffVe.size();i++) {
                if (supportstaffVe[i].getempid() == id) {
                    s = supportstaffVe[i];
                }
            }
        }
        void supstaff()
        {
            while (true) {
                cout << "\t\t\t\t SCHOOL \t MANAGEMENT \t SYSTEM" << endl;
                cout << "Staff Memeber Section" << endl;
                cout << "****************************" << endl;
                cout << "1. View personal details" << endl;
                cout << "2. Check Salary" << endl;
                cout << "3. Check my own attendance" << endl;
                cout << "4. Go back" << endl;

                int choice;
                cin >> choice;

                switch (choice)
                {
                case(1):
                    s.getdetails();
                    break;
                    /*object of support staff.getdetails();*/
                case(2):
                    cout << "Salary :" << s.getsalary() << endl;;
                    /*object of support staff.getsalary();*/
                    break;
                case(3):
                    cout << "ATTENDANCE : " << s.getattendance() << endl;
                    /*object of support staff.getattendance();*/
                    break;
                case(4):
                    return;
                    //			exit code and go to login page
                    break;
                }
            }
        }
    };

    class Studentnavigation
    {
    private:
        Student* s;
        TeacherOperations notice;
        //Student s;
    public:
        Studentnavigation() {}
        Studentnavigation(Student& sample, TeacherOperations t) {
            s = &sample;
            notice = t;
        }
        void student() {
            cout << "________________________________________________________________________________________________________________________" << endl;
            cout << endl;
            cout << "\t\t\t\t SCHOOL \t MANAGEMENT \t SYSTEM" << endl;
            cout << "________________________________________________________________________________________________________________________" << endl;
            cout << endl;
            while (true) {
                cout << endl;

                cout << "****************************" << endl;
                cout << "Student Section" << endl;
                cout << "****************************" << endl;
                cout << "1. View Personal Details" << endl;
                cout << "2. View Attendance" << endl;
                cout << "3. View Notices" << endl;
                cout << "4. View Result" << endl;
                cout << "0. GO back" << endl;

                int choice;
                cin >> choice;

                switch (choice)
                {
                case 0:
                    return;
                case(1):
                    (*s).printReport();
                    break;
                case(2):
                    // s.viewattendance("TE-0001");
                    
                   cout << "Attendance count = " << (*s).getAttendance() << endl;
            
                    break;

                case(3):
                    (notice).read('n');
                    break;
                case 4:
                    (*s).dispResult();

                    break;
                }
            }

        }
    };

}
int main() {

    management::TeacherOperations dataObj("C:\\Users\\hp\\Downloads\\SCHOOL_MGT_SYSTEM\\SCHOOL_MGT_SYSTEM\\ConsoleApplication2\\Debug\\data.db");
    dataObj.viewCredentials('E'); dataObj.viewCredentials('n');
    dataObj.viewCredentials('T'); dataObj.viewCredentials('e');
    dataObj.viewCredentials('s'); dataObj.viewCredentials('S');
    dataObj.viewCredentials('a'); dataObj.viewCredentials('q');
    //char choice;
        // system("cls");
    bool state = true;
    string _id;
    management::Student* std;
    while (state){
        cout << "Enter 1 for Admin, " << endl << "2 for Employee, " << endl<< "3 for student " << endl;
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        if (dataObj.AdminLoginAuth() == 1) {
            management::adminNavigation n1(dataObj);
            int flag = 1;

            while (flag) {
                n1.mainMenu();
                cout << "Enter 0 to exit or any other number to continue.." << endl;
                cin >> flag;
                if (!flag) {
                    cout << "To confirm exiting enter 0 again " << endl;
                    cin >> flag;
                }
            }
            state   = false;
        }
        break;

    case 2:
        _id = dataObj.empLoginAuth();
        if (_id[0] == 'T' || _id[0] == 't') {
            management::teachernavigation empt(dataObj, _id);
            cout << "TEACHER ID " << _id << endl;
            empt.teacher();
            state = false;
            break;

        }
        else if (_id[0]== 'S' || _id[0]=='s') {
            cout<< _id << endl;
            management::staffnavigation s(_id);
            s.supstaff();
            state = false;
            break;
        }
        else if (_id == "") {
            cout << " please try again" << endl;
        }
        break;

    case 3:
        std = dataObj.stdLoginAuth();
        if (std) {
            management::Studentnavigation s1(*(std),dataObj);
            s1.student();
        }
        state = false;
        break;
    }
}

    return 0;
}
