#ifndef ZVD_DATASTRUCTS_NODEBASE_H
#define ZVD_DATASTRUCTS_NODEBASE_H
//------------------------------------------------------------------------------
/**
	This file is part of the "Zavod3D Project".
	For conditions of distribution and use, see copyright notice in LICENSE file.

	Copyright (C) 2012-2019 Marat Sungatullin
*/

#include "DataStructs/HierNode.h"

namespace zvd {

//------------------------------------------------------------------------------
/**
	@class NodeBase
	@ingroup DataStructs

	Базовый интерфейс узла иерархического дерева с возможностью хранения
	кэшированных данных.

	Для использования этого класса, создайте производный класс и реализуйте в нем
	метод UpdateCachedData(). Например:
	@code
	// Класс узла графа сцены
	class SceneNode : public NodeBase {
	public:
		virtual void UpdateCachedData(unsigned long dirtyBitIndex) {
			// Обновить матрицу мировой трансформации узла комбинацией
			//матрицы его локальной трансформации и матрицы мировой
			//трансформации родительского узла.
			//
		}

		// В реализации метода возврата матрицы мировой трансформации
		// нужно вызвать метод Update().

		// При изменении локальной матрицы трансформации, нужно вызвать SetDirty().
	};
	@endcode

*/
class NodeBase : public HierNode {
public:
	virtual ~NodeBase();

	/// Проверка актуальности кэшированных данных.
	bool Dirty(unsigned long dirtyBitIndex) const;
	/// Вызывать перед любым запросом кэшированных данных.
	void Update(unsigned long dirtyBitIndex);

	ErrorReason Append(NodeBase* candidateForChild, unsigned long dirtyBitIndex);
	void Unlink(unsigned long dirtyBitIndex);

	NodeBase* Parent() const;
	NodeBase* FirstChild() const;
	NodeBase* Next() const;
	NodeBase* Prev() const;
	NodeBase* Root() const;


protected:
	/// Вызвать, когда нарушена актуальность кэшированных данных.
	void SetDirty(unsigned long dirtyBitIndex);
	/// Интерфейс для обновления кэшированных данных.
	virtual void UpdateCachedData(unsigned long dirtyBitIndex) = 0;

private:
	void UpdateBranch (unsigned long dirtyBitIndex, bool fForceUpdate = false);

	unsigned long flags_;
};

//------------------------------------------------------------------------------
/**
*/
inline
bool
NodeBase::Dirty(unsigned long dirtyBitIndex) const {
	return (flags_ & (1ul << dirtyBitIndex));
}

//------------------------------------------------------------------------------
/**
*/
inline
HierNode::ErrorReason
NodeBase::Append(NodeBase* candidateForChild, unsigned long dirtyBitIndex) {
	HierNode::ErrorReason er = HierNode::Append(candidateForChild);
	if (kER_OK == er) {
		SetDirty(dirtyBitIndex);
	}
	return er;
}

//------------------------------------------------------------------------------
/**
*/
inline
void
NodeBase::Unlink(unsigned long dirtyBitIndex) {
	if (HierNode::Unlink()) {
		SetDirty(dirtyBitIndex);
	}
}

//------------------------------------------------------------------------------
/**
*/
inline
NodeBase*
NodeBase::Parent() const {
	return static_cast<NodeBase*>(HierNode::Parent());
}

//------------------------------------------------------------------------------
/**
*/
inline
NodeBase*
NodeBase::FirstChild() const {
	return static_cast<NodeBase*>(HierNode::FirstChild());
}

//------------------------------------------------------------------------------
/**
*/
inline
NodeBase*
NodeBase::Next() const {
	return static_cast<NodeBase*>(HierNode::Next());
}

//------------------------------------------------------------------------------
/**
*/
inline
NodeBase*
NodeBase::Prev() const {
	return static_cast<NodeBase*>(HierNode::Prev());
}

//------------------------------------------------------------------------------
/**
*/
inline
NodeBase*
NodeBase::Root() const {
	return static_cast<NodeBase*>(HierNode::Root());
}

//------------------------------------------------------------------------------
/**
*/
inline
void
NodeBase::SetDirty(unsigned long dirtyBitIndex) {
	flags_ |= (1ul << dirtyBitIndex);
}

} // end of zvd
//------------------------------------------------------------------------------
#endif // ZVD_DATASTRUCTS_NODEBASE_H

