#pragma once

namespace R2D
{

template<typename FormatType, typename TClass, typename... ExtraArgs>
class IDeserializer
{
public:
    virtual ~IDeserializer() = default;

    virtual void deserialize(const FormatType& input, TClass& tclass, ExtraArgs&... extraArgs) const = 0;
};

}



