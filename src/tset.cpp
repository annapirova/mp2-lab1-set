// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp) {
    MaxPower = mp;
    BitField = TBitField(mp);
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField) {
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf) {
    MaxPower = bf.GetLength();
};

TSet::operator TBitField() {
	return BitField;
}

int TSet::GetMaxPower(void) const {
    return MaxPower;
}

int TSet::IsMember(const int Elem) const {  // элемент множества?
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) {  // включение элемента множества
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) {  // исключение элемента множества
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) {  // присваивание
    if (this != &s) {
		MaxPower = s.MaxPower;
		BitField = s.BitField;
    }

	return *this;
}

int TSet::operator==(const TSet& s) const {  // сравнение
    if (this != &s) {
        if (MaxPower == s.MaxPower && BitField == s.BitField) {
            return 1;
        }
        else {
            return 0;
        }
    }
	return 1;
}

int TSet::operator!=(const TSet& s) const {  // сравнение
    if (this != &s){
        if (MaxPower != s.MaxPower || BitField != s.BitField) {
            return 1;
        }
        else {
            return 0;
        }
    }
    return 0;
}

TSet TSet::operator+(const TSet& s) {  // объединение
    TBitField res(MaxPower);
    res = BitField | s.BitField;

    return res;
}

TSet TSet::operator+(const int Elem) {  // объединение с элементом
    TSet res(*this);
	res.InsElem(Elem);
	return res;
}

TSet TSet::operator-(const int Elem) {  // разность с элементом
    TSet res(*this);
	res.DelElem(Elem);
	return res;
}

TSet TSet::operator*(const TSet& s) {  // пересечение
    int mp = s.GetMaxPower();

    if (MaxPower > mp) {
        mp = MaxPower;
    }

    TSet res(mp);

    res.BitField = BitField & s.BitField;
    return res;
}

TSet TSet::operator~(void) {  // дополнение
    TSet res(MaxPower);
    res.BitField = ~BitField;
    return res;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) {  // ввод
    for(int i = 0; i < s.MaxPower; i++) {
		istr >> s.BitField;
	}

	return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) {  // вывод
    for(int i = 0; i < s.MaxPower; i++) {
		ostr << s.BitField << " ";
	}

	return ostr;
}