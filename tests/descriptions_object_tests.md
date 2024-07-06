# Перечень тестов для class Object

## Модуль объекта (ObjectLogic)

### 1. Метод void set_position(const sf::Vector2f& position);

#### Тест №1.1 test_set_position (позитивный)
* _Цель_: проверка корректности установки позиции объекта.
* _Входные данные_: Объект `ObjectLogic`.
* _Ожидаемый результат_: Убедиться, что метод `set_position` правильно устанавливает позицию объекта.
* _Описание процесса_: Создается объект `ObjectLogic`. Задается новая позиция с использованием метода `set_position`. Проверяются значения границ объекта через метод `get_rect()` на соответствие установленной позиции.

### 2. Метод bool check_collision(const sf::Vector2f& point);

#### Тест №1.2 test_check_collision (позитивный)
* _Цель_: проверка корректности метода `check_collision` для точек внутри и снаружи объекта.
* _Входные данные_: Объект `ObjectLogic` с заданной позицией и размером.
* _Ожидаемый результат_: Убедиться, что метод `check_collision` правильно определяет, находится ли точка внутри границ объекта или снаружи.
* _Описание процесса_: Создается объект `ObjectLogic` с заданной позицией и размером. Проверяются две точки: одна внутри объекта (ожидаемый результат — true), другая снаружи (ожидаемый результат — false).

### 3. Метод sf::Vector2f move(int32_t time_ms);

#### Тест №1.3 test_move (позитивный)
* _Цель_: проверка корректности перемещения объекта.
* _Входные данные_: Объект `ObjectLogic` с начальной позицией, направлением и скоростью.
* _Ожидаемый результат_: Убедиться, что метод `move` корректно перемещает объект на основе заданного направления, скорости и времени.
* _Описание процесса_: Создается объект `ObjectLogic` с начальной позицией, направлением и скоростью. Вызывается метод `move` с начальным временем, затем снова с временем через определенный интервал. Проверяется новая позиция объекта после перемещения.