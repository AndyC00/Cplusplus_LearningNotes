#ifndef ENTITY_H
#define ENTITY_H

class Entity 
{
public:
    Entity() {}
    virtual ~Entity() {}

    bool m_bVisible;
    bool IsVisible()
    {
        return m_bVisible;
    }
};

#endif // ENTITY_H
