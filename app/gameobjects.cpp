#include "gameobjects.h"

namespace
{
    /**
     * @brief Генерирует случайное число типа float в заданном диапазоне [min, max].
     *
     * Функция использует генератор случайных чисел для создания числа типа float
     * в заданном диапазоне. Используется равномерное распределение.
     *
     * @param min Минимальное значение диапазона.
     * @param max Максимальное значение диапазона.
     * @return Случайное число типа float в диапазоне [min, max].
     */
    float random_on_duration(float min, float max)
    {
        std::random_device rd;   // Используется для получения случайного стартового значения
        std::mt19937 gen(rd());  // Инициализация генератора случайных чисел Mersenne Twister
        std::uniform_real_distribution<float> dist(min, max);  // Определение равномерного распределения в диапазоне [min, max]
        return dist(gen);  // Генерация случайного числа
    }

    /**
     * @brief Настройка объекта Object с заданными параметрами игрового поля.
     *
     * Устанавливает направление, размер, позицию и скорость объекта.
     *
     * @param obj Объект, который нужно настроить.
     * @param game_board Прямоугольник, представляющий игровое поле.
     */
    void setting_object(Object& obj, const sf::FloatRect& game_board)
    {
        obj.set_direction(sf::Vector2f(0.f, 1.f));  ///< Установка направления движения вниз

        float size = random_on_duration(26, 45);
        obj.set_size(sf::Vector2f(size, size));  ///< Установка размера объекта

        // Генерация случайной позиции по оси X в пределах игрового поля
        float from = game_board.left;
        float to = game_board.left + game_board.width - size;
        float pos_x = random_on_duration(from, to);
         // Позиция по оси Y выше верхней границы игрового поля
        float pos_y = game_board.top - size;
        obj.set_position(sf::Vector2f(pos_x, pos_y));  ///< Установка позиции объекта

        float speed = random_on_duration(100.f, 150.f);
        obj.set_speed(speed);  ///< Установка скорости объекта
    }
}

// ================================================
// ===================== Blum =====================
// ================================================

// Статические переменные класса Blum для хранения текстур
sf::Texture Blum::ms_glow_tex;
sf::Texture Blum::ms_activ_tex;
sf::Texture Blum::ms_idle_tex;

/**
 * @brief Конструктор перемещения класса Blum.
 */
Blum::Blum(Blum&& other) noexcept
    : Object(std::move(other)) // Вызов конструктора перемещения базового класса Object
{
}

/**
 * @brief Оператор присваивания с перемещением класса Blum.
 */
Blum& Blum::operator=(Blum&& other) noexcept
{
    if (this != &other)
    {
        Object::operator=(std::move(other)); // Перемещаем базовый класс Object
    }
    return *this;
}

/**
 * @brief Конструктор класса Blum.
 *
 * Инициализирует объект Blum с заданными параметрами игрового поля.
 *
 * @param game_board Прямоугольник, представляющий игровое поле.
 */
Blum::Blum(const sf::FloatRect& game_board)
    : Object(ms_glow_tex, 15, 1000,  // Инициализация базового класса Object с glow текстурой, количеством спрайтов и задержкой
             ms_activ_tex, 3, 200,
             ms_idle_tex, 12, 200)
{
    setting_object(*this, game_board);
}

/**
 * @brief Загрузка ресурсов для класса Blum.
 *
 * Загружает текстуры из файлов и проверяет успешность загрузки.
 *
 * @return true, если все текстуры успешно загружены, иначе false.
 */
bool Blum::load_resources(void)
{
    bool success = true;

    if (!ms_glow_tex.loadFromFile("src/blum_glow.png"))  // Загрузка glow текстуры
        success = false;

    if (!ms_activ_tex.loadFromFile("src/blum_activ.png"))  // Загрузка active текстуры
        success = false;

    if (!ms_idle_tex.loadFromFile("src/blum.png"))  // Загрузка idle текстуры
        success = false;

    return success;
}

