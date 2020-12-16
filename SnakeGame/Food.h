#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include <QGraphicsItem>
#include <vector>

enum PROPERTY{n,su,sd,el}; /*n:normal su:speed up sd:speed down el:extralife*/

class Food:public QObject{
    Q_OBJECT
public:
    std::vector<QGraphicsRectItem*> Item_Food;
    std::vector<PROPERTY> Food_Property;
    void setFood(int i);
    void setFoodColor(int i);
    Food();
};

#endif // FOOD_H
