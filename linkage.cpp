
#include<bits/stdc++.h>
using namespace std;

int op = 1;
ofstream finalout_file("output.csv");

string agglomerative(string input) {

    ifstream file(input);

    map<string, map<string, int>> dist_matrix;
    string line;
    getline(file, line);
    
    int pt=0;
    stringstream str1(line);

    int i=0;
    string point;
    vector<string> points;

    while(getline(str1, point, ',')) {
        if(i == 0) {
            i++;continue;
        }
        points.push_back(point);
    }

    while(getline(file, line)) {
        stringstream str2(line);

        getline(str2, point, ',');

        string dist;
        int idx = 0;
        while(getline(str2, dist, ',')) {
            if(dist.length() != 0) {
                dist_matrix[point][points[idx]] = stoi(dist);
            }
            idx++;
        }
    }

    string pt1, pt2;
    int mid_dist = INT_MAX;

    for(auto itr:dist_matrix) {
        for(auto itr1:itr.second) {
            cout<<itr.first<<" "<<itr1.first<<" "<<itr1.second<<endl;
        }
    }
    cout<<endl;

    for(auto itr:dist_matrix) {
        for(auto itr1:itr.second) {
            string p1 = itr.first, p2=itr1.first;
            int dist = itr1.second;

            if(p1 != p2 and dist < mid_dist) {
                pt1 = p1;
                pt2 = p2;
                mid_dist = dist;
            }
        }
    }

    cout<<"Clusters Chosen: "<<pt1<<" "<<pt2<<endl;

    string up, down;
    if(pt1[0] > pt2[0]) {
        up = pt2;
        down = pt1;
    } 
    else {
        up = pt1;
        down = pt2;
    }

    string newPt = down+up;

    for(auto itr:dist_matrix) {
        point = itr.first;
        if(point[0] > newPt[0]) {
            dist_matrix[point][newPt] = min(dist_matrix[point][up], dist_matrix[point][down]);
        }
    }

    for(auto itr:dist_matrix[down]) {
        point = itr.first;
        int d1 = itr.second;

        if(point[0] < up[0]) {
            d1 = min(d1, dist_matrix[up][point]);
        }
        else {
            d1 = min(d1, dist_matrix[point][up]);
        }

        dist_matrix[newPt][point] = d1;
    }

    for(auto itr:dist_matrix) {
        point = itr.first;

        if(point[0] >= up[0]) {
            int d1 = dist_matrix[point][up];
            
            if(down[0] > point[0]) {
                d1 = min(d1, dist_matrix[down][point]);
            }
            else {
                d1 = min(d1, dist_matrix[point][down]);
            }

            dist_matrix[point][newPt] = d1;
            dist_matrix[point].erase(up);

            if(point[0] >= down[0]) {
                dist_matrix[point].erase(down);
            }
        }
    }

    dist_matrix.erase(up);
    dist_matrix.erase(down);

    string output = "output"+to_string(op++)+".csv";

    ofstream out_file(output);

    out_file<<",";
    for(auto itr:dist_matrix) {
        out_file<<itr.first<<",";
    }
    out_file<<endl;

    for(auto itr:dist_matrix) {
        out_file<<itr.first<<",";
        for(auto itr1:itr.second) {
            out_file<<itr1.second<<",";
        }
        out_file<<endl;
    }

    out_file.close();

    finalout_file<<down<<" & "<<up<<endl;

    return output;
}

int main() {
    ifstream file("input.csv");

    string line;
    getline(file, line);

    int len=0;
    while(getline(file, line)) {
        len++;
    }

    string input = "input.csv";
    for(int i=1;i<=len-2;i++) {
        string output = agglomerative(input);
        input = output;
    }

    return 0;
}