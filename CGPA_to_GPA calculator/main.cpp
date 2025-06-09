#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <tuple>

using namespace std;

double calculate_gpa(const vector<pair<string, double>>& data, const unordered_map<string, double>& gpa_map, double* credit_count) {
    double grades_count = 0.0;
    for (const auto& [grade, credit] : data) {
        if (gpa_map.count(grade)) {
            grades_count += gpa_map.at(grade) * credit;
            *credit_count += credit;
        }
    }
    if (*credit_count == 0) return -1;
    return grades_count / *credit_count;
}


int main() {
    vector<pair<string, double>> zipped = {
        {"B", 3.0}, {"A", 1.0}, {"S", 3.0}, {"P", 1.0}, {"A", 3.0}, {"B", 1.0}, {"B", 3.0}, {"A", 1.0}, {"A", 1.5},
        {"B", 2.0}, {"S", 2.0}, {"B", 3.0}, {"S", 1.0}, {"B", 2.0}, {"A", 1.0}, {"P", 2.0}, {"A", 4.0}, {"C", 3.0},
        {"A", 1.0}, {"A", 1.5}, {"P", 2.0}, {"S", 3.0}, {"A", 3.0}, {"A", 1.0}, {"B", 1.0}, {"A", 2.0}, {"D", 3.0},
        {"B", 4.0}, {"C", 4.0}, {"B", 1.5}, {"A", 3.0}, {"C", 3.0}, {"A", 1.0}, {"C", 3.0}, {"B", 2.0}, {"A", 1.0},
        {"C", 3.0}, {"A", 3.0}, {"B", 3.0}, {"B", 1.0}, {"P", 2.0}, {"B", 1.5}, {"B", 3.0}, {"A", 1.0}, {"A", 3.0},
        {"S", 1.0}, {"B", 3.0}, {"B", 3.0}, {"B", 1.0}, {"B", 3.0}, {"S", 1.0}, {"C", 3.0}, {"P", 2.0}, {"S", 1.5},
        {"B", 3.0}, {"B", 1.0}, {"A", 3.0}, {"D", 3.0}, {"A", 1.0}, {"B", 3.0}, {"C", 3.0}, {"B", 3.0}, {"B", 1.0},
        {"S", 1.5}
    };
    
    unordered_map<string, double> gpa_map = {
        {"S", 4.0}, {"A", 4.0}, {"B", 3.5}, {"C", 3.0}, {"D", 2.5}, {"E", 2.0}, {"F", 0.0}
    };
    
    unordered_map<string, double> cgpa_map = {
        {"S", 10}, {"A", 9.0}, {"B", 8}, {"C", 7}, {"D", 6}, {"E", 5}, {"F", 4}
    };

    vector<tuple<string, int, string, string>> ugc_scale = {
        {"S", 10, "Outstanding", "O"},
        {"A", 9, "Excellent", "A+"},
        {"B", 8, "Very Good", "A"},
        {"C", 7, "Good", "B+"},
        {"D", 6, "Above Average", "B"},
        {"E", 5, "Average", "C"},
        {"F", 0, "Fail", "F"},
    };

    cout << "UGC 10-Point Grading Scale:\n";
    cout << left << setw(8) << "Grade" << setw(8) << "Scale" << setw(15) << "Description" << setw(10) << "US GPA" << "UGC Grade\n";
    for (const auto& [grade, scale, description, us_grade] : ugc_scale) {
        cout << left << setw(8) << grade
             << setw(8) << scale
             << setw(15) << description
             << setw(10) << gpa_map[grade]
             << us_grade << "\n";
    }

    int choice;
    cout << "\nSelect input method:\n1. Use vector data\n2. Enter grades manually\nChoice: ";
    cin >> choice;

    vector<pair<string, double>> input_data;
    if (choice == 1) {
        input_data = zipped;
    } else if (choice == 2) {
        int n;
        cout << "Enter number of subjects: ";
        cin >> n;
        for (int i = 0; i < n; ++i) {
            string grade;
            double credit;
            cout << "Enter grade and credit: ";
            cin >> grade >> credit;
            input_data.emplace_back(grade, credit);
        }
    } else {
        cout << "Invalid choice.\n";
        return 0;
    }
    
    double credit_count = 0.0;
    double* credit_ptr = &credit_count;
    double gpa = calculate_gpa(input_data, gpa_map, credit_ptr);
    credit_count = 0.0;
    double cgpa = calculate_gpa(input_data, cgpa_map, credit_ptr);
    if (gpa == -1) {
        cout << "No valid credits entered.\n";
    } else {
        cout << fixed << setprecision(1);
        cout << "Total Credits: " << credit_count << endl;
        cout << fixed << setprecision(4);
        cout << "Calculated CGPA: " << cgpa << endl;
        cout << "Calculated GPA: " << gpa << endl;
    }

    return 0;
}
