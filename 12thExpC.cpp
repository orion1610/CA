
#include<bits/stdc++.h>
using namespace std;

double custom_gini(double class1_count, double class2_count) {
    // Calculate the total count of instance.
    double total_count = class1_count+class2_count;

    // Calculate Gini Index.
    double class1_proportion = class1_count/total_count;
    double class2_proportion = class2_count/total_count;

    double gini_index = 1.0 - pow(class1_proportion, 2.0) - pow(class2_proportion, 2.0);

    return gini_index;
}

double custom_gini_attribute(map<string, map<string, int>> attribute_data, double total_count) {
    double custom_gini = 0.0;

    for(auto attribute_value:attribute_data) {
        string attribute_value_name = attribute_value.first;
        int play_count = attribute_value.second["Yes"];
        int no_play_count = attribute_value.second["No"];

        double total_instance_count = play_count+no_play_count;

        // Calculate Gini Index for current attribute.
        double gini_value = (total_instance_count / total_count) * (1 - (double(play_count) / total_instance_count) * (double(play_count) / total_instance_count) - (double(no_play_count) / total_instance_count) * (double(no_play_count) / total_instance_count));

        custom_gini += gini_value;
    }

    return custom_gini;
}

int main() {
    ifstream file("input_gini.csv");

    string line, word;
    string rain, temp, status, work, inc_weight;

    map<string, int> parent;
    map<string, unordered_set<string>> dist_val;
    map<string, map<string, int>> val_count;
    vector<string> subclass;
    map<string, double> dist_val_count;
    int count = 0;

    double maxGain = DBL_MIN;
    string root = "null";

    if(!file.is_open()) {
        perror("Error in opening input file:");
        return -1;
    }

    int i=0;
    string attributeName, name;
    while(getline(file, line)) {
        stringstream str(line);

        getline(str, rain, ',');
        getline(str, temp, ',');
        getline(str, status, ',');
        getline(str, work, ',');
        getline(str, inc_weight, ',');

        int choice; 
        if(i == 0) {
            i++;

            subclass.push_back("rain");
            subclass.push_back("temp");
            subclass.push_back("status");
            subclass.push_back("work");
            continue;
        }

        dist_val_count[rain]++;
        dist_val_count[temp]++;
        dist_val_count[status]++;
        dist_val_count[work]++;

        parent[inc_weight]++;
        val_count[rain][inc_weight]++;
        val_count[temp][inc_weight]++;
        val_count[status][inc_weight]++;
        val_count[work][inc_weight]++;

        dist_val["rain"].insert(rain);
        dist_val["temp"].insert(temp);
        dist_val["status"].insert(status);
        dist_val["work"].insert(work);

        count++;
    }

    double posR = parent["Yes"], negR = parent["No"];
    double total = posR+negR;

    double class_entropy = -((posR/total) * log2(posR/total) + (negR/total) * log2(negR/total));
    cout<<"Parent Class Entropy:"<<class_entropy<<endl;

    for(int i=0;i<4;i++) {
        double entropy = 0.0;

        for(auto dv:dist_val[subclass[i]]) {
            double tR = dist_val_count[dv];
            double pR = val_count[dv]["Yes"], nR = val_count[dv]["No"];


            if(pR != 0) {
                entropy += -(tR/total) * ((pR/tR) * log2(pR/tR));
            }
            if(nR != 0) {
                entropy += -(tR/total) * ((nR/tR) * log2(nR/tR));
            }
        }

        cout<<endl<<"InfoGain ("<<subclass[i]<<"| inc_weight )"<<entropy<<endl;

        double gain = class_entropy - entropy;

        cout<<"Gain ( "<<subclass[i]<<"| inc_weight )"<<gain<<endl;

        if(gain > maxGain) {
            maxGain = gain;
            root = subclass[i];
        }
    }

    int p1 = parent["Yes"];
    int p2 = parent["No"];

    double gini_parent = custom_gini(p1, p2);
    cout<<endl<<"Gini Index"<<" (Parent class): "<<gini_parent<<endl;

    cout<<endl<<"Best Splliting attribute:"<<root<<endl;

    // Code for Gini Index.
    map<string, map<string, int>> gini;

    for(auto itr:dist_val[root]) {
        gini[itr]["Yes"] = val_count[itr]["Yes"];
        gini[itr]["No"] = val_count[itr]["No"];
    }

    double ans = custom_gini_attribute(gini, count);
    cout<<endl<<"Gini Index of:"<<root<<":"<<ans<<endl;

    return 0;
}
