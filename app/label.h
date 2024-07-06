#ifndef LABEL_H
#define LABEL_H

#include <SFML/Graphics.hpp>
#include <string>
#include "animation.h"

/**
 * @class Label
 * @brief Класс для управления текстовыми и графическими метками с возможностью анимации.
 */
class Label
{
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    explicit Label(void) = default;

    /**
     * @brief Параметризованный конструктор для создания метки с текстурой, анимацией и шрифтом.
     * @param tex Текстура для анимации.
     * @param n_sprites Количество спрайтов в анимации.
     * @param change_time Время смены спрайтов в анимации.
     * @param font Шрифт для текста метки.
     */
    explicit Label(sf::Texture& tex, std::size_t n_sprites, int32_t change_time, const sf::Font& font);

    /**
     * @brief Деструктор.
     */
    ~Label() = default;

    /**
     * @brief Конструктор перемещения.
     */
    Label(Label&& other) noexcept = default;

    /**
     * @brief Оператор присваивания перемещением.
     * @return Ссылка на текущий объект.
     */
    Label& operator=(Label&& other) noexcept = default;

    /**
     * @brief Установка параметров текста.
     * @param color Цвет текста.
     * @param size Размер текста.
     * @param style Стиль текста (обычный, жирный и т.д.).
     */
    void set_string_settings(const sf::Color& color = sf::Color::White, std::size_t size = 20, sf::Uint32 style = 0);

    /**
     * @brief Установка параметров текста.
     * @param coefficient коэффициент изменения по двум осям.
     */
    void set_string_scale(float coefficient);

    /**
     * @brief Установка размера изображения.
     * @param new_size Новый размер изображения.
     */
    void set_picture_size(const sf::Vector2f& new_size);

    /**
     * @brief Установка позиции изображения.
     * @param new_pos Новая позиция изображения.
     */
    void set_picture_position(const sf::Vector2f& new_pos);

    /**
     * @brief Установка позиции текста.
     * @param new_pos Новая позиция текста.
     */
    void set_string_position(const sf::Vector2f& new_pos);

    /**
     * @brief Установка текста.
     * @param new_string Новый текст.
     */
    void set_string(const std::string& new_string);

    /**
     * @brief Получение прямоугольника, описывающего текст.
     * @return Прямоугольник, описывающий текст.
     */
    sf::FloatRect get_string_rect(void) const;

    /**
     * @brief Отрисовка метки на окне.
     * @param window Окно для отрисовки.
     * @param cur_time Текущее время для управления анимацией.
     */
    void draw(sf::RenderWindow& window, int32_t cur_time);

private:
    sf::Vector2f m_anim_position; ///< Позиция анимации.
    Animation m_anim; ///< Картинка (анимация) метки.
    sf::Text m_text; ///< Текст метки.
};

#endif // LABEL_H
