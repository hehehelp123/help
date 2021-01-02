#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#define LIMIT 1000000

using namespace std;

struct node                                                                             //узлы
{
    int type = 0;
    int routeLength = LIMIT;
    vector<int> connectionVec;
    string timeTrace;
};

int _recursiveCounter = 0;
string _recursiveTrace = "";

void _setLengthAndTrace(node* nodeMas[], int i, int routeLength = 1, string k = "");

string _shorterPath(node* nodeMas[], int nodeMas_size, int startPoint, int endPoint)
{
    for (int j = 0; j < nodeMas_size; ++j) nodeMas[j]->routeLength = LIMIT;
    for (int j = 0; j < nodeMas_size; ++j) nodeMas[j]->timeTrace = "";
    _setLengthAndTrace(nodeMas, startPoint);
    if (nodeMas[endPoint]->routeLength != LIMIT) return to_string(nodeMas[endPoint]->routeLength) + nodeMas[endPoint]->timeTrace;
    else return "none";
    for (int j = 0; j < nodeMas_size; ++j) nodeMas[j]->routeLength = LIMIT;
    for (int j = 0; j < nodeMas_size; ++j) nodeMas[j]->timeTrace = "";
}

void _setLength(node* nodeMas[], int i, int routeLength = 1)                                             //расстояния
{
    if (nodeMas[i]->routeLength <= routeLength) return;
    nodeMas[i]->routeLength = routeLength;
    for (int j = 0; j < nodeMas[i]->connectionVec.size(); ++j)
    {
        _setLength(nodeMas, nodeMas[i]->connectionVec[j], routeLength + 1);
    }
}

void _setLengthAndTrace(node* nodeMas[], int i, int routeLength, string k)                                     //расстояния и пути
{
    if (nodeMas[i]->routeLength <= routeLength) return;
    nodeMas[i]->routeLength = routeLength;
    nodeMas[i]->timeTrace = k + " " + to_string(i);
    for (int j = 0; j < nodeMas[i]->connectionVec.size(); ++j)
    {
        _setLengthAndTrace(nodeMas, nodeMas[i]->connectionVec[j], routeLength + 1, nodeMas[i]->timeTrace);
    }
}

void _setTypes(node* nodeMas[], int i, int type)                                                 //бьет на подграфы
{
    if (nodeMas[i]->type) return;
    nodeMas[i]->type = type;
    ++_recursiveCounter;
    for (int j = 0; j < nodeMas[i]->connectionVec.size(); ++j)
    {
        _setTypes(nodeMas, nodeMas[i]->connectionVec[j], type);
    }
}
/*
Вопрос 1. Сколько в нём рёбер?
Изолятом назывется вершина, не связанная ни с одной другой вершиной.
Вопрос 2. Сколько в графе изолятов? Выведите полный список, упорядоченный по возрастанию
Степенью вершины называется количество ребёр, которые связывают её с другими вершинами.
Вопрос 3. Найдите вершину(вершины) с самой большой степенью.
Кратчайший путь - минимальная сумма рёбер, составляющих путь от одной вершины к другой.
Компонента связности - это максимальный связный подграф. Диаметр - это самый длинный кратчайший путь
Вопрос 4. Найдите диаметр компоненты связности графа
Вопрос 5. Найдите кратчайший путь от A до B. A: 26 B: 279
Вопрос 6. Найдите кратчайший путь от C до D. C: 892 D: 52
Вопрос 7. Найдите кратчайший путь от E до F. E: 843 F: 817
* ответ должен включать в себя длину пути и последовательность вершин
** если путь отсутствует, то сделайте соответствующую пометку.
Удалите из графа следующие вершины: [708, 332, 401, 435, 596, 347, 348]
Вопрос 8. Сколько ребёр в графе?
Вопрос 9. Сколько в графе изолятов? Выведите полный список, упорядоченный по возрастанию
Вопрос 10. Найти вершину(вершины) с самой большой степенью
Вопрос 11. Найдите диаметр компоненты связности графа
Вопрос 12. Найдите кратчайший путь от A до B
Вопрос 13. Найдите кратчайший путь от C до D
Вопрос 14. Найдите кратчайший путь от E до F*/ 

