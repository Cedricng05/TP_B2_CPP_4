#include <iostream>
#include <windows.h>
#include <filesystem>
#include <fstream>
#include <string>
#include "Config.h"
#include "Drive.h"

Config::Config()
{
    //ctor
}

Config::~Config()
{
    //dtor
}


void Config::create(){

    // file pointer
    fstream fout;

    // opens an existing csv file or creates a new file.
    fout.open("config.csv", ios::out | ios::app);

    cout << "Enter the details about file :" <<endl;

    int i, roll;
    string name, value;

    //Read the input
    for (i = 0; i < 2; i++) {
        cin >> roll
            >> name
            >> value;
            break;
    }

    // Insert the data to file
    fout << roll << ","
         << name << ","
         << value
         << "\n";
}

void Config::readRecord()
{

    //File pointer
    fstream fin;

    // OPen an existing file
    fin.open("config.csv", ios::in);

    //Get the roll number
    // of which the data is required
    int rollnum, roll2, count = 0;
    cout << "Enter the roll number "
         << "of the data to display details : ";
    cin >> rollnum;

    //Read the Data from the file
    // as String Vector
    vector <string> row;
    string line, word, temp;

    while (fin >> temp) {

        row.clear();

        //Read an entire row and
        // store it in a string variable 'line'
        getline(fin, line);

        // used for breaking words
        stringstream s(line);

        // read every column data of a row and
        //store it in a string variable, 'word'
        while (getline(s, word, ',')){

            //add all the column data
            //of a row to a vector
            row.push_back(word);
        }

        // comvert string to integer for comparaison
        roll2 = stoi(row[0]);

        // Compare the roll number
        if (roll2 == rollnum){

            // print the found data
            count = 1;
            cout << "Details of Roll" << row[0] << " :\n";
            cout << "Name : " << row[1] << " :\n";
            cout << "Value : " << row[2] << " :\n";
            break;
        }
    }
    if (count == 0){
        cout << "Record not found\n";
    }
}

/*void Config::onlyThat(){

    // Path to the file
    char* filepath = "F:\\keyce_drive";

    // Passing the path as argument to the function
    filesystem::path p(filepath);
    cout <<p.filename();
    p.extension() = ".pdf", ".mp4", ".mp3", ".pptx", ".jpg", ".png", ".gif";

    if (p.extension() != ".pdf") {
         cout << "Error to copy, cause extension form" << endl;
    }
    else{
        copyFile();
    }
}*/

