#pragma once

#include <string>
#include <fstream>
#include <map>

/* Coderitter: Verrückt, dass du auch noch eine Assemblersprache umgesetzt hast. Das hätten 
wir erst für spätere Versionen des Ice Waters vorgesehen.

Ich glaube aber, der Interpreter müsste eher Compiler heißen. Er nimmt das Assembler Programm und
erzeugt daraus Byte Code für die CPU. */

//Class to translate a assembler file into a binarie(.hex) file
//and write the binarie into memory
class Interpreter
{   

    public:
        enum InterpreterState
        {
            OK,
            SyntaxError
        };

    private:

        std::map<std::string, std::string> m = {{"add", "00"}, {"sub", "01"}, {"mul", "02"}, {"div", "03"}, 
                                              {"addi", "04"}, {"subi", "05"}, {"muli", "06"}, {"divi", "07"},
                                              {"ST", "08"}, {"LD", "09"}, {"adr", "FF"}, 
                                              {"a1", "00"}, {"a2", "01"}, {"a3", "02"}, {"a4", "03"}, {"a5", "04"}, {"a6", "05"}, {"a6", "05"}, {"x0", "07"}};
        int file_pos;

        unsigned char* mem_p = NULL;
        std::string binary_path;


    public:
        Interpreter()
        {
            file_pos = 0;
        }

        int Init(std::string name);

        void Test(std::string path);

        //Translate .S file into a binarie(.hex) file
        //Store the binary in the binaries folder
        int ToBinary(std::string name);

        //Write binary(hex) instruction into the memory
        void WriteToMemory();

        void ResetFilePos();

       

    

    private:

        /* Coderitter: Wenn du die beiden Wörter umdrehst, TranslateWord, dann wird es schon besser lesbar. */
        //Translate assembler word into hex code
        int WordTranslate(std::string word, std::string& rlt);

        bool IsNumeric(std::string s);

        int GetSize(std::string file);

        /* Coderitter: Sowas kann man dann z.B. auch so nennen: GetBinaryPath. Da wird es noch ein
        Stück lesbarer. So wie eins oben drüber bei GetSize oder IsNumeric. */
        std::string NameBinary(std::string s);


        
};

