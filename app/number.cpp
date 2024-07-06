#include "number.h"

// Инициализация статического члена
sf::Font Number::ms_font;

Number::Number(const sf::FloatRect& rect, int n)
{
    // Установка шрифта для текста
    m_text.setFont(ms_font);
    // Установка размера шрифта для текста
    m_text.setCharacterSize(mc_font_size);

    // Настройка текста в зависимости от значения n
    if (n < 0)
    {
        // Если число отрицательное, просто отображаем его
        m_text.setString(std::to_string(n));
        // Красный цвет для отрицательных чисел
        m_cur_text_color = sf::Color::Red;
    }
    else
    {
        // Если число положительное, добавляем плюс перед числом
        m_text.setString("+" + std::to_string(n));
        // Желтый цвет для положительных чисел
        m_cur_text_color = sf::Color::Yellow;
    }
    // Установка стиля текста на жирный
    m_text.setStyle(sf::Text::Bold);
    // Установка цвета текста
    m_text.setFillColor(m_cur_text_color);

    // Центрирование текста в пределах заданного прямоугольника
    sf::FloatRect textRect = m_text.getLocalBounds();
    float text_pos_x = rect.left + (rect.width - textRect.width) / 2.f;
    float text_pos_y = rect.top + (rect.height - textRect.height) / 2.f;
    m_cur_pos = sf::Vector2f(text_pos_x, text_pos_y);
    m_text.setPosition(m_cur_pos);
}

bool Number::load_resources(void)
{
    // Загрузка ресурса шрифта из файла
    return ms_font.loadFromFile("./src/Consolas.ttf");
}

void Number::move(int32_t cur_time)
{
    if (m_last_upgrade_time < 0) {
        // Если это первое обновление, устанавливаем текущее время как время последнего обновления
        m_last_upgrade_time = cur_time;
    }

    // Вычисление разницы времени с последнего обновления
    int32_t time_diff = cur_time - m_last_upgrade_time;
    // Преобразование разницы времени в секунды
    float time_diff_sec = time_diff / 1000.f;

    // Обновление позиции числа по вертикали на основании времени
    m_cur_pos.y -= mc_move_speed * time_diff_sec;
    m_text.setPosition(m_cur_pos);

    // Обновление альфа-канала (прозрачности) для постепенного исчезновения текста
    int alpha = static_cast<int>(m_cur_text_color.a - mc_alpha_change_speed * time_diff_sec);
    if (alpha < 0) {
        alpha = 0;
        // Пометить число как неактивное, если оно полностью прозрачное
        m_is_alive = false;
    }
    m_cur_text_color.a = static_cast<sf::Uint8>(alpha);
    m_text.setFillColor(m_cur_text_color);

    // Обновление времени последнего обновления
    m_last_upgrade_time = cur_time;
}

void Number::draw(sf::RenderWindow& window) const
{
    // Отрисовка текста в окне рендеринга
    window.draw(m_text);
}

bool Number::get_status(void) const
{
    // Возвращает статус активности числа
    return m_is_alive;
}
