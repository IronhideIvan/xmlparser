/* 
 * File:   xml_data.cpp
 * Author: Arthur Lisek-Koper
 * e-mail: arthur_lisekkoper@student.uml.edu
 * 
 * Created on September 14, 2014, 8:09 PM
 * Last modified on October 23, 2014.
 */

#include "xml_data.h"

xml_data::xml_data( ) {
    this->ps_elemContent = STARTING_DOCUMENT;
    this->cur_pos = NULL;
    this->stack_elem.push_front(NULL);
    this->tree_elem.push_front(NULL);
}

xml_data::xml_data( const xml_data& orig ) {
}

xml_data::~xml_data( ) {
}

int xml_data::read_file( char* file_name, bool DEBUG_INFO ) {

    //Current line read in document.
    int line_num = 0;

    //Name of file to be opened.
    ifstream file_1(file_name);

    //Maximum character length that will be read of each line.
    char p_line[256];

    // tag_name = name of tag, if present, on currently loaded line.
    string tag_name, trimmed_line;

    // Read each line and search for xml-document tag names,
    // then save the tag name and line-number into a linked list.
    while ( file_1.getline(p_line, 256) != NULL ) {
        ++line_num; //Increment current line number.
        tag_name = p_line; //assign char* p_line to string tag_name for
        //parsing.


        trimmed_line = trim_line(p_line); // remove whitespace.
        tag_name = trimmed_line;
        ps_elemContent = find_tag(&tag_name);

        // If ifGoodtag == ERROR or UNKNOWN, then return EXIT_FAILURE. Otherwise
        //print out current state of program.
        if ( ps_elemContent == ERROR || ps_elemContent == UNKNOWN ) {
            cout << "line no." << line_num << ". ";
            return EXIT_FAILURE;
        } //handle the tag in the appropriate way.
        else {
            if ( handle_tag(trimmed_line, line_num, DEBUG_INFO) == EXIT_FAILURE )
                return EXIT_FAILURE;
        }
    }


    return EXIT_SUCCESS;

}

void xml_data::print_stack_data( ) {

    list<xml_node*>::iterator it = stack_elem.begin(); //iterator for linked-
    // list

    //print out the name of the first object within list_elem.
    for ( int i = 0; *it != NULL; ++i ) {
        cout << ( *it )->getStr_name() << " ";

        it = next(it, 1);
    }
}

string xml_data::trim_line( string file_line ) {
    while ( file_line[0] == ' ' || file_line[0] == '\t' ) {
        file_line.erase(file_line.begin());
    }

    while ( file_line[file_line.length() - 1] == ' ' ||
            file_line[file_line.length() - 1] == '\t' ) {
        file_line.erase(file_line.end() - 1);
    }

    return file_line;
}

