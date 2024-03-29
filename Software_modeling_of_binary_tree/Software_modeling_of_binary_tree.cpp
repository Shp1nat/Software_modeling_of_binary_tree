#include <iostream>
#include <vector>
using namespace std;

struct NodeTree
{
    int data;
    NodeTree* left;
    NodeTree* right;
    NodeTree() : left(nullptr), right(nullptr), data(0) {};
};

class Tree
{
private:
    NodeTree* root;
    int countOfRoots;
    vector <int> forOutPut;
public:
    Tree() : root(nullptr), countOfRoots(0) {};

    bool isEmpty()
    {
        if (root == nullptr)
            return true;
        else
            return false;
    }

    void Insert(int value)
    {
        NodeTree* node = new NodeTree; //выделяем в буфер "node" память для будущего присвоения этой памяти в нужное место
        node->data = value;
        if (isEmpty()) //дерево пусто или вершина отсутствует
        {
            root = node;
            countOfRoots++;
        }
        else
        {
            NodeTree* fakeRoot = root; //тот указатель по которому мы будем двигаться, чтобы не менять основное поле класса
            while (true) //бесконечное движение
            {
                if (value == fakeRoot->data) return; //если нашли совпадение элемента - выход
                if (value > fakeRoot->data) //если наш вставляемый элемент больше текущего, на котором мы "стоим", то узнаем равен ли справа от него элемент "нулптр"
                {
                    if (fakeRoot->right == nullptr) //если равен, то вставляем на это место нашу выделенную память с новым значением и ретюрнем
                    {
                        fakeRoot->right = node;
                        countOfRoots++;
                        return;
                    }
                    fakeRoot = fakeRoot->right; //если не равен, то цикл не ретюрнется и тогда наш "буфер" по которому мы двигаемся сместится просто на шаг вправо
                }
                if (value < fakeRoot->data) //то же самое, что и с "правом", только с "левом"
                {
                    if (fakeRoot->left == nullptr)
                    {
                        fakeRoot->left = node;
                        countOfRoots++;
                        return;
                    }
                    fakeRoot = fakeRoot->left;
                }
            }

        }

    }

    bool IsFound(int _value)
    {
        NodeTree* fakeRoot = root;
        while (true)
        {
            if (fakeRoot == nullptr) return false;
            if (fakeRoot->data == _value) return true;
            if (fakeRoot->data > _value)
            {
                if (fakeRoot->left == nullptr)
                    return false;
                fakeRoot = fakeRoot->left;
            }
            if (fakeRoot->data < _value)
            {
                if (fakeRoot->right == nullptr)
                    return false;
                fakeRoot = fakeRoot->right;
            }
        }
    }

    void toPushAllElementsIntoVector(NodeTree* p)
    {
        if (p != nullptr)
        {
            toPushAllElementsIntoVector(p->left);
            forOutPut.push_back(p->data);
            toPushAllElementsIntoVector(p->right);
        }
    }

    vector<int> GetFullVector()
    {
        toPushAllElementsIntoVector(root);
        return forOutPut;
    }

    void ClearVector()
    {
        forOutPut.clear();
    }

    int returnDelete(int item)
    {
        NodeTree** q, * z;

        q = &root;
        z = root;
        //Поиск элемента удаления
        for (;;)
        {
            if (z == nullptr)
                return NULL;
            else if (item == z->data)
                break;
            else if (item > z->data)
            {
                q = &z->right;
                z = z->right;
            }
            else
            {
                q = &z->left;
                z = z->left;
            }
        }
        //Первый случай (удаляемый узел (на который указывает z) не имеет дочернего правого узла)
        if (z->right == nullptr)
            *q = z->left;
        else
        {
            NodeTree* y = z->right;
            /*Второй случай: удаляемый узел (на который указывает z) имеет необязательный левый и
            обязательный правый дочерний узел, но тот не имеет левого дочернего узла. */
            if (y->left == nullptr)
            {
                y->left = z->left;
                *q = y;
            }
            /*Третий случай: удаляемый узел имеет левый и правый дочерние узлы и те тоже имеют левый и
            правый дочерние узлы*/
            else
            {
                NodeTree* x = y->left;
                while (x->left != nullptr)
                {
                    y = x;
                    x = y->left;
                }
                y->left = x->right;
                x->left = z->left;
                x->right = z->right;
                *q = x;
            }
        }
        countOfRoots--;
        free(z); //Удаление элемента
        return 1;
    }

};

void OutPut(vector<int> _vector)
{
    for (unsigned i = 0; i < _vector.size(); i++)
    {
        cout << _vector[i] << " ";
    }
}

void Find(bool _bool)
{
    if (_bool)
        cout << "Совпадение найдено!";
    else
        cout << "Совпадений не найдено!";
}

void Delete(int a)
{
    if (a)
        cout << "Элемент найден и удален!";
    else
        cout << "Элемент не был найден!";
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int countOfElements = 0;
    Tree tr;
    int choice = 0, element = 0;
    cout << "1. Добавить элементы в дерево\n2. Поиск элемента\n3. Вывод дерева\n4. Удалить элемент" << endl;
    while (true)
    {
        cout << "\nВыберите действие : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "Сколько элементов вы хотите добавить в дерево? : ";
            cin >> countOfElements;
            int* arr = new int[countOfElements];
            cout << "Введите элементы через пробел: ";
            for (int i = 0; i < countOfElements; i++)
            {
                cin >> arr[i];
                tr.Insert(arr[i]);
            }
            delete[] arr;
            break;
        }
        case 2:
        {
            cout << "Введите значение элемента: ";
            cin >> element;
            Find(tr.IsFound(element));
            break;
        }
        case 3:
        {
            OutPut(tr.GetFullVector());
            tr.ClearVector();
            break;
        }
        case 4:
        {
            cout << "Введите удаляемый элемент: ";
            cin >> element;
            Delete(tr.returnDelete(element));
        }
        }
    }
    return 0;
}
