#include <iostream>

class Node {
public:
  int data;
  Node *next;

  Node() {}
  Node(int data) {
    this->data = data;
    this->next = nullptr;
  }
} * linkedList;

int length = 0;

/*Display all elements forming a linked list starting with
head.*/
void displayAll(Node *head) {
  if (!head) {
    std::cout << "No elements to display\n";
    return;
  }
  Node *tempHead = head;

  while (tempHead != nullptr) {
    std::cout << tempHead->data << ' ';
    tempHead = tempHead->next;
  }

  std::cout << '\n';
}

/*Return position of first node which has given data.
Return -1 if not found.*/
int search(int data) {
  int position = 0;

  Node *tempHead = linkedList;
  while (tempHead) {
    if (tempHead->data == data) {
      break;
    }

    tempHead = tempHead->next;
    position++;
  }
  if (!tempHead)
    position = -1;

  return position;
}

/*insert element while keeping sorted order in mind*/
void insert(Node *element) {
  length++;
  if (linkedList == nullptr)
    linkedList = element;

  else {
    Node *tempHead = linkedList;
    if (linkedList->data > element->data) {
      element->next = linkedList;
      linkedList = element;

    } else {
      while (tempHead->next != nullptr) {
        if (element->data < tempHead->next->data) {
          element->next = tempHead->next;
          tempHead->next = element;
          return;
        }
        tempHead = tempHead->next;
      }
      // tempHead->next is nullptr
      // element->data is greatest in size, append at back
      tempHead->next = element;
    }
  }
}

/*Delete element at position.
Delete last element if position > length.*/
void delNode(int position) {
  if (linkedList == nullptr)
    return;

  Node *tempHead = linkedList;

  if (position == 0) {
    linkedList = linkedList->next;

  } else {
    if (length < position)
      position = length - 1;

    // . . . . i x . .
    // 0 1 2 3 4 5 6 7
    // traverse till 'i'
    for (int i = 0; i < position - 1; i++) {
      tempHead = tempHead->next;
    }

    Node *toRelease = tempHead->next;
    if (!toRelease) // only one element in list
      linkedList = nullptr;
    else
      tempHead->next = toRelease->next;
    delete toRelease;
  }
  length--;
}

int main() {
  char choice;
  std::cout << "Linked List\n"
               "a) Insert a new element\t"
               "b) Delete an existing element (by position)\n"
               "c) Search an element\t"
               "d) Display all elements\n"
               "e) Exit\n";

  while (true) {
    std::cout << "\nYour choice: ";
    std::cin >> choice;

    switch (choice) {
    case 'a':
    case 'b':
    case 'c':
      int val;
      std::cout << "Enter value: ";
      std::cin >> val;

      switch (choice) {
      case 'a':
        insert(new Node(val));
        break;
      case 'b':
        delNode(val);
        break;
      case 'c':
        int position = search(val);
        if (position == -1)
          std::cout << "Element not found";
        else
          std::cout << "Found at position: " << position;
        std::cout << '\n';
        break;
      }
      break;

    case 'd':
      displayAll(linkedList);
      break;
    case 'e':
      return 0;
    default:
      std::cout << "Weird Input\n";
    }
  }
}