# Mega-Project-KT
Trivial card game project
## Requirements
1. nlohmann/json
2. SFML
3. gRPC (1.62.2)
4. protobuf (26.1.0)
## Build 
```sh
cd src/proto
protoc --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc='which grpc_cpp_plugin' ./engine.proto
mkdir build
cd build
cmake -DGRPC_INCLUDE_DIR="your path to grpc and absl include dir" ..
make 
./game
```
