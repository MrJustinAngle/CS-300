#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// Namespace declaration so the code can be a bit more concise
using namespace std;

//Initializing the course structure to hold information
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Vector to be able to store all the objects of the Course
vector<Course> courses;

// The function to load the data from the file
void loadDataStructure(const string& fileName) {
    // Opening the file name that is typed
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Unable to open file: " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        Course course;
        size_t pos = line.find(",");
        course.courseNumber = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find(",");
        course.courseTitle = line.substr(0, pos);
        line.erase(0, pos + 1);

        while (!line.empty()) {
            pos = line.find(",");
            string prerequisite = line.substr(0, pos);
            course.prerequisites.push_back(prerequisite);
            if (pos == string::npos) break;
            line.erase(0, pos + 1);
        }

        courses.push_back(course);
    }

    file.close();
}

// Function to print the list of courses
void printCourseList() {
    sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    cout << "Here is a list of courses:" << endl;
    for (const auto& course : courses) {
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}

// Function to print the information about a specific course
void printCourse(const string& courseNumber) {
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& c) {
        return c.courseNumber == courseNumber;
        });

    if (it != courses.end()) {
        cout << it->courseNumber << ", " << it->courseTitle << endl;
        cout << "Prerequisites: ";
        if (it->prerequisites.empty()) {
            cout << "None" << endl;
        }
        else {
            for (const auto& prerequisite : it->prerequisites) {
                cout << prerequisite << ", ";
            }
            cout << endl;
        }
    }
    else {
        cout << "Course not found." << endl;
    }
}

// The main function to hold the actual program
int main() {
    string fileName;
    int choice;
    string courseNumber;

    cout << "Welcome to the course planner." << endl;
    do {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            loadDataStructure("Courses.txt");
            break;
        case 2:
            printCourseList();
            break;
        case 3:
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            printCourse(courseNumber);
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
        }
    } while (choice != 9);

    return 0;
}