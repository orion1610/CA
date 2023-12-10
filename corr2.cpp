#include <bits/stdc++.h>
using namespace std;

double find_corelation(vector<double>x, vector<double>y){
    double n = x.size();
    int x_yes_count= 0;
    int y_yes_count= 0;
    int xy_yes_count = 0;

    for(int i = 0;i<n; i++){
        if(x[i] == 1){
            x_yes_count++;
        }
        if(y[i] == 1){
            y_yes_count++;
        }
        if(x[i] == 1 && y[i]== 1){
            xy_yes_count++;
        }
    }

    double ans = (xy_yes_count/n)/((x_yes_count/n)*(y_yes_count/n));
    return ans;

}

int main(){
   vector<vector<double>>data;
   ifstream input("correlation.csv");
   string line;
   while(getline(input, line)){
    vector<double>d;
    stringstream str(line);
    string s;
    while(getline(str, s, ',')){
        d.push_back(stod(s));
    }
    data.push_back(d);
   }
    ofstream output("correlation_output.csv");
    output << "Corelation," << "Value," << "Analysis" << endl;
    for(int i = 0; i<data.size()-1; i++){
        for(int j = i+1; j<data.size(); j++){
            double corelation = find_corelation(data[i], data[j]); 
            output << i+1<<" "<<j+1 <<","<< corelation<<",";
            if(corelation > 1){
                output << "Positive Correlation"<< endl;
            }
            else if(corelation == 1){
                output<<"Independent" << endl;
            }
            else{
                output<<"Negative Corelation"<<endl;
            }
        }
    }
    
}