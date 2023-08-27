#include<iostream>
#include<string>
#include <vector>


// #include<D:\OOP PPROJECT SMS\Admin - Copy.h>
using namespace std;

namespace Hashir{

class employee
{
	protected:
		string empid;
		string empname;
		float salary;
		int attendance;
	public:
		employee(){}
		employee(string eid,string en,  float s)
		{
			empid = eid;
			empname = en;
			salary = s;
		}
		float getsalary()
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
class SupportStaff: public employee
{
	public:
		SupportStaff( string eid,string en, float s):employee(eid,en,s)
		{		}
};

class teacher: public employee
{
	private:
		string subject;
		int no_ofclasses;
  public:
  teacher(string eid, string en, float s,string subject, int no_ofclasses):employee(eid,en,s){
this->subject = subject;
this-> no_ofclasses = no_ofclasses;

  }
};

class equipment {
  string name;
  string type;
  int quantity;
public:

  
  equipment(string name, string type, int quantity){
    this->name = name;
    this->type = type;
    this->quantity = quantity;
  }
string getName(){
    return name;
  }
string getType(){
    return type;
  }
int getQty(){
    return quantity;
  }
};

class super{
protected :
vector<employee>  empVe;
vector<equipment>  eqpVe;

public:
super(){
  // cout<<"Super has been called"<<endl;
  empVe = { employee("TE-0001","Mr XYZ",1000.50), employee("TE-0002","Mr ABC",1000.50),employee("TE-0003","Mr DFG",1000.50)};
  eqpVe = {equipment("PC", "Electronic", 47),Hashir::equipment("Projector", "Electronic", 7),Hashir::equipment("Desks", "Furniture", 80),Hashir::equipment("White Board", "Furniture", 20)};  
}
};

    class adminOperations: public super {
      
