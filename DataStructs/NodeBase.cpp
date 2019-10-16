#include "DataStructs/NodeBase.h"

namespace zvd {

bool NodeBase::Dirty(unsigned long dirtyBitIndex) const {
	return (flags_ & (1ul << dirtyBitIndex));
}

void NodeBase::UpdateTree(unsigned long dirtyBitIndex) {
	bool fUpdate = false;
	for (NodeBase* node = this; node != 0; node = node->Parent()) {
		if (node->Dirty(dirtyBitIndex)) {
			fUpdate = true;
			break;
		}
	}

	if (fUpdate)
		Root()->UpdateHierarchy(dirtyBitIndex);
}

void NodeBase::UpdateHierarchy (unsigned long dirtyBitIndex, bool fForceUpdate) {
	if (Dirty(dirtyBitIndex) || fForceUpdate) {
		//assert (!IsLinked() || !Parent()->Dirty(dirtyBitIndex)); // parent must not be dirty
		Update(dirtyBitIndex);
		flags_ &= ~(1ul << dirtyBitIndex);
		fForceUpdate = true;
	}
	for (NodeBase* child = FirstChild(); child != 0; child = child->Next()) {
		child->UpdateHierarchy(dirtyBitIndex, fForceUpdate);
	}
}

NodeBase* NodeBase::Parent() const {
    return static_cast<NodeBase*>(HierNode::Parent());
}

NodeBase* NodeBase::FirstChild() const {
    return static_cast<NodeBase*>(HierNode::FirstChild());
}

NodeBase* NodeBase::Next() const {
    return static_cast<NodeBase*>(HierNode::Next());
}

NodeBase* NodeBase::Prev() const {
    return static_cast<NodeBase*>(HierNode::Prev());
}

NodeBase* NodeBase::Root() const {
    return static_cast<NodeBase*>(HierNode::Root());
}

} // end of zvd
