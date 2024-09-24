// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len) : BitLen(len)
{
	if (len < 0)
		throw len;
	else
	{
		MemLen = (len + 15) >> 4;
		pMem = new TELEM[MemLen];
		if (pMem != NULL)
			for (int i = 0; i < MemLen; i++) pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{// преобразовать к int и разделить на 16
	if ((n < 0) || (n > BitLen))
		throw n;
	else
	return n >> 4; 

}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n > BitLen))
		throw n;
	else
	{
		return 1 << (n & 15);
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
		throw n;
	else
		pMem[GetMemIndex(n)] |= GetMemMask(n);
}
void TBitField::ClrBit(const int n) // очистить бит
{

	if ((n < 0) || (n > BitLen))
		throw n;
	else
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen))
		throw n;
	else
	{
		int result = (GetMemMask(n) & pMem[GetMemIndex(n)]);
		if (result == 0)
			return(0);
		else
			return(1);
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField & bf) // присваивание
{
	if (this != &bf)
	{
		delete []pMem;
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
  else
  {
	  for (int i = 0; i < BitLen; i++)
		  if (GetBit(i) != bf.GetBit(i))
			  return 0;
	  return 1;
  }
}

int TBitField::operator!=(const TBitField & bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 1;
	else
	{
		for (int i = 0; i < BitLen; i++)
			if (GetBit(i) != bf.GetBit(i))
				return 1;
		return 0;
	}
}

TBitField TBitField::operator|(const TBitField & bf) // операция "или"
{
	int i;
	if (bf.BitLen > BitLen) BitLen = bf.BitLen;
	TBitField tmp(BitLen);
	for (i = 0; i < MemLen; i++) tmp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++) tmp.pMem[i] |= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	if (BitLen == bf.BitLen)
	{
		int i;

		TBitField tmp(BitLen);

		for (i = 0; i < MemLen; i++) tmp.pMem[i] = pMem[i];

		for (i = 0; i < bf.MemLen; i++) tmp.pMem[i] &= bf.pMem[i];

		return tmp;
	}
	else
	{
		if (BitLen < bf.BitLen) BitLen = bf.BitLen;
		TBitField tmp(BitLen);
		for (int i = 0; i < bf.BitLen; i++)
		{
			int tmpval = (GetBit(i) && bf.GetBit(i));
			if (tmpval == 0)
				tmp.ClrBit(i);
			else
				tmp.SetBit(i);
		}
		for (int i = bf.BitLen; i < BitLen; i++)
			tmp.ClrBit(i);
		return tmp;
	}

}

TBitField TBitField::operator~(void) { // отрицание
	TBitField tmp = (*this);
	for (size_t i = 0; i < BitLen; i++) {
		if (tmp.GetBit(i))
			tmp.ClrBit(i);
		else
			tmp.SetBit(i);
	}
	return tmp;
}

// ввод/вывод

istream& operator>>(istream & istr, TBitField & bf) // ввод
{
	int i = 0;
	while ((i >= 0) && (i < bf.BitLen))
	{
		bf.SetBit(i);
		istr >> i;
	}
	return istr;
}

ostream& operator<<(ostream & ostr, const TBitField & bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	return ostr;
}
