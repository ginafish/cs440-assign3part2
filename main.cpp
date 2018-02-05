#import <vector>
#import <iostream>
#import <fstream>
#include <sstream>

struct Emp {
    int eid, age;
    std::string ename;
    double salary;

}

struct Dept {
    int did, managerid;
    std::string dname;
    double budget;
}

int main() {
    std::vector <Emp> empList = generateEmpList();
}

std::vector <Emp> generateEmpList() {
    std::vector <Emp> empList;
    ofstream empFile;
    empFile.open("Emp.csv");
    if(!empFile.is_open()) {
        std::cout << "Was expecting an 'Emp.csv' file.";
        throw;
    }
    std::string curLine;
    while(getline(empFile, curLine)) {
        if(curLine == '\n') {
            cout << "\n\tEnd of Emp file.\n";
            break;
        }
        std::cout << "[line] " << curLine << "\n";
        empList.push_back(parseEmp(curLine));
    }
}

Emp parseEmp(std::string empLine) {
    Emp tempEmpObj;
    std::string tempParse = "";
    stringstream tempStrStrm(empLine);
    
    //get eid
    getline(tempStrStrm, tempParse, ',');
    tempParse = trimQuotation(tempParse);
    std::cout << "Parsed eid: " << tempParse;
    tempEmpObj.eid = std::stoi(tempParse);

    //get ename
    getline(tempStrStrm, tempParse, ',');
    tempParse = trimQuotation(tempParse);
    std::cout << "Parsed ename: " << tempParse;
    tempEmpObj.ename = tempParse;

    //get age
    getline(tempStrStrm, tempParse, ',');
    tempParse = trimQuotation(tempParse);
    std::cout << "Parsed age: " << tempParse;
    tempEmpObj.age = std::stoi(tempParse);

    //get salary
    getline(tempStrStrm, tempParse, '\n');
    tempParse = trimQuotation(tempParse);
    std::cout << "Parsed salary: " << tempParse;
    tempEmpObj.salary = std::stof(tempParse);

    return tempEmpObj;
}

std::string trimQuotation(std::string str) {
    return str.substr(1, str.size() - 2);
}


