#include "parser/parser.h"
#include "core/actions.h"
#include "core/base.h"
#include "core/card.h"
#include "core/entity.h"
#include <cstdint>
#include <ctime>
#include <iomanip>
#include <iterator>
#include <list>
#include <nlohmann/json.hpp>
#include <random>
#include <variant>

namespace Mayhem { // Parser methods

using Value = nlohmann::basic_json<>;

const size_t NUMBER_OF_CARDS = 40;

const std::string BASES_PATH = "../assets/images/bases/";
const std::string FACTIONS_PATH = "../assets/images/";

void Parser::parse_json(std::vector<Entity *> &entities, const std::string &input_file) {
    std::ifstream in(input_file);
    json jsonData = json::parse(in);
    std::string faction;

    for (const auto &block : jsonData.items()) {
        if (block.key() == "Faction") {
            faction = block.value();
            faction += "/";
        }
    }

    for (const auto &block : jsonData.items()) {
        for (const auto &item : block.value().items()) {
            if (block.key() == "Minion") {
                entities.push_back(parse_minion(entities, item.value(), faction));
            } else if (block.key() == "Action") {
                entities.push_back(parse_action(entities, item.value(), faction));
            } else if (item.key() == "Base") {
                entities.push_back(parse_base(entities, item.value()));
            }
        }
    }
}

Entity *Parser::parse_minion(std::vector<Entity *> &entities, const Value &item_value, const std::string &faction) {
    std::string name;
    uint32_t power;

    for (const auto &field : item_value.items()) {
        if (field.key() == "name") {
            name = field.value();
        } else if (field.key() == "power") {
            power = field.value();
        }
    }

    std::string minion_file = FACTIONS_PATH + faction + name;

    Entity *ent = new Minion(minion_file, FACTIONS_PATH + "shirt", entities.size(), power);
    return ent;
}

Entity *Parser::parse_action(std::vector<Entity *> &entities, const Value &item_value, const std::string &faction) {
    std::string name = item_value.at("name");
    std::string type = item_value.at("type");

    Entity *ent;
    const std::string action_file = FACTIONS_PATH + faction + name;
    if (type == "buff") {
        uint32_t power = item_value.at("power");
        ent = new BuffAction(action_file, FACTIONS_PATH + "shirt", entities.size(), power);
    } else if (type == "debuff") {
        uint32_t power = item_value.at("power");
        ent = new DebuffAction(action_file, FACTIONS_PATH + "shirt", entities.size(), power);
    } else if (type == "destroy") {
        ent = new DestroyAction(action_file, FACTIONS_PATH + "shirt", entities.size());
    } else if (type == "move") {
        ent = new MoveAction(action_file, FACTIONS_PATH + "shirt", entities.size());
    } else if (type == "draw") {
        uint32_t num = item_value.at("num");
        ent = new DrawAction(action_file, FACTIONS_PATH + "shirt", entities.size(), num);
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

    std::string minion_file = BASES_PATH + name;

    Entity *ent = new Base(minion_file, entities.size(), power, points);
    return ent;
}

struct CardInfo {
    uint32_t index;
    uint32_t number;
};

void Parser::json_for_player(const std::string &output_file) {
    const std::string &faction_name = get_faction_name();
    std::string cards_file = FACTIONS_PATH + faction_name + "/cards.json";
    std::ifstream in(cards_file);
    json jsonData = json::parse(in);
    std::ofstream out(output_file);

    json j;
    j["Faction"] = faction_name;

    srand(static_cast<uint32_t>(time(nullptr)));

    std::list<CardInfo> free_minions;
    std::list<CardInfo> free_actions;

    uint32_t index = 0;
    for (auto iter = jsonData.at("Minion").begin(); iter != jsonData.at("Minion").end(); ++iter, ++index) {
        free_minions.push_back({index, (*iter).at("number")});
    }
    index = 0;
    for (auto iter = jsonData.at("Action").begin(); iter != jsonData.at("Action").end(); ++iter, ++index) {
        free_actions.push_back({index, (*iter).at("number")});
    }

    for (size_t i = 0; i != NUMBER_OF_CARDS;) {
        uint32_t position = static_cast<uint32_t>(rand());

        if (position % 2 == 0) {
            if (!free_minions.empty()) {
                uint32_t index = position % free_minions.size();
                auto iter = free_minions.begin();
                std::advance(iter, index);
                j["Minion"] += jsonData.at("Minion")[iter->index];
                --iter->number;
                if (iter->number == 0) {
                    free_minions.erase(iter);
                }
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
                j["Action"] += jsonData.at("Action")[iter->index];
                --iter->number;
                if (iter->number == 0) {
                    free_actions.erase(iter);
                }
                ++i;
            }
        }

        if (free_minions.empty() && free_actions.empty()) {
            break;
        }
    }

    out << std::setw(4) << j << std::endl;
}

const std::string &Parser::get_faction_name() const {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, factions_.size() - 1);

    return factions_[dist(rng)];
}

}; // namespace Mayhem
