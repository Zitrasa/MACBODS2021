# Схема Эль-Гамаля и SHA256
## Вариант 4

Задание выполнено на языке Python 3, в виде консольного приложения.
Поддерживаются следующие команды:
1. ```Gen (p: int)``` – генерация параметров ЭЦП и ключей
2. ```Sign (p: int, q: int, g: int, d: int)``` – подпись текстового сообщения (сообщение вводится после вызова)
3. ```Verify (p: int, q: int, g: int, e: int, r: int, s: int)``` – проверка подписи текстового сообщения (сообщение вводится после вызова)
4. ```Exit``` – выход из программы

* * *
В файле **report.txt** находится консольный ввод - вывод со значениями, соответствующими моему варианту.