#include "parser/parser.h"
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
            } else if (item.key() == "Action") {
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
    std::string name;

    for (const auto &field : item_value.items()) {
        if (field.key() == "name") {
            name = field.value();
        }
    }

    std::string action_file = "../assets/images/" + name;

    Entity *ent = new Action(action_file, entities.size());
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

    std::unordered_set<uint32_t> busy_minions;
    std::unordered_set<uint32_t> busy_actions;

    size_t all_the_minion_cards = jsonData.at("Minion").size();
    // size_t all_the_action_cards = jsonData.at("Action").size();

    for (size_t i = 0; i != NUMBER_OF_CARDS;) {
        uint32_t position = static_cast<uint32_t>(rand());

        if (position % 2 == 0 && busy_minions.find(position % all_the_minion_cards) == busy_minions.end()) {

            j["Minion"] += jsonData.at("Minion")[position % all_the_minion_cards];
            busy_minions.insert(position % all_the_minion_cards);
            ++i;
        }
        //         else if (position % 2 != 0 && busy_actions.find(position % all_the_action_cards) ==
        //         busy_actions.end()) {
        //
        //             j["Action"] += jsonData.at("Action")[position % all_the_action_cards];
        //             busy_actions.insert(position % all_the_action_cards);
        //             ++i;
        //
        //         }
    }

    out << std::setw(4) << j << std::endl;
}

}; // namespace Mayhem
