
#ifndef __UTILL__
#define __UTILL__

#include "stdfx.hpp"

byte stringTobyte(std::string str) {
	byte ret = 0;
	int offset = str.size() - 1;
	for (std::size_t i = 0; i < str.size(); i++) {
		if (str[i] == '1') {
			ret |= (0x1 << offset );
		}
		offset--;
	}
	return ret;
}


String removeAllOccurrences(String str,char toRemove){
    String output;
    output.reserve(str.length()); // optional, avoids buffer reallocations in the loop
    for(size_t i = 0; i < str.length(); ++i){
        if(str[i] != toRemove){
            output += str[i];
        } 
    }
    return output;
}

void printVec(std::vector<std::string> vec){
    for(unsigned int i = 0; i < vec.size(); i++){
        String temp = String(vec[i].c_str());
        Serial.print(temp);
        Serial.print(" ");
    }
    Serial.println("");
}


std::vector<std::string> split(std::string str,char c){
    std::vector<std::string> temp;
    temp.reserve(str.size() / 8);
    std::string toPush;
    if(str[0] == c)           { str.erase(str.begin() ); }
    if(str[str.size()-1] == c){ str.erase(str.end() -1  );  }
    for(int i = 0; i <= str.size(); i++){
        if( str[i] == c ){
            while(str[i+1] == c && i < str.size()){i++;}
            temp.push_back(toPush);
            toPush = "";
        }else if(i == str.size()){
            temp.push_back(toPush);
        }
        else{
            toPush += str[i];
        }
    }
    return temp;
}

#endif