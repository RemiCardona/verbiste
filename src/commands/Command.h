/*  $Id: Command.h,v 1.25 2017/08/29 01:47:43 sarrazip Exp $
    Command.h - Abstract command-line driver

    verbiste - French conjugation system
    Copyright (C) 2003-2010 Pierre Sarrazin <http://sarrazip.com/>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef _H_verbiste_Command
#define _H_verbiste_Command

#if !defined(LIBDATADIR)
#error "LIBDATADIR not defined"
#endif

#include <verbiste/FrenchVerbDictionary.h>

#include <string>
#include <stdlib.h>
#include <errno.h>


namespace verbiste {


/** Abstract class representing a command-line tool.

    A program based on this class will read words either from the command
    line (each argument is a word) or from the standard input (each line is
    a word).  The results are written to the standard output.  The Latin-1
    (ISO-8859-1) character set is assumed.
*/
class Command
{
public:

    /** Initializes the command object and the Verbiste dictionary.
        @param  conjugationFilename filename of the XML document that
                                    defines all the conjugation templates
        @param  verbsFilename       filename of the XML document that
                                    defines all the known verbs and their
                                    corresponding template
        @param  lang                language of the dictionary
        @throws std::logic_error    error message related to a failure to
                                    construct the FrenchVerbDictionary
                                    object
    */
    Command(const std::string &conjugationFilename,
            const std::string &verbsFilename,
            FrenchVerbDictionary::Language lang);

    /** Destroys the Verbiste dictionary object.
    */
    virtual ~Command();

    /** Use the given arguments as verbs, or stdin if no arguments are given.
        If arguments are given, argv[0] must be the first argument, and not
        the name of the current program.
        They are converted to lower-case and passed to the processInputWord()
        method, which must be overridden by a class derived from this one.
    */
    int run(int argc, char *argv[]);

    /** Returns a reference to the Verbiste dictionary object.
        @throws        std::logic_error error message indicating that
                                        the constructor failed to create
                                        the dictionary object
    */
    const FrenchVerbDictionary &getFrenchVerbDictionary() const;

    /** Returns a reference to the Verbiste dictionary object.
        @throws        std::logic_error error message indicating that
                                        the constructor failed to create
                                        the dictionary object
    */
    FrenchVerbDictionary &getFrenchVerbDictionary();

    /** Prints the name of every known verb to the designated text stream.
        Each printed infinitive is separated by a newline sequence.
        @returns EXIT_SUCCESS or EXIT_FAILURE
        @throws        std::logic_error error message indicating that
                                        the constructor failed to create
                                        the dictionary object
    */
    int listAllInfinitives(std::ostream &out) const;

    /** Returns the value of the named environment variable.
        @param      name                non-empty name of the variable
        @param      defaultValue        optional default value to return
                                        if the named variable is not defined
                                        (if null, an empty string is returned)
        @returns                        the value of the named variable if
                                        it is defined, or defaultValue otherwise
                                        if defaultValue is not null (if it is null,
                                        an empty string is returned)
    */
    static std::string getEnv(const char *name, const char *defaultValue = NULL);

protected:

    /** Process a word received from the user.
        @param        inputWord        a Latin-1 string containing the word to process
    */
    virtual void processInputWord(const std::string &inputWord) = 0;


    /** Instance of the Verbiste dictionary to use to process the words.
    */
    FrenchVerbDictionary *fvd;


    /** Indicates current language.
    */
    FrenchVerbDictionary::Language lang;


    // Forbidden operations:
    Command(const Command &);
    Command &operator = (const Command &);

};


}  // namespace verbiste


#endif  /* _H_verbiste_Command */
