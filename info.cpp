#include<bits/stdc++.h>
using namespace std;

double calculate_Entropy(int positive, int negative)
{
    double entropy=0;
    double total= positive + negative;
    double positive_probability = positive/total;
    double negative_probability = negative/total;
    if( positive>0)
    {
        entropy -= positive_probability*log2(positive_probability); 
    }
    if( negative> 0)
    {
        entropy -= negative_probability*log2(negative_probability);
    }
    return entropy;
}

double compute_infogain(map<string, int> &parentcount, map<string, map<string, int>> &childcount)
{

    double InfoGain=0;


    double parentEntropy=0, positiveParent=0, negativeParent=0, totalParent=0;
    positiveParent = parentcount["Yes"];
    negativeParent = parentcount["No"];
    totalParent = (positiveParent+ negativeParent);

    // cout<<"Calculate the entropy of class attribute-> playtennis"<<endl;
    parentEntropy = calculate_Entropy(positiveParent, negativeParent);
    cout<<"Parent Entropy is: "<<parentEntropy<<endl;

    // cout<<"Calculate the entropy of selected attribute-> childName"<<endl;
    double childEntropy=0;
    for(auto it= childcount.begin() ; it!= childcount.end(); it++)
    {
        string child_val = it->first;
        double pos_child_val = it->second["Yes"];
        double neg_child_val = it->second["No"];
        double total_child_val = (pos_child_val+ neg_child_val);
        //get the entropy of each value of selected attribute : Ex: Sunny , rain etc
        double child_val_entropy = calculate_Entropy(pos_child_val, neg_child_val);

        childEntropy+= (total_child_val/totalParent) * child_val_entropy;
    }


    cout<<"Weighted child entropy is: "<<childEntropy<<endl;


    //calculating the infogain:
    InfoGain = parentEntropy - childEntropy;
    cout<<"Info gain for selected attribute is: "<<InfoGain<<endl;

    return InfoGain;
}


int main()
{
    ifstream inputfile("input.csv");
    string line, day, outlook, temp, humidity, wind, playtennis;

    if( !inputfile.is_open())
    {
        cerr<<"Error in input file"<<endl;
        return -1;
    }

    int i=0;
  
    int choice;

    cout<<"Enter your choice->"<<endl;
    cout<<"Press:"<<endl;
    cout<<"1. for outlook"<<endl;
    cout<<"2. for temp"<<endl;
    cout<<"3. for humidity"<<endl;
    cout<<"4. for wind"<<endl;
    cout<<"5. for playtennis"<<endl;
    //getting choice as a user -> input
    cin>>choice;


    //initializing two data structures: map(parent_count)-> for class attribute and map(childcount)-> for selected child attribute
    map<string, int> parentcount; //to store freq of play and np play
    map<string, map<string, int>> childcount; // to store the freq of play no play for every unique value of selected attribute

    string childName;


    while( getline(inputfile, line))
    {
        stringstream str(line);
        //getline(object, dataread_from_the_obj, delimiter(to stop reading from the given obj when certain parameter occurs))
        //here we need to add a delimiter to get the extracted values for each attribute
        getline(str, day, ',');
        getline(str, outlook, ',');
        getline(str, temp, ',');
        getline(str, humidity, ',');
        getline(str, wind, ',');
        getline(str, playtennis, ','); //for last attribute also add a dummy ',' -> after the last column


        switch(choice)
        {
            case 1: 
            childName = outlook;
            break;
            case 2: 
            childName = temp;
            break;
            case 3: 
            childName = humidity;
            break;
            case 4: 
            childName = wind;
            break;
            case 5: 
            childName = playtennis;
            break;
            default:
            childName = playtennis;
            break;
        }

        parentcount[playtennis]++;
        childcount[childName][playtennis]++;
    }


    double InfoGain= compute_infogain(parentcount, childcount);
    cout<<endl;
    cout<<"Computed infogain for selected attribute is "<<InfoGain<<endl;
    inputfile.close();

    return 0;
}