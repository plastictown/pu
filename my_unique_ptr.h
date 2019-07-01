#ifndef __MY_UNIQUE_PTR_H__
#define __MY_UNIQUE_PTR_H__

#include <exception>

template<class T>
  class my_unique_ptr{
  public:
  my_unique_ptr():
    data(nullptr){}
  ~my_unique_ptr(){
    if(nullptr != data)
      delete data;
  }

  my_unique_ptr(const my_unique_ptr&) = delete;
  my_unique_ptr<T>& operator=(const my_unique_ptr<T>&) = delete;

  my_unique_ptr(T* ptr){
    data = ptr;
  }

  my_unique_ptr<T>& operator=(my_unique_ptr<T>&& rhs) {
    clear();
    if (!rhs)    
      return *this;
    data = rhs.data;
    rhs.data = nullptr;
    return *this;
  }

  my_unique_ptr(my_unique_ptr<T>&& rhs){
    *this = std::forward<my_unique_ptr<T>>(rhs);
  }

  T* get() const{
    return data;
  }

  T* operator->() const{
    return data;
  }

  T& operator *() {
    if (nullptr == data) {
      throw std::runtime_error("null pointer!");
    }
    return *data;
  }

  operator bool() const {
    return (nullptr != data);
  }

  private:

    void clear() {
      if (nullptr != data) {
        delete data;
        data = nullptr;
      }
  }
  T* data = nullptr;
};



#endif /* __MY_UNIQUE_PTR_H__ */
