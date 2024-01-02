#pragma once
#include "calc.h"
#include <SFML/Graphics.hpp>
#include "2D.h"
#include "Camera.h"
#include "essential.h"


void draw(obj M, sf::RenderWindow& window, Camera cam, Vec4 light);
