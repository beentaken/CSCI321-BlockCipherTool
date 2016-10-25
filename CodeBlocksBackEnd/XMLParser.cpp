/**
 * Author: Christopher Mellon of CryptoScythe
 * Filename: XMLParser.cpp
 *
 * Parses the custom XML file created from the Front End
 */
#include <iostream>     /**< cout, cin */
#include <fstream>      /**< file input and output stream */
#include <string>       /**< strings */
#include <sstream>      /**< stringstreams */
#include <algorithm>    /**< remove */
#include <vector>       /**< vector, vector iterators */

#include "XMLParser.h"  /**< xml header file */

using namespace std;    /**< standard namespace */

/** \brief
 * ReadXML reads in a file and extracts the XML data line by line til the end of the cipher/file
 *
 * \param
 * filename is the name of the file to be read that has the XML data
 *
 * \param
 * Props is the properties node which is passed by reference
 *
 * \param
 * decrypt is the vector of decryption nodes which is passed by reference
 *
 * \param
 * keygen is the vector of key generation nodes which are passed by reference
 *
 * \return
 * Returns all the encryption nodes gathered in a vector
 */
vector<Node> ReadXML(string filename, Properties& Props, vector<Node>& decrypt, vector<Node>& keygen) {
    vector<Node> encrypt;

    /**< File input stream for the xml */
    ifstream XMLfile;
    XMLfile.open(filename.c_str());

    /**< Checks that the file exists */
    if (XMLfile.good()) {
        /**< Checks that the file is open */
        if (XMLfile.is_open()) {
            /**< Continues to cycle through til end of file */
            while (!XMLfile.eof()) {
                /**< Gets the first line from the file */
                string line;
                getline(XMLfile, line);
                /**< Removes any spaces or tabbing */
                line.erase(remove(line.begin(), line.end(), ' '), line.end());
                line.erase(remove(line.begin(), line.end(), '\t'), line.end());

                /**< Checks that it is reading an encryption or decryption block in the xml */
                if ((line.compare("<encrypt>") == 0) || (line.compare("<decrypt>") == 0)) {
                    /**< Encrypt block */
                    if (line.compare("<encrypt>") == 0) {
                        /**< Parses all encrypt nodes */
                        encrypt = Cycle(XMLfile);
                    } else if (line.compare("<decrypt>") == 0) {
                        /**< Decrypt block */
                        /**< Parses all decrypt nodes */
                        decrypt = Cycle(XMLfile);
                    }
                } else if (line.compare("<keygen>") == 0) {
                    /**< Checks that it is the key generation block */
                    /**< Parses all key generation nodes */
                    keygen = Cycle(XMLfile);
                } else if (line.find("<propertiesWrapper>") != string::npos) {
                    /**< Parses a properties block if the properties tag is found */
                    Props = ParseProps(XMLfile, line);
                }
            }
            /**< Closes the file stream */
            XMLfile.close();
        }
    }

    /**< Returns the encryption vector */
    return encrypt;
}

/** \brief
 * Cycle goes through the xmlfile and continuously parses different kinds of xml blocks into the vector
 *
 * \param
 * XMLfile is the file input stream for the xml file
 *
 * \param
 * KeyCount is the number of keys counted from the parsed in Key Generation block in the xml file
 *
 * \return
 * Returns a vector full of parsed nodes
 *
 */

vector<Node> Cycle(ifstream& XMLfile) {
    vector<Node> result;
    Node temp;
    string line;
    /**< Will continue to cycle until the end of the cipher in the xml */
    while ((line.compare("</encrypt>") != 0) && (line.compare("</decrypt>") != 0) && (line.compare("</keygen>") != 0)) {
        /**< Gets a line from the file and removes the spacing and tabbing */
        getline(XMLfile, line);
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        if (line.find("<pboxs") != string::npos) {
            /**< Parses a PBox if the pbox tag is found */
            temp = ParseSPBox(XMLfile, line, 0);
            result.push_back(temp);
        } else if (line.find("<sboxs") != string::npos) {
            /**< Parses a SBox if the sbox tag is found */
            temp = ParseSPBox(XMLfile, line, 1);
            result.push_back(temp);
        } else if (line.find("<xors") != string::npos) {
            /**< Parses an XOR is the xor tag is found */
            temp = ParseXOR(XMLfile, line, 2);
            result.push_back(temp);
        } else if (line.find("<functions") != string::npos) {
            /**< Parses an F function if the f tag is found */
            temp = ParseFFunc(XMLfile, line, 3);
            result.push_back(temp);
        } else if (line.find("<keys") != string::npos) {
            /**< Parses the subkey identity */
            temp = ParseSubkey(XMLfile, line, 4);
            result.push_back(temp);
        }
    }

    /**< Returns the vector of nodes */
    return result;
}

