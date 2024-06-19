// olivia 
// 23:16 

#pragma once
#include <cstdint>
#include <atomic>

namespace stl{
  class Mutex{
public:
    Mutex(){}
    void lock(){
      flag=true;
    }
    void unlock(){
      flag=false;
    }
    bool try_lock(){
      if(flag){
        return false;
      }else{
        flag= true;
        return flag;
      }
    }
    ~Mutex(){}

private:
    Atomic<bool> flag{false};
  }
}
