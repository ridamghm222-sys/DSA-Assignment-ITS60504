#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace chrono;

// Structure to hold data records
struct DataRecord {
    int value;
    int index;
    
    DataRecord(int v = 0, int i = 0) : value(v), index(i) {}
};

// Global vector to store records
vector<DataRecord> records;

// Function prototypes
void generateDummyData(int size);
void displayAllRecords();
void selectionSort(vector<DataRecord>& arr);
void quickSort(vector<DataRecord>& arr, int low, int high);
int partition(vector<DataRecord>& arr, int low, int high);
void mergeSort(vector<DataRecord>& arr, int left, int right);
void merge(vector<DataRecord>& arr, int left, int mid, int right);
int binarySearch(const vector<DataRecord>& arr, int target);
int interpolationSearch(const vector<DataRecord>& arr, int target);
void sortMenu();
void searchMenu();
void displayMenu();

// ==================== DATA POPULATION ====================
void generateDummyData(int size) {
    records.clear();
    srand(time(0));
    for (int i = 0; i < size; i++) {
        int randomValue = rand() % 10000 + 1; // Values between 1 and 10000
        records.push_back(DataRecord(randomValue, i + 1));
    }
    cout << "Successfully generated " << size << " dummy records!" << endl;
}

// ==================== DISPLAY ALL RECORDS ====================
void displayAllRecords() {
    if (records.empty()) {
        cout << "\n[ERROR] No records found! Please generate data first." << endl;
        return;
    }
    
    cout << "\n================================================================" << endl;
    cout << "                    ALL RECORDS DISPLAY" << endl;
    cout << "================================================================" << endl;
    cout << left << setw(10) << "Index" << setw(15) << "Record ID" << setw(20) << "Value" << endl;
    cout << "---------------------------------------------------------------" << endl;
    
    for (size_t i = 0; i < records.size(); i++) {
        cout << left << setw(10) << i + 1 
             << setw(15) << records[i].index 
             << setw(20) << records[i].value << endl;
    }
    cout << "================================================================" << endl;
    cout << "Total Records: " << records.size() << endl;
}

// ==================== SORTING ALGORITHMS ====================

// a) Selection Sort
void selectionSort(vector<DataRecord>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].value < arr[minIdx].value) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
        }
    }
}

// b) Quick Sort
int partition(vector<DataRecord>& arr, int low, int high) {
    int pivot = arr[high].value;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j].value <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<DataRecord>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// c) Merge Sort
