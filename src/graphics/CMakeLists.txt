set(GRAPHICS_SRC button.cpp draw.cpp drawable.cpp graphics.cpp graphics_controller.cpp graphics_model.cpp graphics_view.cpp command.cpp)
target_sources(game PRIVATE ${GRAPHICS_SRC})
target_sources(test_engine PRIVATE ${GRAPHICS_SRC})
