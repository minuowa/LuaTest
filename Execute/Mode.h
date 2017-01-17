#pragma once

class Result {
  public:
    template<typename T>
    static T GetR() {
    }

    template<>
    static int GetR() {
        return 10;
    }
    template<>
    static void GetR() {
    }
};

template<typename RET>
class Mode {
  public:
    static RET GetReturn() {
        return Result::GetR<RET>();
    }
};

template<>
class Mode<void> {
  public:
    static void GetReturn() {
        return Result::GetR<void>();
    }
};

template<typename RET = void>
RET getMode() {
    return Mode<RET>::GetReturn();
}
