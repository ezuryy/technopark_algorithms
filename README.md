# Алгоритмы и структуры данных

## Модуль 1

### Задача 1

**1.3 Если в числе содержится только один бит со значением 1, записать в выходной поток `OK`. Иначе записать `FAIL`**

Во всех задачах необходимо использование битовых операций.
Использование арифметических операций запрещено.
Входное число лежит в диапазоне `[0, 232 - 1]` и вводится в десятичном виде.

### Задача 2

**2.4 Дан отсортированный массив различных целых чисел `A[0..n-1]` и массив целых чисел `B[0..m-1]`. Для каждого элемента массива `B[i]` найдите минимальный индекс элемента массива `A[k]`, ближайшего по значению к `B[i]`.**  

**Требования:** Время работы поиска для каждого элемента `B[i]`: `O(log(k))`.  
Внимание! В этой задаче для каждого `B[i]` сначала нужно определить диапазон для бинарного поиска размером порядка `k` с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.  
`n ≤ 110000, m ≤ 1000`.

### Задача 3

**3.1. Реализовать очередь с динамическим зацикленным буфером.**

Во всех задачах из списка следует написать структуру данных, обрабатывающую команды `push` и `pop`.  
_Формат входных данных:_  
В первой строке количество команд `n`. `n ≤ 1000000`.  
Каждая команда задаётся как 2 целых числа: `a b`.   
- `a = 1 - push front  `
- `a = 2 - pop front  `
- `a = 3 - push back  `
- `a = 4 - pop back  `

Команды добавления элемента `1` и `3` заданы с неотрицательным параметром `b`.
Для очереди используются команды `2` и `3`. Для дека используются все четыре команды.
Если дана команда `pop`, то число `b` - ожидаемое значение. Если команда `pop` вызвана для пустой структуры данных, то ожидается `-1`.  
_Формат выходных данных:_  
Требуется напечатать `YES` - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать `NO`.

**Требования:** Очередь должна быть реализована в виде класса.

### Задача 4  

**4.1. Слияние массивов**  
Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной `N`.

**Требование для всех вариантов Задачи 4:**  
- Решение всех задач данного раздела предполагает использование кучи, реализованной в виде шаблонного класса.
- Решение должно поддерживать передачу функции сравнения снаружи.
- Куча должна быть динамической.

**Требования:** время работы `O(N * logK)`. Ограничение на размер кучи `O(K)`.  
_Формат входных данных:_  
Сначала вводится количество массивов K. Затем по очереди размер каждого массива и элементы массива. Каждый массив упорядочен по возрастанию.  
_Формат выходных данных:_  
Итоговый отсортированный массив.

### Задача 5

**5.4. Закраска прямой №2**  
На числовой прямой окрасили `N` отрезков. Известны координаты левого и правого концов каждого отрезка (`Li` и `Ri`). Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.

**Требование для всех вариантов Задачи 5:**  
- Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием в виде шаблонной функции.
- Решение должно поддерживать передачу функции сравнения снаружи.
- Общее время работы алгоритма `O(n log n)`.

### Задача 6

**6.1. Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию `Partition` реализуйте методом прохода двумя итераторами от начала массива к концу.**

Дано множество целых чисел из [0..10^9] размера n.
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
1)	10%  перцентиль
2)	медиана
3)	90%  перцентиль

**Требования:** 
- Дополнительная память: `O(n)`
- Среднее время работы: `O(n)`
- Должна быть отдельно выделенная функция `Partition`
- Рекурсия запрещена
- Решение должно поддерживать передачу функции сравнения снаружи

Функцию `Partition` следует реализовывать методом прохода двумя итераторами в одном направлении. Описание для случая прохода от начала массива к концу:
- Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
- Во время работы `Partition` в начале массива содержатся элементы, не бОльшие опорного. Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
- Итератор (индекс) `i` указывает на начало группы элементов, строго бОльших опорного.
- Итератор `j` больше `i`, итератор `j` указывает на первый нерассмотренный элемент.
- Шаг алгоритма. Рассматривается элемент, на который указывает `j`. Если он больше опорного, то сдвигаем `j`.   
Если он не больше опорного, то меняем `a[i]` и `a[j]` местами, сдвигаем `i` и сдвигаем `j`.
- В конце работы алгоритма меняем опорный и элемент, на который указывает итератор `i`.

