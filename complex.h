#ifndef __COMPLEX_H__
#define __COMPLEX_H__
#include <iostream>
#include "types.h"
using namespace std;

template<typename... Args>
auto Sumar(Args... args) {
    return (args + ...); // fold expression
}


/**
 * @file complex.h
 * @brief Declaración de la clase Complex.
 *        Esta clase representa números complejos y 
 *        proporciona operaciones básicas como suma,
 *        resta, multiplicación y división.
 */

// Wrapper para número real puro
struct PureReal {
    Real value;
    explicit PureReal(Real v) : value(v) {}
};

// Wrapper para número imaginario puro
struct PureImag {
    Imag value;
    explicit PureImag(Imag v) : value(v) {}
};

class Complex{
private:
    Real m_real; ///< Parte real del número complejo
    Imag m_imag; ///< Parte imaginaria del número complejo
public:
    // Constructor
    // 1. Tiene el mismo nombre que la clase.
    // 2. No tiene tipo de retorno (ni siquiera void).
    // 3. Puede haber mas de 1 (sobrecarga) y se diferencian por la cantidad o tipo de parámetros.
    // 4. Se llama automáticamente al crear un objeto de la clase.
    // 5. Un constructor puede llamar a otro constructor (delegación de constructores).
    // 6. Si no se define un constructor, el compilador genera uno por defecto (sin parámetros).
    // 7. Si se define un constructor con parámetros, el compilador no genera el constructor por defecto.
    Complex(Real r = 0.0, Imag i = 0.0) { ///< Constructor con valores por defecto
        setReal(r);     setImag(i);
    } 
    Complex(const Complex& other) { ///< Constructor de copia
        setReal(other.getReal());     setImag(other.getImag());
        cout << "Copia de: " << other.m_real << ", " << other.m_imag << endl;
    }
    // TODO: Crear Move constructor
    
    /** Destructor:
    // 1. Tiene el mismo nombre que la clase pero con ~ al inicio.
    // 2. No tiene tipo de retorno (ni siquiera void).
    // 3. No puede tener parámetros.
    // 4. Se llama automáticamente al destruir un objeto de la clase (cuando sale de ámbito o se elimina).
    // 5. Se utiliza para liberar recursos (memoria, archivos, conexiones, etc.) que el objeto haya adquirido durante su vida útil.
    // 6. Solo puede haber un uno por clase (no hay sobrecarga).
    // 7. Es recomendable que siempre sea virtual si la clase 
    //    está destinada a ser una clase base para herencia,
    //    para asegurar que se llame al destructor correcto
    //    en caso de eliminación a través de un puntero a la clase base.
    */
    ~Complex(){
        cout << "Destructor de Complex(" << m_real << ", " << m_imag << "i)" << endl;
    }
    void setReal(Real r) { m_real = r; } ///< Establecer la parte real
    Real getReal() const { return m_real; } ///< Obtener la parte real

    void setImag(Imag i) { m_imag = i; } ///< Establecer la parte imaginaria
    Imag getImag() const { return m_imag; } ///< Obtener la parte imaginaria

    Complex conjugate() const { ///< Conjugado de un número complejo
        return Complex(getReal(), -getImag());
    }

    Complex &operator=(const Complex& other) { ///< Suma de números complejos
        setReal(other.getReal());
        setImag(other.getImag());
        return *this;
    }
    Complex operator+(const Complex& other) const{ ///< Suma de números complejos
        return Complex(getReal()+other.getReal(), getImag()+other.getImag());
    }
    // Complex operator-(const Complex& other) const{ ///< Resta de números complejos
    //     return Complex(0, 0);
    // }
    //susana
    Complex operator-(const Complex& other) const{
    return Complex(m_real - other.m_real, m_imag - other.m_imag);
    }
    
    Complex operator/(const Complex& other) const{ ///< División de números complejos
        Real denominator = other.getReal() * other.getReal() + other.getImag() * other.getImag();
        if (denominator == 0) {
            throw invalid_argument("Division by zero");
        }
        // Cálculo de numerador multiplicando por la conjugada del denominador
        Complex numerator = (*this) * other.conjugate();
        // Se retorna el resultado dividiendo el numerador por el denominador
        return Complex(numerator.getReal() / denominator,
                    numerator.getImag() / denominator);
    }

