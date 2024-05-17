set(CORE_SRC actions.cpp base.cpp card.cpp entity.cpp)
target_sources(game PRIVATE ${CORE_SRC})
if (ENABLE_TESTING)
    target_sources(test_engine PRIVATE ${CORE_SRC})
endif()

