// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)


TBitField::TBitField(int len) : BitLen(len) {
	if (len <= 0)
		throw "Error";

	if (BitLen % BITS_IN_ONE_MEM)
		MemLen = BitLen / BITS_IN_ONE_MEM + 1;

	else
		MemLen = BitLen / BITS_IN_ONE_MEM;

	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++)
		pMem[i] = (TELEM) 0;
};


TBitField::TBitField(const TBitField& bf) {  // конструктор копирования
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}


TBitField::~TBitField() {
	delete[] pMem;
	pMem = nullptr;
}


int TBitField::GetMemIndex(const int n) const {  // индекс Мем для бита n
	if ((n < 0) || (n >= BitLen)) {
		throw "Error";
	}

 	return n / (BITS_IN_ONE_MEM);
}


TELEM TBitField::GetMemMask(const int n) const {  // битовая маска для бита n
	if ((n < 0) || (n >= BitLen)) {
		throw "Error";
	}

	return ((TELEM)1 << (n % BITS_IN_ONE_MEM));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const {  // получить длину (к-во битов)
	return BitLen;
}


void TBitField::SetBit(const int n) {  // установить бит
	if ((n < 0) || (n >= BitLen)) {
		throw "Error";
	}
	pMem[GetMemIndex(n)] |= GetMemMask(n);
} 


void TBitField::ClrBit(const int n) {  // очистить бит
	if ((n < 0) || (n >= BitLen)) {
		throw "Error";
	}
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}


int TBitField::GetBit(const int n) const {  // получить значение бита
	if ((n < 0) || (n >= BitLen)) {
		throw "Error";
	}

	return ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0);
}


// битовые операции

TBitField& TBitField::operator=(const TBitField & bf) {  // присваивание
	if (this != &bf) {
		MemLen = bf.MemLen;
		BitLen = bf.BitLen;

		delete[] pMem;
		pMem = new TELEM[MemLen];

		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}


int TBitField::operator==(const TBitField & bf) const {  // сравнение
	if ((bf.BitLen == BitLen)) {
		for (int i = 0; i < bf.MemLen; i++) {
			if (pMem[i] != bf.pMem[i]) {
				return 0;
			}
		}
		return 1;
	}
	return 0;
}


int TBitField::operator!=(const TBitField & bf) const {  // сравнение
	if (bf.BitLen == BitLen) {
		for (int i = 0; i < bf.MemLen; i++) {
			if (pMem[i] != bf.pMem[i]) {
				return 1;
			}
		}
		return 0;
	}
	return 1;
}


TBitField TBitField::operator|(const TBitField & bf) {  // операция "или"
	const TBitField* bigger;
	const TBitField* smaller;

	if (BitLen >= bf.BitLen) {
		bigger = this;
		smaller = &bf;
	}

	else {
		bigger = &bf;
		smaller = this;
	}

	TBitField result(*bigger);

	for (int i = 0; i < smaller->MemLen; i++)
		result.pMem[i] = bigger->pMem[i] | smaller->pMem[i];

	return result;
}


TBitField TBitField::operator&(const TBitField & bf) {  // операция "и"
	const TBitField* bigger;
	const TBitField* smaller;

	if (BitLen >= bf.BitLen) {
		bigger = this;
		smaller = &bf;
	}

	else {
		bigger = &bf;
		smaller = this;
	}

	TBitField result(bigger->BitLen);

	for (int i = 0; i < smaller->MemLen - 1; i++)
		result.pMem[i] = bigger->pMem[i] & smaller->pMem[i];

	if (MemLen >= 1)
		for (int i = (smaller->MemLen - 1)*BITS_IN_ONE_MEM; i < smaller->BitLen; i++)
			if (bigger->GetBit(i)*smaller->GetBit(i))
				result.SetBit(i);

	return result;
}


TBitField TBitField::operator~(void) {  // отрицание
	TBitField result(*this);

	for (int i = 0; i < MemLen - 1; i++)
		result.pMem[i] = ~pMem[i];

	if (MemLen >= 1)
		for (int i = (MemLen - 1)*BITS_IN_ONE_MEM; i < result.BitLen; i++) {
			if (GetBit(i)) {
				result.ClrBit(i);
			}

			else {
				result.SetBit(i);
			}
		}

	return result;
}


// ввод/вывод

istream& operator>>(istream & istr, TBitField & bf) {  // ввод
	int k;
	istr >> k;
	bf = TBitField(k);

  	return istr;
}


ostream& operator<<(ostream & ostr, const TBitField & bf) {  // вывод
	for (int i = 0; i < bf.BitLen; i++) {
		ostr << bf.GetBit(i) << " ";
	}
	return ostr;
}
