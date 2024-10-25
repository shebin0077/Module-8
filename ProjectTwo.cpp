#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>


using namespace std;


// Course structure to store course information
struct Course {
    string courseNumber;  // Course number (e.g., "CSCI100")
    string courseName;    // Course name (e.g., "Introduction to Computer Science")
    vector<string> prerequisites;  // List of prerequisite courses
};


// Function to load the data from the file into the data structure
void loadCourses(const string &filename, vector<Course> &courses) {
    ifstream file(filename);
    if (!file.is_open()) {
        // Print error message if file cannot be opened
        cout << "Error: Could not open file " << filename << "\n";
        return;
    }


    string line;
    while (getline(file, line)) {
        Course course;
        stringstream ss(line);
        string prerequisite;


        // Read the course number and name from the line
        getline(ss, course.courseNumber, ',');
        getline(ss, course.courseName, ',');


        // Read the prerequisites (if any)
        while (getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }


        // Add the course to the list of courses
        courses.push_back(course);
    }


    file.close();
    cout << "Data loaded successfully.\n";
}


// Function to print the course list in alphanumeric order
void printCourseList(const vector<Course> &courses) {
    vector<Course> sortedCourses = courses;


    // Sort courses alphanumerically by course number
    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course &a, const Course &b) {
        return a.courseNumber < b.courseNumber;
    });


    cout << "\nHere is a sample schedule:\n";
    // Print each course in the sorted list
    for (const auto &course : sortedCourses) {
        cout << course.courseNumber << ", " << course.courseName << "\n";
    }
}


// Function to print information about a specific course
void printCourse(const vector<Course> &courses, const string &courseNumber) {
    // Iterate through the list of courses to find the specified course
    for (const auto &course : courses) {
        if (course.courseNumber == courseNumber) {
            // Print course number and name
            cout << course.courseNumber << ", " << course.courseName << "\n";
            // Print prerequisites if available
            if (!course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                    cout << course.prerequisites[i];
                    if (i < course.prerequisites.size() - 1) {
                        cout << ", ";  // Add comma separator between prerequisites
                    }
                }
                cout << "\n";
            } else {
                cout << "Prerequisites: None\n";  // Print "None" if no prerequisites
            }
            return;
        }
    }
    // Print error message if the course is not found
    cout << "Course not found.\n";
}


// Main function
int main() {
    vector<Course> courses;  // Vector to store the list of courses
    int choice;  // Variable to store user menu choice
    string filename;  // Variable to store filename input


    cout << "Welcome to the course planner.\n";


    do {
        // Display menu options
        cout << "\n1. Load Data Structure.\n";
        cout << "2. Print Course List.\n";
        cout << "3. Print Course.\n";
        cout << "9. Exit\n";
        cout << "\nWhat would you like to do? ";
        cin >> choice;


        // Handle invalid input for menu choice
        if (cin.fail()) {
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
            continue;
        }


        switch (choice) {
            case 1:
                // Load course data from file
                cout << "Enter the file name to load course data: ";
                cin >> filename;
                loadCourses(filename, courses);
                break;
            case 2:
                // Print course list if data is loaded
                if (courses.empty()) {
                    cout << "No data loaded. Please load the data first.\n";
                } else {
                    printCourseList(courses);
                }
                break;
            case 3:
                // Print specific course information if data is loaded
                if (courses.empty()) {
                    cout << "No data loaded. Please load the data first.\n";
                } else {
                    cout << "Enter the course number: ";
                    string courseNumber;
                    cin >> courseNumber;
                    // Convert course number to uppercase to ensure case-insensitive comparison
                    transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
                    printCourse(courses, courseNumber);
                }
                break;
            case 9:
                // Exit the program
                cout << "Thank you for using the course planner\n";
                break;
            default:
                // Handle invalid menu options
                cout << choice << " is not a valid option.\n";
        }
    } while (choice != 9);


    return 0;
}
