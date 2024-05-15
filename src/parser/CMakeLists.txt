set(PARSER_SRC parser.cpp)
target_sources(game PRIVATE ${PARSER_SRC})
target_sources(test_engine PRIVATE ${PARSER_SRC})
