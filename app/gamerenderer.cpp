#include "gamerenderer.h"

// Инициализация статических членов класса
sf::Texture GameRenderer::ms_background_tex;
sf::Texture GameRenderer::ms_frozen_background_tex;
sf::Texture GameRenderer::ms_boom_background_tex;
std::mt19937 GameRenderer::ms_gen;
std::uniform_int_distribution<std::size_t> GameRenderer::ms_dist;

// Конструктор класса GameRenderer
GameRenderer::GameRenderer(const sf::FloatRect& game_board)
    : m_game_board(game_board),
      m_background_anim(ms_background_tex, 1, 1000),
      m_frozen_background_anim(ms_frozen_background_tex, 6, 200),
      m_boom_background_anim(ms_boom_background_tex, 4, 200),
      m_score(game_board),
      m_timer(game_board)
{
    // Изменяем размеры анимаций в соответсвии с размером предоставленного поля
    sf::Vector2f game_board_size(game_board.width, game_board.height);
    m_background_anim.resize(game_board_size);
    m_frozen_background_anim.resize(game_board_size);
    m_boom_background_anim.resize(game_board_size);

    // Инициализация статистики
    statistics = {
        {"miss", 0},
        {"bomb", 0},
        {"ice", 0},
        {"blum", 0}
    };
}

// Метод обновления игры
void GameRenderer::update(int32_t cur_time)
{
    if (m_start_time == -1)
        m_start_time = cur_time;

    spawn_objects(); // Создание новых объектов
    make_movement(cur_time); // Выполнение движения объектов
    update_labels(cur_time); // Обновление отображаемой информации
    delete_died_objects(); // Удаление уничтоженных объектов
}

// Обработка клика мыши
void GameRenderer::click(const sf::Vector2f &mouse_pos)
{
    bool was_hit = false;
    // Проверяем каждый объект на попадание
    for (Blum& blum : m_blums)
    {
        if (blum.try_press(mouse_pos))
        {
            m_cash += 1; // Увеличиваем счетчик
            statistics["blum"] += 1; // Обновляем статистику
            was_hit = true;
            m_numbers.emplace_back(blum.get_rect(), 1); // Добавляем цифру
        }
    }
    for (Ice& ice : m_ices)
    {
        if (ice.try_press(mouse_pos))
        {
            m_is_freezing = true; // Включаем заморозку
            m_freeze_start_time = -1; // Сбрасываем время заморозки

            m_timer.ice(); // Обновляем таймер
            m_frozen_background_anim.start(); // Запускаем анимацию
            statistics["ice"] += 1; // Обновляем статистику
            was_hit = true;
            m_numbers.emplace_back(ice.get_rect(), 0); // Добавляем цифру
        }
    }
    for (Bomb& bomb : m_bombs)
    {
        if (bomb.try_press(mouse_pos))
        {
            m_is_boom = true; // Включаем взрыв бомбы
            m_boom_background_anim.start(); // Запускаем анимацию взрыва
            m_score.boom(); // Обновляем счет
            statistics["bomb"] += 1; // Обновляем статистику
            was_hit = true;
            m_numbers.emplace_back(bomb.get_rect(), -100); // Добавляем цифру с отрицательным значением

            // Уменьшаем счет
            m_cash = std::max(0, m_cash - 100);
        }
    }
    if (!was_hit)
        statistics["miss"] += 1; // Если промах, увеличиваем счетчик промахов
}

// Проверка окончания игры
bool GameRenderer::is_game_over(void)
{
    return m_time_passed > mc_match_time; // Возвращает true, если время игры истекло
}

// Отрисовка на экране
void GameRenderer::draw(sf::RenderWindow &window, int32_t cur_time)
{
    sf::Vector2f game_board_pos(m_game_board.left, m_game_board.top);
    sf::Sprite background;

    ///< Отображаем задний фон в зависимости от текущего игрового состояния
    if (m_is_boom && !m_boom_background_anim.is_end(cur_time))
    {
        background = m_boom_background_anim.get_sprite(cur_time);
    }
    else
    {
        m_is_boom = false;
        background = m_background_anim.get_sprite(cur_time);
    }

    background.setPosition(game_board_pos);
    window.draw(background);

    // отображаем объекты
    std::for_each(m_blums.begin(), m_blums.end(), [&window, cur_time](Blum& blum){
        blum.draw(window, cur_time);
    });
    std::for_each(m_ices.begin(), m_ices.end(), [&window, cur_time](Ice& ice){
        ice.draw(window, cur_time);
    });
    std::for_each(m_bombs.begin(), m_bombs.end(), [&window, cur_time](Bomb& bomb){
        bomb.draw(window, cur_time);
    });
    std::for_each(m_numbers.begin(), m_numbers.end(), [&window](Number& num){
        num.draw(window);
    });

    // Если нужно отображаем анимацию льда
    if (m_is_freezing && !m_frozen_background_anim.is_end(cur_time)) // Если анимация еще не закончилась
    {
        sf::Sprite frozen_screen = m_frozen_background_anim.get_sprite(cur_time);
        frozen_screen.setPosition(game_board_pos);
        window.draw(frozen_screen);
    }

    // отображаем метки
    m_score.draw(window, cur_time);
    m_timer.draw(window, cur_time);
}

