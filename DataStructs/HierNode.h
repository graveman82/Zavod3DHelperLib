#ifndef ZVD_DATASTRUCTS_HIERNODE_H
#define ZVD_DATASTRUCTS_HIERNODE_H
//------------------------------------------------------------------------------
/**
	This file is part of the "Zavod3D Project".
	For conditions of distribution and use, see copyright notice in LICENSE file.

	Copyright (C) 2012-2019 Marat Sungatullin
*/

namespace zvd {

//------------------------------------------------------------------------------
/**
	@class HierNode
    @ingroup DataStructs

	���� �������������� ������.
*/
class HierNode {
public:
	///
    enum ErrorReason{
        kER_OK,
        kER_LINKED, ///< ���� ��� ����������� (� ���� ���� ��������).
        /** ������� ������������� ���� �����, ��� �������� � ������,
        ����� ���� � ��� �� ���� ����������� ������ � ����� ����� ����� ��������.*/
        kER_CYCLING,
    };

	/// �����������.
    HierNode();
	/// ����������.
    virtual ~HierNode();
	/// ������� ��� ����� ���� � ������� ������.
    void Cleanup();

	/// ���������, ����������� �� ��� ���� � ������.
    bool IsLinked() const;
    /// ������������ ���� � ������� � �������� ���������.
    ErrorReason Append(HierNode* candidateForChild);
    /// ����������� ���� �� �������������.
    bool Unlink();

	/// �������� ������������ ����.
    HierNode* Parent() const;
	/// �������� ������ �������� ����.
    HierNode* FirstChild() const;
    /// �������� ��������� � ������ �������� ����� ��������.
    HierNode* Next() const;
    /// �������� ���������� � ������ �������� ����� ��������.
    HierNode* Prev() const;
    /// �������� �������� ���� ������.
    HierNode* Root() const;

private:
    // ��������� � ���������� ����, � ������� ��� �� ��������, ��� � � ������� ����.
    HierNode* next_;
	HierNode* prev_;

    HierNode* parent_;
	// ������ �������� ����.
    HierNode* child_;

private:
	/// ���������� kER_OK, ���� �������� ���� ����� ���� ����������� � �������� ���������.
    ErrorReason IsAllowedToAppend(HierNode* candidateForChild) const;
};

//------------------------------------------------------------------------------
/**
*/
inline
bool
HierNode::IsLinked() const { return parent_ != 0; }

//------------------------------------------------------------------------------
/**
*/
inline
HierNode*
HierNode::Parent() const {
    return parent_;
}

//------------------------------------------------------------------------------
/**
*/
inline
HierNode*
HierNode::FirstChild() const {
    return child_;
}

//------------------------------------------------------------------------------
/**
*/
inline
HierNode*
HierNode::Next() const { return next_; }

//------------------------------------------------------------------------------
/**
*/
inline
HierNode*
HierNode::Prev() const { return prev_; }

//------------------------------------------------------------------------------
/**
*/
inline
HierNode*
HierNode::Root() const {
    const HierNode* root = this;
    while (root->parent_ != 0) {
        root = root->parent_;
    }
    return const_cast<HierNode*>(root);
}

} // end of zvd
//------------------------------------------------------------------------------
#endif // ZVD_DATASTRUCTS_HIERNODE_H


