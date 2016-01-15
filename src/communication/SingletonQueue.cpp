#include "SingletonQueue.h"

using namespace ev3;

template<class T>
SingletonQueue<T> * SingletonQueue<T>::_instance = nullptr;