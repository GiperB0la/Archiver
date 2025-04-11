Простой архиватор.
Поддерживает две функции: архивировать и разорхивировать.
Действие можно отменить сочением клавиш Ctrl+C.
Запусе программы:
```run
Архивировать:
Archiver a <input file> <archive file>
Разархивировать:
Archiver u <archive file> <output file>
```
Сборка:
```build
mkdir build
cd build
cmake ..
make
```
В Release уже предоставлены сборки под Windows и Linux, чтоб не собирать программу самому.