// ====================================================
// ===================== Ice ==========================
// ====================================================

// Статические переменные для хранения текстур класса Ice
sf::Texture Ice::ms_glow_tex;
sf::Texture Ice::ms_activ_tex;
sf::Texture Ice::ms_idle_tex;

/**
 * @brief Конструктор перемещения для класса Ice.
 */
Ice::Ice(Ice&& other) noexcept
    : Object(std::move(other)) // Вызов конструктора перемещения базового класса Object
{
}

/**
 * @brief Оператор присваивания с перемещением для класса Ice.
 */
Ice& Ice::operator=(Ice&& other) noexcept
{
    if (this != &other)
    {
        Object::operator=(std::move(other)); // Перемещение базового класса Object
    }
    return *this;
}

/**
 * @brief Конструктор для класса Ice.
 *
 * Инициализирует объект Ice с заданными параметрами игрового поля.
 *
 * @param game_board Прямоугольник, представляющий игровое поле.
 */
Ice::Ice(const sf::FloatRect& game_board)
    : Object(ms_glow_tex, 1, 1000,  // Инициализация базового класса Object с текстурой glow, количеством спрайтов и задержкой
             ms_activ_tex, 4, 200,
             ms_idle_tex, 9, 200)
{
    setting_object(*this, game_board); // Настройка объекта в пределах игрового поля
}

/**
 * @brief Загрузка ресурсов для класса Ice.
 *
 * Загружает текстуры из файлов и проверяет успешность загрузки.
 *
 * @return true, если все текстуры успешно загружены, иначе false.
 */
bool Ice::load_resources()
{
    bool success = true;

    if (!ms_glow_tex.loadFromFile("src/null.png"))
        success = false;

    if (!ms_activ_tex.loadFromFile("src/ice_activ.png"))
        success = false;

    if (!ms_idle_tex.loadFromFile("src/ice.png"))
        success = false;

    return success;
}
// ====================================================
// ===================== Bomb =========================
// ====================================================

// Статические переменные для хранения текстур класса Bomb
sf::Texture Bomb::ms_glow_tex;
sf::Texture Bomb::ms_activ_tex;
sf::Texture Bomb::ms_idle_tex;

/**
 * @brief Конструктор перемещения для класса Bomb.
 */
Bomb::Bomb(Bomb&& other) noexcept
    : Object(std::move(other)) // Вызов конструктора перемещения базового класса Object
{
}

/**
 * @brief Оператор присваивания с перемещением для класса Bomb.
 */
Bomb& Bomb::operator=(Bomb&& other) noexcept
{
    if (this != &other)
    {
        Object::operator=(std::move(other)); // Перемещение базового класса Object
    }
    return *this;
}

/**
 * @brief Конструктор для класса Bomb.
 *
 * Инициализирует объект Bomb с заданными параметрами игрового поля.
 *
 * @param game_board Прямоугольник, представляющий игровое поле.
 */
Bomb::Bomb(const sf::FloatRect& game_board)
    : Object(ms_glow_tex, 1, 1000,  // Инициализация базового класса Object с текстурой glow, количеством спрайтов и задержкой
             ms_activ_tex, 3, 200,
             ms_idle_tex, 7, 200)
{
    setting_object(*this, game_board); // Настройка объекта в пределах игрового поля
}

/**
 * @brief Загрузка ресурсов для класса Bomb.
 *
 * Загружает текстуры из файлов и проверяет успешность загрузки.
 *
 * @return true, если все текстуры успешно загружены, иначе false.
 */
bool Bomb::load_resources()
{
    bool success = true;

    if (!ms_glow_tex.loadFromFile("src/null.png"))
        success = false;

    if (!ms_activ_tex.loadFromFile("src/bomb_activ.png"))
        success = false;

    if (!ms_idle_tex.loadFromFile("src/bomb.png"))
        success = false;

    return success;
}
