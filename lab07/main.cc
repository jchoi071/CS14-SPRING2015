//  ====================== Description ======================
///
/// Name: Ji Hoon Choi
/// SID: 861160400
/// Date: 5/23/15
///
//  =========================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <chrono>
#include <cstdlib>

using namespace std;

//vector scramble function
void scramble (vector<string>& words)
{
    srand(time(0));

    //run vector size * 3 times for thorough randomization
    for (unsigned a = 0; a < words.size() * 3; ++a)
    {
        unsigned randPosA = rand() % (words.size());
        unsigned randPosB = rand() % (words.size());
        //swap random elements - no slow copies here
        swap(words[randPosA], words[randPosB]);
    }
}

int main()
{
    vector<string> words;
    
    ifstream inWords;
    string currString;
    
    //open the words file
    inWords.open("words.txt");
    
    //if file DNE output error and exit
    if (!inWords.is_open())
    {
        cout << "Cannot open the file or file doesn't exist" << endl;
        exit(0);
    }
    //if file does exist
    else
    {
        //insert each word in the file into the string vector until end of
        //file is reached
        while (!inWords.eof())
        {
            inWords >> currString;
            words.push_back(currString);
        }
    }
    //close the words file
    inWords.close();
    
    unordered_set<string> stringUSet;
    set<string> stringSet;
    
    unsigned n = 0;
    double avgTimeSet;
    double avgTimeUSet;
    double avgTimeSetFind;
    double avgTimeUSetFind;
    
    chrono::time_point<chrono::high_resolution_clock> start;
    chrono::time_point<chrono::high_resolution_clock> end;
    
    //open or create output data file
    ofstream out;
    out.open("data.txt");
    
    //starting at n = 5000 and ending at n = 50000, the loop will run 10 times
    //if n is incremented by 5000 each time
    for (unsigned loop = 0; loop < 10; ++loop)
    {
        avgTimeSet = 0;
        avgTimeUSet = 0;
        
        avgTimeSetFind = 0;
        avgTimeUSetFind = 0;
        
        n += 5000;
        
        //run each test 10 times
        for (unsigned a = 0; a < 10; ++a)
        {
            //scramble the words vector
            scramble(words);
            
            //Set Insert
            
            stringSet.clear();
            //save start time
            start = chrono::high_resolution_clock::now();
            //insert the first n words into the set
            for (unsigned b = 0; b < n; ++b)
            {
                stringSet.insert(words.at(b));
            }
            //save end time
            end = chrono::high_resolution_clock::now();
            
            //divide total time taken by n for average time per query, then add
            //that to a variable for later use
            avgTimeSet += chrono::duration_cast<chrono::nanoseconds>(end - start).count() / n;

            //Unordered Set Insert
            
            stringUSet.clear();
            //save start time
            start = chrono::high_resolution_clock::now();
            //insert the first n words into the unordered set
            for (unsigned b = 0; b < n; ++b)
            {
                stringUSet.insert(words.at(b));
            }
            //save end time
            end = chrono::high_resolution_clock::now();
            
            //divide total time taken by n for average time per query, then add
            //that to a variable for later use
            avgTimeUSet += chrono::duration_cast<chrono::nanoseconds>(end - start).count() / n;

            //Set Find
            
            //save start time
            start = chrono::high_resolution_clock::now();
            //find the first n words in the set
            for (unsigned b = 0; b < n; ++b)
            {
                stringSet.find(words.at(b));
            }
            //save end time
            end = chrono::high_resolution_clock::now();
            
            //divide total time taken by n for average time per query, then add
            //that to a variable for later use
            avgTimeSetFind += chrono::duration_cast<chrono::nanoseconds>(end - start).count() / n;
            
            //Unordered Set Find
            
            //save start time
            start = chrono::high_resolution_clock::now();
            //find the first n words in the unordered set
            for (unsigned b = 0; b < n; ++b)
            {
                stringUSet.find(words.at(b));
            }
            //save end time
            end = chrono::high_resolution_clock::now();
            
            //divide total time taken by n for average time per query, then add
            //that to a variable for later use
            avgTimeUSetFind += chrono::duration_cast<chrono::nanoseconds>(end - start).count() / n;
        }
        //divide all the times by number of tests to find average time per query of all the tests
        avgTimeSet /= 10;
        avgTimeUSet /= 10;
        avgTimeSetFind /= 10;
        avgTimeUSetFind /= 10;
        
        //write the output values to the data file
        out << n << ' ' << avgTimeSet << ' ' << avgTimeUSet << ' ' << avgTimeSetFind << ' ' << avgTimeUSetFind << endl;
    }
    
    //close the data file
    out.close();
    
    cout << "Done" << endl;
    
    return 0;
}