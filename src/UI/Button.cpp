#include "Button.h"
#include "UiConfig.h"

#include "SoundManager.h"

Button::Button(const sf::Font& font, ButtonType type) :m_text(font)
{
  setButtonTextByType(type);
	m_background.setFillColor(sf::Color::Transparent);
}

void Button::draw(WindowManager& window)
{
	window.draw(m_background);
	window.draw(m_text);
}

void Button::handlHover(const sf::Vector2f& hoverPos)
{
	if (isContain(hoverPos))
	{
		if (!m_isHover)
		{
			SoundManager::instance().playSound(SoundType::GTA_MENU);
			m_text.setFillColor(sf::Color::Black);
			m_background.setFillColor(sf::Color::White);
			m_isHover = true;
		}
	}
	else
	{
		m_text.setFillColor(sf::Color::White);
		m_background.setFillColor(sf::Color::Transparent);
		m_isHover = false;
	}

}

ButtonType Button::handlClick(const sf::Vector2f& clickPos)
{
	if (isContain(clickPos))
	{
		return m_type;
	}

	return ButtonType::NONE;
}

sf::FloatRect Button::getLocalBounds() const
{
	return m_background.getLocalBounds();
}

sf::FloatRect Button::getGlobalBounds() const
{
	return m_background.getGlobalBounds();
}

void Button::setScale(const sf::Vector2f& s)
{
	m_text.setScale({ s.x,s.y });
	m_background.setScale({ s.x,s.y });
}

void Button::setButtonType(ButtonType type)
{
	m_type = type;
	setButtonTextByType(type);
}

void Button::setPos(float x, float y)
{
	m_text.setPosition({ x,y });
	m_background.setPosition({ x,y });
}

void Button::setSizeAndOrigin(float fontSize)
{
	m_text.setCharacterSize(fontSize);

	sf::FloatRect bound = m_text.getLocalBounds();

	m_text.setOrigin({ bound.position.x + bound.size.x / 2, bound.position.y + bound.size.y / 2 });

	float paddingX = UiConfig::BUTTON_PAD_X * bound.size.x;
	float paddingY = UiConfig::BUTTON_PAD_Y * bound.size.y;

	m_background.setSize({ bound.size.x + paddingX, +bound.size.y + paddingY });

	m_background.setOrigin({ m_background.getSize().x / 2,m_background.getSize().y / 2 });
}

bool Button::isContain(const sf::Vector2f& pos)
{
	return m_background.getGlobalBounds().contains(pos);
}

void Button::setButtonTextByType(ButtonType type)
{
	switch (type)
	{
	case ButtonType::START:
		m_text.setString(std::string(UiConfig::START_STR));
		break;
	case ButtonType::HELP:
		m_text.setString(std::string(UiConfig::HELP_STR));
		break;
	case ButtonType::EXIT:
		m_text.setString(std::string(UiConfig::EXIT_STR));
		break;
	default:
		break;
	}
}
