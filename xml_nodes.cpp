/* 
 * File:   xml_nodes.cpp
 * Author: Arthur Lisek-Koper
 * e-mail: arthur_lisekkoper@student.uml.edu
 * 
 * Created on October 22, 2014, 9:00 AM
 * Last modified on October 23, 2014.
 */

#include "xml_nodes.h"

xml_node::xml_node( ) {
    this->str_name = "";
    this->content = "";
    this->num_line = 0;
    this->parent = NULL;
    this->size_child = 0;
    this->size_attr = 0;
    this->level = 0;
    this->list_child.push_front(NULL);
    this->list_attr.push_front(NULL);

}

xml_node::xml_node( string name, int line ) {
    this->str_name = name;
    this->num_line = line;
    this->content = "";
    this->parent = NULL;
    this->size_child = 0;
    this->size_attr = 0;
    this->level = 1;
    this->list_child.push_front(NULL);
    this->list_attr.push_front(NULL);
}

xml_node::xml_node( string name, int line, xml_node* father ) {
    this->str_name = name;
    this->num_line = line;
    this->parent = father;
    this->size_child = 0;
    this->size_attr = 0;
    this->level = 1;
    this->list_child.push_front(NULL);
    this->list_attr.push_front(NULL);
}

xml_node::xml_node( const xml_node& orig ) {

}

xml_node::~xml_node( ) {

}

int xml_node::push_attr( string attr_name, string attr_value ) {

    Attribute* temp_attr = new Attribute(attr_name, attr_value);

    if ( temp_attr == NULL ) {
        return EXIT_FAILURE;
    }

    this->list_attr.back() = temp_attr;
    this->list_attr.push_back(NULL);
    this->size_attr += 1;

    return EXIT_SUCCESS;
}

void xml_node::push_child( xml_node* child ) {

    this->list_child.back() = child;
    this->list_child.push_back(NULL);

    this->size_child += 1;
    child->level = ( this->level + 1 );
}

void xml_node::toString( ) {

    list<xml_node*>::iterator it_child = list_child.begin();
    list<Attribute*>::iterator it_attr = list_attr.begin();

    ///Indent line based on which level of the tree the xml_node is located at.
    for ( unsigned int i = 0; i < this->level; ++i ) {
        cout << ". ";
    }

    ///Print out information present within this xml_node. If the node is the
    /// root node, then display that information.
    if ( this->level == 0 ) {
        cout << "Root '" << this->str_name << "' was found on line " << this->num_line;
        cout << " with " << this->size_child << " children and " << this->size_attr;
        cout << " attributes. ";
        if ( this->content == "" ) {
            cout << "Root content = {empty}" << endl;
        }
        else {
            cout << "Root content = " << this->content << endl;
        }
    }
    else {
        cout << "Child '" << this->str_name << "' was found on line " << this->num_line;
        cout << " with " << this->size_child << " children and " << this->size_attr;
        cout << " attributes. ";
        if ( this->content == "" ) {
            cout << "Child content = {empty}" << endl;
        }
        else {
            cout << "Child content = " << this->content << endl;
        }
    }

    ///Display all attribute information of current node.
    if ( this->size_attr > 0 ) {

        for ( int i = 0; *it_attr != NULL; i++ ) {
            for ( unsigned int j = 0; j < this->level; ++j ) {
                cout << "- ";
            }
            cout << "Attribute No. " << i + 1 << ", name = " << ( *it_attr )->getName()
                    << ", value = " << ( *it_attr )->getValue() << endl;
            it_attr = next(it_attr, 1);
        }

    }

    ///Call the next level of nodes.
    while ( *it_child != NULL ) {
        ( *it_child )->toString();
        it_child = next(it_child, 1);
    }

}

void xml_node::toJSON( ofstream* JSON_file ) {



    list<xml_node*>::iterator it_child = list_child.begin();
    list<Attribute*>::iterator it_attr = list_attr.begin();

    if ( this->size_child == 0 && this->size_attr == 0 ) {
        print_spaces(JSON_file);
        *JSON_file << '"' << this->str_name << '"' << ":   ";
        *JSON_file << '"' << this->content << '"';
        return;
    }
    else {

        if ( this->level == 0 ) {
            *JSON_file << '{';
        }
        else {
            print_spaces(JSON_file);
            *JSON_file << '"' << this->str_name << '"' << ":   " << '{';

            if ( this->content != "" ) {
                print_spaces(JSON_file);
                *JSON_file << '"' << "content" << '"' << ":   " << this->content << ',';
            }

            for ( int i = 0; *it_attr != NULL; i++ ) {
                print_spaces(JSON_file);
                *JSON_file << "  " << '"' << "@" << ( *it_attr )->getName() << '"' << ":   ";
                *JSON_file << '"' << ( *it_attr )->getValue() << '"';
                it_attr = next(it_attr, 1);

                if ( this->size_child > 0 || *it_attr != NULL ) {
                    *JSON_file << ',';
                }
            }
        }

        while ( *it_child != NULL ) {
            ( *it_child )->toJSON(JSON_file);
            it_child = next(it_child, 1);

            if ( *it_child != NULL ) {
                *JSON_file << ',';
            }
        }

        print_spaces(JSON_file);
        *JSON_file << '}';
    }
}

void xml_node::print_spaces( ofstream* loc_file, int INDENT_FACTOR ) {

    int indent = ( this->level * INDENT_FACTOR );

    *loc_file << "\n";
    for ( int i = 0; i < indent; i++ ) {
        *loc_file << " ";
    }
}

void xml_node::setNum_line( int num_line ) {
    this->num_line = num_line;
}

int xml_node::getNum_line( ) const {
    return num_line;
}

void xml_node::setStr_name( string str_name ) {
    this->str_name = str_name;
}

string xml_node::getStr_name( ) const {
    return str_name;
}

void xml_node::setSize_attr( int size_attr ) {
    this->size_attr = size_attr;
}

int xml_node::getSize_attr( ) const {
    return size_attr;
}

void xml_node::setParent( xml_node* parent ) {
    this->parent = parent;
}

xml_node* xml_node::getParent( ) const {
    return parent;
}

void xml_node::setSize_child( int size_child ) {
    this->size_child = size_child;
}

int xml_node::getSize_child( ) const {
    return size_child;
}

void xml_node::setContent( string content ) {
    this->content = content;
}

string xml_node::getContent( ) const {
    return content;
}

void xml_node::setLevel( unsigned int level ) {
    this->level = level;
}

unsigned int xml_node::getLevel( ) const {
    return level;
}