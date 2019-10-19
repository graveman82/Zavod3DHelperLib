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

	Узел иерархического дерева.
*/
class HierNode {
public:
	///
	enum ErrorReason{
		kER_OK,
		kER_LINKED, ///< Узел уже присоединен (у него есть родитель).
		/** Попытка присоединения узла такая, что приводит к случаю,
		когда один и тот же узел встречается вверху и внизу своей ветви иерархии.*/
		kER_CYCLING,
	};

	/// Конструктор.
	HierNode();
	/// Деструктор.
	virtual ~HierNode();
	/// Удаляет все связи узла с другими узлами.
	void Cleanup();

	/// Проверяет, присоединен ли уже узел к дереву.
	bool IsLinked() const;
	/// Присоединяет узел к данному в качестве дочернего.
	ErrorReason Append(HierNode* candidateForChild);
	/// Отсоединяет узел от родительского.
	bool Unlink();

	/// Получить родительский узел.
	HierNode* Parent() const;
	/// Получить первый дочерний узел.
	HierNode* FirstChild() const;
	/// Получить следующий в списке дочерних узлов родителя.
	HierNode* Next() const;
	/// Получить предыдущий в списке дочерних узлов родителя.
	HierNode* Prev() const;
	/// Получить корневой узел дерева.
	HierNode* Root() const;

private:
	// Следующий и предыдущий узлы, у которых тот же родитель, что и у данного узла.
	HierNode* next_;
	HierNode* prev_;

	HierNode* parent_;
	// Первый дочерний узел.
	HierNode* child_;

private:
	/// Возвращает kER_OK, если заданный узел может быть присоединен в качестве дочернего.
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


