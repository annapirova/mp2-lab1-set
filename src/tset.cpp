// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
		MaxPower = mp;
}

// конструктор копирования

TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа

TSet::TSet(const TBitField &bf) : BitField(bf)
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

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (BitField.GetBit(Elem) == 1)
		return 1;
	else
		return 0;
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

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	return (BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  return (BitField != s.BitField);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet temp(BitField | s.BitField);
	return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet temp(MaxPower);
	temp = *this;
	if (temp.BitField.GetBit(Elem) != 1)
		temp.BitField.SetBit(Elem);
	return temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet temp(MaxPower);
	temp = *this;
	if (temp.BitField.GetBit(Elem) == 1)
		temp.BitField.ClrBit(Elem);
	return temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet temp(BitField & s.BitField);
	return temp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet Temp(MaxPower);
	Temp.BitField = ~(*this).BitField;  
	return Temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int i;
	cin>> i;
	for (; i > -1; cin >> i)
		s.BitField.SetBit(i);
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0; i < s.BitField.GetLength(); i++)
		ostr << s << ' ';
	return ostr;
}
