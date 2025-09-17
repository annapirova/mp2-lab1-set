// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{
	if (len < 0) throw "negative length";
	BitLen = len;
	MemLen = len / BITS_IN_ONE_MEM + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < BitLen; ++i)
	{
		this->ClrBit(i);
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
}

TBitField::~TBitField()
{
	BitLen = 0;
	MemLen = 0;
	delete pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0) throw "negative index";
	if (n > BitLen) throw "index is out of range";
	return n / BITS_IN_ONE_MEM;
	
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0) throw "negative index";
	int n1 = n % BITS_IN_ONE_MEM;
	return 1 << n1;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0) throw "negative index";
	if (n > this->GetLength()) throw "index is out of range";
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0) throw "negative index";
	if (n > this->GetLength()) throw "index is out of range";
	TELEM zero = 0;
	zero = zero ^ zero;
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & zero;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0) throw "negative index";
	if (n > this->GetLength()) throw "index is out of range";
	return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField & bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	return TBitField(bf);
}

int TBitField::operator==(const TBitField & bf) const // сравнение
{
	if (BitLen == bf.GetLength())  return 1; 
	else return 0;
}

int TBitField::operator!=(const TBitField & bf) const // сравнение
{
	return 0;
}

TBitField TBitField::operator|(const TBitField & bf) // операция "или"
{
	return TBitField(0);
}

TBitField TBitField::operator&(const TBitField & bf) // операция "и"
{
	return TBitField(0);
}

TBitField TBitField::operator~(void) // отрицание
{
  return TBitField(0);
}

// ввод/вывод

istream& operator>>(istream & istr, TBitField & bf) // ввод
{
  return istr;
}

ostream& operator<<(ostream & ostr, const TBitField & bf) // вывод
{
	return ostr;
}
