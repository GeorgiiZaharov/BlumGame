#include <boost/test/included/unit_test.hpp>
#include <SFML/Graphics.hpp>

#include "object.h"

/**
 * @brief Тестирование установки позиции и размера объекта.
 *
 * Этот тест проверяет, корректно ли устанавливается позиция и размер объекта,
 * а также правильность вычисления границ объекта.
 */
BOOST_AUTO_TEST_CASE(test_set_position)
{
    // Создаем объект ObjectLogic
    ObjectLogic obj;

    // Задаем новую позицию и размер
    sf::Vector2f new_pos(10.0f, 20.0f);
    sf::Vector2f new_size(42.0f, 42.0f);

    // Устанавливаем позицию и размер объекта
    obj.set_position(new_pos);
    obj.set_size(new_size);

    // Проверяем, что границы объекта соответствуют установленным значениям
    BOOST_CHECK_EQUAL(obj.get_rect().left, new_pos.x);
    BOOST_CHECK_EQUAL(obj.get_rect().top, new_pos.y);
    BOOST_CHECK_EQUAL(obj.get_rect().width, new_size.x);
    BOOST_CHECK_EQUAL(obj.get_rect().height, new_size.y);
}

/**
 * @brief Тестирование проверки столкновений объекта с точкой.
 *
 * Этот тест проверяет, корректно ли метод check_collision определяет,
 * находится ли заданная точка внутри границ объекта или нет.
 * Объекту задается позиция и размер, затем проверяются точки, одна из которых
 * находится внутри объекта, а другая снаружи.
 */
BOOST_AUTO_TEST_CASE(test_check_collision)
{
    // Создаем объект ObjectLogic
    ObjectLogic obj;

    // Задаем позицию и размер объекта
    sf::Vector2f position(50.0f, 50.0f);
    sf::Vector2f size(100.0f, 100.0f);
    obj.set_position(position);
    obj.set_size(size);

    // Точки для проверки
    sf::Vector2f point_inside(60.0f, 60.0f);  // Точка внутри объекта
    sf::Vector2f point_outside(200.0f, 200.0f);  // Точка снаружи объекта

    // Проверяем, что метод check_collision правильно определяет положение точек
    BOOST_CHECK(obj.check_collision(point_inside));  // Точка должна быть внутри
    BOOST_CHECK(!obj.check_collision(point_outside));  // Точка должна быть снаружи
}

/**
 * @brief Тестирование перемещения объекта.
 *
 * Этот тест проверяет, корректно ли объект перемещается на основе заданного
 * направления, скорости и времени. Объекту задаются начальная позиция,
 * направление движения и скорость. Затем проверяется, правильно ли вычисляется
 * новая позиция объекта через заданный интервал времени.
 */
BOOST_AUTO_TEST_CASE(test_move)
{
    // Создаем объект ObjectLogic
    ObjectLogic obj;

    // Задаем начальную позицию и направление
    sf::Vector2f position(0.0f, 0.0f);
    sf::Vector2f direction(1.0f, 0.0f);  // Направление вдоль оси X
    obj.set_position(position);
    obj.set_direction(direction);
    obj.set_speed(2.0f);  // Устанавливаем скорость

    // Временные метки
    int32_t initial_time = 0;
    int32_t later_time = 1000;  // Прошло 1 секунда

    // Перемещаем объект и проверяем его новую позицию
    obj.move(initial_time);  // Начальная установка времени
    sf::Vector2f new_position = obj.move(later_time);  // Перемещение через 1 секунду

    // Проверяем, что объект переместился на правильное расстояние
    BOOST_CHECK_CLOSE(new_position.x, 2.0f, 0.001);  // Ожидаемое смещение вдоль оси X
    BOOST_CHECK_CLOSE(new_position.y, 0.0f, 0.001);  // Смещение вдоль оси Y должно быть 0
}
