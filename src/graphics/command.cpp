#include "graphics/command.hpp"
#include "core/actions.h"
#include "core/base.h"
#include "core/deck.h"
#include "engine/engine.h"

namespace Mayhem {

Command::Command(GraphicsModel &m) : model(m) {}

void Command::set_card(PlayerCard *card) {
    if (!card)
        return;
    if (Action *action_card = dynamic_cast<Action *>(card); action_card) {
        events.push_back(std::make_pair(Type::action_on_hand, action_card));
        action_card->press();
    } else if (Minion *minion = dynamic_cast<Minion *>(card); minion) {
        events.push_back(std::make_pair(Type::minion_on_hand, minion));
        minion->press();
    }
    check_commands();
}

void Command::set_shown_card(PlayerCard *card) {
    if (!card)
        return;
    if (Action *action_card = dynamic_cast<Action *>(card); action_card) {
        events.push_back(std::make_pair(Type::action_on_base, action_card));
        action_card->press();
    } else if (Minion *minion = dynamic_cast<Minion *>(card); minion) {
        events.push_back(std::make_pair(Type::minion_on_base, minion));
        minion->press();
    }
    check_commands();
}

void Command::set_base(Base *base) {
    if (!base)
        return;
    events.push_back(std::make_pair(Type::base, dynamic_cast<Drawable *>(base)));
    base->press();
    model.attributes.shown_place.first = base;
    check_commands();
}

void Command::set_deck(Deck<PlayerCard *> *deck) {
    if (!deck)
        return;
    events.push_back(std::make_pair(Type::deck, dynamic_cast<Drawable *>(deck)));
    deck->press();
    check_commands();
}

void Command::set_button(Button::Type type) {
    switch (type) {
    case Button::Type::end_turn:
        clear();
        events.push_back(std::make_pair(Type::end_turn, nullptr));
        break;
    case Button::Type::close_window:
        clear();
        events.push_back(std::make_pair(Type::close_window, nullptr));
        break;
    default:
        break;
    }
    check_commands();
}

template <std::size_t N> Command::Status Command::is_this_command(const std::array<Type, N> &data) const {
    if (data.size() < events.size())
        return Status::different;

    auto data_it = data.begin();
    for (auto event_it = events.begin(); event_it != events.end(); ++event_it, ++data_it) {
        if (event_it->first != *data_it)
            return Status::different;
    }

    return (data.size() == events.size()) ? Status::same : Status::possible;
}

void Command::activate_move_action() {
    MoveAction *action_card = dynamic_cast<MoveAction *>(events[0].second);
    Base *base_from = dynamic_cast<Base *>(events[1].second);
    Minion *minion = dynamic_cast<Minion *>(events[2].second);
    Base *base_to = dynamic_cast<Base *>(events[3].second);
    Player *player = dynamic_cast<Player *>(model.engine.get_by_id(model.attributes.draw_player));

    if (player->get_actions_limit()) {
        if (model.engine.isOnline())
            model.engine.play_action_online(model.attributes.draw_player, action_card->get_id(), minion->get_id(),
                                            base_from->get_id(), base_to->get_id());
        else {
            model.engine.play_action(model.attributes.draw_player, action_card->get_id(), minion->get_id(),
                                     base_from->get_id(), base_to->get_id());
        }
    }
    clear();
}

void Command::activate_typical_action() {
    Action *action_card = dynamic_cast<Action *>(events[0].second);
    Base *base = dynamic_cast<Base *>(events[1].second);
    Minion *minion = dynamic_cast<Minion *>(events[2].second);
    Player *player = dynamic_cast<Player *>(model.engine.get_by_id(model.attributes.draw_player));

    if (player->get_actions_limit()) {
        if (model.engine.isOnline()) {
            model.engine.play_action_online(model.attributes.draw_player, action_card->get_id(), minion->get_id(),
                                            base->get_id(), 0);
        } else {
            model.engine.play_action(model.attributes.draw_player, action_card->get_id(), minion->get_id(), base->get_id(),
                                     0);
        }
    }
    clear();
}

void Command::activate_draw_action() {
    DrawAction *action_card = dynamic_cast<DrawAction *>(events[0].second);
    uint16_t player_id = model.attributes.draw_player;
    Player *player = dynamic_cast<Player *>(model.engine.get_by_id(player_id));

    if (player->get_actions_limit()) {
        if (model.engine.isOnline()) {
            model.engine.play_action_online(player_id, action_card->get_id(), 0, 0, 0);
        } else {
            model.engine.play_action(player_id, action_card->get_id(), 0, 0, 0);
        }
    }
    clear();
}

void Command::check_commands() {
    Status status = is_this_command<1>(close_window);
    switch (status) {
    case Status::same:
        model.attributes.window.close();
        clear();
        return;
    default:
        break;
    }

    switch (is_this_command<1>(end_turn)) {
    case Status::same:
        clear();
        if (model.engine.isOnline())
            model.engine.end_turn_online(model.attributes.draw_player);
        else
            model.attributes.draw_player = model.engine.end_turn(model.attributes.draw_player);
        return;
    case Status::possible:
        status = Status::possible;
        break;
    default:
        break;
    }

    switch (is_this_command<2>(choose_minion)) {
    case Status::same:
        events[0].second->release();
        events[0] = events[1];
        events[0].second->press();
        events.pop_back();
        status = Status::same;
        return;
    case Status::possible:
        status = Status::possible;
        return;
    default:
        break;
    }

    switch (is_this_command<2>(choose_base)) {
    case Status::same:
        events[0].second->release();
        events[0] = events[1];
        events[0].second->press();
        events.pop_back();
        status = Status::same;
        return;
    case Status::possible:
        status = Status::possible;
        return;
    default:
        break;
    }

    switch (is_this_command<2>(minion_to_base)) {
    case Status::same:
        if (model.engine.isOnline()) {
            model.engine.place_card_online(model.attributes.draw_player,
                                           dynamic_cast<Entity *>(events[0].second)->get_id(),
                                           dynamic_cast<Entity *>(events[1].second)->get_id());
        } else {
            model.engine.place_card(model.attributes.draw_player, dynamic_cast<Entity *>(events[0].second)->get_id(),
                                    dynamic_cast<Entity *>(events[1].second)->get_id());
        }

        clear();
        return;
    case Status::possible:
        status = Status::possible;
    default:
        break;
    }

    switch (is_this_command<4>(move_action)) {
    case Status::same:
        activate_move_action();
        return;
    case Status::possible:
        status = Status::possible;
    default:
        break;
    }

    switch (is_this_command<3>(action)) {
    case Status::same:
        if (dynamic_cast<MoveAction *>(events[0].second) == nullptr) {
            activate_typical_action();
            return;
        }
        break;
    case Status::possible:
        status = Status::possible;
    default:
        break;
    }

    switch (is_this_command<2>(draw_action)) {
    case Status::same:
        if (dynamic_cast<DrawAction *>(events[0].second)) {
            activate_draw_action();
            return;
        }
        break;
    case Status::possible:
        status = Status::possible;
    default:
        break;
    }

    if (status == Status::different) {
        clear();
    }
}

void Command::clear() {
    for (auto it : events) {
        if (it.first != Type::end_turn && it.first != Type::close_window) {
            it.second->release();
        }
    }
    model.attributes.popping_up_card = nullptr;
    model.attributes.shown_place.first = nullptr;
    model.attributes.shown_place.second.clear();
    events.clear();
}

} // namespace Mayhem
