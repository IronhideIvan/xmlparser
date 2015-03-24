/* 
 * File:   xml_data.h
 * Author: Arthur Lisek-Koper
 * e-mail: arthur_lisekkoper@student.uml.edu
 * 
 * Created on September 14, 2014, 8:09 PM
 * Last modified on October 23, 2014.
 * 
 * This code parses xml data and stored all element data into a tree
 *  retaining the hierarchical structure of the original file.
 * 
 * TODO: Expand isSpace() to check if there are any illegal
 *          symbols within the xml tag instead of just spaces..
 */

#ifndef XML_DATA_H
#define	XML_DATA_H

#include <list>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>

#include "Parser_State.h"
#include "xml_nodes.h"

/**
 * The xml_data class is used to handle the various tasks involved in reading
 *  and parsing the data within an xml document. This class separates out the 
 *  element tag names and stores its respective contents, attributes, and 
 *  children for further processing.
 */
class xml_data {
private:
    ///Stack structure of the xml document. Used during parsing of the document
    /// to ensure legality of its structure.
    list<xml_node*> stack_elem;

    ///Tree of all elements within xml document.
    list<xml_node*> tree_elem;

    ///Current Parsing state of the xml document
    ParserState ps_elemContent;

    ///The current position within the tree data structure.
    xml_node* cur_pos;

public:
    ///Default constructor created by Netbeans.
    xml_data();
    
    ///Default copy constructor created by Netbeans.
    xml_data(const xml_data& orig);
    
    ///Default destructor created by Netbeans.
    virtual ~xml_data();

    /**
     * Processes an input xml file
     * 
     * @param file_name - path of file to be processed.
     * 
     * @param DEBUG_INFO - prints out debugging information if set to
     *                      one.
     * 
     * @return  - EXIT_FAILURE or EXIT_SUCCESS.
     */
    int read_file(char* file_name, bool DEBUG_INFO = false);

    /**
     * Remove whitespace from the beginning and the end of the given string.
     * 
     * @param file_line - string to trimmed.
     * 
     * @return  - trimmed string.
     */
    string trim_line(string file_line);

    /**
     * Find the parser state of the given line.
     * 
     * @param line_ptr  - address of line to be examined.
     * 
     * @return  - ParserState of current line.
     */
    ParserState find_tag(string* line_ptr);

    /**
     * Finds the attributes present within the passed xml line, and then
     *  stores them into memory.
     * 
     * @param line - The trimmed xml line to be read for attributes.
     * @param temp_node - Pointer to the xml_node containing the element data from
     *                      the read line.
     * @return - EXIT_SUCCESS or EXIT_FAILURE;
     */
    int get_attribute(string line, xml_node* temp_node);

    /**
     * Insert an xml_node into the tree data structure.
     * 
     * @param line - Full element line to be parsed for attributes.
     * @param name - Only the name of the element.
     * @param line_number - The line number which the element was found.
     * @return EXIT_SUCCESS, or EXIT_FAILURE
     */
    int insert_tree(string line, string name, int line_number);

    /**
     * Returns a pointer one level up from cur_pos.
     * 
     * @return pointer to the parent object of what cur_pos is pointing to.
     */
    xml_node* Parent_tree();

    /**
     * Handles the current line appropriately, depending on the state of
     *  ps_elemContent.
     * 
     * @param trimmed_line  - line pertaining to this class' current state.
     * 
     * @param line_number   - line number where parameter trimmed_line was
     *                          found.
     * 
     * @param DEBUG_INFO - see \ref read_file
     * 
     * @return  - EXIT_SUCCESS or EXIT_FAILURE
     */
    int handle_tag(string trimmed_line, int line_number, bool DEBUG_INFO);

    /**
     * finds the string name between the brackets of an opening or closing tag.
     * @param line  - string where tag exists
     * 
     * @param init  - position within passed string to begin looking for
     *                  a tag. (Useful if both an opening and closing tag
     *                  exist in the same string).
     * 
     * @return  - string containing the name of the tag within the given line.
     */
    string get_tag_name(string line, int init = 0);

    /**
     * Checks if a space exists immediately after the first parameter or
     *  before the second parameter. created to check for legality of an opening
     *  or closing bracket. 
     * 
     * @param file_line - the entire line of the file to be read 
     * 
     * @param poso - integer position within string file_line to be tested if 
     *               parameter is legal opening bracket.
     * 
     * @param posc - integer position within string file_line to be tested if 
     *               parameter is legal closing bracket.
     * 
     * @return TRUE if legal bracket.
     *         FALSE if illegal bracket.
     */
    bool isSpace(string file_line, int poso, int posc);

    /**
     * Debugging function created by Jesse Heines. Taken from his class notes.
     * Edited by Arthur Lisek-Koper.
     * 
     * Function prints out the current state of the passed ParserState object.
     * 
     * @param ps    - ParserState to be printed out onto user display.
     */
    void show_state(ParserState ps);

    /**
     * Pushes data into list list_elem.
     * 
     * @param tag_name - string to be assigned as str_name in new xml_node.
     * @param line_number - line number to be assigned as num_line in xml_node.
     * @return - EXIT_FAILURE or EXIT_SUCCESS
     */
    int store_stack(string tag_name,
            int line_number);

    /**
     * Store tag information into a tree.
     * 
     * @param name - Element name of the tag to be stored.
     * @param line - entire line to be parsed for attributes
     * @param line_num - line number of the tag to be stored.
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int store_tree(string name, string line, int line_num);


    /**
     * Pops the first element in list_elem.
     */
    void pop_stack();

    /**
     * Checks if the given string is equal to str_name in the first element
     *  of list_elem. 
     * @param tag_name  - string to be compared with str_name.
     * @return  - true is both strings are equal.
     *          - false is string are not equal.  
     */
    bool are_tags_equal(string tag_name);

    /**
     * Print out the current content within the stack
     */
    void print_stack_data();

    /**
     * calls the toString() method of the first element within tree_elem. This
     * outputs all of the data within the tree.
     */
    void print_tree_data();
    
    /**
     * Prints out the xml data structure in JSON format.
     * 
     * @param file_name - file location where output of JSON data will be stored
     * 
     * @return EXIT_SUCCESS or EXIT_FAILURE
     */
    int XMLtoJSON( string file_name );
};

#endif	/* XML_DATA_H */

