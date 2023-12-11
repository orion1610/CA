#include<bits/stdc++.h>
#include <sstream>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>

using namespace std;

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

int main(){
    ifstream inputFile("ass11.csv");

    if (!inputFile.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    string line;
    getline(inputFile, line);
    map<pair<string,string>,double>r1;
    map<pair<string,string>,double>r2;
    map<pair<string,string>,double>r3;
    map<pair<string,string>,double>r4;
    unordered_map<string,int>mp;
    int tot = 0;
    while(getline(inputFile,line)){
        istringstream ss(line);
        string token;
        char delimiter = ',';
        size_t ind = 0;
        string col;
        string leg;
        string hig;
        string sme;
        string spe;
        while(getline(ss,token,delimiter)){
            if(ind==0){
                col = trim(token);
            }else if(ind==1){
                leg = trim(token);
            }else if(ind==2){
                hig = trim(token);
            }else if(ind==3){
                sme = trim(token);
            }else{
                spe = trim(token);
            }
            ind++;
        }
        //cout<<col<<" "<<leg<<" "<<hig<<" "<<sme<<" "<<spe<<endl;
        mp[spe]++;
        r1[{col,spe}]++;
        r2[{leg,spe}]++;
        r3[{hig,spe}]++;
        r4[{sme,spe}]++;
        tot++;
    }
    for(auto it: r1){
        string col = it.first.first;
        string spe = it.first.second;
        double val = it.second;
        double update = (val)/(double)mp[spe];
        cout<<col<<" "<<spe<<" "<<val<<" "<<update<<endl;
        r1[{col,spe}] = update;
    }
    cout<<endl;
    for(auto it: r2){
        string col = it.first.first;
        string spe = it.first.second;
        double val = it.second;
        double update = (val)/(double)mp[spe];
        cout<<col<<" "<<spe<<" "<<val<<" "<<update<<endl;
        r2[{col,spe}] = update;
    }
    cout<<endl;
    for(auto it: r3){
        string col = it.first.first;
        string spe = it.first.second;
        double val = it.second;
        double update = (val)/(double)mp[spe];
        cout<<col<<" "<<spe<<" "<<val<<" "<<update<<endl;
        r3[{col,spe}] = update;
    }
    cout<<endl;
    for(auto it: r4){
        string col = it.first.first;
        string spe = it.first.second;
        double val = it.second;
        double update = (val)/(double)mp[spe];
        cout<<col<<" "<<spe<<" "<<val<<" "<<update<<endl;
        r4[{col,spe}] = update;
    }
    

    //Calculate for new Value.......

    string col = "Green";
    string leg = "2";
    string hig = "Tall";
    string sme = "No";

    double ans = 0;
    string res;
    vector<pair<string,double>>all;

    for(auto it: mp){
        string s = it.first;
        int get = it.second;
        double prob = (get/(double)tot)*(r1[{col,s}])*(r2[{leg,s}])*(r3[{hig,s}])*(r4[{sme,s}]);
        all.push_back({s,prob});
        if(ans<prob){
            ans = prob;
            res = s;
        }
    }
    for(int i=0; i<all.size(); i++){
        cout<<all[i].first<<" "<<all[i].second<<endl;
    }
    cout<<endl;
    ofstream outputFile("output11.csv");
    cout<<"For color: "<<col<<" leg: "<<leg<<" Height: "<<hig<<" Smelly: "<<sme<<endl;
    outputFile<<"Color,Leg,Height,Smelly,Species(pred)"<<endl;
    cout<<"The resulting Species: "<<res<<endl;
    outputFile<<col<<","<<leg<<","<<hig<<","<<sme<<","<<res<<endl;

}
