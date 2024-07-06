#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "animation.h"

/**
 * @brief Класс для логики объекта.
 *
 * Определяет поведение и состояние объекта, такие как его положение, размер, направление и скорость.
 */
class ObjectLogic
{
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    explicit ObjectLogic(void) = default;

    /**
     * @brief Виртуальный деструктор по умолчанию.
     */
    virtual ~ObjectLogic() = default;

    /**
     * @brief Конструктор перемещения.
     */
    ObjectLogic(ObjectLogic&& other) noexcept = default;

    /**
     * @brief Оператор присваивания перемещением.
     */
    ObjectLogic& operator=(ObjectLogic&& other) noexcept = default;

    /**
     * @brief Получить прямоугольник, описывающий границы объекта.
     *
     * Метод возвращает объект sf::FloatRect, который описывает границы объекта
     * на основе текущей позиции и размера.
     *
     * @return Объект sf::FloatRect, описывающий границы объекта.
     */
    sf::FloatRect get_rect(void) const;

    /**
     * @brief Установить позицию объекта.
     *
     * @param new_pos Новая позиция объекта.
     */
    void set_position(const sf::Vector2f& new_pos);

    /**
     * @brief Установить размер объекта.
     *
     * @param new_size Новый размер объекта.
     */
    void set_size(const sf::Vector2f& new_size);

    /**
     * @brief Установить направление движения объекта.
     *
     * Метод нормализует вектор направления перед его установкой, чтобы его длина была равна единице.
     *
     * @param new_direct Новый вектор направления. Должен быть ненулевой длины для нормализации.
     */
    void set_direction(const sf::Vector2f& new_direct);

    /**
     * @brief Установить скорость движения объекта.
     *
     * @param new_speed Новая скорость объекта.
     */
    void set_speed(float new_speed);

    /**
     * @brief Проверить столкновение с точкой.
     *
     * Проверяет, находится ли заданная точка внутри границ объекта.
     *
     * @param pos Позиция для проверки на столкновение.
     * @return true, если произошло столкновение, иначе false.
     */
    bool check_collision(const sf::Vector2f& pos) const;

    /**
     * @brief Переместить объект.
     *
     * Вычисляет новую позицию объекта на основе текущего времени и скорости.
     *
     * @param cur_time Текущее время.
     * @return Новая позиция объекта.
     */
    sf::Vector2f move(int32_t cur_time);

private:
    sf::Vector2f m_direction;           ///< Направление движения объекта.
    sf::Vector2f m_cur_position;        ///< Текущая позиция объекта (центр).
    sf::Vector2f m_size;                ///< Размер объекта.
    float m_speed;                      ///< Скорость движения объекта.
    int32_t m_last_update_time = -1;    ///< Время последнего обновления состояния объекта.
};

/**
 * @brief Класс объекта с анимацией, который наследует логику из ObjectLogic и добавляет графический интерфейс
 *
 * Класс Object наследует функциональность из класса ObjectLogic и добавляет визуальное представление объекта.
 * Управляет отображением объекта в окне с использованием анимаций, таких как анимация свечения, активации и бездействия.
 */
class Object: private ObjectLogic
{
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    explicit Object(void) = default;

    /**
     * @brief Конструктор с параметрами.
     *
     * @param glow_tex Текстура для анимации свечения.
     * @param glow_n Количество спрайтов в анимации свечения.
     * @param glow_change_time Время смены спрайтов в анимации свечения.
     * @param activ_tex Текстура для анимации активации.
     * @param activ_n Количество спрайтов в анимации активации.
     * @param activ_change_time Время смены спрайтов в анимации активации.
     * @param idle_tex Текстура для анимации бездействия.
     * @param idle_n Количество спрайтов в анимации бездействия.
     * @param idle_change_time Время смены спрайтов в анимации бездействия.
     */
    explicit Object(sf::Texture& glow_tex, std::size_t glow_n, int32_t glow_change_time,
                    sf::Texture& activ_tex, std::size_t activ_n, int32_t activ_change_time,
                    sf::Texture& idle_tex, std::size_t idle_n, int32_t idle_change_time);

    /**
     * @brief Виртуальный деструктор по умолчанию.
     */
    virtual ~Object() = default;

    /**
     * @brief Конструктор перемещения.
     */
    Object(Object&& other) noexcept = default;

    /**
     * @brief Оператор присваивания перемещением.
     */
    Object& operator=(Object&& other) noexcept = default;

    /**
     * @brief Получить текущий статус объекта (жив или нет).
     *
     * @return true, если объект жив, false в противном случае.
     */
    bool get_status(void) const;

    /**
     * @brief Получить прямоугольник, описывающий границы объекта.
     *
     * Метод возвращает объект sf::FloatRect, который описывает границы объекта
     * на основе текущей позиции и размера.
     *
     * @return Объект sf::FloatRect, описывающий границы объекта.
     */
    sf::FloatRect get_rect(void) const;

    /**
     * @brief Установить позицию объекта.
     *
     * @param new_pos Новая позиция объекта.
     */
    void set_position(const sf::Vector2f& new_pos);

    /**
     * @brief Установить размер объекта.
     *
     * @param new_size Новый размер объекта.
     */
    void set_size(const sf::Vector2f& new_size);

    /**
     * @brief Установить направление движения объекта.
     *
     * Метод нормализует вектор направления перед его установкой, чтобы его длина была равна единице.
     * Нормализация вектора сохраняет его направление, но приводит его длину к единице.
     *
     * @param new_direct Новый вектор направления. Должен быть ненулевой длины для нормализации.
     */
    void set_direction(const sf::Vector2f& new_direct);

    /**
     * @brief Установить скорость движения объекта.
     *
     * @param new_speed Новая скорость движения объекта.
     */
    void set_speed(float new_speed);

    /**
     * @brief Выполнить перемещение объекта на основе текущего времени.
     *
     * @param cur_time Текущее время для вычисления перемещения.
     */
    void move(int32_t cur_time);

    /**
     * @brief Попытаться нажать объект по указанной позиции мыши.
     *
     * Запускает анимацию окончания, если нажатие по объекту произошло.
     *
     * @param mouse_pos Позиция мыши для проверки нажатия.
     * @return Возращает true если есть пересечение с объектом, иначе false
     */
    bool try_press(const sf::Vector2f& mouse_pos);

    /**
     * @brief Отрисовка объекта в окне.
     *
     * Если активная анимация выполняется, рисует спрайт этой анимации.
     * В противном случае отрисовывает спрайты для анимации покоя и свечения.
     *
     * @param window Окно для отрисовки.
     * @param cur_time Текущее время для анимации.
     */
    void draw(sf::RenderWindow& window, int32_t cur_time);

private:
    Animation m_glow_anim;          ///< Анимация свечения объекта.
    Animation m_activ_anim;         ///< Анимация активации объекта.
    Animation m_idle_anim;          ///< Анимация бездействия объекта.
    bool m_alive = true;            ///< Статус объекта (жив или нет).
    bool m_activated = false;       ///< Статус объекта (активирован или нет).
};

#endif // OBJECT_H
