For English scroll down

___
# СУБД с SQL подобным языком запросов

Это учебный проект по созданию СУБД с SQL подобным языком запросов, созданный с помощью языка C++, с использованием оптимизирующих структур данных для ускоренного поиска/вставки/удаления данных в БД. 


# Запуск

1. Скачать Zip архив
2. Перейти в папку "/database/build" .
3. Запустить в этой папке Cmake коммандой "cmake . ."
3. Дождаться генерации Makefile, затем запустить Make c помощью команды "make"(Результатом сборки является файл DataBase)
5. Запускаем с помощью команды "./DataBase" без аргументов коммандной строки.
6. При старте СУБД запрашивает размер Хэш-таблицы (см. ниже) и файл для инициализации БД (в качестве примера приложен dbInit.txt  где находятся записи вида <name> <phone> <group> по одной записи на строку).
7. Вводим необходимые комманды (см. ниже)

# Как это работает ?

СУБД имеет 3 поля со строгой типизацией:
| Название | Тип | Диапазон | Поисковая структура |
| ------ | ------ |------ | ------ |
Name | Строка | до 1024 символов| Красно-чёрное дерево (1)|
Phone |Целое число | до 2^31 - 1  | Хэш-таблица АВЛ-деревьев (2)|
Group |Целое число | до 2^31 - 1  |  Красно-чёрное дерево (3)|

1. [Красно-чёрное дерево] - Поисковая структура для поля Name. В качестве отношения порядка используется лексикографический порядок строк . Исходный код лежит в файлах RedBlackTreeName..
2. [Хэш-таблица] состоящая из [АВЛ-деревьев] - Поисковая структура для поля Phone. [Хэш-функция] - остаток от деления суммы цифр phone на значение, которое просит ввести программа при старте.  Исходный код лежит в файлах hash.. и AVLTree..
3. [Красно-чёрное дерево] - Поисковая структура для поля Group. В качестве отношения порядка используется стандартный порядок на числовой прямой. В связи с большим количество повторений среди полей Group, каждый лист Красно-чёрного дерева содержит свою копию структур (1), (2) совпадающих по полю Group. Исходный код лежит в файлах RedBlackTree..

