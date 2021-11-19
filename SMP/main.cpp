/*
    In mathematics, economics, and computer science, the stable marriage problem is
    the problem of finding a stable matching between two equally sized sets of ele-
    ments given an ordering of preferences for each element. A matching is a bijec-
    tion from the elements of one set to the elements of the other set. A matching 
    is not stable if: There is an element A of the first matched set which prefers
    some given element B of the second matched set over the element to which A is 
    already matched, and B also prefers A over the element to which B is already m-
    atched.                                 -From Wikipedia, the free encyclopedia

    This program is an implementation of the stable marriage problem, which is don-
    e from scratch by my approach.
*/

#include <iostream>
#include <algorithm>
#include <queue>
#include <random>
#include <forward_list>
#include <map>

using namespace std;

// produce a random preference list with the random state, first element idx is index in profile
int* produceRandomPreferenceList(int size, int idx, int randomState=1) 
{
    int* digits = new int[size + 1];
    int i = 1;
    digits[0] = idx;
    for_each(digits + 1, digits + size + 1, [&](int& x){x = i++;});
    shuffle(digits + 1, digits + size + 1, default_random_engine(randomState));
    return digits;
}

// print preference profiles for men and women in a horizontal stack
void printPreferenceProfiles(int**& menPrefile, int**& womenProfile, int size) 
{
    for(int i = 0; i < size; i++)
    {  
        cout << "[M";
        cout << menPrefile[i][0] << "] -> ";
        for(int j = 0; j < size; j++)
        {
            cout << menPrefile[i][j + 1] << ' ';
        }

        cout << "    ";

        cout << "[W";
        cout << womenProfile[i][0] << "] -> ";
        for(int j = 0; j < size; j++)
        {
            cout << womenProfile[i][j + 1] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

/* 
    apply Gale-Shapley algorithm to men's and women's profiles so as to rearrange them 
    into a match satisfing the conditions of the problem, moreover, time complexity is
    O(size^2), return a map mapping men to corresponding women, value starting from 0
*/
map<int, int>* applyGS(int**& menProfile, int**& womenProfile, int size)
{
    /* 
        toWhomMenLastproposed[i] equals to last rank of woman to whom (i + 1)th man was engaged
    */
    int* toWhomMenLastProposed = new int[size];  
    fill(toWhomMenLastProposed, toWhomMenLastProposed + size, -1); // initialized by -1

    /* 
        whomWomenAreEngaging[i] equals to (i + 1)th woman has not been proposed 
    */
    int* whomWomenAreEngaging = new int[size];
    fill(whomWomenAreEngaging, whomWomenAreEngaging + size, -1); // initialized by -1

    /* 
        exchange women's profile's keys and values
    */
    int** womenRankingTable = new int*[size];
    for(int i = 0; i < size; i++)
    {
        womenRankingTable[i] = new int[size];
        for(int j= 0; j < size; j++)
        {
            womenRankingTable[i][womenProfile[i][j + 1] - 1] = j;
        }
    }

    /* 
        log whether a man is currently free or not to make yielding a free man subject to O(1)
    */
    forward_list<int> freeMen;
    for(int i = 0; i < size; i++)
    {
        freeMen.push_front(i);
    }

    while(!freeMen.empty()) // main loop
    {
        // propose
        int freeMan = freeMen.front();
        toWhomMenLastProposed[freeMan]++;
        int proposeTo = menProfile[freeMan][toWhomMenLastProposed[freeMan] + 1] - 1;
        int& fiance = whomWomenAreEngaging[proposeTo];

        // if no fiance
        if(fiance == -1)
        {
            fiance = freeMan;           
            freeMen.pop_front();
        }
        // if new proposer is better than fiance
        else if(womenRankingTable[proposeTo][freeMan] < womenRankingTable[proposeTo][fiance])
        {
            int temp = fiance;
            fiance = freeMan;
            freeMen.pop_front();
            freeMen.push_front(temp);
        }
    }
    
    map<int, int>* matches = new map<int, int>;
    for(int i = 0; i < size; i++)
    {
        matches->insert(pair<int, int>(whomWomenAreEngaging[i], i));
    }

    return matches;
}


int main()
{
    int size = 9, randomstate = 1, idxM = 1, idxW = 1;
    int** menProfile = new int*[size]; 
    int** womenProfile = new int*[size];
    for_each(menProfile, menProfile + size,
     [size, &randomstate, &idxM](int*& list){list = produceRandomPreferenceList(size, idxM++, randomstate++);});
    for_each(womenProfile, womenProfile + size,
     [size, &randomstate, &idxW](int*& list){list = produceRandomPreferenceList(size, idxW++, randomstate++);});

    // print instance
    printPreferenceProfiles(menProfile, womenProfile, size);

    // solve
    map<int, int>* matches = applyGS(menProfile, womenProfile, size);

    // rearrange
    int** newWomenProfile = new int*[size];
    for(auto iter = matches->begin(); iter != matches->end(); ++iter)
    {
        newWomenProfile[iter->second] = new int[size + 1];
        for(int i = 0; i < size + 1; i++)
        {
            newWomenProfile[iter->second][i] = womenProfile[iter->first][i];
        }
    }

    // print answer
    printPreferenceProfiles(menProfile, newWomenProfile, size);

    system("pause"); 
}