/** \brief
 * ParseSubkey parses in a subkey from the key generation block
 *
 * \param
 * XMLfile is the input file stream of the xml file
 *
 * \param
 * line is the line of input from the input stream
 *
 * \param
 * type is the type of node being parsed from the xml file
 *
 * \param
 * KeyCount is the number of keys counted
 *
 * \return
 * Returns a node back to the vector
 *
 */

Node ParseSubkey(ifstream& XMLfile, string line, int type) {
    Node N;
    /**< Attempts to find the subkey number */
    if (line.find("ID") != string::npos) {
        /**< Sets the Node defaults */
        N.type = type;
        N.ID = StringToNumber(line);
        N.inputs = NULL;
        N.outputs = NULL;
        N.NumInputs = 1;
        N.NumOutputs = (-1);
        N.rows = (-1);

        /**< Continues to cycle until the end of the subkey block */
        while (line.compare("</keys>") != 0) {
            /**< Gets a line input and removes the spacing */
            getline(XMLfile, line);
            line.erase(remove(line.begin(), line.end(), '\t'), line.end());
            line.erase(remove(line.begin(), line.end(), ' '), line.end());

            /**< Finds an input block */
            if (line.find("<input") != string::npos) {
                /**< Initializes the block */
                InOuts * inputs = new InOuts[1];

                /**< Stores the input into the input node */
                int p = line.find_last_of("=");

                string s = line.substr(p);
                string s2 = line.substr(0, p);

                /**< Stores the Connection ID and the size */
                inputs[0].InputConID = StringToNumber(s2);
                inputs[0].InputSizes = StringToNumber(s);
                N.inputs = inputs;
            }
        }
    }

    /**< Returns the node */
    return N;
}

/** \brief
 * ParseProps parses the properties block from the xml file into the properties node
 *
 * \param
 * XMLfile is the input file stream from the xml file
 *
 * \param
 * line is the line of input from the xml file
 *
 * \return
 * It returns a properties block with the parsed information
 *
 */

Properties ParseProps(ifstream& XMLfile, string line) {
    Properties Props;

    /**< Continues to cycle through until the properties block is completely parsed in */
    while (line.compare("</propertiesWrapper>") != 0) {
        /**< Gets a line of input and removes all spacing */
        getline(XMLfile, line);
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());

        /**< If its the startID assign an integer to the Properties node */
        if (line.find("startID") != string::npos) {
            Props.StartID = StringToNumber(line);
            /**< If its the endID assign an integer to the Properties node */
        } else if (line.find("endID") != string::npos) {
            Props.EndID = StringToNumber(line);
            /**< If it is the number of rounds, assign an integer to the Properties node */
        } else if (line.find("numberOfRounds") != string::npos) {
            Props.NumRounds = StringToNumber(line);
            /**< If it is the block size, assign an integer to the Properties node */
        } else if (line.find("blockSize") != string::npos) {
            Props.BlockSize = StringToNumber(line);
            /**< If it is the key size, assign an integer to the Properties node */
        } else if (line.find("keySize") != string::npos) {
            Props.KeySize = StringToNumber(line);
        }
    }

    /**< Return the properties node */
    return Props;
}

/** \brief
 * ParseFFunc reads in the xml data from a file and stores the data in a node
 *
 * \param
 * XMLfile is the file stream that is being read from
 *
 * \param
 * line is the input read from the file stream
 *
 * \param
 * type is the the type of node that is being read in
 *
 * \param
 * KeyCount is the number of keys generated
 *
 * \return
 * Returns a node with the xml
 *
 */
