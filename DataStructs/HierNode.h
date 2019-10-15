#ifndef ZVD_DATASTRUCTS_HIERNODE_H
#define ZVD_DATASTRUCTS_HIERNODE_H

namespace zvd {

/// ���� �������������� ������
class HierNode {
public:
    enum ErrorReason{
        kER_OK,
        kER_LINKED, ///< ���� ��� ����������� (� ���� ���� ��������).
        /** ������� ������������� ���� �����, ��� �������� � ������,
        ����� ���� � ��� �� ���� ����������� ������ � ����� ����� ����� ��������.*/
        kER_CYCLING,
    };
protected:
    // ��������� � ���������� ����, � ������� ��� �� ��������, ��� � ������ ����
    HierNode* next_, *prev_;
    HierNode* parent_;
    HierNode* child_; // ������ �������� ����

public:
    HierNode();

    bool IsLinked() const;
    /// ���������� kER_OK, ���� �������� ���� ����� ���� ����������� � �������� ���������.
    ErrorReason IsAllowedToAppend(HierNode* candidateForChild);
    /// ������������ �������� ���� � �������� ���������.
    ErrorReason Append(HierNode* candidateForChild);
    /// ����������� ���� �� �������������.
    void Unlink();

    HierNode* Parent();
    HierNode* FirstChild();
    /// ��������� � ������ �������� ����� ��������.
    HierNode* Next();
    /// ���������� � ������ �������� ����� ��������.
    HierNode* Prev();
    /// ���������� �������� ���� ������.
    HierNode* Root();
};

} // end of zvd

#endif // ZVD_DATASTRUCTS_HIERNODE_H


