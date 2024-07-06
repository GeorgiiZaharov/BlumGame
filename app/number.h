#ifndef NUMBER_H
#define NUMBER_H

#include <SFML/Graphics.hpp>

/**
 * @class Number
 * @brief Класс, представляющий движущееся число с графическими свойствами.
 */
class Number
{
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    explicit Number(void) = default;

    /**
     * @brief Параметризированный конструктор.
     * @param rect Начальная позиция и размер числа.
     * @param n Целое число, которое будет отображаться.
     */
    explicit Number(const sf::FloatRect& rect, int n);

    /**
     * @brief Загружает необходимые ресурсы для класса Number.
     * @return true, если ресурсы успешно загружены, иначе false.
     */
    static bool load_resources(void);

    /**
     * @brief Перемещает число на основе текущего времени.
     * @param cur_time Текущее время, используемое для расчета движения.
     */
    void move(int32_t cur_time);

    /**
     * @brief Рисует число на указанном окне рендеринга.
     * @param window Окно рендеринга SFML, на котором будет нарисовано число.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Проверяет, активен ли номер.
     * @return true, если номер активен, иначе false.
     */
    bool get_status(void) const;

private:
    bool m_is_alive = true; /**< Указывает, активен ли номер. */
    sf::Vector2f m_cur_pos; /**< Текущее положение номера. */
    sf::Text m_text; /**< Объект текста SFML, представляющий номер. */
    const float mc_alpha_change_speed = 100.f; /**< Скорость, с которой номер исчезает. */
    const float mc_move_speed = 20.f; /**< Скорость, с которой номер перемещается. */
    const std::size_t mc_font_size = 32; /**< Размер шрифта номера. */
    int32_t m_last_upgrade_time = -1; /**< Время последнего обновления для плавного движения/исчезновения. */
    sf::Color m_cur_text_color; /**< Текущий цвет текста. */
    static sf::Font ms_font; /**< Статический шрифт, используемый для рендеринга номера. */
};

#endif // NUMBER_H
