#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int prefixArr[100];
int patternFoundindexArray[50];
int Index = -1;
string pattern;
int patternSize;

//preprocessing(prefix function)
void prefixFn(string ptn){
    pattern =ptn;
    prefixArr[1] = 0;
    patternSize = ptn.size();
    int k=-1;
    for(int i=1; i < patternSize; i++){
        while(k>-1 && ptn[k+1]!=ptn[i]){
            k= prefixArr[k] - 1;
        }
        if(ptn[k+1]== ptn[i]){
            k++;
        }
        prefixArr[i+1]= k + 1;
    }
}

//KMP ALOGORITHM
void kmpMatch(string text){
    int sizeText = text.size();
    int numOfmatch = 0;
    int position = -1;

    for(int i=0;i<sizeText;i++){
        while(position > -1 && pattern[position+1]!=text[i]){
            if(prefixArr[numOfmatch]==0) {
                position = -1;
            }else {
                position = prefixArr[numOfmatch]-1;
            }
            numOfmatch = prefixArr[numOfmatch];
        }
        if(pattern[position+1]==text[i]){
            position++;
            numOfmatch++;
        }
        if(numOfmatch==patternSize) {
            if(prefixArr[numOfmatch]==0) {
                position = -1;
            }else
                position=prefixArr[numOfmatch]-1;
            numOfmatch = prefixArr[numOfmatch];
            Index++;
            patternFoundindexArray[Index] = i+1 - patternSize;  // if any match is found then put than index into this array
        }
    }
}

int main(){
    fstream myFile;
    fstream myPattern;

    //pass pattern in to the prefix function to calculate prefix values.
    myPattern.open("pattern1.txt",ios::in); // read pattern
    if (myPattern.is_open()){
        string line;
        while (getline(myPattern,line)){
            prefixFn(line);
        }
        myPattern.close();
    }

    //pass line by line into kmp alogrithm to find matches
    myFile.open("text1.txt",ios::in); //read text
    if(myFile.is_open()){
        string  line;
        while(getline(myFile,line)){
            kmpMatch(line);
        }
        myFile.close();
    }
    if(Index ==-1){
        cout<< "Pattern not found in text."<<endl;
    }else{
        cout<< "Pattern found.Indexs' are :" << endl;
        for(int i=0;i<=Index;i++){
            cout << patternFoundindexArray[i] << " ";
        }
    }
}
