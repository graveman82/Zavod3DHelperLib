//------------------------------------------------------------------------------
//  NodeBase.cpp
//  This file is part of the "Zavod3D Project".
//	For conditions of distribution and use, see copyright notice in LICENSE file.
//	
//	Copyright (C) 2012-2019 Marat Sungatullin
//------------------------------------------------------------------------------
#include "DataStructs/NodeBase.h"

namespace zvd {

//------------------------------------------------------------------------------
/**
*/
NodeBase::~NodeBase() {
	// empty
}

//------------------------------------------------------------------------------
/**
	Обновляет кэшированнные данные узлов, начиная с самого верхнего
	"грязного" узла в ветке, которой принадлежит данный узел.
*/
void 
NodeBase::Update(unsigned long dirtyBitIndex) {
	NodeBase* dirtyNode = 0;
	NodeBase* node = this;
	while (node != 0) {
		if (node->Dirty(dirtyBitIndex)) {
			dirtyNode = node;
		}
		node = node->Parent();
	}

	if (dirtyNode != 0)
		dirtyNode->UpdateBranch(dirtyBitIndex);
}

//------------------------------------------------------------------------------
/**
	Рекурсивное обновление кэшированных данных в ветке, где этот узел - корень.
*/
void 
NodeBase::UpdateBranch (unsigned long dirtyBitIndex, bool fForceUpdate) {
	if (Dirty(dirtyBitIndex) || fForceUpdate) {
		//assert (!IsLinked() || !Parent()->Dirty(dirtyBitIndex)); // parent must not be dirty
		UpdateCachedData(dirtyBitIndex);
		flags_ &= ~(1ul << dirtyBitIndex);
		fForceUpdate = true;
	}
	for (NodeBase* child = FirstChild(); child != 0; child = child->Next()) {
		child->UpdateBranch(dirtyBitIndex, fForceUpdate);
	}
}

} // end of zvd
