#include <bits/stdc++.h>
using namespace std;

class CellData {
public:
    int value;
    int totalWeight;
    int rowWeight;

    CellData() : value(0), totalWeight(0), rowWeight(0) {}
};

class CSVProcessor {
private:
    map<string, map<string, CellData>> cellData;
    map<string, int> columnTotal;
    map<string, int> rowTotal;
    string inputFilename;
    string outputFilename;

public:
    CSVProcessor(const string &input, const string &output)
        : inputFilename(input), outputFilename(output) {}

    void processCSV() {
        readCSVData();
        writeCSVResult();
    }

private:
    void readCSVData() {
        fstream file(inputFilename, ios::in);
        if (!file.is_open()) {
            cout << "Error: Unable to open file: " << inputFilename << endl;
            return;
        }

        string line, row, col, value;
        int lineNumber = 0;

        while (getline(file, line)) {
            if (lineNumber++ == 0) continue; // Skip header line

            stringstream str(line);
            getline(str, row, ',');
            getline(str, col, ',');
            getline(str, value, ',');

            int val = stoi(value);
            cellData[row][col].value += val;
            columnTotal[col] += val;
            rowTotal[row] += val;
        }

        file.close();
    }

    void writeCSVResult() {
    ofstream output(outputFilename, ios::out);
    if (!output.is_open()) {
        cout << "Error: Unable to open file: " << outputFilename << endl;
        return;
    }

    // Write header
    output << "Row/Column";
    for (const auto &colEntry : columnTotal) {
        output << ", " << colEntry.first << " Value, " << colEntry.first << " Total Weight, " << colEntry.first << " Row Weight";
    }
    output << ", Total\n";

    // Write data for each row
    for (const auto &rowEntry : cellData) {
        const string &row = rowEntry.first;
        output << row;
        for (const auto &colEntry : rowEntry.second) {
            const string &col = colEntry.first;
            const CellData &cell = colEntry.second;
            output << ", " << cell.value
                   << ", " << static_cast<float>(cell.value) / rowTotal[row] * 100 << "%"
                   << ", " << static_cast<float>(cell.value) / columnTotal[col] * 100 << "%";
        }
        output << ", " << rowTotal[row] << "\n";
    }

    // Write column totals
    output << "Total";
    for (const auto &colEntry : columnTotal) {
        output << ", " << colEntry.second
               << ", " << static_cast<float>(colEntry.second) / columnTotal[colEntry.first] * 100 << "%"
               << ", 100%";
    }
    output << "\n";

    output.close();
}

};

int main() {
    CSVProcessor csvProcessor("input.csv", "output.csv");
    csvProcessor.processCSV();

    cout << "Data processing complete. Results saved to 'output.csv'." << endl;
    return 0;
}
