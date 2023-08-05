#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int prefixArr[100];
int patternFoundindexArray[50];
int Index = -1;
string pattern;
string text;
int patternSize;
int textSize;

void firstCharacters();
void lastCharacters();
void prefixFn(string);
int kmpMatch(string text);
void dividParts();


void print(){
    cout<<"string : "<<text<<endl;
    cout<<"pattern : "<<pattern<<endl;
}

void firstCharacters(){
    int flag=0;
    for(int i=0;i<patternSize-1;i++){
        if(pattern[i+1]!=text[i]){
            flag=1;
            break;
        }
    }
    print();
    if(flag==0){
        cout<<"True"<<endl;
    }else
        cout<<"False"<<endl;
}

void lastCharacters(){
    int flag = 0;
    int start= textSize - patternSize +1;
    for(int i=0;i<patternSize-1;i++){
        if (pattern[i+1]!=text[start+i]){
            flag=1;
            break;
        }
    }
    print();
    if(flag==0){
        cout<<"True"<<endl;
    }else
        cout<<"False"<<endl;
}

//preprocessing(prefix function)
void prefixFn(string pattern){
    prefixArr[1] = 0;
    patternSize = pattern.size();
        int k=-1;
        for(int i=1; i < patternSize; i++){
            while(k>-1 && pattern[k+1]!=pattern[i]){
                k= prefixArr[k] - 1;
            }
            if(pattern[k+1]== pattern[i]){
                k++;
            }
            prefixArr[i+1]= k + 1;
        }
}

//KMP ALOGORITHM
int kmpMatch(string pattern){
    prefixFn(pattern);
    int numOfmatch = 0;
    int position = -1;

        for(int i=0; i < textSize; i++){
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

        if(Index ==-1){
            return 0;
        }else{
            return 1;
            }
}

void dividParts(){
    int flag1=0;
    int flag2=0;
    if(pattern[0]=='/'){
        flag2=1;
        firstCharacters();
    }else if(pattern[0]=='$'){
        flag2=1;
        lastCharacters();
    }else{
        for(int i=0;i<patternSize;i++){
            if(pattern[i]=='|'){
                if(kmpMatch(pattern.substr(0,i) ) || kmpMatch(pattern.substr(i+1))) {
                    print();
                    cout<< "Pattern found.Indexs' are :" << endl;
                    for(int i=0;i<=Index;i++){
                        cout << patternFoundindexArray[i] << " ";
                    }
                }
                flag1=1;
                break;
            }
        }
    }
    if(flag1==0 && flag2==0){
        if(kmpMatch(pattern)){
            print();
            cout<< "Pattern found.Indexs' are :" << endl;
            for(int i=0;i<=Index;i++){
                cout << patternFoundindexArray[i] << " ";
            }
        }else{
            cout<<"Pattern not found."<<endl;
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
            pattern = line;
        }
        myPattern.close();
    }

    //pass line by line into kmp alogrithm to find matches
    myFile.open("text1.txt",ios::in); //read text
    if(myFile.is_open()){
        string  line;
        while(getline(myFile,line)){
            text = line;
        }
        myFile.close();
    }
    patternSize = pattern.size();
    textSize = text.size();
    dividParts();
}
