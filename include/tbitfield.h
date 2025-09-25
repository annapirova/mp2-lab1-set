// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#ifndef __BITFIELD_H__
#define __BITFIELD_H__

#include <iostream>

using namespace std;



template <typename TELEM> class TBitField;

template <typename TELEM>
istream& operator>>(istream& istr, TBitField<TELEM>& bf);

template <typename TELEM>
ostream& operator<<(ostream& ostr, const TBitField<TELEM>& bf);

template <typename TELEM>
class TBitField
{
private:
  int  BitLen; // длина битового поля - макс. к-во битов
  TELEM *pMem; // память для представления битового поля
  int  MemLen; // к-во эл-тов Мем для представления бит.поля

  // методы реализации
  int   GetMemIndex(const int n) const; // индекс в pМем для бита n       (#О2)
  TELEM GetMemMask (const int n) const; // битовая маска для бита n       (#О3)
public:
  TBitField(int len);                //                                   (#О1)
  TBitField(const TBitField &bf);    //                                   (#П1)
  ~TBitField();                      //                                    (#С)

  // доступ к битам
  int GetLength(void) const;      // получить длину (к-во битов)           (#О)
  void SetBit(const int n);       // установить бит                       (#О4)
  void ClrBit(const int n);       // очистить бит                         (#П2)
  int  GetBit(const int n) const; // получить значение бита               (#Л1)

  // надо учитывать, что TBitField может быть разной длины в int-ах
  // TBitField bf1(100) - 4 int, bf2(15) - 1 int
  TBitField& operator=(const TBitField &bf); // присваивание              (#П3)
  TBitField  operator|(const TBitField &bf); // операция "или"            (#О6)
  TBitField  operator&(const TBitField &bf); // операция "и"              (#Л2)
  int operator==(const TBitField& bf) const; // сравнение                 (#О5)
  int operator!=(const TBitField& bf) const; // сравнение
    
  TBitField  operator~(void);                // отрицание                  (#С)

   friend istream& operator>> <TELEM>(istream& istr, TBitField<TELEM>& bf);
  friend ostream& operator<< <TELEM>(ostream& ostr, const TBitField<TELEM>& bf);};


#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

template <typename TELEM> 
TBitField<TELEM>::TBitField(int len) {
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
  int result = (n / BITS_IN_ONE_MEM);
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
  return BitLen;
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
  if (n<0){
    throw invalid_argument("Incorrect position");
  }
  pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

template <typename TELEM>
int TBitField<TELEM>::GetBit(const int n) const // получить значение бита
{
  if (n < 0 || n >= BitLen)
    throw invalid_argument("Incorrect input");

  int memIndex = n / BITS_IN_ONE_MEM;
  int bitPos = n % BITS_IN_ONE_MEM;

  return ((pMem[memIndex] & GetMemMask(n)) >> bitPos);
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
  return !(*this == bf);
}

template <typename TELEM>
TBitField<TELEM>
TBitField<TELEM>::operator|(const TBitField &bf) // операция "или"
{
  int maxLen = max(BitLen, bf.BitLen);
  TBitField result(maxLen);

  for (int i = 0; i < MemLen; i++) {
    result.pMem[i] = pMem[i];
  }

  for (int i = 0; i < bf.MemLen; i++) {
    result.pMem[i] |= bf.pMem[i];
  }

  return result;
}

template <typename TELEM>
TBitField<TELEM>
TBitField<TELEM>::operator&(const TBitField &bf) // операция "и"
{
  int minLen = min(BitLen, bf.BitLen);
  TBitField result(minLen);

  for (int i = 0; i < result.MemLen; i++) {
    result.pMem[i] = pMem[i] & bf.pMem[i];
  }

  return result;
}

template <typename TELEM>
TBitField<TELEM> TBitField<TELEM>::operator~(void) // отрицание
{
  TBitField result(*this);
  for (int i = 0; i < MemLen - 1; i++) {
    result.pMem[i] = ~pMem[i];
  }
  int extraBits = BitLen % BITS_IN_ONE_MEM;
  if (extraBits != 0) {
    for(int i=BITS_IN_ONE_MEM*(MemLen-1);i<BitLen;i++){
      if(!GetBit(i)){
        result.SetBit(i);
      }
      if(GetBit(i)){
        result.ClrBit(i);
      }
    }
    
  }
  else{
      result.pMem[MemLen-1]=~pMem[MemLen-1];
  }
  return result;
}

// ввод/вывод
template <typename TELEM>
istream &operator>>(istream &istr, TBitField<TELEM> &bf) {
  for (int i = 0; i < bf.BitLen; i++) {
    int bit;
    istr >> bit;
    if (bit == 1)
      bf.SetBit(i);
    else if (bit == 0)
      bf.ClrBit(i);
  }
  return istr;
}

template <typename TELEM>
ostream &operator<<(ostream &ostr, const TBitField<TELEM> &bf) {
  for (int i = 0; i < bf.BitLen; i++) {
    ostr << (bf.GetBit(i) ? '1' : '0');
    if ((i + 1) % 8 == 0)
      ostr << " ";
  }
  return ostr;
}

template class TBitField<unsigned int>;
template class TBitField<unsigned long>;

template istream &operator>>
    <unsigned int>(istream &istr, TBitField<unsigned int> &bf);
template ostream &operator<< <unsigned int>(ostream &ostr,
                                            const TBitField<unsigned int> &bf);
template istream &operator>>
    <unsigned long>(istream &istr, TBitField<unsigned long> &bf);
template ostream &
operator<< <unsigned long>(ostream &ostr, const TBitField<unsigned long> &bf);




#endif