ParserState xml_data::find_tag( string* line_ptr ) {

    // opbr = the position of the '<' bracket.
    // clbr = the position of the '>' bracket.
    int opbr, clbr;

    // trimmed_line = line from read file with trimmed whitespace.
    string trimmed_line = *line_ptr;

    //find first case of '<' and '>'. if none exist, return value is -1 (npos)
    opbr = trimmed_line.find('<');
    clbr = trimmed_line.find('>');

    //if no '>' exists, and current state is IN_COMMENT or STARTING_COMMENT,
    //  return IN_COMMENT.   
    if ( clbr == -1 ) {
        if ( ps_elemContent == IN_COMMENT || ps_elemContent == STARTING_COMMENT ) {
            return IN_COMMENT;
        }//if line is only whitespace, return EMPTY_LINE
        else if ( trimmed_line[0] == '\r' ) {
            return EMPTY_LINE;
        }
            //else if no opening tag is found as well, but current state is
            //  ELEMENT_OPENING_TAG, return ELEMENT_CONTENT.
        else if ( opbr == -1 && ps_elemContent == ELEMENT_OPENING_TAG ) {
            return ELEMENT_CONTENT;
        } //else if '<' is '<!--', return STARTING_COMMENT.
        else if ( ( opbr != -1 ) && ( trimmed_line.substr(opbr, 4) == "<!--" ) )
            return STARTING_COMMENT;

            //else return UNKNOWN.
        else {
            cout << "Unidentified State" << endl;
            return UNKNOWN;
        }
    }

    //if '<' is followed by '?' and '>' is preceeded by '?', return DIRECTIVE.
    if ( trimmed_line[opbr + 1] == '?' ) {

        //if '?' does not come before '>', and spaces exist before closing tag 
        // and after the opening tag, return ERROR.
        if ( trimmed_line[clbr - 1] != '?' ||
                ( isSpace(trimmed_line, opbr + 1, clbr - 1) == true ) )
            return ERROR;

        else return DIRECTIVE;
    }//else if '<' doesn't exist, but '-->' does, return ENDING_COMMENT.
    else if ( ( opbr == -1 ) &&
            ( trimmed_line.substr(clbr - 2, 3) == "-->" ) )
        return ENDING_COMMENT;

        //else if '<' is '<!--' and '>' is also '-->', return ONE_LINE_COMMENT.
    else if ( ( trimmed_line.substr(opbr, 4) == "<!--" ) ) {

        if ( trimmed_line.substr(clbr - 2, 3) == "-->" )
            return ONE_LINE_COMMENT;

        else return ERROR;
    }//else if '<' is '</', and space surrounding the respective brackets is
        //  legal, return ELEMENT_CLOSING_TAG.
    else if ( trimmed_line.substr(opbr, 2) == "</" ) {

        if ( isSpace(trimmed_line, opbr, clbr) == true ) {
            cout << "Illegal spacing" << endl;
            return ERROR;
        }
        else return ELEMENT_CLOSING_TAG;
    }//else an opening tag has been found.    
    else {

        if ( isSpace(trimmed_line, opbr, clbr) == true ) {
            cout << "Illegal spacing" << endl;
            return ERROR;
        }

        if ( trimmed_line.find("</", clbr + 1) != string::npos ) {
            return ELEMENT_NAME_AND_CONTENT;
        }//else if the tag is self closing, the contents is set to an empty 
            //  string, return SELF_CLOSING_TAG
        else if ( trimmed_line.find("/>") != string::npos ) {
            return SELF_CLOSING_TAG;
        }//else return ELEMENT_OPENING_TAG
        else {
            return ELEMENT_OPENING_TAG;
        }
    }

}

bool xml_data::isSpace( string file_line, int poso, int posc ) {

    if ( ( file_line.substr(poso + 1, 1) == " " ) ||
            ( file_line.substr(posc - 1, 1) == " " ) )
        return true;

    else return false;
}

