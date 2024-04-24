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

    const std::vector<std::string> factions_ = {"Drukhari", "Holy host", "Rogues"};

    using Value = nlohmann::basic_json<>;

    // Parse minion from json
    Entity *parse_minion(std::vector<Entity *> &entities, const Value &value, const std::string &faction);

    // Parse action from json
    Entity *parse_action(std::vector<Entity *> &entities, const Value &value, const std::string &faction);

    // Parse base from json
    Entity *parse_base(std::vector<Entity *> &entities, const Value &value);

    const std::string &get_faction_name() const;

  public:
    Parser() = default;

    // Make json file for player
    void json_for_player(const std::string &output_file);

    // Parse json file
    void parse_json(std::vector<Entity *> &entities, const std::string &input_file);
};

} // namespace Mayhem

#endif
