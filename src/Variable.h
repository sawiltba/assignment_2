#ifndef __VARIABLE_H
#define __VARIABLE_H

class Variable{
	private:
		std::string name, type;
		int width;
		bool Signed;
	public:
		Variable(std::string name, std::string type, int width, bool sign){
			this->name = name;
			this->type = type;
			this->width = width;
			this->Signed = sign;
		}
		std::string toString(){
			//<dir> <width> <name>;
			size_t len = 2 + name.length() + type.length();
			char widthStr[16] = "";
			if(width > 1){
				// [w-1:0]
				len += 5 + std::to_string(width - 1).length();
				sprintf(widthStr, " [%d:0]", width - 1);
			}
			char* str = (char*)malloc(len + 1);
			sprintf(str, "%s%s %s;\n", type.c_str(), 
					widthStr, name.c_str());
			std::string toReturn{str};
			return toReturn;
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
