#ifndef PARSE_H
#define PARSE_H


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include "core/entity.h"


using json = nlohmann::json;
using namespace nlohmann;

namespace Mayhem {

class Parser {

    using Value = nlohmann::basic_json<>;

    void parse_minion(std::vector<Entity*>& entities, const Value &value);
    void parse_action(std::vector<Entity*>& entities, const Value &value);
    void parse_base(std::vector<Entity*>& entities, const Value &value);
    void json_for_player(const std::string &input_file, const std::string &output_file);

public:
    Parser() = default;

    void parse_json(std::vector<Entity *> &entities, const std::string &input_file);
};

}


#endif
