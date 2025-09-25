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
	MemLen = (len + BITS_IN_ONE_MEM - 1) / BITS_IN_ONE_MEM;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i)
	{
		pMem[i] = bf.pMem[i];
	}
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
	TELEM amask = ~GetMemMask(n);
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & amask;
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
	delete[] pMem;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i)
	{
		pMem[i] = bf.pMem[i];
	}
	return TBitField(bf); // what to return?
}

int TBitField::operator==(const TBitField & bf) const // сравнение
{
	if (BitLen != bf.GetLength()) return 0;
	int flag = 1;
	for (int i = 0; i < BitLen; ++i)
	{
		if (this->GetBit(i) != bf.GetBit(i)) flag = 0;
	}
	return flag;
}

int TBitField::operator!=(const TBitField & bf) const // сравнение
{
	if (BitLen != bf.GetLength()) return 1;
	int flag = 0;
	for (int i = 0; i < BitLen; ++i)
	{
		if (this->GetBit(i) != bf.GetBit(i)) flag = 1;
	}
	return flag;
}

TBitField TBitField::operator|(const TBitField & bf) // операция "или"
{
	TBitField temp(0);
	int lesser = 0;
	if (BitLen > bf.BitLen) 
	{
		temp = *this;
		lesser = bf.BitLen;
	}
	else {
		
		temp = bf;
		lesser = BitLen;
	}
	for (int i = 0; i < lesser; ++i)
	{
		if (this->GetBit(i) + bf.GetBit(i))
		{
			temp.SetBit(i);
		}
	}
	return temp;
}

TBitField TBitField::operator&(const TBitField & bf) // операция "и"
{
	TBitField temp(max(BitLen, bf.BitLen));
	if (BitLen == bf.BitLen) {
		for (int i = 0; i < BitLen; ++i)
		{
			if (this->GetBit(i) * bf.GetBit(i)) temp.SetBit(i);
		}
	}
	int lesser = min(BitLen, bf.BitLen);
	for (int i = 0; i < lesser; ++i)
	{
		if (this->GetBit(i) * bf.GetBit(i)) temp.SetBit(i);
	}
	/*if (BitLen > bf.BitLen)
	{
		temp = TBitField(BitLen);
		lesser = bf.BitLen;
		for (int i = lesser; i < temp.BitLen; ++i)
		{
			if (this->GetBit(i)) {
				temp.SetBit(i);
			}
			else {
				temp.ClrBit(i);
			}
		}
	}
	else {

		temp = TBitField(bf.BitLen);
		lesser = BitLen;
		for (int i = lesser; i < temp.BitLen; ++i)
		{
			if (bf.GetBit(i)) {
				temp.SetBit(i);
			}
			else {
				temp.ClrBit(i);
			}
		}
	}
	for (int i = 0; i < lesser; ++i)
	{
		if (this->GetBit(i) * bf.GetBit(i)) temp.SetBit(i);
	}*/
	
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(BitLen);
	for (int i = 0; i < BitLen; ++i)
	{
		if (this->GetBit(i)) 
		{
			temp.ClrBit(i);
		}
		else 
		{
			temp.SetBit(i);
		}
	}
	return temp;
}

// ввод/вывод

istream& operator>>(istream & istr, TBitField & bf) // ввод
{
	string InputData;
	istr >> InputData;

	for (int i = 0; i < bf.MemLen; ++i) bf.pMem[i] = (TELEM)0;

	for (int i = 0; i < bf.GetLength(); ++i) {
		if (InputData[i] == '1') bf.SetBit(bf.GetLength() - i);
	}

	return istr;
}

ostream& operator<<(ostream & ostr, const TBitField & bf) // вывод
{
	for (int i = bf.BitLen - 1; i >= 0; i--) {
		ostr << bf.GetBit(i);
	}

	return ostr;
}
