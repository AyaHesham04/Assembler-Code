#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;


bool is_integer(char s)
{
    return isdigit(s);
}

string hexToBinary(string& hexString) {

    string binaryString;

    for (char hexChar : hexString) {
        int hexValue;
        if (isdigit(hexChar)) {
            hexValue = hexChar - '0';
        }
        else {
            hexValue = toupper(hexChar) - 'A' + 10;
        }

        for (int i = 3; i >= 0; --i) {
            int bit = (hexValue >> i) & 1;
            binaryString += to_string(bit);
        }
    }

    return binaryString;
}

int main()
{
    string MemoryInstruction[7][3] = {
        {"AND", "0", "8"},
        {"ADD", "1", "9"},
        {"LDA", "2", "A"},
        {"STA", "3", "B"},
        {"BUN", "4", "C"},
        {"BSA", "5", "D"},
        {"ISZ", "6", "E"}
    };

    string RegisterInstruction[12][2] = {
       {"CLA", "7800"},
       {"CLE", "7400"},
       {"CMA", "7200"},
       {"CME", "7100"},
       {"CIR", "7080"},
       {"CIL", "7040"},
       {"INC", "7020"},
       {"SPA", "7010"},
       {"SNA", "7008"},
       {"SZA", "7004"},
       {"SZE", "7002"},
       {"HLT", "7001"}
    };

    string InOutInstruction[6][2] = {
        {"INP", "F800"},
        {"OUT", "F400"},
        {"SKI", "F200"},
        {"SKO", "F100"},
        {"ION", "F080"},
        {"IOF", "F040"}
    };

    string input, counter, sub;
    string lines[100]; // array of strings to store all lines in the file
    for (int i = 0; i < 100; i++)
    {
        lines[i].clear();
    }


    ifstream inputFile;
    int x = 0, check = 0, org = 0, j = 0, ct = 0, mempos = 0, g = 0, data = 0;
    int space, found = 0;
    string label, mode;

    inputFile.open("C:/Users/ASUS/OneDrive/Desktop/CO Project/input.txt");

    if (inputFile.is_open())
    {
        //cout << "File is Open" << endl;

        while (getline(inputFile, input))
        {
            if (x == 0)
            {
                if (input[0] == 'O' && input[1] == 'R' && input[2] == 'G') // looking for org
                {
                    org = 1; // ORG is found
                }

                if (org == 1)
                {
                    for (j = 4; j < input.length(); j++)
                    {
                        counter += input[j];
                    }

                    ct = stoi(counter);
                    ct--;

                }
                else
                {
                    ct = 100;
                }
            }

            lines[x] = input; // Store each line in the array

            x++;

        }

        cout << "Assembly code entered: " << endl;
        for (int i = 0; i < x; i++)
        {
            cout << lines[i] << endl;;
        }
        cout << endl;

        cout << "Equivalent hexadecimal code: " << endl;
        inputFile.close();
        x = ct + x;
        g = 0;
        for (int f = ct; f < x; f++, g++)
        {
            string line = lines[g];

            check = 0, data = 0;

            if (line.length() > 4)
            {
                if (is_integer(line[4]))
                {
                    space = 0;
                    for (j = 0; j < line.length(); j++)
                    {
                        if (line[j] == ' ')
                        {
                            space++; //count no.of spaces
                        }
                        if (space == 2)
                        {
                            break;
                        }
                    }
                    if (space == 2) //2 spaces means there is an I present
                    {
                        mode = line.substr(j + 1);
                        for (int i = 0; i < 7; i++)
                        {
                            if (MemoryInstruction[i][0] == line.substr(0, 3))
                            {
                                if (mode == "I")
                                {
                                    //cout << "Hex Code: " << MemoryInstruction[i][2] << line.substr(4, j - 4) << endl;

                                    cout << MemoryInstruction[i][2] << line.substr(4, j - 4) << endl;

                                    sub = line.substr(4, j - 4);

                                    //cout << "Binary Code: " << hexToBinary(MemoryInstruction[i][2])+ hexToBinary(sub) << endl << endl;
                                    check = 1;
                                    sub.clear();

                                    break;
                                }

                            }
                        }

                    }
                    else
                    {
                        mode = "";
                        for (int i = 0; i < 7; i++)
                        {
                            if (MemoryInstruction[i][0] == line.substr(0, 3))
                            {
                                if (mode == "")
                                {
                                    //cout << "Hex Code: " << MemoryInstruction[i][1] << line.substr(4) << endl;

                                    cout << MemoryInstruction[i][1] << line.substr(4) << endl;

                                    sub = line.substr(4);

                                    //cout << "Binary Code: " << hexToBinary(MemoryInstruction[i][1]) + hexToBinary(sub) << endl << endl;
                                    check = 1;
                                    sub.clear();

                                    break;
                                }
                            }
                        }

                    }


                }
                else
                {
                    space = 0;
                    for (j = 0; j < line.length(); j++)
                    {
                        if (line[j] == ' ')
                        {
                            space++;
                        }
                        if (space == 2)
                        {
                            break;
                        }
                    }
                    if (space == 2)
                    {
                        label = line.substr(4, j - 4);
                        mode = line.substr(j + 1);
                    }
                    else
                    {
                        label = line.substr(4);
                        mode = "";
                    }

                    if (label.length() == 3)
                    {

                        for (int i = 0; i < 7; i++)
                        {
                            if (MemoryInstruction[i][0] == line.substr(0, 3))
                            {
                                mempos = i;
                                check = 1;
                                break;
                            }

                        }
                        found = 0;
                        string temp;
                        string location;

                        for (int z = 0; z < x - ct; z++)
                        {
                            temp = lines[z];

                            if ((temp.substr(0, 3) == label) && temp[3] == ',')
                            {
                                found = 1;
                                if (ct + z > ct + 9)
                                {
                                    if (ct + z == ct + 10) { location = "10A"; }
                                    if (ct + z == ct + 11) { location = "10B"; }
                                    if (ct + z == ct + 12) { location = "10C"; }
                                    if (ct + z == ct + 13) { location = "10D"; }
                                    if (ct + z == ct + 14) { location = "10E"; }
                                    if (ct + z == ct + 15) { location = "10F"; }

                                    if (mode == "")
                                    {
                                        //cout << "Hex code: " << MemoryInstruction[mempos][1] << location << endl;
                                        cout << MemoryInstruction[mempos][1] << location << endl;

                                        //cout << "Binary Code: " << hexToBinary(MemoryInstruction[mempos][1]) << hexToBinary(location) << endl << endl;

                                    }
                                    else
                                    {
                                        //cout << "Hex code: " << MemoryInstruction[mempos][2] << location << endl;
                                        cout << MemoryInstruction[mempos][2] << location << endl;

                                        //cout << "Binary Code: " << hexToBinary(MemoryInstruction[mempos][2]) << hexToBinary(location) << endl << endl;

                                    }

                                }
                                else
                                {
                                    if (mode == "")
                                    {
                                        //cout << "Hex code: " << MemoryInstruction[mempos][1] << ct + z << endl;
                                        sub = ct + z;
                                        cout << MemoryInstruction[mempos][1] << ct + z << endl;

                                        //cout << "Binary Code: " << hexToBinary(MemoryInstruction[mempos][1]) << hexToBinary(sub) << endl<<endl;
                                        sub.clear();

                                    }
                                    else
                                    {

                                        //cout << "Hex code: " << MemoryInstruction[mempos][2] << ct + z  << endl;
                                        sub = ct + z;

                                        cout << MemoryInstruction[mempos][2] << ct + z << endl;

                                        //cout << "Binary Code: " << hexToBinary(MemoryInstruction[mempos][2]) << hexToBinary(sub) << endl << endl;
                                        sub.clear();

                                    }
                                }
                            }

                            location.clear();

                        }
                        if (found == 0)
                        {
                            cout << "ERROR!! undeclared variable: " << label << endl << endl;
                            break;
                        }

                        location.clear();
                        label.clear();
                    }
                    else
                    {
                        if (label.length() >= 3 && line[3] == ',') //cout data after variable
                        {
                            //cout <<"Hex code: "<< line.substr(5) << endl;
                            sub = line.substr(5);
                            //cout << "Binary Code: " << hexToBinary(sub)<< endl << endl;
                            cout << line.substr(5) << endl;

                            sub.clear();

                            data = 1;
                        }
                        else {
                            cout << "ERROR!! label has to be 3 or less characters and ends in a comma: " << line << endl << endl;
                            check = 2;
                            break;
                        }
                    }
                }

                if (check == 0 && data == 0 && g > 0)
                {
                    cout << "ERROR!! unknown instruction: " << line << endl << endl;
                }
            }


            if (check == 2)
            {
                break;
            }

            //check=0 not memory
            //check=1 memory
            //check=2 label error

            if (check == 0)
            {
                for (int i = 0; i < 12; i++)
                {
                    if (RegisterInstruction[i][0] == line.substr(0, 3))
                    {
                        //cout << "Hex code: "<< RegisterInstruction[i][1] << endl;
                        cout << RegisterInstruction[i][1] << endl;

                        //cout << "Binary Code: " << hexToBinary(RegisterInstruction[i][1]) << endl << endl;

                        check = 1;
                        break;
                    }
                }

                for (int i = 0; i < 6; i++)
                {
                    if (InOutInstruction[i][0] == line.substr(0, 3))
                    {
                        //cout << "Hex code: " << InOutInstruction[i][1] << endl;
                        cout << InOutInstruction[i][1] << endl;

                        //cout << "Binary Code: " << hexToBinary(InOutInstruction[i][1]) << endl << endl;

                        check = 1;
                        break;
                    }
                }


                if (check == 0 && g > 0 && data == 0)
                {
                    //cout << "Hex code: " << line << endl;
                    if (line.length() == 3)
                    {
                        cout << "instruction not found " << endl;
                    }
                    else {

                    cout << line << endl;
                    }

                    //cout << "Binary Code: " << hexToBinary(line) << endl << endl;

                }
            }

        }

        return 0;

    }
    else
    {
        cout << "Unable to open the file" << endl;
        return 1;
    }
}
