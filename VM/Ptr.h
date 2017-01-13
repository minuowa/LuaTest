#pragma once
template<typename T>
class Ptr {
  private:
    T* object_;
  public:
    Ptr( T* obj )
        : object_( obj ) {
        if ( object_ )
            object_->AddReference();
    }

    Ptr( Ptr<T>& ptr )
        : object_( ptr.GetObject() ) {
        if ( object_ )
            object_->AddReference();
    }

    Ptr operator=( Ptr<T> ptr ) {
        this->Dec();
        object_ = ptr.GetObject();
        if ( object_ )
            object_->AddReference();
    }

    T* operator->() {
        return object_;
    }

    ~Ptr() {
        this->Dec();
    }
  public:
    T* GetObject() {
        return object_;
    }
    bool Valid() {
        return object_;
    }
  private:
    void Dec() {
        if ( object_ && object_->DecReference() == 0 ) {
            delete object_;
            object_ = nullptr;
        }
    }
};

