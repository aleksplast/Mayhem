#include "parser/parser.h"
#include "core/base.h"
#include "core/card.h"
#include "core/entity.h"
#include <nlohmann/json.hpp>
#include <variant>
#include <ctime>
#include <cstdlib>



#define NUMBER_OF_CARDS 10
#define ALL_THE_MINION_CARDS 10
#define ALL_THE_ACTION_CARDS 10


namespace Mayhem { // Parser methods

using Value = nlohmann::basic_json<>;

void Parser::parse_json(std::vector<Entity *> &entities, const std::string &input_file) {
    std::ifstream in(input_file);
    json jsonData = json::parse(in);

    for (const auto &block : jsonData.items()) {
        for (const auto &item : block.value().items()) {
            if (item.key() == "Minion") {
                parse_minion(entities, item.value());
            } else if (item.key() == "Action") {
                parse_action(entities, item.value());
            } else if (item.key() == "Base") {
                parse_base(entities, item.value());
            }
        }
    }
}

void Parser::parse_minion(std::vector<Entity *> &entities, const Value &item_value) {
    std::string name, ability;
    uint32_t power;

    for (const auto &field : item_value.items()) {
        if (field.key() == "name") {
            name = field.value();
        } else if (field.key() == "ability") {
            ability = field.value();
        } else if (field.key() == "power") {
            power = field.value();
        }
    }

    std::string minion_file = "../src/graphics/images/" + name;

    Entity *ent = new Minion(minion_file, entities.size(), ability, power);
    entities.push_back(ent);
}

void Parser::parse_action(std::vector<Entity *> &entities, const Value &item_value) {
    std::string name, ability;

    for (const auto &field : item_value.items()) {
        if (field.key() == "name") {
            name = field.value();
        }
        if (field.key() == "ability") {
            ability = field.value();
        }
    }

    std::string action_file = "../src/graphics/images/" + name;

    Entity *ent = new Action(action_file, entities.size(), ability);
    entities.push_back(ent);
}

void Parser::parse_base(std::vector<Entity *> &entities, const Value &item_value) {
    std::string name, ability;
    uint32_t power;
    std::array<uint32_t, 3> points = {0, 0, 0};

    for (const auto &field : item_value.items()) {
        if (field.key() == "name") {
            name = field.value();
        } else if (field.key() == "ability") {
            ability = field.value();
        } else if (field.key() == "power") {
            power = field.value();
        } else if (field.key() == "points") {
            size_t i = 0;
            for (const auto& point : (field.value()).items()) {
                points[i] = point.value();
                ++i;
            } 
        }
    }

    std::string minion_file = "../src/graphics/images/" + name;

    Entity *ent = new Base(minion_file, entities.size(), ability, power, points);
    entities.push_back(ent);
}


const std::string& Parser::json_for_player(const std::string &input_file, const std::string &output_file) {
    std::ifstream in(input_file);
    json jsonData = json::parse(in);
    std::ofstream out(output_file);

    json j;

    srand(static_cast<uint32_t>(time(nullptr)));
    
    std::unordered_set<uint32_t> busy_minions;
    std::unordered_set<uint32_t> busy_actions;
   
    for (size_t i = 0; i != NUMBER_OF_CARDS;) {
        uint32_t position = static_cast<uint32_t>(rand());
        
        if (position % 2 == 0 && busy_minions.find(position % ALL_THE_MINION_CARDS) == busy_minions.end()) {
            
            j["Minion"] += jsonData.at("Minion")[position % ALL_THE_MINION_CARDS];
            busy_minions.insert(position % ALL_THE_MINION_CARDS);
            ++i;
        
        } else if (position % 2 != 0 && busy_actions.find(position % ALL_THE_ACTION_CARDS) == busy_actions.end()) {

            j["Action"] += jsonData.at("Action")[position % ALL_THE_ACTION_CARDS];
            busy_actions.insert(position % ALL_THE_ACTION_CARDS);
            ++i;
        
        }
    }

    out << std::setw(4) << j << std::endl;
    return output_file;
}



}; // namespace Mayhem
