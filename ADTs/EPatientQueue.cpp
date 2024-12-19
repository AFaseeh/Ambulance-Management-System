#include "EPatientQueue.h"

void EPatientQueue::InsertAtBeginning(Patient* p)
{
    int pri = p->GetSeverity();
    if (head != nullptr && head->getPri() >= pri)
    {
        pri = head->getPri() + 1;
    }

    priNode<Patient *>* newNode = new priNode<Patient *>(p, pri);

    newNode->setNext(head);
    head = newNode;
    count++;
}
