#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

// Structure for File
struct File {
    string name;
    int priority;

    File(string n, int p = 0) {
        name = n;
        priority = p;
    }
};

// Binary Search Tree for File Records
class BST {
    struct Node {
        File data;
        Node *left, *right;

        Node(string name) : data(name) {
            left = right = NULL;
        }
    };

    Node* root;

    Node* insert(Node* root, string name) {
        if (root == NULL)
            return new Node(name);

        if (name < root->data.name)
            root->left = insert(root->left, name);
        else if (name > root->data.name)
            root->right = insert(root->right, name);

        return root;
    }

    bool search(Node* root, string name) {
        if (root == NULL)
            return false;

        if (root->data.name == name)
            return true;

        if (name < root->data.name)
            return search(root->left, name);

        return search(root->right, name);
    }

    Node* findMin(Node* root) {
        while (root && root->left)
            root = root->left;

        return root;
    }

    Node* deleteNode(Node* root, string name) {
        if (root == NULL)
            return root;

        if (name < root->data.name)
            root->left = deleteNode(root->left, name);

        else if (name > root->data.name)
            root->right = deleteNode(root->right, name);

        else {
            if (root->left == NULL) {
                Node* temp = root->right;
                delete root;
                return temp;
            }

            else if (root->right == NULL) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data.name);
        }

        return root;
    }

    void inorder(Node* root) {
        if (root == NULL)
            return;

        inorder(root->left);
        cout << root->data.name << " ";
        inorder(root->right);
    }

public:
    BST() {
        root = NULL;
    }

    void insertFile(string name) {
        root = insert(root, name);
        cout << "File inserted successfully!\n";
    }

    void searchFile(string name) {
        if (search(root, name))
            cout << "File found: " << name << endl;
        else
            cout << "File not found!\n";
    }

    void deleteFile(string name) {
        if (!search(root, name)) {
            cout << "File not found!\n";
            return;
        }

        root = deleteNode(root, name);
        cout << "File deleted successfully!\n";
    }

    void displayFiles() {
        if (root == NULL) {
            cout << "No files available.\n";
            return;
        }

        cout << "Files (Inorder Traversal): ";
        inorder(root);
        cout << endl;
    }
};

// Tree for Directory Structure
class Directory {
    struct Node {
        string name;
        vector<Node*> children;

        Node(string n) {
            name = n;
        }
    };

    Node* root;

    Node* findFolder(Node* node, string name) {
        if (node == NULL)
            return NULL;

        if (node->name == name)
            return node;

        for (Node* child : node->children) {
            Node* result = findFolder(child, name);

            if (result != NULL)
                return result;
        }

        return NULL;
    }

    void preorder(Node* node) {
        if (!node)
            return;

        cout << node->name << " ";

        for (Node* child : node->children)
            preorder(child);
    }

    void postorder(Node* node) {
        if (!node)
            return;

        for (Node* child : node->children)
            postorder(child);

        cout << node->name << " ";
    }

public:
    Directory() {
        root = new Node("Root");
    }

    void createFolder(string parent, string name) {
        Node* p = findFolder(root, parent);

        if (p == NULL) {
            cout << "Parent folder not found!\n";
            return;
        }

        if (findFolder(root, name) != NULL) {
            cout << "Folder already exists!\n";
            return;
        }

        p->children.push_back(new Node(name));
        cout << "Folder created successfully!\n";
    }

    void deleteFolder(string name) {
        if (root->name == name) {
            cout << "Root folder cannot be deleted!\n";
            return;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            for (int i = 0; i < current->children.size(); i++) {
                if (current->children[i]->name == name) {
                    delete current->children[i];

                    current->children.erase(
                        current->children.begin() + i
                    );

                    cout << "Folder deleted successfully!\n";
                    return;
                }

                q.push(current->children[i]);
            }
        }

        cout << "Folder not found!\n";
    }

    void searchFolder(string name) {
        if (findFolder(root, name))
            cout << "Folder found: " << name << endl;
        else
            cout << "Folder not found!\n";
    }

    void preorderDisplay() {
        cout << "Preorder: ";
        preorder(root);
        cout << endl;
    }