Схема взаимодействия данных внутри программы:
![Image alt](https://sun1-23.userapi.com/2qI0G7jY_KO7Q7apvbjtjGQnqVU0nVmwEQTp5A/bqMGt8Uo6es.jpg)

# Синтаксис языка запросов

1. **quit;** **stop;** – завершить работу
2. **insert (<name>, <phone>, <group>)**; – добавить структуру с указанными полями в список;
3. **select <аргументы>** – вывести элементы списка, удовлетворяющие указанным в команде условиям, и в указанном в команде виде. Аргументы могут быть:
    * задающие набор выводимых столбцов (обязательный аргумент):
    в качестве списка пока что может быть только * – выводить все столбцы
    
    * задающие критерий, которому должны удовлетворять выводимые строки (необязательный аргумент):
    **where <условия>** – выводить строки, удовлетворяющие указанным условиям.
    Условия могут быть:
        * <поле> <оператор> <выражение>, где
        – <поле> – имя поля таблицы (name, phone, value)
        – <оператор> – логический оператор отношения: = – равно, <> – не равно, <, >, <=, >= – соответствуют языку C
        – <выражение> – константное выражение соответствующего типа
    **Пример: where name = Ivanov**
        * **<поле> like <образец>**, где
    – <поле> – имя поля таблицы символьного типа (name)
    – <образец> – образец поиска. Может включать в себя специальные
    символы: % – соответствует 0 или более любым символам
    **Пример: where name like Iv%**

    * Из двух таких условий можно строить более сложные:
    • <условие1> and <условие2>
    • <условие1> or <условие2>
    На условия здесь накладывается ограничение: <условие1> и <условие2> задают условия на разные поля записи.
    **Пример команд:
    select group, name where phone = 1234567 and name = Student;
    select * where phone >= 1234567 and name like St%;
    select * where group = 208 and phone <> 1234567;
    select * where name = Student or phone = 1234567;**
4. **delete <аргументы>** – удалить строки таблицы, удовлетворяющие указанным в команде условиям. Аргументы могут быть:
    * нет аргументов – удалить все строки таблицы
    * **where <условия>** – удалить строки, удовлетворяющие указанным условиям (см. описание условий в команде **select**).
5. **order by <поле>**
Выводит найденные записи, отсортированные(По возрастанию) по значению указанного поля. Например, select * where phone = 1234567 order by name; выводит найденные записи отсортированными по значению поля name.

6. Разделителем команд является “**;**”, разделителями аргументов команды являются пробел, символ табуляции и символ новой строки.


# Дальнейшее развитие
1. Исправление незначительных багов.
2. Добавить возможность выводить столбцы в указанном порядке. Например вывести только Phone и Name. Пример: **select phone, name where group = 208 and phone > 100000;**
3. Улучшить парсер, используя синтаксическое дерево разбора, а не линейный разбор. Таким образом можно будет комбинировать большее количество условий. 

___
# DBMS with SQL similar query language

This is a training project to create a DBMS with SQL similar query language. It was created using the C++ with using optimizing data structures for accelerating searching/inserting/deleting data operations in the database.

# Launch

1. Download Zip archive
2. Change directory to the "/database/build"
3. Run in the directory Cmake with command "cmake.."
3. Wait till the Makefile to be generated, then run Make using the "make" command (The result of the building is a DataBase file)
5. Start programm using "./DataBase" command without command line arguments.
6. The DBMS asks for the size of the Hash table (see below) and the file for initializing the database (File must consists of Records: <name> <phone> <group>, one Record per line. An example "DataBaseInit.txt" is applied).
7. Enter the necessary commands (see below)

# How it works ?

DBMS has 3 fields with fixed type:
| Title | Type | Range | Search Structure|
| ------ | ------ | ------ | ------ |
Name | String | up to 1024 characters | Red–black tree (1) |
Phone | Integer | up to 2 ^ 31 - 1 | Hash table of AVL trees (2) |
Group | Integer | up to 2 ^ 31 - 1 |  Red–black tree (3) |

1. [Red-black tree] - Search structure for the Name field. The lexicographical order of strings is used as an order relation. The source code is in the RedBlackTreeName.. files
2. [Hash table] consisting of [AVL trees] - Search structure for the Phone field. [Hash function] - the remainder of dividing the sum of phone digits by the value that the program asks to enter at startup. The source code is in the files hash .. and AVLTree ..
3. [Red-black tree] - Search structure for the Group field. As the order relation, the standard order on the number line is used. Due to the large number of repetitions among the Group fields, each leaf of the Red-Black Tree contains its own copy of structures (1), (2) with the same value of Group field. The source code is in the RedBlackTree files ..

The scheme of data interaction within the program:
![Image alt](https://sun1-23.userapi.com/2qI0G7jY_KO7Q7apvbjtjGQnqVU0nVmwEQTp5A/bqMGt8Uo6es.jpg)

# Query language syntax

1. **quit;** **stop;** -finish work
2. **insert (<name>, <phone>, <group>);** - add a record with the specified fields to the container;
3. **select <arguments>** - display records that satisfy the conditions specified in the command and in the form specified in the command. Arguments may be:
    * defining a set of output columns (required argument):
    as a list so far there can only be * - output all columns
    * defining a criterion that the output lines must satisfy (optional argument):
    **where <conditions>** - display lines that satisfy the specified conditions. Conditions may be:
            * <field> <operator> <expression>, where
            - <field> - table field name (name, phone, value)
            - <operator> - logical relation operator: = - equal, <> - not equal, <,>, <=,> = - correspond to the language C
            - <expression> - constant expression of the corresponding type
            -**Example: where name = Mike**
    *  **<field> like <sample>** , where  <field> - field name of the table of the character type (name). <sample> - search pattern. May include special characters:
        * % - matches 0 or more to any characters
            Example: **where name like Jack%**
    * It is possible to build complex conditions of those basic type using **and**, **or** :
    • <condition1> **and** <condition2>
    • <condition1> **or** <condition2>
    There is a restriction on the conditions here: <condition1> **and** <condition2> specify conditions for different fields of the record.
    Command example:
    **select group, name where phone = 1234567 and name = Student;
    select * where phone> = 1234567 and name like St%;
    select * where group = 208 and phone <> 1234567;
    select * where name = Student or phone = 1234567;**

4. **delete <arguments>** - delete table lines that satisfy the conditions specified in the command. Arguments may be:
    * no arguments - delete all lines of the table
    * where <conditions> - delete lines that satisfy the specified conditions (see the description of conditions in the **select** command).
 5. **order by <field>** - displays found records sorted (Ascending) by the value of the specified field. For example, select * where phone = 1234567 order by name; displays the found records sorted by the value of the name field.

6. The command delimiter is “**;**”, the command delimiter is a space, a tab character, and a newline.


# Todos

1. Fix minor bugs.
2. Add the ability to display columns in the specified order, for example, group, name - display only the third and first fields. Example: **select phone, name where group = 208 and phone > 100000;**
3. Upgrade parser using parsing tree.


[Red-black tree]: <https://en.wikipedia.org/wiki/Red%E2%80%93black_tree>
[Hash table]: <https://en.wikipedia.org/wiki/Hash_table>
[AVL trees]: <https://en.wikipedia.org/wiki/AVL_tree>
[Hash function]: <https://en.wikipedia.org/wiki/Hash_function>



[Красно-чёрное дерево]: <https://ru.wikipedia.org/wiki/%D0%9A%D1%80%D0%B0%D1%81%D0%BD%D0%BE-%D1%87%D1%91%D1%80%D0%BD%D0%BE%D0%B5_%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE>
[Хэш-таблица]: <https://ru.wikipedia.org/wiki/%D0%A5%D0%B5%D1%88-%D1%82%D0%B0%D0%B1%D0%BB%D0%B8%D1%86%D0%B0>
[Хэш-функция]: <https://ru.wikipedia.org/wiki/%D0%A5%D0%B5%D1%88-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F>
[АВЛ-деревьев]: <https://ru.wikipedia.org/wiki/%D0%90%D0%92%D0%9B-%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE>