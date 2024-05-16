#include "engine/engine.h"
#include "../proto/engine.grpc.pb.h"
#include "../proto/engine.pb.h"
#include "core/actions.h"
#include "core/base.h"
#include "engine/player.h"
#include "graphics/graphics.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

namespace Mayhem { // Engine methods

MainServerEngineClient::MainServerEngineClient(std::shared_ptr<Channel> channel)
    : stub_(enginePackage::MainServerEngine::NewStub(channel)){};
MainServerEngineClient::MainServerEngineClient(MainServerEngineClient &&client) : stub_(std::move(client.stub_)){};

void MainServerEngineClient::place_card(uint16_t player_id, uint16_t card_id, uint16_t base_id) {
    ClientContext context;
    enginePackage::placeCardArgs args;
    args.set_playerid(player_id);
    args.set_cardid(card_id);
    args.set_baseid(base_id);
    enginePackage::ServerResponse engineResponse;
    engineResponse.set_status(false);

    Status status = stub_->placeCard(&context, args, &engineResponse);
    if (!status.ok()) {
        std::cout << "GetFeature rpc failed." << std::endl;
        std::cout << "Cur status " << status.error_code() << std::endl;
        std::cout << "Cur status " << status.error_details() << std::endl;
        std::cout << "Cur status " << status.error_message() << std::endl;
        return;
    }

    std::cout << "Get response: " << engineResponse.status() << std::endl;
};

void MainServerEngineClient::play_action(uint16_t player_id, uint16_t action_id, uint16_t target_id, uint16_t src_id,
                                         uint16_t dest_id) {
    ClientContext context;
    enginePackage::playActionArgs args;
    args.set_playerid(player_id);
    args.set_actionid(action_id);
    args.set_targetid(target_id);
    args.set_srcid(src_id);
    args.set_destid(dest_id);
    enginePackage::ServerResponse engineResponse;
    engineResponse.set_status(false);

    Status status = stub_->playAction(&context, args, &engineResponse);
    if (!status.ok()) {
        std::cout << "GetFeature rpc failed." << std::endl;
        std::cout << "Cur status " << status.error_code() << std::endl;
        std::cout << "Cur status " << status.error_details() << std::endl;
        std::cout << "Cur status " << status.error_message() << std::endl;
        return;
    }

    std::cout << "Get response: " << engineResponse.status() << std::endl;
};

void MainServerEngineClient::end_turn(uint16_t player_id) {
    ClientContext context;
    enginePackage::endTurnArgs args;
    args.set_playerid(player_id);
    enginePackage::ServerResponse engineResponse;
    engineResponse.set_status(false);

    Status status = stub_->endTurn(&context, args, &engineResponse);
    if (!status.ok()) {
        std::cout << "GetFeature rpc failed." << std::endl;
        std::cout << "Cur status " << status.error_code() << std::endl;
        std::cout << "Cur status " << status.error_details() << std::endl;
        std::cout << "Cur status " << status.error_message() << std::endl;
        return;
    }

    std::cout << "Get response: " << engineResponse.status() << std::endl;
};

void MainServerEngineClient::initClient(uint32_t port) {
    std::ofstream outputFile("player0_deck.json"); // FIXME TIAZH: error handling
    outputFile << GetFile("player0_deck.json");
    outputFile.close();
    outputFile.open("player1_deck.json"); // FIXME TIAZH: error handling
    outputFile << GetFile("player1_deck.json");
    outputFile.close();
    outputFile.open("player2_deck.json"); // FIXME TIAZH: error handling
    outputFile << GetFile("player2_deck.json");
    outputFile.close();
    outputFile.open("player3_deck.json"); // FIXME TIAZH: error handling
    outputFile << GetFile("player3_deck.json");
    outputFile.close();
    ClientContext context;
    enginePackage::ClientNetInfo net_info;
    net_info.set_port(port);
    enginePackage::ServerResponse engine_response;
    Status status = stub_->initClient(&context, net_info, &engine_response);

    if (!status.ok()) {
        std::cout << "GetFeature rpc failed." << std::endl;
        return;
    }
};

std::string MainServerEngineClient::GetFile(const std::string &filename) {
    enginePackage::FileRequest request;
    request.set_file_name(filename);

    enginePackage::FileResponse response;

    ClientContext context;
    Status status = stub_->GetFile(&context, request, &response);

    if (status.ok()) {
        return response.file_content();
    } else {
        std::cerr << "RPC failed: " << status.error_message() << std::endl;
        return "";
    }
};

// FIXME TIAZH: I don't know where to put it, maybe in diff file
SlaveServerEngineClient::SlaveServerEngineClient(std::shared_ptr<Channel> channel)
    : stub_(enginePackage::SlaveServerEngine::NewStub(channel)){};

void SlaveServerEngineClient::place_card(uint16_t player_id, uint16_t card_id, uint16_t base_id) {
    ClientContext context;
    enginePackage::placeCardArgs args;
    args.set_playerid(player_id);
    args.set_cardid(card_id);
    args.set_baseid(base_id);
    enginePackage::ServerResponse engineResponse;
    engineResponse.set_status(false);

    Status status = stub_->placeCardSlave(&context, args, &engineResponse);
    if (!status.ok()) {
        std::cout << "SlaveServer placeCard failed." << std::endl;
        std::cout << "Cur status " << status.error_code() << std::endl;
        std::cout << "Cur status " << status.error_details() << std::endl;
        std::cout << "Cur status " << status.error_message() << std::endl;
        return;
    }

    std::cout << "Get response: " << engineResponse.status() << std::endl;
};

void SlaveServerEngineClient::play_action(uint16_t player_id, uint16_t action_id, uint16_t target_id, uint16_t src_id,
                                          uint16_t dest_id) {
    ClientContext context;
    enginePackage::playActionArgs args;
    args.set_playerid(player_id);
    args.set_actionid(action_id);
    args.set_targetid(target_id);
    args.set_srcid(src_id);
    args.set_destid(dest_id);
    enginePackage::ServerResponse engineResponse;
    engineResponse.set_status(false);

    Status status = stub_->playActionSlave(&context, args, &engineResponse);
    if (!status.ok()) {
        std::cout << "SlaveServer placeCard failed." << std::endl;
        std::cout << "Cur status " << status.error_code() << std::endl;
        std::cout << "Cur status " << status.error_details() << std::endl;
        std::cout << "Cur status " << status.error_message() << std::endl;
        return;
    }

    std::cout << "Get response: " << engineResponse.status() << std::endl;
};

void SlaveServerEngineClient::end_turn(uint16_t player_id) {
    ClientContext context;
    enginePackage::endTurnArgs args;
    args.set_playerid(player_id);
    enginePackage::ServerResponse engineResponse;
    engineResponse.set_status(false);

    Status status = stub_->endTurnSlave(&context, args, &engineResponse);
    if (!status.ok()) {
        std::cout << "SlaveServer placeCard failed." << std::endl;
        std::cout << "Cur status " << status.error_code() << std::endl;
        std::cout << "Cur status " << status.error_details() << std::endl;
        std::cout << "Cur status " << status.error_message() << std::endl;
        return;
    }

    std::cout << "Get response: " << engineResponse.status() << std::endl;
};
// Player can only have 10 cards in hand
const uint32_t MAX_CARDS_IN_HAND = 10;

// At the end of the turn player draw 2 cards
const uint32_t CARDS_TO_DRAW_END_TURN = 2;

// Location of the data base with all bases
const std::string BASE_DATA_BASE_FILE = "../assets/base_data_base.json";

const std::string PLAYER = "player";

const std::string DECK_JSON_FILE = "_deck.json";

const uint32_t NUMBER_OF_WINNERS = 3;

Engine::Engine()
    : turn_(0), isOnline_(false), isSlave_(false), time_(0), entities_(), playground(entities_), parser_(){};
Engine::Engine(std::shared_ptr<Channel> Channel, std::string port)
    : isOnline_(true), isSlave_(true), turn_(0), time_(0), entities_(), playground(entities_), parser_(),
      client_(Channel) {
    std::string server_address("localhost:" + port);
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(static_cast<enginePackage::SlaveServerEngine::Service *>(this));
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    client_.initClient(stoi(port));
    server_ = std::move(server);
};

Entity *Engine::get_by_id(uint16_t entity_id) {
    if (entity_id >= entities_.size()) {
        std::cout << "HERE NEED TO BE LOG: entity id is bigger than vector size" << std::endl;
        return nullptr;
    }

    return entities_[entity_id];
};

Status Engine::placeCard(::grpc::ServerContext *context, const ::enginePackage::placeCardArgs *request,
                         ::enginePackage::ServerResponse *response) {
    std::cout << "Received placeCard request" << std::endl;

    uint16_t player_id = request->playerid();
    uint16_t card_id = request->cardid();
    uint16_t base_id = request->baseid();

    if (place_card(player_id, card_id, base_id)) {
        response->set_status(1);
        for (auto &player : players_) {
            player.place_card(player_id, card_id, base_id);
        }
    } else
        response->set_status(0);

    std::cout << "Sending to all servers" << std::endl;

    return Status::OK;
};

// FIXME notimortant: add some check if place card is executed
Status Engine::placeCardSlave(::grpc::ServerContext *context, const ::enginePackage::placeCardArgs *request,
                              ::enginePackage::ServerResponse *response) {
    uint16_t player_id = request->playerid();
    uint16_t card_id = request->cardid();
    uint16_t base_id = request->baseid();

    place_card(player_id, card_id, base_id);

    response->set_status(1);
    return Status::OK;
};

void Engine::place_card_online(uint16_t player_id, uint16_t card_id, uint16_t base_id) {
    this->client_.place_card(player_id, card_id, base_id);
}

bool Engine::place_card(uint16_t player_id, uint16_t card_id, uint16_t base_id) {
    // Проверка на мастера и на слейва
    if (player_id != turn_)
        return false;

    Player *player = static_cast<Player *>(get_by_id(player_id));

    if (player->get_minions_limit() == 0) {
        return false;
    }

    Minion *card = static_cast<Minion *>(get_by_id(card_id));
    Base *base = static_cast<Base *>(get_by_id(base_id));

    if (player_id != card->get_owner())
        return false;

    player->play_card(card); // FIXME: add error handling
    base->gain_minion(card);
    player->change_minions_limit(-1);

    return true;
}

Status Engine::playAction(::grpc::ServerContext *context, const ::enginePackage::playActionArgs *request,
                          ::enginePackage::ServerResponse *response) {
    std::cout << "Received playAction request" << std::endl;

    uint16_t player_id = request->playerid();
    uint16_t action_id = request->actionid();
    uint16_t target_id = request->targetid();
    uint16_t src_id = request->srcid();
    uint16_t dest_id = request->destid();

    if (play_action(player_id, action_id, target_id, src_id, dest_id)) {
        response->set_status(1);
        for (auto &player : players_) {
            player.play_action(player_id, action_id, target_id, src_id, dest_id);
        }
    } else
        response->set_status(0);

    std::cout << "Sending to all servers" << std::endl;

    return Status::OK;
};

Status Engine::playActionSlave(::grpc::ServerContext *context, const ::enginePackage::playActionArgs *request,
                               ::enginePackage::ServerResponse *response) {
    uint16_t player_id = request->playerid();
    uint16_t action_id = request->actionid();
    uint16_t target_id = request->targetid();
    uint16_t src_id = request->srcid();
    uint16_t dest_id = request->destid();
    play_action(player_id, action_id, target_id, src_id, dest_id);

    response->set_status(1);
    return Status::OK;
};

void Engine::play_action_online(uint16_t player_id, uint16_t action_id, uint16_t target_id, uint16_t src_id,
                                uint16_t dest_id) {
    this->client_.play_action(player_id, action_id, target_id, src_id, dest_id);
}

bool Engine::play_action(uint16_t player_id, uint16_t action_id, uint16_t target_id, uint16_t src_id,
                         uint16_t dest_id) {
    std::cout << "Current Turn" << turn_ << std::endl;

    if (player_id != turn_)
        return false;

    if (auto *act = dynamic_cast<Action *>(get_by_id(action_id))) {
        Player *player = static_cast<Player *>(get_by_id(player_id));

        if (player->get_actions_limit() == 0) {
            return false;
        }

        player->play_card(act);

        if (auto draw_act = dynamic_cast<DrawAction *>(act)) {
            draw_act->activate_ability(player);
        } else {
            Minion *target = dynamic_cast<Minion *>(get_by_id(target_id));
            Base *src = dynamic_cast<Base *>(get_by_id(src_id));
            Base *dest = dynamic_cast<Base *>(get_by_id(dest_id));
            act->activate_abillity(target, src, dest);
        }

        player->change_actions_limit(-1);

        return true;
    }

    return false;
}

Status Engine::endTurn(::grpc::ServerContext *context, const ::enginePackage::endTurnArgs *request,
                       ::enginePackage::ServerResponse *response) {
    uint16_t player_id = request->playerid();

    if (end_turn(player_id) + 6) {
        response->set_status(1);
        for (auto &player : players_) {
            player.end_turn(player_id);
        }
    } else
        response->set_status(0);

    std::cout << "Sending to all servers" << std::endl;

    return Status::OK;
}

Status Engine::endTurnSlave(::grpc::ServerContext *context, const ::enginePackage::endTurnArgs *request,
                            ::enginePackage::ServerResponse *response) {
    uint16_t player_id = request->playerid();
    end_turn(player_id);

    response->set_status(1);
    return Status::OK;
}

void Engine::end_turn_online(uint16_t player_id) { this->client_.end_turn(player_id); }

uint16_t Engine::end_turn(uint16_t player_id) {
    std::cout << "Current turn is " << turn_ << std::endl;
    std::cout << "Your turn is " << player_id << std::endl;
    if (player_id != turn_) {
        return turn_;
    }
    Player *player = dynamic_cast<Player *>(get_by_id(player_id));

    std::vector<Base *> captured_bases = playground.check_bases();
    for (auto base : captured_bases) {
        LeaderBoard_t leader_board = playground.capture_base(base);
        playground.destroy_base(base);
        playground.set_new_base();

        distribute_points(base, leader_board);
    }

    player->take_card(CARDS_TO_DRAW_END_TURN);
    player->set_actions_limit(1);
    player->set_minions_limit(1);

    while (player->get_number_of_cards() > MAX_CARDS_IN_HAND) {
        player->dump_random_card();
    }

    auto win_pair = playground.check_for_winner();

    if (win_pair.first) {
        game_over_ = true;
        winner_ = win_pair.second;
    }

    turn_ = (turn_ + 1) % (playground.get_number_of_players());
    return turn_;
}

bool Engine::is_over() const { return game_over_; }

uint32_t Engine::get_winner() const { return winner_; }

void Engine::prepare_game() {
    std::vector<std::string> names;

    std::vector<std::string> names;

    for (uint16_t i = 0; i < playground.get_number_of_players(); i++) {
        std::string player_deck_file = PLAYER + std::to_string(i) + DECK_JSON_FILE;
        parser_.json_for_player(player_deck_file);
        names.push_back(player_deck_file);
    }

    set_players_decks_names(names);
    set_bases_deck_name(BASE_DATA_BASE_FILE);
}

void Engine::start_game() {
    size_t curr_id = playground.get_number_of_players();

    parser_.parse_json(entities_, bases_deck_);
    for (size_t id = curr_id; id < entities_.size(); id++) {
        playground.gain_base_on_start(static_cast<Base *>(get_by_id(id)));
    }

    for (size_t i = 0; i < playground.get_number_of_players(); ++i) {
        playground.set_new_base();
    }

    curr_id = entities_.size();

    for (uint16_t i = 0; i < playground.get_number_of_players(); i++) {
        std::string player_deck_file = get_players_decks_names().at(i);

        parser_.parse_json(entities_, player_deck_file);
        Player *player = static_cast<Player *>(get_by_id(i));

        for (size_t id = curr_id; id < entities_.size(); id++) {
            PlayerCard *card = static_cast<PlayerCard *>(get_by_id(id));
            card->change_owner(i);
            player->gain_card_on_start(card);
        }

        curr_id = entities_.size();

        player->take_card(5);
    }
}

void Engine::distribute_points(Base *base, LeaderBoard_t &leader_board) {
    uint32_t winner_num = 0;
    uint32_t prev_points = leader_board.front().second;
    uint32_t same_score = 1;

    for (auto &player_winner : leader_board) {
        Player *player = static_cast<Player *>(get_by_id(player_winner.first));

        if (player_winner.first == leader_board.front().first) {
            player->gain_points(base->get_points().at(winner_num));
            prev_points = player_winner.second;
            continue;
        } else if (prev_points == player_winner.second) {
            same_score += 1;
        } else {
            winner_num += same_score;
            same_score = 1;
        }

        if (winner_num >= NUMBER_OF_WINNERS) {
            break;
        }

        player->gain_points(base->get_points().at(winner_num));
    }
}

Engine::~Engine() {
    for (auto curr = entities_.begin(), end = entities_.end(); curr != end; ++curr) {
        delete (*curr);
    }
}

void Engine::dump_state(std::string file_name) const {
    std::ofstream os(file_name);

    os << "------------------------------------\n";
    os << "Dumping state of engine\n";
    os << "Turn: " << turn_ << "\n";
    os << "Time: " << time_ << "\n";

    os << "Dumping entities\n";
    for (auto curr = entities_.begin(), end = entities_.end(); curr != end; ++curr) {
        os << "\tId: " << (*curr)->get_id() << "\n";
    }

    playground.dump_state(os);

    os << "------------------------------------\n";
}

const std::vector<std::string> &Engine::get_players_decks_names() const {
    return players_decks_names_;
}

void Engine::set_players_decks_names(std::vector<std::string> &names) {
    players_decks_names_ = names;
}

const std::string &Engine::get_bases_deck_name() const {
    return bases_deck_;
}

void Engine::set_bases_deck_name(const std::string &name) {
    bases_deck_ = name;
}

} // namespace Mayhem
