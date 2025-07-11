# ASCII Art

**ASCII Art** — это консольное приложение на C++, которое преобразует изображения в формате BMP в текстовую ASCII-графику.

## Описание

Программа читает BMP-файл, анализирует яркость каждого пикселя и отображает изображение в консоли с помощью символов ASCII. Чем выше яркость пикселя, тем "плотнее" символ используется для его отображения (например, '@' для самых ярких участков). Это позволяет получить художественное представление изображения с помощью обычных текстовых символов.

## Как работает

1. Открывает BMP-файл для чтения в бинарном режиме.
2. Извлекает из заголовка изображения параметры: смещение данных, ширину, высоту, глубину цвета.
3. Считывает байты изображения, вычисляет яркость каждого пикселя.
4. Преобразует значение яркости в соответствующий символ ASCII и выводит результат в консоль.

(итог зависит от исходного изображения)

## Установка и запуск

1. **Сборка:**
   ```
   git clone https://github.com/rzmsq/ascii_art.git
   cd ascii_art
   mkdir build && cd build
   cmake ..
   make
   ```

2. **Использование:**
   - Поместите BMP-файл в корень проекта (по умолчанию программа ищет `images.bmp`).
   - Запустите исполняемый файл:
     ```
     ./ascii_art
     ```

## Зависимости

- C++20
- CMake 3.30+
- Любая современная ОС с поддержкой CMake и g++

## Настройка

Если вы хотите использовать свой BMP-файл или другой путь, отредактируйте строку открытия файла в `main.cpp`:
```cpp
std::ifstream input("images.bmp", std::ios::binary);
```
