#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <exception>
#include <limits>

#include <unistd.h>

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
    //std::cout << "\nParsed salary: " << tempParse << std::endl;
    tempEmpObj.salary = std::stof(tempParse);

    return tempEmpObj;
}

std::vector<Emp> generateEmpList() {
    //std::cout << "\nGenerating Emp list." << std::endl;
    std::vector<Emp> empList;
    std::ifstream empFile("Emp.csv");
    if(!empFile.is_open()) {
        std::cout << "\nERROR: Was expecting a 'Emp.csv' file." << std::endl;
        throw;
    }
    std::string curLine;
    while(getline(empFile, curLine)) {
        if(checkLineForLineEnd(curLine)) {
            std::cout << "\n\tEnd of Emp file." << std::endl;
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
    //std::cout << "\nGenerating Dept list." << std::endl;
    std::vector<Dept> deptList;
    std::ifstream deptFile("Dept.csv");
    if(!deptFile.is_open()) {
        std::cout << "\nERROR: Was expecting a 'Dept.csv' file\n.";
        throw;
    }
    std::string curLine;
    while(getline(deptFile, curLine)) {
        if(checkLineForLineEnd(curLine)) {
            std::cout << "\n\tEnd of Dept file." << std::endl;
            break;
        }
        //std::cout << "\n\n[line]" << curLine;
        deptList.push_back(parseDept(curLine));
    }
    deptFile.close();
    return deptList;
}



std::vector<Emp> readLinesFromEmpFile(std::fstream& empFile, int count) {
    std::cout << "reading lines from emp file." << std::endl;
    std::vector<Emp> empList;
    for(int i = 0; i < count; ++i) {
        if(empFile.eof()) {
            std::cout << "\n\tEnd of Emp file." << std::endl;
            break;
        }
        std::cout << "Made it past the if statement." << std::endl;
        std::string curLine;
        
        getline(empFile, curLine);
        std::cout << "Made it past the getline statement.  End of file? " << !empFile.eof() << std::endl;
        //std::cout << curLine << std::endl;
        if(!empFile.eof()) {
            std::cout << "About to parse:" << curLine << std::endl;
            Emp testEmp = parseEmp(curLine);
            std::cout << "Parsed." << std::endl;
            std::cout << testEmp.ename << std::endl;
            empList.push_back(testEmp);
        }
    }
    return empList;
}

std::vector<Dept> readLinesFromDeptFile(std::fstream& deptFile, int count) {
    std::vector<Dept> deptList;
    for(int i = 0; i < count; ++i) {
        if(deptFile.eof()) {
            std::cout << "\n\tEnd of Dept file." << std::endl;
            break;
        }
        std::string curLine;
        getline(deptFile, curLine);
        std::cout << curLine << std::endl;
        if(!deptFile.eof()) {
            deptList.push_back(parseDept(curLine));
        }
    }
    return deptList;
}



std::string rebuildSingleEmpToString(Emp emp) {
    std::stringstream sstream;
    sstream << "\"" << emp.eid << "\",\"" << emp.ename << "\",\"" << emp.age << "\",\"" << emp.salary << "\"" << std::endl;
    //std::cout << "rebuilt string:" << sstream.str() << std::endl;
    return sstream.str();
}

std::string rebuildEmpToString(std::vector<Emp> empList) {
    std::stringstream sstream;
    for(int i = 0; i < empList.size(); ++i) {
        sstream << "\"" << empList[i].eid << "\",\"" << empList[i].ename << "\",\"" << empList[i].age << "\",\"" << empList[i].salary << "\"" << std::endl;
    }
    return sstream.str();
}

std::string rebuildSingleDeptToString(Dept dept) {
    std::stringstream sstream;
    sstream << "\"" << dept.did << "\",\"" << dept.dname << "\",\"" << dept.budget << "\",\"" << dept.managerid << "\"" << std::endl;
    return sstream.str();
}

std::string rebuildDeptToString(std::vector<Dept> deptList) {
    std::stringstream sstream;
    for(int i = 0; i < deptList.size(); ++i) {
        sstream << "\"" << deptList[i].did << "\",\"" << deptList[i].dname << "\",\"" << deptList[i].budget << "\",\"" << deptList[i].managerid << "\"" << std::endl;
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

std::vector<Emp> generateSortedEmpList(std::fstream& sourceEmpFile, std::fstream& targetEmpFile) {
    sourceEmpFile.clear();
    targetEmpFile.clear();
    sourceEmpFile.seekg(0, std::ios::beg);
    targetEmpFile.seekg(0, std::ios::beg);
    std::cout << "Starting to generate sorted emp list." << std::endl;
    while(!sourceEmpFile.eof()) {
        std::vector<Emp> tempList;
        Emp tempLowest;
        std::string tempLowestNotParsed;
        tempLowest.eid = std::numeric_limits<int>::max();

        //std::cout << "About to find lowest val." << std::endl;
        //find lowest value in source value
        while(!sourceEmpFile.eof()) {
            //std::cout << "About to read lines from file." << std::endl;
            tempList = readLinesFromEmpFile(sourceEmpFile, 21);
            //std::cout << "About to sort lines." << std::endl;
            tempList = sortEmpList(tempList);
            std::cout << "Comparing " << tempList[0].eid << " to " << tempLowest.eid << std::endl;
            if(tempList[0].eid < tempLowest.eid) {
                tempLowest = tempList[0];
                tempLowestNotParsed = rebuildSingleEmpToString(tempLowest);
            }
        }
        std::cout << "Lowest val:" << tempLowest.eid << std::endl;

        //add lowest value to target file
        targetEmpFile << tempLowestNotParsed;
        std::cout << "Added lowest val to target file." << std::endl;

        //remove lowest from source file
        sourceEmpFile.clear();
        sourceEmpFile.seekg(0, std::ios::beg);
        std::string curLine;
        std::fstream tempFile("temp.csv", std::ios::app | std::ios::in | std::ios::out | std::ios::trunc);

        int res = access("./temp.csv", R_OK);
        if (res < 0) {
            if (errno == ENOENT) {
                std::cout << "temp.csv not created." << std::endl;
            }
        }

        std::cout << "Removing lowest val from source file." << std::endl;
        while(getline(sourceEmpFile, curLine)) {
            std::cout << !curLine.compare(tempLowestNotParsed.substr(0, tempLowestNotParsed.length() - 1)) << std::endl;
            //std::cout << curLine << std::endl << tempLowestNotParsed.substr(0, tempLowestNotParsed.length() - 1) << std::endl;
            if(!curLine.compare(tempLowestNotParsed.substr(0, tempLowestNotParsed.length() - 1))) {
                continue;
            }
            //std::cout << curLine << std::endl;
            tempFile << curLine << std::endl;
        }
        tempFile.close();
        sourceEmpFile.close();
        remove("Emp-copy.csv");
        rename("temp.csv", "Emp-copy.csv");
        sourceEmpFile.open("Emp-copy.csv", std::ios::out | std::ios::in);
        sourceEmpFile.clear();
        sourceEmpFile.seekg(0, std::ios::beg);
        std::cout << "Removed and renamed lowest val from source." << std::endl;
    }
}

std::vector<Dept> generateSortedDeptList(std::fstream& sourceDeptFile, std::fstream& targetDeptFile) {
    sourceDeptFile.clear();
    targetDeptFile.clear();
    sourceDeptFile.seekg(0, std::ios::beg);
    targetDeptFile.seekg(0, std::ios::beg);
    while(!sourceDeptFile.eof()) {
        std::vector<Dept> tempList;
        Dept tempLowest;
        std::string tempLowestNotParsed;
        tempLowest.managerid = std::numeric_limits<int>::max();


        //find lowest value in source value
        while(!sourceDeptFile.eof()) {
            tempList = readLinesFromDeptFile(sourceDeptFile, 21);
            tempList = sortDeptList(tempList);
            if(tempList[0].managerid < tempLowest.managerid) {
                tempLowest = tempList[0];
                tempLowestNotParsed = rebuildSingleDeptToString(tempLowest);
            }
        }

        //add lowest value to target file
        targetDeptFile << tempLowestNotParsed;

        //remove lowest from source file
        sourceDeptFile.clear();
        sourceDeptFile.seekg(0, std::ios::beg);
        std::string curLine;
        std::fstream tempFile("temp.csv", std::ios::app | std::ios::in | std::ios::out);
        while(getline(sourceDeptFile, curLine)) {
            if(!curLine.compare(curLine)) {
                continue;
            }
            tempFile << curLine;
        }
        remove("Dept-copy.csv");
        rename("temp.csv", "Dept-copy.csv");
        sourceDeptFile.clear();
        sourceDeptFile.seekg(0, std::ios::beg);
    }
}


// ------------ Merging ------------

void writeResult(Emp e, Dept d, std::fstream& joinFile) {
    joinFile << "\"" << d.did << "\"," << "\"" << d.dname << "\"," 
            << "\"" << d.budget << "\"," << "\"" << d.managerid << "\"," 
            << "\"" << e.ename << "\"," << "\"" << e.age << "\","<< "\"" 
            << e.salary << "\"" << std::endl;
}

void merge(std::fstream& sortedEmpFile, std::fstream& sortedDeptFile, std::fstream& joinFile) {
    std::vector<Emp> empRecordsInMM;
    std::vector<Dept> deptRecordsInMM;

    empRecordsInMM = readLinesFromEmpFile(sortedEmpFile, 11);
    deptRecordsInMM = readLinesFromDeptFile(sortedDeptFile, 11);

    while(empRecordsInMM.size() > 0 && deptRecordsInMM.size() > 0) {
        if(empRecordsInMM[0].eid < deptRecordsInMM[0].managerid) {
            empRecordsInMM.erase(empRecordsInMM.begin());
        } else if(deptRecordsInMM[0].managerid < empRecordsInMM[0].eid) {
            deptRecordsInMM.erase(deptRecordsInMM.begin());
        } else {
            while(deptRecordsInMM.size() > 0 && deptRecordsInMM[0].managerid == empRecordsInMM[0].eid) {
                writeResult(empRecordsInMM[0], deptRecordsInMM[0], joinFile);
                deptRecordsInMM.erase(deptRecordsInMM.begin());
            }
            empRecordsInMM.erase(empRecordsInMM.begin());
        }

        if(empRecordsInMM.size() == 0) {
            empRecordsInMM = readLinesFromEmpFile(sortedEmpFile, 11);
        } else if (deptRecordsInMM.size() == 0) {
            deptRecordsInMM = readLinesFromDeptFile(sortedDeptFile, 11);
        }
    }
}


int main() {
    std::fstream joinFile("join.csv", std::ios::out | std::ios::trunc);
    std::fstream empFile("Emp.csv", std::ios::in);
    std::fstream deptFile("Dept.csv", std::ios::in);

    std::fstream empFileCopy("Emp-copy.csv", std::ios::out | std::ios::in | std::ios::trunc);
    std::fstream deptFileCopy("Dept-copy.csv", std::ios::out | std::ios::in | std::ios::trunc);

    std::cout << "creating copy files." << std::endl;
    while(!empFile.eof()) {
        std::string temp;
        getline(empFile, temp);
        empFileCopy << temp << std::endl;
    }
    while(!deptFile.eof()) {
        std::string temp;
        getline(deptFile, temp);
        deptFileCopy << temp << std::endl;
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

    generateSortedEmpList(empFileCopy, sortedEmpFile);
    generateSortedDeptList(deptFileCopy, sortedDeptFile);
    merge(sortedEmpFile, sortedDeptFile, joinFile);
}