    // Mas operadores aqui
    
    // 1. Bernaola Gayoso - César Raúl
    Complex& operator+=(const Complex& other) {
        m_real += other.m_real;
        m_imag += other.m_imag;
        return *this;
    }

    // 2. Cuadros-Vargas Ernesto
    // Método variadic para sumar a la parte real
    template<typename... Args>
    Complex& AddReal(Args... args) {
        m_real += Sumar(args...);
        return *this;
    }

    // Método variadic para sumar a la parte imaginaria
    template<typename... Args>
    Complex& AddImag(Args... args) {
        m_imag += Sumar(args...);
        return *this;
    }
    // 3. Diaz Tapia Adderly
    Complex &operator-=(const Complex& other) {
        m_real -= other.getReal();
        m_imag -= other.getImag();
        return *this; 
    }
    // 4. Lopez Flores Royer Amed
    // Según la IA mejor definir el operador *=, 
    //y luego definir el operador * en términos de *= 
    //por que así se evita la duplicación de código y 
    //se mejora el mantenimiento, además de que el operador
    // *= es más eficiente para objetos grandes como los complejos, 
    //ya que modifica el objeto actual en lugar de crear uno nuevo.
    Complex& operator*=(const Complex& other) {
        Real newReal = getReal() * other.getReal() - getImag() * other.getImag();
        Imag newImag = getReal() * other.getImag() + getImag() * other.getReal();
        setReal(newReal);
        setImag(newImag);
        return *this;
    }
    // 5. López Sandoval, Heiner

    /*
    // Operador /
    Complex operator/(const Complex& other) const {
        double denom = other.m_real * other.m_real + other.m_imag * other.m_imag;
        return Complex((m_real * other.m_real + m_imag * other.m_imag) / denom,
                       (m_imag * other.m_real - m_real * other.m_imag) / denom);
    }
    */

    // Operador /=
    Complex& operator/=(const Complex& other) {
        *this = *this / other;  // reutiliza operator/
        return *this;
    }

    // 6. Mallaupoma Cesar

    // 7. Miranda Zarate Jorge Luis
    // Función para calcular la potencia de un número complejo (z^n)
    Complex operator^(int n){
        Complex result(1.0, 0.0);
        for(int i = 0; i < n; ++i){
            result = result * (*this);
        }
        return result;
    }

    // 8. Riveros Guevara

    // 9. Segovia Giancarlo

    // 10. Suarez Maciel Susana Isabel
    

    // 11. Tellez Jhon
    Complex operator*(const Complex& other) const{ ///< Multiplicación de números complejos
        Real real = getReal() * other.getReal() - getImag() * other.getImag();
        Imag imag = getReal() * other.getImag() + getImag() * other.getReal();

        return Complex(real, imag);
    } 

    // 12. Valcarcel Julian

    // 13. Vilca Aguilar Luis

    // 14. Vinatea Chávez Camilo Jorge  

    void PrintX(ostream &os) const{
        os << getReal() << " + " << getImag() << "i" << endl;
    }

    // Operadores para PureReal
    Complex operator+(const PureReal& pr) const {
        return Complex(getReal() + pr.value, getImag());
    }

    friend Complex operator+(const PureReal& pr, const Complex& c) {
        return Complex(c.getReal() + pr.value, c.getImag());
    }

    Complex& operator+=(const PureReal& pr) {
        m_real += pr.value;
        return *this;
    }

    Complex operator-(const PureReal& pr) const {
        return Complex(getReal() - pr.value, getImag());
    }

    friend Complex operator-(const PureReal& pr, const Complex& c) {
        return Complex(pr.value - c.getReal(), -c.getImag());
    }

    Complex& operator-=(const PureReal& pr) {
        m_real -= pr.value;
        return *this;
    }

    // Operadores para PureImag
    Complex operator+(const PureImag& pi) const {
        return Complex(getReal(), getImag() + pi.value);
    }

    friend Complex operator+(const PureImag& pi, const Complex& c) {
        return Complex(c.getReal(), c.getImag() + pi.value);
    }

    Complex& operator+=(const PureImag& pi) {
        m_imag += pi.value;
        return *this;
    }

