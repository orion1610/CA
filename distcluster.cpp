#include<bits/stdc++.h>
using namespace std;

double distance(double x1, double y1, int x2, int y2){
    return sqrt(((double)x2 - x1) * ((double)x2 - x1) + ((double)y2 - y1) * ((double)y2 - y1));
}

int main(){
    ifstream inputfile("input.csv");
    ofstream outputfile("output.csv");
    double x=0, y=0;
    if(!inputfile.is_open() || !outputfile.is_open()){
            cout<<"error opening the file"<<endl;
            return 1;
    }

    string header;
    getline(inputfile, header);

    vector<pair<double, double>> points;
    string line;
    while(getline(inputfile, line)){
        stringstream ss(line);
        string value;

        // to skip 1st value of each row
        getline(ss, value, ',');


        getline(ss, value, ',');
        x = stod(value);
        getline(ss, value, ',');
        y = stod(value);

        points.push_back(make_pair(x,y));
    }

    double xcent = 0.0, ycent = 0.0;

    for(int i=0; i<points.size(); i++){
        xcent+=points[i].first;
        ycent+=points[i].second;
    }
    xcent = xcent/points.size();
    ycent = ycent/points.size();
    cout<<"Mid-point of the given points is ("<<xcent<<","<<ycent<<")";

    outputfile<<"row/column, C,";

    for(int i=0; i<points.size(); i++){
        outputfile<<"p"+to_string(i)<<",";
    }
    outputfile<<endl;
    outputfile<<"C"<<","<<"0"<<endl;
    for (int i = 0; i < points.size(); i++) {
        outputfile <<"p" + to_string(i) << ", ";
        outputfile << distance(points[i].first, points[i].second, xcent, ycent)<<",";

        for (int j = 0; j <=i; ++j) {
            double dist = distance(points[i].first, points[i].second, points[j].first, points[j].second);
            outputfile << dist << ", ";
        }

        outputfile << endl;
    }

}