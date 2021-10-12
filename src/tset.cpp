// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Множество - реализация через битовые поля

#include <iostream>
#include "tbitfield.h"
#include "tset.h"

TSet::TSet(size_t mp) : bitField(mp)
{
    if (maxPower < 0)
    {
        throw maxPower;
    }
    maxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.bitField) 
{
    maxPower = s.maxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf)
{
    maxPower = bf.getLength();
}

TSet::operator TBitField()
{
    TBitField field(bitField);
    return field;
}

size_t TSet::getMaxPower() const // получить макс. к-во эл-тов
{
    return maxPower;
}

bool TSet::isMember(const elType elem) const // элемент множества?
{
    if (bitField.getBit(elem))
        return true;
    else
        return false;
}

void TSet::insElem(const elType elem) // включение элемента множества
{
    bitField.setBit(elem);
}

void TSet::delElem(const elType elem) // исключение элемента множества
{
    bitField.clrBit(elem);
}

// теоретико-множественные операции
TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this != &s)
    {
        maxPower = s.maxPower;
        bitField = s.bitField;
    }
    return *this;
}

bool TSet::operator==(const TSet &s) const // сравнение
{
    if (maxPower !=s.maxPower || bitField!= s.bitField)
        return false;
    else
        return true;
}

bool TSet::operator!=(const TSet &s) const // сравнение
{
    if (maxPower == s.maxPower && bitField == s.bitField)
        return false;
    else
        return true;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet Set(bitField | s.bitField);
    return Set;
}

TSet TSet::operator+(const elType elem) // объединение с элементом
{
    TSet Set(*this);
    if (!isMember(elem))
    {
        Set.insElem(elem);
    }
    return Set;
}

TSet TSet::operator-(const elType elem) // разность с элементом
{
    TSet Set(*this);
    if (isMember(elem))
    {
        Set.delElem(elem);
    }
    return Set;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet Set(bitField & s.bitField);
    return Set;
}

TSet TSet::operator~() // дополнение
{
    TSet Set(~bitField);
    return Set;
}

// перегрузка ввода/вывода
std::istream &operator>>(std::istream &istr, TSet &s) // ввод
{
    istr >> s.bitField;
    s.maxPower = s.bitField.getLength();
    return istr;
}

std::ostream& operator<<(std::ostream &ostr, const TSet &s) // вывод
{
    for (int i = 0; i < s.maxPower; i++)
    {
        if (s.isMember(i))
        {
            ostr << i << ' ';
        }
    }
    return ostr;
}
