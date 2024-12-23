#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <unordered_map>

struct BencodeValue;

using BencodeVariant = std::variant<long, std::string, std::vector<BencodeValue>, std::unordered_map<std::string, BencodeValue>>;

struct BencodeValue : public BencodeVariant
{
    using BencodeVariant::BencodeVariant;
};

void printBencodeValue(const BencodeValue& value, int indent = 0) {
    std::string indentation(indent, ' ');

    std::visit([&](const auto& v) {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, long>) {
            std::cout << indentation << v << '\n';
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << indentation << '"' << v << '"' << '\n';
        } else if constexpr (std::is_same_v<T, std::vector<BencodeValue>>) {
            std::cout << indentation << "[\n";
            for (const auto& item : v) {
                printBencodeValue(item, indent + 2); 
            }
            std::cout << indentation << "]\n";
        } else if constexpr (std::is_same_v<T, std::unordered_map<std::string, BencodeValue>>) {
            std::cout << indentation << "{\n";
            for (const auto& [key, val] : v) {
                std::cout << indentation << "  \"" << key << "\": ";
                printBencodeValue(val, indent + 2);
            }
            std::cout << indentation << "}\n";
        }
    }, value);
}

class Bencode_Parser {
public:
    BencodeValue parse(const std::string input) {
        pos = 0;
        return parseValue(input);
    }

private:
    BencodeValue parseValue(const std::string input) {
        char cur = input[pos];

        if (cur == 'i') return parseInt(input);
        else if (cur == 'l') return parseList(input);
        else if (cur == 'd') return parseDict(input);
        else if (std::isdigit(cur)) return parseString(input);

        throw std::runtime_error("Wrong format of file");
    }

    long parseInt(const std::string input) {
        ++pos;
        std::string str;
        while (input[pos] != 'e') {
            str += input[pos++];
        }
        ++pos;
        return std::stol(str);
    }

    std::vector<BencodeValue> parseList(const std::string input) {
        ++pos;
        std::vector<BencodeValue> vec;

        while (input[pos] != 'e') {
            vec.push_back(parseValue(input));
        }

        ++pos;
        return vec;
    }

    std::unordered_map<std::string, BencodeValue> parseDict(const std::string input) {
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

    std::string parseString(const std::string input) {
        std::string lenght;

        while (input[pos] != ':') {
            lenght += input[pos++];
        }

        ++pos;
        std::string result;

        int len = std::stoi(lenght);

        for (int i = 0; i < len; ++i) {
            result += input[pos++];
        }

        return result;
    }

private:
    std::size_t pos;
};
