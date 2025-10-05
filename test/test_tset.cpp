// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
#include <stdexcept>

TSet::TSet(int mp) : BitField(mp)
{
    if (mp <= 0) throw std::invalid_argument("the power must be greater than 0");
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const
{
    if (Elem < 0 || Elem >= MaxPower)
        throw std::out_of_range("Element out of range");
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
        throw std::out_of_range("Element out of range");
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
        throw std::out_of_range("Element out of range");
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    if (&s == this) return;
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    if (MaxPower != s.MaxPower) return false;
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return !(*this == s) ? 1 : 0;
}

TSet TSet::operator+(const TSet& s) // объединение
{
    int Power = max(this->MaxPower, s.MaxPower);
    TSet Result(Power);
    Result.BitField = this->BitField;
    Result.BitField = Result.BitField | s.BitField;
    return Result;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
        throw std::out_of_range("Element out of range");
    TSet Result(MaxPower);
    Result.BitField = this->BitField;
    Result.BitField.SetBit(Elem);
    return Result;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
        throw std::out_of_range("Element out of range");
    TSet Result(*this);
    Result.BitField.ClrBit(Elem);
    return Result;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    int Power = min(this->MaxPower, s.MaxPower);
    TSet Result(Power);
    Result.BitField = this->BitField & s.BitField;
    return Result;
}

TSet TSet::operator~(void) // дополнение
{
    TSet Result(MaxPower);
    Result.BitField = ~this->BitField;
    return Result;
}

// перегрузка ввода/вывода

// Ввод множества
istream& operator>>(istream& istr, TSet& s)
{
    char c;
    for (int i = 0; i < s.GetMaxPower(); i++)
    {
        istr >> c;                       // читаем один символ
        if (c == '1') s.InsElem(i);      // ставим бит
        else if (c == '0') s.DelElem(i); // очищаем бит
        else throw std::invalid_argument("Invalid character in set input");
    }
    return istr;
}

// Вывод множества
ostream& operator<<(ostream& ostr, const TSet& s)
{
    for (int i = 0; i < s.GetMaxPower(); i++)
    {
        ostr << s.BitField.GetBit(i);   // выводим 0 или 1
    }
    return ostr;
}