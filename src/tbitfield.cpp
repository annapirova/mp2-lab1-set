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
			throw "negative lenght";
		else
		{
			BitLen = len;
			MemLen = BitLen / BITS_IN_ONE_MEM + 1;
			pMem = new TELEM[MemLen];
			for (int i = 0; i < MemLen; i++)
				pMem[i] = 0;
		}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete []pMem;

	BitLen = 0; 
	MemLen = 0; 
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / BITS_IN_ONE_MEM; 
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return ((TELEM)1 << (n % BITS_IN_ONE_MEM));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= 0 && n < BitLen)
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	else
		throw "error";
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen)
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	else
		throw "error";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
		if (n >= 0 && n < BitLen)
			return ((pMem[GetMemIndex(n)] >> (n % BITS_IN_ONE_MEM)) & 1);
		else
			throw "error";
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		delete[]pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen;i++)
		pMem[i] = bf.pMem[i];
	}
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 1;
	if (BitLen != bf.BitLen)
		res = 0;
	else
		for (int i = 0; i<MemLen; i++)
			if (pMem[i] != bf.pMem[i])
			{
				res = 0;
				break;
			}
	return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int res = 1;
	if (*this == bf)
		res = 0;
	return res;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
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

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
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
	TBitField temp(*this);
	for (int i = 0; i < MemLen - 1; i++)
		temp.pMem[i] = ~temp.pMem[i];
	for (int i = (MemLen - 1)*BITS_IN_ONE_MEM; i < BitLen; i++)
		if (temp.GetBit(i) == 0) temp.SetBit(i);
		 else
			temp.ClrBit(i);
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int k;
	cin >> k;
	while (k>-1)
	{
		bf.SetBit(k);
		cin >> k;
	}
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	cout << "{";
	for (int k = 0; k < bf.BitLen; k++)
		cout << bf.GetBit(k);
	cout << "}\n";
  return ostr;
}
