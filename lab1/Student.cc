#include "Student.h"
#include <string>
#include <sstream>
#include "Class.h"
#include <iostream>
std::string Student::toString() const
{
    std::ostringstream oss;
    oss << "Student Information:"
        << "\n\tid: " << id
        << "\n\tname: " << name
        << "\n\tenrollment year: " << year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << std::endl;
    return oss.str();
    return "";
}

void Student::addClass(Class* c){
    this->classes.push_back(c);
}

double Undergraduate::getGrade(){
    double grade = 0.0;
    int TotalPoint = 0;
    for(std::vector<Class*>::iterator it = classes.begin();it != classes.end();++it){
        StudentWrapper s = (*it)->getStudentWrapper(id);
        TotalPoint += (*it)->point;
        grade += (s.getScore()/20)*((*it)->point);
    }
    return grade/TotalPoint;
}

double Graduate::getGrade(){
    int TotalPoint = 0;
    double grade = 0.0;
    for(std::vector<Class*>::iterator it = classes.begin();it != classes.end();++it){
        StudentWrapper s = (*it)->getStudentWrapper(id);
        TotalPoint += (*it)->point;
        double tempGrade = 0.0;
        int score = s.getScore();
        if(score >= 90) tempGrade = 4.0;
        else if(score >= 80) tempGrade = 3.5;
        else if(score >= 70) tempGrade = 3.0;
        else if(score >= 60) tempGrade = 2.5;
        else tempGrade = 2.0;
        grade += tempGrade*((*it)->point);
    }
    return grade/TotalPoint;
}