### Задача 7
**7.1. MSD для строк**  

Дан массив строк. Количество строк не больше `10^5`. Отсортировать массив методом поразрядной сортировки MSD по символам. Размер алфавита - `256` символов. Последний символ строки = `‘\0’`.

## Модуль 2

### Задача 1. Хеш-таблица

**1.1. Для разрешения коллизий используйте квадратичное пробирование. `i`-ая проба
`g(k, i) = g(k, i - 1) + i (mod m)`. `m` - степень двойки.**

Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.   

Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.  

Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.  

Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.

**Требования:** В таблице запрещено хранение указателей на описатель элемента.  
_Формат входных данных:_  
Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.
Тип операции  – один из трех символов:
- `+` означает добавление данной строки в множество;
- `-` означает удаление  строки из множества;  
- `?` означает проверку принадлежности данной строки множеству.  

При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.  
_Формат выходных данных:_  
Программа должна вывести для каждой операции одну из двух строк `OK` или `FAIL`, в зависимости от того, встречается ли данное слово в нашем множестве.

### Задача 2. Порядок обхода

**2.3. Выведите элементы в порядке `post-order` (снизу вверх).**

Дано число `N < 10^6` и последовательность целых чисел из `[-231, 231]` длиной `N`.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа `K` в дерево с корнем `root`, если `root→Key ≤ K`, то узел `K` добавляется в правое поддерево `root`; иначе в левое поддерево `root`.  
**Требования:** 
- Рекурсия запрещена. 
- Решение должно поддерживать передачу функции сравнения снаружи.

### Задача 4. Использование АВЛ-дерева 

**4.2. Порядковые статистики.**  

Дано число `N` и `N` строк. Каждая строка содержит команду добавления или удаления натуральных чисел, а также запрос на получение k-ой порядковой статистики. Команда добавления числа A задается положительным числом A, команда удаления числа A задается отрицательным числом “-A”. Запрос на получение k-ой порядковой статистики задается числом k.

**Требование для всех вариантов Задачи 4:**  
Решение должно поддерживать передачу функции сравнения снаружи.

**Требования:** скорость выполнения запроса - `O(log n)`.

## Модуль 3

### Задача 1. Представление графа

**Дан базовый интерфейс для представления ориентированного графа:**   
```
struct IGraph {
virtual ~IGraph() {}
// Добавление ребра от from к to. virtual void AddEdge(int from, int to) = 0;
virtual int VerticesCount() const = 0;
virtual std::vector<int> GetNextVertices(int vertex) const = 0;
virtual std::vector<int> GetPrevVertices(int vertex) const = 0; };
```
**Необходимо написать несколько реализаций интерфейса:**
- `ListGraph`, хранящий граф в виде массива списков смежности,
- `MatrixGraph`, хранящий граф в виде матрицы смежности,
- `SetGraph`, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев
  поиска,
- `ArcGraph`, хранящий граф в виде одного массива пар `{from, to}`.  

Также необходимо реализовать конструктор, принимающий `const IGraph&`. Такой конструктор должен скопировать переданный граф в создаваемый объект.   
Для каждого класса создавайте отдельные `h` и `cpp` файлы.   
Число вершин графа задается в конструкторе каждой реализации.

### Задача 2. Количество различных путей

**Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. 
Найдите количество различных кратчайших путей между заданными вершинами.**

**Требования:** сложность `O(V+E)`.  
_Формат ввода:_  
`v`: кол-во вершин (макс. 50000),  
`n`: кол-во ребер (макс. 200000),  
`n` пар реберных вершин,  
пара вершин `u`, `w` для запроса.  
_Формат вывода:_  
Количество кратчайших путей от `u` к `w`.

### Задача 3. Города

**Требуется отыскать самый выгодный маршрут между городами.**  

**Требования:** время работы `O((N+M)logN)`, где `N` - количество городов, `M` - известных дорог между ними.  
_Формат входных данных:_  
Первая строка содержит число `N` – количество городов.  
Вторая строка содержит число `M` - количество дорог.  
Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).  
Последняя строка содержит маршрут (откуда и куда нужно доехать).  
_Формат выходных данных:_  
Вывести длину самого выгодного маршрута.