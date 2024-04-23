#include "parser/parser.h"
#include "core/actions.h"
#include "core/base.h"
#include "core/card.h"
#include "core/entity.h"
#include <cstdint>
#include <ctime>
#include <iterator>
#include <list>
#include <nlohmann/json.hpp>
#include <variant>

namespace Mayhem { // Parser methods

using Value = nlohmann::basic_json<>;

const size_t NUMBER_OF_CARDS = 40;

std::vector<Entity *> Parser::parse_json(std::vector<Entity *> &entities, std::string input_file) {
    std::ifstream in(input_file);
    json jsonData = json::parse(in);

    for (const auto &block : jsonData.items()) {
        for (const auto &item : block.value().items()) {
            if (block.key() == "Minion") {
                entities.push_back(parse_minion(entities, item.value()));
            } else if (block.key() == "Action") {
                parse_action(entities, item.value());
            } else if (item.key() == "Base") {
                entities.push_back(parse_base(entities, item.value()));
            }
        }
    }

    return entities;
}

Entity *Parser::parse_minion(std::vector<Entity *> &entities, const Value &item_value) {
    std::string name;
    uint32_t power;

    for (const auto &field : item_value.items()) {
        if (field.key() == "name") {
            name = field.value();
        } else if (field.key() == "power") {
            power = field.value();
        }
    }

    std::string minion_file = "../assets/images/drukhari/" + name;

    Entity *ent = new Minion(minion_file, entities.size(), power);
    return ent;
}

Entity *Parser::parse_action(std::vector<Entity *> &entities, const Value &item_value) {
    std::string name = item_value.at("name");
    std::string type = item_value.at("type");

    Entity *ent;
    std::string action_file = "../assets/images/drukhari/" + name;
    if (type == "buff") {
        uint32_t power = item_value.at("power");
        ent = new BuffAction(action_file, entities.size(), power);
    } else if (type == "buff") {
        uint32_t power = item_value.at("power");
        ent = new DebuffAction(action_file, entities.size(), power);
    } else if (type == "destroy") {
        ent = new DestroyAction(action_file, entities.size());
    } else {
        ent = new MoveAction(action_file, entities.size());
    }

    return ent;
}

Entity *Parser::parse_base(std::vector<Entity *> &entities, const Value &item_value) {
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

    std::string minion_file = "../assets/images/bases/" + name;

    Entity *ent = new Base(minion_file, entities.size(), power, points);
    return ent;
}

void Parser::json_for_player(const std::string &input_file, const std::string &output_file) {
    std::ifstream in(input_file);
    json jsonData = json::parse(in);
    std::ofstream out(output_file);

    json j;

    srand(static_cast<uint32_t>(time(nullptr)));

    std::list<uint32_t> free_minions;
    std::list<uint32_t> free_actions;

    for (size_t i = 0; i != jsonData.at("Minion").size(); ++i) {
        free_minions.push_back(i);
    }
    for (size_t i = 0; i != jsonData.at("Action").size(); ++i) {
        free_actions.push_back(i);
    }

    for (size_t i = 0; i != NUMBER_OF_CARDS;) {
        uint32_t position = static_cast<uint32_t>(rand());

        if (position % 2 == 0) {
            if (!free_minions.empty()) {
                uint32_t index = position % free_minions.size();
                auto iter = free_minions.begin();
                std::advance(iter, index);
                j["Minion"] += jsonData.at("Minion")[*iter];
                free_minions.erase(iter);
                ++i;
            } else {
                ++position;
            }
        }

        if (position % 2 != 0) {
            if (!free_actions.empty()) {
                uint32_t index = position % free_actions.size();
                auto iter = free_actions.begin();
                std::advance(iter, index);
                j["Action"] += jsonData.at("Action")[*iter];
                free_actions.erase(iter);
                ++i;
            }
        }

        if (free_minions.empty() && free_actions.empty()) {
            break;
        }
    }

    out << std::setw(4) << j << std::endl;
}

}; // namespace Mayhem
