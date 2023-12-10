#include<bits/stdc++.h>
using namespace std;

double findMedian(vector<double> &data){
    int size = data.size();

    if(size%2==1){
        return data[size/2];
    }
    else{
        return (data[size/2-1]+data[size/2])/2.0;
    }
}

double findFquar(vector<double> &data){
    int n = data.size();
    vector<double> lower(data.begin(), data.begin()+n/2);
    return findMedian(lower);
}

double findSquar(vector<double> &data){
    int n = data.size();
    vector<double> upper(data.begin()+(n+1)/2, data.end());
    return findMedian(upper);
}

int main(){
    ifstream inputfile("input.csv");
    ofstream outputfile("output.csv");

    if(!inputfile.is_open() || !outputfile.is_open()){
        cout<<"Error opening input or output file"<<endl;
        return 1;
    }

    inputfile.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<double> data;
    
    string line;
    while(getline(inputfile, line)){
        data.push_back(stod(line));
    }
    inputfile.close();

    sort(data.begin(), data.end());
    double median = findMedian(data);
    double fquar = findFquar(data);
    double squar = findSquar(data);

    outputfile<<"Minimum"<<','<<data[0]<<endl;
    outputfile<<"1st Quartile"<<','<<fquar<<endl;
    outputfile<<"Median"<<','<<median<<endl;
    outputfile<<"2nd Quartile"<<','<<squar<<endl;
    outputfile<<"Maximum"<<','<<data[data.size()-1]<<endl;


    outputfile.close();
    cout<<"Results stored in output.csv"<<endl;

}