Node ParseFFunc(ifstream& XMLfile, string line, int type) {
    Node N;
    /**< Attempts to find the ID */
    if (line.find("ID") != string::npos) {
        /**< Sets the Node defaults */
        N.type = type;
        N.ID = StringToNumber(line);
        N.inputs = NULL;
        N.outputs = NULL;
        N.NumInputs = (-1);
        N.NumOutputs = (-1);
        N.rows = (-1);

        /**< Continues to cycle until the end of the F function */
        while(line.compare("</functions>") != 0) {
            /**< Gets a line input and removes the spacing */
            getline(XMLfile, line);
            line.erase(remove(line.begin(), line.end(), '\t'), line.end());
            line.erase(remove(line.begin(), line.end(), ' '), line.end());

            if (line.find("<pboxs") != string::npos) {
                /**< Parses in a p box and adds it to the end of the vector */
                Node temp = ParseSPBox(XMLfile, line, 0);
                N.Next.push_back(temp);
            } else if (line.find("<sboxs") != string::npos) {
                /**< Parses in a s box and adds it to the end of the vector */
                Node temp = ParseSPBox(XMLfile, line, 1);
                N.Next.push_back(temp);
            } else if (line.find("<xors") != string::npos) {
                /**< Parses in an xor and adds it to the end of the vector */
                Node temp = ParseXOR(XMLfile, line, 2);
                N.Next.push_back(temp);
            } else if (line.find("<functions") != string::npos) {
                /**< Parses in an f function and adds it to the end of the vector */
                Node temp = ParseFFunc(XMLfile, line, 3);
                N.Next.push_back(temp);
            } else if (line.find("<keys") != string::npos) {
                /**< Parses the subkey and adds it to the end of the vector */
                Node temp = ParseSubkey(XMLfile, line, 4);
                N.Next.push_back(temp);
            }
        }
    }
    /**< Returns the node to be added to the vector */
    return N;
}

/** \brief
 * ParseXOR reads in an xor block from the xmlfile into the node
 *
 * \param
 * XMLfile is the filestream that reads in the xml file
 *
 * \param
 * line is the input from the filestream
 *
 * \param
 * type is the type of node being read in
 *
 * \return
 * Returns a node with the xml
 *
 */
Node ParseXOR(ifstream& XMLfile, string line, int type) {
    Node N;
    /**< Checks for an ID */
    if (line.find("ID") != string::npos) {
        /**< Sets the defaults for the Node */
        N.type = type;
        N.ID = StringToNumber(line);
        N.inputs = NULL;
        N.outputs = NULL;
        N.NumInputs = (-1);
        N.NumOutputs = (-1);
        N.rows = (-1);

        /**< Continues to cycle until the end of the xor block */
        while (line.compare("</xors>") != 0) {
            /**< Gets a line of input and erases the spacing */
            getline(XMLfile, line);
            line.erase(remove(line.begin(), line.end(), '\t'), line.end());
            line.erase(remove(line.begin(), line.end(), ' '), line.end());

            if (line.find("<inputs") != string::npos) {
                /**< Gets the number of inputs for the xor block */
                N.NumInputs = StringToNumber(line);

                /**< Creates a new inputs node */
                InOuts * inputs = new InOuts[N.NumInputs];
                int inscounter = 0;
                /**< Cycles until the end of the inputs block */
                while (line.compare("</inputs>") != 0) {
                    /**< Gets input and removes the spacing */
                    getline(XMLfile, line);
                    line.erase(remove(line.begin(), line.end(), '\t'), line.end());
                    line.erase(remove(line.begin(), line.end(), ' '), line.end());

                    if (line.find("<input") != string::npos) {
                        /**< Stores the input into the input node */
                        int p = line.find_last_of("=");

                        /**< Splits the string into sizes and connectionIDs */
                        string s = line.substr(p);
                        string s2 = line.substr(0, p);

                        /**< Stores the Connection ID the size and the values */
                        if (s2.find("k") != string::npos) {
                            int key = StringToNumber(s2);
                            inputs[inscounter].InputConID = (0 - key);
                        } else {
                            inputs[inscounter].InputConID = StringToNumber(s2);
                        }
                        inputs[inscounter].InputSizes = StringToNumber(s);
                        inscounter++;
                    }
                }

                /**< Stores the inputs into the node */
                N.inputs = inputs;
            } else if (line.find("<outputs") != string::npos) {
                /**< Gets the number of outputs */
                N.NumOutputs = StringToNumber(line);

                /**< Initilizes the size of the outputs */
                InOuts * outputs = new InOuts[N.NumOutputs];
                int outscounter = 0;

                /**< Cycles through the entire outputs block */
                while (line.compare("</outputs>") != 0) {
                    /**< Gets input and removes the spacing */
                    getline(XMLfile, line);
                    line.erase(remove(line.begin(), line.end(), '\t'), line.end());
                    line.erase(remove(line.begin(), line.end(), ' '), line.end());

                    if (line.find("<output") != string::npos) {
                        /**< Stores the output into the output node */
                        int p = line.find_last_of("=");

                        /**< Splits the string for easy reading */
                        string s = line.substr(p);
                        string s2 = line.substr(0, p);

                        /**< Stores the Connection ID the size and the values */
                        if (s2.find("k") != string::npos) {
                            int key = StringToNumber(s2);
                            outputs[outscounter].InputConID = (0 - key);
                        } else {
                            outputs[outscounter].InputConID = StringToNumber(s2);
                        }
                        outputs[outscounter].InputSizes = StringToNumber(s);
                        outscounter++;
                    }
                }
                /**< Stores the outputs into the node */
                N.outputs = outputs;
            }
        }
    }
    /**< Returns a node with the xor information */
    return N;
}

