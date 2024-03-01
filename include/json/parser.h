#ifndef PARSE_H
#define PARSE_H


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "json.hpp"
#include "core/entity.h"


using json = nlohmann::json;
using namespace nlohmann;

namespace Mayhem {

class Parser {

    using Value = nlohmann::basic_json<>;

    void parse_minion(std::vector<Entity*>& entities, const Value &value);
    void parse_action(std::vector<Entity*>& entities, const Value &value);
    void parse_base(std::vector<Entity*>& entities, const Value &value);

public:
    Parser() = default;

    void parse_json(std::vector<Entity*>& entities, std::string input_file);
};

}


#endif
