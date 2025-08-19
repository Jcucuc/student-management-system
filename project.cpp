#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

/////////////////////////////////////////////////////////////////
//////////  ------  ( Student Management System )  ------  /////

class Student {
    private:
        int Student_Id;
        string Student_Name;
        int Age;
        double Gpa;
    public:
    Student() {
        cout << " Please Enter The Student ID : ";
        cin >> Student_Id;


        cout << "Please Enter The Student Name : ";
        cin.ignore();
        getline(cin, Student_Name);


        cout << "Please Enter The Age : ";
        cin >> Age;

        cout << "Please Enter The Gpa : ";
        cin >> Gpa;
        cout << endl;
    }

    Student(int id, string name, int age, double gpa) {
        Student_Id = id;
        Student_Name = name;
        Age = age;
        Gpa = gpa;
    }

        [[nodiscard]] string getstudent_name() const {
            return Student_Name;
        }

        [[nodiscard]] int get_age() const {
            return Age;
        }

        [[nodiscard]] double get_gpa() const {
            return Gpa;
        }

        void Show_Info() {
        cout<<"Student ID : "<<Student_Id<<"\t"<<" Student Name : "<<Student_Name<<endl;
        cout<<"Age : "<<Age<<"\t"<<" GPA : "<<Gpa<<endl;
    }

    void update_Info(string name , int age, double gpa) {
        Student_Name = name;
        Age = age;
        Gpa = gpa;
        cout<<"Inf Updated successfully"<<endl;
    }

    int get_Student_ID() {
        return Student_Id;
    }

};
class Course {
private:
    int Course_Id;
    string Course_Title;
    int Max_Student;
    vector<int> Enrolled_Student_IDC;
    queue<int >waiting_list;
public:
    Course() {
        cout<<"Please Enter The Course ID : ";
        cin>>Course_Id;
        cout<<"Please Enter The Course Name : ";
        cin.ignore();
        getline(cin, Course_Title);

        cout<<"Please Enter The Max_Student : ";
        cin>>Max_Student;
    }

    void Show_Info() {
        cout<<"Course ID : "<<Course_Id<<"\t"<<"Course Title : "<<Course_Title<<endl;
        cout<<"Max Student : "<<Max_Student<<endl;
        //print queue//
        cout<<"Enrolled Students :";
        for (auto id:Enrolled_Student_IDC) cout<<id<<" ";
            cout<<endl;
        cout<<"Waiting list : ";
        queue<int> temp=waiting_list;//to print with out delete
        while (!temp.empty()) {
            cout<<temp.front()<<" ";
            temp.pop();
        }
        cout<<endl;


    }

    void Enroll_Student(int Stud_Id) {
        if (Enrolled_Student_IDC.size() < Max_Student) {
            Enrolled_Student_IDC.push_back(Stud_Id);
            cout<<"Student "<<Stud_Id<<" Enrolled in "<<Course_Title<<endl;
        }else {
            waiting_list.push(Stud_Id);
            cout<<"Course is full !Student : "<<Stud_Id<<"Added to waiting list for course"<<Course_Title<<endl;
        }

    }

    void Remove_Student(int Stud_id) {
        auto it=find(Enrolled_Student_IDC.begin(), Enrolled_Student_IDC.end(), Stud_id);
        if (it!=Enrolled_Student_IDC.end()) {
            Enrolled_Student_IDC.erase(it);
            cout<<"Student with ID : "<<Stud_id<<"removed from course"<<Course_Title<<endl;

        if (!waiting_list.empty()) {
            int Next_Student_id=waiting_list.front();
            waiting_list.pop();
            Enrolled_Student_IDC.push_back(Next_Student_id);
            cout<<"Student"<<Next_Student_id<<" removed from waiting list to course"<<Course_Title<<endl;
        }
    }else {
        cout<<"Student with ID :"<<Stud_id<<" Not found in this course "<<Course_Title<<endl;
    }

    }

    int get_Course_ID() {
        return Course_Id;
    }
};
class System_Manager {
private:
    vector<Student> Students;
    vector<Course> Courses;

public:
    void Add_Student(Student s) {
        Students.push_back(s);
    }

    void Add_Course(Course c) {
        Courses.push_back(c);
    }

