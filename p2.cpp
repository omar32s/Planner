#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include "BST.h"
#include <vector>
using namespace std;

bool niceword(string input) 
{
    if (input[0] != '"' && input[input.size() - 1] != '"') return 0;
    else return 1;
}


bool nicehour(string input) {

    for (int i = 0; i < input.length(); i++) {
        if (!isdigit(input[i])) return 0;
    }
    if (stoi(input) > 23 || stoi(input) < 0) return 0;
    return 1;

}

bool niceday(string input) {

    for (int i = 0; i < input.length(); i++) {
        if (!isdigit(input[i])) return 0;
    }
    if (stoi(input) > 365 || stoi(input) < 1) return 0;
    return 1;

}


vector<string> extract(string input) {
    int Qo = 0;
    vector<string> words;
    string word;
    int start = 0;
    int end = 0;

    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '"') { Qo++; end = i; }

    }


    if (Qo < 2) { words.clear(); return words; }

    for (int i = 0; i < input.length(); i++) {
        if (input[i] == ' ')continue;
        if (input[i] == '"') { start = i; break; }
    }


    if (start != 0) {
        for (int i = 0; i < start; i++) {
            if (input[i] != ' ')word.push_back(input[i]);
            else {
                if (word.empty())continue;
                words.push_back(word);
                word.clear();
            }
        }
    }

    if (input[end + 1] != ' ') { words.clear(); return words; }

    for (int i = start; i <= end; i++) {
        word.push_back(input[i]);
    }

    words.push_back(word);
    word.clear();

    for (int i = end + 1; i < input.length(); i++) {
        if (input[i] != ' ')word.push_back(input[i]);
        else {
            if (word.empty())continue;
            words.push_back(word);
            word.clear();
        }
    }

    if (word.empty())return words;

    words.push_back(word);
    word.clear();


    return words;

}




int main(int argc, char **argv)
{
  
    if (argc != 2)
    {
        cout << "Invalid arguments" << endl;
        return 0;
    }
    
    
    
    ifstream txtfile;
    txtfile.open(argv[1]);
    if (!txtfile.is_open()) cout <<"File not Found" << endl;  //check if is still open (retrun error)

    BST tree;
    int wordscount = 0;
    string line;
    string word;
    string command;
    string f_title;
    string f_day;
    string f_hour;
    vector <string>fullline;
    string findres;
    while (getline(txtfile, line))  // separate file into lines
    {
        wordscount = 0;
        stringstream streamline(line);

       // counter(line);
        while (streamline >> word) // separate lines into words (separated by whitespaces and endlines)
        {
            wordscount++;
        }

      
        stringstream streamline2(line);
        streamline2 >> command;

 /////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (command == "ADD")
        {

            fullline = extract(line);
            if (fullline.size() == 0)
            {
                cout << "Invalid title" << endl;
                continue;
            }

            
            if (fullline.size() != 4)
            {
                cout << "Invalid arguments" << endl;
                continue;
            }
            
            streamline2 >> f_title;
            streamline2 >> f_day;
            streamline2 >> f_hour;

            if (!niceword(fullline[1])) { cout << "Invalid title" << endl; continue; }
            if (!niceday(fullline[2])) { cout << "Invalid day" << endl; continue; }
            if (!nicehour(fullline[3])) { cout << "Invalid hour" << endl; continue; }
            tree.insert(fullline[1], fullline[2],fullline[3]);
        }
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (command == "Find")
        {
            if (wordscount != 3)
            {
                cout << "Invalid arguments" << endl;
                continue;
            }
            streamline2 >> f_day;
            streamline2 >> f_hour;

            if (!niceday(f_day)) { cout << "Invalid day" << endl; continue;}
            if (!nicehour(f_hour)) { cout << "Invalid hour" << endl; continue; }
            findres = tree.find(f_day, f_hour);
            if (findres == "Empty day hour")
            {
                cout << "Empty " << f_day << " " << f_hour << endl;
            }
            else { cout << findres << endl; }
        }
 /// /////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (command == "MOD")
        {

            fullline = extract(line);
            if (fullline.size() == 0)
            {
                cout << "Invalid title" << endl;
                continue;
            }

            if (fullline.size() != 4)
            {
                cout << "Invalid arguments" << endl;
                continue;
            }

            streamline2 >> f_title;
            streamline2 >> f_day;
            streamline2 >> f_hour;


            if (!niceword(fullline[1])) { cout << "Invalid title" << endl; continue; }
            if (!niceday(fullline[2])) { cout << "Invalid day" << endl; continue; }
            if (!nicehour(fullline[3])) { cout << "Invalid hour" << endl; continue; }
            tree.mod(fullline[1], fullline[2], fullline[3]);
        }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (command == "DEL")
        {
            if (wordscount != 3)
            {
                cout << "Invalid arguments" << endl;
                continue;
            }
            streamline2 >> f_day;
            streamline2 >> f_hour;
           
            if (!niceday(f_day)) { cout << "Invalid day" << endl; continue; }
            if (!nicehour(f_hour)) { cout << "Invalid hour" << endl; continue; }
            tree.remove(f_day, f_hour);
        }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (command == "Print")
        {
            if (wordscount != 1)
            {
                cout << "Invalid arguments" << endl;
                continue;
            }
            tree.printall();

        }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else
        {
            cout << "Invalid command" << endl;
        }
        


    }
    txtfile.close();


}