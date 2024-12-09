#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <conio.h>
#include <regex>
#include <functional>
using namespace std;


long multiplier(const string& filepath);
void PatternPuller(string& line, vector<string>& validPatterns);
int mul(int a , int b);


int main(){

    int testResult = multiplier("C:/Users/meela/Downloads/Personal-Projects/AdventOfCode/Day3/Day3TestInput.txt");
    int result = multiplier("C:/Users/meela/Downloads/Personal-Projects/AdventOfCode/Day3/Day3Input.txt");

    cout << result << endl;

    return 0;
}

long multiplier(const string& filepath){
    ofstream outputFile("C:/Users/meela/Downloads/Personal-Projects/AdventOfCode/Day3/results.txt");
    ifstream file(filepath);
    vector<string> patterns;

    map<string, function<int(int, int)>> functionMap;
    functionMap["mul"] = mul;
    bool canDo = true;

    long result = 0;


    if (!file.is_open()) {
        cerr << "Error: File not found: " << filepath << endl;
        return -1; 

    }else{
        string line;
        while(getline(file, line)){
            patterns.clear();
            PatternPuller(line, patterns);

            for(const string& pattern: patterns){
                outputFile << pattern << endl;
                
                if (pattern == "do()"){
                    canDo = true;
                    outputFile << "Resume" << endl;
                }else if(pattern == "don't()"){
                    canDo = false;
                    outputFile << "Pause" << endl;
                }else{
                    smatch match;
                    regex funcRegex(R"((\w+)\((\d+),(\d+)\))");         
                    if(regex_match(pattern, match, funcRegex)){
                        if(canDo){        
                            string funcName = match[1];
                            int arg1 = stoi(match[2]);
                            int arg2 = stoi(match[3]);
                            
                            result += functionMap[funcName](arg1,arg2);
                            outputFile << result << endl;
                        }
                    }
                }
            }
        }

        file.close();
        outputFile.close();
    }
    return result;
}


void PatternPuller(string& line, vector<string>& validPatterns){
    regex mulPattern(R"(mul\(\d+,\d+\)|do\(\)|don't\(\))");
    sregex_iterator begin(line.begin(), line.end(), mulPattern);
    sregex_iterator end;

    for(auto it = begin; it != end; ++it){
        validPatterns.push_back(it -> str());
    }
}

int mul(int a, int b){
    return a*b;
}
