/* 
 * File:   xml_nodes.h
 * Author: Arthur Lisek-Koper
 * e-mail: arthur_lisekkoper@student.uml.edu
 * 
 * Created on October 22, 2014, 9:00 AM
 * Last modified on October 23, 2014.
 * 
 * This code is a node within a tree containing data from an xml document.
 */

#ifndef XML_NODES_H
#define	XML_NODES_H

#include <string>
#include <fstream>

#include "Attribute.h"

using namespace std;

/**
 * class xml_node is a data container for class xml_data.
 */
class xml_node {
private:
    ///name of xml tag.
    string str_name;

    ///The content of an element.
    string content;

    ///Line number of the xml tag.
    int num_line;

    ///Number of children this object currently has.
    int size_child;

    ///Number of attributes this object holds.
    int size_attr;

    ///The current level of the object within the tree.
    unsigned int level;

    ///Pointer to the parent of this object. If object is the root element,
    /// then the object points to itself.
    xml_node* parent;

    ///Pointers to the list of all children this object currently has.
    list<xml_node*> list_child;

    ///Pointers to the list of all attributes attached to this object, if any.
    list<Attribute*> list_attr;

public:
    ///Default constructor created by Netbeans.
    xml_node();
    
    /**
     * Constructor which assigns the given name and which line the element was
     *  found.
     * 
     * @param name - Name of the found element within the xml document.
     * @param line - Which line within the xml document was the element found.
     */
    xml_node(string name, int line);
    
    /**
     * Constructor which assigns the given name, which line the element was
     *  found, and the parent object if the node is part of a tree structure.
     * 
     * @param name - Name of the found element within the xml document.
     * @param line - Which line within the xml document was the element found.
     * @param father - Pointer to the parent object of this node within a tree.
     */
    xml_node(string name, int line, xml_node* father);
    
    ///Default copy constructor created by Netbeans.
    xml_node(const xml_node& orig);
    
    ///Default destructor created by Netbeans.
    virtual ~xml_node();

    /**
     * Print out all private member variables.
     */
    void toString();
    
    /**
     * Print out member variables in JSON format.
     * 
     * @param JSON_file - file location where JSON data will be stored.
     */
    void toJSON( ofstream* JSON_file );
    
    /**
     * Prints out onto the display a number of spaces in each new line
     *  while converting xml data to a JSON file.
     * 
     * @param loc_file - location of the JSON file to be edited.
     * 
     * @param INDENT_FACTOR - how many spaces each indent should be.
     * 
     * @see toJSON
     */
    void print_spaces( ofstream* loc_file, int INDENT_FACTOR = 2 );

    /**
     * Push the passed attribute information into a list of 'Attribute' objects.
     * 
     * @param attr_name - string containing the name of the attribute.
     * @param attr_value - string containing the value of the attribute.
     * @return - EXIT_SUCCESS or EXIT_FAILURE;
     */
    int push_attr(string attr_name, string attr_value);

    /**
     * Push an xml_node as a child to this object.
     * 
     * @param child - the xml_node* to be pushed.
     */
    void push_child(xml_node* child);

    /**
     * Setter function for 'num_line'
     * @param new content of 'num_line' to be set.
     */
    void setNum_line(int num_line);

    /**
     * Getter function for 'num_line'
     * @return the content of 'num_line'.
     */
    int getNum_line() const;

    /**
     * Setter function for 'str_name'
     * @param new content of 'str_name' to be set.
     */
    void setStr_name(string str_name);

    /**
     * Getter function for 'str_name'
     * @return the content of 'str_name'.
     */
    string getStr_name() const;

    /**
     * Setter function for 'size_attr'
     * @param new content of 'size_attr' to be set.
     */
    void setSize_attr(int size_attr);

    /**
     * Getter function for 'size_attr'
     * @return the content of 'size_attr'.
     */
    int getSize_attr() const;

    /**
     * Setter function for 'parent'
     * @param new content of 'parent' to be set.
     */
    void setParent(xml_node* parent);

    /**
     * Getter function for 'parent'
     * @return the content of 'parent'.
     */
    xml_node* getParent() const;

    /**
     * Setter function for 'size_child'
     * @param new content of 'size_child' to be set.
     */
    void setSize_child(int size_child);

    /**
     * Getter function for 'size_child'
     * @return the content of 'size_child'.
     */
    int getSize_child() const;

    /**
     * Setter function for 'content'
     * @param new content of 'content' to be set.
     */
    void setContent(string content);

    /**
     * Getter function for 'content'
     * @return the content of 'content'.
     */
    string getContent() const;

    /**
     * Setter function for 'level'
     * @param new content of 'level' to be set.
     */
    void setLevel(unsigned int level);

    /**
     * Getter function for 'level'
     * @return the content of 'level'.
     */
    unsigned int getLevel() const;

};
#endif	/* XML_NODES_H */

