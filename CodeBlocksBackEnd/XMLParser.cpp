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

                /**< Checks that it is reading a cipher in the xml */
                if ((line.compare("<encrypt>") == 0) || (line.compare("<decrypt>") == 0)) {
                    int KeyCount = 0;
                    if (line.compare("<encrypt>") == 0) {
                        encrypt = Cycle(XMLfile, KeyCount);
                    } else if (line.compare("<decrypt>") == 0) {
                        decrypt = Cycle(XMLfile, KeyCount);
                    }
                    Props.NumKey = KeyCount;
                } else if (line.compare("<keygen>") == 0) {
                    int KeyCount = 0;
                    keygen = Cycle(XMLfile, KeyCount);
                } else if (line.find("<properties") != string::npos) {
                    /**< Parses a properties block if the properties tag is found */
                    Props = ParseProps(XMLfile, line);
                }
            }

            /**< Closes the file stream */
            XMLfile.close();
        }
    }

    return encrypt;
}

vector<Node> Cycle(ifstream& XMLfile, int& KeyCount) {
    vector<Node> result;
    Node temp;
    string line;
        /**< Will continue to cycle until the end of the cipher in the xml */
    while ((line.compare("</encrypt>") != 0) && (line.compare("</decrypt>") != 0) && (line.compare("</keygen>") != 0)) {
        /**< Gets a line from the file and removes the spacing and tabbing */
        getline(XMLfile, line);
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), '\t'), line.end());
        if (line.find("<pbox") != string::npos) {
            /**< Parses a PBox if the pbox tag is found */
            temp = ParseSPBox(XMLfile, line, 0, KeyCount);
            result.push_back(temp);
        } else if (line.find("<sbox") != string::npos) {
            /**< Parses a SBox if the sbox tag is found */
            temp = ParseSPBox(XMLfile, line, 1, KeyCount);
            result.push_back(temp);
        } else if (line.find("<xor") != string::npos) {
            /**< Parses an XOR is the xor tag is found */
            temp = ParseXOR(XMLfile, line, 2, KeyCount);
            result.push_back(temp);
        } else if (line.find("<function") != string::npos) {
            /**< Parses an F function if the f tag is found */
            temp = ParseFFunc(XMLfile, line, 3, KeyCount);
            result.push_back(temp);
        } else if (line.find("<subkey") != string::npos) {
            /**< Parses the subkey identity */
            temp = ParseSubkey(XMLfile, line, 4);
            result.push_back(temp);
        }
    }

    return result;
}

Node ParseSubkey(ifstream& XMLfile, string line, int type) {
    Node N;
    /**< Attempts to find the ID */
    if (line.find("NUM") != string::npos) {
        /**< Sets the Node defaults */
        N.type = type;
        N.ID = StringToNumber(line);
        N.inputs = NULL;
        N.outputs = NULL;
        N.NumInputs = (-1);
        N.NumOutputs = (-1);
        N.rows = (-1);

        while (line.compare("</subkey>") != 0) {
            /**< Gets a line input and removes the spacing */
            getline(XMLfile, line);
            line.erase(remove(line.begin(), line.end(), '\t'), line.end());
            line.erase(remove(line.begin(), line.end(), ' '), line.end());

            if (line.find("<input") != string::npos) {
                InOuts * inputs = new InOuts[1];

                /**< Stores the input into the input node */
                int p = line.find_last_of("=");

                string s = line.substr(p);
                string s2 = line.substr(0, p);

                /**< Stores the Connection ID the size and the values */
                inputs[0].InputConID = StringToNumber(s2);
                inputs[0].InputSizes = StringToNumber(s);
                N.inputs = inputs;
            }
        }
    }

    return N;
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
Node ParseFFunc(ifstream& XMLfile, string line, int type, int& KeyCount) {
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
        while(line.compare("</function>") != 0) {
            /**< Gets a line input and removes the spacing */
            getline(XMLfile, line);
            line.erase(remove(line.begin(), line.end(), '\t'), line.end());
            line.erase(remove(line.begin(), line.end(), ' '), line.end());

            if (line.find("<pbox") != string::npos) {
                /**< Parses in a p box and adds it to the end of the linked list */
                Node temp = ParseSPBox(XMLfile, line, 0, KeyCount);
                N.Next.push_back(temp);
            } else if (line.find("<sbox") != string::npos) {
                /**< Parses in a s box and adds it to the end of the linked list */
                Node temp = ParseSPBox(XMLfile, line, 1, KeyCount);
                N.Next.push_back(temp);
            } else if (line.find("<xor") != string::npos) {
                /**< Parses in an xor and adds it to the end of the linked list */
                Node temp = ParseXOR(XMLfile, line, 2, KeyCount);
                N.Next.push_back(temp);
            } else if (line.find("<f") != string::npos) {
                /**< Parses in an f function and adds it to the end of the linked list */
                Node temp = ParseFFunc(XMLfile, line, 3, KeyCount);
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
Node ParseXOR(ifstream& XMLfile, string line, int type, int& KeyCount) {
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
        N.rows = (-1);

        /**< Continues to cycle until the end of the xor block */
        while (line.compare("</xor>") != 0) {
            /**< Gets a line of input and erases the spacing */
            getline(XMLfile, line);
            line.erase(remove(line.begin(), line.end(), '\t'), line.end());
            line.erase(remove(line.begin(), line.end(), ' '), line.end());

            if (line.find("<inputs") != string::npos) {
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
                        int p = line.find_last_of("=");

                        string s = line.substr(p);
                        string s2 = line.substr(0, p);

                        /**< Stores the Connection ID the size and the values */
                        if (s2.find("k") != string::npos) {
                            int key = StringToNumber(s2);
                            KeyCount++;
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
                N.NumOutputs = StringToNumber(line);

                InOuts * outputs = new InOuts[N.NumOutputs];
                int outscounter = 0;

                while (line.compare("</outputs>") != 0) {
                    /**< Gets input and removes the spacing */
                    getline(XMLfile, line);
                    line.erase(remove(line.begin(), line.end(), '\t'), line.end());
                    line.erase(remove(line.begin(), line.end(), ' '), line.end());

                    if (line.find("<output") != string::npos) {
                        /**< Stores the output into the output node */
                        int p = line.find_last_of("=");

                        string s = line.substr(p);
                        string s2 = line.substr(0, p);

                        /**< Stores the Connection ID the size and the values */
                        if (s2.find("k") != string::npos) {
                            int key = StringToNumber(s2);
                            KeyCount++;
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

Node ParseSPBox(ifstream& XMLfile, string line, int type, int& KeyCount) {
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
        while ((line.compare("</pbox>") != 0) && (line.compare("</sbox>") != 0)) {
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
                            KeyCount++;
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
                                KeyCount++;
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

                string s = line.substr(found);
                string s2 = line.substr(0, found);

                N.rows = StringToNumber(s);
                N.cols = StringToNumber(s2);

                N.table = new int*[N.rows];
                int counter = 0;
                while (line.compare("</table>") != 0) {
                    getline(XMLfile, line);
                    line.erase(remove(line.begin(), line.end(), '\t'), line.end());
                    line.erase(remove(line.begin(), line.end(), ' '), line.end());

                    if (line.find("<rows") != string::npos) {
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
