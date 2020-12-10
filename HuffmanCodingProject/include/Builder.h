#ifndef __BUILDER
#define __BUILDER
#include "HuffmanCallable.h"

class Builder
{
public:
    virtual void buildMode(Mode m) {}
    virtual void buildInput(const std::string & = "") {}
    virtual void buildOutput(const std::string & = "") {}
    virtual void buildTreeStream(const std::string & = "") {}
    virtual void buildTreeVizStream(const std::string & = "") {}

    Builder() = default;
    virtual ~Builder() = default;
};

class HuffmanCodeBuilder : public Builder
{
private:
    HuffmanCallable hcallable;

public:
    HuffmanCodeBuilder() = default;
    ~HuffmanCodeBuilder() = default;
    void buildMode(Mode m) override;
    void buildInput(const std::string & = "") override;
    void buildOutput(const std::string & = "") override;
    void buildTreeStream(const std::string & = "") override;
    void buildTreeVizStream(const std::string & = "") override;
    HuffmanCallable &getBuilt();
};

#endif