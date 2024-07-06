#include "gamelabels.h"

// =======================================================
// ===================== Timer label =====================
// =======================================================

// Инициализация статических членов класса TimerLabel
sf::Texture TimerLabel::ms_timer_idle_anim_tex;
sf::Texture TimerLabel::ms_timer_ice_anim_tex;
sf::Font TimerLabel::ms_timer_font;

// Конструктор с параметром для инициализации игровой доски
TimerLabel::TimerLabel(const sf::FloatRect& game_board)
    : m_label_idle(ms_timer_idle_anim_tex, 1, 1000, ms_timer_font),
      m_label_ice(ms_timer_ice_anim_tex, 1, 1000, ms_timer_font),
      m_game_board(game_board)
{
    // устанавливаем начальные настройи для меток
    label_settings(m_label_idle);
    label_settings(m_label_ice);

    // на оба таймер установит начальное время "00:00"
    set_time(0);
}

void TimerLabel::ice(void)
{
    m_is_ice = true;
}

// Установка текущего времени
void TimerLabel::set_time(int32_t cur_time)
{
    // устанавливаем текущее время
    std::string timer_str = format_seconds(cur_time);
    m_label_idle.set_string(timer_str);
    m_label_ice.set_string(timer_str);
}

void TimerLabel::draw(sf::RenderWindow &window, int32_t cur_time)
{
    ///< Проверяем события
    if (m_is_ice)// Был активирован лед
    {
        // Засекаем врямя его начала
        m_start_ice_time = cur_time;
    }
    ///< Отображаем в зависимости от текущего состояния
    // мы находимся на промежутке замерзания
    if (m_start_ice_time != -1 &&
            cur_time - m_start_ice_time <= mc_ice_time)
    {
        m_label_ice.draw(window, cur_time);
    }
    // мы отображаем обычный таймер
    else
    {
        m_label_idle.draw(window, cur_time);
    }

    // сбрасываем флаг
    m_is_ice = false;
}

// Форматирование времени в строку формата "MM:SS"
std::string TimerLabel::format_seconds(int seconds) const
{
    int minutes = seconds / 60;
    int remainingSeconds = seconds % 60;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << remainingSeconds;

    return oss.str();
}

// Загрузка ресурсов (текстуры и шрифта) для метки времени
bool TimerLabel::load_resources(void)
{
    bool success = true;
    // Загрузка текстуры
    if (!ms_timer_idle_anim_tex.loadFromFile("./src/timer_bg.png"))
        success = false;

    if (!ms_timer_ice_anim_tex.loadFromFile("./src/timer_ice_bg.png"))
        success = false;

    // Загрузка шрифта
    if (!ms_timer_font.loadFromFile("./src/Consolas.ttf"))
        success = false;

    return success;
}

float TimerLabel::calc_text_x_position(void) const
{
    return m_game_board.left + 35.f;
}

float TimerLabel::calc_text_y_position(void) const
{

    return m_game_board.top + 15.f;
}

float TimerLabel::calc_pic_x_position(void) const
{
    return m_game_board.left + 15.f;
}

float TimerLabel::calc_pic_y_position(void) const
{
    return m_game_board.top + 15.f;
}

void TimerLabel::label_settings(Label& label)
{
    // Установка начальных параметров для текста
    label.set_string_settings(sf::Color::Yellow, mc_font_size, sf::Text::Bold);

    // Установка начальных значений для картинок
    label.set_picture_size(sf::Vector2f(mc_picture_size_w, mc_picture_size_h));

    // Установка позиции таймера
    // строки
    float text_pos_x = calc_text_x_position();
    float text_pos_y = calc_text_y_position();
    label.set_string_position(sf::Vector2f(text_pos_x, text_pos_y));

    // картинки
    float pic_pos_x = calc_pic_x_position();
    float pic_pos_y = calc_pic_y_position();
    label.set_picture_position(sf::Vector2f(pic_pos_x, pic_pos_y));
}

// =======================================================
// ===================== Score label =====================
// =======================================================

// Инициализация статических членов класса ScoreLabel
sf::Texture ScoreLabel::ms_score_idle_anim_tex;
sf::Texture ScoreLabel::ms_score_boom_anim_tex;
sf::Font ScoreLabel::ms_score_font;


// Конструктор с параметром для инициализации игровой доски
ScoreLabel::ScoreLabel(const sf::FloatRect& game_board)
    : m_label_idle(ms_score_idle_anim_tex, 1, 1000, ms_score_font),
      m_label_boom(ms_score_boom_anim_tex, 1, 1000, ms_score_font),
      m_game_board(game_board)
{
    // Установка начальных параметров для текста
    m_label_idle.set_string_settings(sf::Color::White, mc_font_size, sf::Text::Bold);
    m_label_boom.set_string_settings(sf::Color::Red,   mc_font_size, sf::Text::Bold);
}

