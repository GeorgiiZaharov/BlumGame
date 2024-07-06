#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <SFML/Graphics.hpp>
#include <random>
#include "object.h"

// ================================================
// ===================== Blum =====================
// ================================================

/**
 * @class Blum
 * @brief Класс Blum, наследующий от Object.
 *
 * Класс представляет объект Blum, который может быть инициализирован
 * с использованием игрового поля. Включает методы для перемещения и
 * загрузки ресурсов.
 */
class Blum final: public Object
{
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    explicit Blum(void) = default;

    /**
     * @brief Деструктор по умолчанию.
     */
    ~Blum() override = default;

    /**
     * @brief Конструктор класса Blum.
     *
     * Инициализирует объект Blum с заданными параметрами игрового поля.
     *
     * @param game_board Прямоугольник, представляющий игровое поле.
     */
    explicit Blum(const sf::FloatRect& game_board);

    /**
     * @brief Конструктор перемещения класса Blum.
     */
    explicit Blum(Blum&& other) noexcept;

    /**
     * @brief Оператор присваивания с перемещением класса Blum.
     */
    Blum& operator=(Blum&& other) noexcept;

    /**
     * @brief Загрузка ресурсов для класса Blum.
     *
     * Загружает текстуры из файлов и проверяет успешность загрузки.
     *
     * @return true, если все текстуры успешно загружены, иначе false.
     */
    static bool load_resources();

private:
    static sf::Texture ms_glow_tex;   ///< Текстура для glow состояния
    static sf::Texture ms_activ_tex;  ///< Текстура для active состояния
    static sf::Texture ms_idle_tex;   ///< Текстура для idle состояния
};

// ===============================================
// ===================== Ice =====================
// ===============================================

/**
 * @class Ice
 * @brief Класс Ice, наследующий от Object.
 *
 * Класс представляет объект Ice, который может быть инициализирован
 * с использованием игрового поля. Включает методы для перемещения и
 * загрузки ресурсов.
 */
class Ice final: public Object
{
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    explicit Ice() = default;

    /**
     * @brief Конструктор класса Ice.
     *
     * Инициализирует объект Ice с заданными параметрами игрового поля.
     *
     * @param game_board Прямоугольник, представляющий игровое поле.
     */
    explicit Ice(const sf::FloatRect& game_board);

    /**
     * @brief Деструктор по умолчанию.
     */
    ~Ice() override = default;

    /**
     * @brief Конструктор перемещения класса Ice.
     */
    explicit Ice(Ice&& other) noexcept;

    /**
     * @brief Оператор присваивания с перемещением класса Ice.
     */
    Ice& operator=(Ice&& other) noexcept;

    /**
     * @brief Загрузка ресурсов для класса Ice.
     *
     * Загружает текстуры из файлов и проверяет успешность загрузки.
     *
     * @return true, если все текстуры успешно загружены, иначе false.
     */
    static bool load_resources();

private:
    static sf::Texture ms_glow_tex;   ///< Текстура для glow состояния
    static sf::Texture ms_activ_tex;  ///< Текстура для active состояния
    static sf::Texture ms_idle_tex;   ///< Текстура для idle состояния
};

// ================================================
// ===================== Bomb =====================
// ================================================

/**
 * @class Bomb
 * @brief Класс Bomb, наследующий от Object.
 *
 * Класс представляет объект Bomb, который может быть инициализирован
 * с использованием игрового поля. Включает методы для перемещения и
 * загрузки ресурсов.
 */
class Bomb final: public Object
{
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    explicit Bomb() = default;

    /**
     * @brief Конструктор класса Bomb.
     *
     * Инициализирует объект Bomb с заданными параметрами игрового поля.
     *
     * @param game_board Прямоугольник, представляющий игровое поле.
     */
    explicit Bomb(const sf::FloatRect& game_board);

    /**
     * @brief Деструктор по умолчанию.
     */
    ~Bomb() override = default;

    /**
     * @brief Конструктор перемещения класса Bomb.
     */
    explicit Bomb(Bomb&& other) noexcept;

    /**
     * @brief Оператор присваивания с перемещением класса Bomb.
     */
    Bomb& operator=(Bomb&& other) noexcept;

    /**
     * @brief Загрузка ресурсов для класса Bomb.
     *
     * Загружает текстуры из файлов и проверяет успешность загрузки.
     *
     * @return true, если все текстуры успешно загружены, иначе false.
     */
    static bool load_resources();

private:
    static sf::Texture ms_glow_tex;   ///< Текстура для glow состояния
    static sf::Texture ms_activ_tex;  ///< Текстура для active состояния
    static sf::Texture ms_idle_tex;   ///< Текстура для idle состояния
};

#endif // GAMEOBJECTS_H
