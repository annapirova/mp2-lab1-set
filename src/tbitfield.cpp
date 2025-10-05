// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8) //перевод в биты

TBitField::TBitField(int len)
{
    if (len < 0) throw std::invalid_argument("Bit length must be >= 0");
    BitLen = len;
    if (BitLen == 0) {
        MemLen = 0;
        pMem = nullptr;
    }
    else {
        MemLen = (BitLen + BITS_IN_ONE_MEM - 1) / BITS_IN_ONE_MEM;
        pMem = new TELEM[MemLen];
        std::fill(pMem, pMem + MemLen, 0);
        /*for (int i = 0; i < MemLen; i++) {
          pMem[i] = 0;
          }
        */
    }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    if (&bf == this) return; //самокопирование 
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    if (MemLen > 0) {
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
    }
    else pMem = nullptr;
}

TBitField::~TBitField()
{
    BitLen = 0;
    MemLen = 0;
    delete[] pMem;
    pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return (n / BITS_IN_ONE_MEM);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{

    return (1 << (n % BITS_IN_ONE_MEM));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n >= BitLen))
        throw 2;
    int i = GetMemIndex(n);
    TELEM Mask = GetMemMask(n);
    pMem[i] |= Mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n >= BitLen)) throw 2;
    int i = GetMemIndex(n);
    TELEM Mask = GetMemMask(n);
    pMem[i] &= ~Mask; //~Mask - инверсия маски 
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n >= BitLen)) throw 2;
    int i = GetMemIndex(n);
    TELEM Mask = GetMemMask(n);
    return (pMem[i] & Mask) ? 1 : 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (&bf == this) return *this;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    if (pMem != nullptr) {
        delete[] pMem;
        pMem = nullptr;
    }
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField& bf) const
{
    // 1. Проверка длины
    if (BitLen != bf.BitLen)
        return 0; // false

    // 2. Сравнение всех полных элементов массива
    for (int i = 0; i < MemLen - 1; i++)
    {
        if (pMem[i] != bf.pMem[i])
            return 0; // false
    }

    // 3. Сравнение последнего элемента
    if (MemLen > 0)
    {
        int k = BitLen % BITS_IN_ONE_MEM; // количество значимых битов в последнем элементе
        if (k == 0) // элемент полностью заполнен
        {
            if (pMem[MemLen - 1] != bf.pMem[MemLen - 1])
                return 0; // false
        }
        else // частично заполненный элемент
        {
            TELEM Mask = (1 << k) - 1; // маска значимых битов
            if ((pMem[MemLen - 1] & Mask) != (bf.pMem[MemLen - 1] & Mask))
                return 0; // false
        }
    }

    // 4. Все совпало
    return 1; // true
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return (int)(!(*this == bf));
}

TBitField TBitField::operator|(const TBitField& bf)
{
    int newLen = std::max(this->BitLen, bf.BitLen);
    TBitField result(newLen);

    // побитовое ИЛИ всех элементов
    for (int i = 0; i < result.MemLen; i++)
    {
        TELEM a = (i < this->MemLen) ? this->pMem[i] : 0;
        TELEM b = (i < bf.MemLen) ? bf.pMem[i] : 0;
        result.pMem[i] = a | b;
    }

    // обнуляем лишние биты в последнем элементе
    int k = newLen % BITS_IN_ONE_MEM;
    if (k != 0)
    {
        TELEM Mask = (1 << k) - 1;
        result.pMem[result.MemLen - 1] &= Mask;
    }

    return result;
}


TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    int newLen = std::max(this->BitLen, bf.BitLen);
    TBitField result(newLen);

    // побитовое И всех элементов
    for (int i = 0; i < result.MemLen; i++)
    {
        TELEM a = (i < this->MemLen) ? this->pMem[i] : 0;
        TELEM b = (i < bf.MemLen) ? bf.pMem[i] : 0;
        result.pMem[i] = a & b;
    }

    // обнуляем лишние биты в последнем элементе, если длина не кратна TELEM
    int k = newLen % BITS_IN_ONE_MEM;
    if (k != 0)
    {
        TELEM Mask = (1 << k) - 1;
        result.pMem[result.MemLen - 1] &= Mask;
    }

    return result;
}

TBitField TBitField::operator~(void) // отрицание
{

    TBitField result(BitLen);
    for (int i = 0; i < MemLen; i++) {
        result.pMem[i] = ~(this->pMem[i]);
    }
    if (BitLen % BITS_IN_ONE_MEM != 0) {
        TELEM Mask = (1 << (BitLen % BITS_IN_ONE_MEM)) - 1;
        result.pMem[MemLen - 1] &= Mask;
    }
    return result;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf)
{
    char c;
    for (int i = 0; i < bf.GetLength(); i++)
    {
        istr >> c;                     // читаем один символ
        if (c == '1')
            bf.SetBit(i);              // ставим бит
        else if (c == '0')
            bf.ClrBit(i);              // очищаем бит
        else
            throw std::invalid_argument("Invalid character in bitfield input");
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.GetLength(); i++) {
        ostr << bf.GetBit(i);
    }
    return ostr;
}