#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

struct Record {
    const static int size = 56;
};

struct Emp : Record {
    int eid, age;
    std::string ename;
    double salary;
};

struct Dept : Record {
    int did, managerid;
    std::string dname;
    double budget;
};

std::string trimQuotation(std::string str) {
    return str.substr(1, str.size() - 2);
}

bool checkLineForLineEnd(std::string str) {
    for(int i = 0; i < str.length(); ++i) {
        if (str[i] == '\n') {
            return true;
        }
    }
    return false;
}


Emp parseEmp(std::string empLine) {
    Emp tempEmpObj;
    std::string tempParse = "";
    std::stringstream tempStrStrm(empLine);
    
    //get eid
    getline(tempStrStrm, tempParse, ',');
    tempParse = trimQuotation(tempParse);
    //std::cout << "\nParsed eid: " << tempParse;
    tempEmpObj.eid = std::stoi(tempParse);

    //get ename
    getline(tempStrStrm, tempParse, ',');
    tempParse = trimQuotation(tempParse);
    //std::cout << "\nParsed ename: " << tempParse;
    tempEmpObj.ename = tempParse;

    //get age
    getline(tempStrStrm, tempParse, ',');
    tempParse = trimQuotation(tempParse);
    //std::cout << "\nParsed age: " << tempParse;
    tempEmpObj.age = std::stoi(tempParse);

    //get salary
    getline(tempStrStrm, tempParse, '\n');
    tempParse = trimQuotation(tempParse);
    //std::cout << "\nParsed salary: " << tempParse;
    tempEmpObj.salary = std::stof(tempParse);

    return tempEmpObj;
}

std::vector <Emp> generateEmpList() {
    //std::cout << "\nGenerating Emp list.\n";
    std::vector<Emp> empList;
    std::ifstream empFile("Emp.csv");
    if(!empFile.is_open()) {
        std::cout << "\nERROR: Was expecting a 'Emp.csv' file.\n";
        throw;
    }
    std::string curLine;
    while(getline(empFile, curLine)) {
        if(checkLineForLineEnd(curLine)) {
            std::cout << "\n\tEnd of Emp file.\n";
            break;
        }
        //std::cout << "\n\n[line]" << curLine;
        empList.push_back(parseEmp(curLine));
    }
    empFile.close();
    return empList;
}


Dept parseDept(std::string deptLine) {
    Dept tempDeptObj;
    std::string tempParse = "";
    std::stringstream tempStrStrm(deptLine);
    
    //get did
    getline(tempStrStrm, tempParse, ',');
    tempParse = trimQuotation(tempParse);
    //std::cout << "\nParsed did: " << tempParse;
    tempDeptObj.did = std::stoi(tempParse);

    //get dname
    getline(tempStrStrm, tempParse, ',');
    tempParse = trimQuotation(tempParse);
    //std::cout << "\nParsed dname: " << tempParse;
    tempDeptObj.dname = tempParse;

    //get budget
    getline(tempStrStrm, tempParse, ',');
    tempParse = trimQuotation(tempParse);
    //std::cout << "\nParsed budget: " << tempParse;
    tempDeptObj.budget = std::stof(tempParse);

    //get managerid
    getline(tempStrStrm, tempParse, '\n');
    tempParse = trimQuotation(tempParse);
    //std::cout << "\nParsed managerid: " << tempParse;
    tempDeptObj.managerid = std::stoi(tempParse);

    return tempDeptObj;
}

std::vector <Dept> generateDeptList() {
    //std::cout << "\nGenerating Dept list.\n";
    std::vector<Dept> deptList;
    std::ifstream deptFile("Dept.csv");
    if(!deptFile.is_open()) {
        std::cout << "\nERROR: Was expecting a 'Dept.csv' file\n.";
        throw;
    }
    std::string curLine;
    while(getline(deptFile, curLine)) {
        if(checkLineForLineEnd(curLine)) {
            std::cout << "\n\tEnd of Dept file.\n";
            break;
        }
        //std::cout << "\n\n[line]" << curLine;
        deptList.push_back(parseDept(curLine));
    }
    deptFile.close();
    return deptList;
}


int main() {
    std::vector<Emp> empList = generateEmpList();
    std::vector<Dept> deptList = generateDeptList();
    std::vector<Record> memory;
}
