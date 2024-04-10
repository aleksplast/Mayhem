#include "parser/parser.h"
#include "core/actions.h"
#include "core/base.h"
#include "core/card.h"
#include "core/entity.h"
#include <cstdint>
#include <ctime>
#include <nlohmann/json.hpp>
#include <unordered_set>
#include <variant>

namespace Mayhem { // Parser methods

using Value = nlohmann::basic_json<>;

const size_t NUMBER_OF_CARDS = 40;

void Parser::parse_json(std::vector<Entity *> &entities, std::string input_file) {
    std::ifstream in(input_file);
    json jsonData = json::parse(in);

    for (const auto &block : jsonData.items()) {
        for (const auto &item : block.value().items()) {
            if (block.key() == "Minion") {
                parse_minion(entities, item.value());
            } else if (block.key() == "Action") {
                parse_action(entities, item.value());
            } else if (item.key() == "Base") {
                parse_base(entities, item.value());
            }
        }
    }
}

void Parser::parse_minion(std::vector<Entity *> &entities, const Value &item_value) {
    std::string name;
    uint32_t power;

    for (const auto &field : item_value.items()) {
        if (field.key() == "name") {
            name = field.value();
        } else if (field.key() == "power") {
            power = field.value();
        }
    }

    std::string minion_file = "../assets/images/" + name;

    Entity *ent = new Minion(minion_file, entities.size(), power);
    entities.push_back(ent);
}

void Parser::parse_action(std::vector<Entity *> &entities, const Value &item_value) {
    std::string name = item_value.at("name");
    std::string type = item_value.at("type");

    Entity *ent;
    std::string action_file = "../assets/images/" + name;
    if (type == "buff") {
        uint32_t power = item_value.at("power");
        ent = new BuffAction(action_file, entities.size(), type, power);
    } else if (type == "buff") {
        uint32_t power = item_value.at("power");
        ent = new DebuffAction(action_file, entities.size(), type, power);
    } else if (type == "destroy") {
        ent = new DestroyAction(action_file, entities.size(), type);
    } else {
        ent = new MoveAction(action_file, entities.size(), type);
    }

    entities.push_back(ent);
}

void Parser::parse_base(std::vector<Entity *> &entities, const Value &item_value) {
    std::string name;
    uint32_t power;
    std::array<uint32_t, 3> points = {0, 0, 0};

    for (const auto &field : item_value.items()) {
        if (field.key() == "name") {
            name = field.value();
        } else if (field.key() == "power") {
            power = field.value();
        } else if (field.key() == "points") {
            size_t i = 0;
            for (const auto &point : (field.value()).items()) {
                points[i] = point.value();
                ++i;
            }
        }
    }

    std::string minion_file = "../assets/images/" + name;

    Entity *ent = new Base(minion_file, entities.size(), power, points);
    entities.push_back(ent);
}

void Parser::json_for_player(const std::string &input_file, const std::string &output_file) {
    std::ifstream in(input_file);
    json jsonData = json::parse(in);
    std::ofstream out(output_file);

    json j;

    srand(static_cast<uint32_t>(time(nullptr)));

    std::unordered_set<uint32_t> free_minions;
    std::unordered_set<uint32_t> free_actions;

    for (size_t i = 0; i != jsonData.at("Minion").size(); ++i) {
        free_minions.insert(i);
    }
    for (size_t i = 0; i != jsonData.at("Action").size(); ++i) {
        free_actions.insert(i);
    }

    for (size_t i = 0; i != NUMBER_OF_CARDS;) {
        uint32_t position = static_cast<uint32_t>(rand());

        if (position % 2 == 0 && free_minions.size() != 0) {
            uint32_t index = position % free_minions.size();
            j["Minion"] += jsonData.at("Minion")[index];
            free_minions.erase(index);
            ++i;

        } else if (position % 2 != 0 && free_actions.size() != 0) {
            uint32_t index = position % free_actions.size();
            j["Action"] += jsonData.at("Action")[index];
            free_actions.erase(index);
            ++i;

        } else if (free_minions.size() == 0 && free_actions.size() == 0) {
            break;
        }
    }

    out << std::setw(4) << j << std::endl;
}

}; // namespace Mayhem
