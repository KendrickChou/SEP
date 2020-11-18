#include <vector>
#include <iostream>
#include <fstream>
#include "Class.h"
#include "Student.h"

using namespace std;

class AppX {
private:
    vector<Student *> studentVec;
    vector<Class *> classVec;

    void loadFiles();
    void inputScore();
    void printAvgScore();
    void printGpa();

public:
    AppX();
    ~AppX();
    int run();
};

AppX::~AppX()
{
    // You can use the traditional loop, which is more clear.
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if (*it) delete (*it);
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (const auto &s: studentVec) {
        if (s) delete (s);
    }
}

AppX::AppX()
{
    loadFiles();
}

void AppX::loadFiles()
{
    string line;
    size_t pos1, pos2;
    vector<string> bufv;
    Student *st = nullptr;
    string clsname;
    int point;
    Class *cl = nullptr;

    // Open a file as a input stream.
    ifstream stfile("./Students.txt");

    while (getline(stfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;

        // The bufv vector stores each columnes in the line.
        bufv.clear();
        // Split the line into columes.
        //   pos1: begining the the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';', pos1 + 1);
            if (pos2 == string::npos) { // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            } else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }
        if (bufv[3] == "U")
            st = new Undergraduate(bufv[0], bufv[1], bufv[2]);
        else
            st = new Graduate(bufv[0], bufv[1], bufv[2]);

        studentVec.push_back(st);
    }

    stfile.close();

    ifstream stFile("./Classes.txt");

    while(getline(stFile, line)){
        if(line.empty()) continue;
        if(line[0] == '#') continue;
        if(line[0] == 'C'){
            pos1 = line.find(':');
            clsname = line.substr(pos1 + 1,string::npos);
            getline(stFile,line);
            pos1 = line.find(':');
            point = line[pos1 + 1] - '0';
            cl = new Class(clsname,point);
            classVec.push_back(cl);
            getline(stFile,line);
            while(!line.empty()){
                bool flag = false;
                for(int i = 0;i < studentVec.size(); ++i){
                    if(studentVec[i]->id == line){
                        cl->addStudent(*studentVec[i]);
                        studentVec[i]->addClass(cl);
                        flag = true;
                        break;
                    }
                }
                getline(stFile,line);
            }
        }
    }

    stFile.close();
    // TODO: load data from ./Classes.txt and push objects to the vector.
    // Hint: how is student information read?
}

void AppX::inputScore()
{
    double score = 0;
    string sbuf;
    Class *cl;

    while(true){
        cout << "Please input the class name(or input q to quit): ";
        cin >> sbuf;
        if(sbuf == "q") break;
        cl = nullptr;
        for (vector<Class *>::iterator it = classVec.begin();it != classVec.end();++it) {
            if ((*it)->name == sbuf) {
                 cl = *it;
                 break;
              }
        }
        if(cl == nullptr){
            cout << "No match class!" << endl;
            continue;
        }
        while(true){
                string Tips;
                cout << "Please input the student's id(or input q to quit): ";
                cin >> sbuf;
                if(sbuf == "q") break;
                try{
                    StudentWrapper &s = cl->getStudentWrapper(sbuf);
                    Tips = s.toString();
                    cout << Tips;
                        cout << "Please input the score(or input q to quit): ";
                        cin >> sbuf;
                        if(sbuf == "q") break;
                        for(int i = 0;i < sbuf.size(); ++i){
                            score *= 10;
                            score += sbuf[i] - '0';
                        }
                        try{
                        s.setScore(score) ;
                         score = 0;
                        }
                        catch(char const* e){
                            cout << e << endl;
                        }
                        score = 0;
                    }
                catch(char const* e){
                    cout << e << endl;
                }
            }
        }
    }

void AppX::printAvgScore()
{
    string sbuf;
    Class *cl;
    double avg = 0.0;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;
        cl = nullptr;
        for (vector<Class *>::iterator it = classVec.begin();
             it != classVec.end();
             ++it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }
        avg = cl->getAvgScore();
        cout << "The average score is: ";
        printf("%.2f",avg);
        cout << endl;
    }
}

void AppX::printGpa()
{
    string sbuf;
    Student *s;
    double gpa;

    while (true) {
        cout << "Please input the student's id (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;
        s = nullptr;
        for(vector<Student*>::iterator it = studentVec.begin(); it != studentVec.end(); ++it){
            if((*it)->id == sbuf){
                s = *it;
                break;
            }
        }
        if(s == nullptr){
            cout << "No match student!" << endl;
            continue;
        }
        gpa = s->getGrade();
        cout << "GPA = ";
        printf("%.2f",gpa);
        cout << endl;
    }
}

int AppX::run()
{
    char cmd;
    while (true) {
        cout << "Command menu:\n"
            << "\ti: Input score\n"
            << "\ta: Compute average score of a class\n"
            << "\tg: Compute grade of a student\n"
            << "\tq: Quit\n"
            << "Please input the command: ";
        cin >> cmd;
        if (cmd == 'i') {
            inputScore();
        } else if (cmd == 'a') {
            printAvgScore();
        } else if (cmd == 'g') {
            printGpa();
        } else if (cmd == 'q') {
            break;
        } else {
            cout << "Invalid command!\n" << endl;
        }
    }
    return 0;
}

int main()
{
    AppX app;
    return app.run();
}
