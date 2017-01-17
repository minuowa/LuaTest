#pragma once
/// strong reference
template<typename T>
class Pointer {
  private:
    T* object_;
  public:
    Pointer(T* obj)
        : object_(obj) {
        if (object_)
            object_->AddReference();
    }

    Pointer(const Pointer<T>& ptr)
        : object_(ptr.GetObject()) {
        if (object_)
            object_->AddReference();
    }

    Pointer& operator=(Pointer<T> ptr) {
        this->Dec();
        object_ = ptr.GetObject();
        if (object_)
            object_->AddReference();
        return *this;
    }

    T* operator->() const {
        return object_;
    }

    bool operator==(T* ptr) {
        return object_ == ptr;
    }
    bool operator==(const Pointer<T>& ptr) const {
        return object_ == ptr.GetObject();
    }
    bool operator==(Pointer<T>& ptr) {
        return object_ == ptr.GetObject();
    }
    bool operator==(const Pointer<T> ptr) {
        return object_ == ptr.GetObject();
    }

    ~Pointer() {
        this->Dec();
    }
  public:
    T* GetObject() const {
        return object_;
    }
    bool Valid() const {
        return object_ != nullptr;
    }
    void RemoveReference() {
        this->Dec();
        object_ = nullptr;
    }
  private:
    void Dec() {
        if (object_ && object_->DecReference() == 0) {
            delete object_;
            object_ = nullptr;
        }
    }
};