      public:
      void  create(char key){ 
     switch (key)
     {  
      case 'e':{
                string _id ; 
                string _name ;
                float salary=0.00;
                cout<<"ENTER EMPLOYEE CREDENTIALS "<<endl;
                cout<<"Enter EMPLOYEE Id"<<endl;
                cin>>_id;
                cout<<"Enter Employee Name"<<endl;
                cin>>_name;
                cout<<"Enter Employee's salary"<<endl;
                cin>>salary;
                // for(int){
                  // if(e.getId()==_id){
                  //   cout<<"Employee with Id "+_id+" already exists. Please enter a unique ID for a new employee"<<endl;
                  //   break;
                  // }
                // }
                empVe.push_back(employee(_id,_name,salary));
                cout<<"Data Updated succesfully!!"<<endl;
                break;
      }
              
            case 's':
            //student code here
            break;
            case 'q':
                {
                string _type ; 
                string _name ;
                int _qty;
                cout<<"ENTER EQUIPMENT CREDENTIALS "<<endl;
                cout<<"Enter Equipment Name"<<endl;
                cin>>_name;
                cout<<"Enter Equipment Type"<<endl;
                cin>>_type;
                cout<<"Enter Equipment Quantity"<<endl;
                cin>>_qty;
                for(equipment &e:eqpVe){
                  if(e.getName()==_name){
                    cout<<"Equipment with name "+_name+" already exists. Please enter a new equipment "<<endl;
                  }
                }
                eqpVe.push_back(equipment(_name,_type,_qty));
                cout<<"Data updated succesfully!!"<<endl;
                break;
      }
        } 
       }
    void  read(char key){  
        switch (key){
            case 'e':
                cout<<"EMPLOYEE DATA."<<endl;
                if(empVe.size()==0){
                  cout<<"No data found..";
                }
              for(int i=0;i<empVe.size();i++){
                cout<<"ID : "<< empVe[i].getempid()<< " NAME : " <<empVe[i].getempname()<< " SALARY : " <<empVe[i].getsalary()<< endl ;
              }       
              break;
            case 's':
            //student code here
            break;
            case 'q':
                if(empVe.size()==0){
                  cout<<"No data found..";
                }
              for (int i =0; i<eqpVe.size(); i++) {
                cout << "Name: " << eqpVe[i].getName() << endl;
                cout << "Type: " << eqpVe[i].getType() << endl;
                cout << "Quantity: " << eqpVe[i].getQty() << endl;
                cout << endl;
              }
              break;
        } 
        }
    void del(char key){
//to be decided
      }
    int _find(char key){  
      string req;
    options:
      switch (key){
            case 'e':
                cout<< "Enter the ID of the employee you want to find. "<<endl;
                cin>>req;
                cout<<"EMPLOYEE DATA."<<endl;
                if(empVe.size()==0){
                  cout<< "No data found..";
                  return -1;
                }
              for(int i=0;i<empVe.size();i++){
                if(empVe[i].getempid() == req){
                  string found = "ID :" + empVe[i].getempid()+ "\nNAME : " + empVe[i].getempname() + "\nSALARY : " + to_string(empVe[i].getsalary()) + "\n" ;
                  cout<< found;
                  return i;
                }
              }  
              cout<<"No match found for " + req<<endl;     
              return -1;
              
            case 's':
            //student code here
            break;
            case 'q':
                cout<< "Enter the Name of the equipment you want to find. "<<endl;
                cin>>req;
                cout<<"EMPLOYEE DATA."<<endl;
                if(empVe.size()==0){
                  cout<<"No data found..";
                  return -1; 
                }
              for(int i=0;i<eqpVe.size();i++){
                if(eqpVe[i].getName() == req){
                  string found = "Name: " + eqpVe[i].getName()+ "\nType: " + eqpVe[i].getType() + "\nQuantity: " +  to_string(eqpVe[i].getQty()) ;
                cout << endl;
                  cout<< found;
                  return i;
                }
              }  
              cout<< "No match found for " + req<<endl;     
              return -1;
              
              default:
                return -1;
                break;
        }  
        return -1;
      }
    void  update(char key){  

      // string updatee=find(key);
      int begin,end;
      int count ;
      options:
      switch (key)
     {
      
      case 'e':{
              //   string _id; 
              //   cout<< "Enter the ID of the employee you want to update. "<<endl;
              //   cin>>_id;
              //   cout<<"EMPLOYEE DATA."<<endl;
              //   if(empVe.size()==0){
              //     cout<<"No data found..";
              //   }
              //   bool loop = true;
              // for(int i=0;i<empVe.size()&&loop;i++){
              //   if(empVe[i].getId() == _id){
              //     string found = "ID :" + empVe[i].getId()+ "\nNAME : " + empVe[i].getName() + "\nSALARY : " + to_string(empVe[i].getSalary() ) + "\n";
              //     cout<<found;
                  
              //   }
              //   else{
              //     cout<<"COULD NOT FIND "+_id<<endl;
              //     loop =false;
              //   }
              // }  
              count=_find('e');
              
              if (count>=0){
                  empVe.erase(empVe.begin(),empVe.begin()+count);
                  cout<<"Here"<<endl;
                  create('e');
                
              }
                break;
      }
              
            case 's':
            //student code here
            break;
            case 'q':
                {
                // string _id; 
              //   cout<< "Enter the Name of the equipment you want to update. "<<endl;
              //   cin>>_id;
              //   cout<<"EMPLOYEE DATA."<<endl;
              //   if(eqpVe.size()==0){
              //     cout<<"No data found..";
              //     break;
              //   }
              //   int count =0;
              
              // for(int i=0;i<eqpVe.size();i++){
              //   if(eqpVe[i].getName() == _id){
              //     string found = "NAME :" + eqpVe[i].getName()+ "\nTYPE : " + eqpVe[i].getType() + "\nQUANTITY : " + to_string(empVe[i].getQty() ) + "\n";
              //     cout<<found;
              //     count=i;
              //   }
              // }
              //   eqpVe.erase(eqpVe.begin(),eqpVe.begin()+(count-1));
              //   // int i = (int)index;
              //   create('q');
              //   cout<<"Updated Name is "<<eqpVe[eqpVe.size()-1].getName()<<endl;
                
                count=_find('q');
              if (count>=0){
                  empVe.erase(empVe.begin(),empVe.begin()+count);
                  cout<<"Here"<<endl;
                  create('q');
                
              }
                break;
      }
        } 
      
      }
    };

class navigation{  


public:
navigation(){
  
}
void equipmentSection(){
    cout << "1. Add equipment" << endl;
    cout << "2. Update equipment" << endl;
    cout << "3. Delete equipment" << endl;
    cout << "4. View equipment" << endl;
    cout << "5. Find equipment" << endl;
    cout << "0. Go back" << endl;
    // break;
    int choice;
    cin >> choice;
    adminOperations eqp;
    switch (choice) {
      case 0:
        mainMenu();
        break;
      case(1):
        // equipmentList[0].add();
        eqp.create('q');
        break;
      case(2):
        // equipmentList[0].update(equipmentList);
        eqp. update('q');
        break;
      case(3):
        // equipmentList[0].remove(equipmentList);
        eqp. del('q');
        break;
      case(4):
        eqp. read('q');
        // equipmentList[0].view(equipmentList);
        break;
      case(5):
     cout<< eqp._find('q') <<endl;
        break;
    }

}


void employeeSection(){
    system("cls");
    cout << " EMPLOYEE SECTION " << endl;
    cout << " *************************** "<<endl;
    cout<< "1. View all employees " << endl;
    cout<< "2. Search employee " << endl;
    cout<< "3. Update employee details" << endl;
    cout<< "4. Add Employee" << endl;
    cout<< "5. Delete employee " << endl;
    cout<< "6. Mark employee attendance" << endl;
    cout<< "0. Go back " << endl;
    cout<< "Enter the serial number to perform the corresponding operation "<< endl;

    int nav;
    int i;
cin>> nav;
bool repeat = false;
adminOperations em;
options:
    switch (nav){
        case 0:
        mainMenu();
        break;
        case 1:
        // viewEmp()
        em.read('e');
        // cout<< "Employees detail will be updated soon "<<endl;
        break;

        case 2:
        //searchEmp
        i =em._find('e');
        break;
        
        case 3:
        //updateEmp
        em.update('e');
        break;

        case 4:
        em.create('e');
        break;

        case 5:
        //delEmp
        
        cout<< " coming soon... "<<endl;
        break;
        case 6:
        //empAtt
        cout<< " coming soon... "<<endl;
        
        break;



        default:
        cout<<"Please enter the correct number "<< endl;
        repeat = true;
        break;
}
cout<<"Enter 1 to go back to the Employee details section or else press any other number...  "<<endl;
cin>>nav;
if(nav == 1){
    repeat = true;
}

if (repeat){

    employeeSection();
}
}

void mainMenu(){
    system("cls");

    cout<<"*** ADMIN SECTION *** " << endl;
    cout<< "1 . EMPLOYEE DETAILS " <<endl;
    cout<< "2 . STUDENT DETAILS " <<endl;
    cout<< "3 . EQUIPMENT DETAILS  " <<endl;
    cout<< "4 . VENUE DETAILS " <<endl;
    cout<< "5 . DEPARTMENT DETAILS" <<endl;
    cout<< "6 . TRANSPORT DETAILS" <<endl;
    cout<< "7 . NOTICES" <<endl;
    cout<< "8 . RESULTS" <<endl;
    cout<< "0 . Go Back" <<endl;

cout<< "Enter the serial number of the section  you want to go to... "<< endl;
int nav;
bool repeat = false;
cin>> nav;
options:
    switch (nav){
        case 0:
            break;
        case 1:
        employeeSection();
        break;

        case 2:
        //studentSection
        break;
        
        case 3:
        equipmentSection();
        break;

        case 4:
        //venueSection
        break;

        case 5:
        //deptSection
        break;

        case 6:
        //transportSection
        break;

        case 7:
        //noticeSection
        break;

        case 8:
        //resultSection
        break;

        default:
        repeat = true;
        break;
        

    }
    if (repeat){
    cout<<"Please enter the correct number "<< endl;
//this_thread::sleep_for(chrono::seconds(10));    // _sleep(50);
    mainMenu();
}
}
};


}
int main(){
    
    // vector< Admin> adminVe;
    //  Admin ad("abc","lkx");
    // adminVe.push_back( Admin("AD-0001","John Smith"));
    // adminVe.push_back( Admin("AD-0002","Micheal Steve"));
    // cout<< "Press any key to proceed";
    // string x;
    // cin>>x ;
    //     for(int i =0;i<=adminVe.size();i++){
    //     cout<< "ID : "<< adminVe[i].getId() << endl;
    //     cout<< "NAME : "<< adminVe[i].getName() << endl;

    // }
   
    
    system("cls");
    int flag =1;
    while(flag){
    Hashir::navigation n1;
    n1.mainMenu();
    cout<< "Enter 0 to exit or any other number to continue.."<< endl;
    cin >> flag;
    if(!flag){
        cout<< "To confirm exiting enter 0 again "<<endl;
        cin>>flag;
    }
    }
    return 0;
}