// Загрузка ресурсов
bool GameRenderer::load_resources(void)
{
    bool success = true;
    if (!ms_background_tex.loadFromFile("./src/background.png"))
        success = false;

    if (!ms_frozen_background_tex.loadFromFile("./src/frozen_anim.png"))
        success = false;

    if (!ms_boom_background_tex.loadFromFile("./src/boom_background_anim.png"))
        success = false;

    if (!ScoreLabel::load_resources())
        success = false;

    if (!TimerLabel::load_resources())
        success = false;

    if (!Blum::load_resources())
        success = false;

    if (!Ice::load_resources())
        success = false;

    if (!Bomb::load_resources())
        success = false;

    if (!Number::load_resources())
        success = false;

    std::random_device rd;   // устройство генерации случайных чисел
    ms_gen.seed(rd());          // инициализация генератора случайных чисел с устройства
    ms_dist = std::uniform_int_distribution<std::size_t>(0, 1000); // равномерное распределение от 0 до 1000

    return success;
}

// Удаление умерших объектов
void GameRenderer::delete_died_objects(void)
{
    // Определяем вышедшие за границы game_board объекты и удаляем их
    remove_departed_elements(m_blums);
    remove_departed_elements(m_ices);
    remove_departed_elements(m_bombs);

    // Определяем умершие элементы и удаляем их
    remove_died_elements(m_blums);
    remove_died_elements(m_ices);
    remove_died_elements(m_bombs);
    remove_died_elements(m_numbers);
}

// Создание новых объектов
void GameRenderer::spawn_objects(void)
{
    if (!m_is_freezing) // Если мы не в режиме заморозки
    {
        // Создаем элементы с заданной для их типа вероятностью
        if (should_spawn_object(m_blum_probability))
            m_blums.emplace_back(m_game_board);

        if (should_spawn_object(m_bomb_probability))
            m_bombs.emplace_back(m_game_board);

        if (should_spawn_object(m_ice_probability))
            m_ices.emplace_back(m_game_board);
    }
}

// Движение объектов
void GameRenderer::make_movement(int32_t cur_time)
{
    // Перемещаем объекты в соответствии с deltatime концепцией
    move_elements(m_blums, cur_time);
    move_elements(m_ices, cur_time);
    move_elements(m_bombs, cur_time);
    move_elements(m_numbers, cur_time);
}

// Обновление меток и таймера
void GameRenderer::update_labels(int32_t cur_time)
{
    // Работа с таймером
    if (!m_is_freezing) // Если мы не в заморозке
    {
        // Рассчитываем пройденной вермя как промежуток между текущим моментом
        // и началом, без времени в заморозке
        m_time_passed = cur_time - m_start_time - m_time_in_freezing_mode;
        int32_t seconds_passed = m_time_passed / 1000;  // Переводим в секунды
        int32_t seconds_left = mc_match_time / 1000 - seconds_passed; // Вычисляем сколько осталось
        m_timer.set_time(seconds_left); // Устанавливаем время на таймер
    }
    else
    {
        // Увеличиваем общее время в режиме заморозки
        m_time_in_freezing_mode += cur_time - m_last_freeze_time;

        if (m_freeze_start_time == -1) // Если мы впервые заморозились
        {
            freeze_elements();  // Замораживаем все элементы
            m_freeze_start_time = cur_time; // Запоминаем время когда мы начали
        }
        if (m_freeze_start_time != -1 &&  // Если мы в заморозке слишком долго
                cur_time - m_freeze_start_time >= mc_freeze_time)
        {
            m_is_freezing = false; // Выходим из заморозки

            unfreeze_elements();    // Размораживаем все элементы
            m_freeze_start_time = -1; // Очищаем стартовое время
        }
    }
    m_last_freeze_time = cur_time;

    // Работа со счетом
    m_score.set_score(m_cash);
}

// Заморозка объектов
void GameRenderer::freeze_elements(void)
{
    sf::Vector2f direct(0.f, 0.f);
    change_direction_elements(m_blums, direct);
    change_direction_elements(m_ices, direct);
    change_direction_elements(m_bombs, direct);
}

// Разморозка объектов
void GameRenderer::unfreeze_elements(void)
{
    sf::Vector2f direct(0.f, 1.f);
    change_direction_elements(m_blums, direct);
    change_direction_elements(m_ices, direct);
    change_direction_elements(m_bombs, direct);
}

// Удаление объектов, вышедших за границы игрового поля
template <typename T>
void GameRenderer::remove_departed_elements(std::list<T>& list)
{
    // Создаем прямоугольник на котором, могут находится объекты
    sf::FloatRect sandbox(m_game_board.left, m_game_board.top - 100.f,
                          m_game_board.width, m_game_board.height + 100.f);
    // Если объекты непересекают данный прямоугольник, то они должны быть удалены
    list.remove_if([sandbox](const T& obj) {
        return !sandbox.intersects(obj.get_rect());
    });
}

// Удаление "мертвых" объектов
template <typename T>
void GameRenderer::remove_died_elements(std::list<T>& list)
{
    list.remove_if([](const T& obj) {
        return !obj.get_status();
    });
}

// Движение элементов
template <typename T>
void GameRenderer::move_elements(std::list<T>& list, int32_t cur_time)
{
    std::for_each(list.begin(), list.end(), [cur_time](T& obj){
       obj.move(cur_time);
    });
}

// Изменение направления движения элементов
template <typename T>
void GameRenderer::change_direction_elements(std::list<T>& list, const sf::Vector2f& direct)
{
    std::for_each(list.begin(), list.end(), [direct](T& obj){
       obj.set_direction(direct);
    });
}

// Проверка нужно ли создать новый объект
bool GameRenderer::should_spawn_object(std::size_t chance)
{
    std::size_t cur_num = ms_dist(ms_gen); // генерируем случайное число

    return cur_num < chance;
}
