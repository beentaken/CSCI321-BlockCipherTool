#include <iostream>     /**< cout, cin */
#include <fstream>      /**< file input and output stream */
#include <string>       /**< strings */
#include <sstream>      /**< stringstreams */
#include <algorithm>    /**< remove */
#include <vector>

#include "XMLParser.h"  /**< Header file */

using namespace std;    /**< Namespace standard */

/** \brief
 * ReadXML reads in a file and extracts the XML data line by line til the end of the cipher/file
 *
 * \param
 * filename is the name of the file to be read that has the XML data
 *
 * \return
 * Returns all the data gathered in a vector
 */
vector<Node> ReadXML(string filename, Properties& Props) {
    vector<Node> result;

    /**< File input stream for the xml */
    ifstream XMLfile;
    XMLfile.open(filename.c_str());

    /**< Checks that the file exists */
    if (XMLfile.good()) {
        /**< Checks that the file is open */
        if (XMLfile.is_open()) {
            /**< Gets the first line from the file */
            string line;
            getline(XMLfile, line);
            /**< Removes any spaces or tabbing */
            line.erase(remove(line.begin(), line.end(), ' '), line.end());
            line.erase(remove(line.begin(), line.end(), '\t'), line.end());

            /**< Checks that it is reading a cipher in the xml */
            if (line.compare("<cipher>") == 0) {
                Node temp;
                /**< Will continue to cycle until the end of the cipher in the xml */
                while (line.compare("</cipher>") != 0) {
                    /**< Gets a line from the file and removes the spacing and tabbing */
                    getline(XMLfile, line);
                    line.erase(remove(line.begin(), line.end(), ' '), line.end());
                    line.erase(remove(line.begin(), line.end(), '\t'), line.end());

                    if (line.find("<pbox") != string::npos) {
                        /**< Parses a PBox if the pbox tag is found */
                        temp = ParseSPBox(XMLfile, line, 0);
                        result.push_back(temp);
                    } else if (line.find("<sbox") != string::npos) {
                        /**< Parses a SBox if the sbox tag is found */
                        temp = ParseSPBox(XMLfile, line, 1);
                        result.push_back(temp);
                    } else if (line.find("<xor") != string::npos) {
                        /**< Parses an XOR is the xor tag is found */
                        temp = ParseXOR(XMLfile, line, 2);
                        result.push_back(temp);
                    } else if (line.find("<f") != string::npos) {
                        /**< Parses an F function if the f tag is found */
                        temp = ParseFFunc(XMLfile, line, 3);
                        result.push_back(temp);
                    } else if (line.find("<connection") != string::npos) {
                        /**< Parses a connection is the connection tag is found */
                        temp = ParseConn(XMLfile, line, 4);
                        result.push_back(temp);
                    } else if (line.find("<properties") != string::npos) {
                        /**< Parses a properties block if the properties tag is found */
                        Props = ParseProps(XMLfile, line);
                    }
                }
            }

            /**< Closes the file stream */
            XMLfile.close();
        }
    }

    return result;
}

Properties ParseProps(ifstream& XMLfile, string line) {
    Properties Props;

    while (line.compare("</properties>") != 0) {
        getline(XMLfile, line);
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());

        if (line.find("startID") != string::npos) {
            Props.StartID = StringToNumber(line);
        } else if (line.find("endID") != string::npos) {
            Props.EndID = StringToNumber(line);
        } else if (line.find("numberOfRounds") != string::npos) {
            Props.NumRounds = StringToNumber(line);
        } else if (line.find("blockSize") != string::npos) {
            Props.BlockSize = StringToNumber(line);
        } else if (line.find("keySize") != string::npos) {
            Props.KeySize = StringToNumber(line);
        }
    }

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


        /**< Continues to cycle until the end of the F function */
        while(line.compare("</f>") != 0) {
            /**< Gets a line input and removes the spacing */
            getline(XMLfile, line);
            line.erase(remove(line.begin(), line.end(), '\t'), line.end());
            line.erase(remove(line.begin(), line.end(), ' '), line.end());

            if (line.find("<pbox") != string::npos) {
                /**< Parses in a p box and adds it to the end of the linked list */
                Node temp = ParseSPBox(XMLfile, line, 0);
                N.Next.push_back(temp);
            } else if (line.find("<sbox") != string::npos) {
                /**< Parses in a s box and adds it to the end of the linked list */
                Node temp = ParseSPBox(XMLfile, line, 1);
                N.Next.push_back(temp);
            } else if (line.find("<xor") != string::npos) {
                /**< Parses in an xor and adds it to the end of the linked list */
                Node temp = ParseXOR(XMLfile, line, 2);
                N.Next.push_back(temp);
            } else if (line.find("<f") != string::npos) {
                /**< Parses in an f function and adds it to the end of the linked list */
                Node temp = ParseFFunc(XMLfile, line, 3);
                N.Next.push_back(temp);
            } else if (line.find("<connection") != string::npos) {
                /**< Parses in a connection and adds it to the end of the linked list */
                Node temp = ParseConn(XMLfile, line, 4);
                N.Next.push_back(temp);
            }
        }
    }
    /**< Returns the node to be added to the vector */
    return N;
}

/** \brief
 * ParseConn parses in a connection and stores it from the xmlfile into the node
 *
 * \param
 * XMLfile is the file input stream
 *
 * \param
 * line is the input from the xmlfile stream
 *
 * \param
 * type is the type of node being read in
 *
 * \return
 * Returns a node with the xml info
 *
 */
