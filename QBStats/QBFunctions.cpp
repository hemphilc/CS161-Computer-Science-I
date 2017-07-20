/**
  * @brief Assignment 9
  * @author Corey Hemphill
  */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

#include "qbfunctions.h"

Quarterback* readQbs(const string fileName, int& numRecords) {
    ifstream inFile;
    inFile.open(fileName);
    if(inFile.fail()) {
        cout << "Could not open " << fileName << endl;
    }
    int listLength;
    inFile >> listLength;
    numRecords = listLength;
    Quarterback* qbList = new Quarterback[listLength];
        while(!inFile.eof()) {
            for(int i = 0; i < listLength; i++) {
                inFile >> qbList[i].nameFirst;
                inFile >> qbList[i].nameLast;
                for(int j = 0; j < NUM_GAMES; j++) {
                    inFile >> qbList[i].gameLog[j][COMPLETIONS];
                    inFile >> qbList[i].gameLog[j][ATTEMPTS];
                    inFile >> qbList[i].gameLog[j][YARDS];
                    inFile >> qbList[i].gameLog[j][TOUCHDOWNS];
                    inFile >> qbList[i].gameLog[j][INTERCEPTIONS];
                }
            }
        }
    inFile.close();
    return qbList;
}


void getQbMenu(Quarterback* qbList, int numRecords) {
    int selection = 0;
    int player = 0;
    while (selection != 4) {
        cout << "1: Print Player" << endl;
        cout << "2: Print Player Stats" << endl;
        cout << "3: Print Passer Ratings" << endl;
        cout << "4: Exit" << endl;
        cin >> selection;
        if (selection == 1) {
            cin >> player;
            printPlayer(qbList, player);
        }
        else if (selection == 2) {
            cin >> player;
            printPlayerStats(qbList, player);
        }
        else if (selection == 3) {
            printPasserRatings(qbList, numRecords);
        }
    }
}


void printPlayer(Quarterback* qbList, int player) {
    cout << endl;
    cout << qbList[player - 1].nameFirst << " ";
    cout << qbList[player - 1].nameLast << ":" << endl;
    cout << right << setw(23) << "Atts" << right << setw(8) << "Comps" << right << setw(9) << "Yards";
    cout << right << setw(6) << "TDs" << right << setw(8) << "Ints" << endl;
    for(int i = 0; i < NUM_GAMES; i++) {
        cout << right << setw(12) << "Game " << setw(2) << left << setw(8) << (i + 1);
        for(int j = 0; j < NUM_STATS; j++) {
            cout << left << setw(7) << qbList[player - 1].gameLog[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


void getStatTotal(Quarterback* qbList, int& comps, int& atts, int& yards, int& tds, int& ints, int player) {
    comps = 0;
    atts = 0;
    yards = 0;
    tds = 0;
    ints = 0;
    for(int i = 0; i < NUM_GAMES; i++) {
        comps += qbList[player].gameLog[i][COMPLETIONS];
        atts += qbList[player].gameLog[i][ATTEMPTS];
        yards += qbList[player].gameLog[i][YARDS];
        tds += qbList[player].gameLog[i][TOUCHDOWNS];
        ints += qbList[player].gameLog[i][INTERCEPTIONS];
    }
}


void printPlayerStats(Quarterback* qbList, int player) {
    int totalComps = 0;
    int totalAtts = 0;
    int totalYards = 0;
    int totalTds = 0;
    int totalInts = 0;
    getStatTotal(qbList, totalComps, totalAtts, totalYards, totalTds, totalInts, (player - 1));
    cout << endl;
    cout << qbList[player - 1].nameFirst << " ";
    cout << qbList[player - 1].nameLast << ":" << endl;
    cout << "Total " << left << setw(16) << "Attempts" << right << setw(5) << totalAtts << endl;
    cout << "Total " << left << setw(16) << "Completions" << right << setw(5) << totalComps << endl;
    cout << "Total " << left << setw(16) << "Yards" << right << setw(5) << totalYards << endl;
    cout << "Total " << left << setw(16) << "Touchdowns" << right << setw(5) << totalTds << endl;
    cout << "Total " << left << setw(16) << "Interceptions" << right << setw(5) << totalInts << endl;
    cout << endl;
}


void printPasserRatings(Quarterback* qbList, int numRecords) {
    int totalComps = 0;
    int totalAtts = 0;
    int totalYards = 0;
    int totalTds = 0;
    int totalInts = 0;
    cout << endl;
    cout << right << setw(13) << "Name" << right << setw(24) << "Passer Rating" << endl;
    for(int i = 0; i < numRecords; i++) {
        getStatTotal(qbList, totalComps, totalAtts, totalYards, totalTds, totalInts, i);
        double a = (((totalComps/static_cast<double>(totalAtts)) - 0.3) * 5);
        checkValueLimit(a);
        double b = (((totalYards/static_cast<double>(totalAtts)) - 3) * 0.25);
        checkValueLimit(b);
        double c = ((totalTds/static_cast<double>(totalAtts)) * 20);;
        checkValueLimit(c);
        double d = (2.375 - ((totalInts/static_cast<double>(totalAtts)) * 25));
        checkValueLimit(d);
        double passerRating = ((a + b + c + d)/0.06);
        cout << right << setw(10) << qbList[i].nameFirst << " " << left << setw(16) << qbList[i].nameLast;
        cout << right << setw(6) << fixed << setprecision(2) << passerRating << endl;
    }
    cout << endl;
}


void checkValueLimit(double& x) {
    if (x > 2.375) {
        x = 2.375;
    }
    else if (x < 0) {
        x = 0;
    }
}


