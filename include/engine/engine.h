#ifndef ENGINE_H
#define ENGINE_H

#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>

#include "core/actions.h"
#include "core/base.h"
#include "core/card.h"
#include "core/deck.h"
#include "core/entity.h"
#include "graphics/graphics_view.hpp"
#include "parser/parser.h"
#include "player.h"
#include "playground.h"
#include "proto/engine.grpc.pb.h"
#include "proto/engine.pb.h"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

namespace Mayhem {

class MainServerEngineClient {
  public:
    MainServerEngineClient(){};
    MainServerEngineClient(std::shared_ptr<Channel> channel);
    MainServerEngineClient(MainServerEngineClient &&client);

    void place_card(uint16_t player_id, uint16_t card_id, uint16_t base_id);
    void play_action(uint16_t player_id, uint16_t action_id, uint16_t target_id, uint16_t src_id, uint16_t dest_id);
    void end_turn(uint16_t player_id);

    void initClient(uint32_t port);

  private:
    std::unique_ptr<enginePackage::MainServerEngine::Stub> stub_;
    std::string GetFile(const std::string &filename);
};

class SlaveServerEngineClient {
  public:
    SlaveServerEngineClient(){};
    SlaveServerEngineClient(std::shared_ptr<Channel> channel);

    void place_card(uint16_t player_id, uint16_t card_id, uint16_t base_id);
    void play_action(uint16_t player_id, uint16_t action_id, uint16_t target_id, uint16_t src_id, uint16_t dest_id);
    void end_turn(uint16_t player_id);

  private:
    std::unique_ptr<enginePackage::SlaveServerEngine::Stub> stub_;
};

// Main controlling structure
class Engine final : public enginePackage::MainServerEngine::Service, public enginePackage::SlaveServerEngine::Service {

  private:
    std::unique_ptr<Server> server_;
    // Indicates if engine is slave
    bool isSlave_;
    // Indicates if current game is online
    bool isOnline_;
    // Time for one turn
    int time_; // FIXME notimportatn: add support for time in game
    // Indicates, which player's turn is now
    uint16_t turn_;
    // All entities in the game
    std::vector<Entity *> entities_;
    // Playground of the game
    Playground playground;
    // Parser for game start
    Parser parser_;
    // Winner of the game
    size_t winner_ = SIZE_MAX;
    // Flag, indicates if the game is over
    bool game_over_ = false;
    // Vector of names of players decks
    std::vector<std::string> players_decks_names_;
    // File with bases
    std::string bases_deck_;

    // vector of online players
    std::vector<SlaveServerEngineClient> players_;
    MainServerEngineClient client_;

  public:
    //!--------------------------------
    //! @brief Engine can't be copied
    //!--------------------------------
    Engine(const Engine &rhs) = delete;
    Engine &operator=(const Engine &rhs) = delete;

    //!--------------------------------
    //! @brief Engine can't be moved
    //!--------------------------------
    Engine(Engine &&rhs) = delete;
    Engine &operator=(Engine &&rhs) = delete;

    //!--------------------------------
    //! @brief Default Constructor for Engine
    //!--------------------------------
    Engine();
    Engine(std::shared_ptr<Channel> channel, std::string port);

    //!--------------------------------
    //! @brief Default Engine Destructor
    //!--------------------------------
    ~Engine();

    //!--------------------------------
    //! @brief Get entity by id
    //! @param[in] entity_id Entity id
    //! @return Pointer to the Entity
    //!--------------------------------
    Entity *get_by_id(uint16_t entity_id);

    //!--------------------------------
    //! @brief Function for placing Minion to Base. Takes player's, minion's, base's id. Removes minion from player
    //! hand, adds minion to base.
    //! @param[in] player_id Player id, that is playing Minion
    //! @param[in] card_id Minion id
    //! @param[in] base_id base_id, where to place Minion
    //! @return true if success, false if not
    //!--------------------------------
    bool place_card(uint16_t player_id, uint16_t card_id, uint16_t base_id);
    void place_card_online(uint16_t player_id, uint16_t card_id, uint16_t base_id);
    Status placeCard(::grpc::ServerContext *context, const ::enginePackage::placeCardArgs *request,
                     ::enginePackage::ServerResponse *response) override;
    Status placeCardSlave(::grpc::ServerContext *, const ::enginePackage::placeCardArgs *,
                          ::enginePackage::ServerResponse *) override;

