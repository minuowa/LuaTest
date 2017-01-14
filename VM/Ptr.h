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

    Ptr& operator=( Ptr<T> ptr ) {
        this->Dec();
        object_ = ptr.GetObject();
        if ( object_ )
            object_->AddReference();
        return *this;
    }

    T* operator->() {
        return object_;
    }

    bool operator==(T* ptr) {
        return object_ == ptr;
    }
    bool operator==(const Ptr<T>& ptr) const {
        return object_ == ptr.GetObject();
    }
    bool operator==(Ptr<T>& ptr) {
        return object_ == ptr.GetObject();
    }
    bool operator==(const Ptr<T> ptr) {
        return object_ == ptr.GetObject();
    }

    ~Ptr() {
        this->Dec();
    }
  public:
    T* GetObject() const {
        return object_;
    }
    bool Valid() {
        return object_;
    }
    void ClearObject() {
        object_ = nullptr;
    }
  private:
    void Dec() {
        if ( object_ && object_->DecReference() == 0 ) {
            delete object_;
            object_ = nullptr;
        }
    }
};

