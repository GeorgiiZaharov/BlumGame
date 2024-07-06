#ifndef GAMELABELS_H
#define GAMELABELS_H

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <string>

#include "label.h"

// =======================================================
// ===================== Timer label =====================
// =======================================================

/**
 * @class TimerLabel
 * @brief Класс для отображения и управления таймером в игре.
 */
class TimerLabel
{
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    explicit TimerLabel(void) = default;

    /**
     * @brief Конструктор с указанием игрового поля.
     * @param game_board Положение и размеры игрового поля.
     */
    explicit TimerLabel(const sf::FloatRect& game_board);

    /**
     * @brief Активирует эффект "заморозки".
     */
    void ice(void);

    /**
     * @brief Устанавливает текущее время.
     * @param cur_time Текущее время.
     */
    void set_time(int32_t cur_time);

    /**
     * @brief Отрисовывает метку таймера на окне.
     * @param window Окно, в котором будет производиться отрисовка.
     * @param cur_time Текущее время в игре.
     */
    void draw(sf::RenderWindow& window, int32_t cur_time);

    /**
     * @brief Загружает ресурсы, необходимые для отображения таймера.
     * @return true, если ресурсы успешно загружены, false в противном случае.
     */
    static bool load_resources(void);

private:
    /**
     * @brief Форматирует время в секундах в строку вида "MM:SS".
     * @param seconds Время в секундах.
     * @return Форматированная строка.
     */
    std::string formatSeconds(int seconds);

    /**
     * @brief Вычисляет позицию текста по оси X.
     * @return Позиция текста по оси X.
     */
    float calc_text_x_position(void);

    /**
     * @brief Вычисляет позицию текста по оси Y.
     * @return Позиция текста по оси Y.
     */
    float calc_text_y_position(void);

    /**
     * @brief Вычисляет позицию изображения по оси X.
     * @return Позиция изображения по оси X.
     */
    float calc_pic_x_position(void);

    /**
     * @brief Вычисляет позицию изображения по оси Y.
     * @return Позиция изображения по оси Y.
     */
    float calc_pic_y_position(void);

    /**
     * @brief Устанавливает настройки для метки.
     * такие как: цвет текста, размер текста, позицию текста, стиль текста,
     * размер картинки позицию картинки
     * @param label - метка которую нужно настроить.
     */
    void label_settings(Label& label);

    Label m_label_idle;                ///< Метка в нормальном состоянии.
    Label m_label_ice;                 ///< Метка в состоянии "заморозка".
    bool m_is_ice = false;             ///< Флаг состояния "заморозка".
    sf::FloatRect m_game_board;        ///< Прямоугольник игрового поля.
    int32_t m_start_ice_time = -1;     ///< Время начала эффекта "заморозка".
    const float mc_picture_size_w = 136.f; ///< Ширина заднего фона для таймера
    const float mc_picture_size_h = 46.f; ///< Высота заднего фона для таймера.
    const int32_t mc_ice_time = 2000;  ///< Время эффекта "заморозка" (2 сек).
    const std::size_t mc_font_size = 35; ///< Стандартный размер шрифта.
    static sf::Texture ms_timer_idle_anim_tex; ///< Текстура для нормального состояния.
    static sf::Texture ms_timer_ice_anim_tex; ///< Текстура для состояния "заморозка".
    static sf::Font ms_timer_font; ///< Шрифт для отображения таймера.
};

// =======================================================
// ===================== Score label =====================
// =======================================================

/**
 * @class ScoreLabel
 * @brief Класс для отображения и управления меткой очков в игре.
 */
class ScoreLabel
{
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    explicit ScoreLabel(void) = default;

    /**
     * @brief Конструктор с указанием игрового поля.
     * @param game_board Положение и размеры игрового поля.
     */
    explicit ScoreLabel(const sf::FloatRect& game_board);

    /**
     * @brief Устанавливает текущее количество очков.
     * @param cur_score Текущее количество очков.
     */
    void set_score(std::size_t cur_score);

    /**
     * @brief Активирует эффект "взрыва".
     */
    void boom(void);

    /**
     * @brief Отрисовывает метку на окне.
     * @param window Окно, в котором будет производиться отрисовка.
     * @param cur_time Текущее время в игре.
     */
    void draw(sf::RenderWindow& window, int32_t cur_time);

    /**
     * @brief Загружает ресурсы, необходимые для отображения метки.
     * @return true, если ресурсы успешно загружены, false в противном случае.
     */
    static bool load_resources(void);

    /**
     * @brief Устанавливает настройки для метки.
     * такие как: цвет текста, размер текста, позицию текста, стиль текста,
     * размер картинки позицию картинки
     * @param label - метка которую нужно настроить.
     */
    void label_settings(Label& label);

private:
    /**
     * @brief Вычисляет позицию текста по оси X.
     * @param hitbox Прямоугольник, определяющий границы игрового поля.
     * @return Позиция текста по оси X.
     */
    float calc_text_x_position(const sf::FloatRect& hitbox);

    /**
     * @brief Вычисляет позицию текста по оси Y.
     * @return Позиция текста по оси Y.
     */
    float calc_text_y_position(void);

    /**
     * @brief Вычисляет позицию изображения по оси X.
     * @param hitbox Прямоугольник, определяющий границы игрового поля.
     * @return Позиция изображения по оси X.
     */
    float calc_pic_x_position(const sf::FloatRect& hitbox);

    /**
     * @brief Вычисляет позицию изображения по оси Y.
     * @return Позиция изображения по оси Y.
     */
    float calc_pic_y_position(const sf::FloatRect& hitbox);

    /**
     * @brief Вычисляет текущую позицию метки.
     * @return Вектор, содержащий текущую позицию метки.
     */
    sf::Vector2f calc_cur_label_position(void);

    /**
     * @brief Обновляет изображение метки.
     * @param label Ссылка на объект метки.
     */
    void update_picture(Label& label);

    Label m_label_idle;                ///< Метка в нормальном состоянии.
    Label m_label_boom;                ///< Метка в состоянии "взрыв".
    bool m_is_score_changed = false;   ///< Флаг изменения очков.
    bool m_is_boom = false;            ///< Флаг состояния "взрыв".
    sf::FloatRect m_game_board;        ///< Прямоугольник игрового поля.
    float m_cur_increase_cof = 1.f;  ///< Текущий размер увеличения шрифта.
    std::size_t m_prev_score = -1;     ///< Предыдущее количество очков.
    int32_t m_start_increase_time = -1; ///< Время начала увеличения.
    int32_t m_start_boom_time = -1;     ///< Время начала эффекта "взрыв".

    const std::size_t mc_font_size = 35; ///< Стандартный размер шрифта.
    const int32_t mc_increase_time = 500; ///< Время увеличения (0.5 сек).
    const float mc_increase_cof_per_sec = 0.5f; ///< Интервал увеличения текста (каждую секунду увеличивается на 5%).
    const int32_t mc_boom_time = 500; ///< Время эффекта "взрыв" (0.5 сек).
    static sf::Texture ms_score_idle_anim_tex; ///< Текстура для нормального состояния.
    static sf::Texture ms_score_boom_anim_tex; ///< Текстура для состояния "взрыв".
    static sf::Font ms_score_font; ///< Шрифт для отображения очков.
};

#endif // GAMELABELS_H
