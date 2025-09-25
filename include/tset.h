// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество

#ifndef __SET_H__
#define __SET_H__

using namespace std;
#include "tbitfield.h"


template <typename TELEM> class TSet;

template <typename TELEM>
istream& operator>>(istream& istr, TSet<TELEM>& s);

template <typename TELEM>
ostream& operator<<(ostream& ostr, const TSet<TELEM>& s);

template <typename TELEM>
class TSet
{
private:
    int MaxPower;       // максимальная мощность множества
    TBitField<TELEM> BitField; // битовое поле для хранения характеристического вектора
public:
    TSet(int mp);
    TSet(const TSet<TELEM> &s);       // конструктор копирования
    TSet(const TBitField<TELEM> &bf); // конструктор преобразования типа
    operator TBitField<TELEM>();      // преобразование типа к битовому полю
    // доступ к битам
    int GetMaxPower(void) const;     // максимальная мощность множества
    void InsElem(const int Elem);       // включить элемент в множество
    void DelElem(const int Elem);       // удалить элемент из множества
    int IsMember(const int Elem) const; // проверить наличие элемента в множестве
    // теоретико-множественные операции
    int operator== (const TSet &s) const; // сравнение
    int operator!= (const TSet &s) const; // сравнение
    TSet& operator=(const TSet &s);  // присваивание
    TSet operator+ (const int Elem); // объединение с элементом
    // элемент должен быть из того же универса
    TSet operator- (const int Elem); // разность с элементом
    // элемент должен быть из того же универса
    TSet operator+ (const TSet &s);  // объединение
    TSet operator* (const TSet &s);  // пересечение
    TSet operator~ (void);           // дополнение

    friend istream& operator>> <>(istream& istr, TSet<TELEM>& s);
    friend ostream& operator<< <>(ostream& ostr, const TSet<TELEM>& s);};
    #endif

    // ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля



template <typename TELEM>
TSet<TELEM>::TSet(int mp) : MaxPower(mp), BitField(mp) {}

// конструктор копирования
template <typename TELEM>
TSet<TELEM>::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

// конструктор преобразования типа
template <typename TELEM>
TSet<TELEM>::TSet(const TBitField<TELEM> &bf)
: MaxPower(bf.GetLength()), BitField(bf) {}

template <typename TELEM> TSet<TELEM>::operator TBitField<TELEM>() {
    return BitField;
}

template <typename TELEM>
int TSet<TELEM>::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

template <typename TELEM>
int TSet<TELEM>::IsMember(const int Elem) const // элемент множества?
{
    if (Elem < 0 || Elem >= MaxPower)
        throw out_of_range("Element out of range");
    return BitField.GetBit(Elem);
}

template <typename TELEM>
void TSet<TELEM>::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
        throw out_of_range("Element out of range");
    BitField.SetBit(Elem);
}

template <typename TELEM>
void TSet<TELEM>::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
        throw out_of_range("Element out of range");
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

template <typename TELEM>
TSet<TELEM> &TSet<TELEM>::operator=(const TSet &s) // присваивание
{
    if (this != &s) {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }
    return *this;
}

template <typename TELEM>
int TSet<TELEM>::operator==(const TSet &s) const // сравнение
{
    return (MaxPower == s.MaxPower) && (BitField == s.BitField);
}

template <typename TELEM>
int TSet<TELEM>::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

template <typename TELEM>
TSet<TELEM> TSet<TELEM>::operator+(const TSet &s) // объединение
{
    int newMaxPower = max(MaxPower, s.MaxPower);
    TSet result(newMaxPower);
    result.BitField = BitField | s.BitField;
    return result;
}

template <typename TELEM>
TSet<TELEM> TSet<TELEM>::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
        throw out_of_range("Element out of range");

    TSet result(*this);
    result.InsElem(Elem);
    return result;
}

template <typename TELEM>
TSet<TELEM> TSet<TELEM>::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
        throw out_of_range("Element out of range");

    TSet result(*this);
    result.DelElem(Elem);
    return result;
}

template <typename TELEM>
TSet<TELEM> TSet<TELEM>::operator*(const TSet& s) // пересечение
{
  int max_len = max(s.MaxPower, MaxPower);
  TSet tmp(max_len);
  int min_len = min(s.MaxPower, MaxPower);
  for (int i = 0; i < min_len; i++){
    if(BitField.GetBit(i) == 1 && s.BitField.GetBit(i) == 1){
        tmp.BitField.SetBit(i);
    }
    
  }

  return tmp;
}

template <typename TELEM>
TSet<TELEM> TSet<TELEM>::operator~(void) // дополнение
{
    TSet result(MaxPower);
    result.BitField = ~BitField;
    return result;
}

// перегрузка ввода/вывода

template <typename TELEM>
istream& operator>>(istream& istr, TSet<TELEM>& s) {
    int elem;
    while (istr >> elem) {
        if (elem >= 0 && elem < s.MaxPower) {
            s.InsElem(elem);
        }
    }
    return istr;
}

// Реализация оператора вывода
template <typename TELEM>
ostream& operator<<(ostream& ostr, const TSet<TELEM>& s) {
    ostr << "{ ";
    for (int i = 0; i < s.MaxPower; i++) {
        if (s.IsMember(i)) {
            ostr << i << " ";
        }
    }
    ostr << "}";
    return ostr;
}

// Явное инстанцирование для часто используемых типов
template class TSet<unsigned int>;
template class TSet<unsigned long>;

// Явное инстанцирование операторов
template istream& operator>> <unsigned int>(istream& istr, TSet<unsigned int>& s);
template ostream& operator<< <unsigned int>(ostream& ostr, const TSet<unsigned int>& s);
template istream& operator>> <unsigned long>(istream& istr, TSet<unsigned long>& s);
template ostream& operator<< <unsigned long>(ostream& ostr, const TSet<unsigned long>& s);


