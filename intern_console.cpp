#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

const string fname = "interns_details.txt";

class Intern{

    private:
        string name;
        string email;
        string dob;
    
    public:
        Intern(const string& n, const string& e, const string& d):
        name(n),email(e),dob(d){}

        string getName() const{
            return name;
        }

        string getEmail() const {
            return email;
        }

        string getDob() const{
            return dob;
        }

        void display() const{
            cout<<"Name: "<<name<<endl<<"Email: "<<email<<endl<<"DOB: "<<dob<<endl;
        }
};

class InternManager{

    private:
        vector<Intern> interns;
        string file_path = "";

        void loadInterns(){
            //from file to vector
            interns.clear();

            ifstream ifile(file_path);

            if(!ifile.is_open()){
                return;
            }

            string line;

            while(getline(ifile,line)){
                stringstream ss(line);
                string name,  email,  dob;

                if(getline(ss,name,',')){
                    if(getline(ss,email,',')){
                        if(getline(ss,dob)){
                            interns.emplace_back(name,email,dob);
                        }
                    }
                }
            }
             ifile.close();
        }

        void saveInterns() const{

            //from vector to file

            ofstream ofile(file_path);

            if(!ofile.is_open()){
                cerr<<"Error: Could not open "<<file_path<<" for writing.\n";
                return;
            }

            for(const auto& intern : interns){
                ofile<<intern.getName()<<","<<intern.getEmail()<<","<<intern.getDob()<<endl;
            }

            ofile.close();
        }

    public:
        InternManager(string path): file_path(path){
            loadInterns();
        }

        void addIntern(){
            cout<<"\n===== Add New Intern =====\n";
            string n,e,dob;
            cout<<"Enter Name: ";
            getline(cin,n);
            cout<<"Enter Email: ";
            getline(cin,e);
            cout<<"Enter Date of Birth(DD/MM/YYYY): ";
            getline(cin,dob);

            interns.emplace_back(n,e,dob);

            saveInterns();

            cout<<"Intern "<<n<<" added successfully."<<endl;
        }

        void showInternDetails() const{
            cout<<"\n===== Show Intern Details =====\n";

            string srchName;
            cout<<"Enter name of Intern : ";
            getline(cin,srchName);

            bool found = false;

            for(const auto& intern : interns){
                if(intern.getName() == srchName){
                    cout<<"\nDetails for "<<srchName<<":\n";
                    intern.display();
                    found = true;
                }
            }

            if(!found){
                cout<<"Intern "<<srchName<<" not found.\n";
            }
        }

        void deleteIntern(){
            cout<<"===== Delete Intern Record =====\n";

            string delName;
            cout<<"Enter Name of Intern to delete: ";
            getline(cin,delName);

            int oldSize = interns.size();

            auto is_intern_to_delete = [&](const Intern& intern){
                return intern.getName() == delName;
            };

            auto new_end_it = remove_if(interns.begin(),interns.end(),is_intern_to_delete);
         
            interns.erase(new_end_it,interns.end());

            if(interns.size()<oldSize){
                saveInterns();
                cout<<"Intern "<<delName<<" deleted successfully.\n";
            }
            else{
                cout<<"Intern "<<delName<<" not found.\n";
            }
        }

        void listAllInterns() const{

            if(interns.empty()){
                cout<<"\nNo interns currently in the system.\n";
                return;
            }

            cout<<"===== Interns =====\n";
            for(const auto& intern : interns){
                intern.display();
                cout<<"=============================\n";
            }
        }
};

void dispplayMenu(){

    cout<<"\n===== Intern Management System =====\n";
    cout<<"1. Add Intern\n"
        <<"2. Show Intern\n"
        <<"3. Delete Intern\n"
        <<"4. List All Interns\n"
        <<"5. Exit\n"
        <<"Enter your choice : ";
}

int main(){

    InternManager mngr(fname);
    int choice;

    do{
        dispplayMenu();
        cin>>choice;
        if(cin.fail()){
            cout<<"Invalid Input.Please enter a number."<<endl;
            cin.clear();
            cin.ignore(100,'\n');
            choice=0;
            continue;
        }

        switch (choice){
            
            case 1: cin.ignore();
                    mngr.addIntern();
                    break;

            case 2: cin.ignore();
                    mngr.showInternDetails();
                    break;

            case 3: cin.ignore();
                    mngr.deleteIntern();
                    break;

            case 4: cin.ignore();
                    mngr.listAllInterns();
                    break;      
            case 5:
                    cout<<"Exiting ... \nBye!\n";
                    break;

            default:cout<<"Invalid choice. Please try again";
                    break;
        }
        
    }while(choice != 5);
    return 0;
}