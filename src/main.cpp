#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>

#include "contour_io.h"
#include "contour_features.h"
#include "compare.h"

//В этом файле собираем все, что было до этого и сравниваем
// с эталонными файалами (они должны быть изначально)

// Структура одного эталона
struct Prototype {
    std::string objectName;
    std::vector<Feature> features;
};

// Загрузка одного эталонного контура
// получаем признаки 
// добавляем запись
void addPrototype(
    std::vector<Prototype>& database,
    const std::string& objectName,
    const std::string& filename,
    double eps
) {
    auto contour = readContour(filename);
    auto features = extractFeatures(contour, eps);
    database.push_back({objectName, features});
}

int main(int argc, char* argv[]) {

    double eps = 0.3;

    // Чтение входного
    auto inputContour = readContour(argv[1]);
    auto inputFeatures = extractFeatures(inputContour, eps);

    // Формирование базы эталонов
    std::vector<Prototype> database;

    // Добавление в базу координат Самолета
    addPrototype(database, "AIRPLANE", "data/airplane/airplane_a0_s1.0.txt", eps);
    addPrototype(database, "AIRPLANE", "data/airplane/airplane_a30_s1.0.txt", eps);
    addPrototype(database, "AIRPLANE", "data/airplane/airplane_a60_s1.0.txt", eps);
    addPrototype(database, "AIRPLANE", "data/airplane/airplane_a90_s1.0.txt", eps);

    addPrototype(database, "AIRPLANE", "data/airplane/airplane_a0_s1.5.txt", eps);
    addPrototype(database, "AIRPLANE", "data/airplane/airplane_a30_s1.5.txt", eps);
    addPrototype(database, "AIRPLANE", "data/airplane/airplane_a60_s1.5.txt", eps);
    addPrototype(database, "AIRPLANE", "data/airplane/airplane_a90_s1.5.txt", eps);

    addPrototype(database, "AIRPLANE", "data/airplane/airplane_a0_s2.0.txt", eps);
    addPrototype(database, "AIRPLANE", "data/airplane/airplane_a30_s2.0.txt", eps);
    addPrototype(database, "AIRPLANE", "data/airplane/airplane_a60_s2.0.txt", eps);
    addPrototype(database, "AIRPLANE", "data/airplane/airplane_a90_s2.0.txt", eps);


    // Добавление в базу координат Танка
    addPrototype(database, "TANK", "data/tank/tank_a0_s1.0.txt", eps);
    addPrototype(database, "TANK", "data/tank/tank_a30_s1.0.txt", eps);
    addPrototype(database, "TANK", "data/tank/tank_a60_s1.0.txt", eps);
    addPrototype(database, "TANK", "data/tank/tank_a90_s1.0.txt", eps);

    addPrototype(database, "TANK", "data/tank/tank_a0_s1.5.txt", eps);
    addPrototype(database, "TANK", "data/tank/tank_a30_s1.5.txt", eps);
    addPrototype(database, "TANK", "data/tank/tank_a60_s1.5.txt", eps);
    addPrototype(database, "TANK", "data/tank/tank_a90_s1.5.txt", eps);

    addPrototype(database, "TANK", "data/tank/tank_a0_s2.0.txt", eps);
    addPrototype(database, "TANK", "data/tank/tank_a30_s2.0.txt", eps);
    addPrototype(database, "TANK", "data/tank/tank_a60_s2.0.txt", eps);
    addPrototype(database, "TANK", "data/tank/tank_a90_s2.0.txt", eps);

    // Добавление в базу координат Корабля
    addPrototype(database, "SHIP", "data/ship/ship_a0_s1.0.txt", eps);
    addPrototype(database, "SHIP", "data/ship/ship_a30_s1.0.txt", eps);
    addPrototype(database, "SHIP", "data/ship/ship_a60_s1.0.txt", eps);
    addPrototype(database, "SHIP", "data/ship/ship_a90_s1.0.txt", eps);

    addPrototype(database, "SHIP", "data/ship/ship_a0_s1.5.txt", eps);
    addPrototype(database, "SHIP", "data/ship/ship_a30_s1.5.txt", eps);
    addPrototype(database, "SHIP", "data/ship/ship_a60_s1.5.txt", eps);
    addPrototype(database, "SHIP", "data/ship/ship_a90_s1.5.txt", eps);

    addPrototype(database, "SHIP", "data/ship/ship_a0_s2.0.txt", eps);
    addPrototype(database, "SHIP", "data/ship/ship_a30_s2.0.txt", eps);
    addPrototype(database, "SHIP", "data/ship/ship_a60_s2.0.txt", eps);
    addPrototype(database, "SHIP", "data/ship/ship_a90_s2.0.txt", eps);


    // создаем словари для дальнейшего сравнения
    std::map<std::string, double> scoreSum;
    std::map<std::string, int> scoreCount;

    // Сравнение с каждым элементом 
    for (const auto& proto : database) {
        double d = compareContours(inputFeatures, proto.features);
        scoreSum[proto.objectName] += d;
        scoreCount[proto.objectName]++;
    }

    // Выбор наиболее вероятного объекта 
    std::string bestObject;
    double bestScore = std::numeric_limits<double>::max();

    // Выводим все наши значения по формуле ключ : значение
    
    for (const auto& [name, sum] : scoreSum) {
        double avg = sum / scoreCount[name];
        std::cout << "Object " << name
                  << " average distance: " << avg << std::endl;

        if (avg < bestScore) {
            bestScore = avg;
            bestObject = name;
        }
    }

    std::cout << "\nMost probable object: " << bestObject << std::endl;
    return 0;
}
