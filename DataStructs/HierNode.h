#ifndef ZVD_DATASTRUCTS_HIERNODE_H
#define ZVD_DATASTRUCTS_HIERNODE_H

namespace zvd {

/// ”зел иерархического дерева
class HierNode {
public:
    enum ErrorReason{
        kER_OK,
        kER_LINKED, ///< ”зел уже присоединен (у него есть родитель).
        /** ѕопытка присоединени€ узла така€, что приводит к случаю,
        когда один и тот же узел встречаетс€ вверху и внизу своей ветви иерархии.*/
        kER_CYCLING,
    };
protected:
    // —ледующий и предыдущий узлы, у которых тот же родитель, что и уэтого узла
    HierNode* next_, *prev_;
    HierNode* parent_;
    HierNode* child_; // ѕервый дочерний узел

public:
    HierNode();
    ~HierNode();

    void Cleanup();

    bool IsLinked() const;
    /// ¬озвращает kER_OK, если заданный узел может быть присоединен в качестве дочернего.
    ErrorReason IsAllowedToAppend(HierNode* candidateForChild) const;
    /// ѕрисоедин€ет узел к данному в качестве дочернего.
    ErrorReason Append(HierNode* candidateForChild);
    /// ќтсоедин€ет узел от родительского.
    void Unlink();

    HierNode* Parent() const;
    HierNode* FirstChild() const;
    /// —ледующий в списке дочерних узлов родител€.
    HierNode* Next() const;
    /// ѕредыдущий в списке дочерних узлов родител€.
    HierNode* Prev() const;
    /// ¬озвращает корневой узел дерева.
    HierNode* Root() const;
};

} // end of zvd

#endif // ZVD_DATASTRUCTS_HIERNODE_H


