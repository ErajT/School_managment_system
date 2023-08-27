#include <iostream>
#include<vector>
using namespace std;
class employee{
    public:
    string id;
    string name;
    vector <employee> static e;
    employee(string id,string name){
        this->id=id;
        this->name=name;
    }
    void insert(){
        e.push_back(employee(id,name));
    }
};
class myclass:public employee{
    vector <employee> e1;
    public:
    void i(string i,string n){
        e1.push_back(employee(i,n));
    }
    void display(){
        for(int i=0;i<(e.size());i++){
            cout << e[i];
        }
    }
};
int main(){
   myclass obj;
   obj.i("123","Muneer");
   obj.insert();
   obj.display();
   

}