    Complex operator-(const PureImag& pi) const {
        return Complex(getReal(), getImag() - pi.value);
    }

    friend Complex operator-(const PureImag& pi, const Complex& c) {
        return Complex(-c.getReal(), pi.value - c.getImag());
    }

    Complex& operator-=(const PureImag& pi) {
        m_imag -= pi.value;
        return *this;
    }

    // Multiplicación: Complex * Real
    Complex operator*(Real scalar) const {
        return Complex(getReal() * scalar, getImag() * scalar);
    }

    // Multiplicación: Real * Complex (conmutativa)
    friend Complex operator*(Real scalar, const Complex& c) {
        return Complex(c.getReal() * scalar, c.getImag() * scalar);
    }

    // División: Complex / Real
    Complex operator/(Real scalar) const {
        if (scalar == 0) {
            throw invalid_argument("Division by zero");
        }
        return Complex(getReal() / scalar, getImag() / scalar);
    }

    // Operadores compuestos con escalares
    Complex& operator*=(Real scalar) {
        m_real *= scalar;
        m_imag *= scalar;
        return *this;
    }

    Complex& operator/=(Real scalar) {
        if (scalar == 0) {
            throw invalid_argument("Division by zero");
        }
        m_real /= scalar;
        m_imag /= scalar;
        return *this;
    }
    // ============================================
    // OPERADORES CON ESCALARES DIRECTOS
    // (Para casos como: 5 - c, 10 / c, etc.)
    // ============================================
    
    // Suma: Complex + Real
    Complex operator+(Real r) const {
        return Complex(getReal() + r, getImag());
    }

    // Suma: Real + Complex
    friend Complex operator+(Real r, const Complex& c) {
        return Complex(c.getReal() + r, c.getImag());
    }

    // Resta: Complex - Real
    Complex operator-(Real r) const {
        return Complex(getReal() - r, getImag());
    }

    // Resta: Real - Complex
    friend Complex operator-(Real r, const Complex& c) {
        return Complex(r - c.getReal(), -c.getImag());
    }

    // Operadores compuestos
    Complex& operator+=(Real r) {
        m_real += r;
        return *this;
    }

    Complex& operator-=(Real r) {
        m_real -= r;
        return *this;
    }

    // División: Real / Complex
    friend Complex operator/(Real scalar, const Complex& c) {
        Real denom = c.getReal() * c.getReal() + c.getImag() * c.getImag();
        if (denom == 0) {
            throw invalid_argument("Division by zero");
        }
        return Complex((scalar * c.getReal()) / denom, 
                       -(scalar * c.getImag()) / denom);
    }
};

inline ostream &operator<<(ostream &os, const Complex &c){
    return os << c.getReal() << " + " << c.getImag() << "i";
}

// Leer un Complejo desde un istream
inline istream &operator>>(istream &is, Complex &c){
    Real real;
    Imag imag;
    is >> real >> imag;
    c.setReal(real);
    c.setImag(imag);
    return is;
}

// User defined literal
// inline Complex operator"" i(long double i) { ///< Literal para números imaginarios (flotante)
//     return Complex(0.0, static_cast<Imag>(i));
// }
// inline Complex operator"" i(long double i) { ///< Literal para números imaginarios (entero)
//     return Complex(0.0, static_cast<Imag>(i));
// }
// inline Complex operator"" r(long double r) { ///< Literal para números reales (flotante)
//     return Complex(static_cast<Real>(r), 0.0);
// }
// inline Complex operator"" r(long double r) { ///< Literal para números reales (entero)
//     return Complex(static_cast<Real>(r), 0.0);
// }

// Literal para imaginarios puros
inline Complex operator"" _i(long double i) {
    return Complex(0.0, static_cast<Imag>(i));
}

inline Complex operator"" _i(unsigned long long i) {
    return Complex(0.0, static_cast<Imag>(i));
}

// Literal para reales puros (opcional, ya funciona con el constructor)
inline Complex operator"" _r(long double r) {
    return Complex(static_cast<Real>(r), 0.0);
}

inline Complex operator"" _r(unsigned long long r) {
    return Complex(static_cast<Real>(r), 0.0);
}

void DemoComplex();

#endif // __COMPLEX_H__