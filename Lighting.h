#pragma once
#include <SFML/Graphics.hpp>
#include "essential.h"
#include "calc.h"

sf::Color applyLighting2(Vec4 light, Vec4 normal, Vec4 view, float ambient, material m = default_material);

