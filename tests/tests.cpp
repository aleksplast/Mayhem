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

TEST_F(TestEngine, test_play_action_not_on_your_turn) {
    engine->place_card(0, 19, 8);
    ASSERT_EQ(engine->play_action(2, 38, 19, 8, 0), false);
}

TEST_F(TestEngine, test_actions_limit) {
    engine->place_card(0, 21, 8);
    engine->end_turn(0);
    engine->place_card(1, 31, 8);
    engine->end_turn(1);
    engine->play_action(2, 38, 21, 8, 0);
    engine->end_turn(2);
    engine->place_card(3, 51, 8);
    engine->end_turn(3);
    engine->play_action(0, 15, 31, 8, 0);
    ASSERT_EQ(engine->play_action(0, 16, 51, 8, 0), false);
}

TEST_F(TestEngine, test_play_others_action) {
    engine->place_card(0, 19, 8);
    engine->end_turn(0);
    ASSERT_EQ(engine->play_action(1, 38, 19, 8, 0), false);
}

TEST_F(TestEngine, test_end_other_turn) {
    engine->place_card(0, 19, 8);
    ASSERT_EQ(engine->end_turn(1), 0);
}

TEST_F(TestEngine, test_end_zero_turn) {
    engine->place_card(0, 19, 8);
    ASSERT_EQ(engine->end_turn(0), 1);
}

TEST_F(TestEngine, test_end_first_turn) {
    engine->place_card(0, 19, 8);
    engine->end_turn(0);
    engine->place_card(1, 32, 8);
    ASSERT_EQ(engine->end_turn(1), 2);
}

TEST_F(TestEngine, test_end_second_turn) {
    engine->place_card(0, 19, 8);
    engine->end_turn(0);
    engine->place_card(1, 32, 8);
    engine->end_turn(1);
    engine->place_card(2, 42, 8);
    ASSERT_EQ(engine->end_turn(2), 3);
}

TEST_F(TestEngine, test_end_third_turn) {
    engine->place_card(0, 19, 8);
    engine->end_turn(0);
    engine->place_card(1, 32, 8);
    engine->end_turn(1);
    engine->place_card(2, 42, 8);
    engine->end_turn(2);
    engine->place_card(3, 53, 8);
    ASSERT_EQ(engine->end_turn(3), 0);
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
