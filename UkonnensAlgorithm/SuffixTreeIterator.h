//#pragma once
//class SuffixTreeIterator
//{
//	SuffixTreeIterator(pointer ptr) : m_ptr(ptr) {}
//
//    reference operator*() const { return *m_ptr; }
//    pointer operator->() { return m_ptr; }
//
//    // Prefix increment
//    Iterator& operator++() { m_ptr++; return *this; }
//
//    // Postfix increment
//    Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
//
//    friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
//    friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
//private:
//
//	pointer m_ptr;
//};
//