int xml_data::handle_tag( string trimmed_line, int line_number, bool DEBUG_INFO ) {

    string tag_name;
    tag_name = get_tag_name(trimmed_line);

    if ( ps_elemContent != EMPTY_LINE && DEBUG_INFO == true ) {
        cout << "Full line - " << trimmed_line << endl;
        cout << "Line no. - " << line_number << endl;
        show_state(ps_elemContent);
    }

    switch ( ps_elemContent ) {

        case ELEMENT_OPENING_TAG:

            if ( store_stack(tag_name, line_number) == EXIT_FAILURE ) {
                return EXIT_FAILURE;
            }

            if ( insert_tree(trimmed_line, tag_name, line_number) == EXIT_FAILURE ) {
                return EXIT_FAILURE;
            }

            if ( DEBUG_INFO == true ) {
                cout << "Data stored." << endl;
                cout << "Status of stack(list): ";
                print_stack_data();
                cout << endl << endl;
            }
            break;

        case ELEMENT_NAME_AND_CONTENT:

            if ( DEBUG_INFO == true ) {
                cout << "Tag - " << tag_name << endl;
            }

            //checks if the opening tag and the closing tag are the same.
            if ( tag_name !=
                    get_tag_name(trimmed_line, trimmed_line.find('>')) ) {
                cout << "Closing tag and opening tag are not equal." << endl;
                return EXIT_FAILURE;
            }

            if ( insert_tree(trimmed_line, tag_name, line_number) == EXIT_FAILURE ) {
                return EXIT_FAILURE;
            }

        {
            //find and print out the content between opening and closing
            //  tags.
            int opbr, clbr;
            string content;

            clbr = trimmed_line.find('>');
            opbr = trimmed_line.find('<', clbr);

            content = trimmed_line.substr(clbr + 1, ( opbr - clbr ) - 1);
            this->cur_pos->setContent(content);
            if ( DEBUG_INFO == true ) {
                cout << "Content - " << content << endl << endl;
            }
        }

            ///Because ELEMENT_NAME_AND_CONTENT contains a closing tag,
            /// return cur_pos back to the parent since there is no motion
            /// on the stack.
            this->cur_pos = Parent_tree();

            break;

        case ELEMENT_CLOSING_TAG:

            if ( !are_tags_equal(tag_name) ) {
                cout << "Error in document format, terminating program" << endl;
                return EXIT_FAILURE;
            }

            pop_stack();

            if ( DEBUG_INFO == true ) {
                cout << "Data stored." << endl;
                cout << "Status of stack(list): ";
                print_stack_data();
                cout << endl << endl;
            }

            this->cur_pos = Parent_tree();

            break;

        case SELF_CLOSING_TAG:

            if ( insert_tree(trimmed_line, tag_name, line_number) == EXIT_FAILURE ) {
                return EXIT_FAILURE;
            }

            this->cur_pos = Parent_tree();

            if ( DEBUG_INFO == true ) {
                cout << "Content - {EMPTY}" << endl;
            }

        case DIRECTIVE:
        case ELEMENT_CONTENT:
        case STARTING_COMMENT:
        case IN_COMMENT:
        case ENDING_COMMENT:
        case ONE_LINE_COMMENT:
            if ( DEBUG_INFO == true ) {
                cout << "No action taken." << endl << endl;
            }
            break;

        case EMPTY_LINE:
            //Do nothing.
            break;

        case ERROR:
        case UNKNOWN:
        default:
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

string xml_data::get_tag_name( string line, int init ) {

    //Find whether a '>' or a ' ' is closer to the '<' to determine
    //where the tag name ends.
    int space, bracket, length, pos;

    pos = line.find('<', init);
    space = line.find(' ', pos);
    bracket = line.find('>', pos);

    if ( space == -1 || bracket < space ) {
        length = ( bracket - pos );
    }
    else {
        length = ( space - pos );
    }

    //if tag is closing tag, account for the '/' character.
    if ( line[pos + 1] == '/' ) {
        pos += 1;
        length -= 1; //account for shift in pos so substring does not
        //  include the '>'.
    }

    return line.substr(pos + 1, length - 1);
}

int xml_data::store_stack( string tag_name, int line_number ) {

    xml_node* node_ptr = new xml_node(tag_name, line_number); //allocate memory

    //The following are for debugging purposes, uncomment to use.
    //cout << "tag name to be stored: " << tag_name << endl;
    //cout << "line number to be stored: " << line_number << endl;
    // --- end of debugging comments.

    if ( node_ptr == NULL ) {
        cout << "ERROR - node_ptr == NULL. return EXIT_FAILURE." << endl;
        return EXIT_FAILURE;
    }

    stack_elem.push_front(node_ptr);

    return EXIT_SUCCESS;
}

void xml_data::pop_stack( ) {

    delete( stack_elem.front() );
    stack_elem.pop_front();

}

bool xml_data::are_tags_equal( string tag_name ) {

    list<xml_node*>::iterator it = stack_elem.begin();

    if ( ( *it )->getStr_name() == tag_name ) {
        return true;
    }
    else return false;
}

void xml_data::show_state( ParserState ps ) {
    cout << "ParserState = ";
    switch ( ps ) {
        case UNKNOWN: cout << "UNKNOWN";
            break;
        case STARTING_DOCUMENT: cout << "STARTING_DOCUMENT";
            break;
        case DIRECTIVE: cout << "DIRECTIVE";
            break;
        case ELEMENT_OPENING_TAG: cout << "ELEMENT_OPENING_TAG";
            break;
        case ELEMENT_CONTENT: cout << "ELEMENT_CONTENT";
            break;
        case ELEMENT_NAME_AND_CONTENT: cout << "ELEMENT_NAME_AND_CONTENT";
            break;
        case ELEMENT_CLOSING_TAG: cout << "ELEMENT_CLOSING_TAG";
            break;
        case SELF_CLOSING_TAG: cout << "SELF_CLOSING_TAG";
            break;
        case STARTING_COMMENT: cout << "STARTING_COMMENT";
            break;
        case IN_COMMENT: cout << "IN_COMMENT";
            break;
        case ENDING_COMMENT: cout << "ENDING_COMMENT";
            break;
        case ONE_LINE_COMMENT: cout << "ONE_LINE_COMMENT";
            break;
        case ERROR: cout << "ERROR";
            break;
        case EMPTY_LINE: break;
        default: cout << "UNKNOWN";
            break;
    }
    cout << endl;
}

int xml_data::get_attribute( string line, xml_node* temp_node ) {

    unsigned int left_pos, right_pos, next_pos, closing_tag_pos;

    //for attribute, find the first space.
    next_pos = line.find(' ');
    closing_tag_pos = line.find('>');

    //if no ' ' exists or is found after '>', then there are no more attributes.
    // If '/' is immediately after next_pos, then you have reached the end of
    //      a self-closing tag.
    while ( next_pos != string::npos &&
            next_pos < closing_tag_pos &&
            line[next_pos + 1] != '/' ) {
        string attr_name, attr_value;

        left_pos = next_pos;
        right_pos = line.find('=', left_pos);

        //  if no '=' is found, there is an error.
        if ( left_pos == string::npos || left_pos > closing_tag_pos ) {
            cout << "No '=' found for attribute." << endl;
            return EXIT_FAILURE;
        }

        attr_name = line.substr(left_pos + 1, ( right_pos - ( left_pos + 1 ) ));

        left_pos = right_pos + 1;
        right_pos = line.find('\"', left_pos + 1);

        //  if the first '\"' does not exist after the '=', or if the second '\"'
        // does not exist before the next ' ' or '>', return an error.
        if ( line[left_pos] != '\"' || right_pos > closing_tag_pos || right_pos == string::npos ) {
            cout << "Attribute value could not be found. EXITING PROGRAM" << endl;
            return EXIT_FAILURE;
        }

        attr_value = line.substr(left_pos + 1, ( right_pos - ( left_pos + 1 ) ));

        //Push the attribute contents onto its parent elements.
        if ( temp_node->push_attr(attr_name, attr_value) == EXIT_FAILURE ) {
            return EXIT_FAILURE;
        }

        next_pos = line.find(' ', right_pos);
    }

    return EXIT_SUCCESS;
}

int xml_data::insert_tree( string line, string name, int line_number ) {

    //This line of code is placed here for debugging purposes
    //cout << "Stack size = " << stack_elem.size() << endl;

    if ( cur_pos != NULL ) {
        for ( unsigned int i = 0; cur_pos->getLevel() > ( stack_elem.size() - i ); ++i ) {
            cur_pos = cur_pos->getParent();
        }
    }

    xml_node* temp_node = new xml_node(name, line_number, cur_pos);

    if ( temp_node == NULL ) {
        return EXIT_FAILURE;
    }

    if ( get_attribute(line, temp_node) == EXIT_FAILURE ) {
        cout << "An Error Occurred while searching for attributes. EXITING PROGRAM"
                << endl;
        return EXIT_FAILURE;
    }

    //If inserting a root element, the parent is set as itself.
    if ( this->tree_elem.front() == NULL ) {
        this->tree_elem.back() = temp_node;
        this->tree_elem.push_back(NULL);
        this->tree_elem.front()->setLevel(0);
        temp_node->setParent(temp_node);
        this->cur_pos = temp_node;
    }
        //Else, Set the parent as the current position in the new node. then
        // set cur_pos as the position of the new node.
    else {
        temp_node->setParent(cur_pos);
        temp_node->setLevel(( this->stack_elem.size() - 2 ));
        this->cur_pos->push_child(temp_node);
        this->cur_pos = temp_node;
    }

    return EXIT_SUCCESS;
}

xml_node* xml_data::Parent_tree( ) {
    return this->cur_pos->getParent();
}

void xml_data::print_tree_data( ) {

    if ( this->tree_elem.front() != NULL ) {
        this->tree_elem.front()->toString();
    }
    else {
        cout << "No elements detected." << endl;
    }
}

int xml_data::XMLtoJSON( string file_name ) {

    ofstream JSON_file;

    if ( this->tree_elem.front() != NULL ) {
        JSON_file.open(file_name);

        if ( !( JSON_file.is_open() ) ) {
            return EXIT_FAILURE;
        }

        this->tree_elem.front()->toJSON( &JSON_file );

        JSON_file.close();
    }
    else {
        cout << "No elements detected." << endl;
    }

    return EXIT_SUCCESS;
}