// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) {
    if (len <= 0) {
        throw 2;
    }
    BitLen = len;
    MemLen = (len + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
    
}


TBitField::TBitField(const TBitField& bf) {
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


int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0 || n >= BitLen) { throw 2; }
    
    
    return n / (sizeof(TELEM) * 8);
}
TELEM TBitField::GetMemMask(const int n) const {
    if (n < 0 || n >= BitLen) {
        throw 2;
    }
    return  1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(int n) {
 
    if (n < 0 || n >= BitLen) {
        throw 2;
    }
    int index = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    pMem[index] |= mask;
}


void TBitField::ClrBit(int n) {
    if ((n < 0)|| (n >= BitLen)) {
        throw 2;
    }
    int index = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    pMem[index] &= ~mask;
}


int TBitField::GetBit(const int n) const {
    if (n < 0 || n >= BitLen) { throw 2; }
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0 ? 1 : 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) {
    if (this != &bf) {
        delete[] pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (MemLen != MemLen) {
        return 0;
    }
    for (int i = 0;i < MemLen;i++) {
        if (pMem[i] != bf.pMem[i]) {
            return 0;
        }
    }
    return 1;

}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (MemLen != MemLen) {
        return 1;
    }
    for (int i = 0;i < MemLen;i++) {
        if (pMem[i] != bf.pMem[i]) {
            return 1;
        }
    }
    return 0;

}
TBitField TBitField::operator|(const TBitField& bf) {
    int maxLen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField temp(maxLen);
    for (int i = 0; i < temp.MemLen; i++) {
        temp.pMem[i] = (i < MemLen ? pMem[i] : 0) | (i < bf.MemLen ? bf.pMem[i] : 0);
    }
    return temp;
}

TBitField TBitField::operator&(const TBitField& bf) {
    int maxLen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField temp(maxLen);
    for (int i = 0; i < temp.MemLen; i++) {
        temp.pMem[i] = (i < MemLen ? pMem[i] : 0) & (i < bf.MemLen ? bf.pMem[i] : 0);
    }
    return temp;
}

TBitField TBitField::operator~() {
    TBitField temp(BitLen);

    for (int i = 0; i < BitLen; i++) {
        if (GetBit(i) == 0) {
            temp.SetBit(i);
        }
        else {
            temp.ClrBit(i);
        }
    }

    return temp;
}


// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) {
    for (int i = 0; i < bf.BitLen; i++) {
        int bit;
        istr >> bit;
        if (bit) bf.SetBit(i);
        else bf.ClrBit(i);
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) {
    for (int i = 0; i < bf.BitLen; i++) {
        ostr << bf.GetBit(i);
    }
    return ostr;
}
