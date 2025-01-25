#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
public:
    std::string name;
    bool chopped;
    float animationTime;

    Ingredient(const std::string& ingredientName)
        : name(ingredientName), chopped(false), animationTime(0.0f) {}
};

#endif // INGREDIENT_H
