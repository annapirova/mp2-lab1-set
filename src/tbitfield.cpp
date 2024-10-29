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
	BitLen = len;
	MemLen = BitLen;
	pMem = new TELEM[MemLen];
};

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
}

TBitField::~TBitField()
{
	delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
 	return n >> BITS_IN_ONE_MEM - 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % BITS_IN_ONE_MEM - 1);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return MemLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
		{throw 2;}
	pMem[GetMemIndex(MemLen - n)] |= GetMemMask(MemLen - n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen))
		{throw 2;}
	pMem[GetMemIndex(MemLen - n)] &= GetMemMask(MemLen - n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen))
		{throw 2;}
	return pMem[GetMemIndex(MemLen - n)] & 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField & bf) // присваивание
{
	if (this != &bf)
	{
		MemLen = bf.MemLen;
		BitLen = bf.BitLen;
		pMem = new TELEM[BitLen];
	}
	memcpy(pMem,bf.pMem,MemLen * BITS_IN_ONE_MEM);
	return *this;
}

int TBitField::operator==(const TBitField & bf) const // сравнение
{
	if ((bf.MemLen == MemLen) && (bf.BitLen == BitLen))
	{
		for (int i = 0;i < GetLength();i++)
		{
			if (GetBit(GetMemIndex(i)) != bf.GetBit(GetMemIndex(i)))
			{
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

int TBitField::operator!=(const TBitField & bf) const // сравнение
{
	if ((bf.MemLen == MemLen) && (bf.BitLen == BitLen))
	{
		for (int i = 0;i < GetLength();i++)
		{
			if (GetBit(GetMemIndex(i)) != bf.GetBit(GetMemIndex(i)))
			{
				return 1;
			}
		}
		return 0;
	}
	return 1;
}

TBitField TBitField::operator|(const TBitField & bf) // операция "или"
{
	if (bf.MemLen == MemLen && bf.BitLen == BitLen)
	{
		for (int i = 0;i < GetLength();i++)
		{
			if (GetBit(GetMemIndex(i)) != bf.GetBit(GetMemIndex(i)))
			{
				SetBit(GetMemIndex(i));
			}
		}
		return *this;
	}
	return TBitField(0);
}

TBitField TBitField::operator&(const TBitField & bf) // операция "и"
{
	if (bf.MemLen == MemLen && bf.BitLen == BitLen)
	{
		for (int i = 0;i < GetLength();i++)
		{
			if (GetBit(GetMemIndex(i)) != bf.GetBit(GetMemIndex(i)))
			{
				ClrBit(GetMemIndex(i));
			}
		}
		return *this;
	}
	return TBitField(0);
}

TBitField TBitField::operator~(void) // отрицание
{
	for (int i = 0;i < GetLength();i++)
	{
		if (GetBit(GetMemIndex(i)) == 1)
		{
			ClrBit(GetMemIndex(i));
		}
		else
		{
			SetBit((GetMemIndex(i)));
		}
	}
}

// ввод/вывод

istream& operator>>(istream & istr, TBitField & bf) // ввод
{
	for (int i = 0; i < bf.MemLen; i++)
		{
			istr >> bf.pMem[i];
		}
  	return istr;
}

ostream& operator<<(ostream & ostr, const TBitField & bf) // вывод
{
	for (int i = 0; i < bf.MemLen; i++)
		{
			ostr << bf.pMem[i] << "";
		}
	return ostr;
}
