# Guic

GUIC (Graphical User Interface Creator) - библиотека для создания графических интерфейсов. Guic позволяет строить интерфейсы без тяжёлых фреймворков и без глубокого знания графических API. Как основа рендерера используется SDL.

**Версия:** 0.2.0

Используется система версионности SemVer 2.0.0 https://semver.org

## Документация

- Русская: https://slideeex.github.io/Guic/ru/
- English: https://slideeex.github.io/Guic/en/

Метки стабильности функций описаны на странице «Пояснение к меткам» в разделе «Публичный API»: [ru](https://slideeex.github.io/Guic/ru/stability/), [en](https://slideeex.github.io/Guic/en/stability/).

## Лицензия

Guic распространяется под GNU LGPL версии 3 с дополнительными разрешениями на линковку и распространение. Тексты лицензий лежат в папке `Licenses/` каждой сборки (`MinGW/Licenses`, `Visual Cpp/Licenses`, `Linux/Licenses`):

- `LICENSE`
- `COPYING`
- `ADDITIONAL_PERMISSIONS.md` - дополнительные разрешения
- `THIRD_PARTY_LICENSES.md` - сторонние компоненты

При распространении архив должен содержать эту папку.

## Сборки

| Папка | Платформа | Содержимое |
|---|---|---|
| `MinGW/x64` | Windows x64, MinGW | `guic.dll`, `guic-d.dll`, статические библиотеки, заголовки |
| `MinGW/x32` | Windows x86, MinGW | `guic.dll`, `guic-d.dll`, статические библиотеки, заголовки |
| `Visual Cpp/x64` | Windows x64, Visual C++ | `guic.dll`, `guic-d.dll`, `guic.lib`, `guic-d.lib`, `guic-s.lib`, `guic-s-d.lib`, заголовки |
| `Visual Cpp/x32` | Windows x86, Visual C++ | `guic.dll`, `guic-d.dll`, `guic.lib`, `guic-d.lib`, `guic-s.lib`, `guic-s-d.lib`, заголовки |
| `Linux/x64` | Linux x86_64 | `libguic.so`, `libguic.a`, заголовки |

`-d` в имени означает отладочную сборку.

`-s` в имени означает статическую сборку.

Для Linux бинарники x86 (32-бит) не поставляются. Для остальных разрядностей и платформ библиотеку нужно собрать из исходников в `Code/`.

Чтобы программа на Linux находила `libguic.so`, необходимо положить библиотеку рядом с исполняемым файлом: исполняемый файл ищет её в своей папке. На Windows `guic.dll` также кладётся рядом с `.exe`.

## Исходный код

- `Code/headers/` - публичные заголовки и внутренние заголовки движка.
- `Code/source/` - реализация.

## Пример

`Tutorial/` содержит `main.cpp` и готовую сборку примера из раздела "Давайте начнём" в документации.

## Используемые библиотеки

- SDL2 2.32.10 и SDL2_ttf 2.24.0 (zlib)
- FreeType 2.13.2 (FreeType License, FTL)
- HarfBuzz 8.1.1 (Old MIT)
- stb_image 2.30 (Public Domain)
- MaxRects (MaxRectsBinPack), Jukka Jylänki (Public Domain)

Авторские права: Copyright (C) 2026 V. Zaidov. Полный список и тексты лицензий: `Licenses/THIRD_PARTY_LICENSES.md`.

## Баги

Сообщайте об ошибках в Issues: [https://github.com/SlideeeX/Guic/issues](https://github.com/SlideeeX/Guic/issues)

## Roadmap

Планы, а не обещания: порядок и состав могут меняться.

- Оптимизация рендерера: сортировка изображений по размеру для атласа MaxRects.
- Класс `Icon` для загрузки изображений SVG.
- Метод контейнера для добавления нескольких элементов сразу.
- Расширенные методы окна: включение и отключение Drag and Drop, установка полноэкранного режима и подобные прокси-методы.
- Безопасное удаление ресурсов без неопределённого поведения.
- Вывод ошибок, предупреждений и информации из Guic.

