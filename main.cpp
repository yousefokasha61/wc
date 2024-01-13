#include <iostream>
#include <fstream>

using namespace std;

int countNumberOfLines(ifstream &file) {
    int numOfLines = 0;
    string line;

    if (!file.is_open()) {
        cout << "Error opening file!, function: `countNumberOfLines`" << endl;
        return -1;
    }

    while (getline(file, line))
        numOfLines++;

    return numOfLines;
}

int countNumberOfBytes(ifstream &file) {
    int result = 0;
    if (!file.is_open()) {
        cout << "Error opening file!, function: `countNumberOfBytes`" << endl;
        return -1;
    }

    file.seekg(0, ios::end);
    result = int(file.tellg());
    return result;
}

int countNumberOfCharacters(ifstream &file) {
    int numOfCharacters = 0;
    char ch;

    while (file.get(ch))
        numOfCharacters++;

    return numOfCharacters;
}

int countNumberOfWords(ifstream &file) {
    int numberOfWords = 0;
    string line;

    while (getline(file, line)) {
        int i = 0;
        while (i < line.length()) {
            if (isspace(line[i])) {
                i++;
                continue;
            }
            numberOfWords++;
            while (i < line.length() && !isspace(line[i]))
                i++;
        }
    }

    return numberOfWords;
}

bool validOption(string option) {
    if (option.length() != 2 || (option.length() == 2 && option[0] != '-'))
        return false;
    return true;
}


int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        cerr << "Usage: " << argv[0] << " <-l | -w | -c | -m> <filename>" << endl;
        return 1;
    }

    if (argc == 2 && cin.peek()) {
        if (!validOption(string(argv[1]))) {
            cerr << "Usage: " << argv[0] << " <-l | -w | -c | -m> <filename>" << endl;
            return 1;
        }

        char op = string(argv[1])[1];

        string stdInputFileName = "stdInputFile.txt";

        ofstream outputFile(stdInputFileName);

        if (!outputFile) {
            cerr << "Error creating the file " << stdInputFileName << endl;
            return 1;
        }

        string input;
        while (getline(cin, input))
            outputFile << input << endl;

        outputFile.close();

        ifstream stdInputFile(stdInputFileName);

        if (!stdInputFile.is_open()) {
            cerr << "Error: Could not open file " << stdInputFileName << endl;
            return 1;
        }

        switch (op) {
            case 'l':
                cout << countNumberOfLines(stdInputFile) << endl;
                break;
            case 'c':
                cout << countNumberOfBytes(stdInputFile) << endl;
                break;
            case 'm':
                cout << countNumberOfCharacters(stdInputFile) << endl;
                break;
            case 'w':
                cout << countNumberOfWords(stdInputFile) << endl;
                break;
            default:
                cerr << "Error: Invalid option. Use -l, -w, -c or -m." << endl;
                break;
        }

        stdInputFile.close();

        if (remove(stdInputFileName.c_str()) == 0) {
            // File successfully deleted
        } else {
            cerr << "Error: Deleting the file " << stdInputFileName << endl;
            return 1;
        }

        return 0;


    }
    else if (argc == 2)
    {
        ifstream inputFile(argv[1]);

        if (!inputFile.is_open())
        {
            cerr << "Error: Could not open file " << argv[1] << endl;
            return 1;
        }

        cout << countNumberOfLines(inputFile) << " ";

        inputFile.clear();               // Clear any error flags
        inputFile.seekg(0, ios::beg);    // Move to the start of the file

        cout << countNumberOfWords(inputFile) << " ";

        inputFile.clear();               // Clear any error flags
        inputFile.seekg(0, ios::beg);    // Move to the start of the file

        cout << countNumberOfBytes(inputFile) << " " <<  argv[1] << endl;

        inputFile.close();

        return 0;
    }
    if (argc == 3)
    {
        if (!validOption(string(argv[1])))
        {
            cerr << "Usage: " << argv[0] << " <-l | -w | -c | -m> <filename>" << endl;
            return 1;
        }

        char option = string(argv[1])[1];

        ifstream inputFile(argv[2]);

        if (!inputFile.is_open())
        {
            cerr << "Error: Could not open file " << argv[2] << endl;
            return 1;
        }

        switch (option)
        {
            case 'l':
                cout << countNumberOfLines(inputFile) << " " << argv[2] << endl;
                break;
            case 'c':
                cout << countNumberOfBytes(inputFile) << " " << argv[2] << endl;
                break;
            case 'm':
                cout << countNumberOfCharacters(inputFile) << " " << argv[2] << endl;
                break;
            case 'w':
                cout << countNumberOfWords(inputFile) << " " << argv[2] << endl;
                break;
            default:
                cerr << "Error: Invalid option. Use -l, -w, -c or -m." << endl;
                return 1;
        }

        inputFile.close();

        return 0;
    }
    return 0;
}
