#include "parser/parser.h"
#include "core/base.h"
#include "core/card.h"
#include "core/entity.h"
#include <nlohmann/json.hpp>
#include <variant>

namespace Mayhem { // Parser methods

using Value = nlohmann::basic_json<>;

void Parser::parse_json(std::vector<Entity *> &entities, std::string input_file) {
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
    std::array<uint32_t, 3> points;

    for (const auto &field : item_value.items()) {
        if (field.key() == "name") {
            name = field.value();
        } else if (field.key() == "ability") {
            ability = field.value();
        } else if (field.key() == "power") {
            power = field.value();
        } else if (field.key() == "points") {
            // PARSE POINTS HERE
        }
    }

    std::string minion_file = "../src/graphics/images/" + name;

    Entity *ent = new Base(minion_file, entities.size(), ability, power, points);
    entities.push_back(ent);
}

}; // namespace Mayhem
