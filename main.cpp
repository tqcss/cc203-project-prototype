#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <ctime>


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

// FUNCTION FORWARD DECLARATION
std::string capitalize(const std::string &str);
template<typename ... Args>
std::string concat(Args&&...args);

// CLASS FORWARD DECLARATION
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
      _lastName(capitalize(lastName)),
      _firstName(capitalize(firstName)),
      _middleInitial(capitalize(middleInitial)),
      _extension(capitalize(extension)) {}

    std::string getLastName() const { return _lastName; }
    std::string getFirstName() const { return _firstName; }
    std::string getMiddleInitial() const { return _middleInitial; }
    std::string getExtension() const { return _extension; }

    void setLastName(const std::string &name) { _lastName = capitalize(name); }
    void setFirstName(const std::string &name) { _firstName = capitalize(name); }
    void setMiddleInitial(const std::string &initial) { _middleInitial = capitalize(initial); }
    void setExtension(const std::string &extension) { _extension = capitalize(extension); }

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
        : _id(capitalize(id)),
          isRegularStudent(isRegular),
          section(section),
          User(college, gender, lastName, firstName, middleInitial, extension) {
        
        students->emplace(id, this);
    }

    ~Student() {
        students->at(_id) = nullptr;
        students->erase(_id);
    }

    std::string getId() const { return _id; }

    void setId(const std::string id);
};
std::unique_ptr<std::unordered_map<std::string, Student*>> Student::students = std::make_unique<std::unordered_map<std::string, Student*>>();


class Lecturer : public User {
    // yet to be implemented
};


class Section {
public:
    static std::unique_ptr<std::vector<Section*>> sections;
};
std::unique_ptr<std::vector<Section*>> Section::sections = std::make_unique<std::vector<Section*>>();


std::string capitalize(const std::string &str) {
    std::string result;
    for (const char &letter : str) {
        result += std::toupper(letter);
    }
    return result;
}

template<typename ... Args>
std::string concat(Args&&...args)
{
    std::stringstream ss;
    (ss << ... << std::forward<Args>(args));
    return ss.str();
}

int main() {

    return 0;
}

