 #pragma once

class STUUtils
{
public:
  template <typename T> static T *GetSTUPlayerComponent(APawn *APawn)
  {
    if (!APawn) return nullptr;
    const auto Component = APawn->GetComponentByClass(T::StaticClass());
    return Cast<T>(Component);
  }
};