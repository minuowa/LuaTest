#pragma once
class PointerBase {
  public:
    PointerBase();
    virtual ~PointerBase();

    const int GetReferenceCount() const;
    int DecReference();
    int AddReference();
  private:
    int reference_;
};