    void inorderDisplay() {
        cout << "Inorder: ";
        cout << root->name << " ";

        for (Node* child : root->children)
            preorder(child);

        cout << endl;
    }

    void postorderDisplay() {
        cout << "Postorder: ";
        postorder(root);
        cout << endl;
    }

    void levelOrderDisplay() {
        queue<Node*> q;
        q.push(root);

        cout << "Level Order: ";

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            cout << current->name << " ";

            for (Node* child : current->children)
                q.push(child);
        }

        cout << endl;
    }
};

// Binary Max Heap for Priority Management
class MaxHeap {
    vector<File> heap;

    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;

            if (heap[parent].priority >= heap[i].priority)
                break;

            swap(heap[parent], heap[i]);
            i = parent;
        }
    }

    void heapifyDown(int i) {
        int n = heap.size();

        while (true) {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < n &&
                heap[left].priority > heap[largest].priority)
                largest = left;

            if (right < n &&
                heap[right].priority > heap[largest].priority)
                largest = right;

            if (largest == i)
                break;

            swap(heap[i], heap[largest]);
            i = largest;
        }
    }

public:
    void insertTask(string name, int priority) {
        heap.push_back(File(name, priority));
        heapifyUp(heap.size() - 1);

        cout << "Task added successfully!\n";
    }

    void executeTask() {
        if (heap.empty()) {
            cout << "No pending tasks!\n";
            return;
        }

        cout << "Executing highest priority task: "
             << heap[0].name
             << " (Priority: " << heap[0].priority << ")\n";

        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty())
            heapifyDown(0);
    }

    void displayTasks() {
        if (heap.empty()) {
            cout << "No tasks available.\n";
            return;
        }

        cout << "Priority Tasks:\n";

        for (auto task : heap) {
            cout << task.name
                 << " - Priority: "
                 << task.priority << endl;
        }
    }
};

// Main Function
int main() {
    Directory directory;
    BST files;
    MaxHeap tasks;

    int choice;
    string name, parent;
    int priority;

    do {
        cout << "\n===== SMART FILE AND FOLDER MANAGEMENT SYSTEM =====\n";
        cout << "1. Create Folder\n";
        cout << "2. Delete Folder\n";
        cout << "3. Search Folder\n";
        cout << "4. Create File\n";
        cout << "5. Delete File\n";
        cout << "6. Search File\n";
        cout << "7. Display Files\n";
        cout << "8. Preorder Traversal\n";
        cout << "9. Inorder Traversal\n";
        cout << "10. Postorder Traversal\n";
        cout << "11. Level Order Traversal\n";
        cout << "12. Add Priority Task\n";
        cout << "13. Execute Priority Task\n";
        cout << "14. Display Priority Tasks\n";
        cout << "0. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                cout << "Enter parent folder name: ";
                cin >> parent;

                cout << "Enter new folder name: ";
                cin >> name;

                directory.createFolder(parent, name);
                break;

            case 2:
                cout << "Enter folder name to delete: ";
                cin >> name;

                directory.deleteFolder(name);
                break;

            case 3:
                cout << "Enter folder name to search: ";
                cin >> name;

                directory.searchFolder(name);
                break;

            case 4:
                cout << "Enter file name: ";
                cin >> name;

                files.insertFile(name);
                break;

            case 5:
                cout << "Enter file name to delete: ";
                cin >> name;

                files.deleteFile(name);
                break;

            case 6:
                cout << "Enter file name to search: ";
                cin >> name;

                files.searchFile(name);
                break;

            case 7:
                files.displayFiles();
                break;

            case 8:
                directory.preorderDisplay();
                break;

            case 9:
                directory.inorderDisplay();
                break;

            case 10:
                directory.postorderDisplay();
                break;

            case 11:
                directory.levelOrderDisplay();
                break;

            case 12:
                cout << "Enter task/file name: ";
                cin >> name;

                cout << "Enter priority: ";
                cin >> priority;

                tasks.insertTask(name, priority);
                break;

            case 13:
                tasks.executeTask();
                break;

            case 14:
                tasks.displayTasks();
                break;

            case 0:
                cout << "Exiting Smart File Management System...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
