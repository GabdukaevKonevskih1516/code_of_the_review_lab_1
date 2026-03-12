#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <climits>

// Проверка валидности количества предметов 
bool IsCountValid(int InCount);

// Проверка валидности веса 
bool IsWeightValid(int InWeight);

// Основная функция решения задачи археолога 
void SolveArchaeologistTask();
