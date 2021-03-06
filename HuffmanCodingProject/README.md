# Алгоритъм на Хъфман за компресия на данни
## Кратко описание на алгоритъма
Целта на алгоритъма е да направи по-добра степен на компресия върху символите в текста, които се срещат най-често. Това става чрез двоично дърво.

Алгоритъмът за създаване на двоичното дърво е следният:

    1. Прочита се входният текст.
    2. Създава таблица с броя на срещанията на всеки символ в текста.
    3. За всеки елемент от таблицата се създава  двоично дърво от един възел от вида: `Node{int брой срещания, char символ, left *Node, right *Node}` и ги слагаме в приоритетна опашка, в която възлите с най-малък брой срещания имат най-голям приоритет.
    4. Докато опашката не е празна:
        - взимаме най-малките два възела и ги премахваме от опашката
        - създаваме нов възел, който има за ляво и дясно поддърво двата възела, в който броят на срещанията е сборът от броя срещания на лявото и дясното поддърво, а символът му е без значение
        - добавяме новосъздадения възел в опашката
    5. Последният възел в опашката е дървото, който съдържа всички останали възли

На всяко ребро от дървото съпоставяме числото 0 - за ляво ребро и 1 - за дясно. Компресираната стойност за даден символ представлява пътят от корена на дървото до листото, което съдържа този символ. 

Така колкото по-голям брой срещания има дадено листо, толкова по-кратък е пътя от корена до него.


За повече информация [тук](https://en.wikipedia.org/wiki/Huffman_coding).

**Пример:**
![Demo](img/image.png)

## Начин на използване на програмата

Програмата се стартира с въвеждането на вече компилирания файл, следван от ключовата дума *huffman* и комбинация от флагове.

**Програмата поддържа следните флагове:**

    -c                  --- режим на компресия
    -d                  --- режим на декомпресия
    -i <filename>       --- входен файл
    -о <filename>       --- изходен файл
    -t <filename>       --- файл с дървото на Хъфман(по избор)
    -v <filename>       --- .dot файл с дървото на Хъфман(по избор)

**Пример:**

    ./a.out huffman -c -i "src.txt" -o "decodedSrc.txt" -v "treeviz.dot"

**Важно: при декомпресия задължително трябва да се подава дървото на Хъфман или чрез *-t* или в началото на входния файл** 