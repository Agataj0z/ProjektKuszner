#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>    // std::next_permutation, std::sort  
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

int factorial(int n) {
    long number = 1.0;
    if (n < 0)
        cout << "Error! Factorial of a negative number doesn't exist.";
    else
    {
        for (int i = 1; i <= n; ++i)
        {
            number *= i;
        }
    }
    return number;
}

int find_element(vector<int> v, int element) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == element)
            return i;
    }
    return -1;
}

vector<int> generate_unique_numbers(int tabSize)
{
    vector<int> numbers;
    vector<int> result;

    for (int i = 0; i < 100; i++)
        numbers.push_back(i);

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(numbers.begin(), numbers.end(), default_random_engine(seed));

    for (int i = 0; i < tabSize; i++)
        result.push_back(numbers[i]);

    return result;
}

string convert_to_one_line(vector<int> tab, vector<int> tab2)
{
    string one_line_notation;
    int n = tab.size();
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) 
    {
        if (visited[i]) continue;
        int j = i;
        one_line_notation += "( ";
        do {
            visited[j] = true;
            one_line_notation += to_string(tab[j]);
            one_line_notation += ' ';
            j = find_element(tab, tab2[j]);
        } while (j != i);
        one_line_notation += ")";
    }
    return one_line_notation;
}

vector<string> generate_permutation(ofstream& myfile, vector<int> tab, int lineNumber, int count)
{
    vector<string> stringArray;
    vector<int> originalArray;

    myfile << "\\subsection{Permutacje " << lineNumber + 1 << "-ego zbioru \'zapis w dwoch liniach\'}" << endl;
    myfile << "\\begin{center}" << endl;
    myfile << "\\begin{longtable}{|c|}" << endl;
    myfile << "\\hline" << endl;

    sort(tab.begin(), tab.end());
    originalArray = tab;

    for (int i = 0; i < count; i++)
    {
        for (int i = 0; i < tab.size(); i++)
        {
            myfile << tab[i] << " ";
        }
        myfile << "\\\\" << endl;
        if (i != 0) 
        {
            stringArray.push_back(convert_to_one_line(originalArray, tab));
        }
        next_permutation(tab.begin(), tab.end());
    }

    myfile << "\\hline" << endl;
    myfile << "\\end{longtable}" << endl;
    myfile << "\\end{center}" << endl;

    return stringArray;
}

vector<string> generate_all_permutations(ofstream& myfile, vector<int> tab, int lineNumber)
{   
    vector<string> stringArray;
    vector<int> originalArray;

    myfile << "\\subsection{Permutacje " << lineNumber + 1 << "-ego zbioru \'zapis w dwoch liniach\'}" << endl;
    myfile << "\\begin{center}" << endl;
    myfile << "\\begin{longtable}{|c|}" << endl;
    myfile << "\\hline" << endl;

    sort(tab.begin(), tab.end());
    originalArray = tab;

    int j = 0;
    do {
        for (int i = 0; i < tab.size(); i++)
        {
            myfile << tab[i] << " ";
        }
        myfile << "\\\\" << endl;

        if (j != 0)
        {
            stringArray.push_back(convert_to_one_line(originalArray, tab));
        }
        j++;
    } while (next_permutation(tab.begin(), tab.end()));

    myfile << "\\hline" << endl;
    myfile << "\\end{longtable}" << endl;
    myfile << "\\end{center}" << endl;

    return stringArray;
}

bool check_number(string str) {
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}

