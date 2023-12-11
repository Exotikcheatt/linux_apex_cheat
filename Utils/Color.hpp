#pragma once
#include "../imgui/imgui.h"
#include <stdexcept>

struct Color {
    float red;
    float green;
    float blue;

    bool operator==(const Color& other) const {
        return (red == other.red) && (green == other.green) && (blue == other.blue);
    }

    bool operator!=(const Color& other) const {
        return !(*this == other);
    }

    // Implementierung des Operator[]
    float& operator[](int index) {
        if (index == 0) return red;
        else if (index == 1) return green;
        else if (index == 2) return blue;
        else throw std::out_of_range("Index out of range");
    }

    // Konstante Überladung für den Zugriff auf Farbwerte
    const float& operator[](int index) const {
        if (index == 0) return red;
        else if (index == 1) return green;
        else if (index == 2) return blue;
        else throw std::out_of_range("Index out of range");
    }

    static void ImGuiColorToColor(const float imguiColor[4], Color* colorArray) {
    colorArray->red = imguiColor[0] * 10;
    colorArray->green = imguiColor[1] * 10;
    colorArray->blue = imguiColor[2] * 10;
    }
};