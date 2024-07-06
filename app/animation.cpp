#include "animation.h"

// ==========================================================
// ===================== AnimationLogic =====================
// ==========================================================

AnimationLogic::AnimationLogic(std::size_t n, int32_t change_time)
    : m_max_sprite_index(n),       // Установка максимального индекса спрайта
      m_change_time(change_time)  // Установка времени смены спрайтов
{
    if (m_max_sprite_index <= 0)
        throw std::runtime_error("Incorrect sprite num (probably error with download");
    if (m_change_time <= 0)
        throw std::runtime_error("Incorrect change time value");
}

void AnimationLogic::start(void)
{
    m_cur_sprite_index = 0;  ///< Сбрасываем индекс текущего спрайта в начало
    m_last_time = -1;        ///< Сбрасываем последнее время изменения
}

bool AnimationLogic::is_end(int32_t cur_time) const
{
    if (need_next_sprite(cur_time))
    {
        // Вычисляем индекс следующего спрайта с учетом циклической анимации
        std::size_t next_index = (m_cur_sprite_index + 1) % m_max_sprite_index;

        // Если вернулись в начало анимации, значит она закончилась
        if (next_index == 0)
        {
            return true;
        }
    }
    return false;
}

std::size_t AnimationLogic::get_current_sprite_index(int32_t cur_time)
{
    if (need_next_sprite(cur_time))
    {
        // Обновляем индекс текущего спрайта с учетом циклической анимации
        m_cur_sprite_index = (m_cur_sprite_index + 1) % m_max_sprite_index;
        // Обновляем последнее время изменения
        m_last_time = cur_time;

    }

    if (m_last_time == -1)// Устанавливаем начальное значение
    {
        m_last_time = cur_time;
    }

    return m_cur_sprite_index;
}

bool AnimationLogic::need_next_sprite(int32_t cur_time) const
{
    ///< Если последнее время было установлено и прошло достаточно времени для смены спрайта
    return m_last_time != -1 && cur_time - m_last_time >= m_change_time;
}

// =====================================================
// ===================== Animation =====================
// =====================================================

Animation::Animation(sf::Texture& tex, std::size_t n, int32_t change_time)
    : AnimationLogic(n, change_time) // Инициализация базового класса AnimationLogic
{
    ///> нарезаем текстуру на спрайты
    sf::Vector2u tex_size = tex.getSize();  // Получаем размер текстуры
    int one_frame_width = tex_size.x / n;  // Вычисляем ширину одного кадра (спрайта)
    sf::IntRect to_cut(0, 0, one_frame_width, tex_size.y);  // Инициализируем прямоугольник для разрезания текстуры
    m_sprites.reserve(n);   // Выделяем место в векторе для спрайтов

    for (std::size_t i = 0; i < n; ++i) {
        m_sprites.emplace_back(tex, to_cut); // Добавляем спрайт в конец вектора m_sprites

        to_cut.left += one_frame_width;  // Сдвигаем левую границу прямоугольника для следующего спрайта
    }
}

sf::Sprite Animation::get_sprite(int32_t cur_time)
{
    std::size_t index = get_current_sprite_index(cur_time);  // Получаем текущий индекс спрайта из базового класса
    return m_sprites[index];  // Возвращаем спрайт по текущему индексу
}

bool Animation::is_end(int32_t cur_time) const
{
    return AnimationLogic::is_end(cur_time);
}

void Animation::start(void)
{
    AnimationLogic::start();
}

void Animation::resize(const sf::Vector2f& new_size)
{
    std::for_each(m_sprites.begin(), m_sprites.end(), [&new_size](sf::Sprite& sprite) {
        sprite.setScale(1.f, 1.f);  // Сбрасываем масштаб спрайта

        sf::FloatRect sprite_bounds = sprite.getLocalBounds();  // Получаем локальные границы спрайта

        // Изменяем размер спрайта
        float imageScale_x = new_size.x / sprite_bounds.width;
        float imageScale_y = new_size.y / sprite_bounds.height;

        sprite.setScale(imageScale_x, imageScale_y);  // Применяем новый масштаб
    });
}
