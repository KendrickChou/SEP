#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include <QGraphicsItem>
#include <vector>

enum PROPERTY{n,su,sd,el,ds}; /*n:normal su:speed up sd:speed down el:extralife ds:doublescore*/

class Food:public QObject{
    Q_OBJECT
public:
    std::vector<QGraphicsRectItem*> Item_Food;
    std::vector<PROPERTY> Food_Property;//the property of Item_Food[i]
    void setFood(int i);// make a new food
    void setFoodColor(int i);//set the food color
    Food();
};

#endif // FOOD_H
