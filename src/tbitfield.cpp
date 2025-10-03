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
		if (len % (sizeof(TELEM) * 8) == 0)
		{
			MemLen = len / (8 * sizeof(TELEM));
		}
		else
		{
			MemLen = len / (8 * sizeof(TELEM)) + 1;
		}
		pMem = new TELEM[MemLen]{0};
	}
	else
	{
		throw"1";
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n >= BitLen))
	{
		throw "No";
	}
	return n/(sizeof(TELEM)*8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0)
		return 0;
	int k = n % (sizeof(TELEM) * 8);
	TELEM maska = (1 << k);
	return maska;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen))
	{
		throw "NO";
	}
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen))
	{
		throw "No";
	}
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen))
	{
		throw "No";
	}
	return GetMemMask(n)&pMem[GetMemIndex(n)];
}

// битовые операции

TBitField& TBitField::operator=(const TBitField & bf) // присваивание
{
	if (this == &bf)
	{
		return *this;
	}

	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[] pMem;

	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return 0;
	}
	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i])
		{
			return 0;
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField & bf) // операция "или"
{
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;

	TBitField tmp(len);
	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] |= bf.pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField & bf) // операция "и"
{
	int len = BitLen;
	if (bf.BitLen > len)
	{
		len = bf.BitLen;

		TBitField tmp(len);
		for (int i = 0; i < MemLen; i++)
		{
			tmp.pMem[i] = pMem[i];
		}
		for (int i = 0; i < MemLen; i++)
		{
			tmp.pMem[i] &= bf.pMem[i];
		}
		return tmp;
	}
	else
	{
		len = BitLen;

		TBitField tmp(len);
		for (int i = 0; i < bf.MemLen; i++)
		{
			tmp.pMem[i] = bf.pMem[i];
		}
		for (int i = 0; i < bf.MemLen; i++)
		{
			tmp.pMem[i] &= pMem[i];
		}
		return tmp;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(*this);
	for (int i = 0; i < MemLen - 1; i++)
		res.pMem[i] = ~res.pMem[i];
	if (MemLen > 0)
		for (int i = (MemLen - 1) * (sizeof(TELEM) * 8); i < res.BitLen; i++)
			if (GetBit(i))
				res.ClrBit(i);
			else
				res.SetBit(i);
	return res;
}

// ввод/вывод

istream& operator>>(istream & istr, TBitField & bf) // ввод
{
	TELEM bit;
	for (int i = 0; i < bf.BitLen; i++)
	{
		istr >> bit;
		if (i / 32 == 0) {
			bf.pMem[bf.GetMemIndex(i / 32)] |= bit;
		}
		else {
			bf.pMem[bf.GetMemIndex(i / 32)] <<= 1;
			bf.pMem[bf.GetMemIndex(i / 32)] |= bit;
		}
	}
	return istr;
}

ostream& operator<<(ostream & ostr, const TBitField & bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); ++i)
	{
		if (bf.GetBit(i))
		{
			ostr << '1';
		}
		else
		{
			ostr << '0';
		}
	}
	return ostr;
}
