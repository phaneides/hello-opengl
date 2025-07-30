
#include <iostream>
#include <cmath> // Para std::sqrt

struct Vector2D {
    float x;
    float y;

    // Suma de vectores
    Vector2D operator+(const Vector2D& v) const {
        return {x + v.x, y + v.y};
    }

    // Resta de vectores 
    
    Vector2D operator-(const Vector2D& v) const {
        return {x - v.x, y - v.y};

    }

    // Multiplicación por escalar (derecha)
    Vector2D operator*(float a) const {
        return {a * x, a * y};
    }

    // División por escalar
    
    Vector2D operator/(float a) const {
        return {x/a, y/a};
    }

    // Norma del vector (magnitud)
    float norm() const {
        return std::sqrt(x * x + y * y);
    }

    // Normalizar vector 
    
    Vector2D unit() const {
        float mag = norm();
        if (mag == 0.0f) return {0, 0};

        return  *this/mag;
    }

    // Producto punto (dot product)
    float dot(const Vector2D& v) const {
        return x * v.x + y * v.y;
    }

    float angle(const Vector2D& other) const {
        float dotProduct = this->dot(other);
        float norms = this->norm() * other.norm();

        if (norms == 0.0f) return 0.0f; // Evita división por cero

        float cosTheta = dotProduct / norms;

        // Corrección numérica: asegurar que el valor esté en [-1, 1]
        if (cosTheta > 1.0f) cosTheta = 1.0f;
        if (cosTheta < -1.0f) cosTheta = -1.0f;

        return std::acos(cosTheta);
    }

    // Impresión con <<
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }

    // Multiplicación escalar por izquierda
    friend Vector2D operator*(float a, const Vector2D& v) {
        return {a * v.x, a * v.y};
    }
};



int main() {
    Vector2D A = {1.0f, 0.0f};
    Vector2D B = {1.0f, 1.0f};

    Vector2D C = A + B;
    Vector2D D = 2.0f * A;
    float norm_A = A.norm();
    float A_dot_B = A.dot(B);
    Vector2D unit_B = B.unit();

    std::cout << "A = " << A << "\n";
    std::cout << "B = " << B << "\n";
    std::cout << "A + B = " << C << "\n";
    std::cout << "2 * A = " << D << "\n";
    std::cout << "|A| = " << norm_A << "\n";
    std::cout << "A · B = " << A_dot_B << "\n";
    std::cout << "unit(B) = " << unit_B << "\n";
    std::cout << "Ángulo (radianes): " << A.angle(B) << "\n";

    return 0;
}

