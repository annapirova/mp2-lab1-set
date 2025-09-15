// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество

#ifndef __SET_H__
#define __SET_H__

using namespace std;
#include "tbitfield.h"


template <typename TELEM> class TSet;

template <typename TELEM>
istream& operator>>(istream& istr, TSet<TELEM>& s);

template <typename TELEM>
ostream& operator<<(ostream& ostr, const TSet<TELEM>& s);

template <typename TELEM>
class TSet
{
private:
  int MaxPower;       // максимальная мощность множества
  TBitField<TELEM> BitField; // битовое поле для хранения характеристического вектора
public:
  TSet(int mp);
  TSet(const TSet<TELEM> &s);       // конструктор копирования
  TSet(const TBitField<TELEM> &bf); // конструктор преобразования типа
  operator TBitField<TELEM>();      // преобразование типа к битовому полю
  // доступ к битам
  int GetMaxPower(void) const;     // максимальная мощность множества
  void InsElem(const int Elem);       // включить элемент в множество
  void DelElem(const int Elem);       // удалить элемент из множества
  int IsMember(const int Elem) const; // проверить наличие элемента в множестве
  // теоретико-множественные операции
  int operator== (const TSet &s) const; // сравнение
  int operator!= (const TSet &s) const; // сравнение
  TSet& operator=(const TSet &s);  // присваивание
  TSet operator+ (const int Elem); // объединение с элементом
                                   // элемент должен быть из того же универса
  TSet operator- (const int Elem); // разность с элементом
                                   // элемент должен быть из того же универса
  TSet operator+ (const TSet &s);  // объединение
  TSet operator* (const TSet &s);  // пересечение
  TSet operator~ (void);           // дополнение

 friend istream& operator>> <>(istream& istr, TSet<TELEM>& s);
friend ostream& operator<< <>(ostream& ostr, const TSet<TELEM>& s);};
#endif
