#include <bits/stdc++.h>
using namespace std;

ifstream custom_input;
double custom_min_support;
vector<set<string>> custom_data;
set<string> custom_items;
map<string, int> custom_item_count;
double custom_min_confidence;

vector<string> customSplitString(string str) {
    vector<string> words;
    string temp = "";
    for (char c : str) {
        if (isalnum(c))
            temp += c;
        else {
            if (!temp.empty())
                words.push_back(temp);
            temp = "";
        }
    }

    if (!temp.empty())
        words.push_back(temp);

    return words;
}

string customCombineStrings(vector<string> &strings, int exclude_index) {
    string combined;
    for (int i = 0; i < strings.size(); i++) {
        if (i != exclude_index)
            combined += strings[i] + " ";
    }
    combined = combined.substr(0, combined.size() - 1);
    return combined;
}

set<string> customCloneSet(set<string> &original) {
    set<string> duplicate;
    for (const string &item : original)
        duplicate.insert(item);
    return duplicate;
}

set<string> customGenerateCandidates(set<string> &item_sets, int k) {
    set<string> new_set;
    for (set<string>::iterator it1 = item_sets.begin(); it1 != item_sets.end(); it1++) {
        set<string>::iterator it2 = it1;
        it2++;
        for (; it2 != item_sets.end(); it2++) {
            vector<string> v1 = customSplitString(*it1);
            vector<string> v2 = customSplitString(*it2);

            bool all_equal = true;
            for (int i = 0; i < k - 1 && all_equal; i++) {
                if (v1[i] != v2[i])
                    all_equal = false;
            }

            v1.push_back(v2[k - 1]);
            if (v1[v1.size() - 1] < v1[v1.size() - 2])
                swap(v1[v1.size() - 1], v1[v1.size() - 2]);

            for (int i = 0; i < v1.size() && all_equal; i++) {
                string temp = customCombineStrings(v1, i);
                if (item_sets.find(temp) == item_sets.end())
                    all_equal = false;
            }
            if (all_equal)
                new_set.insert(customCombineStrings(v1, -1));
        }
    }
    return new_set;
}

int customCountOccurrences(vector<string> items) {
    int count = 0;

    for (auto transaction : custom_data) {
        bool present = true;

        for (auto item : items) {
            if (transaction.find(item) == transaction.end()) {
                present = false;
                break;
            }
        }

        if (present)
            count++;
    }

    return count;
}

ofstream custom_output("output.csv", ios::out);

void customGenerateSubsets(vector<string> items, vector<string> set1, vector<string> set2, int index) {
    if (index == items.size()) {
        if (set1.empty() || set2.empty())
            return;

        int count1 = customCountOccurrences(items);
        int count2 = customCountOccurrences(set1);

        double confidence = (((double)count1) / count2) * 100;

        if (confidence >= custom_min_confidence) {
            custom_output << "Association Rule: { ";
            for (auto item : set1) {
                custom_output << item << " ";
            }
            custom_output << "} -> {";
            for (auto item : set2) {
                custom_output << item << " ";
            }
            custom_output << "} , Confidence: " << confidence << "%" << endl;
        }

        return;
    }

    set1.push_back(items[index]);
    customGenerateSubsets(items, set1, set2, index + 1);

    set1.pop_back();
    set2.push_back(items[index]);
    customGenerateSubsets(items, set1, set2, index + 1);
    set2.pop_back();
}

void customGenerateAssociationRules(set<string> frequent_items) {
    for (auto it = frequent_items.begin(); it != frequent_items.end(); it++) {
        vector<string> items = customSplitString(*it);
        customGenerateSubsets(items, {}, {}, 0);
    }
}

int main() {
    custom_input.open("input.csv", ios::in);

    if (!custom_input.is_open()) {
        cerr << "Error in opening file." << endl;
        return 1;
    }

    cout << "Enter Minimum Support (%): ";
    cin >> custom_min_support;

    cout << "Enter Minimum Confidence (%): ";
    cin >> custom_min_confidence;

    string line;
    while (!custom_input.eof()) {
        getline(custom_input, line);
        vector<string> words = customSplitString(line);
        set<string> item_set;
        for (int i = 0; i < words.size(); i++)
            item_set.insert(words[i]);
        custom_data.push_back(item_set);

        for (set<string>::iterator it = item_set.begin(); it != item_set.end(); it++) {
            custom_items.insert(*it);
            custom_item_count[*it]++;
        }
    }
    custom_input.close();

    cout << "Number of transactions: " << custom_data.size() << endl;
    custom_min_support = custom_min_support * custom_data.size() / 100;
    cout << "Minimum Support Threshold: " << custom_min_support << endl;

    queue<set<string>::iterator> custom_removal_queue;
    for (set<string>::iterator it = custom_items.begin(); it != custom_items.end(); it++)
        if (custom_item_count[*it] < custom_min_support)
            custom_removal_queue.push(it);

    while (!custom_removal_queue.empty()) {
        custom_items.erase(*custom_removal_queue.front());
        custom_removal_queue.pop();
    }

    int custom_pass = 1;
    cout << "Frequent " << custom_pass++ << "-item set: " << endl;
    for (set<string>::iterator it = custom_items.begin(); it != custom_items.end(); it++)
        cout << "{" << *it << "} - Support: " << custom_item_count[*it] << endl;

    int k = 2;
    set<string> custom_previous_set = customCloneSet(custom_items);

    while (k) {
        set<string> current_set = customGenerateCandidates(custom_previous_set, k - 1);

        if (current_set.empty()) {
            break;
        }

        for (set<string>::iterator it = current_set.begin(); it != current_set.end(); it++) {
            vector<string> items = customSplitString(*it);

            int total_count = 0;
            for (int j = 0; j < custom_data.size(); j++) {
                bool present = true;
                for (int i = 0; i < items.size() && present; i++)
                    if (custom_data[j].find(items[i]) == custom_data[j].end())
                        present = false;
                if (present)
                    total_count++;
            }
            if (total_count >= custom_min_support)
                custom_item_count[*it] += total_count;
            else
                custom_removal_queue.push(it);
        }

        while (!custom_removal_queue.empty()) {
            current_set.erase(*custom_removal_queue.front());
            custom_removal_queue.pop();
        }

        bool flag = true;

        for (set<string>::iterator it = current_set.begin(); it != current_set.end(); it++) {
            vector<string> items = customSplitString(*it);

            if (custom_item_count[*it] < custom_min_support)
                flag = false;
        }

        if (current_set.empty())
            break;

        cout << "\nFrequent " << custom_pass++ << "-item set: " << endl;
        for (set<string>::iterator it = current_set.begin(); it != current_set.end(); it++)
            cout << "{" << *it << "} - Support: " << custom_item_count[*it] << endl;

        custom_previous_set = customCloneSet(current_set);
        k++;
    }

    customGenerateAssociationRules(custom_previous_set);

    cout << "Association rules generated successfully." << endl;

    return 0;
}
