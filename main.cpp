#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

struct Emp {
    int eid, age;
    std::string ename;
    double salary;

    bool operator < (const Emp& othEmp) const {
        return (eid < othEmp.eid);
    }
};

struct Dept {
    int did, managerid;
    std::string dname;
    double budget;

    bool operator < (const Dept& othDept) const {
        return (managerid < othDept.managerid);
    }
};



// ------------ Parsing and Reading Files ------------

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

std::vector<Emp> generateEmpList() {
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

std::vector<Dept> generateDeptList() {
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



std::vector<Emp> readLinesFromEmpFile(std::fstream empFile, int count) {
    std::vector<Record> empList;
    for(int i = 0; i < count; ++i) {
        if(empFile.eof()) {
            std::cout << "\n\tEnd of Emp file.\n";
            break;
        }
        std::string curLine;
        getline(empFile, curLine);
        empList.push_back(parseEmp(curLine));
    }
    return empList;
}

std::vector<Dept> readLinesFromDeptFile(std::fstream deptFile, int count) {
    std::vector<Dept> deptList;
    for(int i = 0; i < count; ++i) {
        if(deptFile.eof()) {
            std::cout << "\n\tEnd of Dept file.\n";
            break;
        }
        std::string curLine;
        getline(deptFile, curLine);
        deptList.push_back(parseDept(curLine));
    }
    return deptList;
}



std::string rebuildSingleEmpToString(Emp emp) {
    std::stringstream sstream;
    sstream << "\"" << emp.eid << "\",\"" << emp.ename << "\",\"" << emp.age << "\",\"" << emp.salary << "\"\n";
    return sstream.str();
}

std::string rebuildEmpToString(std::vector<Emp> empList) {
    std::stringstream sstream;
    for(int i = 0; i < empList.size(); ++i) {
        sstream << "\"" << empList[i].eid << "\",\"" << empList[i].ename << "\",\"" << empList[i].age << "\",\"" << empList[i].salary << "\"\n";
    }
    return sstream.str();
}

std::string rebuildSingleDeptToString(Dept dept) {
    std::stringstream sstream;
    sstream << "\"" << dept.did << "\",\"" << dept.dname << "\",\"" << dept.budget << "\",\"" << dept.managerid << "\"\n";
    return sstream.str();
}

std::string rebuildDeptToString(std::vector<Dept> deptList) {
    std::stringstream sstream;
    for(int i = 0; i < deptList.size(); ++i) {
        sstream << "\"" << deptList[i].did << "\",\"" << deptList[i].dname << "\",\"" << deptList[i].budget << "\",\"" << deptList[i].managerid << "\"\n";
    }
    return sstream.str();
}


// ------------ Sorting ------------

std::vector<Emp> sortEmpList(std::vector<Emp> recordList) {
    std::sort(recordList.begin(), recordList.end());
    return recordList;
}
std::vector<Dept> sortDeptList(std::vector<Dept> recordList) {
    std::sort(recordList.begin(), recordList.end());
    return recordList;
}

std::vector<Emp> generateSortedEmpList(std::fstream sourceEmpFile, std::fstream targetEmpFile) {
    while(!sourceEmpFile.eof()) {
        std::vector<Emp> tempList;
        Emp tempLowest;
        std::string tempLowestNotParsed;

        //find lowest value in source value
        while(!sourceEmpFile.eof()) {
            tempList = readLinesFromEmpFile(sourceEmpFile, 21);
            tempList = sortEmpList(tempList);
            if(tempList[0].eid < tempLowest.eid) {
                tempLowest = tempList[0];
                tempLowestNotParsed = rebuildSingleEmpToString(tempLowest);
            }
        }

        //add lowest value to target file
        targetEmpFile << tempLowestNotParsed;

        //remove lowest from source file
        sourceEmpFile.clear();
        sourceEmpFile.seekg(0, std::ios::beg);
        std::string curLine;
        std::fstream tempFile();
        while(getline(sourceEmpFile, curLine)) {
            if(!curLine.compare(curLine)) {
                continue;
            }
            tempFile << curLine;
        }
        sourceEmpFile.clear();
        sourceEmpFile.seekg(0, std::ios::beg);
    }
}

std::vector<Dept> generateSortedDeptList(std::fstream sourceDeptFile, std::fstream targetDeptFile) {
    while(!sourceDeptFile.eof()) {
        std::vector<Emp> tempList;
        Emp tempLowest;
        std::string tempLowestNotParsed;

        //find lowest value in source value
        while(!sourceDeptFile.eof()) {
            tempList = readLinesFromEmpFile(sourceDeptFile, 21);
            tempList = sortEmpList(tempList);
            if(tempList[0].eid < tempLowest.eid) {
                tempLowest = tempList[0];
                tempLowestNotParsed = rebuildSingleEmpToString(tempLowest);
            }
        }

        //add lowest value to target file
        targetDeptFile << tempLowestNotParsed;

        //remove lowest from source file
        sourceDeptFile.clear();
        sourceDeptFile.seekg(0, std::ios::beg);
        std::string curLine;
        std::fstream tempFile();
        while(getline(sourceDeptFile, curLine)) {
            if(!curLine.compare(curLine)) {
                continue;
            }
            tempFile << curLine;
        }
        sourceDeptFile.clear();
        sourceDeptFile.seekg(0, std::ios::beg);
    }
}


// ------------ Merging ------------

void writeResult(Emp e, Dept d, std::fstream joinFile) {
    joinFile << "\"" << d.did << "\"," << "\"" << d.dname << "\"," 
            << "\"" << d.budget << "\"," << "\"" << d.managerid << "\"," 
            << "\"" << e.ename << "\"," << "\"" << e.age << "\","<< "\"" 
            << e.salary << "\"\n";
}

void merge(std::fstream sortedEmpFile, std::fstream sortedDeptFile, std::fstream joinFile) {
    std::vector<Emp> empRecordsInMM;
    std::vector<Dept> deptRecordsInMM;

    empRecordsInMM = readLinesFromEmpFile(sortedEmpFile, 11);
    deptRecordsInMM = readLinesFromDeptFile(sorteDeptFile, 11);

    while(empRecordsInMM.size() > 0 && deptRecordsInMM.size() > 0) {
        if(empRecordsInMM[0].eid < deptRecordsInMM[0].managerid) {
            empRecordsInMM.erase(0);
        } else if(deptRecordsInMM[0].managerid < empRecordsInMM[0].eid) {
            deptRecordsInMM.erase(0);
        } else {
            while(deptRecordsInMM.size() > 0) {
                writeResult(empRecordsInMM[0], deptRecordsInMM[0], joinFile);
                deptRecordsInMM.erase(0);
            }
            empRecordsInMM.erase(0);
        }

        if(empRecordsInMM.size() == 0) {
            empRecordsInMM = readLinesFromEmpFile(sortedEmpFile, 11);
        } else if (deptRecordsInMM.size() == 0) {
            deptRecordsInMM = readLinesFromDeptFile(sorteDeptFile, 11);
        }
    }
}


int main() {
    std::fstream joinFile("join.csv", std::ios::out | std::ios::trunc | std::ios::app);
    std::fstream empFile("Emp.csv", std::ios::in);
    std::fstream deptFile("Dept.csv", std::ios::in);

    std::fstream empFileCopy("Emp-copy.csv", std::ios::out | std::ios:: in);
    std::fstream deptFileCopy("Dept-copy.csv", std::ios::out | std::ios::in);

    while(!empFile.eof()) {
        std::string temp;
        getline(empFile, temp);
        empFileCopy << temp;
    }
    while(!deptFile.eof()) {
        std::string temp;
        getline(deptFile, temp);
        deptFileCopy << temp;
    }
    empFile.clear();
    deptFile.clear();
    empFileCopy.clear();
    deptFileCopy.clear();
    empFile.seekg(0, std::ios::beg);
    deptFile.seekg(0, std::ios::beg);
    empFileCopy.seekg(0, std::ios::beg);
    deptFileCopy.seekg(0, std::ios::beg);
    
    std::fstream sortedEmpFile("sorted-emp.csv", std::ios::in | std::ios::out);
    std::fstream sortedDeptFile("sorted-dept.csv", std::ios::in | std::ios::out);



}
