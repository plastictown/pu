#pragma once
#ifndef __CYCLED_QUEUE_H__
#define __CYCLED_QUEUE_H__

#include <string>
#include <exception>
#include <iostream>
#include <initializer_list>
#include <utility>
#include <iterator>

using namespace std;

#define log_me()  std::cout << __FUNCTION__ << std::endl

template <class val_type> class MyQueue {
public:
  // dtor
	~MyQueue() {
    log_me();
		clear();
	}

  // default ctor
	MyQueue():
		  m_data{ nullptr }
		, first{0u}
		, last {0u}
		, cap  {0u}
		, size {0u}
{
    log_me();
		//alloc(init_val_);
}// !ctor(default)

    //---IL ctor---//
    MyQueue (const std::initializer_list<val_type>& l) :
	MyQueue ()
    {
      log_me();
      this->reserve (l.size ());
      for (const auto& el : l)
	{
	  push (el);
	}
    }// !ctor(IL)

    MyQueue(MyQueue<val_type>&& rhs):
    MyQueue(){
      log_me();
	  this->cap = rhs.cap;
	  this->size = rhs.size;
	  this->first = rhs.first;
	  this->last = rhs.last;
	  this->m_data = rhs.m_data;

	  rhs.m_data = nullptr;
	  rhs.cap = 0u;
	  rhs.size = 0u;
	  rhs.first = 0u;
	  rhs.last = 0u;
    }// !ctor(&&)

    MyQueue(const MyQueue<val_type>& rhs) :
      MyQueue() {
      log_me();
	  if (rhs.empty()) return;

	  flying_hamster(rhs.cap);
	  size_t idx = 0u;
	  for (size_t i = rhs.first; i != rhs.last; i = rhs.next(i), ++idx) {
		  m_data[idx] = rhs.m_data[i];
	  }
	  size = rhs.size;
	  first = 0;
	  last = idx;
    }// !ctor(&&)

    MyQueue(size_t n, const val_type& val):
      MyQueue(){
      if(n < 1) return;
      reserve(n);
      for(size_t i=0u; i < n; ++i){
	  push(val);
      }
    }

    MyQueue<val_type>& operator= (MyQueue<val_type>&& rhs) {
      log_me();
      clear();

      this->cap = rhs.cap;
      this->size = rhs.size;
      this->first = rhs.first;
      this->last = rhs.last;
      this->m_data = rhs.m_data;

      rhs.m_data = nullptr;
      rhs.cap = 0u;
      rhs.size = 0u;
      rhs.first = 0u;
      rhs.last = 0u;

      return *this;
    }// !operator=(&&)

    MyQueue<val_type>& operator= (const MyQueue<val_type>& rhs) {
      log_me();
      if (rhs.empty()) {
		clear();
        return *this;
      }
	  first = 0u; last = 0u; size = 0u;
      reserve(rhs.cap);
      size_t idx = 0u;
      for (size_t i = rhs.first; i != rhs.last; i = rhs.next(i),++idx) {
        m_data[idx]=rhs.m_data[i];
      }
      size = rhs.size;
      first = 0;
      last = idx;
      return *this;
    }// !operator=(&)

    /**
     * \brief realloc and normalize buffer with
     * specified capacity
     * \param[in] new_cap - new capacity of buffer
     * \remarks all data is moved to the new array and normalized
     * \ throws std::invalid_argument
     */
    void
    flying_hamster (size_t new_cap)
    {
      log_me();
      if (new_cap < size)
	throw std::invalid_argument ("specified capacity too small");
      val_type* pTemp = new val_type[new_cap];
      size_t idx = 0u;
      for (size_t i = first; i != last; i = next (i), ++idx)
	{
	  pTemp[idx] = std::move (m_data[i]);
	}
      if(nullptr !=m_data)
        delete[] m_data;
      m_data = pTemp;
      pTemp = nullptr;
      cap = new_cap;
      first = 0;
      last = idx;
    }// !flying_hamster

    //---PUSH---//
    void
    push (const val_type& el)
    {
      log_me();
	  if (full())
		  flying_hamster(cap * 2);

	  if (!empty())
		  last = next(last);
	  m_data[last] = el;
	  ++size;
    } // !push(&)
    
    void
    push (val_type&& el)
    {
      log_me();
      if (full ())
	flying_hamster (cap * 2);

	  if (!empty())
		last = next(last);
	  m_data[last] = std::move(el);
	  ++size;
    } // !push(&&)

    //---RESERVE---//
    void
    reserve (size_t sz)
    {
      log_me();
      // do nothing
      if (cap - size >= sz)
	{
	  return;
	}
      // alllocate some yet memory
      flying_hamster (size + sz);
    } // !reserve


	//------------------------------------------------------//

	template<typename T> void _push(T&& el) {
		if (full())
			flying_hamster(cap * 2);

		if (!empty())
			last = next(last);
		m_data[last] = std::forward<T>(el);
		++size;
	}

	//------------------------------------------------------//

    //---POP---//
    val_type
    pop ()
    {
      log_me();
      if (empty ())
	throw std::runtime_error ("the queue is empty");

      size_t idx = first;
      if (first != last)
	first = next (first);
      --size;
      return std::move (m_data[idx]);
    } // !pop

private:
	const size_t init_val_ = 10u;
	const size_t delta = 2u;
	val_type* m_data = nullptr;
	size_t first = 0u;
	size_t last  = 0u;
	size_t cap   = 0u;
	size_t size  = 0u;

    // stupid clear
    void
    clear ()
    {
      log_me();
      if (nullptr != m_data)
	delete[] m_data;
      m_data = nullptr;
      cap   = 0u;
      size  = 0u;
      first = 0u;
      last  = 0u;
    }

    // stupid alloc
    void
    alloc (size_t sz)
    {
      log_me();
      if (nullptr != m_data)
	clear ();
      m_data = new val_type[sz];
      cap = sz;
    }
  size_t next(size_t from) const { return ((from + 1) % cap); }

public:
  bool   empty()        const    { return size == 0u;  }
  bool   full()         const    { return size >= cap; }
  size_t get_first()    const    { return first;       }
  size_t get_last()     const    { return last;        }
  size_t get_size()     const    { return this->size;  }
  size_t get_capacity() const    { return cap;         }

};

#endif // !__CYCLED_QUEUE_H__
