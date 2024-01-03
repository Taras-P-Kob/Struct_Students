#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct Student {
    std::string name;
    std::string address;
    std::string phone;
};

bool isPhoneEmpty(const std::string& phone);
void readDataFromFile(const std::string& fileName, std::vector<Student>& students);
void printPhoneOrAddress(const std::vector<Student>& students, const std::string& searchName);
void Search_and_output();


int main() {
    Search_and_output();
    return 0;
}


void Search_and_output() {
    std::vector<Student> students;
    readDataFromFile("./students.txt", students);

    while (true) {
        std::string studentName;
        std::cout << "Enter student name (or press 'q' to quit): ";
        std::getline(std::cin, studentName);

        if (studentName == "q") {
            break;
        }

        bool found = false;
        for (const auto& student : students) {
            if (student.name == studentName) {
                printPhoneOrAddress(students, studentName);
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "Student not found. Please try again.\n" << std::endl;
        }
    }
}


bool isPhoneEmpty(const std::string& phone) {
    for (char ch : phone) {
        if (!isspace(ch)) {
            return false;
        }
    }
    return true;
}

void readDataFromFile(const std::string& fileName, std::vector<Student>& students) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Could not open file" << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Student temp;
        std::getline(iss, temp.name, ',');
        std::getline(iss, temp.address, ',');
        std::getline(iss, temp.phone);
        students.push_back(temp);
    }
    file.close();
}

void printPhoneOrAddress(const std::vector<Student>& students, const std::string& searchName) {
    for (const auto& student : students) {
        if (student.name == searchName) {
            if (!isPhoneEmpty(student.phone)) {
                std::cout << "Phone: " << student.phone << std::endl << std::endl;
            }
            else {
                std::cout << "Address: " << student.address << std::endl;
            }
            return;
        }
    }
    std::cout << "Student not found.\n" << std::endl;

}