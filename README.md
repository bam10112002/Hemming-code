# Код Хэмминга

## Coder
Данное прилажение позволяет кодировать файл переданный в качестве аргументов командной строки:
-n x, где x – размер блока в битах
-o output_filename, указывает путь до выходного файла
-i input_filename, указывает путь до входного файла
для удобство редактирования и симуляции возникновения ошибки запись осуществялется в текстовом виде, что значительно увеличивает размер файла закодированного кодом Хэмминга, в случае полноценного использования ПО необходимо изменть функцию записи и чтения массива хеминга применив запись в бинарном виде.

## Decoder
Данное приложение позволяет декодировать файл, аргументы командной строки совподаю с указанными для приложения "coder", после исправления ошибок decoder записывает исходное сообщение в указанный файл.

## Demon 
Приложение запускает бесконечный цикл, отвечающий за выявление и исправление ошибок в директории указанной в качестве аргументов командной строки:
-d namedir: каталог в котоырый берет демон под свой контроль.
-t s, где s количество секунд через которое будет происходить запуск проверки директории.
-l log_name: относительный путь до лог файла в который будет производиться запись.

## Main
Тестовое приложение обладающими всем функционалом описанным выше.

## Makefile
Позволяет скомпилировать ПО а автоматизированном режиме, что значительно упрощает и ускоряет данный процесс.
