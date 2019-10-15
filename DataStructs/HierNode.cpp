#include "DataStructs/HierNode.h"

namespace zvd {

HierNode::HierNode() : next_(0), prev_(0), parent_(0), child_(0) {}

bool HierNode::IsLinked() const { return parent_ != 0; }

HierNode::ErrorReason HierNode::IsAllowedToAppend(HierNode* candidateForChild) {
    // assert (candidateForChild);
    if (candidateForChild->IsLinked())
        return kER_LINKED;

    HierNode* checkedNode = this;
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
    if (child_ == this) {
        child_ = next_;
    }
    parent_ = 0;
    next_ = prev_ = 0;
}

HierNode* HierNode::Parent() {
    return parent_;
}

HierNode* HierNode::FirstChild() {
    return child_;
}

HierNode* HierNode::Next() { return next_; }

HierNode* HierNode::Prev() { return prev_; }

HierNode* HierNode::Root() {
    HierNode* root = this;
    while (root->parent_ != 0) {
        root = root->parent_;
    }
    return root;
}
} // end of zvd
