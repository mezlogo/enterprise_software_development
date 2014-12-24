#include <stdlib.h>
#include "Key.h"
#include "Configuration.h"
#include "LinkedListNode.h"
#include "LinkedListHandler.h"

#include "SimpleCUnit.h"

void test_case() {
    Key key1 = {10, 10};
    Key key2 = {40, 20};
    Key key3 = {50, 30};

    LinkedListNode n1 = {&key1};
    LinkedListNode n2 = {&key2};
    LinkedListNode n3 = {&key3};

    assertTrue("Root shouldn't be null", (unsigned long) NULL != (unsigned long) &n1);

    assertLongEquals("Add success", LINKED_LIST_NODE_SUCCESS_OP,  addLinkedListNode(&n1, &n2));
    assertLongEquals("Add success", LINKED_LIST_NODE_SUCCESS_OP,  addLinkedListNode(&n1, &n3));

    assertLongEquals("Find success", (unsigned long) &n3, (unsigned long) findLinkedListNodeByKey(&n1, &key3));
    assertLongEquals("Find fail", (unsigned long) NULL, (unsigned long) findLinkedListNodeByKey(&n3, &key1));
    assertLongEquals("Find fail", (unsigned long) NULL, (unsigned long) findLinkedListNodeByKey(NULL, &key1));

    assertLongEquals("Root is null", LINKED_LIST_NODE_ROOT_IS_NULL,  addLinkedListNode(NULL, &n3));

    assertLongEquals("n1 should ref n2", (unsigned long) &n2, (unsigned long) n1.next);
    assertLongEquals("n1 should ref n3 through n2", (unsigned long) &n3, (unsigned long) (n1.next->next));

    assertLongEquals("Remove success", LINKED_LIST_NODE_SUCCESS_OP,  removeLinkedListNode(&n1, &n2));

    assertLongEquals("n1 should ref n3 without n2", (unsigned long) &n3, (unsigned long) n1.next);

    assertLongEquals("You can't remove root", LINKED_LIST_NODE_ROOT_IS_CANT_BE_REMOVED,  removeLinkedListNode(&n1, &n1));

    assertLongEquals("Nothing to remove", LINKED_LIST_NODE_NOT_FOUND,  removeLinkedListNode(&n1, &n2));

}

int main(int argc, char** argv) {
    testSuit("Linked list handler suit", 1,
	     initTestCase("Main test", &test_case)
	    );
    return 0;
}