Node ParseConn(ifstream& XMLfile, string line, int type) {
    Node N;

    /**< Checks for an ID for the connection */
    if (line.find("ID") != string::npos) {
        /**< Sets the defaults for the Node */
        N.type = type;
        N.ID = StringToNumber(line);
        N.inputs = NULL;
        N.outputs = NULL;
        N.NumInputs = (-1);
        N.NumOutputs = (-1);

        /**< Continues to cycle until it has read all of the connection node properties */
        while(line.compare("</connection>") != 0) {
            /**< Gets a line of input from the file stream and removes the spacing */
            getline(XMLfile, line);
            line.erase(remove(line.begin(), line.end(), '\t'), line.end());
            line.erase(remove(line.begin(), line.end(), ' '), line.end());

            if (line.find("<X1>") != string::npos) {
                /**< Stores the first X coordinate */
                getline(XMLfile, line);
                N.XPos = StringToNumber(line);
            } else if (line.find("<X2>") != string::npos) {
                /**< Stores the second X coordinate */
                getline(XMLfile, line);
                N.XPos2 = StringToNumber(line);
            } else if (line.find("<Y1>") != string::npos) {
                /**< Stores the first Y coordinate */
                getline(XMLfile, line);
                N.YPos = StringToNumber(line);
            } else if (line.find("<Y2>") != string::npos) {
                /**< Stores the second Y coordiante */
                getline(XMLfile, line);
                N.YPos2 = StringToNumber(line);
            } else if (line.find("<from>") != string::npos) {
                /**< Stores the from Node ID */
                getline(XMLfile, line);
                N.from = StringToNumber(line);
            } else if (line.find("<to>") != string::npos) {
                /**< Stores the to Node ID */
                getline(XMLfile, line);
                N.to = StringToNumber(line);
            }
        }
    }

    /**< Returns the Connection Node */
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
    /**< Checks for an ID and size  */
    if (line.find("ID") != string::npos) {
        /**< Sets the defaults for the Node */
        N.type = type;
        N.ID = StringToNumber(line);
        N.inputs = NULL;
        N.outputs = NULL;
        N.NumInputs = (-1);
        N.NumOutputs = (-1);

        /**< Continues to cycle until the end of the xor block */
        while (line.compare("</xor>") != 0) {
            /**< Gets a line of input and erases the spacing */
            getline(XMLfile, line);
            line.erase(remove(line.begin(), line.end(), '\t'), line.end());
            line.erase(remove(line.begin(), line.end(), ' '), line.end());

            if (line.compare("<X>") == 0) {
                /**< Gets an X value and stores it*/
                getline(XMLfile, line);
                N.XPos = StringToNumber(line);
            } else if (line.compare("<Y>") == 0) {
                /**< Gets an Y value and stores it*/
                getline(XMLfile, line);
                N.YPos = StringToNumber(line);
            } else if (line.find("<inputs") != string::npos) {
                /**< Gets the inputs for the xor block */
                N.NumInputs = StringToNumber(line);

                /**< Creates a new inputs node */
                InOuts * inputs = new InOuts[N.NumInputs];
                int inscounter = 0;
                while (line.compare("</inputs>") != 0) {
                    /**< Gets input and removes the spacing */
                    getline(XMLfile, line);
                    line.erase(remove(line.begin(), line.end(), '\t'), line.end());
                    line.erase(remove(line.begin(), line.end(), ' '), line.end());

                    if (line.find("<input") != string::npos) {
                        /**< Stores the input into the input node */
                        int p = line.find_last_of("size=");

                        string s = line.substr(p);
                        string s2 = line.substr(0, p);
                        p = s2.find_last_of("=");
                        s2 = s2.substr(p);

                        /**< Stores the Connection ID the size and the values */
                        inputs[inscounter].InputConID = StringToNumber(s2);
                        inputs[inscounter].InputSizes = StringToNumber(s);

                        getline(XMLfile, line);
                        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
                        line.erase(remove(line.begin(), line.end(), ' '), line.end());
                        int * tempin = new int[1];
                        tempin[0] = StringToNumber(line);
                        inputs[inscounter].values = tempin;
                        inscounter++;
                    }
                }

                /**< Stores the inputs into the node */
                N.inputs = inputs;
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

        /**< Cycles until the end of the box */
        while ((line.compare("</pbox>") != 0) && (line.compare("</sbox>"))) {
            /**< Gets a line from the xml file and removes the spacing */
            getline(XMLfile, line);
            line.erase(remove(line.begin(), line.end(), ' '), line.end());
            line.erase(remove(line.begin(), line.end(), '\t'), line.end());

            if (line.compare("<X>") == 0) {
                /**< Stores the X coordinate of the box */
                getline(XMLfile, line);
                N.XPos = StringToNumber(line);
            } else if (line.compare("<Y>") == 0) {
                /**< Stores the Y coordinate of the box */
                getline(XMLfile, line);
                N.YPos = StringToNumber(line);
            } else if (line.find("<inputs") != string::npos) {
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
                        int p = line.find_last_of("size=");

                        string s = line.substr(p);
                        string s2 = line.substr(0, p);

                        /**< Stores the connection id and size of the input */
                        inputs[inputspos].InputConID = StringToNumber(s2);
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
                        int p = line.find_last_of("size=");

                        /**< Splits the string and stores the connection id and size */
                        string s = line.substr(p);
                        string s2 = line.substr(0, p);

                        outputs[outputspos].InputConID = StringToNumber(s2);
                        outputs[outputspos].InputSizes = StringToNumber(s);
                    }

                    if (line.find(",") != string::npos) {
                        /**< Stores the values of the output */
                        outputs[outputspos].values = StringToIntArr(line, ',');
                    }

                    if (line.find("</output>") != string::npos) {
                        /**< Increments the output */
                        outputspos++;
                    }
                }
                /**< Stores the node output */
                N.outputs = outputs;
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

    /**< Removes any non digit characters */
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
