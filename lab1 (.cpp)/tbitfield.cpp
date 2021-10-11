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
	if (len < 0)
		throw 1;
	throw "negative length";

	BitLen = len;
	MemLen = (BitLen +32 - 1) / 32;
	pMem = new TELEM[len];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
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
	return 0;
	return n / BITS_IN_ONE_MEM;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 0;
	return (1 << ((n % BITS_IN_ONE_MEM)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return 0;
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
		throw 2;
	if (n >= 0 && n < BitLen)
		pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen)
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= 0 && n < BitLen)
		return ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField & bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[] pMem;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];

	return *this;
}

int TBitField::operator==(const TBitField & bf) const // сравнение
{
	int res = 0;
	if (BitLen == bf.BitLen)
	{
		res = 1;
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				res = 0;
	}
	return res;
}

int TBitField::operator!=(const TBitField & bf) const // сравнение
{
	int res = 0;
	if (BitLen != bf.BitLen)
	{
		res = 1;
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				res = 0;
	}
	return res;
}

TBitField TBitField::operator|(const TBitField & bf) // операция "или"
{
	//return TBitField(0);
	if (BitLen >= bf.BitLen)
	{
		TBitField Temp(BitLen);
		for (int i = 0; i < MemLen; i++)
			Temp.pMem[i] = pMem[i] | bf.pMem[i];
		return Temp;
	}
	else
	{
		TBitField Temp(bf.BitLen);
		for (int i = 0; i < bf.MemLen; i++)
			Temp.pMem[i] = pMem[i] | bf.pMem[i];
		return Temp;
	}
}

TBitField TBitField::operator&(const TBitField & bf) // операция "и"
{
	//return TBitField(0);
	if (BitLen >= bf.BitLen)
	{
		TBitField Temp(bf.BitLen);
		for (int i = 0; i < bf.MemLen; i++)
			Temp.pMem[i] = pMem[i] & bf.pMem[i];
		return Temp;
	}
	else
	{
		TBitField Temp(BitLen);
		for (int i = 0; i < MemLen; i++)
			Temp.pMem[i] = pMem[i] & bf.pMem[i];
		return Temp;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	//return TBitField(0);
	TBitField Temp(*this);
	for (int i = 0; i < (MemLen - 1); i++)
		Temp.pMem[i] = ~Temp.pMem[i];
	for (int i = (MemLen - 1) * BITS_IN_ONE_MEM; i < BitLen; i++)
	{
		if (Temp.GetBit(i) == 0)
			Temp.ClrBit(i);
		else
			Temp.SetBit(i);
	}
	return Temp;
}

// ввод/вывод

istream& operator>>(istream & istr, TBitField & bf) // ввод
{
	//return istr;
	char c;
	int i = 0;
	istr >> c;
	while ((c == '1') || (c == '0'))
	{
		if (c == '1')
		{
			bf.SetBit(i);
		}
		if (c == '0')
		{
			bf.ClrBit(i);
		}
		i++;
		istr >> c;
	}
	return istr;
}

ostream& operator<<(ostream & ostr, const TBitField & bf) // вывод
{
	return ostr;
	cout << "{";
	for (int i = 0; i < bf.BitLen; i++)
		cout << bf.GetBit(i);
	cout << "}\n";
	return ostr;
}
