// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"


TBitField::TBitField(int len)
{
    if (len < 0) {
        throw "Negative lenght";
    }
    BitLen = len;

    const size_t bitsINElem = sizeof(TELEM) * 8;
    MemLen = (BitLen + bitsINElem - 1) / bitsINElem;

    if (MemLen > 0) {
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = 0;
        }
    }
    else {
        pMem = nullptr;
    }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    if (MemLen > 0) {
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
    }
    else {
        pMem = nullptr;
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
    pMem = nullptr;
    BitLen = 0;
    MemLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    const size_t bitsINElem = sizeof(TELEM) * 8;
    return n / bitsINElem;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    const size_t bitsINElem = sizeof(TELEM) * 8;
    int pos = n % bitsINElem;
    return (TELEM)1 << pos;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= BitLen) {
        throw "Index out of range";
    }
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen) {
        throw "Index out of range";
    }
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= BitLen) {
        throw "Index out of range";
    }
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (this == &bf) {
        return *this;
    }
    if (MemLen != bf.MemLen) {
        delete[] pMem;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
    }
    BitLen = bf.BitLen;
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.BitLen) {
        return 0;
    }
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) {
            return 0;
        }
    }
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    int max_len = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField res(max_len);

    for (int i = 0; i < res.MemLen; i++) {
        if (i < MemLen && i < bf.MemLen) {
            res.pMem[i] = pMem[i] | bf.pMem[i];
        }
        else if (i < MemLen) {
            res.pMem[i] = pMem[i];
        }
        else {
            res.pMem[i] = bf.pMem[i];
        }
    }
    return res;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    int maxLen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField res(maxLen);

    int minMemLen = (MemLen < bf.MemLen) ? MemLen : bf.MemLen;
    for (int i = 0; i < minMemLen; i++) {
        res.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(BitLen);
    for (int i = 0; i < MemLen; ++i) {
        res.pMem[i] = ~pMem[i];
    }
    const size_t bitsInElem = sizeof(TELEM) * 8;
    int extraBits = BitLen % bitsInElem;
    if (extraBits != 0) {
        TELEM mask = ((TELEM)1 << extraBits) - 1;
        res.pMem[MemLen - 1] &= mask;
    }

    return res;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    char ch;
    for (int i = 0; i < bf.BitLen; ++i) {
        istr >> ch;
        if (ch == '1') {
            bf.SetBit(i);
        }
        else if (ch == '0') {
            bf.ClrBit(i);
        }
        else {
            break;
        }
    }
    return istr;
}
ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.BitLen; ++i) {
        ostr << bf.GetBit(i);
    }
    return ostr;
}