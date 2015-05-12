//  ====================== Description ======================
///
/// Name: Ji Hoon Choi
/// SID: 861160400
/// Date: 4/29/15
///
//  =========================================================


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <map>
#include <list>
#include <math.h>
#include "lab5.h"
using namespace std;

int main()
{
    cout << "Test Case 1: Wikipedia Example Tree" << endl;
    BST test;
    
    test.insert(8);
    test.insert(3);
    test.insert(1);
    test.insert(6);
    test.insert(4);
    test.insert(7);
    test.insert(10);
    test.insert(14);
    test.insert(13);
    
    cout << "Part 1" << endl;
    test.minCover();
    test.displayMinCover();
    
    cout << endl << "Test Case 2: Lab Specs Example Tree" << endl;
    BST test2;
    test2.insert(50);
    test2.insert(20);
    test2.insert(10);
    test2.insert(40);
    test2.insert(35);
    test2.insert(45);
    test2.insert(60);
    test2.insert(70);
    
    cout << "Part 1" << endl;
    test2.minCover();
    test2.displayMinCover();
    
    cout << endl << "Test Case 3: User-made Random Tree" << endl;
    BST test3;
    test3.insert(4);
    test3.insert(44);
    test3.insert(52);
    test3.insert(24);
    test3.insert(15);
    test3.insert(16);
    test3.insert(50);
    test3.insert(25);
    test3.insert(253);
    
    cout << "Part 1" << endl;
    test3.minCover();
    test3.displayMinCover();
    
    cout << endl << "Test Case 4: Empty Tree" << endl;
    BST test4;
    
    cout << "Part 1" << endl;
    test4.minCover();
    test4.displayMinCover();
    
    cout << endl << "Test Case 5: Tree with one node" << endl;
    BST test5;
    
    test4.insert(45);
    
    cout << "Part 1" << endl;
    test4.minCover();
    test4.displayMinCover();
}