/** \brief
 * Parses an S Box or P Box from the xml file to the node
 *
 * \param
 * line is the input from the file stream
 *
 * \param
 * type is the type of xml block being read from the file
 *
 * \return
 * Returns a node containing the xml block
 *
 */

Node ParseSPBox(ifstream& XMLfile, string line, int type) {
    Node N;
    /**< Finds the ID of the S or P Box */
    if (line.find_first_of("ID") != string::npos) {
        /**< Sets the node defaults */
        N.type = type;
        N.ID = StringToNumber(line);
        N.inputs = NULL;
        N.outputs = NULL;
        N.NumInputs = (-1);
        N.NumOutputs = (-1);
        N.rows = (-1);

        /**< Cycles until the end of the box */
        while ((line.compare("</pboxs>") != 0) && (line.compare("</sboxs>") != 0)) {
            /**< Gets a line from the xml file and removes the spacing */
            getline(XMLfile, line);
            line.erase(remove(line.begin(), line.end(), ' '), line.end());
            line.erase(remove(line.begin(), line.end(), '\t'), line.end());

            if (line.find("<inputs") != string::npos) {
                /**< Stores the number of inputs */
                N.NumInputs = StringToNumber(line);

                /**< Creates a node for the inputs */
                InOuts * inputs = new InOuts[N.NumInputs];
                int inputspos = 0;
                while (line.compare("</inputs>") != 0) {
                    /**< Gets a line of input and removes the spacing */
                    getline(XMLfile, line);
                    line.erase(remove(line.begin(), line.end(), '\t'), line.end());
                    line.erase(remove(line.begin(), line.end(), ' '), line.end());
                    if (line.find("<input") != string::npos) {
                        /**< Splits the string into the connection id and size */
                        int p = line.find_last_of("=");

                        string s = line.substr(p);
                        string s2 = line.substr(0, p);

                        /**< Stores the connection id and size of the input */
                        if (s2.find("k") != string::npos) {
                            int key = StringToNumber(s2);
                            inputs[inputspos].InputConID = (0 - key);
                        } else {
                            inputs[inputspos].InputConID = StringToNumber(s2);
                        }
                        inputs[inputspos].InputSizes = StringToNumber(s);
                        inputspos++;
                    }
                }

                /**< Stores the Node inputs */
                N.inputs = inputs;
            } else if (line.find("<outputs") != string::npos) {
                /**< Stores the number of outputs */
                N.NumOutputs = StringToNumber(line);

                /**< Creates an output node */
                InOuts * outputs = new InOuts[N.NumOutputs];
                int outputspos = 0;
                while (line.compare("</outputs>") != 0) {
                    /**< Gets the next line in the file and removes the spacing */
                    getline(XMLfile, line);
                    line.erase(remove(line.begin(), line.end(), '\t'), line.end());
                    line.erase(remove(line.begin(), line.end(), ' '), line.end());

                    if (line.find("<output") != string::npos) {
                        /**< Stores an output node */
                        int p = line.find_last_of("=");

                        if (line.find("</output>") == string::npos) {
                            /**< Splits the string and stores the connection id and size */
                            string s = line.substr(p);
                            string s2 = line.substr(0, p);

                            outputs[outputspos].InputConID = StringToNumber(s2);
                            outputs[outputspos].InputSizes = StringToNumber(s);
                            outputs[outputspos].positions = new int[1];
                            outputs[outputspos].positions[0] = (-1);
                            outputspos++;
                        } else {
                            /**< Splits the string and stores the connection id and size */
                            string s = line.substr(p);
                            string s2 = line.substr(0, p);
                            p = s.find_first_of(">");
                            string s3 = s.substr(p);
                            s = s.substr(0, p);

                            /**< Stores the Connection ID the size and the values */
                            if (s2.find("k") != string::npos) {
                                int key = StringToNumber(s2);
                                outputs[outputspos].InputConID = (0 - key);
                            } else {
                                outputs[outputspos].InputConID = StringToNumber(s2);
                            }
                            outputs[outputspos].InputSizes = StringToNumber(s);
                            outputs[outputspos].positions = StringToIntArr(s3, ',');
                            outputspos++;
                        }
                    }
                }
                /**< Stores the node output */
                N.outputs = outputs;
            } else if (line.find("<table") != string::npos) {
                int found = line.find_last_of("=");

                /**< Splits the string to store the rows and columns */
                string s = line.substr(found);
                string s2 = line.substr(0, found);

                /**< Rows and columns are stored and converted from string to int */
                N.rows = StringToNumber(s);
                N.cols = StringToNumber(s2);

                /**< Initilizes table rows */
                N.table = new int*[N.rows];
                int counter = 0;

                /**< Cycles through til end of table block */
                while (line.compare("</table>") != 0) {
                    /**< Gets a line and removes the spacing */
                    getline(XMLfile, line);
                    line.erase(remove(line.begin(), line.end(), '\t'), line.end());
                    line.erase(remove(line.begin(), line.end(), ' '), line.end());

                    /**< Every time it finds a row */
                    if (line.find("<rows") != string::npos) {
                        /**< Store the column values into the appropriate row on the table */
                        int * temp = StringToIntArr(line, ',');
                        N.table[counter] = new int[N.cols];
                        for (int i = 0; i < N.cols; i++) {
                            N.table[counter][i] = temp[i+1];
                        }
                        delete [] temp;
                        counter++;
                    }
                }
            }
        }
    }

    /**< Returns the node */
    return N;
}