int main()
{
    srand(time(NULL));
    vector<int> tab;
    vector<string> stringArray;
    int countI, numCount, permCount;
    string stringNum;
    ofstream writeFile;
    fstream inputFile;

    inputFile.open("config.txt", ios::in);
    writeFile.open("tekst.tex");

    writeFile << "\\documentclass[11pt,twoside,a4paper]{article}" << endl;
    writeFile << "\\usepackage[T1]{fontenc}" << endl;
    writeFile << "\\usepackage[utf8]{inputenc}" << endl;
    writeFile << "\\usepackage[polish]{babel}" << endl;
    writeFile << "\\usepackage{amsmath}" << endl;
    writeFile << "\\usepackage{longtable}" << endl;
    writeFile << "\\usepackage[margin = 1in]{geometry}" << endl;
    writeFile << "\\title{Projekt - srodowisko programisty}" << endl;
    writeFile << "\\author{Julia Radosz i Agata Jozefczuk}" << endl;
    writeFile << "\\begin{document}" << endl;
    writeFile << "\\maketitle" << endl;
    writeFile << "\\tableofcontents" << endl;
    writeFile << "\\section{Rodzaje permutacji}" << endl;
    writeFile << "W tym rozdziale zostana przedstawione 2 wybrane rodzaje zapisu permutacji z ktorych korzystamy w programie" << endl;
    writeFile << "\\subsection{Permutacja w notacji \'zapis w dwoch liniach\'}" << endl;
    writeFile << "\\begin{center}" << endl;
    writeFile << "\\[" << endl;
    writeFile << "\\pi =" << endl;
    writeFile << "\\begin{pmatrix}" << endl;
    writeFile << "1 & 2 & 3 & 4 \\\\" << endl;
    writeFile << "4 & 1 & 3 & 2 " << endl;
    writeFile << "\\end{pmatrix}" << endl;
    writeFile << "\\]" << endl;
    writeFile << "\\end{center}" << endl;
    writeFile << "Jest to najbardziej spotykany zapis permutacji." << endl;
    writeFile << "\\subsection{Permutacja w notacji \'zapis w jednej lini\'}" << endl;
    writeFile << "\\begin{center}" << endl;
    writeFile << "\\[" << endl;
    writeFile << "\\pi =" << endl;
    writeFile << "\\begin{pmatrix}" << endl;
    writeFile << "1 & 2 & 3 & 4 & 5 \\\\" << endl;
    writeFile << "5 & 2 & 3 & 1 & 4 " << endl;
    writeFile << "\\end{pmatrix}" << endl;
    writeFile << "= (1 5 4)(2)(3)" << endl;
    writeFile << "\\]" << endl;
    writeFile << "\\end{center}" << endl;
    writeFile << "Przyklad permutacji w zapisie cykli rozlacznych" << endl;
    
    inputFile >> stringNum;
    if (check_number(stringNum))
    {
        countI = stoi(stringNum);
        for (int i = 0; i < countI; i++) // wiersz
        {
            writeFile << "\\section{Permutacje " << i + 1 << "-ego zbioru}" << endl;
            writeFile << "W tym rozdziale zostana przedstawione 2 notacje permutacji zbioru" << endl;

            inputFile >> stringNum;
            if (check_number(stringNum))
            {
                tab.clear();
                numCount = stoi(stringNum); // ile cyfr
                tab = generate_unique_numbers(numCount);

                inputFile >> stringNum; // ile permutacji
                if (check_number(stringNum))
                {
                    permCount = stoi(stringNum);
                    if (factorial(numCount) < permCount)
                    {
                        cout << "too much permutations" << endl;
                        return 0;
                    }
                    stringArray = generate_permutation(writeFile, tab, i, permCount);
                }
                else if (stringNum == "A")
                {
                    stringArray = generate_all_permutations(writeFile, tab, i);
                }
                else
                {
                    cout << stringNum << " is not valid" << endl;
                    return 0;
                }
            }
            else
            {
                cout << stringNum << " is not a valid number" << endl;
                return 0;
            }

            // 1 linia notacja
            writeFile << "\\subsection{Permutacje " << i + 1 << "-ego zbioru \'zapis w jednej lini\'}" << endl;
            writeFile << "\\begin{center}" << endl;
            writeFile << "\\begin{longtable}{|c|}" << endl;
            writeFile << "\\hline" << endl;

            for (int i = 0; i < stringArray.size(); i++)
            {
                writeFile << stringArray[i] << "\\\\" << endl;
            }

            writeFile << "\\hline" << endl;
            writeFile << "\\end{longtable}" << endl;
            writeFile << "\\end{center}" << endl;
            // 1 linia notacja
        }
    }
    else
    {
        cout << stringNum << " is not a valid number" << endl;
    }
    writeFile << "\\end{document}" << endl;

    inputFile.close();
    writeFile.close();
    return 0;
}
