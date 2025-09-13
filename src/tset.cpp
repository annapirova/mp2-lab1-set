// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "../include/tset.h"

template <typename TELEM>
TSet<TELEM>::TSet(int mp) : MaxPower(mp), BitField(mp) {}

// конструктор копирования
template <typename TELEM>
TSet<TELEM>::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

// конструктор преобразования типа
template <typename TELEM>
TSet<TELEM>::TSet(const TBitField<TELEM> &bf) : MaxPower(bf.GetLength()), BitField(bf) {}

template <typename TELEM>
TSet<TELEM>::operator TBitField<TELEM>() { 
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
TSet<TELEM> TSet<TELEM>::operator*(const TSet &s) // пересечение
{
    int newMaxPower = max(MaxPower, s.MaxPower);
    TSet result(newMaxPower);
    result.BitField = BitField & s.BitField;
    return result;
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
istream &operator>>(istream &istr, TSet<TELEM> &s) // ввод
{
    int elem;
    while (istr >> elem) {
        if (elem >= 0 && elem < s.MaxPower) {
            s.InsElem(elem);
        }
    }
    return istr;
}

template <typename TELEM>
ostream &operator<<(ostream &ostr, const TSet<TELEM> &s) // вывод
{
    ostr << "{ ";
    for (int i = 0; i < s.MaxPower; i++) {
        if (s.IsMember(i)) {
            ostr << i << " ";
        }
    }
    ostr << "}";
    return ostr;
}

// Явное инстанцирование шаблонов для часто используемых типов
template class TSet<uint>;
template class TSet<ulong>;