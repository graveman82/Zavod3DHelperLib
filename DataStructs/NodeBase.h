#ifndef ZVD_DATASTRUCTS_NODEBASE_H
#define ZVD_DATASTRUCTS_NODEBASE_H

#include "DataStructs/HierNode.h"

namespace zvd {

class NodeBase : public HierNode {
    unsigned long flags_;

public:
    bool Dirty(unsigned long dirtyBitIndex) const;
    /// Вызывать перед любой операцией, где данные узла зависят от актуальности данных родительской цепочки
    void UpdateTree(unsigned long dirtyBitIndex);
    virtual void Update(unsigned long dirtyBitIndex) = 0;
    void UpdateHierarchy (unsigned long dirtyBitIndex, bool fForceUpdate = false);

    NodeBase* Parent() const;
    NodeBase* FirstChild() const;
    NodeBase* Next() const;
    NodeBase* Prev() const;
    NodeBase* Root() const;
};

} // end of zvd

#endif // ZVD_DATASTRUCTS_NODEBASE_H

