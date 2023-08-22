# User-Defined Regex
Implement Regex characters using the Knuth-Morris-Pratt (KMP) string matching algorithm. The solution was done using the C++ programming language.

## How to run?
First, go to the [C++ code](main.cpp) .You can run it using your own test cases and  If you want to add a new test case, go to the folder and create your own test case file.

You can change this text file name to your own file name.

file handling part.

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

## Methodology
I use the `Knuth-Morris-Pratt (KMP)` algorithm to implement this and filter the pattern using simple if statements. Also, the matching condition is called to the relevant function, and the output is given as a Boolean value.

    void dividParts(){
    int flag1=0;
    int flag2=0;
    if(pattern[0]=='^'){
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
                    cout<<"True"<<endl;
                }
                flag1=1;
                break;
            }
        }
    }
    if(flag1==0 && flag2==0){
        if(kmpMatch(pattern)){
            print();
            cout<<"True"<<endl;
        }else{
            print();
            cout<<"Pattern not found."<<endl;
        }
     }
    }   

In this version, the program recognizes `^` `|` `$` as the regex character.