int main()
{
    const int masSize = 1000;
    node* nodeMas[masSize];
    for (int i = 0; i < masSize; ++i) nodeMas[i] = new node();
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    int lines = 0;
    for (int numberNode; cin >> numberNode;)
    {
        int connectionNode;
        cin >> connectionNode;
        nodeMas[numberNode]->connectionVec.push_back(connectionNode);
        nodeMas[connectionNode]->connectionVec.push_back(numberNode);
        ++lines;
    }
    cout << "1: " << lines << endl;                                                      //Вопрос 1 
    int countEnclave = 0;
    cout << "2:" << endl;                                                               //Вопрос 2
    for (int i = 0; i < masSize; ++i) if (!nodeMas[i]->connectionVec.size())
    {
        cout << i << endl;
        ++countEnclave;
    }
    cout << "" << countEnclave << endl;
    vector<int> listOfMaximum;
    int maxDeg = 0;
    for (int i = 0; i < masSize; ++i)                                                      //наибольшая степень
    {
        if (maxDeg > nodeMas[i]->connectionVec.size()) continue;
        if (maxDeg == nodeMas[i]->connectionVec.size()) listOfMaximum.push_back(i);
        if (maxDeg < nodeMas[i]->connectionVec.size())
        {
            maxDeg = nodeMas[i]->connectionVec.size();
            listOfMaximum.resize(0);
            listOfMaximum.push_back(i);
        }
    }
    cout << "3: " << maxDeg;                                                         //Вопрос 3
    for (int i = 0; i < listOfMaximum.size(); ++i)
    {
        cout << " " << listOfMaximum[i];
    }
    cout << endl;
    vector<int> types;
    int routeLength = 1;
    int maxGraphSize = 0;
    int startNode;
    int type = 0;
    for (int i = 0; i < masSize; ++i)                                                  //разбиение на подграфы
    {
        if (nodeMas[i]->type) continue;
        _recursiveCounter = 0;
        _setTypes(nodeMas, i, routeLength);
        ++routeLength;
        int timeMax = _recursiveCounter;
        if (timeMax > maxGraphSize)
        {
            maxGraphSize = timeMax;
            startNode = i;
            type = nodeMas[i]->type;
        }
    }
    int diametr = 0;
    string trace;
    int index;
    for (int i = startNode; i < masSize; ++i)                                                 //Поиск диаметра компоненты связности
    {
        if (nodeMas[i]->type != type) continue;
        _recursiveCounter = 0;
        _recursiveTrace = "";
        _setLength(nodeMas, i);
        int timeMax = 0;
        for (int j = 0; j < masSize; ++j)
        {
            if (timeMax < nodeMas[j]->routeLength && nodeMas[j]->routeLength != LIMIT)
            {
                timeMax = nodeMas[j]->routeLength;
                _recursiveCounter = nodeMas[j]->routeLength;
                _recursiveTrace = nodeMas[j]->timeTrace;
            }
        }
        if (_recursiveCounter > diametr)
        {
            diametr = _recursiveCounter;
            trace = _recursiveTrace;
            index = i;
        }
        for (int j = 0; j < masSize; ++j) nodeMas[j]->routeLength = LIMIT;
    }
    cout << "4: " << diametr << " " << trace << endl;                                   //Вопрос 4
    _setLengthAndTrace(nodeMas, index);
    for (int j = 0; j < masSize; ++j)
    {
        if (nodeMas[j]->routeLength == diametr)
        {
            cout << nodeMas[j]->timeTrace << endl;
            break;
        }
    }
    cout << "5: " << _shorterPath(nodeMas, masSize, 26, 279) << endl;
    cout << "6: " << _shorterPath(nodeMas, masSize, 892, 52) << endl;
    cout << "7: " << _shorterPath(nodeMas, masSize, 843, 817) << endl;

    vector<int> forDelete = { 708, 332, 401, 435, 596, 347, 348 };

    for (int k = 0; k < forDelete.size(); ++k)                                           //удаление лишних
    {
        for (int i = 0; i < masSize; ++i)
        {
            for (int j = 0; j < nodeMas[i]->connectionVec.size(); ++j)
            {
                if (i == forDelete[k] || i % 17 == 0)
                {
                    nodeMas[i]->connectionVec.resize(0);
                    break;
                }
                if (nodeMas[i]->connectionVec[j] == forDelete[k] || nodeMas[i]->connectionVec[j]%17 == 0)
                {
                    nodeMas[i]->connectionVec.erase(nodeMas[i]->connectionVec.begin() + j);
                    --j;
                }
            }
        }
    }
    lines = 0;
    for (int i = 0; i < masSize; ++i)
    {
        lines += nodeMas[i]->connectionVec.size();
    }
    cout << "8: " << lines/2 << endl;                                                //Вопрос 8

    countEnclave = 0;
    cout << "9:" << endl;                                                           //Вопрос 9
    for (int i = 0; i < masSize; ++i)                                                  //Изоляты
    {
        if (!nodeMas[i]->connectionVec.size())
        {
            int fl = 0;
            for (int j = 0; j < forDelete.size(); ++j) if (i == forDelete[j] || i % 17 == 0) fl = 1;
            if (fl) continue;
            cout << i << endl;
            ++countEnclave;
        }
    }
    cout << "" << countEnclave << endl;
    listOfMaximum.resize(0);
    maxDeg = 0;
    for (int i = 0; i < masSize; ++i)                                                  //наибольшая степень
    {
        if (maxDeg > nodeMas[i]->connectionVec.size()) continue;
        if (maxDeg == nodeMas[i]->connectionVec.size()) listOfMaximum.push_back(i);
        if (maxDeg < nodeMas[i]->connectionVec.size())
        {
            maxDeg = nodeMas[i]->connectionVec.size();
            listOfMaximum.resize(0);
            listOfMaximum.push_back(i);
        }
    }
    cout << "10: " << maxDeg;                                                        //Вопрос 10
    for (int i = 0; i < listOfMaximum.size(); ++i)
    {
        cout << " " << listOfMaximum[i];
    }
    cout << endl;
    types.resize(0);
    routeLength = 1;
    maxGraphSize = 0;
    type = 0;
    for (int i = 0; i < masSize; ++i)
    {
        nodeMas[i]->type = 0;
        nodeMas[i]->routeLength = 0;
    }
    for (int i = 0; i < masSize; ++i)                                                  //разбиение на подграфы
    {
        if (nodeMas[i]->type) continue;
        _recursiveCounter = 0;
        _setTypes(nodeMas, i, routeLength);
        int timeMax = _recursiveCounter;
        if (timeMax > maxGraphSize)
        {
            maxGraphSize = timeMax;
            startNode = i;
            type = nodeMas[i]->type;
        }
    }
    diametr = 0;
    for (int i = 11; i < masSize; ++i)                                                 //Диаметр
    {
        if (nodeMas[i]->type != type) continue;
        _recursiveCounter = 0;
        _recursiveTrace = "";
        _setLength(nodeMas, i);
        int timeMax = 0;
        for (int j = 0; j < masSize; ++j)
        {
            if (timeMax < nodeMas[j]->routeLength && nodeMas[j]->routeLength != LIMIT)
            {
                timeMax = nodeMas[j]->routeLength;
                _recursiveCounter = nodeMas[j]->routeLength;
                _recursiveTrace = nodeMas[j]->timeTrace;
            }
        }
        if (_recursiveCounter > diametr)
        {
            diametr = _recursiveCounter;
            trace = _recursiveTrace;
            index = i;
        }
        for (int j = 0; j < masSize; ++j) nodeMas[j]->routeLength = LIMIT;
    }
    cout << "11: " << diametr << " " << trace << endl;                                  //Вопрос 11
    _setLengthAndTrace(nodeMas, index);
    for (int j = 0; j < masSize; ++j)
    {
        if (nodeMas[j]->routeLength == diametr)
        {
            cout << nodeMas[j]->timeTrace << endl;
            break;
        }
    }
    cout << "12: " << _shorterPath(nodeMas, masSize, 26, 279) << endl;                     //Вопрос 12
    cout << "13: " << _shorterPath(nodeMas, masSize, 892, 52) << endl;                     //Вопрос 13
    cout << "14: " << _shorterPath(nodeMas, masSize, 843, 817) << endl;                    //Вопрос 14
}
