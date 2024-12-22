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
	{
		throw std::runtime_error ("Error len");
	}
	else
	{
		int size = (len + 31)/32;
		pMem = new TELEM[size];
		memset(pMem, 0, sizeof(TELEM) * size);
	}
}

TBitField::TBitField(const TBitField& bf) 
{
	BitLen = bf.BitLen;
	MemLen = (bf.BitLen + BITS_IN_ONE_MEM - 1) / BITS_IN_ONE_MEM;
	pMem = new TELEM[MemLen];
	if (!pMem)
	{
		throw std::bad_alloc();
	}
	memcpy(pMem, bf.pMem, sizeof(TELEM) * MemLen);
}

TBitField::~TBitField() // деструктор
{
	delete[] pMem; 
	pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n >= BitLen)
	{
		throw std::out_of_range("Индекс вне диапозона");
	}
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % BITS_IN_ONE_MEM);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	int memIndex = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[memIndex] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	int memIndex = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[memIndex] &= ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int memIndex = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	return (pMem[memIndex] & mask) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField & bf) // присваивание
{
	if (this == &bf) return *this;  
	BitLen = bf.BitLen;
	MemLen = (BitLen + BITS_IN_ONE_MEM - 1) / BITS_IN_ONE_MEM;
	TELEM* newMem = new TELEM[MemLen];
	if (!newMem) 
	{
		throw std::bad_alloc();
	}
	memcpy(newMem, bf.pMem, sizeof(TELEM) * MemLen);
	delete[] pMem;
	pMem = newMem;
	return *this;
}

int TBitField::operator==(const TBitField & bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return false;
	for (int i = 0; i < MemLen; ++i)
	{
		if (pMem[i] != bf.pMem[i])
			return false;
	}
	return true;
}

int TBitField::operator!=(const TBitField & bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 1;  
	return memcmp(pMem, bf.pMem, sizeof(TELEM) * MemLen) != 0;
}

TBitField TBitField::operator|(const TBitField& bf)
{
	int maxLen = std::max(BitLen, bf.BitLen);  
	TBitField result(maxLen);
	for (int i = 0; i < MemLen; ++i) {
		if (i < bf.MemLen) {
			result.pMem[i] = pMem[i] | bf.pMem[i];  
		}
		else {
			result.pMem[i] = pMem[i];  
		}
	}
	if (bf.MemLen > MemLen) {
		for (int i = MemLen; i < bf.MemLen; ++i) {
			result.pMem[i] = bf.pMem[i];
		}
	}
	return result;
}

TBitField TBitField::operator&(const TBitField& bf)
{
	int maxLen = std::max(BitLen, bf.BitLen);  
	TBitField result(maxLen);

	for (int i = 0; i < MemLen; ++i) {
		if (i < bf.MemLen) {
			result.pMem[i] = pMem[i] & bf.pMem[i]; 
		}
	}

	return result;
}


TBitField TBitField::operator~(void) // отрицание
{
	TBitField result(BitLen);
	for (int i = 0; i < MemLen; ++i)
	{
		result.pMem[i] = ~pMem[i];
	}
	return result;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf)
{
	for (int i = 0; i < bf.BitLen; ++i)
	{
		char bit;
		istr >> bit;
		if (bit == '1')
			bf.SetBit(i);
		else if (bit == '0')
			bf.ClrBit(i);
		else
			throw std::invalid_argument("Invalid bit input");
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf)
{
	for (int i = 0; i < bf.BitLen; ++i)
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}