// Установка текущего счета
void ScoreLabel::set_score(std::size_t cur_score)
{
    if (cur_score != m_prev_score) // Является ли значение новым
    {
        m_is_score_changed = true;
        m_prev_score = cur_score;

        // Устанавливаем новый результат
        std::string cur_str_res = std::to_string(cur_score);

        m_label_idle.set_string(cur_str_res);
        m_label_boom.set_string(cur_str_res);

        // Позиционируем его в зависимости от занимаемого пространства
        sf::Vector2f new_labels_pos = calc_cur_label_position();
        m_label_idle.set_string_position(new_labels_pos);
        m_label_boom.set_string_position(new_labels_pos);
    }
}

void ScoreLabel::boom(void)
{
    m_is_boom = true;
}

void ScoreLabel::draw(sf::RenderWindow& window, int32_t cur_time)
{
    ///<  Обрабатываем различные сценарии отображения (бомба и(или) заработок)
    // Если значение счета с предыдущего раза поменялось => засекаем время начала увеличения
    if (m_is_score_changed)
    {
        m_start_increase_time = cur_time;
    }

    // Если с предыдущего раза была бомба, засекаем время начала красного текста
    if (m_is_boom)
    {
        m_start_boom_time = cur_time;
    }

    // Если мы находимся в промежутке увеличения метки, пересчитвываем новый размер текста
    if (m_start_increase_time != -1 &&
            cur_time - m_start_increase_time <= mc_increase_time)
    {
        // Получаем коэфицент увеличения стандартный для текущего времени
        float delta_recomend_size = (cur_time - m_start_increase_time) / 1000.f * mc_increase_cof_per_sec;
        // Выбираем текущий размер как максимальный, из текущего и стандартного (рекомендованного)
        m_cur_increase_cof = std::max(m_cur_increase_cof, 1.f + delta_recomend_size);
    }
    else // Иначе оставляем его константным (без увеличения)
    {
        m_cur_increase_cof = 1.f;
    }

    // если сейчас метка должна быть красной
    if (m_start_boom_time != -1 &&
            cur_time - m_start_boom_time <= mc_boom_time)
    {
        // обновляем размер и позицию картинки в соответсвии с размером шрифта
        m_label_boom.set_string_scale(m_cur_increase_cof);
        update_picture(m_label_boom);

        // отображаем результат
        m_label_boom.draw(window, cur_time);

    }
    else // метка должна быть обычной
    {
        // обновляем размер и позицию картинки в соответсвии с размером шрифта
        m_label_idle.set_string_scale(m_cur_increase_cof);
        update_picture(m_label_idle);

        // отображаем результат
        m_label_idle.draw(window, cur_time);
    }

    // опускаем все флаги
    m_is_score_changed = false;
    m_is_boom = false;
}

// Загрузка ресурсов (текстуры и шрифта) для метки счета
bool ScoreLabel::load_resources(void)
{
    bool success = true;
    // Загрузка текстур
    if (!ms_score_idle_anim_tex.loadFromFile("./src/blum_sign.png"))
        success = false;

    if (!ms_score_boom_anim_tex.loadFromFile("./src/blum_red_sign.png"))
        success = false;

    // Загрузка шрифта
    if (!ms_score_font.loadFromFile("./src/Consolas.ttf"))
        success = false;

    return success;
}

float ScoreLabel::calc_text_x_position(const sf::FloatRect& hitbox) const
{
    float right_edge_game_board = m_game_board.left + m_game_board.width;
    float right_duration = 15.f; // величина отступа от границы с права

    float x_pos = right_edge_game_board - hitbox.width - right_duration;

    return x_pos;
}

float ScoreLabel::calc_text_y_position(void) const
{
    float top_edge_game_board = m_game_board.top;
    float up_duration = 15.f;   // Величина отступа от верхней границы

    float y_pos = top_edge_game_board + up_duration;

    return y_pos;
}

float ScoreLabel::calc_pic_x_position(const sf::FloatRect& hitbox) const
{
    return hitbox.left - hitbox.height;
}

float ScoreLabel::calc_pic_y_position(const sf::FloatRect& hitbox) const
{
    return hitbox.top;
}

// Рассчитывает позицию метки
sf::Vector2f ScoreLabel::calc_cur_label_position(void) const
{
    // Получаем ее ограничивающий прямоугольник
    sf::FloatRect text_rect = m_label_idle.get_string_rect();
    // Относительно этого прямоугольника рассчитываем ее новое положение
    float new_x_pos = calc_text_x_position(text_rect);
    float new_y_pos = calc_text_y_position();
    return sf::Vector2f(new_x_pos, new_y_pos);
}

void ScoreLabel::update_picture(Label& label)
{
    // Позиционируем блок с картинкой в зависимости от размера строки
    sf::FloatRect hitbox = label.get_string_rect();// обновили хитбокс строки

    // Обновляем размер картинки в соответствии с высотой тектса
    float string_height = hitbox.height;
    label.set_picture_size(sf::Vector2f(string_height, string_height));

    // позиционируем картинку в окне
    float new_x_pos = calc_pic_x_position(hitbox);
    float new_y_pos = calc_pic_y_position(hitbox);
    label.set_picture_position(sf::Vector2f(new_x_pos, new_y_pos));
}

