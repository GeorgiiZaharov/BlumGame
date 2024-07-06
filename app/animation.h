#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>  // Для std::for_each
#include <stdexcept>

/**
 * @brief Класс для логики анимации, который не зависит от графического интерфейса.
 */
class AnimationLogic
{
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    AnimationLogic(void) = default;

    /**
     * @brief Конструктор с параметрами.
     * @param n Количество спрайтов в анимации.
     * @param change_time Время смены спрайтов в миллисекундах.
     * @throw std::runtime_error при некорректных данных (n должно быть > 0 и change_time должно быть > 0)
     */
    AnimationLogic(std::size_t n, int32_t change_time);

    /**
     * @brief Конструктор перемещения.
     * @param other Другой объект AnimationLogic для перемещения.
     */
    AnimationLogic(AnimationLogic&& other) noexcept = default;

    /**
     * @brief Виртуальный деструктор.
     */
    virtual ~AnimationLogic(void) = default;

    /**
     * @brief Оператор присваивания перемещением.
     * @param other Другой объект AnimationLogic для присваивания.
     * @return Ссылка на текущий объект AnimationLogic.
     */
    AnimationLogic& operator=(AnimationLogic&& other) noexcept = default;

    /**
     * @brief Метод для начала нециклической анимации с начала.
     */
    void start(void);

    /**
     * @brief Метод для возращения статуса нециклической анимации.
     * @param cur_time Текущее время в миллисекундах.
     * @return true если есть спрайт для этой анимации, иначе false
     */
    bool is_end(int32_t cur_time) const;

    /**
     * @brief Вычислить текущий индекс кадра на основе текущего времени.
     * @param cur_time Текущее время в миллисекундах.
     * @return Индекс текущего спрайта.
     */
    std::size_t get_current_sprite_index(int32_t cur_time);

private:
    /**
     * @brief Проверить, нужно ли переключить на следующий спрайт.
     * @param cur_time Текущее время в миллисекундах.
     * @return true, если нужно переключить на следующий спрайт, false в противном случае.
     */
    bool need_next_sprite(int32_t cur_time) const;

    std::size_t m_cur_sprite_index = 0; ///< Текущий индекс спрайта.
    std::size_t m_max_sprite_index; ///< Максимальный индекс спрайта.
    int32_t m_change_time;          ///< Время смены спрайта в миллисекундах.
    int32_t m_last_time = -1;            ///< Время последнего обновления спрайта в миллисекундах.
};

/**
 * @brief Класс для анимации, который наследует логику из AnimationLogic и добавляет графический интерфейс.
 */
class Animation : private AnimationLogic
{
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    explicit Animation(void) = default;

    /**
     * @brief Конструктор с параметрами.
     * @param tex Текстура для анимации.
     * @param n Количество спрайтов в текстуре.
     * @param change_time Время смены спрайтов в миллисекундах.
     */
    explicit Animation(sf::Texture& tex, std::size_t n, int32_t change_time);

    /**
     * @brief Конструктор перемещения.
     * @param other Другой объект Animation для перемещения.
     */
    explicit Animation(Animation&& other) noexcept = default;

    /**
     * @brief Оператор присваивания перемещением.
     * @param other Другой объект Animation для присваивания.
     * @return Ссылка на текущий объект Animation.
     */
    Animation& operator=(Animation&& other) noexcept = default;

    /**
     * @brief Деструктор.
     */
    ~Animation(void) override = default;

    /**
     * @brief Получить текущий спрайт на основе текущего времени. Изменяет m_is_running на false после демонстрации всех спрайтов.
     * @param cur_time Текущее время в миллисекундах.
     * @return Текущий спрайт.
     */
    sf::Sprite get_sprite(int32_t cur_time);

    /**
     * @brief Метод для возращения статуса нециклической анимации.
     * @param cur_time Текущее время в миллисекундах.
     * @return true если есть спрайт для этой анимации, иначе false
     */
    bool is_end(int32_t cur_time) const;

    /**
     * @brief Начать анимацию с начала.
     */
    void start(void);

    /**
     * @brief Изменить размер спрайтов анимации.
     * @param new_size Новый размер.
     */
    void resize(const sf::Vector2f& new_size);

private:
    std::vector<sf::Sprite> m_sprites; ///< Вектор спрайтов для анимации.
};

#endif // ANIMATION_H
