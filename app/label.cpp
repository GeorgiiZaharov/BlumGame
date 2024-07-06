#include "label.h"


Label::Label(sf::Texture& tex, std::size_t n_sprites, int32_t change_time, const sf::Font& font)
    :m_anim(tex, n_sprites, change_time)
{
    m_text.setFont(font);
}

// Настройка параметров текста (цвет и размер)
void Label::set_string_settings(const sf::Color& color, std::size_t size, sf::Uint32 style)
{
    m_text.setFillColor(color);
    m_text.setCharacterSize(size);
    m_text.setStyle(style);
}

void Label::set_string_scale(float coefficient)
{
    m_text.setScale(1.f, 1.f); // сбрасываем старое масштабирование, чтобы оно не накладывалось с новым
    m_text.setScale(coefficient, coefficient); // устанавливаем новое масштабирование
}

// Установка размера изображения
void Label::set_picture_size(const sf::Vector2f& new_size)
{
    m_anim.resize(new_size);
}

// Установка позиции изображения
void Label::set_picture_position(const sf::Vector2f& new_pos)
{
    m_anim_position = new_pos;
}

// Установка позиции текста
void Label::set_string_position(const sf::Vector2f& new_pos)
{
    m_text.setPosition(new_pos);
}

// Установка текста
void Label::set_string(const std::string& new_string)
{
    m_text.setString(new_string);
}

// Получение прямоугольника, описывающего текст
sf::FloatRect Label::get_string_rect(void) const
{
    return m_text.getGlobalBounds();
}

// Отрисовка изображения и текста в окне
void Label::draw(sf::RenderWindow& window, int32_t cur_time)
{
    sf::Sprite tmp = m_anim.get_sprite(cur_time);
    tmp.setPosition(m_anim_position); // Позиционируем спрайт катринки (анимации)

    window.draw(tmp);
    window.draw(m_text);
}
