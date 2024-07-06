#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include <SFML/Graphics.hpp>
#include <list>
#include <map>
#include <random> // для использования случайных чисел

#include "animation.h"
#include "gameobjects.h"
#include "gamelabels.h"
#include "number.h"

/**
 * @brief Класс, отвечающий за отрисовку игры.
 *
 * Этот класс управляет отрисовкой и игровой логикой игры.
 */
class GameRenderer
{
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    explicit GameRenderer(void) = default;

    /**
     * @brief Конструктор с указанием размеров игрового поля.
     * @param game_board Прямоугольник, задающий границы игрового поля.
     */
    explicit GameRenderer(const sf::FloatRect& game_board);

    /**
     * @brief Деструктор по умолчанию.
     */
    ~GameRenderer() = default;

    /**
     * @brief Обновляет состояние игры на основе текущего времени.
     * @param cur_time Текущее время в миллисекундах.
     */
    void update(int32_t cur_time);

    /**
     * @brief Обрабатывает событие клика мыши.
     * @param mouse_pos Позиция клика мыши.
     */
    void click(const sf::Vector2f& mouse_pos);

    /**
     * @brief Проверяет, завершена ли игра.
     * @return True, если игра завершена, false в противном случае.
     */
    bool is_game_over(void) const;

    /**
     * @brief Отрисовывает игровые объекты на окне.
     * @param window Окно SFML для отрисовки.
     * @param cur_time Текущее время в миллисекундах.
     */
    void draw(sf::RenderWindow& window, int32_t cur_time);

    /**
     * @brief Загружает игровые ресурсы.
     * @return True, если ресурсы были успешно загружены, false в противном случае.
     */
    static bool load_resources(void);

private:
    /**
     * @brief Удаляет объекты, которые погибли.
     */
    void delete_died_objects(void);

    /**
     * @brief Создает новые игровые объекты.
     */
    void spawn_objects(void);

    /**
     * @brief Выполняет перемещение элементов в зависимости от текущего времени.
     * @param cur_time Текущее время в миллисекундах.
     */
    void make_movement(int32_t cur_time);

    /**
     * @brief Обновляет метки (лейблы) на основе текущего времени.
     * @param cur_time Текущее время в миллисекундах.
     */
    void update_labels(int32_t cur_time);

    /**
     * @brief Замораживает элементы игры.
     */
    void freeze_elements(void);

    /**
     * @brief Размораживает элементы игры.
     */
    void unfreeze_elements(void);

    /**
     * @brief Удаляет элементы, которые покинули экран.
     * @tparam T Тип элементов в списке.
     * @param list Список элементов для обработки.
     */
    template <typename T>
    void remove_departed_elements(std::list<T>& list);

    /**
     * @brief Удаляет элементы, которые погибли.
     * @tparam T Тип элементов в списке.
     * @param list Список элементов для обработки.
     */
    template <typename T>
    void remove_died_elements(std::list<T>& list);

    /**
     * @brief Перемещает элементы в зависимости от текущего времени.
     * @tparam T Тип элементов в списке.
     * @param list Список элементов для перемещения.
     * @param cur_time Текущее время в миллисекундах.
     */
    template <typename T>
    void move_elements(std::list<T>& list, int32_t cur_time) const;

    /**
     * @brief Изменяет направление движения элементов.
     * @tparam T Тип элементов в списке.
     * @param list Список элементов для обработки.
     * @param direct Новый вектор направления.
     */
    template <typename T>
    void change_direction_elements(std::list<T>& list, const sf::Vector2f& direct) const;

    /**
     * @brief Определяет, должен ли объект появиться на основе вероятности.
     * @param chance Вероятность появления объекта (от 0 до 1000).
     * @return True, если объект должен появиться, false в противном случае.
     */
    bool should_spawn_object(std::size_t chance) const;

    bool m_is_freezing = false; ///< Флаг, указывающий на нахождение игры в режиме заморозки.
    bool m_is_boom = false; ///< Флаг, указывающий на наличие взрыва в игре.

    int m_cash = 0; ///< Внутриигровая валюта игрока.

    const int32_t mc_freeze_time = 2000; ///< Продолжительность заморозки в миллисекундах (2 секунды).
    const int32_t mc_match_time = 45000; ///< Общее время матча в миллисекундах (45 секунд).

    int32_t m_start_time = -1; ///< Время начала игры.
    int32_t m_time_passed = 0; ///< Прошедшее время с начала игры.
    int32_t m_time_in_freezing_mode = 0; ///< Время, проведенное в режиме заморозки.
    int32_t m_last_freeze_time = -1; ///< Последнее время, когда была заморозка.
    int32_t m_freeze_start_time = -1; ///< Время начала заморозки.

    sf::FloatRect m_game_board; ///< Прямоугольник, определяющий область игрового поля.

    std::list<Blum> m_blums; ///< Список объектов типа Blum в игре.
    std::list<Ice> m_ices; ///< Список объектов типа Ice в игре.
    std::list<Bomb> m_bombs; ///< Список объектов типа Bomb в игре.

    std::size_t m_bomb_probability = 2; ///< Вероятность появления бомб (от 0 до 1000).
    std::size_t m_ice_probability = 2; ///< Вероятность появления льда (от 0 до 1000).
    std::size_t m_blum_probability = 60; ///< Вероятность появления Blum (от 0 до 1000).

    std::list<Number> m_numbers; ///< Список объектов типа Number в игре.

    std::map<std::string, std::size_t, std::less<>> statistics =///< Карта для хранения игровой статистики.
    {
        {"miss", 0},
        {"bomb", 0},
        {"ice",  0},
        {"blum", 0}
    };
    Animation m_background_anim; ///< Анимация для фона.
    Animation m_frozen_background_anim; ///< Анимация для замороженного фона.
    Animation m_boom_background_anim; ///< Анимация для взрывающегося фона.

    ScoreLabel m_score; ///< Лейбл счета, отображающий счет игрока.
    TimerLabel m_timer; ///< Лейбл таймера, отображающий игровое время.

    static sf::Texture ms_background_tex; ///< Статическая текстура для фона.
    static sf::Texture ms_frozen_background_tex; ///< Статическая текстура для замороженного фона.
    static sf::Texture ms_boom_background_tex; ///< Статическая текстура для взрывающегося фона.

    static std::mt19937 ms_gen; ///< Статический генератор случайных чисел Mersenne Twister.
    static std::uniform_int_distribution<std::size_t> ms_dist; ///< Статическое равномерное распределение.
};

#endif // GAMERENDERER_H
