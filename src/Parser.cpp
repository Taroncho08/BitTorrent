#include "Parser.hpp"

BencodeValue Bencode_Parser::parse(const std::string& input) {
    pos = 0; 
    return parseValue(input);
}

BencodeValue Bencode_Parser::parseValue(const std::string& input) {
    char cur = input[pos];

    if (cur == 'i') return parseInt(input);    
    else if (cur == 'l') return parseList(input);  
    else if (cur == 'd') return parseDict(input);  
    else if (std::isdigit(cur)) return parseString(input); 

    throw std::runtime_error("Wrong format of file");  
}

int64_t Bencode_Parser::parseInt(const std::string& input) {
    ++pos;  
    std::string str;
    
    while (input[pos] != 'e') {
        str += input[pos++];
    }
    ++pos; 

    return std::stol(str); 
}

std::vector<BencodeValue> Bencode_Parser::parseList(const std::string& input) {
    ++pos;  
    std::vector<BencodeValue> vec;

    while (input[pos] != 'e') {
        vec.push_back(parseValue(input));
    }
    ++pos;  

    return vec;
}

std::unordered_map<std::string, BencodeValue> Bencode_Parser::parseDict(const std::string& input) {
    ++pos; 
    std::unordered_map<std::string, BencodeValue> mp;

    while (input[pos] != 'e') {
        std::string key = parseString(input);     
        BencodeValue value = parseValue(input);   

        mp[key] = value;  
    }
    ++pos;  

    return mp;
}

std::string Bencode_Parser::parseString(const std::string& input) {
    std::string length;

    while (input[pos] != ':') {
        length += input[pos++];
    }
    ++pos;  

    std::string result;

    int len = std::stoi(length);  

    for (int i = 0; i < len; ++i) {
        result += input[pos++];
    }

    return result;
}
