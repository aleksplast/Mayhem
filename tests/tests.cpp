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

class TestEngine : public ::testing::Test {
    void SetUp() {
        engine = new Engine;
        GraphicsModel model(*engine);
        GraphicsController controller(model);
        GraphicsView view(model);

        std::vector<std::string> names;
        for (uint16_t i = 0; i < PLAYERS_NUM; i++) {
            std::string test_deck_file = TEST_DECK + std::to_string(i) + JSON;
            names.push_back(test_deck_file);
        }

        engine->set_players_decks_names(names);
        engine->start_game(model.attributes);
        engine->dump_state("test_dump");
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

TEST(Start_game, test_start_game) {
    Engine *engine = new Engine;
    GraphicsModel model(*engine);
    GraphicsController controller(model);
    GraphicsView view(model);

    std::vector<std::string> names;
    for (uint16_t i = 0; i < PLAYERS_NUM; i++) {
        std::string test_deck_file = TEST_DECK + std::to_string(i) + JSON;
        names.push_back(test_deck_file);
    }

    engine->set_players_decks_names(names);

    engine->start_game(model.attributes);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}
