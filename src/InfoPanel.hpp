#ifndef INFOPANEL_HPP_
#define INFOPANEL_HPP_

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <filesystem>

class InfoPanel final
{
  public:
    InfoPanel();
    ~InfoPanel();

    void loadFont(const std::filesystem::path& p);
    void setText(const std::string& str);

    const sf::Vector2f& getSize() const
    {
      return panel.getSize();
    }

    void setSize(const float x, const float y)
    {
      panel.setSize(sf::Vector2f(x, y));
    }

    const sf::Vector2f& getPosition() const
    {
      return panel.getPosition();
    }

    void setPosition(const float x, const float y)
    {
      panel.setPosition(sf::Vector2f(x, y));
    }

    const sf::Color& getTextColor() const
    {
      return txtInfo.getFillColor();
    }

    void setTextColor(const sf::Color& c)
    {
      txtInfo.setFillColor(c);
    }

    const int getTextSize() const
    {
      return txtInfo.getCharacterSize();
    }

    void setTextSize(const int size)
    {
      txtInfo.setCharacterSize(size);
    }

    void render(sf::RenderWindow* window);

  private:
    sf::RectangleShape panel;
    sf::Font font;
    sf::Text txtInfo;

    void init();
};

#endif /* INFOPANEL_HPP_ */
