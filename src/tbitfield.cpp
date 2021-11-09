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
	if (len > 0)
	{
		BitLen = len;
		MemLen = (len / BITS_IN_ONE_MEM);
		if ((MemLen * BITS_IN_ONE_MEM) < len)
			MemLen += 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else
	{
		throw std::invalid_argument("Error");
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int index = n / (BITS_IN_ONE_MEM);
	return index;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n<0 || n > BitLen)
		throw "error";
	else return ((TELEM)1) << (n) % (BITS_IN_ONE_MEM);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
		throw 2;
	else
	{
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen))
		throw 2;
	else
	{
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen))
		throw 2;
	else
	{
		return ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0);
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField & bf) // присваивание
{
	if (pMem != bf.pMem)
	{
		delete[]pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField & bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i])
			return 0;
	}
    return 1;
}

int TBitField::operator!=(const TBitField & bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 1;
	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i])
			return 1;
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField & bf) // операция "или"
{
	int len = BitLen;
	if (len < bf.BitLen)
		len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] |= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField & bf) // операция "и"
{
	int len = BitLen, i;
	if (len < bf.BitLen)
		len = bf.BitLen;
	TBitField temp(len);
	for (i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++)
		temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField otr(*this);
	for (int i = 0; i < MemLen - 1; i++)
		otr.pMem[i] = ~otr.pMem[i];
	if (MemLen > 0)
		for (int i = (MemLen - 1) * BITS_IN_ONE_MEM; i < otr.BitLen; i++)
			if (GetBit(i))
				otr.ClrBit(i);
			else
				otr.SetBit(i);
	return otr;
}

// ввод/вывод

istream& operator>>(istream & istr, TBitField & bf) // ввод
{
	int p;
	cin >> p;
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (p == 1)
			bf.SetBit(i);
		else if (p == 0)
			bf.ClrBit(i);
	}

	return istr;
}

ostream& operator<<(ostream & ostr, const TBitField & bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}
