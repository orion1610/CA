#include<bits/stdc++.h>
using namespace std;

double custom_gini(double class1_count, double class2_count) {
    // Calculate total count of instance.
    double total_count = class1_count+class2_count;

    double class1_proportion = class1_count/total_count;
    double class2_proportion = class2_count/total_count;

    double gini_index = 1.0 - pow(class1_proportion, 2.0) - pow(class2_proportion, 2.0);

    return gini_index;
}

double custom_gini_attribute(map<string, map<string, int>> attribute_data, double total_count) {
    double custom_gini = 0.0;

    for(auto value:attribute_data) {
        string name = value.first;
        int yes_count = value.second["Yes"];
        int no_count = value.second["No"];

        double total_inst_count = yes_count+no_count;

        double gini_value = (total_inst_count / total_count) * (1 - (double(yes_count) /total_inst_count) * (double(yes_count) / total_inst_count) - (double(no_count) / total_inst_count) * (double(no_count) / total_inst_count));

        custom_gini += gini_value;
    }

    return custom_gini;
}

int main() {

    ifstream file("input.csv");
    vector<string> sub_classes;
    map<string, int> mainClass;
    map<string, unordered_set<string>> dist_val;
    map<string, int> dist_val_count;
    map<string, map<string, int>> val_count;

    double maxGain = DBL_MIN;
    string root = "null";

    ofstream out_file("output.csv");

    string line, word;
    string day, outlook, temp, humidity, wind, playGame;

    if(!file.is_open()) {
        perror("Couldn't open the file");
        return -1;
    }

    int j=0;
    string main_class = "playgame";

    while(getline(file, line)) {
        stringstream str(line);

        getline(str, day, ',');
        getline(str, outlook, ',');
        getline(str, temp, ',');
        getline(str, humidity, ',');
        getline(str, wind, ',');
        getline(str, playGame, ',');

        if(j == 0) {
            j++;
            sub_classes.push_back(day);
            sub_classes.push_back(outlook);
            sub_classes.push_back(temp);
            sub_classes.push_back(humidity);
            sub_classes.push_back(wind);
            continue;
        }

        dist_val["day"].insert(day);
        dist_val["outlook"].insert(outlook);
        dist_val["temp"].insert(temp);
        dist_val["humidity"].insert(humidity);
        dist_val["wind"].insert(wind);

        mainClass[playGame]++;

        dist_val_count[day]++;
        dist_val_count[outlook]++;
        dist_val_count[temp]++;
        dist_val_count[humidity]++;
        dist_val_count[wind]++;

        val_count[day][playGame]++;
        val_count[outlook][playGame]++;
        val_count[temp][playGame]++;
        val_count[humidity][playGame]++;
        val_count[wind][playGame]++;
    }

    double posR = mainClass["Yes"], negR = mainClass["No"];
    double totR = posR+negR;

    double mainC_gain = -((posR/totR) * log2(posR/totR) + (negR/totR) * log2(negR/totR));

    cout<<"Main Class Gain: "<<mainC_gain<<endl;

    for(int i=1;i<5;i++) {
        double totR = mainClass["Yes"] + mainClass["No"];
        double entropy = 0;

        for(auto dv:dist_val[sub_classes[i]]) {
            double tR = dist_val_count[dv];
            double pR = val_count[dv]["Yes"], nR = val_count[dv]["No"];

            if(pR != 0) {
                entropy += - (tR/totR) * ((pR/tR) * log2(pR/tR));
            }
            if(nR != 0) {
                entropy += -((tR/totR) * (nR/tR) * log2(nR/tR));
            }
        }

        cout<<"InfoGain ( "<<sub_classes[i]<<"|"<<"playGame ) : "<<entropy<<endl;
        out_file<<"InfoGain ( "<<sub_classes[i]<<"|"<<"playGame ),"<<entropy<<endl;

        double gain = mainC_gain-entropy;

        cout<<"Gain ( "<<sub_classes[i]<<"|"<<"playGame ) : "<<gain<<endl;
        out_file<<"Gain ( "<<sub_classes[i]<<"|"<<"playGame ),"<<gain<<endl;

        if(gain > maxGain) {
            maxGain = gain;
            root = sub_classes[i];
        }
    }

    cout<<"SubClass : "<<root<<" has maximum gain. Hence it will be selected as root for splitting."<<endl;
    out_file<<"SubClass : "<<root<<" has maximum gain. Hence it will be selected as root for splitting."<<endl;

    double gini_parent = custom_gini(posR, negR);
    cout<<"Gini Index of Parent class:"<<gini_parent<<endl;

    for(auto itr:dist_val_count) {
        cout<<itr.first<<" "<<itr.second<<endl;
    }
    
    return 0;
}