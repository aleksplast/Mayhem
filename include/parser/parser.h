#ifndef PARSE_H
#define PARSE_H

#include "core/entity.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;
using namespace nlohmann;

namespace Mayhem {

// Parser class
class Parser {

    using Value = nlohmann::basic_json<>;

    // Parse minion from json
    Entity *parse_minion(std::vector<Entity *> &entities, const Value &value);

    // Parse action from json
    Entity *parse_action(std::vector<Entity *> &entities, const Value &value);

    // Parse base from json
    Entity *parse_base(std::vector<Entity *> &entities, const Value &value);

  public:
    Parser() = default;

    // Make json file for player
    void json_for_player(const std::string &input_file, const std::string &output_file);

    // Parse json file
    std::vector<Entity *> parse_json(std::vector<Entity *> &entities, std::string input_file);
};

} // namespace Mayhem

#endif
