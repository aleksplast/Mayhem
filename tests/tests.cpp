#include <gtest/gtest.h>
#include <iostream>
#include "engine/engine.h"
#include "graphics/graphics.hpp"
#include "graphics/graphics_controller.hpp"
#include "graphics/graphics_model.hpp"
#include "graphics/graphics_view.hpp"


namespace Mayhem {

const uint16_t PLAYERS_NUM = 4;
const std::string TEST_DECK = "test_deck";
const std::string JSON = ".json";
const std::string TEST_BASES = "test_bases.json";

class TestEngine : public ::testing::Test {
    void SetUp() {
        engine = new Engine;
        std::vector<std::string> names;
        for (uint16_t i = 0; i < PLAYERS_NUM; i++) {
            std::string test_deck_file = TEST_DECK + std::to_string(i) + JSON;
            names.push_back(test_deck_file);
        }

        engine->set_bases_deck_name(TEST_BASES);
        engine->set_players_decks_names(names);
        engine->start_game();
    }

    void TearDown() {
        delete engine;
    }

    public:
    Engine *engine;
}; // class TestEngine

TEST_F(TestEngine, test_game_over_at_start) {
    ASSERT_EQ(engine->is_over(), false);
}

TEST_F(TestEngine, test_winner_at_start) {
    ASSERT_NE(engine->get_winner(), SIZE_MAX);
}

TEST_F(TestEngine, test_place_card) {
    ASSERT_EQ(engine->place_card(0, 19, 8), true);
}

TEST_F(TestEngine, test_place_others_card) {
    ASSERT_EQ(engine->place_card(0, 32, 8), false);
}

TEST_F(TestEngine, test_place_card_not_on_your_turn) {
    ASSERT_EQ(engine->place_card(1, 32, 8), false);
}

TEST_F(TestEngine, test_minions_limit) {
    engine->place_card(0, 19, 8);
    ASSERT_EQ(engine->place_card(0, 21, 8), false);
}

TEST(Start_game, test_start_game) {
    Engine *engine = new Engine;
    std::vector<std::string> names;
    for (uint16_t i = 0; i < PLAYERS_NUM; i++) {
        std::string test_deck_file = TEST_DECK + std::to_string(i) + JSON;
        names.push_back(test_deck_file);
    }

    engine->set_bases_deck_name(TEST_BASES);
    engine->set_players_decks_names(names);

    engine->start_game();
    engine->dump_state("test_dump");
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}