void merge(vector<DataRecord>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<DataRecord> leftArr(n1);
    vector<DataRecord> rightArr(n2);
    
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (leftArr[i].value <= rightArr[j].value) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(vector<DataRecord>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// ==================== SEARCHING ALGORITHMS ====================

// a) Binary Search
int binarySearch(const vector<DataRecord>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid].value == target) {
            return mid;
        }
        if (arr[mid].value < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// b) Interpolation Search
int interpolationSearch(const vector<DataRecord>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
    
    while (low <= high && target >= arr[low].value && target <= arr[high].value) {
        if (low == high) {
            if (arr[low].value == target) return low;
            return -1;
        }
        
        // Interpolation formula
        int pos = low + ((double)(high - low) / (arr[high].value - arr[low].value)) 
                  * (target - arr[low].value);
        
        // Ensure pos is within bounds
        if (pos < low || pos > high) {
            return -1;
        }
        
        if (arr[pos].value == target) {
            return pos;
        }
        
        if (arr[pos].value < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    return -1;
}

// ==================== SORT MENU FUNCTION ====================
void sortMenu() {
    if (records.empty()) {
        cout << "\n[ERROR] No records found! Please generate data first." << endl;
        return;
    }
    
    cout << "\n================================================================" << endl;
    cout << "                     SORTING ALGORITHMS" << endl;
    cout << "================================================================" << endl;
    cout << "a) Selection Sort" << endl;
    cout << "b) Quick Sort" << endl;
    cout << "c) Merge Sort" << endl;
    cout << "================================================================" << endl;
    cout << "Enter your choice (a/b/c): ";
    
    char choice;
    cin >> choice;
    
    vector<DataRecord> tempRecords = records; // Copy for sorting
    auto start = high_resolution_clock::now();
    
    switch (choice) {
        case 'a':
        case 'A':
            selectionSort(tempRecords);
            cout << "\n[SUCCESS] Selection Sort completed!" << endl;
            break;
        case 'b':
        case 'B':
            quickSort(tempRecords, 0, tempRecords.size() - 1);
            cout << "\n[SUCCESS] Quick Sort completed!" << endl;
            break;
        case 'c':
        case 'C':
            mergeSort(tempRecords, 0, tempRecords.size() - 1);
            cout << "\n[SUCCESS] Merge Sort completed!" << endl;
            break;
        default:
            cout << "\n[ERROR] Invalid choice!" << endl;
            return;
    }
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    
    cout << "Time taken: " << duration.count() << " ms" << endl;
    
    // Update records with sorted data
    records = tempRecords;
    cout << "Records have been sorted in ascending order!" << endl;
    
    // Display first 10 records after sorting
    cout << "\nFirst 10 records after sorting:" << endl;
    cout << left << setw(10) << "Index" << setw(15) << "Record ID" << setw(20) << "Value" << endl;
    cout << "---------------------------------------------------------------" << endl;
    for (int i = 0; i < min(10, (int)records.size()); i++) {
        cout << left << setw(10) << i + 1 
             << setw(15) << records[i].index 
             << setw(20) << records[i].value << endl;
    }
}

// ==================== SEARCH MENU FUNCTION ====================
void searchMenu() {
    if (records.empty()) {
        cout << "\n[ERROR] No records found! Please generate data first." << endl;
        return;
    }
    
    cout << "\n================================================================" << endl;
    cout << "                     SEARCHING ALGORITHMS" << endl;
    cout << "================================================================" << endl;
    cout << "a) Binary Search" << endl;
    cout << "b) Interpolation Search" << endl;
    cout << "================================================================" << endl;
    cout << "Enter your choice (a/b): ";
    
    char choice;
    cin >> choice;
    
    int target;
    cout << "Enter the number to search: ";
    cin >> target;
    
    // Check if records are sorted (required for binary and interpolation search)
    bool isSorted = true;
    for (size_t i = 1; i < records.size(); i++) {
        if (records[i].value < records[i-1].value) {
            isSorted = false;
            break;
        }
    }
    
    if (!isSorted) {
        cout << "\n[WARNING] Records are not sorted! Searching on unsorted data may yield incorrect results." << endl;
        cout << "Please sort the data first using the Sort menu." << endl;
        return;
    }
    
    auto start = high_resolution_clock::now();
    int result = -1;
    
    switch (choice) {
        case 'a':
        case 'A':
            result = binarySearch(records, target);
            cout << "\n[INFO] Binary Search executed." << endl;
            break;
        case 'b':
        case 'B':
            result = interpolationSearch(records, target);
            cout << "\n[INFO] Interpolation Search executed." << endl;
            break;
        default:
            cout << "\n[ERROR] Invalid choice!" << endl;
            return;
    }
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    
    if (result != -1) {
        cout << "[SUCCESS] Target " << target << " found at position " << result + 1 << endl;
        cout << "Record ID: " << records[result].index << endl;
        cout << "Value: " << records[result].value << endl;
    } else {
        cout << "[INFO] Target " << target << " not found in the dataset." << endl;
    }
    
    cout << "Search time: " << duration.count() << " ms" << endl;
}

// ==================== MAIN MENU ====================
void displayMenu() {
    cout << "\n================================================================" << endl;
    cout << "          DATA STRUCTURES & ALGORITHMS APPLICATION" << endl;
    cout << "================================================================" << endl;
    cout << "A. Display All Records" << endl;
    cout << "B. Sort Records" << endl;
    cout << "C. Search for Number" << endl;
    cout << "D. Exit Application" << endl;
    cout << "================================================================" << endl;
    cout << "Enter your choice (A/B/C/D): ";
}

// ==================== MAIN FUNCTION ====================
int main() {
    cout << "\n================================================================" << endl;
    cout << "          DATA STRUCTURES & ALGORITHMS APPLICATION" << endl;
    cout << "================================================================" << endl;
    cout << "Initializing system..." << endl;
    
    // Generate initial data
    generateDummyData(100);
    cout << "System ready!" << endl;
    
    char choice;
    do {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 'a':
            case 'A':
                displayAllRecords();
                break;
            case 'b':
            case 'B':
                sortMenu();
                break;
            case 'c':
            case 'C':
                searchMenu();
                break;
            case 'd':
            case 'D':
                cout << "\n[INFO] Exiting application. Goodbye!" << endl;
                break;
            default:
                cout << "\n[ERROR] Invalid choice! Please try again." << endl;
        }
    } while (choice != 'd' && choice != 'D');
    
    return 0;
}
