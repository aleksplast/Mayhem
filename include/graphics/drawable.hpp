#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Mayhem {

/// class describing the objects to be drawn
class Drawable {
  protected:
#ifdef DEBUG
    std::string texture_name;
#endif

    /// @brief Main texture of button
    sf::Texture main_texture = sf::Texture();
    /// @brief Extra texture of button
    sf::Texture extra_texture = sf::Texture();
    /// @brief button pressing flag
    bool is_pressed = false;

  public:
    /// @brief Button sprite
    sf::Sprite sprite = sf::Sprite();

  public:
    /// @brief Constructor
    Drawable() = default;
    /// @brief Constructor
    /// @param[in] main_file Name file with main texture
    /// @param[in] extra_file Name file with extra texture
    Drawable(const std::string &main_file, const std::string &extra_file = "");

    /// @brief Draw entity on the window
    /// @param[out] window Window
    /// @param[in] rect Boundaries
    /// @param[in] angle Angle
    virtual void draw(sf::RenderWindow &window, const sf::FloatRect &rect, const float angle);

    /// @brief Set main texture
    void set_main_texture();

    /// @brief Set extra texture
    void set_extra_texture();

    /// @brief Clicks on the entity
    void press();

    /// @brief Disable entity selection
    void release();

    /// @brief Destructor
    virtual ~Drawable() = default;
}; // class Drawable

} // namespace Mayhem

#endif // DRAWABLE_H
