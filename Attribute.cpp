/* 
 * File:   Attribute.cpp
 * Author: Arthur Lisek-Koper
 * e-mail: arthur_lisekkoper@student.uml.edu
 * 
 * Created on October 21, 2014, 2:41 PM
 * Last modified on October 23, 2014.
 */

#include "Attribute.h"

Attribute::Attribute( ) {
    this->name = "{EMPTY}";
    this->value = "{EMPTY}";
}

Attribute::Attribute( string attr_name, string attr_value ) {
    this->name = attr_name;
    this->value = attr_value;
}

Attribute::Attribute( const Attribute& orig ) {
}

Attribute::~Attribute( ) {
}

void Attribute::setValue( string value ) {
    this->value = value;
}

string Attribute::getValue( ) const {
    return value;
}

void Attribute::setName( string name ) {
    this->name = name;
}

string Attribute::getName( ) const {
    return name;
}