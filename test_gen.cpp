#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

const int studentIdSeed = 25120459;
const int largeSize = 100000;
const int smallSize = 10000;

int generateRandomInt(int minValue, int maxValue) {
    static mt19937 numberGenerator(studentIdSeed);
    uniform_int_distribution<int> valueDistribution(minValue, maxValue);
    return valueDistribution(numberGenerator);
}

string generateRandomString(int stringLength) {
    string resultString = "";
    for (int i = 0; i < stringLength; i++) {
        int randomNumber = generateRandomInt(0, 25);
        char randomChar = (char)('a' + randomNumber);
        resultString += randomChar;
    }
    return resultString;
}

void mergeStrings(vector<string>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<string> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSortStrings(vector<string>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortStrings(arr, left, mid);
        mergeSortStrings(arr, mid + 1, right);
        mergeStrings(arr, left, mid, right);
    }
}

void generateIntTest(int testId) {
    cout << largeSize << "\n";
    vector<int> numberArray(largeSize);

    if (testId == 1) {
        for (int i = 0; i < largeSize; i++) {
            cout << generateRandomInt(-2000000000, 2000000000) << "\n";
        }
    } 
    else if (testId == 2) {
        for (int i = 0; i < largeSize; i++) {
            numberArray[i] = i - 49000;
            cout << numberArray[i] << "\n";
        }
    } 
    else if (testId == 3) {
        for (int i = 0; i < largeSize; i++) {
            numberArray[i] = 49000 - i;
            cout << numberArray[i] << "\n";
        }
    } 
    else if (testId == 4) {
        for (int i = 0; i < largeSize; i++) {
            cout << 9999 << "\n";
        }
    } 
    else if (testId == 5) {
        for (int i = 0; i < largeSize; i++) {
            cout << generateRandomInt(-2000000000, -1) << "\n";
        }
    }
}

void generateStrLexiTest(int testId) {
    cout << largeSize << "\n";

    if (testId == 1) {
        for (int i = 0; i < largeSize; i++) {
            int randomLength = generateRandomInt(12, 98);
            cout << generateRandomString(randomLength) << "\n";
        }
    } 
    else if (testId == 2) {
        for (int i = 0; i < largeSize; i++) {
            cout << generateRandomString(98) << "\n";
        }
    } 
    else if (testId == 3) {
        string commonPrefix = generateRandomString(88);
        for (int i = 0; i < largeSize; i++) {
            string suffixPart = generateRandomString(10);
            cout << commonPrefix + suffixPart << "\n";
        }
    } 
    else if (testId == 4) {
        vector<string> stringArray(largeSize);
        for (int i = 0; i < largeSize; i++) {
            stringArray[i] = generateRandomString(15);
        }
        mergeSortStrings(stringArray, 0, largeSize - 1);
        for (int i = 0; i < largeSize; i++) {
            cout << stringArray[i] << "\n";
        }
    } 
    else if (testId == 5) {
        string identicalString = generateRandomString(50);
        for (int i = 0; i < largeSize; i++) {
            cout << identicalString << "\n";
        }
    }
}

void generateStrLenLexiTest(int testId) {
    cout << smallSize << "\n";

    if (testId == 1) {
        for (int i = 0; i < smallSize; i++) {
            int randomLength = generateRandomInt(12, 98);
            cout << generateRandomString(randomLength) << "\n";
        }
    } 
    else if (testId == 2) {
        for (int i = 0; i < smallSize; i++) {
            int probabilityRatio = generateRandomInt(1, 100);
            if (probabilityRatio == 1) {
                cout << generateRandomString(98) << "\n";
            } else {
                cout << generateRandomString(12) << "\n";
            }
        }
    } 
    else if (testId == 3) {
        string commonPrefix = generateRandomString(78);
        for (int i = 0; i < smallSize; i++) {
            string suffixPart = generateRandomString(20);
            cout << commonPrefix + suffixPart << "\n";
        }
    } 
    else if (testId == 4) {
        for (int i = 0; i < smallSize; i++) {
            if (i % 2 == 0) {
                cout << generateRandomString(12) << "\n";
            } else {
                cout << generateRandomString(95) << "\n";
            }
        }
    } 
    else if (testId == 5) {
        string identicalString = generateRandomString(98);
        for (int i = 0; i < smallSize; i++) {
            cout << identicalString << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (argc != 3) {
        return 1;
    }

    string dataType = argv[1];
    int testId = stoi(argv[2]);

    if (testId < 1 || testId > 5) {
        return 1;
    }

    if (dataType == "int") {
        generateIntTest(testId);
    } 
    else if (dataType == "strlexi") {
        generateStrLexiTest(testId);
    } 
    else if (dataType == "strlenlexi") {
        generateStrLenLexiTest(testId);
    } 
    else {
        return 1;
    }

    return 0;
}