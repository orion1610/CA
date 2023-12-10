#include <bits/stdc++.h>
using namespace std;

    vector<long double> minmaxnorm(const vector<long double> &data, long double minnew, long double maxnew){
        vector<long double> ans;
        //sort(data.begin(), data.end());
        long double minold = *min_element(data.begin(), data.end());
        long double mxold = *max_element(data.begin(), data.end());
       
        long double oldDiff = mxold-minold;
        long double newDiff = maxnew-minnew;

        for(int i=0; i<data.size(); i++){
            long double x = ((data[i]-minold)/oldDiff)*newDiff + minnew;
            ans.push_back(x);
        }

        return ans;
    }

    vector<long double> zscorenorm(const vector<long double> &data){
        vector<long double> ans;
        long double sum = 0;
        for (long double x : data) {
            sum += x;
        }
        long double mean = sum / data.size();

        long double sumSqDiff = 0;
        for (long double x : data) {
            sumSqDiff += pow(x - mean, 2);
        }
        long double stdDev = sqrt(sumSqDiff / data.size());

        for (long double x : data) {
            long double z = (x - mean) / stdDev;
            ans.push_back(z);
        }

        return ans;

    }

    int main(){
        // open the files
        ifstream inputfile("input.csv");
        ofstream outputfile("output.csv");

        // check if files is open 
        if(!inputfile.is_open() || !outputfile.is_open()){
            cout<<"error opening the file"<<endl;
            return 1;
        }



        inputfile.ignore(numeric_limits<streamsize>::max(), '\n');
        vector<long double> data;

        string line;
        while(getline(inputfile, line)){
            data.push_back(stod(line));
        }
        inputfile.close();
        long double minnew=0, maxnew=0;

        cout<<"for min-max normalisation insert new minimum and maximum value"<<endl;
        cout<<"New Minimum: ";
        cin>>minnew;
        cout<<"New Maximum: ";
        cin>>maxnew;

       vector<long double> minmax = minmaxnorm(data, minnew, maxnew);
       vector<long double> zscore = zscorenorm(data);

        outputfile<<"original_data"<<','<<"MinMax_normalised"<<','<<"ZScoreNormalised"<<endl;
        for(int i=0; i<data.size(); i++){
            outputfile<<data[i]<<','<<minmax[i]<<','<<zscore[i]<<endl;
        }
        outputfile.close();
        cout<<"Results of MinMax and Zscore Normalisation are saved to output.csv"<<endl;
    }
