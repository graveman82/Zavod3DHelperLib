#include "DataStructs/HierNode.h"

namespace zvd {

HierNode::HierNode() : next_(0), prev_(0), parent_(0), child_(0) {}

HierNode::~HierNode() {
    Cleanup();
}

void HierNode::Cleanup() {
    Unlink();
    HierNode* child = child_;
    while (child != 0) {
        HierNode* nextChild = child->next_;
        child->Unlink();
        child = nextChild;
    }
    child_ = 0;
}

bool HierNode::IsLinked() const { return parent_ != 0; }

HierNode::ErrorReason HierNode::IsAllowedToAppend(HierNode* candidateForChild) const {
    // assert (candidateForChild);
    if (candidateForChild->IsLinked())
        return kER_LINKED;

    const HierNode* checkedNode = this;
    while (checkedNode != 0) {
        if (checkedNode == candidateForChild)
            return kER_CYCLING;
        checkedNode = checkedNode->parent_;
    }
    return kER_OK;
}

HierNode::ErrorReason HierNode::Append(HierNode* candidateForChild) {
    // assert (candidateForChild);
    ErrorReason er = IsAllowedToAppend(candidateForChild);
    if (kER_OK != er)
        return er;

    if (child_ != 0) {
        candidateForChild->next_ = child_;
        child_->prev_ = candidateForChild;
    }
    child_ = candidateForChild;
    return kER_OK;
}

void HierNode::Unlink() {
    if (!IsLinked()) return;

    if (next_ != 0) {
        next_->prev_ = prev_;
    }
    if (prev_ != 0) {
        prev_->next_ = next_;
    }
    //assert(parent_);
    if (parent_->child_ == this) {
        parent_->child_ = next_;
    }
    parent_ = 0;
    next_ = prev_ = 0;
}

HierNode* HierNode::Parent() const {
    return parent_;
}

HierNode* HierNode::FirstChild() const {
    return child_;
}

HierNode* HierNode::Next() const { return next_; }

HierNode* HierNode::Prev() const { return prev_; }

HierNode* HierNode::Root() const {
    const HierNode* root = this;
    while (root->parent_ != 0) {
        root = root->parent_;
    }
    return const_cast<HierNode*>(root);
}
} // end of zvd
