#include <iostream>
using namespace std;

template <typename T>
/*
Каждая вершина содержит минимум три поля: для хранения данных, указатель для левой вершины и указатель для правой вершины
Структура в C++ представляет собой производный тип данных, который представляет какую-то определенную сущность, также как и класс. 
Структура также может определять переменные, функции, конструкторы, деструкторы. 
Cтруктуры служат для хранения каких-то общедоступных данных в виде публичных переменных(нужно хранить элементы разных типов данных в одном типе данных).
*/
struct Branch {//структура для узлов дерева
    T item;
    struct Branch *left;
    struct Branch *right;

   Branch(T n_item) {
        item = n_item;
        left = NULL;
        right = NULL;
    }
};
template <typename T>
class MyBinaryTree {//класс для дерева
private:
    Branch<T> *tree;//самое начало дерева

    void print_tree(Branch<T> *branch, int str)const {//рекурсивная функция для печати дерева
        
        if (!branch) {//если ветки нет (тоже самое, что и branch == NULL)
            for (int i = 0; i < str*4; i++) {
                cout << " ";
            }
            cout << "##" << endl;//печатаем, что значений никаких
            return;//выходим из цикла и дальше
        }

        print_tree(branch->right, str+1);//рекурсивно спускаемся и считаем уровни 
        for (int i = 0; i < str*4; i++) {
            cout << " ";
        }
        cout <<  branch->item << endl;//печатаем значение при вершине(которая на уровень выше)
        print_tree(branch->left, str+1);//смотрим, что слева
    }

    void clear(Branch<T> *branch) {//функция для удаления дерева, начиная с указанной ветви
        if (branch) {
            clear(branch->right);
            clear(branch->left);
            delete branch;
        }
    }

public:

    MyBinaryTree() {
        tree = NULL;
    }
    MyBinaryTree(T n_item) {
        tree = new Branch<T>(n_item);
    }
    ~MyBinaryTree() {
       clear(tree); //полное удаление дерева
       tree = NULL;
    }

    void push(T n_item) {
        if (!tree) {//если дерева вообще еще нет, записываем самое первое значение
            tree = new Branch<T>(n_item);
        } else {
            Branch<T> *branch = tree; //фиксируем значение корня в переменной и
            while(true) {//чтоб цикл повторялся пока не внесем значение
                if (n_item < branch->item) { //если новое значение меньше старого
                    if (!branch->left) {//и место свободно
                        branch->left = new Branch<T>(n_item);//записываем и заканчиваем
                        break;
                    } else {
                        branch = branch->left;//переходим на следующий/занятый узел и рассматриваем все то же самое для него
                    }
                } else if (n_item > branch->item) {
                    if (!branch->right) {
                        branch->right = new Branch<T>(n_item);
                        break;
                    } else {
                        branch = branch->right;
                    }
                } else {//если вдруг будет элемент, который уже был, сразу заканчиваем
                    break;
                }
            }
        }
    }
  
/*Стандартный выходной поток cout имеет тип std::ostream. Поэтому первый параметр (левый операнд) операции << представляет ссылку на неконстантный объект ostream. 
Данный объект не должен представлять константу, так как запись в поток изменяет его состояние.
Второй параметр оператора определяется как ссылка на константный объекта класса, который надо вывести в поток.
Для совместимости с другими операторами переопределяемый оператор должен возвращать значение параметра std::ostream.
*/
    friend ostream& operator<< (ostream& out, const MyBinaryTree<T>& Tree){
        Tree.print_tree(Tree.tree,0);
        return out;
    }
};

int main() {
    MyBinaryTree<int> a;
    a.push(10);
    a.push(20);
    a.push(3);
    a.push(5);
    a.push(11);
    a.push(4);
    a.push(2);

    cout << a << endl << '\v' << '\v' << '\v';

    MyBinaryTree<double> b;
    b.push(5.349);
    b.push(2.42);
    b.push(23.3);
    b.push(5);
    b.push(11.11);
    b.push(4);
    b.push(88.2);

    cout << b << endl << '\v' << '\v' << '\v';

    MyBinaryTree<string> c;//строки сравниваются посимвольно и 99 > 123, так как 9 > 1
    c.push("478");
    c.push("345");
    c.push("23");
    c.push("73");
    c.push("981");
    c.push("1123");
    c.push("335");

    cout << c << endl << '\v' << '\v' << '\v';

    return 0;
}
/*
Шаблонный класс - класс, работающий с разными типами данных, для каждого типа не нужна разая реализация
template - говорит, что класс шаблонный <typename> - говрит, что используются обобщенные типы данных
T - обобщенный тип данных
Так как класс шаблонный при создании объекта мы должны указать тип данных, например, MyBinaryTree<int> a
*/