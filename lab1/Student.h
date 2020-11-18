#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>

class Class;

enum Degree {
    undergraduate,
    graduate
};

class Student {
private:
    const std::string name,year;
    Degree degree;
protected:
    std::vector<Class*> classes;
public:
    Student(){};
    Student(std::string Id,std::string Name,std::string Year):id(Id),name(Name),year(Year){};
    const std::string id;
    std::string toString() const;
    virtual double getGrade() = 0;
    void addClass(Class* c);
};


class StudentWrapper {
private:
    const Student &student;
    double score = 0.0;
public:
    const std::string id;
    // TODO: fix error
    StudentWrapper(const std::string &id, const Student &student):student(student),id(id){};

    void setScore(double score)
    {
        if (score < 0 || score > 100)
            throw "Wrong score!";
        this->score = score;
    }

    double getScore() const
    {
        return this->score;
    }

    std::string toString() const
    {
        return student.toString();
    }
};

class Graduate:public Student{
public:
    Graduate(std::string Id,std::string name,std::string year):Student(Id,name,year){
    };
    virtual double getGrade();
};


class Undergraduate:public Student{
public:
    Undergraduate(std::string Id,std::string name,std::string year):Student(Id,name,year){
    };
    virtual double getGrade();
};


#endif // STUDENT_H_
