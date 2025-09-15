// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <algorithm>

using namespace std;

template <typename TELEM> class TBitField;

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

template <typename TELEM> TBitField<TELEM>::TBitField(int len) {
  if (len < 1) {
    throw invalid_argument("Len must be >=1");
  }
  BitLen = len;
  MemLen = (len + (BITS_IN_ONE_MEM - 1)) / (BITS_IN_ONE_MEM);
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++) {
    pMem[i] = 0;
  }
}

template <typename TELEM>
TBitField<TELEM>::TBitField(const TBitField &bf) // конструктор копирования
{
  this->BitLen = bf.BitLen;
  this->MemLen = bf.MemLen;
  this->pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++) {
    this->pMem[i] = bf.pMem[i];
  }
}

template <typename TELEM> TBitField<TELEM>::~TBitField() {
  delete[] pMem;
  pMem = nullptr;
}

template <typename TELEM>
int TBitField<TELEM>::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if (n >= this->BitLen) {
    throw invalid_argument("Incorrect input");
  }
  int result = (n + (sizeof(n) * 8) - 1) / (BITS_IN_ONE_MEM);
  return result;
}
template <typename TELEM>
TELEM TBitField<TELEM>::GetMemMask(
    const int n) const // битовая маска для бита n
{
  TELEM res = (TELEM)1 << n % (BITS_IN_ONE_MEM);
  return res;
}

// доступ к битам битового поля
template <typename TELEM>
int TBitField<TELEM>::GetLength(void) const // получить длину (к-во битов)
{
  return MemLen;
}

template <typename TELEM>
void TBitField<TELEM>::SetBit(const int n) // установить бит
{
  if ((n < 0) || (n > BitLen))
    throw invalid_argument("Incorrect Input");
  pMem[GetMemIndex(n)] |= GetMemMask(n);
}

template <typename TELEM>
void TBitField<TELEM>::ClrBit(const int n) // очистить бит
{
  pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

template <typename TELEM>
int TBitField<TELEM>::GetBit(const int n) const // получить значение бита
{
  TELEM res1 = pMem[GetMemIndex(n)];
  TELEM res2 = 1 << GetMemMask(n);
  TELEM res3 = res1 & res2;
  res3 = res3 >> GetMemMask(n);
  if (res3 = 0) {
    return 0;
  } else {
    return 1;
  }

  return 0;
}

// битовые операции
template <typename TELEM>
TBitField<TELEM> &
TBitField<TELEM>::operator=(const TBitField &bf) // присваивание
{
  this->MemLen = bf.MemLen;
  this->BitLen = bf.BitLen;
  for (int i = 0; i < MemLen; i++) {
    this->pMem[i] = bf.pMem[i];
  }
  return *this;
}

template <typename TELEM>
int TBitField<TELEM>::operator==(const TBitField &bf) const // сравнение
{
  int flag = 1;
  if (this->BitLen != bf.BitLen) {
    flag = 0;
  }
  if (this->MemLen != bf.MemLen) {
    flag = 0;
  }
  if (flag == 1) {
    for (int i = 0; i < MemLen; i++) {
      if (this->pMem[i] != bf.pMem[i]) {
        flag = 0;
        break;
      }
    }
  }
  return flag;
}

template <typename TELEM>
int TBitField<TELEM>::operator!=(const TBitField &bf) const // сравнение
{
  int flag = 1;
  if (this->BitLen == bf.BitLen) {
    flag = 0;
  }
  if (this->MemLen == bf.MemLen) {
    flag = 0;
  }
  if (flag == 0) {
    for (int i = 0; i < MemLen; i++) {
      if (this->pMem[i] != bf.pMem[i]) {
        flag = 0;
        break;
      }
    }
  }
  return flag;
}

template <typename TELEM>
TBitField<TELEM>
TBitField<TELEM>::operator|(const TBitField &bf) // операция "или"
{
  return TBitField(0);
}

template <typename TELEM>
TBitField<TELEM>
TBitField<TELEM>::operator&(const TBitField &bf) // операция "и"
{
  return TBitField(0);
}

template <typename TELEM>
TBitField<TELEM> TBitField<TELEM>::operator~(void) // отрицание
{
  TBitField result(*this);
  for (int i = 0; i < MemLen - 1; i++) {
    pMem[i] = ~pMem[i];
  }
  int extraBits = BitLen % BITS_IN_ONE_MEM;
  if (extraBits != 0) {
    TELEM mask = (TELEM(1) << extraBits) - 1;
    result.pMem[MemLen - 1] &= mask;
  }
  return result;
}

// ввод/вывод
template <typename TELEM>
istream& operator>>(istream& istr, TBitField<TELEM>& bf) {
    for (int i = 0; i < bf.BitLen; i++) {
        int bit;
        istr >> bit;
        if (bit == 1) bf.SetBit(i);
        else if (bit == 0) bf.ClrBit(i);
    }
    return istr;
}

template <typename TELEM>
ostream& operator<<(ostream& ostr, const TBitField<TELEM>& bf) {
    for (int i = 0; i < bf.BitLen; i++) {
        ostr << (bf.GetBit(i) ? '1' : '0');
        if ((i + 1) % 8 == 0) ostr << " ";
    }
    return ostr;
}

template class TBitField<unsigned int>;
template class TBitField<unsigned long>;

template istream& operator>> <unsigned int>(istream& istr, TBitField<unsigned int>& bf);
template ostream& operator<< <unsigned int>(ostream& ostr, const TBitField<unsigned int>& bf);
template istream& operator>> <unsigned long>(istream& istr, TBitField<unsigned long>& bf);
template ostream& operator<< <unsigned long>(ostream& ostr, const TBitField<unsigned long>& bf);