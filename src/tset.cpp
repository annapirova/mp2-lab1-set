// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf)
{
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem >= 0 && Elem < MaxPower)
    {
        return BitField.GetBit(Elem); // Возвращаем значение бита
    }
    else
    {
        throw std::out_of_range("Element out of range");
    }
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem >= 0 && Elem < MaxPower)
    {
        BitField.SetBit(Elem); // Устанавливаем бит для данного элемента
    }
    else
    {
        throw std::out_of_range("Element out of range");
    }
}

void TSet::DelElem(const int Elem)
{
    if (Elem >= 0 && Elem < MaxPower)
    {
        BitField.ClrBit(Elem); // Очищаем бит для данного элемента
    }
    else
    {
        throw std::out_of_range("Element out of range");
    }
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    if (this == &s) return *this; // Защита от самоприсваивания
    MaxPower = s.MaxPower;
    BitField = s.BitField; // Копируем битовое поле
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return BitField != s.BitField;
}

TSet TSet::operator+(const TSet& s)
{
    int newSize = std::max(MaxPower, s.MaxPower);  // Вычисляем максимальный размер
    TSet result(newSize); // Создаем множество с этим размером
    result.BitField = BitField | s.BitField; // Выполняем объединение
    return result;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw std::out_of_range("Element out of range");
    }
    TSet result(*this);  // Создаем копию множества
    result.InsElem(Elem);  // Включаем элемент
    return result;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw std::out_of_range("Element out of range");
    }
    TSet result(*this);  // Создаем копию множества
    result.DelElem(Elem);  // Удаляем элемент
    return result;
}

TSet TSet::operator*(const TSet& s)
{
    int newSize = std::max(MaxPower, s.MaxPower); // Вычисляем максимальный размер
    TSet result(newSize); // Создаем множество с этим размером
    result.BitField = BitField & s.BitField; // Выполняем пересечение
    return result;
}


TSet TSet::operator~(void) // дополнение
{
    TSet result(MaxPower);
    result.BitField = ~BitField;  // Инвертируем битовое поле
    return result;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    for (int i = 0; i < s.MaxPower; ++i)
    {
        int bit;
        istr >> bit;
        if (bit == 1)
        {
            s.InsElem(i); // Включаем элемент
        }
        else if (bit == 0)
        {
            s.DelElem(i); // Удаляем элемент
        }
        else
        {
            throw std::invalid_argument("Invalid input");
        }
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
	for (int i = 0; i < s.MaxPower; ++i)
	{
		ostr << s.IsMember(i); // Печатаем элемент (1 или 0)
	}
	return ostr;
}
