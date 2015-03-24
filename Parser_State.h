/* 
 * File:   Parser_State.h
 * Author: Arthur Lisek-Koper
 * e-mail: arthur_lisekkoper@student.uml.edu
 * 
 * Created on October 1, 2014, 5:03 PM
 * Last Modified on October 2, 2014
 * 
 * Summary of Code: enum of the various parsing states used by xml_data.cpp.
 * 
 */

#ifndef PARSER_STATE_H
#define	PARSER_STATE_H

    // Enum of the various parser states while processing an xml document.
    //  Original code taken from Jesse Heines' class notes. Edited by 
    //  Arthur Lisek-Koper.
    enum ParserState {
        UNKNOWN, 
        STARTING_DOCUMENT, 
        DIRECTIVE,
        ELEMENT_OPENING_TAG, 
        ELEMENT_CONTENT, 
        ELEMENT_NAME_AND_CONTENT,
        ELEMENT_CLOSING_TAG, 
        SELF_CLOSING_TAG,
        STARTING_COMMENT, 
        IN_COMMENT, 
        ENDING_COMMENT, 
        ONE_LINE_COMMENT,
        ERROR,
        EMPTY_LINE
    };

#endif	/* PARSER_STATE_H */