    //!--------------------------------
    //! @brief Function for playing Action. Takes player's, action's id and all id's for action ability, removes action
    //! from player hand.
    //! @param[in] player_id Player id, that is playing action
    //! @param[in] action_id Action id
    //! @param[in] target_id target id, Minion target for action
    //! @param[in] src_id base_id, where target is located
    //! @param[in] dest_id base_id, where to move target
    //! @return true if success, false if not
    //!--------------------------------
    bool play_action(uint16_t player_id, uint16_t action_id, uint16_t target_id, uint16_t src_id, uint16_t dest_id);
    void play_action_online(uint16_t player_id, uint16_t action_id, uint16_t target_id, uint16_t src_id,
                            uint16_t dest_id);
    Status playAction(::grpc::ServerContext *context, const ::enginePackage::playActionArgs *request,
                      ::enginePackage::ServerResponse *response) override;
    Status playActionSlave(::grpc::ServerContext *context, const ::enginePackage::playActionArgs *request,
                           ::enginePackage::ServerResponse *response) override;

    //!--------------------------------
    //! @brief End turn logic
    //! @param[in] player_id Player id, that is finishing turn
    //! @return Number of next turn
    //!--------------------------------
    uint16_t end_turn(uint16_t player_id);
    void end_turn_online(uint16_t player_id);
    Status endTurn(::grpc::ServerContext *context, const ::enginePackage::endTurnArgs *request,
                   ::enginePackage::ServerResponse *response) override;
    Status endTurnSlave(::grpc::ServerContext *context, const ::enginePackage::endTurnArgs *request,
                        ::enginePackage::ServerResponse *response) override;
    bool isOnline() { return isOnline_; };

    //!--------------------------------
    //! @brief After base capture distribute points between top players
    //! @param[out] base Captured base
    //! @param[out] leaderboard Leaderboard on this base
    //!--------------------------------
    void distribute_points(Base *base, LeaderBoard_t &leaderboard);

    //!--------------------------------
    //! @brief Choose factions for players and generate their decks
    //!--------------------------------
    void prepare_game();
    void engine_wait() { server_->Wait(); };

    // Parse players' decks, create bases, distribute cards
    void start_game();

    //!--------------------------------
    //! @brief Dumps state of engine and all of its components
    //! @param[in] file_name Name of the file to dump to
    //!--------------------------------
    void dump_state(std::string file_name) const;

    //!--------------------------------
    //! @brief Check, if the game is over
    //! @return bool flag, true if over, false if not
    //!--------------------------------
    bool is_over() const;

    //!--------------------------------
    //! @brief Get winner of the game
    //! @return Winner player's id
    //!--------------------------------
    uint32_t get_winner() const;

    //!--------------------------------
    //! @brief Get players decks names
    //!--------------------------------
    const std::vector<std::string> &get_players_decks_names() const;

    //!--------------------------------
    //! @brief Set players decks names
    //!--------------------------------
    void set_players_decks_names(std::vector<std::string> &names);
    // Inits online player
    Status initClient(::grpc::ServerContext *context, const ::enginePackage::ClientNetInfo *request,
                      ::enginePackage::ServerResponse *response) override;
    Status GetFile(grpc::ServerContext *context, const enginePackage::FileRequest *request,
                   enginePackage::FileResponse *response) override;

  private:
    // Add player in players structure
    void add_player(uint32_t port);

    //!--------------------------------
    //! @brief Get bases deck name
    //!--------------------------------
    const std::string &get_bases_deck_name() const;

    //!--------------------------------
    //! @brief Set bases deck name
    //!--------------------------------
    void set_bases_deck_name(const std::string &name);

  public: // graphic functions
    // Draw Engine
    void draw(GraphicsModel::Data::Attributes &attributes);
}; // class Engine

} // namespace Mayhem

#endif // ENGINE_H