    void Show_Students() {
        for (auto &is:Students ){
            is.Show_Info();
        }
    }

    void Show_Courses() {
        for (auto &ic:Courses) {
            ic.Show_Info();
        }
    }

    void Remove_StudentCourse(int Studentid,int Courseid) {
        for (auto &c:Courses) {
            if (c.get_Course_ID()==Courseid) {
                c.Remove_Student(Studentid);
                return;
            }
        }
        cout<<"Course not found"<<endl;

    }
    void Enroll_StudentCourse(int Studentid,int Courseid) {
            for (auto &c:Courses) {
                if (c.get_Course_ID()==Courseid) {
                    c.Enroll_Student(Studentid);
                    return;
                }
            }
        cout<<"Course not found"<<endl;
    }
    void Save_Students() {
    ofstream output("Student_file.txt");
        for (auto &s : Students) {
            output<<s.get_Student_ID()<<","
            <<s.getstudent_name()<<","
            <<s.get_age()<<","
            <<s.get_gpa()<<endl;
        }
        output.close();
        cout<<"Student saved successfully"<<endl;
    }
    void Load_Students() {
        ifstream input("Student_file.txt");
        if (!input) {
            cout<<" Student File not found"<<endl;
            return;
        }
        Students.clear();
        string line;
        while (getline(input, line)) {
            stringstream ss(line);
            string token;
            int id, age;
            double gpa;
            string name;

            getline(ss, token, ','); id = stoi(token);
            getline(ss, name, ',');
            getline(ss, token, ','); age = stoi(token);
            getline(ss, token, ','); gpa = stod(token);

            Student s(id, name, age, gpa);
            Students.push_back(s);
        }
        input.close();
        for (auto &s : Students) {
            s.Show_Info();
        }

        cout<<"Student  Loaded successfully"<<endl;
    }
    void Search_Studentsby_ID(int id) {
        for (auto &c:Students) {
            if (c.get_Student_ID()==id) {
                cout<<"Student found "<<endl;
                c.Show_Info();
                return;
            }
        }
        cout<<" Sorry Student with id : "<<id<<"Not Found"<<endl;
    }

};

int main() {

    System_Manager sm;
    int Choice;
    while (true) {
        cout<<"==== Student Management System ===="<<endl;
        cout<<"1. Add Student"<<endl;
        cout<<"2. Add Course"<<endl;
        cout<<"3. Show Students"<<endl;
        cout<<"4. Show Courses"<<endl;
        cout<<"5. Enroll Student in Course"<<endl;
        cout<<"6. Remove Student from Course"<<endl;
        cout<<"7. Save Students"<<endl;
        cout<<"8. Load Students"<<endl;
        cout<<"9. Search Student by ID in Course"<<endl;
        cout<<"0. Exit"<<endl;
        cout<<"=================================="<<endl;

        cout<<"Please Enter Your Choice : ";
        cin>>Choice;
        switch (Choice) {

            case 1: {
                Student s1;
                sm.Add_Student(s1);
                break;
            }
            case 2: {
                Course c1;
                sm.Add_Course(c1);
                break;
            }

            case 3: {
                sm.Show_Students();
                break;
            }
            case 4: {
                sm.Show_Courses();
                break;
            }
            case 5: {
                int Studentid;
                cout<<"Enter Student id : "<<endl;
                cin>>Studentid;
                int Courseid;
                cout<<"Enter course id : "<<endl;
                cin>>Courseid;
                sm.Enroll_StudentCourse(Studentid,Courseid);
                break;
            }

            case 6: {
                int Studentid,Courseid;
                cout<<"Enter Student id : "<<endl;
                cin>>Studentid;
                cout<<"Enter course id : "<<endl;
                cin>>Courseid;
                sm.Remove_StudentCourse(Studentid,Courseid);
                break;
            }

            case 7: {
                sm.Save_Students();
                break;
            }
            case 8: {
                sm.Load_Students();
                break;
            }
            case 9: {
                int id;
                cout<<"Enter Student ID To Search : "<<endl;
                cin>>id;
                sm.Search_Studentsby_ID(id);
                break;
            }

            case 0 :
                cout << "Exiting... Goodbye!" << endl;
                return 0;

            default:cout<<"Invalid Choice"<<endl;
        }
    }



    return 0;
}



