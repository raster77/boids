#include <InfoPanel.hpp>

InfoPanel::InfoPanel()
{
  init();
}

InfoPanel::~InfoPanel()
{
}

void InfoPanel::loadFont(const std::filesystem::path& p)
{
  if(std::filesystem::exists(p))
  {
    font.loadFromFile(p.string());
  }
}

void InfoPanel::setText(const std::string& str)
{
  txtInfo.setString(str);
}

void InfoPanel::render(sf::RenderWindow* window)
{
  window->draw(panel);
  window->draw(txtInfo);
}

void InfoPanel::init()
{
  panel.setPosition(0.f, 0.f);
  panel.setSize(sf::Vector2f(140.f, 80.f));
  panel.setFillColor(sf::Color(50, 50, 50, 100));
  txtInfo.setFont(font);
  txtInfo.setCharacterSize(12);
  txtInfo.setFillColor(sf::Color::White);
  txtInfo.setPosition(5.f, 5.f);
}

