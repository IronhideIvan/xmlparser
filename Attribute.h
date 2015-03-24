/* 
 * File:   Attribute.h
 * Author: Arthur Lisek-Koper
 * e-mail: arthur_lisekkoper@student.uml.edu
 * 
 * Created on October 21, 2014, 2:41 PM
 * Last modified on October 23, 2014.
 * 
 * This code is used to contain the attributes present within each element
 *  of an xml document, if any exist.
 */

#ifndef ATTRIBUTE_H
#define	ATTRIBUTE_H

#include <string>


using namespace std;

/**
 * This class holds the attribute information of a single attribute found within
 *  an element from an xml document. 
 */
class Attribute {
public:
    ///Default constructor created by Netbeans.
    Attribute();
    
    /**
     * Constructor that assigns the name and value of the Attribute object.
     * @param attr_name - Name of the attribute.
     * @param attr_value - Value of the attribute.
     */
    Attribute(string attr_name, string attr_value);
    
    ///Default copy constructor created by Netbeans.
    Attribute(const Attribute& orig);
    
    ///Default destructor created by Netbeans.
    virtual ~Attribute();

    /**
     * Setter function for 'value'
     * @param new content of 'value' to be set.
     */
    void setValue(string value);

    /**
     * Getter function for 'value'
     * @return the content of 'value'.
     */
    string getValue() const;

    /**
     * Setter function for 'name'
     * @param new content of 'name' to be set.
     */
    void setName(string name);

    /**
     * Getter function for 'name'
     * @return the content of 'name'.
     */
    string getName() const;

private:
    ///Name of the attribute.
    string name;
    
    ///Value of the attribute.
    string value;
};

#endif	/* ATTRIBUTE_H */

