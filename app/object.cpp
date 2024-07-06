#include "object.h"

// =======================================================
// ===================== ObjectLogic =====================
// =======================================================
sf::FloatRect ObjectLogic::get_rect(void) const
{
    return sf::FloatRect(m_cur_position, m_size);
}

void ObjectLogic::set_position(const sf::Vector2f& new_pos)
{
    m_cur_position = new_pos;
}

void ObjectLogic::set_size(const sf::Vector2f& new_size)
{
    m_size = new_size;
}

void ObjectLogic::set_direction(const sf::Vector2f& new_direct)
{
    float length = std::sqrt(new_direct.x * new_direct.x + new_direct.y * new_direct.y);
    if (length != 0.0f)
    {
        m_direction = new_direct / length;
    }
    else
    {
        m_direction = sf::Vector2f(0.f, 0.f);
    }
}

void ObjectLogic::set_speed(float new_speed)
{
    m_speed = new_speed;
}

bool ObjectLogic::check_collision(const sf::Vector2f& pos) const
{
    return get_rect().contains(pos);
}

sf::Vector2f ObjectLogic::move(int32_t cur_time)
{
    if (m_last_update_time == -1) {
        m_last_update_time = cur_time;
        return m_cur_position;
    }

    int32_t delta_time = cur_time - m_last_update_time;
    m_last_update_time = cur_time;

    sf::Vector2f movement = m_direction * m_speed * (delta_time / 1000.0f);
    m_cur_position += movement;

    return m_cur_position;
}

// ==================================================
// ===================== Object =====================
// ==================================================
Object::Object(sf::Texture& glow_tex, std::size_t glow_n, int32_t glow_change_time,
               sf::Texture& activ_tex, std::size_t activ_n, int32_t activ_change_time,
               sf::Texture& idle_tex, std::size_t idle_n, int32_t idle_change_time)
    : m_glow_anim(glow_tex, glow_n, glow_change_time),
      m_activ_anim(activ_tex, activ_n, activ_change_time),
      m_idle_anim(idle_tex, idle_n, idle_change_time)
{

}

bool Object::get_status(void) const
{
    return m_alive;
}

sf::FloatRect Object::get_rect(void) const
{
    return ObjectLogic::get_rect();
}

void Object::set_position(const sf::Vector2f& new_pos)
{
    ObjectLogic::set_position(new_pos);
}

void Object::set_size(const sf::Vector2f& new_size)
{
    m_glow_anim.resize(new_size);
    m_activ_anim.resize(new_size);
    m_idle_anim.resize(new_size);

    ObjectLogic::set_size(new_size);
}

void Object::set_direction(const sf::Vector2f& new_direct)
{
    ObjectLogic::set_direction(new_direct);
}

void Object::set_speed(float new_speed)
{
    ObjectLogic::set_speed(new_speed);
}

void Object::move(int32_t cur_time)
{
    ObjectLogic::move(cur_time);
}

bool Object::try_press(const sf::Vector2f& mouse_pos)
{
    if (check_collision(mouse_pos) && !m_activated) // Есть пересечение и этот объект еще не активирован
    {
        m_activ_anim.start(); // Запускаем активную анимацию.
        m_activated = true; // Активируем объект
        return true;
    }
    return false;
}

void Object::draw(sf::RenderWindow& window, int32_t cur_time)
{
    sf::FloatRect rec = get_rect();

    if (m_activated) //  Объект был нажат (активирован)
    {
        if (m_activ_anim.is_end(cur_time)) // Если закончилась анимация
        {
            m_alive = false; // Помечаем объект как неактивный (мертвый).
            return;
        }

        sf::Sprite sprite = m_activ_anim.get_sprite(cur_time); // Получаем спрайт текущего кадра активной анимации.
        sprite.setPosition(rec.left, rec.top); // Перемещаем спрайт активной анимации на его позицию.
        window.draw(sprite); // Отрисовываем спрайт активной анимации.
    }
    else // Объект жив
    {
        sf::Sprite sprite = m_idle_anim.get_sprite(cur_time); // Получаем спрайт текущего кадра анимации покоя.
        sf::Sprite glow = m_glow_anim.get_sprite(cur_time); // Получаем спрайт текущего кадра анимации свечения.
        sprite.setPosition(rec.left, rec.top); // Перемещаем обычный спрайт на его позицию.
        glow.setPosition(rec.left, rec.top - rec.height / 2.f); // Перемещаем спрайт свечения чуть выше, чем позиция.
        window.draw(sprite); // Отрисовываем спрайт анимации покоя.
        window.draw(glow); // Отрисовываем спрайт анимации свечения.
    }
}


