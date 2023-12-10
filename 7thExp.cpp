#include <bits/stdc++.h>
using namespace std;

ifstream inputFile;
double minFrequencyThreshold;
vector<set<string>> transactions;
set<string> uniqueItems;
map<string, int> itemFrequency;

vector<string> splitWords(string str) {
    vector<string> words;
    string word = "";
    for (char c : str) {
        if (isalnum(c)) {
            word += c;
        } else {
            if (!word.empty()) {
                words.push_back(word);
                word = "";
            }
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

string combineWords(vector<string>& words, int excludeIndex) {
    string combined;
    for (int i = 0; i < words.size(); i++) {
        if (i != excludeIndex) {
            combined += words[i] + " ";
        }
    }
    if (!combined.empty()) {
        combined.pop_back();
    }
    return combined;
}

set<string> cloneItemSet(const set<string>& originalSet) {
    set<string> clonedSet;
    for (const string& item : originalSet) {
        clonedSet.insert(item);
    }
    return clonedSet;
}

set<string> generateCandidateItemSets(set<string>& itemSets, int k) {
    set<string> candidateSet;
    for (const string& item1 : itemSets) {
        for (const string& item2 : itemSets) {
            if (item1 < item2) {
                vector<string> words1 = splitWords(item1);
                vector<string> words2 = splitWords(item2);

                bool allEqual = true;
                for (int i = 0; i < k - 1 && allEqual; i++) {
                    if (words1[i] != words2[i]) {
                        allEqual = false;
                    }
                }

                words1.push_back(words2[k - 1]);
                if (words1.back() < words1[words1.size() - 2]) {
                    swap(words1.back(), words1[words1.size() - 2]);
                }

                for (int i = 0; i < words1.size() && allEqual; i++) {
                    string tmp = combineWords(words1, i);
                    if (itemSets.find(tmp) == itemSets.end()) {
                        allEqual = false;
                    }
                }

                if (allEqual) {
                    candidateSet.insert(combineWords(words1, -1));
                }
            }
        }
    }
    return candidateSet;
}

int main() {
    inputFile.open("input.csv", ios::in);

    if (!inputFile.is_open()) {
        perror("Error in opening file: ");
        return 1;
    }

    cout << "Frequency Threshold (%): ";
    cin >> minFrequencyThreshold;

    string line;
    while (getline(inputFile, line)) {
        vector<string> words = splitWords(line);
        set<string> itemSet;

        for (const string& word : words) {
            itemSet.insert(word);
        }
        transactions.push_back(itemSet);

        for (const string& item : itemSet) {
            uniqueItems.insert(item);
            itemFrequency[item]++;
        }
    }
    inputFile.close();

    cout << "Number of transactions: " << transactions.size() << endl;
    minFrequencyThreshold = minFrequencyThreshold * transactions.size() / 100;
    cout << "Minimum Frequency Threshold: " << minFrequencyThreshold << endl;

    queue<set<string>::iterator> removalQueue;
    for (set<string>::iterator it = uniqueItems.begin(); it != uniqueItems.end(); it++) {
        if (itemFrequency[*it] < minFrequencyThreshold) {
            removalQueue.push(it);
        }
    }

    while (!removalQueue.empty()) {
        uniqueItems.erase(*removalQueue.front());
        removalQueue.pop();
    }

    int pass = 1;
    cout << "\nFrequent " << pass++ << "-item set:\n";
    for (set<string>::iterator it = uniqueItems.begin(); it != uniqueItems.end(); it++) {
        cout << "{" << *it << "} " << itemFrequency[*it] << endl;
    }

    int k = 2;
    set<string> previousSet = cloneItemSet(uniqueItems);

    while (k) {
        set<string> currentSet = generateCandidateItemSets(previousSet, k - 1);

        if (currentSet.empty()) {
            break;
        }

        for (set<string>::iterator it = currentSet.begin(); it != currentSet.end(); it++) {
            vector<string> words = splitWords(*it);
            int totalCount = 0;

            for (int j = 0; j < transactions.size(); j++) {
                bool present = true;

                for (const string& word : words) {
                    if (transactions[j].find(word) == transactions[j].end()) {
                        present = false;
                        break;
                    }
                }

                if (present) {
                    totalCount++;
                }
            }

            if (totalCount >= minFrequencyThreshold) {
                itemFrequency[*it] += totalCount;
            } else {
                removalQueue.push(it);
            }
        }

        while (!removalQueue.empty()) {
            currentSet.erase(*removalQueue.front());
            removalQueue.pop();
        }

        bool flag = true;
        for (set<string>::iterator it = currentSet.begin(); it != currentSet.end(); it++) {
            if (itemFrequency[*it] < minFrequencyThreshold) {
                flag = false;
                break;
            }
        }

        if (currentSet.empty()) {
            break;
        }

        cout << "\n\nFrequent " << pass++ << "-item set:\n";
        for (set<string>::iterator it = currentSet.begin(); it != currentSet.end(); it++) {
            cout << "{" << *it << "} " << itemFrequency[*it] << endl;
        }

        previousSet = cloneItemSet(currentSet);
        k++;
    }

    ofstream outputFile("output.csv", ios::out);

    for (const string& item : previousSet) {
        outputFile << "{" << item << "}\n";
    }

    return 0;
}
