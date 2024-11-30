#include "TSet.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}

TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {}

TSet::operator TBitField() {
    return BitField;
}

int TSet::GetMaxPower() const {
    return MaxPower;
}

void TSet::InsElem(const int Elem) {
    if (Elem < 0 || Elem >= MaxPower) throw 2;
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) {
    if (Elem < 0 || Elem >= MaxPower) throw 2;
    BitField.ClrBit(Elem);
}

int TSet::IsMember(const int Elem) const {
    if (Elem < 0 || Elem >= MaxPower) throw 2;
    return BitField.GetBit(Elem);
}

int TSet::operator==(const TSet& s) const {
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const {
    if (MaxPower != s.MaxPower) {
        return 1;  
    }
    return BitField != s.BitField;  
}

TSet& TSet::operator=(const TSet& s) {
    if (this != &s) {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }
    return *this;
}

TSet TSet::operator+(const int Elem) {
    TSet temp(*this);
    temp.InsElem(Elem);
    return temp;
}

TSet TSet::operator-(const int Elem) {
    TSet temp(*this);
    temp.DelElem(Elem);
    return temp;
}

TSet TSet::operator+(const TSet& s) {
    TSet temp(MaxPower > s.MaxPower ? MaxPower : s.MaxPower);
    temp.BitField = BitField | s.BitField;
    return temp;
}

TSet TSet::operator*(const TSet& s) {
    TSet temp(MaxPower > s.MaxPower ? MaxPower : s.MaxPower);
    temp.BitField = BitField & s.BitField;
    return temp;
}

TSet TSet::operator~() {
    TSet temp(MaxPower);
    temp.BitField = ~BitField;
    return temp;
}

istream& operator>>(istream& istr, TSet& s) {
    int temp;
    while (istr >> temp) {
        s.InsElem(temp);
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) {
    for (int i = 0; i < s.MaxPower; i++) {
        if (s.IsMember(i)) {
            ostr << i << " ";
        }
    }
    return ostr;
}
