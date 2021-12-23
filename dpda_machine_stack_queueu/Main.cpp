#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>

using namespace std;

//DPDA dosyası için gerekli depolama alanları
vector<string> stationNamesVector;
vector<string> alphabetVector;
vector<string> outputDigitsVector;
vector<vector<string>> stationsParametersVector;
vector<string> tempStationsVector;
vector<string> finishStations;
string startStationString;


//stack node for type string
class StackNode{
public:
    string data;
    StackNode* next;
    StackNode(const string& data = "", StackNode* next=NULL) : data(data), next(next){}
};

//stack class adapted string
class StackString{
    StackNode* root;
public:
    StackString() : root(NULL) {}

    ~StackString(){
        makeEmpty();
    };

    StackNode* begin()const {
        return root;
    }

    StackNode* end()const{
        return NULL;
    }

    bool isEmpty()const {
        return begin()==end();
    }

    void push(const string& value){
        StackNode* tmp = new StackNode(value,root);
        root = tmp;
    }

    void pop(){
        if (isEmpty()){
            cout << "stop! the stack is empty." << endl;
        }else{
            StackNode* tmp = root;
            root = tmp->next;
            delete tmp;
        }
    }

    string top()const{
        string result;
        if (!isEmpty()){
            result = begin()->data;
        }
        return result;
    }

    int size()const{
        int stackSize = 0;
        StackNode* firstNode = begin();
        while(firstNode != end()){
            stackSize++;
            firstNode = firstNode->next;
        }
        return stackSize;
    }

    void print()const{
        StackNode* firstNode = begin();
        while(firstNode != end()){
            cout << firstNode->data << endl;
            firstNode = firstNode->next;
        }
    }

    string show()const{
        StackNode* firstNode = begin();
        string resultString = "";
        StackString s2;
        while(firstNode != end()){
            s2.push(firstNode->data);
            firstNode = firstNode->next;
        }

        while(s2.begin() != s2.end()){
            resultString += s2.top();
            s2.pop();
            resultString += ",";
        }
        resultString = resultString.substr(0,resultString.length()-1);
        return resultString;
    }

    void makeEmpty(){
        while (!isEmpty()){
            pop();
        }
        root = NULL;
    }
};

string readToString(string fileName, string wholeTxt, int* lenOfLine )
{
    fstream new_file;
    new_file.open(fileName, ios::in);
    string line;
    if(!new_file){
        cout << "No such file" << endl;
    }else{
        // Use a while loop together with the getline() function to read the file line by line
        while(getline(new_file,line)){
            //output the text from file
            wholeTxt += line + "/";
            *lenOfLine = *lenOfLine + 1;
        }
        new_file.close();
    }
    return wholeTxt;
}

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
    return result;
}

