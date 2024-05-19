set(ENGINE_SRC engine.cpp player.cpp playground.cpp)

include (common.cmake)
include_directories(${GRPC_INCLUDE_DIR})
message("Gprc inlcude dir is ${GRPC_INCLUDE_DIR}")
set(rg_proto_srcs "${CMAKE_SOURCE_DIR}/src/proto/engine.pb.cc")
set(rg_proto_hdrs "${CMAKE_SOURCE_DIR}/src/proto/engine.pb.h")
set(rg_grpc_srcs "${CMAKE_SOURCE_DIR}/src/proto/engine.grpc.pb.cc")
set(rg_grpc_hdrs "${CMAKE_SOURCE_DIR}/src/proto/engine.grpc.pb.h")
set(port_def "")

add_library(rg_grpc_proto
  ${rg_grpc_srcs}
  ${rg_grpc_hdrs}
  ${rg_proto_srcs}
  ${rg_proto_hdrs})
target_link_libraries(rg_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

target_link_libraries(game
    rg_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})

target_sources(game PRIVATE ${ENGINE_SRC})
if (ENABLE_TESTING)
    target_sources(test_engine PRIVATE ${ENGINE_SRC})
    target_link_libraries(test_engine
    rg_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})
endif()
