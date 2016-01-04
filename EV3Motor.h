#pragma once

class EV3Motor
{
public:
    EV3Motor();
    EV3Motor(const EV3Motor& orig);
    virtual ~EV3Motor();

    enum TYPE
    {
        LARGE,
        MEDIUM
    };
private:
    TYPE _type;
};

