#include "Component.h"
#include "../Netlist.h"

virtual void Component::checkConnections(std::string line){
	size_t len = inputs.size() + outputs.size();
	std::vector<bool> connections;
	connections.resize(len, false);
	for(unsigned i = 0; i < inputs.size(); i++){
		for(Variable &v : netlist->getInputs()){
			if(v.getName() == inputs[i]){
				connections[i] = true;
				v.setUsed();
			}
		}
		for(Variable &v : netlist->getWires()){
			if(v.getName() == inputs[i]){
				connections[i] = true;
				v.setUsed();
			}
		}
	}
	for(unsigned i = 0; i < outputs.size(); i++){
		for(Variable &v : netlist->getOutputs()){
			if(v.getName() == outputs[i]){
				connections[i + inputs.size()] = true;
				v.setUsed();
			}
		}
		for(Variable &v : netlist->getWires()){
			if(v.getName() == outputs[i]){
				connections[i + inputs.size()] = true;
				v.setUsed();
			}
		}
	}
	for(unsigned i = 0; i < connections.size(); i++){
		if(!connections[i]){
			throw std::length_error{"Missing connection! At line: " + line};
		}
	}
}

virtual void Component::checkWidths(){
	bool sign = this->isSigned();
	this->getWidth();
	for(unsigned i = 0; i < inputs.size(); i++){
		for(Variable v : this->netlist->getInputs()){
			if(inputs[i] == v.getName() && v.getWidth() < this->width && !v.isSigned() && sign){
				inputs[i] = "$signed({1'b0, " + inputs[i] + "})";
			} else if(inputs[i] == v.getName() && v.getWidth() > this->width){
				char width[16] = "";
				sprintf(width, "[%d:0]", this->width - 1);
				inputs[i] = inputs[i] + std::string{width};
			}
		}
		for(Variable v : this->netlist->getWires()){
			if(inputs[i] == v.getName() && v.getWidth() < this->width && !v.isSigned() && sign){
				inputs[i] = "$signed({1'b0, " + inputs[i] + "})";
			} else if(inputs[i] == v.getName() && v.getWidth() > this->width){
				char width[16] = "";
				sprintf(width, "[%d:0]", this->width - 1);
				inputs[i] = inputs[i] + std::string{width};
			}
		}
	}
}

virtual void Component::checkRegisters(){
	std::vector<std::shared_ptr<Component>> regs = this->netlist->getComponents();
	for(std::shared_ptr<Component> reg : regs){
		if(reg->componentName.find("REG") == std::string::npos){
			return;
		}
		for(int i = 0; i < inputs.size(); i++){
			if(inputs[i] == reg->idName){
				inputs[i] = reg->outputs[0];
			}
		}
		for(int i = 0; i < outputs.size(); i++){
			if(outputs[i] == reg->idName){
				outputs[i] = reg->inputs[2];
			}
		}
	}
}

virtual int Component::getWidth() {
	if(this->width != -1){
		return this->width;
	}
	int toReturn = 0;
	for(std::string output : outputs){
		for(Variable v : this->netlist->getOutputs()){
			if(output == v.getName() && v.getWidth() > toReturn){
				toReturn = v.getWidth();
			}
		}
		for(Variable v : this->netlist->getWires()){
			if(output == v.getName() && v.getWidth() > toReturn){
				toReturn = v.getWidth();
			}
		}
	}
	this->width = toReturn;
	if(this->width <= 0){
		throw std::length_error("Width of component must be greater than zero!");
	}
	return toReturn;
}

virtual bool Component::isSigned(){
	for(std::string output : outputs){
		for(Variable outputVar : this->netlist->getOutputs()){
			if(output == outputVar.getName() && outputVar.isSigned()){
				return true;
			}
		}
		for(Variable wireVar : this->netlist->getWires()){
			if(output == wireVar.getName() && wireVar.isSigned()){
				return true;
			}
		}
	}
	return false;
}
