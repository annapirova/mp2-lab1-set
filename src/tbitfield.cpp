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
	if (len >= 0)
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
		pMem[i] = bf.pMem[i]; ;
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
 //return 0;
 return (n / BITS_IN_ONE_MEM);
	
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n > BitLen) {
		throw "error ";
	}
	else
		return ((TELEM)1) << (n) % (BITS_IN_ONE_MEM);
	//return 0; 
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
//	return 0;
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
		throw 2;
	else
	{
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
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
	//return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField & bf) // присваивание
{
	if (pMem != bf.pMem)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete[] pMem;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField & bf) const // сравнение
{
	int res = 1;
	int i;
	if (BitLen != bf.BitLen)
		res = 0;
	else
		for (i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i]) {
				res = 0;
				break;
			}
		}
	return res;
	//return 0;
}

int TBitField::operator!=(const TBitField & bf) const // сравнение
{
	int res = 0;
	if (BitLen != bf.BitLen)
		res = 1;
	else
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i]) {
				res = 1;
				break;
			}
		}
	return res;
	//return 0;
}

TBitField TBitField::operator|(const TBitField & bf) // операция "или"
{
	int ln = 0;
	int i;
	ln = BitLen;
	if (ln < bf.BitLen)
		ln = bf.BitLen;
	TBitField tmp(ln);
	for (i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] |= bf.pMem[i];
	return tmp; 
	//return TBitField(0);
}

TBitField TBitField::operator&(const TBitField & bf) // операция "и"
{
	int i;
	int	ln = BitLen;
	if (bf.BitLen > ln)
		ln = bf.BitLen;
	TBitField tmp(ln);
	for (i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] &= bf.pMem[i];
	return tmp;
	//return TBitField(0);
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(*this);
	for (int i = 0; i < MemLen - 1; i++)
	{
		tmp.pMem[i] = ~tmp.pMem[i];
	}
	for (int i = BITS_IN_ONE_MEM * (MemLen - 1); i < BitLen; i++)
	{
		if ((tmp).GetBit(i) == 1)
			tmp.ClrBit(i);
		else
			tmp.SetBit(i);
	}
	return tmp;
  //return TBitField(0);
}

// ввод/вывод

istream& operator>>(istream & istr, TBitField & bf) // ввод
{
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
	ostr << " Length of BitField=" << bf.BitLen << endl; 
	for (int i = 0; i < bf.BitLen; i++)  
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}
