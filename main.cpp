/* 
 * File:   main.cpp
 * Author: Arthur Lisek-Koper
 * e-mail: arthur_lisekkoper@student.uml.edu
 * Class: 91.204
 *
 * Created on September 14, 2014, 7:54 PM
 * Last Modified on October 2, 2014
 * 
 * \mainpage Xml parser in C++
 * 
 * \section summary_sec Summary of Code
 * This Program is designed to open an xml file, store tag information within
 * a tree, then print out the entire tree containing the hierarchical structure
 * of the original xml document in a readable manner.
 * 
 * A copy of the output is saved within the project folder
 * as "Output.txt in case there was a problem running the code on your machine.
 */

#include <cstdlib>
#include <ostream>
#include "xml_data.h"

using namespace std;

int main( int argc, char** argv ) {

    xml_data xfile_1;

    //name of xml file is read from the command line.
    if ( xfile_1.read_file(argv[1]) == EXIT_FAILURE ) {
        cout << "AN ERROR OCCURED, TERMINATING PROGRAM." << endl;
        return EXIT_FAILURE;
    }

    //name of file to place JSON output.
    if ( xfile_1.XMLtoJSON(argv[2]) == EXIT_FAILURE ) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

