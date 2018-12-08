#ifndef __VARIABLE_H
#define __VARIABLE_H

#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>

class Variable{
	private:
		std::string name, type;
		int width;
		bool Signed;
        bool used = false;
	public:
		Variable(std::string name, std::string type, int width, bool sign){
			this->name = name;
			this->type = type;
			this->width = width;
			this->Signed = sign;
		}
		std::string toString(){
			//<dir> <width> <name>;
            std::stringstream toReturn;
            if (type.compare("variable")) {
				toReturn << "reg";
			}
			else if (type.compare("output")) {
				toReturn << "output reg";
			}
			else {
				toReturn << type;
			}
            
			if(width > 1){
				// [w-1:0]
				//len += 5 + std::to_string(width - 1).length();
				//sprintf(widthStr, "%s [%d:0]", signedStr, width - 1);
                toReturn << " [" << width - 1 << ":0]";
			}
            
            toReturn << " " << name << ";\n";
			return toReturn.str();
		}

        bool isUsed(){
            return used;
        }

        void setUsed(){
            used = true;
        }

		std::string getType(){
			return type;
		}

		std::string getName(){
			return name;
		}

		int getWidth(){
			return width;
		}

		bool isSigned(){
			return Signed;
		}
};

#endif
