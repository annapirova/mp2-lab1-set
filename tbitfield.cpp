// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

//len = 5
//5+31=36
//36/32 = 1,....
//
//len = 32
//(32+31)/32= 1
//
//len = 64
//(64+31)/32 = 2

TBitField::TBitField(int len) :BitLen(len)
{
	if (len <= 0)
		throw "Invalid value entered";
	int size = (len + BITS_IN_ONE_MEM - 1) / (BITS_IN_ONE_MEM); // количество бит в поле
	MemLen = size; // количество блоков
	pMem = new TELEM[MemLen]; // массив с полем
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
	delete pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	//int Nfield = n / 32; // в каком из полей (блоков поля) находится элемент
	if ((n < 0)||(n>=BitLen))
		throw "Invalid index for bit index";
	return n / (BITS_IN_ONE_MEM); // какой блок
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n >= BitLen))
		throw "Invalid index for mask";
	return (TELEM)1 << (n % (BITS_IN_ONE_MEM));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen))
		throw "Invalid index was entered";
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen))
		throw "Invalid index was entered";
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~(GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen))
		throw "Invalid index was entered";
	return ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0);//(1 << (n % 32));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField & bf) // присваивание
{
	if (this == &bf) return *this;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete pMem;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField & bf) const // сравнение
{
	if (bf.BitLen != BitLen)
		return 0;
	for (int i = 0; i < bf.MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 0;
	return 1;
}

int TBitField::operator!=(const TBitField & bf) const // сравнение
{
	if (bf.BitLen != BitLen)
		return 1;
	for (int i = 0; i < bf.MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 1;
	return 0;
}

TBitField TBitField::operator|(const TBitField & bf) // операция "или"
{
	int maxSize = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
	TBitField NewF(maxSize);
	for (int i = 0; i < NewF.MemLen; i++)
	{
		TELEM a = (i < MemLen) ? pMem[i] : 0;
		TELEM b = (i < bf.MemLen) ? bf.pMem[i] : 0;
		NewF.pMem[i] = a | b;
	}
	return NewF;
}

TBitField TBitField::operator&(const TBitField & bf) // операция "и"
{
	int len = BitLen;
	if (bf.BitLen > len) len = bf.BitLen;
	TBitField res(len);
	for (int i = 0; i < MemLen; i++)
		res.pMem[i] = pMem[i];
	for (int j = 0; j < MemLen; j++)
		res.pMem[j] &= bf.pMem[j];
	/*int maxSize = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
	TBitField NewF(maxSize);
	for (int i = 0; i < NewF.MemLen; i++)
	{
		TELEM a = (i < MemLen) ? pMem[i] : (TELEM)0;
		TELEM b = (i < bf.MemLen) ? bf.pMem[i] : (TELEM)0;
		NewF.pMem[i] = a & b;
	}*/
	return res;
}


//32-bit
// len = 40
// c 40 to 63
TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for (int i = 1; i < BitLen+1; i++)
	{
		if (GetBit(BitLen - i))res.ClrBit(BitLen - i);
		else res.SetBit(BitLen - i);
	}		
	return res;
}

// ввод/вывод

istream& operator>>(istream & istr, TBitField & bf) // ввод
{
	for (int i = 0; i < bf.MemLen; i++) {
		istr >> bf.pMem[i];
	}
  return istr;
}

ostream& operator<<(ostream & ostr, const TBitField & bf) // вывод
{
	for (int i = 0; i < bf.MemLen; i++)
	{
		ostr << bf.pMem[i] << "\t";
	}
	return ostr;
}
