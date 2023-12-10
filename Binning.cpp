#include <bits/stdc++.h>
using namespace std;
class DataBinning {
private:
    vector<double> data;
    vector<double> equalFrequencyBins;
    vector<double> equalWidthBins;

public:
    DataBinning() {}

    void readData(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                double value;
                istringstream iss(line);
                if (iss >> value) {
                    data.push_back(value);
                }
            }
            file.close();
        } else {
            cerr << "Error: Cannot open input file." << endl;
        }
    }

    void calculateEqualFrequencyBins(int numBins) {
        sort(data.begin(), data.end());
        int dataSize = data.size();
        int binSize = dataSize / numBins;
        int remainder = dataSize % numBins;
        int currentIndex = 0;

        ofstream file("equal_frequency_bins.csv");
        if (file.is_open()) {
            for (int i = 0; i < numBins; i++) {
                int binStart = currentIndex;
                int binEnd = binStart + binSize;
                if (remainder > 0) {
                    binEnd++;
                    remainder--;
                }

                double binValue = data[binEnd - 1];
                equalFrequencyBins.push_back(binValue);

                file << "Bin " << i << " contains: ";
                for (int j = binStart; j < binEnd; j++) {
                    file << data[j] << " ";
                }
                file << endl;

                currentIndex = binEnd;
            }
            file.close();
        } else {
            cerr << "Error: Cannot open output file for equal frequency bins." << endl;
        }
    }

    void calculateEqualWidthBins(int numBins) {
        double minVal = *min_element(data.begin(), data.end());
        double maxVal = *max_element(data.begin(), data.end());
        double binWidth = (maxVal - minVal) / numBins;

        ofstream file("equal_width_bins.csv");
        if (file.is_open()) {
            for (int i = 0; i < numBins; i++) {
                double binStart = minVal + i * binWidth;
                double binEnd = binStart + binWidth;
                equalWidthBins.push_back(binEnd);

                file << "Bin " << i << " [" << binStart << " - " << binEnd << "] contains: ";
                for (int j = 0; j < data.size(); j++) {
                    if (data[j] > binStart && data[j] <= binEnd) {
                        file << data[j] << " ";
                    }
                }
                file << endl;
            }
            file.close();
        } else {
            cerr << "Error: Cannot open output file for equal width bins." << endl;
        }
    }
};

int main() {
    DataBinning binning;

    binning.readData("input.csv");

    int numEqualFrequencyBins, numEqualWidthBins;

    cout << "Enter the number of equal frequency bins: ";
    cin >> numEqualFrequencyBins;
    binning.calculateEqualFrequencyBins(numEqualFrequencyBins);

    cout << "Enter the number of equal width bins: ";
    cin >> numEqualWidthBins;
    binning.calculateEqualWidthBins(numEqualWidthBins);

    return 0;
}


