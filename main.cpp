#include  <vector>
#include  <iostream>
#include  <fstream>
#include  <sstream>

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
    for(int i = 0; i < str.len(); ++i) {
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

std::vector <Emp> generateEmpList() {
    std::cout << "\nGenerating Emp list.\n"
    std::vector<Emp> empList;
    ofstream empFile;
    empFile.open("Emp.csv");
    if(!empFile.is_open()) {
        std::cout << "Was expecting a 'Emp.csv' file.";
        throw;
    }
    std::string curLine;
    while(getline(empFile, curLine)) {
        if(checkLineForLineEnd(curLine)) {
            std::cout << "\n\tEnd of Emp file.\n";
            break;
        }
        std::cout << "[line] " << curLine << "\n";
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
    std::cout << "Parsed did: " << tempParse;
    tempDeptObj.did = std::stoi(tempParse);

    //get dname
    getline(tempStrStrm, tempParse, ',');
    tempParse = trimQuotation(tempParse);
    std::cout << "Parsed dname: " << tempParse;
    tempDeptObj.dname = tempParse;

    //get budget
    getline(tempStrStrm, tempParse, '\n');
    tempParse = trimQuotation(tempParse);
    std::cout << "Parsed budget: " << tempParse;
    tempDeptObj.budget = std::stof(tempParse);

    //get managerid
    getline(tempStrStrm, tempParse, ',');
    tempParse = trimQuotation(tempParse);
    std::cout << "Parsed managerid: " << tempParse;
    tempDeptObj.managerid = std::stoi(tempParse);

    return tempDeptObj;
}

std::vector <Dept> generateDeptList() {
    std::cout << "\nGenerating Dept list.\n"
    std::vector<Dept> deptList;
    ofstream deptFile;
    deptFile.open("Emp.csv");
    if(!deptFile.is_open()) {
        std::cout << "Was expecting a 'Dept.csv' file.";
        throw;
    }
    std::string curLine;
    while(getline(deptFile, curLine)) {
        if(checkLineForLineEnd(curLine)) {
            std::cout << "\n\tEnd of Dept file.\n";
            break;
        }
        std::cout << "[line] " << curLine << "\n";
        deptList.push_back(parseDept(curLine));
    }
    deptFile.close();
    return deptList;
}


int main() {
    std::vector<Emp> empList = generateEmpList();
    //std::vector<Dept> deptList = generateDeptList();
    std::vector<Record> memory;
}