/** \brief
 * StringToNumber transforms the string into an integer
 *
 * \param
 * input is the string to be transformed
 *
 * \return
 * returns an integer of the string
 *
 */

int StringToNumber(string input) {
    stringstream convert;
    int result = (-1);

    /**< Removes any non digit characters and converts it into a string */
    int len = input.length();
    for (int i = 0; i < len; i++) {
        if (!isdigit(input[i])) {
            input[i] = ' ';
        }
    }

    /**< Removes the spacing */
    input.erase(remove(input.begin(), input.end(), ' '), input.end());

    /**< Checks an integer is present */
    bool emptycheck = false;
    for (size_t i = 0; i < input.length() && emptycheck == false; i++) {
        if (isspace(input[i])) {
            emptycheck = true;
        }
    }

    /**< Converts the string to an int */
    if (emptycheck == false) {
        convert << input;
        convert >> result;
    }

    /**< Returns an int */
    return result;
}

/** \brief
 * StringToIntArr transforms a string into an array of integers
 *
 * \param
 * input is the string to be transformed
 *
 * \param
 * delimeter is the separator between integers
 *
 * \return
 * An array of integers
 *
 */

int* StringToIntArr(string input, char delimeter) {
    stringstream convert;
    string temp;
    int* result;
    int* res;
    int realcount = 0;
    int counter = 1;
    convert << input;
    /**< Checks how many delimeters are present */
    for (size_t i = 0; i < input.length(); i++) {
        if (input[i] == delimeter) {
            counter++;
        }
    }

    /**< Creates the integer array */
    res = new int[counter];

    /**< Reads in the integers */
    for (int i = 0; i < counter; i++) {
        /**< Tokenizes the string and stores the integer */
        getline(convert, temp, delimeter);
        res[i] = StringToNumber(temp);

        /**< Increases the real amount of integer count */
        if (res[i] != (-1)) {
            realcount++;
        }
    }

    /**< Creates an integer array */
    result = new int[realcount+1];
    result[0] = realcount;
    int realcounter = 1;
    for (int i = 0; i < counter; i++) {
        /**< Stores the integers accordingly */
        if (res[i] != (-1)) {
            result[realcounter] = res[i];
            realcounter++;
        }
    }

    /**< Deletes the dynamic array */
    delete [] res;

    /**< Returns the integer array */
    return result;
}
