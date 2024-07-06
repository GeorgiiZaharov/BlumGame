#include <boost/test/included/unit_test.hpp>
#include "animation.h"

/**
 * @brief Тест получения текущего индекса спрайта.
 */
BOOST_AUTO_TEST_CASE(GetCurrentSpriteIndex) {
    AnimationLogic anim(5, 100);

    // Симуляция времени и проверка индекса спрайта
    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(50), 0);   ///< До времени смены спрайта
    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(150), 1);  ///< После времени смены спрайта
}

/**
 * @brief Тест циклической анимации.
 */
BOOST_AUTO_TEST_CASE(LoopingAnimation) {
    AnimationLogic anim(2, 50);

    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(0), 0);    ///< Начальный индекс
    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(50), 1);   ///< Первая смена спрайта
    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(150), 0);  ///< Возвращение к началу после цикла
}

/**
 * @brief Тест сброса старой анимации и начала новой.
 */
BOOST_AUTO_TEST_CASE(StartNewAnimation) {
    AnimationLogic anim(3, 50);

    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(0), 0);    ///< Начальный индекс
    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(50), 1);   ///< Первая смена спрайта
    anim.start();
    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(150), 0);  ///< Возвращаемся к началу
}

/**
 * @brief Тест концовки не циклической анимации положительный.
 */
BOOST_AUTO_TEST_CASE(EndNoCicleAnimationTrue) {
    AnimationLogic anim(3, 50);

    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(0), 0);    ///< Начальный индекс
    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(50), 1);   ///< Первая смена спрайта
    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(100), 2);  ///< Возвращаемся к началу
    BOOST_CHECK_EQUAL(anim.is_end(150), true); ///< Спрайтов для этой анимации больше нет
}

/**
 * @brief Тест концовки не циклической анимации отрицательный.
 */
BOOST_AUTO_TEST_CASE(EndNoCicleAnimationFalse) {
    AnimationLogic anim(3, 50);

    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(0), 0);    ///< Начальный индекс
    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(50), 1);   ///< Первая смена спрайта
    BOOST_CHECK_EQUAL(anim.is_end(101), false); ///< Спрайтов для этой анимации больше нет
}

/**
 * @brief Тест остановки анимации.
 */
BOOST_AUTO_TEST_CASE(StopAnimation) {
    AnimationLogic anim(2, 100);

    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(0), 0);  ///< Запускаем анимацию

    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(200), 1);  ///< Достигаем конца анимации

    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(300), 0);  ///< Проверяем, что попали в начало
}

/**
 * @brief Дополнительный тест на сценарий запуска анимации после остановки.
 */
BOOST_AUTO_TEST_CASE(RestartAnimationAfterStop) {
    AnimationLogic anim(2, 100);

    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(0), 0);    ///< Начальный индекс
    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(200), 1);  ///< Достигаем конца анимации
    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(300), 0);  ///< Проверяем возвращение к началу

    anim.start();  ///< Запускаем анимацию снова
    BOOST_CHECK_EQUAL(anim.get_current_sprite_index(400), 0);  ///< Проверяем первую смену спрайта после запуска
}
