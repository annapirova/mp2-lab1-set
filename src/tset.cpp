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

bool TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}


// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
	if (this == &s)
		return *this;
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

bool TSet::operator==(const TSet& s) const // сравнение
{
	return BitField == s.BitField;
}

bool TSet::operator!=(const TSet& s) const // сравнение
{
	return !(*this == s);
}

TSet TSet::operator+(const TSet& s) // объединение
{
	TSet res(std::max(MaxPower, s.MaxPower));
	res.BitField = BitField | s.BitField;
	return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet res(*this);
	res.BitField.SetBit(Elem);
	return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet res(*this);
	res.BitField.ClrBit(Elem);
	return res;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
	TSet res(std::max(MaxPower, s.MaxPower));
	res.BitField = BitField & s.BitField;
	return res;
}

TSet TSet::operator~(void) // дополнение
{
	TSet res(MaxPower);
	res.BitField = ~BitField;
	return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &in, TSet &s) // ввод
{
	return in;
}

ostream& operator<<(ostream& out, const TSet& s) // вывод
{
	for (int i = 0; i < s.BitField.GetLength(); i++)
	{
		if (s.BitField.GetBit(i));
		{
			if (i == s.BitField.GetLength() - 1)
				out << i;
			else
				out << i << ", ";
		}
	}
	return out;
}
