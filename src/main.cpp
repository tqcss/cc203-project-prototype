#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <ctime>

#include "../include/strmanip.h"


// ENUMS:

enum Gender {
    Male,
    Female
};

enum StudentType {
    Regular,
    Irregular
};

enum College {
    CAS,
    CBM,
    COC,
    COD,
    COE,
    CICT,
    COL,
    COM,
    CON,
    PESCAR
};


// CLASS FORWARD DECLARATION:

class Section;


// CLASS DEFINITIONS

// User -> Base class for Student and Lecturer
class User {
private:
    std::string _lastName;
    std::string _firstName;
    std::string _middleInitial;
    std::string _extension;

public:
    College college;
    Gender gender;

    User(const College &college,
        const Gender &gender,
        const std::string &lastName,
        const std::string &firstName,
        const std::string &middleInitial,
        const std::string &extension)
    : college(college),
      gender(gender),
      _lastName(toUppercase(lastName)),
      _firstName(toUppercase(firstName)),
      _middleInitial(toUppercase(middleInitial)),
      _extension(toUppercase(extension)) {}

    std::string getLastName() const { return _lastName; }
    std::string getFirstName() const { return _firstName; }
    std::string getMiddleInitial() const { return _middleInitial; }
    std::string getExtension() const { return _extension; }

    void setLastName(const std::string &name) { _lastName = toUppercase(name); }
    void setFirstName(const std::string &name) { _firstName = toUppercase(name); }
    void setMiddleInitial(const std::string &initial) { _middleInitial = toUppercase(initial); }
    void setExtension(const std::string &extension) { _extension = toUppercase(extension); }

    std::string getFullName() {
        return concat(_lastName, ", ", _firstName, " ", _middleInitial, ".");
    }
};


class Student : public User {
private:
    std::string _id;

public:
    static std::unique_ptr<std::unordered_map<std::string, Student*>> students;
    Section *section;
    bool isRegularStudent;

    Student(const std::string &id,
            const bool &isRegular,
            const College &college,
            Section *section,
            const Gender &gender,
            const std::string &lastName,
            const std::string &firstName,
            const std::string &middleInitial,
            const std::string &extension = "")
        : _id(toUppercase(id)),
          isRegularStudent(isRegular),
          User(college, gender, lastName, firstName, middleInitial, extension) {
        
        students->emplace(id, this);
    }

    ~Student() {
        students->at(_id) = nullptr;
        students->erase(_id);
    }

    std::string getId() const { return _id; }

    void setId(const std::string &id) {
        _id = toUppercase(id);
    };
};
std::unique_ptr<std::unordered_map<std::string, Student*>> Student::students = std::make_unique<std::unordered_map<std::string, Student*>>();


class Lecturer : public User {
    // yet to be implemented
};


// yet to be fully implemented
class _Class {
private:
    std::string subjectCode;
    std::string subjectName;
public:
    static std::unique_ptr<std::vector<_Class*>> classes;
    std::vector<Student*> students;



};
std::unique_ptr<std::vector<_Class*>> _Class::classes = std::make_unique<std::vector<_Class*>>();


class Section {
private:
    std::string _program;
    char _section;

public:
    static std::unique_ptr<std::vector<Section*>> sections;
    std::vector<Student*> students;
    unsigned short year;

    Section(const std::string &program,
            const unsigned short &year,
            const char &section)
        : _program(toUppercase(program)), 
          year(year),
          _section(std::toupper(section)) {
        
        sections->push_back(this);
    }

    ~Section() {
        for (int index = 0; index < sections->size(); index++) {
            if (sections->at(index) != this) continue;
            sections->erase(sections->begin() + index);
            return;
        }
    }

    std::string getName() {
        return concat(_program, " ", year, "-", _section);
    }

    // FUNCTION NOT TESTED
    void addStudent(const std::string &studentId) {
        if (Student::students->find(studentId) == Student::students->end()) {
            throw std::invalid_argument(concat("Student with the id: '", studentId, "' not found."));
        }
        Student &student = *(Student::students->at(studentId));
        students.push_back(&student);
        student.section = this;
    }

    void addStudent(Student *student) {
        if (student == nullptr) {
            throw std::invalid_argument("Passed in argument must not be a nullptr.");
        }
        students.push_back(student);
        student->section = this;
        student = nullptr;
    }

    void removeStudent(std::string &studentId) {
        for (int index = 0; index < students.size(); index++) {
            if (studentId != students.at(index)->getId()) continue;

            students.at(index) = nullptr;
            students.erase(students.begin() + index);
            return;
        }
        throw std::invalid_argument(concat("Student with id: '", studentId, "' was not found in section or doesn't exist."));
    }

    void removeStudent(Student *student) {
        for (int index = 0; index = students.size(); index++) {
            if (student != students.at(index)) continue;

            students.at(index) = nullptr;
            students.erase(students.begin() + index);
            return;
        }
        throw std::invalid_argument("The student pointer that was passed was not found in section or doesn't exist.");
    }

    std::string getProgram() const { return _program; }
    char getSection() const { return _section; }

    void setProgram(const std::string program) { _program = toUppercase(program); }
    void setSection(const char section) { _section = std::toupper(section); }
};
std::unique_ptr<std::vector<Section*>> Section::sections = std::make_unique<std::vector<Section*>>();


int main() {
    std::unique_ptr<Section> BSCS1A = std::make_unique<Section>("BSCS", 1, 'A');
    std::unique_ptr<Student> me = std::make_unique<Student>("1815A0001", true, CICT, BSCS1A.get(), Male, "Doe", "John", "A");
    
    BSCS1A->addStudent(me.get());

    std::cout << "students of BSCS 1-A = [ ";
    for (Student* student : BSCS1A->students) {
        std::cout << student->getId() << ' ';
    }
    std::cout << "]\n";

    std::cout << "Section of '" << me->getFullName() << "' is " << me->section->getName();
    return 0;
}