int main(int argc, char *argv[]) {
    //file names declaration
    //string DPDAFile = "dpda1.txt";
    string DPDAFile = argv[1];
    //string inputFile = "input1.txt";
    string inputFile = argv[2];
    //string outputFile = "output1.txt";
    string outputFile = argv[3];

    //reading the dpda files (we have line height and every line in string array)
    string DPDAText = "";
    int* pointer_length_of_the_line_for_the_DPDA_text;
    int length_of_the_line_for_the_DPDA_text = 0; //length of the line for the DPDA text
    pointer_length_of_the_line_for_the_DPDA_text = &length_of_the_line_for_the_DPDA_text;
    DPDAText = readToString(DPDAFile,DPDAFile,pointer_length_of_the_line_for_the_DPDA_text);
    string DPDA_line_height[length_of_the_line_for_the_DPDA_text];

    //reading the input files (we have line height and every line in string array)
    string inputText = "";
    int* pointer_length_of_the_line_for_the_input_text;
    int length_of_the_line_for_the_input_text = 0; //length of the line for the input text
    pointer_length_of_the_line_for_the_input_text = &length_of_the_line_for_the_input_text;
    inputText = readToString(inputFile, inputText,pointer_length_of_the_line_for_the_input_text);
    string input_line_height[length_of_the_line_for_the_input_text];

    //cout << "line 173" << endl;

    int counter = 0;
    string line;
    ifstream file(DPDAFile);
    //cout << "checkpoint 1" << endl;
    if(file.is_open())
    {
        //cout << "checkpoint 2" << endl;
        while(!file.eof())
        {
            //cout << "checkpoint 3" << endl;
            getline(file,line);
            //cout << "checkpoint 4" << endl;
            DPDA_line_height[counter] = line;
            //cout << "checkpoint 5" << endl;
            counter = counter + 1;
        }
        //cout << "checkpoint 6" << endl;
        file.close();
    }
    //cout << "line 188" << endl;
    counter = 0;
    line = "";
    ifstream file_2(inputFile);
    if(file_2.is_open())
    {
        while(!file_2.eof())
        {
            getline(file_2,line);
            input_line_height[counter] = line;
            counter = counter + 1;
        }
        file.close();
    }


    //dpda dosyasında ayıklama islemleri
    for (int i = 0; i < length_of_the_line_for_the_DPDA_text; i++) {
        char firstDigit = DPDA_line_height[i][0];
        int lengthOfLine = DPDA_line_height[i].length();

        //station ile ilgili işlemleri burada ele alacaz.
        if (firstDigit=='Q'){
            int pos = DPDA_line_height[i].find("=>",0);
            string stationsString = DPDA_line_height[i].substr(2,pos-3);
            //cout << "Station names: " << stationsString << endl;
            stationNamesVector = split(stationsString, ',');

            string startFinishStations = DPDA_line_height[i].substr(pos+3);
            //cout << "Start and finish station names: " << startFinishStations << endl;
            tempStationsVector = split(startFinishStations,',');
            for (int j = 1; j <tempStationsVector.size() ; j++) {
                //cout << tempStationsVector[j] << endl;
                string tempStr = tempStationsVector[j].substr(1,tempStationsVector[0].length()-2);
                finishStations.push_back(tempStr);
            }

            startStationString = tempStationsVector[0].substr(1,tempStationsVector[0].length()-2);
            //cout << "Start point: " << startStationString << endl;
        }

        //input alfabesini burada ele alacaz. T lerin input ksımında bilgilere var mı diye bakacaz.
        else if (firstDigit=='A'){
            string alphabetString = DPDA_line_height[i].substr(2,lengthOfLine-2);
            //cout << "Alphabet: " << alphabetString << endl;
            alphabetVector = split(alphabetString,',');
        }

        else if (firstDigit=='Z'){
            string outputDigitsString = DPDA_line_height[i].substr(2,lengthOfLine-2);
            //cout << "Output Stack Alphabet: " << outputDigitsString << endl;
            outputDigitsVector = split(outputDigitsString,',');
        }

        else if (firstDigit=='T'){
            string stationsParametersString = DPDA_line_height[i].substr(2,lengthOfLine-2);
            //cout << "Stations: " << stationsParametersString << endl;
            vector<string> stationsJustOne = split(stationsParametersString,',');
            stationsParametersVector.push_back(stationsJustOne);
        }
    }
    //end - dpda dosyasında ayıklama islemleri

    bool anyMistake = false;
    bool isInclude = false;


    //stationların varlığını kontrol ediyoruz.
    for (int i = 0; i < stationsParametersVector.size(); i++) {
        for (int j = 0; j < stationNamesVector.size() ; j++) {
            if (stationsParametersVector[i][0]==stationNamesVector[j]){
                isInclude=true;
            }
        }
        if (!isInclude){
            anyMistake=true;
        }
        isInclude = false;
    }

    for (int i = 0; i < stationsParametersVector.size(); i++) {
        for (int j = 0; j < stationNamesVector.size() ; j++) {
            if (stationsParametersVector[i][3]==stationNamesVector[j]){
                isInclude=true;
            }
        }
        if (!isInclude){
            anyMistake=true;
        }
        isInclude = false;
    }

    //inputların varlığını kontrol ediyoruz.
    for (int i = 0; i < stationsParametersVector.size(); i++) {
        for (int j = 0; j < alphabetVector.size() ; j++) {
            if (stationsParametersVector[i][1]==alphabetVector[j] || stationsParametersVector[i][1]=="e"){
                isInclude=true;
            }
        }
        if (!isInclude){
            anyMistake=true;
        }
        isInclude = false;
    }

    //pushlanacak elemanın listede olup olmadıgını kontrol ediyoruz
    for (int i = 0; i < stationsParametersVector.size(); i++) {
        for (int j = 0; j < outputDigitsVector.size() ; j++) {
            if (stationsParametersVector[i][4]==outputDigitsVector[j] || stationsParametersVector[i][4]=="e"){
                isInclude=true;
            }
        }
        if (!isInclude){
            anyMistake=true;
        }
        isInclude = false;
    }


    //input dosyası için gerekli depolama vectorleri
    vector<vector<string>> inputVector;

    for (int i = 0; i < length_of_the_line_for_the_input_text; i++) {
        vector<string> tempVectorPerLine = split(input_line_height[i],',');
        inputVector.push_back(tempVectorPerLine);
    }
    //end - input dosyası için gerekli input dosyası

    ofstream myfile;
    myfile.open (outputFile);
    string result;
    StackString outputStack;
    queue<string> inputsQueue;


    if (anyMistake){
        result += "Error [1]:DPDA description is invalid!\n";

    }
    else{
        for (int i = 0; i < inputVector.size(); i++) {
            if (inputVector[i].empty()){
                result += "ACCEPT\n\n";
            }
           else{
                for (int j = 0; j <inputVector[i].size() ; j++) {
                    string input = inputVector[i][j];
                    inputsQueue.push(input);
                }

                string firstQ = startStationString;
                string lastStation;
                string lastInput;

                while (!inputsQueue.empty()){
                    string input = inputsQueue.front();
                    bool uygunStateVarMi = false;
                    bool ikiliKontrol = false;

                    for (int k = 0; k < stationsParametersVector.size(); k++) {
                        if (stationsParametersVector[k][0]==firstQ && stationsParametersVector[k][1]==input && (stationsParametersVector[k][2]==outputStack.top() || stationsParametersVector[k][2]=="e")){
                            lastInput = input;
                            uygunStateVarMi = true;
                            ikiliKontrol = true;
                            if (outputStack.top() == stationsParametersVector[k][2]) {
                                outputStack.pop();
                            }
                            firstQ = stationsParametersVector[k][3];
                            lastStation = stationsParametersVector[k][3];
                            if (!(stationsParametersVector[k][4] == "e"))
                                outputStack.push(stationsParametersVector[k][4]);
                            result += stationsParametersVector[k][0] + "," + input + "," + stationsParametersVector[k][2] + " => " + stationsParametersVector[k][3] + "," + stationsParametersVector[k][4] + " [STACK]:" + outputStack.show() + "\n";
                            input = "";
                            inputsQueue.pop();
                        }
                    }

                    if (!uygunStateVarMi){
                        input = "e";
                        for (int k = 0; k < stationsParametersVector.size(); k++) {
                            if (stationsParametersVector[k][0]==firstQ && stationsParametersVector[k][1]==input){
                                lastInput = "e";
                                ikiliKontrol = true;
                                uygunStateVarMi = true;
                                firstQ = stationsParametersVector[k][0];
                                if (outputStack.top() == stationsParametersVector[k][2]) {
                                    outputStack.pop();
                                }
                                firstQ = stationsParametersVector[k][3];

                                if (!(stationsParametersVector[k][4] == "e"))
                                    outputStack.push(stationsParametersVector[k][4]);
                                result += stationsParametersVector[k][0] + "," + input + "," + stationsParametersVector[k][2] + " => " + stationsParametersVector[k][3] + "," + stationsParametersVector[k][4] + " [STACK]:" + outputStack.show() + "\n";
                                input = "";
                            }
                        }
                    }

                    if (!ikiliKontrol){
                        break;
                    }
                }

                if (!(lastInput=="e")){
                    for (int j = 0; j < stationsParametersVector.size(); j++) {
                        if (stationsParametersVector[j][0]==lastStation && stationsParametersVector[j][1]=="e" && (stationsParametersVector[j][2]==outputStack.top() || stationsParametersVector[j][2]=="e")){
                            if (outputStack.top() == stationsParametersVector[j][2]) {
                                outputStack.pop();
                            }
                            lastStation = stationsParametersVector[j][3];
                            if (!(stationsParametersVector[j][4] == "e"))
                                outputStack.push(stationsParametersVector[j][4]);
                            result += stationsParametersVector[j][0] + "," + stationsParametersVector[j][1] + "," + stationsParametersVector[j][2] + " => " + stationsParametersVector[j][3] + "," + stationsParametersVector[j][4] + " [STACK]:" + outputStack.show() + "\n";
                        }
                    }
                }

                if (outputStack.isEmpty() || ((outputStack.size()==1) && (outputStack.top() == "$")))
                    result += "ACCEPT\n";
                else
                    result += "REJECT\n";
                result += "\n";
                while (!inputsQueue.empty()){
                    inputsQueue.pop();
                }
                outputStack.makeEmpty();
           }
        }
    }
    myfile << result;

    return 0;
}